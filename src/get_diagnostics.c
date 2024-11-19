#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_get_diagnostics_req_message() {
    get_diag_req.location.key = get_diagnostics_req_field_names[get_diagnostics_req_location] ;
    get_diag_req.location.val.str_val = gdr_location ;

    get_diag_req.retries.key = get_diagnostics_req_field_names[get_diagnostics_req_retries] ;
    get_diag_req.retry_interval.key = get_diagnostics_req_field_names[get_diagnostics_req_retry_interval] ;

    get_diag_req.start_time.key = get_diagnostics_req_field_names[get_diagnostics_req_start_time] ;
    get_diag_req.start_time.val.str_val = gdr_start_time ;

    get_diag_req.stop_time.key = get_diagnostics_req_field_names[get_diagnostics_req_stop_time] ;
    get_diag_req.stop_time.val.str_val = gdr_stop_time ;    
}

void init_get_diagnostics_conf_message() {
    get_diag_conf.file_name.key = get_diagnostics_conf_field_name[get_diagnostics_conf_file_name] ;
    get_diag_conf.file_name.val.str_val = gdc_file_name ;
}

int make_ocpp_get_diagnostics_req_message(char *buf, char *message_id, raw_get_diagnostics_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[GET_DIAGNOSTICS_INDEX].action ;

    get_diag_req.location.key = get_diagnostics_req_field_names[get_diagnostics_req_location] ;
    get_diag_req.location.val.str_val = rreq->location ;

    get_diag_req.retries.key = get_diagnostics_req_field_names[get_diagnostics_req_retries] ;
    get_diag_req.retries.val.int_val = rreq->retries ;

    get_diag_req.retry_interval.key = get_diagnostics_req_field_names[get_diagnostics_req_retry_interval] ;
    get_diag_req.retry_interval.val.int_val = rreq->retry_interval ;

    get_diag_req.start_time.key = get_diagnostics_req_field_names[get_diagnostics_req_start_time] ;
    get_diag_req.start_time.val.str_val = rreq->start_time ;

    get_diag_req.stop_time.key = get_diagnostics_req_field_names[get_diagnostics_req_stop_time] ;
    get_diag_req.stop_time.val.str_val = rreq->stop_time ;

    object = json_object_new_object() ;
    json_object_object_add(object, get_diag_req.location.key, json_object_new_string(get_diag_req.location.val.str_val)) ;

    if(get_diag_req.retries.val.int_val != -1)
        json_object_object_add(object, get_diag_req.retries.key, json_object_new_int(get_diag_req.retries.val.int_val)) ;

    if(get_diag_req.retry_interval.val.int_val != -1)
        json_object_object_add(object, get_diag_req.retry_interval.key, json_object_new_int(get_diag_req.retry_interval.val.int_val)) ;

    if(get_diag_req.start_time.val.str_val != NULL)
        json_object_object_add(object, get_diag_req.start_time.key, json_object_new_string(get_diag_req.start_time.val.str_val)) ;

    if(get_diag_req.stop_time.val.str_val != NULL)
        json_object_object_add(object, get_diag_req.stop_time.key, json_object_new_string(get_diag_req.stop_time.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_get_diagnostics_conf_message(char *buf, char *message_id, char *file_name) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    get_diag_conf.file_name.key = get_diagnostics_conf_field_name[get_diagnostics_conf_file_name] ;
    get_diag_conf.file_name.val.str_val = file_name ;

    object = json_object_new_object() ;
    
    if(file_name != NULL)
        json_object_object_add(object, get_diag_conf.file_name.key, json_object_new_string(get_diag_conf.file_name.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_get_diagnostics_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, get_diag_req.location.key) ;
    strcpy(get_diag_req.location.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, get_diag_req.retries.key) ;
    if(value != NULL)
        get_diag_req.retries.val.int_val = json_object_get_int(value) ;
    else
        get_diag_req.retries.val.int_val = -1 ;

    value = json_object_object_get(object, get_diag_req.retry_interval.key) ;
    if(value != NULL)
        get_diag_req.retry_interval.val.int_val = json_object_get_int(value) ;
    else
        get_diag_req.retry_interval.val.int_val= -1 ;

    value = json_object_object_get(object, get_diag_req.start_time.key) ;
    if(value != NULL)
        strcpy(get_diag_req.start_time.val.str_val, json_object_get_string(value)) ;
    else
        get_diag_req.start_time.val.str_val = NULL ;

    value = json_object_object_get(object, get_diag_req.stop_time.key) ;
    if(value != NULL)
        strcpy(get_diag_req.stop_time.val.str_val, json_object_get_string(value)) ;
    else
        get_diag_req.stop_time.val.str_val = NULL ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_get_diagnostics_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, get_diag_conf.file_name.key) ;
    if(value != NULL)
        strcpy(get_diag_conf.file_name.val.str_val, json_object_get_string(value)) ;
    else
        get_diag_conf.file_name.val.str_val = NULL ;

    json_object_put(object) ;
    return 0 ;
}

int do_get_diagnostics(ocpp_call_message *req, char *resp) {
    char file_name_buf[STRING_50_TYPE_LENGTH] ;

    init_get_diagnostics_req_message() ;
    parse_ocpp_get_diagnostics_req_message(req->payload) ;

    strcpy(file_name_buf, "/Users/charlie/C/nestfield/src") ;
    make_ocpp_get_diagnostics_conf_message(resp, req->message_id, file_name_buf) ;
    return 0 ;
}
