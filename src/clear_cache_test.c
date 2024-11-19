#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

int proc_clear_cache_req(char *req, char *resp) ;

int clear_cache_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;
    make_ocpp_clear_cache_req_message(req_buf, message_id) ;

    proc_clear_cache_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_clear_cache_conf_message() ;
    parse_ocpp_clear_cache_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", clear_cac_conf.status.key, clear_cac_conf.status.val.str_val) ;

    return 0 ;
}

int proc_clear_cache_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;
    init_clear_cache_req_message() ;
    parse_ocpp_clear_cache_req_message(msg.payload) ;

    make_ocpp_clear_cache_conf_message(resp, msg.message_id, clear_cache_status_values[clear_cache_status_accepted]) ;
    return 0 ;
}
