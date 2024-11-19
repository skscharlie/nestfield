#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_cancel_reservation_req_message() {
    cancel_res_req.reservation_id.key = cancel_reservation_req_field_names[cancel_reservation_req_reservation_id] ;
    // value 는 field type이 integer이므로 initialize할 필요가 없슴.
}

void init_cancel_reservation_conf_message() {
    cancel_res_conf.status.key = cancel_reservation_conf_field_names[cancel_reservation_conf_status] ;
    cancel_res_conf.status.val.str_val = crc_status ;
}

int make_ocpp_cancel_reservation_req_message(char *buf, char *message_id, int reservation_id) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[CANCEL_RESERVATION_INDEX].action ;

    cancel_res_req.reservation_id.key = cancel_reservation_req_field_names[cancel_reservation_req_reservation_id] ;
    cancel_res_req.reservation_id.val.int_val = reservation_id ;

    object = json_object_new_object() ;
    json_object_object_add(object, cancel_res_req.reservation_id.key, json_object_new_int(cancel_res_req.reservation_id.val.int_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;
    json_object_put(object) ;

    return 0 ;
}

int make_ocpp_cancel_reservation_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    cancel_res_conf.status.key = cancel_reservation_conf_field_names[cancel_reservation_conf_status] ;
    cancel_res_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, cancel_res_conf.status.key, json_object_new_string(cancel_res_conf.status.val.str_val)) ;

    printf("resunt json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;
    json_object_put(object) ;

    return 0 ;
}

int parse_ocpp_cancel_reservation_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, cancel_res_req.reservation_id.key) ;
    cancel_res_req.reservation_id.val.int_val = json_object_get_int(value) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_cancel_reservation_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, cancel_res_conf.status.key) ;
    strcpy(cancel_res_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;

    return 0 ;
}

int do_cancel_reservation(ocpp_call_message *msg, char *resp) {
    init_cancel_reservation_req_message() ;
    parse_ocpp_cancel_reservation_req_message(msg->payload) ;

    make_ocpp_cancel_reservation_conf_message(resp, msg->message_id, cancel_reservation_status_values[cancel_reservation_status_accepted]) ;
    return 0 ;
}
