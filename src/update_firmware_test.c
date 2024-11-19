#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_update_firmware_req(char *req, char *resp) ;

int update_firmware_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    char location_buf[STRING_255_TYPE_LENGTH + 1], retrieve_date_buf[DATE_TIME_LENGTH + 1] ;
    raw_update_firmware_req rreq ;

    make_message_id(message_id) ;

    rreq.location = location_buf ;
    rreq.retries = 3 ;
    rreq.retrieve_date = retrieve_date_buf ;
    rreq.retry_interval = 30 ;

    strcpy(location_buf, "http://www.updatefirmwarereq.com/download/v1.0") ;
    get_future_date(retrieve_date_buf, 0) ;

    make_ocpp_update_firmware_req_message(req_buf, message_id, &rreq) ;

    proc_update_firmware_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_update_firmware_conf_message() ;
    parse_ocpp_update_firmware_conf_message(msg.payload) ;

    return 0 ;
}

int proc_update_firmware_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;
    init_update_firmware_req_message() ;
    parse_ocpp_update_firmware_req_message(msg.payload) ;

    make_ocpp_update_firmware_conf_message(resp, msg.message_id) ;

    return 0 ;
}