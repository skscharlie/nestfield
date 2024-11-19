#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <json.h>
#include "ocpp.h"

int proc_heartbeat_req(char *req, char *resp) ;

int heartbeat_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;
    make_ocpp_heartbeat_req_message(req_buf, message_id) ;

    proc_heartbeat_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_heartbeat_conf_message() ;
    parse_ocpp_heartbeat_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", hbeat_conf.current_time.key, hbeat_conf.current_time.val.str_val) ;
    return 0 ;
}

int proc_heartbeat_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char current_time_buf[DATE_TIME_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_heartbeat_req_message() ;
    parse_ocpp_heartbeat_req_message(msg.payload) ;

    get_future_date(current_time_buf, 0) ;
    make_ocpp_heartbeat_conf_message(resp, msg.message_id,  current_time_buf) ;
    return 0 ;
}
