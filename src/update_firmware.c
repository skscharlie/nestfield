#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_update_firmware_req_message() {
    update_fw_req.location.key = update_firmware_req_field_names[update_firmware_req_location] ;
    update_fw_req.location.val.str_val = ufr_location ;

    update_fw_req.retries.key = update_firmware_req_field_names[update_firmware_req_retries] ;
    // value type이 integer이므로 initialize할 필요가 없다

    update_fw_req.retrieve_date.key = update_firmware_req_field_names[update_firmware_req_retrieve_date] ;
    update_fw_req.retrieve_date.val.str_val = ufr_retrieve_date ;

    update_fw_req.retry_interval.key = update_firmware_req_field_names[update_firmware_req_retry_interval] ;
    // value type이 integer이므로 initialize할 필요가 없다
}

void init_update_firmware_conf_message() {}

int make_ocpp_update_firmware_req_message(char *buf, char *message_id, raw_update_firmware_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[UPDATE_FIRMWARE_INDEX].action ;

    update_fw_req.location.key = update_firmware_req_field_names[update_firmware_req_location] ;
    update_fw_req.location.val.str_val = rreq->location ;

    update_fw_req.retries.key = update_firmware_req_field_names[update_firmware_req_location] ;
    update_fw_req.retries.val.int_val = rreq->retries ;

    update_fw_req.retrieve_date.key = update_firmware_req_field_names[update_firmware_req_retrieve_date] ;
    update_fw_req.retrieve_date.val.str_val = rreq->retrieve_date ;

    update_fw_req.retry_interval.key = update_firmware_req_field_names[update_firmware_req_retry_interval] ;
    update_fw_req.retry_interval.val.int_val = rreq->retry_interval ;

    object = json_object_new_object() ;
    json_object_object_add(object, update_fw_req.location.key, json_object_new_string(update_fw_req.location.val.str_val)) ;
    json_object_object_add(object, update_fw_req.retries.key, json_object_new_int(update_fw_req.retries.val.int_val)) ;
    json_object_object_add(object, update_fw_req.retrieve_date.key, json_object_new_string(update_fw_req.retrieve_date.val.str_val)) ;
    json_object_object_add(object, update_fw_req.retry_interval.key, json_object_new_int(update_fw_req.retry_interval.val.int_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_update_firmware_conf_message(char *buf, char *message_id) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    object = json_object_new_object() ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;

    return 0 ;
}

int parse_ocpp_update_firmware_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, update_fw_req.location.key) ;
    strcpy(update_fw_req.location.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, update_fw_req.retries.key) ;
    update_fw_req.retries.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, update_fw_req.retrieve_date.key) ;
    strcpy(update_fw_req.retrieve_date.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, update_fw_req.retry_interval.key) ;
    update_fw_req.retry_interval.val.int_val = json_object_get_int(value) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_update_firmware_conf_message(char *data) {
    return 0 ;
}

int do_update_firmware(ocpp_call_message *req, char *resp) {
    init_update_firmware_req_message() ;
    parse_ocpp_update_firmware_req_message(req->payload) ;

    make_ocpp_update_firmware_conf_message(resp, req->message_id) ;

    return 0 ;
}