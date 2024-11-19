#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>
#include <json.h>
#include <libwebsockets.h>
#include "ocpp.h"

void *ocpp_command_input(void *arg) {
    struct lws_context *context = *(struct lws_context **)arg ;
    char buff[1024] ;

    while(true) {
        fgets(buff, sizeof(buff), stdin) ;
        buff[strlen(buff) - 1] = 0x00 ;

        if(strlen(buff) == 0)
            continue ;

        pthread_mutex_lock(&terminal_input_mutex) ;
        terminal_input_valid = true ;
        strcpy(shared_data, buff) ;
        pthread_mutex_unlock(&terminal_input_mutex) ;

        lws_cancel_service(context) ;;
    }

    printf("ocpp_command_input_ending\n") ;
    return NULL ;
}

void parse_input_command(char *command, input_command *ic) {
    char **cmd_array ;
    int number_of_command = 0, i = 0 ;
    char *token ;
    char *temp_buf ;

    temp_buf = (char *)malloc((strlen(command) + 1) * sizeof(char)) ;
    strcpy(temp_buf, command) ;

    token = strtok(temp_buf, " ") ;
    while(token != NULL) {
        number_of_command++ ;
        token = strtok(NULL, " ") ;
    }

    ic->ppcommand = (char **)malloc(number_of_command * sizeof(char *)) ;
    ic->number_of_command = number_of_command ;

    token = strtok(command, " ") ;
    while(token != NULL) {
        ic->ppcommand[i] = (char *)malloc((strlen(token) + 1) * sizeof(char)) ;
        strcpy(ic->ppcommand[i], token) ;
        token = strtok(NULL, " ") ;
        i++ ;
    }
}

void process_input_command(char *command) {
    input_command ic ;

    parse_input_command(command, &ic) ;

    for(int i = 0 ; i < charge_point_initiated_actions_length ; i++) {
        if(strcmp(charge_point_initiated_actions[i].action, ic.ppcommand[0]) == 0) {
            charge_point_initiated_actions[i].req_func(ic.ppcommand) ;
        }
    }

    for(int i = 0 ; i < ic.number_of_command ; i++) {
        free(ic.ppcommand[i]) ;
    }

    free(ic.ppcommand) ;
}