#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_status_notification_req(char *req, char *resp) ;

int status_notification_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_status_notification_req rreq ;
    char error_code_buf[STRING_25_TYPE_LENGTH + 1], info_buf[STRING_50_TYPE_LENGTH + 1], status_buf[STRING_20_TYPE_LENGTH + 1] ;
    char timestamp_buf[DATE_TIME_LENGTH + 1], vendor_id_buf[STRING_255_TYPE_LENGTH + 1], vendor_error_code_buf[STRING_50_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;

    rreq.connector_id = 1 ;
    rreq.error_code = error_code_buf ;
    rreq.info = info_buf ;
    rreq.status = status_buf ;
    rreq.timestamp = timestamp_buf ;
    rreq.vendor_id = vendor_id_buf ;
    rreq.vendor_error_code = vendor_error_code_buf ;

    strcpy(error_code_buf, charge_point_error_code_values[charge_point_error_code_no_error]) ;
    strcpy(info_buf, "connector id #1 operate well") ;
    strcpy(status_buf, charge_point_status_values[charge_point_status_available]) ;
    get_future_date(timestamp_buf, 0) ;
    strcpy(vendor_id_buf, "") ;
    strcpy(vendor_error_code_buf, "") ;

    make_ocpp_status_notification_req_message(req_buf, message_id, &rreq) ;

    proc_status_notification_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_status_notification_conf_message() ;
    parse_ocpp_status_notification_conf_message(msg.payload) ;

    return 0 ;
}

int proc_status_notification_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;
    init_status_notification_req_message() ;
    parse_ocpp_status_notification_req_message(msg.payload) ;

    make_ocpp_status_notification_conf_message(resp, msg.message_id) ;
}