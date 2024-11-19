#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_remote_stop_transaction_req_message() {
    remote_stop_trans_req.transaction_id.key = remote_stop_transaction_req_field_name[remote_stop_transaction_req_transaction_id] ;
}

void init_remote_stop_transaction_conf_message() {
    remote_stop_trans_conf.status.key = remote_stop_transaction_conf_field_name[remote_stop_transaction_conf_status] ;
    remote_stop_trans_conf.status.val.str_val = rstc_status ;
}

int make_ocpp_remote_stop_transaction_req_message(char *buf, char *message_id, int transaction_id) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[REMOTE_STOP_TRANSACTION_INDEX].action ;

    remote_stop_trans_req.transaction_id.key = remote_stop_transaction_req_field_name[remote_stop_transaction_req_transaction_id] ;
    remote_stop_trans_req.transaction_id.val.int_val = transaction_id ;

    object = json_object_new_object() ;
    json_object_object_add(object, remote_stop_trans_req.transaction_id.key, json_object_new_int(remote_stop_trans_req.transaction_id.val.int_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_remote_stop_transaction_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    remote_stop_trans_conf.status.key = remote_stop_transaction_conf_field_name[remote_stop_transaction_conf_status] ;
    remote_stop_trans_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, remote_stop_trans_conf.status.key, json_object_new_string(remote_stop_trans_conf.status.val.str_val)) ;

    printf("resdult json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_remote_stop_transaction_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, remote_stop_trans_req.transaction_id.key) ;
    remote_stop_trans_req.transaction_id.val.int_val = json_object_get_int(value) ;

    json_object_put(value) ;

    return 0 ;
}

int parse_ocpp_remote_stop_transaction_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, remote_stop_trans_conf.status.key) ;
    strcpy(remote_stop_trans_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_remote_stop_transaction(ocpp_call_message *req, char *resp) {
    init_remote_stop_transaction_req_message() ;
    parse_ocpp_remote_stop_transaction_req_message(req->payload) ;

    make_ocpp_remote_stop_transaction_conf_message(resp, req->message_id, remote_start_stop_status_values[remote_start_stop_status_accepted]) ;
    return 0 ;
}
