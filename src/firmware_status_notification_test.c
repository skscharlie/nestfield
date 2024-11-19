#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_firmware_status_notification_req(char *req, char *resp) ;

int firmware_status_notification_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    char status_buf[STRING_20_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;
    strcpy(status_buf, firmware_status_values[firmware_status_idle]) ;

    make_ocpp_firmware_status_notification_req_message(req_buf, message_id, status_buf) ;
    proc_firmware_status_notification_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_firmware_status_notification_conf_message() ;
    parse_ocpp_firmware_status_notification_conf_message(msg.payload) ;

    return 0 ;
}

int proc_firmware_status_notification_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;
    init_firmware_status_notification_req_message() ;
    parse_ocpp_firmware_status_notification_req_message(msg.payload) ;

    make_ocpp_firmware_status_notification_conf_message(resp, msg.message_id) ;

    return 0 ;
}
