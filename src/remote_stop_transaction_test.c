#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_remote_stop_transaction_req(char *req, char *resp) ;

int remote_stop_transaction_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;

    make_ocpp_remote_stop_transaction_req_message(req_buf, message_id, 123456789) ;

    proc_remote_stop_transaction_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_remote_stop_transaction_conf_message() ;
    parse_ocpp_remote_stop_transaction_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", remote_stop_trans_conf.status.key, remote_stop_trans_conf.status.val.str_val) ;
    return 0 ;
}

int proc_remote_stop_transaction_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char status_buf[STRING_20_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_remote_stop_transaction_req_message() ;
    parse_ocpp_remote_stop_transaction_req_message(msg.payload) ;

    strcpy(status_buf, remote_start_stop_status_values[remote_start_stop_status_accepted]) ;
    make_ocpp_remote_stop_transaction_conf_message(resp, msg.message_id, status_buf) ;

    return 0 ;
}
