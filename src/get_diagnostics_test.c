#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <json.h>
#include "ocpp.h"

int proc_get_diagnostics_req(char *req, char *resp) ;

int get_diagnostics_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_get_diagnostics_req rreq ;
    char location_buf[STRING_255_TYPE_LENGTH + 1], start_time_buf[DATE_TIME_LENGTH + 1], stop_time_buf[DATE_TIME_LENGTH + 1] ;

    make_message_id(message_id) ;
    rreq.location = location_buf ;
    rreq.retries = 10 ;
    rreq.retry_interval = 100 ;
    rreq.start_time = start_time_buf ;
    rreq.stop_time = stop_time_buf ;

    strcpy(location_buf, "http://www.location.co.kr") ;
    get_future_date(start_time_buf, 1) ;
    get_future_date(stop_time_buf, 30) ;

    make_ocpp_get_diagnostics_req_message(req_buf, message_id, &rreq) ;

    proc_get_diagnostics_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_get_diagnostics_conf_message() ;
    parse_ocpp_get_diagnostics_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", get_diag_conf.file_name.key, get_diag_conf.file_name.val.str_val) ;
    return 0 ;
}

int proc_get_diagnostics_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char file_name_buf[STRING_50_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_get_diagnostics_req_message() ;
    parse_ocpp_get_diagnostics_req_message(msg.payload) ;

    strcpy(file_name_buf, "/Users/charlie/C/nestfield/src") ;
    make_ocpp_get_diagnostics_conf_message(resp, msg.message_id, file_name_buf) ;

    return 0 ;
}
