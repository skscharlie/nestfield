#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

int proc_cancel_reservation_req(char *req, char *resp) ;

int cancel_reservation_test() {
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    int reservation_id ;

    make_message_id(message_id) ;
    reservation_id = 10 ;
    make_ocpp_cancel_reservation_req_message(req_buf, message_id, reservation_id) ;

    proc_cancel_reservation_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_cancel_reservation_conf_message() ;
    parse_ocpp_cancel_reservation_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", cancel_res_conf.status.key, cancel_res_conf.status.val.str_val) ;

    return 0 ;
}

int proc_cancel_reservation_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;
    init_cancel_reservation_req_message() ;
    parse_ocpp_cancel_reservation_req_message(msg.payload) ;

    make_ocpp_cancel_reservation_conf_message(resp, msg.message_id, cancel_reservation_status_values[cancel_reservation_status_accepted]) ;
    return 0 ;
}