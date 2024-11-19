#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

int proc_change_availability_req(char *req, char *resp) ;

int change_availability_test() {
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_change_availability_req rreq ;
    char type_buf[STRING_20_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;
    strcpy(type_buf, availability_type_values[availability_type_inoperative]) ;

    rreq.connector_id = 1 ;
    rreq.type = type_buf ;

    make_ocpp_change_availability_req_message(req_buf, message_id, &rreq) ;

    proc_change_availability_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;

    init_change_availability_conf_message() ;
    parse_ocpp_change_availability_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", change_avail_conf.status.key, change_avail_conf.status.val.str_val) ;

    return 0 ;
}

int proc_change_availability_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;

    init_change_availability_req_message() ;
    parse_ocpp_change_availability_req_message(msg.payload) ;

    make_ocpp_change_availability_conf_message(resp, msg.message_id, availability_status_values[availability_status_accepted]) ;
    
    return 0 ;
}
