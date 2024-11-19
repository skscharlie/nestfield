#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_unlock_connector_req(char *req, char *resp) ;

int unlock_connector_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;
    
    make_ocpp_unlock_connector_req_message(req_buf, message_id, 1) ;

    proc_unlock_connector_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_unlock_connector_conf_message() ;
    parse_ocpp_unlock_connector_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", unlock_con_conf.status.key, unlock_con_conf.status.val.str_val) ;

    return 0 ;
}

int proc_unlock_connector_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char status_buf[STRING_20_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_unlock_connector_req_message() ;
    parse_ocpp_unlock_connector_req_message(msg.payload) ;

    strcpy(status_buf, unlock_status_values[unlock_status_unlocked]) ;

    make_ocpp_unlock_connector_conf_message(resp, msg.message_id, status_buf) ;

    return 0 ;
}
