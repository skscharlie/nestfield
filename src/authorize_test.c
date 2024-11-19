
#include <stdio.h>
#include <strings.h>
#include <json.h>
#include "ocpp.h"

int proc_authorize_req(char *, char *) ;

int authorize_test() {
    char req_buf[1024], resp_buf[1024] ;
    ocpp_callresult_message msg ;
    int message_type_id ;
    char message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;
    make_ocpp_authorize_req_message(req_buf, message_id, "id_tag_charlie") ;  

    proc_authorize_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;

    /* 
     * ocpp message의 payload를 parse 하기 전에는 반드시 init message를 해야함. 
     */
    init_authorize_conf_message() ;
    parse_ocpp_authorize_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", auth_conf.id_tag_info.val.iti_val->expiry_date.key, auth_conf.id_tag_info.val.iti_val->expiry_date.val.str_val) ;
    printf("key : %s, value : %s\n", auth_conf.id_tag_info.val.iti_val->parent_id_tag.key, auth_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val) ;
    printf("key : %s, value : %s\n", auth_conf.id_tag_info.val.iti_val->status.key, auth_conf.id_tag_info.val.iti_val->status.val.str_val) ;
    return 0 ;
}

int proc_authorize_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char expiry_date_buf[32], parent_id_tag_buf[STRING_20_TYPE_LENGTH + 1], status_buf[MAX_STATUS_LENGTH + 1] ;
    raw_id_tag_info riti ;

    parse_req_message(req, &msg) ;

    /* 
     * ocpp message의 payload를 parse 하기 전에는 반드시 init message를 해야함. 
     */
    init_authorize_req_message() ;
    parse_ocpp_authorize_req_message(msg.payload) ;
    
    riti.expiry_date = expiry_date_buf ;
    riti.parent_id_tag = parent_id_tag_buf ;
    riti.status = authorization_status_values[authorization_status_accepted] ;

    get_future_date(expiry_date_buf, 30) ;
    strcpy(parent_id_tag_buf, "charlie 123") ;
    strcpy(status_buf, authorization_status_values[authorization_status_accepted]) ;

    make_ocpp_authorize_conf_message(resp, msg.message_id, &riti) ;

    return 0 ;
}

