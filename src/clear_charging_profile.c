#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_clear_charging_profile_req_message() {
    clear_chg_prof_req.id.key = clear_charging_profile_req_field_names[clear_charging_profile_req_id] ;
    // field type이 integer 이므로 value를 initialize 할 필요가 없슴

    clear_chg_prof_req.connector_id.key = clear_charging_profile_req_field_names[clear_charging_profile_req_connector_id] ;
    // field type이 integer 이므로 value를 initialize 할 필요가 없슴

    clear_chg_prof_req.charging_profile_purpose.key = clear_charging_profile_req_field_names[clear_charging_profile_req_charging_profile_purpose] ;
    clear_chg_prof_req.charging_profile_purpose.val.str_val = ccpr_charging_profile_purpose ;

    clear_chg_prof_req.stack_level.key = clear_charging_profile_req_field_names[clear_charging_profile_req_stack_level] ;
    // field type이 integer 이므로 value를 initialize 할 필요가 없슴
}

void init_clear_charging_profile_conf_message() {
    clear_chg_prof_conf.status.key = clear_charging_profile_conf_field_names[clear_charging_profile_conf_status] ;
    clear_chg_prof_conf.status.val.str_val = ccpc_status ;
}

int make_ocpp_clear_charging_profile_req_message(char *buf, char *message_id, raw_clear_charging_profile_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[CLEAR_CHARGING_PROFILE_INDEX].action ;

    clear_chg_prof_req.id.key = clear_charging_profile_req_field_names[clear_charging_profile_req_id] ;
    clear_chg_prof_req.id.val.int_val = rreq->id ;

    clear_chg_prof_req.connector_id.key = clear_charging_profile_req_field_names[clear_charging_profile_req_connector_id] ;
    clear_chg_prof_req.connector_id.val.int_val = rreq->connector_id ;

    clear_chg_prof_req.charging_profile_purpose.key = clear_charging_profile_req_field_names[clear_charging_profile_req_charging_profile_purpose] ;
    clear_chg_prof_req.charging_profile_purpose.val.str_val = rreq->charging_profile_purpose ;

    clear_chg_prof_req.stack_level.key = clear_charging_profile_req_field_names[clear_charging_profile_req_stack_level] ;
    clear_chg_prof_req.stack_level.val.int_val = rreq->stack_level ;

    object = json_object_new_object() ;
    if(clear_chg_prof_req.id.val.int_val != -1)
        json_object_object_add(object, clear_chg_prof_req.id.key, json_object_new_int(clear_chg_prof_req.id.val.int_val)) ;
    
    if(clear_chg_prof_req.connector_id.val.int_val != -1)
        json_object_object_add(object, clear_chg_prof_req.connector_id.key, json_object_new_int(clear_chg_prof_req.connector_id.val.int_val)) ;

    if(clear_chg_prof_req.charging_profile_purpose.val.str_val != NULL)
        json_object_object_add(object, clear_chg_prof_req.charging_profile_purpose.key, json_object_new_string(clear_chg_prof_req.charging_profile_purpose.val.str_val)) ;

    if(clear_chg_prof_req.stack_level.val.int_val != -1)    
        json_object_object_add(object, clear_chg_prof_req.stack_level.key, json_object_new_int(clear_chg_prof_req.stack_level.val.int_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_clear_charging_profile_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    clear_chg_prof_conf.status.key = clear_charging_profile_conf_field_names[clear_charging_profile_conf_status] ;
    clear_chg_prof_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, clear_chg_prof_conf.status.key, json_object_new_string(clear_chg_prof_conf.status.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_clear_charging_profile_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, clear_chg_prof_req.id.key) ;
    if(value != NULL)
        clear_chg_prof_req.id.val.int_val = json_object_get_int(value) ;
    else
        clear_chg_prof_req.id.val.int_val = -1 ;

    value = json_object_object_get(object, clear_chg_prof_req.connector_id.key) ;
    if(value != NULL)
        clear_chg_prof_req.connector_id.val.int_val = json_object_get_int(value) ;
    else
        clear_chg_prof_req.connector_id.val.int_val = -1 ;

    value = json_object_object_get(object, clear_chg_prof_req.charging_profile_purpose.key) ;
    if(value != NULL)
        strcpy(clear_chg_prof_req.charging_profile_purpose.val.str_val, json_object_get_string(value)) ;
    else
        clear_chg_prof_req.charging_profile_purpose.val.str_val = NULL ;

    value = json_object_object_get(object, clear_chg_prof_req.stack_level.key) ;
    if(value != NULL)
        clear_chg_prof_req.stack_level.val.int_val = json_object_get_int(value) ;
    else
        clear_chg_prof_req.stack_level.val.int_val = -1 ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_clear_charging_profile_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, clear_chg_prof_conf.status.key) ;
    strcpy(clear_chg_prof_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_clear_charging_profile(ocpp_call_message *req, char *resp) {
    init_clear_charging_profile_req_message() ;
    parse_ocpp_clear_charging_profile_req_message(req->payload) ;

    make_ocpp_change_configuration_conf_message(resp, req->message_id, clear_charging_profile_status_values[clear_charging_profile_status_accepted]) ;

    return 0 ;
}
