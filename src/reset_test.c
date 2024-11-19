#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_reset_req(char *req, char *resp) ;

int reset_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    char type_buf[STRING_20_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;
    strcpy(type_buf, reset_type_values[reset_type_hard]) ;

    make_ocpp_reset_req_message(req_buf, message_id, type_buf) ;

    proc_reset_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_reset_conf_message() ;
    parse_ocpp_reset_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", rset_conf.status.key, rset_conf.status.val.str_val) ;

    return 0 ;
}

int proc_reset_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char status_buf[STRING_20_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_reset_req_message() ;
    parse_ocpp_reset_req_message(msg.payload) ;

    strcpy(status_buf, reset_status_values[reset_status_accepted]) ;
    make_ocpp_reset_conf_message(resp, msg.message_id, status_buf) ;
}