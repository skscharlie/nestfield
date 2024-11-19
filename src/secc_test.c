#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "ocpp.h"

int main(int argc, char **argv) {
    int sock = 0 ;
    struct sockaddr_in serv_addr ;
    char buff[4096] ;
    struct ocpp_comm_buff oc_buff ;
    int datalen ;

    if(argc != 3) {
        /*
         * 각 command 에 필요한 data 는 db에 미리 넣어놓고 secc_test 실행함. 
         */
        printf("Usage : secc_test command connector_id\n") ;
        return -1 ;
    }

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error\n") ;
        return -1 ;
    }

    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_port = htons(SECC_COMM_PORT) ;

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("inet_pton error\n") ;
        return -1 ;
    }

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("connect error\n") ;
        return -1 ;
    }

    oc_buff.command = atoi(argv[1]) ;
    oc_buff.connector_id = atoi(argv[2]) ;

    printf("command : %d, connector_id : %d\n", oc_buff.command, oc_buff.connector_id) ;
    bzero(oc_buff.data, sizeof(oc_buff.data)) ;

    write(sock, &oc_buff, sizeof(oc_buff)) ;

    read(sock, &oc_buff, sizeof(oc_buff)) ;

    printf("%d\n", oc_buff.command) ;
    printf("%d\n", oc_buff.connector_id) ;
    printf("%s\n", oc_buff.data) ;

    close(sock) ;

    return 0 ;
}