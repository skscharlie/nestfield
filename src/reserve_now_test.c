#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_reserve_now_req(char *req, char *resp) ;

int reserve_now_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_reserve_now_req rreq ;
    char expiry_date_buf[DATE_TIME_LENGTH + 1], id_tag_buf[STRING_20_TYPE_LENGTH + 1], parent_id_tag_buf[STRING_20_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;

    rreq.connector_id = 1 ;
    rreq.expiry_date = expiry_date_buf ;
    rreq.id_tag = id_tag_buf ;
    rreq.parent_id_tag = parent_id_tag_buf ;
    rreq.reservation_id = 123456789 ;

    get_future_date(expiry_date_buf, 365) ;
    strcpy(id_tag_buf, "charlie") ;
    strcpy(parent_id_tag_buf, "charlie's parent") ;

    make_ocpp_reserve_now_req_message(req_buf, message_id, &rreq) ;

    proc_reserve_now_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_reserve_now_conf_message() ;
    parse_ocpp_reserve_now_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", reserve_n_conf.status.key, reserve_n_conf.status.val.str_val) ;

    return 0 ;
}

int proc_reserve_now_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char status_buf[STRING_20_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_reserve_now_req_message() ;
    parse_ocpp_reserve_now_req_message(msg.payload) ;

    strcpy(status_buf, reservation_status_values[reservation_status_accepted]) ;
    make_ocpp_reserve_now_conf_message(resp, msg.message_id, status_buf) ;

    return 0 ;
}