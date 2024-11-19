#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_heartbeat_req_message() {}

void init_heartbeat_conf_message() {
    hbeat_conf.current_time.key = heartbeat_conf_field_name[heartbeat_conf_current_time] ;
    hbeat_conf.current_time.val.str_val = hc_current_time ;
}

int make_ocpp_heartbeat_req_message(char *buf, char *message_id) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[HEARTBEAT_INDEX].action ;

    object = json_object_new_object() ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_heartbeat_conf_message(char *buf, char *message_id, char *current_time) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    hbeat_conf.current_time.key = heartbeat_conf_field_name[heartbeat_conf_current_time] ;
    hbeat_conf.current_time.val.str_val = current_time ;

    object = json_object_new_object() ;
    json_object_object_add(object, hbeat_conf.current_time.key, json_object_new_string(hbeat_conf.current_time.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

/*
 * req message에는 field가 없으므로 아무것도 하지 않고 return 함.
 */
int parse_ocpp_heartbeat_req_message(char *data) {
    return 0 ;
}

int parse_ocpp_heartbeat_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, hbeat_conf.current_time.key) ;
    strcpy(hbeat_conf.current_time.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_heartbeat_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;

    make_ocpp_heartbeat_req_message(user_data_buffer.resp_buf, message_id) ;
    strcpy(conf_act.message_id, message_id) ;
    conf_act.func = do_heartbeat_conf ;
    return 0 ;
}

int do_heartbeat_conf(ocpp_callresult_message *msg) {
    return 0 ;
}

int do_heartbeat_error(ocpp_callerror_message *msg) {
    return 0 ;    
}
