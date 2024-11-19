#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_reserve_now_req_message() {
    reserve_n_req.connector_id.key = reserve_now_req_field_names[reserve_now_req_connector_id] ;
    
    reserve_n_req.expiry_date.key = reserve_now_req_field_names[reserve_now_req_expiry_date] ;
    reserve_n_req.expiry_date.val.str_val = rnr_expiry_date ;

    reserve_n_req.id_tag.key = reserve_now_req_field_names[reserve_now_req_id_tag] ;
    reserve_n_req.id_tag.val.str_val = rnr_id_tag ;

    reserve_n_req.parent_id_tag.key = reserve_now_req_field_names[reserve_now_req_parent_id_tag] ;
    reserve_n_req.parent_id_tag.val.str_val = rnr_parent_id_tag ;

    reserve_n_req.reservation_id.key = reserve_now_req_field_names[reserve_now_req_reseration_id] ;
}

void init_reserve_now_conf_message() {
    reserve_n_conf.status.key = reserve_now_conf_field_name[reserve_now_conf_status] ;
    reserve_n_conf.status.val.str_val = nrc_status ;
}

int make_ocpp_reserve_now_req_message(char *buf, char *message_id, raw_reserve_now_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[RESERVE_NOW_INDEX].action ;

    reserve_n_req.connector_id.key = reserve_now_req_field_names[reserve_now_req_connector_id] ;
    reserve_n_req.connector_id.val.int_val = rreq->connector_id ;

    reserve_n_req.expiry_date.key = reserve_now_req_field_names[reserve_now_req_expiry_date] ;
    reserve_n_req.expiry_date.val.str_val = rreq->expiry_date ;

    reserve_n_req.id_tag.key = reserve_now_req_field_names[reserve_now_req_id_tag] ;
    reserve_n_req.id_tag.val.str_val = rreq->id_tag ;

    reserve_n_req.parent_id_tag.key = reserve_now_req_field_names[reserve_now_req_parent_id_tag] ;
    reserve_n_req.parent_id_tag.val.str_val = rreq->parent_id_tag ;

    reserve_n_req.reservation_id.key = reserve_now_req_field_names[reserve_now_req_reseration_id] ;
    reserve_n_req.reservation_id.val.int_val = rreq->reservation_id ;

    object = json_object_new_object() ;
    json_object_object_add(object, reserve_n_req.connector_id.key, json_object_new_int(reserve_n_req.connector_id.val.int_val)) ;
    json_object_object_add(object, reserve_n_req.expiry_date.key, json_object_new_string(reserve_n_req.expiry_date.val.str_val)) ;
    json_object_object_add(object, reserve_n_req.id_tag.key, json_object_new_string(reserve_n_req.id_tag.val.str_val)) ;

    if(reserve_n_req.parent_id_tag.val.str_val != NULL && strlen(reserve_n_req.parent_id_tag.val.str_val) != 0)
        json_object_object_add(object, reserve_n_req.parent_id_tag.key, json_object_new_string(reserve_n_req.parent_id_tag.val.str_val)) ;
    
    json_object_object_add(object, reserve_n_req.reservation_id.key, json_object_new_int(reserve_n_req.reservation_id.val.int_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d,, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_reserve_now_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    reserve_n_conf.status.key = reserve_now_conf_field_name[reserve_now_conf_status] ;
    reserve_n_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, reserve_n_conf.status.key, json_object_new_string(reserve_n_conf.status.val.str_val)) ;  

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;  
}

int parse_ocpp_reserve_now_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, reserve_n_req.connector_id.key) ;
    reserve_n_req.connector_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, reserve_n_req.expiry_date.key) ;
    strcpy(reserve_n_req.expiry_date.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, reserve_n_req.id_tag.key) ;
    strcpy(reserve_n_req.id_tag.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, reserve_n_req.parent_id_tag.key) ;
    if(value != NULL)
        strcpy(reserve_n_req.parent_id_tag.val.str_val, json_object_to_json_string(value)) ;

    value = json_object_object_get(object, reserve_n_req.reservation_id.key) ;
    reserve_n_req.reservation_id.val.int_val = json_object_get_int(value) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_reserve_now_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, reserve_n_conf.status.key) ;
    strcpy(reserve_n_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_reserve_now(ocpp_call_message *req, char *resp) {
    init_reserve_now_req_message() ;
    parse_ocpp_reserve_now_req_message(req->payload) ;

    make_ocpp_reserve_now_conf_message(resp, req->message_id, reservation_status_values[reservation_status_accepted]) ;
    return 0 ;
}
