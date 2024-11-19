#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_start_transaction_req(char *req, char *resp) ;

int start_transaction_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_start_transaction_req rreq ;
    char id_tag_buf[STRING_20_TYPE_LENGTH + 1], timestamp_buf[DATE_TIME_LENGTH + 1] ;

    make_message_id(message_id) ;

    rreq.connector_id = 1 ;
    rreq.id_tag = id_tag_buf ;
    rreq.meter_start = 10 ;
    rreq.reservation_id = 12345;
    rreq.timestamp = timestamp_buf ;

    strcpy(id_tag_buf, "charlie") ;
    get_future_date(timestamp_buf, 0) ;

    make_ocpp_start_transaction_req_message(req_buf, message_id, &rreq) ;

    proc_start_transaction_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_start_transaction_conf_message() ;
    parse_ocpp_start_transaction_conf_message(msg.payload) ;

    printf("key : %s.%s, value : %s\n", start_trans_conf.id_tag_info.key, 
                                        start_trans_conf.id_tag_info.val.iti_val->expiry_date.key, 
                                        start_trans_conf.id_tag_info.val.iti_val->expiry_date.val.str_val) ;
    printf("key : %s.%s, value : %s\n", start_trans_conf.id_tag_info.key, 
                                        start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.key, 
                                        start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val) ;
    printf("key : %s.%s, value : %s\n", start_trans_conf.id_tag_info.key, 
                                        start_trans_conf.id_tag_info.val.iti_val->status.key, 
                                        start_trans_conf.id_tag_info.val.iti_val->status.val.str_val) ;
    printf("key : %s, value : %d\n", start_trans_conf.transaction_id.key, start_trans_conf.transaction_id.val.int_val) ;

    return 0 ;
}

int proc_start_transaction_req(char *req, char *resp) {
    ocpp_call_message msg ;
    raw_start_transaction_conf rconf ;
    raw_id_tag_info riti ;
    char expiry_date_buf[DATE_TIME_LENGTH + 1], parent_id_tag_buf[STRING_20_TYPE_LENGTH + 1], status_buf[STRING_20_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_start_transaction_req_message() ;
    parse_ocpp_start_transaction_req_message(msg.payload) ;

    rconf.id_tag_info = &riti ;
    rconf.transaction_id = make_transaction_id() ;

    riti.expiry_date = expiry_date_buf ;
    riti.parent_id_tag = parent_id_tag_buf ;
    riti.status = status_buf ;

    get_future_date(expiry_date_buf, 60) ;
    strcpy(parent_id_tag_buf, "charlie's parent") ;
    strcpy(status_buf, authorization_status_values[authorization_status_accepted]) ;

    make_ocpp_start_transaction_conf_message(resp, msg.message_id, &rconf) ;

    return 0 ;
}