#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_trigger_message_req(char *req, char *resp) ;

int trigger_message_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_trigger_message_req rreq ;
    char requested_message_buf[STRING_50_TYPE_LENGTH + 1], status_buf[STRING_20_TYPE_LENGTH + 1] ;

    rreq.requested_message = requested_message_buf ;
    rreq.connector_id = 1 ;

    strcpy(rreq.requested_message, message_trigger_values[message_trigger_diagnostics_status_notification]) ;

    make_message_id(message_id) ;

    make_ocpp_trigger_message_req_message(req_buf, message_id, &rreq) ;

    proc_trigger_message_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;

    init_trigger_message_conf_message() ;

    parse_ocpp_trigger_message_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", trigger_msg_conf.status.key, trigger_msg_conf.status.val.str_val) ;

    return 0 ;
}

int proc_trigger_message_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char status_buf[STRING_20_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;

    init_trigger_message_req_message() ;
    parse_ocpp_trigger_message_req_message(msg.payload) ;

    strcpy(status_buf, trigger_message_status_values[trigger_message_status_accepted]) ;
    make_ocpp_trigger_message_conf_message(resp, msg.message_id, status_buf) ;

    return 0 ;
}