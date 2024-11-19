#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_unlock_connector_req_message() {
    unlock_con_req.connector_id.key = unlock_connector_req_field_name[unlock_connector_req_connector_id] ;
    // value type이 integer이므로 initialize할 필요가 없다
}

void init_unlock_connector_conf_message() {
    unlock_con_conf.status.key = unlock_connector_conf_field_name[unlock_connector_conf_status] ;
    unlock_con_conf.status.val.str_val = ucc_status ;
}

int make_ocpp_unlock_connector_req_message(char *buf, char *message_id, int connector_id) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[UNLOCK_CONNECTOR_INDEX].action ;

    unlock_con_req.connector_id.key = unlock_connector_req_field_name[unlock_connector_req_connector_id] ;
    unlock_con_req.connector_id.val.int_val = connector_id ;

    object = json_object_new_object() ;
    json_object_object_add(object, unlock_con_req.connector_id.key, json_object_new_int(unlock_con_req.connector_id.val.int_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_unlock_connector_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    unlock_con_conf.status.key = unlock_connector_conf_field_name[unlock_connector_conf_status] ;
    unlock_con_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, unlock_con_conf.status.key, json_object_new_string(unlock_con_conf.status.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_unlock_connector_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, unlock_con_req.connector_id.key) ;
    unlock_con_req.connector_id.val.int_val = json_object_get_int(value) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_unlock_connector_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, unlock_con_conf.status.key) ;
    strcpy(unlock_con_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_unlock_connector(ocpp_call_message *req, char *resp) {
    init_unlock_connector_req_message() ;
    parse_ocpp_unlock_connector_req_message(req->payload) ;

    make_ocpp_unlock_connector_conf_message(resp, req->message_id, unlock_status_values[unlock_status_unlocked]) ;
    return 0 ;
}
