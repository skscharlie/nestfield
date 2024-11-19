#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

#define NUMBER_OF_AUTHORIAZTION_DATA    2

raw_authorization_data rad[NUMBER_OF_AUTHORIAZTION_DATA] ;
raw_id_tag_info riti[NUMBER_OF_AUTHORIAZTION_DATA] ;
char update_type_buf[STRING_20_TYPE_LENGTH + 1] ;
char id_tag_buf[NUMBER_OF_AUTHORIAZTION_DATA][STRING_20_TYPE_LENGTH + 1] ;
char expiry_date_buf[NUMBER_OF_AUTHORIAZTION_DATA][DATE_TIME_LENGTH + 1] ;
char parent_id_tag_buf[NUMBER_OF_AUTHORIAZTION_DATA][STRING_20_TYPE_LENGTH + 1] ;
char status_buf[NUMBER_OF_AUTHORIAZTION_DATA][STRING_20_TYPE_LENGTH + 1] ;

void init_req_authorization_data() ;
int proc_send_local_list_req(char *req, char *resp) ;

int send_local_list_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_send_local_list_req rreq ;

    make_message_id(message_id) ;
    init_req_authorization_data() ;

    rreq.list_version = 1 ;
    rreq.number_of_authorization_data = NUMBER_OF_AUTHORIAZTION_DATA ;
    rreq.local_authorization_list = rad ;
    rreq.update_type = update_type_buf ;

    make_ocpp_send_local_list_req_message(req_buf, message_id, &rreq) ;

    proc_send_local_list_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_send_local_list_conf_message() ;
    parse_ocpp_send_local_list_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", send_local_lst_conf.status.key, send_local_lst_conf.status.val.str_val) ;

    return 0 ;
}

int proc_send_local_list_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char *status_buf[STRING_20_TYPE_LENGTH + 1] ;
    authorization_data *pauth_data ;

    parse_req_message(req, &msg) ;
    init_send_local_list_req_message() ;
    parse_ocpp_send_local_list_req_message(msg.payload) ;
    printf("1\n") ;

    /*
     * send_local_list_req_message를 사용한 후 memory free를 해줘야함.
     */
    pauth_data = send_local_lst_req.local_authorization_list.val.autho_data ;
    for(int i = 0 ; i < send_local_lst_req.number_of_authrization_data ; i++, pauth_data++) {
        free(pauth_data->id_tag.val.str_val) ;
        free(pauth_data->id_tag_info.val.iti_val->expiry_date.val.str_val) ;
        free(pauth_data->id_tag_info.val.iti_val->parent_id_tag.val.str_val) ;
        free(pauth_data->id_tag_info.val.iti_val->status.val.str_val) ;
        free(pauth_data->id_tag_info.val.iti_val) ;
    }
    free(send_local_lst_req.local_authorization_list.val.autho_data) ;

    strcpy(status_buf, update_status_values[update_status_accepted]) ;
    make_ocpp_send_local_list_conf_message(resp, msg.message_id, status_buf) ;

    return 0 ;
}

void init_req_authorization_data() {
    int i ;

    for(i = 0 ; i < NUMBER_OF_AUTHORIAZTION_DATA ; i++) {
        riti[i].expiry_date = expiry_date_buf[i] ;
        riti[i].parent_id_tag = parent_id_tag_buf[i] ;
        riti[i].status = status_buf[i] ;

        rad[i].id_tag = id_tag_buf[i] ;
        rad[i].id_tag_info = &riti[i] ;
    }

    strcpy(id_tag_buf[0], "B4E62CEE") ;
    strcpy(id_tag_buf[1], "A3D4F5G6") ;

    strcpy(parent_id_tag_buf[0], "C1C2C3C4") ;
    strcpy(parent_id_tag_buf[1], "C1C2C3C5") ;

    get_future_date(expiry_date_buf[0], 30) ;
    get_future_date(expiry_date_buf[1], 60) ;

    strcpy(status_buf[0], authorization_status_values[authorization_status_accepted]) ;
    strcpy(status_buf[1], authorization_status_values[authorization_status_current_tx]) ;
}
