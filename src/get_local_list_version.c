#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_get_local_list_version_req_message() {}

void init_get_local_list_version_conf_message() {
    get_ll_version_conf.list_version.key = get_local_list_version_conf_field_name[get_local_list_version_conf_list_version] ;
}

int make_ocpp_get_local_list_version_req_message(char *buf, char *message_id) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[GET_LOCAL_LIST_VERSION_INDEX].action ;

    object = json_object_new_object() ;
    
    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_get_local_list_version_conf_message(char *buf, char *message_id, int list_version) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    get_ll_version_conf.list_version.key = get_local_list_version_conf_field_name[get_local_list_version_conf_list_version] ;
    get_ll_version_conf.list_version.val.int_val = list_version ;

    object = json_object_new_object() ;
    json_object_object_add(object, get_ll_version_conf.list_version.key, json_object_new_int(get_ll_version_conf.list_version.val.int_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_get_local_list_version_req_message(char *data) {
    return 0 ;
}

int parse_ocpp_get_local_list_version_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, get_ll_version_conf.list_version.key) ;
    get_ll_version_conf.list_version.val.int_val = json_object_get_int(value) ;

    json_object_put(object) ;
    return 0 ;
}

int do_get_local_list_version(ocpp_call_message *req, char *resp) {
    init_get_local_list_version_req_message() ;
    parse_ocpp_get_local_list_version_req_message(req->payload) ;

    make_ocpp_get_local_list_version_conf_message(resp, req->message_id, 1) ;
    return 0 ;
}
