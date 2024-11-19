#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <libwebsockets.h>
#include "ocpp.h"

void* secc_comm_main(void *arg) {
    struct lws_context *context = *(struct lws_context **)arg ;
    char buff[4096] ;

    int server_fd, new_socket ;
    struct sockaddr_in address ;
    int opt = 1 ;
    int addrlen = sizeof(address) ;
    int datalen ;
    struct ocpp_comm_buff oc_buff ;

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket fail") ;
        return NULL ;
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsocketopt fail") ;
        return NULL ;
    }

    address.sin_family = AF_INET ;
    address.sin_addr.s_addr = INADDR_ANY ;
    address.sin_port = htons(SECC_COMM_PORT) ;

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind error") ;
        return NULL ;
    }

    if(listen(server_fd, 3) < 0) {
        perror("listen error") ;
        return NULL ;
    }

    while(true) {
        if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept error") ;
            return NULL ;
        }

        read(new_socket, &oc_buff, sizeof(oc_buff)) ;

        pthread_mutex_lock(&secc_mutex) ;
        secc_data_valid = true ;
        secc_comm_end = false ;
        memcpy(shared_data, &oc_buff, sizeof(oc_buff)) ;
        pthread_mutex_unlock(&secc_mutex) ;

        lws_cancel_service(context) ;

        /*
         * OCPP server 에서 응답을 받을때까지 기다린 후 SECC 에 응답을 보내고 close 해야함.
         */

        while(true) {
            pthread_mutex_lock(&secc_mutex) ;
            if(secc_comm_end) {
                pthread_mutex_unlock(&secc_mutex) ;
                break ;
            }
            pthread_mutex_unlock(&secc_mutex) ;
            usleep(100) ;
        }

        strcpy(oc_buff.data, authorization_status_values[authorization_status_accepted]) ;
        write(new_socket, &oc_buff, sizeof(oc_buff)) ;

        close(new_socket) ;
    }
}

void process_secc_data(struct ocpp_comm_buff *oc_buff, struct lws *web_socket, struct lws_context *context) {
    char *data[2] ;
    int ret = 0 ;

    printf("process_secc_data\n") ;

    secc_ocpp_actions *soa = &so_actions[oc_buff->command] ;

    for(int i = 0 ; i < soa->number_of_ocpp_actions ; i++) {
        for(int j = 0 ; j < charge_point_initiated_actions_length ; j++) {
            if(strcmp(charge_point_initiated_actions[j].action, soa->ocpp_actions[i]) == 0) {
                pthread_mutex_lock(&ocpp_mutex) ;
                ocpp_comm_end = false ;
                pthread_mutex_unlock(&ocpp_mutex) ;
                /*
                 * terminal input 을 받아서 test하면서 만들었던 function argument 에 맟추기 위해서 하는 작업 
                 */
                data[0] = charge_point_initiated_actions[i].action ;
                data[1] = (char *)&oc_buff->connector_id ;
                ret = charge_point_initiated_actions[j].req_func(data) ;
                if(ret == -1) {
                    ocpp_comm_end = true ;
                }

                lws_callback_on_writable(web_socket) ;
                lws_service(context, 250) ;

                while(true) {
                    pthread_mutex_lock(&ocpp_mutex) ;
                    if(ocpp_comm_end) {
                        pthread_mutex_unlock(&ocpp_mutex) ;
                        break ;
                    }
                    pthread_mutex_unlock(&ocpp_mutex) ;
                    usleep(100) ;
                    lws_service(context, 250) ;
                }
                
            }
        }
        if(ret == -1) {
            break ;
        }
    }

    pthread_mutex_lock(&secc_mutex) ;
    secc_comm_end = true ;
    pthread_mutex_unlock(&secc_mutex) ;
}