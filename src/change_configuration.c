#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_change_configuration_req_message() {
    change_config_req.key.key = change_configuration_req_field_names[change_configuration_req_key] ;
    change_config_req.key.val.str_val = ccr_key ;

    change_config_req.value.key = change_configuration_req_field_names[change_configuration_req_value] ;
    change_config_req.value.val.str_val = ccr_value ;
}

void init_change_configuration_conf_message() {
    change_config_conf.status.key = change_configuration_conf_field_names[change_configuration_conf_status] ;
    change_config_conf.status.val.str_val = ccc_status ;
}

int make_ocpp_change_configuration_req_message(char *buf, char *message_id, raw_change_configuration_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[CHANGE_CONFIGURATION_INDEX].action ;

    change_config_req.key.key = change_configuration_req_field_names[change_configuration_req_key] ;
    change_config_req.key.val.str_val = rreq->key ;

    change_config_req.value.key = change_configuration_req_field_names[change_configuration_req_value] ;
    change_config_req.value.val.str_val = rreq->value ;

    object = json_object_new_object() ;
    json_object_object_add(object, change_config_req.key.key, json_object_new_string(change_config_req.key.val.str_val)) ;
    json_object_object_add(object, change_config_req.value.key, json_object_new_string(change_config_req.value.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;

    return 0 ;
}

int make_ocpp_change_configuration_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    change_config_conf.status.key = change_configuration_conf_field_names[change_configuration_conf_status] ;
    change_config_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, change_config_conf.status.key, json_object_new_string(change_config_conf.status.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_change_configuration_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, change_config_req.key.key) ;
    strcpy(change_config_req.key.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, change_config_req.value.key) ;
    strcpy(change_config_req.value.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_change_configuration_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, change_config_conf.status.key) ;
    strcpy(change_config_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_change_configuration(ocpp_call_message *req, char *resp) {
    init_change_configuration_req_message() ;
    parse_ocpp_change_configuration_req_message(req->payload) ;

    make_ocpp_change_configuration_conf_message(resp, req->message_id, configuration_status_values[configuration_status_accepted]) ;
    return 0 ;
}

