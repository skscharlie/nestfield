#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <json.h>
#include "ocpp.h"

int proc_get_local_list_version_req(char *req, char *resp) ;

int get_local_list_version_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;
    make_ocpp_get_local_list_version_req_message(req_buf, message_id) ;

    proc_get_local_list_version_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_get_local_list_version_conf_message() ;
    parse_ocpp_get_local_list_version_conf_message(msg.payload) ;

    printf("key : %s, value : %d\n", get_ll_version_conf.list_version.key, get_ll_version_conf.list_version.val.int_val) ;

    return 0 ;
}

int proc_get_local_list_version_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;
    init_get_local_list_version_req_message() ;
    parse_ocpp_get_local_list_version_req_message(msg.payload) ;

    make_ocpp_get_local_list_version_conf_message(resp, msg.message_id, 10) ;

    return 0 ;
}