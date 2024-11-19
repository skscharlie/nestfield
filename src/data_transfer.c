#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_data_transfer_req_message() {
    data_trans_req.vendor_id.key = data_transfer_req_field_names[data_trans_req_vendor_id] ;
    data_trans_req.vendor_id.val.str_val = dtr_vendor_id ;

    data_trans_req.message_id.key = data_transfer_req_field_names[data_trans_req_message_id] ;
    data_trans_req.message_id.val.str_val = dtr_message_id ;

    data_trans_req.data.key = data_transfer_req_field_names[data_trans_req_data] ;
    data_trans_req.data.val.str_val = NULL ;
}

void init_data_transfer_conf_message() {
    data_trans_conf.status.key = data_transfer_conf_field_names[data_trans_conf_status] ;
    data_trans_conf.status.val.str_val = dtc_status ;

    data_trans_conf.data.key = data_transfer_conf_field_names[data_trans_conf_data] ;
    data_trans_conf.data.val.str_val = NULL ;
}

int make_ocpp_data_transfer_req_message(char *buf, char *message_id, raw_data_transfer_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[CHARGE_POINT_INITIATED_DATA_TRANSFER_INDEX].action ;

    data_trans_req.vendor_id.key = data_transfer_req_field_names[data_trans_req_vendor_id] ;
    data_trans_req.vendor_id.val.str_val = rreq->vendor_id ;

    data_trans_req.message_id.key = data_transfer_req_field_names[data_trans_req_message_id] ;
    data_trans_req.message_id.val.str_val = rreq->message_id ;

    data_trans_req.data.key = data_transfer_req_field_names[data_trans_req_data] ;
    data_trans_req.data.val.str_val = rreq->data ;

    object = json_object_new_object() ;
    json_object_object_add(object, data_trans_req.vendor_id.key, json_object_new_string(data_trans_req.vendor_id.val.str_val)) ;
    if(data_trans_req.message_id.val.str_val != NULL)
        json_object_object_add(object, data_trans_req.message_id.key, json_object_new_string(data_trans_req.message_id.val.str_val)) ;

    if(data_trans_req.data.val.str_val != NULL)
        json_object_object_add(object, data_trans_req.data.key, json_object_new_string(data_trans_req.data.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_data_transfer_conf_message(char *buf, char *message_id, raw_data_transfer_conf *rconf) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    data_trans_conf.status.key = data_transfer_conf_field_names[data_trans_conf_status] ;
    data_trans_conf.status.val.str_val = rconf->status ;

    data_trans_conf.data.key = data_transfer_conf_field_names[data_trans_conf_data] ;
    data_trans_conf.data.val.str_val = rconf->data ;

    object = json_object_new_object() ;
    json_object_object_add(object, data_trans_conf.status.key, json_object_new_string(data_trans_conf.status.val.str_val)) ;
    if(data_trans_conf.data.val.str_val != NULL)
        json_object_object_add(object, data_trans_conf.data.key, json_object_new_string(data_trans_conf.data.val.str_val)) ;

    printf("result josn : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_data_transfer_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;
    char *ptr ;
    int ptr_len ;

    value = json_object_object_get(object, data_trans_req.vendor_id.key) ;
    strcpy(data_trans_req.vendor_id.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, data_trans_req.message_id.key) ;
    if(value != NULL)
        strcpy(data_trans_req.message_id.val.str_val, json_object_get_string(value)) ;
    else
        data_trans_req.message_id.val.str_val = NULL ;

    value = json_object_object_get(object, data_trans_req.data.key) ;
    if(value != NULL) {

        /*
        * data 의 size 가 정해져있지 않으므로 받은 data의 size를 계산하여 malloc 후 거기에 copy 함.
        * 처리가 끝나면 반드시 free 해야함.
        */
        ptr = (char *)json_object_to_json_string(value) ;
        ptr_len = strlen(ptr) ;

        data_trans_req.data.val.str_val = malloc(ptr_len + 1) ;
        strcpy(data_trans_req.data.val.str_val, ptr) ;
    }
    else
        data_trans_conf.data.val.str_val = NULL ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_data_transfer_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;
    char *ptr ;
    int ptr_len ;

    value = json_object_object_get(object, data_trans_conf.status.key) ;
    strcpy(data_trans_conf.status.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, data_trans_conf.data.key) ;
    ptr = (char *)json_object_get_string(value) ;
    ptr_len = strlen(ptr) ;

    data_trans_conf.data.val.str_val = malloc(ptr_len + 1) ;
    strcpy(data_trans_conf.data.val.str_val, ptr) ;

    json_object_put(object) ;
    return 0 ;
}

int do_data_transfer(ocpp_call_message *req, char *resp) {
    init_data_transfer_req_message() ;
    parse_ocpp_data_transfer_req_message(req->payload) ;
    
    raw_data_transfer_conf rconf ;
    rconf.status = data_transfer_status_values[data_transfer_status_accepted] ;
    rconf.data = NULL ;

    make_ocpp_data_transfer_conf_message(resp, req->message_id, &rconf) ;
    return 0 ;
}

static field_buffers field_buff[] = {
    {"vendorId", dtr_vendor_id},
    {"messageId", dtr_message_id},
    {"data", NULL}
} ;

int do_data_transfer_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_data_transfer_req rreq ;
    FILE *file = fopen(ppcommand[1], "r") ;
    if(file == NULL) {
        printf("Error opening file : %s", ppcommand[1]) ;
        return -1 ;
    }


    char line[1024] ;
    char *pdelimiter ;
    int length = sizeof(field_buff) / sizeof(field_buffers) ;
    while(fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0 ;
        pdelimiter = strchr(line, '=') ;
        *pdelimiter = 0 ;
        pdelimiter++ ;

        for(int i = 0 ; i < length ; i++) {
            if(strcmp(trim(line), field_buff[i].field_name) == 0) {
                /*
                 * data field는 length 가 정해져 있지 않으므로 malloc을 해서 copy 해야함.
                 */
                if(i == 2) {   
                    field_buff[i].val.buffer = (char *)malloc(strlen(pdelimiter) + 1) ;
                }

                strcpy(field_buff[i].val.buffer, trim(pdelimiter)) ;
                break ;
            }
        }
    }

    rreq.message_id = NULL ;
    rreq.data = NULL ;

    rreq.vendor_id = dtr_vendor_id ;

    if(strlen(dtr_message_id) != 0)
        rreq.message_id = dtr_message_id ;

    rreq.data = field_buff[2].val.buffer ;

    make_message_id(message_id) ;
    make_ocpp_data_transfer_req_message(user_data_buffer.resp_buf, message_id, &rreq) ;

    conf_act.func = do_data_transfer_conf ;
    strcpy(conf_act.message_id, message_id) ;

    return 0 ;
}

int do_data_transfer_conf(ocpp_callresult_message *resp) {
    printf("do data transfer conf : %s\n", resp->payload) ;
    return 0 ;
}

int do_data_transfer_error(ocpp_callerror_message *msg) {
    return 0 ;    
}
