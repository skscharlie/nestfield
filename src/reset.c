#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_reset_req_message() {
    rset_req.type.key = reset_req_field_name[reset_req_type] ;
    rset_req.type.val.str_val = rr_type ;
}

void init_reset_conf_message() {
    rset_conf.status.key = reset_conf_field_name[reset_conf_status] ;
    rset_conf.status.val.str_val = rc_status ;
}

int make_ocpp_reset_req_message(char *buf, char *message_id, char *type) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[RESET_INDEX].action ;

    rset_req.type.key = reset_req_field_name[reset_req_type] ;
    rset_req.type.val.str_val = type ;

    object = json_object_new_object() ;
    json_object_object_add(object, rset_req.type.key, json_object_new_string(rset_req.type.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_reset_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    rset_conf.status.key = reset_conf_field_name[reset_conf_status] ;
    rset_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, rset_conf.status.key, json_object_new_string(rset_conf.status.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_reset_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, rset_req.type.key) ;
    strcpy(rset_req.type.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_reset_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, rset_conf.status.key) ;
    strcpy(rset_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_reset(ocpp_call_message *req, char *resp) {
    init_reset_req_message() ;
    parse_ocpp_reset_req_message(req->payload) ;

    make_ocpp_reset_conf_message(resp, req->message_id, reset_status_values[reset_status_accepted]) ;
    return 0 ;
}
