#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_trigger_message_req_message() {
    trigger_msg_req.requested_message.key = trigger_message_req_field_names[trigger_message_req_requested_message] ;
    trigger_msg_req.requested_message.val.str_val = tmr_requested_message ;

    trigger_msg_req.connector_id.key = trigger_message_req_field_names[trigger_message_req_connector_id] ;
    // value가 integer이므로 initialize할 필요가 없슴 
}

void init_trigger_message_conf_message() {
    trigger_msg_conf.status.key = trigger_message_conf_field_name[trigger_message_conf_status] ;
    trigger_msg_conf.status.val.str_val = tmc_status ;
}

int make_ocpp_trigger_message_req_message(char *buf, char *message_id, raw_trigger_message_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[TRIGGER_MESSAGE_INDEX].action ;

    trigger_msg_req.requested_message.key = trigger_message_req_field_names[trigger_message_req_requested_message] ;
    trigger_msg_req.requested_message.val.str_val = rreq->requested_message ;

    trigger_msg_req.connector_id.key = trigger_message_req_field_names[trigger_message_req_connector_id] ;
    trigger_msg_req.connector_id.val.int_val = rreq->connector_id ;

    object = json_object_new_object() ;
    json_object_object_add(object, trigger_msg_req.requested_message.key, json_object_new_string(trigger_msg_req.requested_message.val.str_val)) ;
    json_object_object_add(object, trigger_msg_req.connector_id.key, json_object_new_int(trigger_msg_req.connector_id.val.int_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;

    return 0 ;
}

int make_ocpp_trigger_message_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    trigger_msg_conf.status.key = trigger_message_conf_field_name[trigger_message_conf_status] ;
    trigger_msg_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, trigger_msg_conf.status.key, json_object_new_string(trigger_msg_conf.status.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_trigger_message_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, trigger_msg_req.requested_message.key) ;
    strcpy(trigger_msg_req.requested_message.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, trigger_msg_req.connector_id.key) ;
    trigger_msg_req.connector_id.val.int_val = json_object_get_int(value) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_trigger_message_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, trigger_msg_conf.status.key) ;
    strcpy(trigger_msg_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_trigger_message(ocpp_call_message *req, char *resp) {
    init_trigger_message_req_message() ;
    parse_ocpp_trigger_message_req_message(req->payload) ;

    make_ocpp_trigger_message_conf_message(resp, req->message_id, trigger_message_status_values[trigger_message_status_accepted]) ;
    return 0 ;
}
