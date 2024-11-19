#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_start_transaction_req_message() {
    start_trans_req.connector_id.key = start_transaction_req_field_names[start_transaction_req_connector_id] ;
    //value type이 integer 이므로 initialize할 필요가 없슴.

    start_trans_req.id_tag.key = start_transaction_req_field_names[start_transaction_req_id_tag] ;
    start_trans_req.id_tag.val.str_val = str_id_tag ;

    start_trans_req.meter_start.key = start_transaction_req_field_names[start_transaction_req_meter_start] ;
    start_trans_req.reservation_id.key = start_transaction_req_field_names[start_transaction_req_reservation_id] ;

    start_trans_req.timestamp.key = start_transaction_req_field_names[start_transaction_req_timestamp] ;
    start_trans_req.timestamp.val.str_val = str_timestamp ;
}

void init_start_transaction_conf_message() {
    start_trans_conf.id_tag_info.key = start_transaction_conf_field_names[start_transaction_conf_id_tag_info] ;
    start_trans_conf.id_tag_info.val.iti_val = &id_tag_inf ;

    start_trans_conf.id_tag_info.val.iti_val->expiry_date.key = id_tag_info_field_names[id_tag_info_expiry_date] ;
    start_trans_conf.id_tag_info.val.iti_val->expiry_date.val.str_val = iti_expiry_date ;

    start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.key = id_tag_info_field_names[id_tag_info_parient_id_tag] ;
    start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val = iti_parent_id_tag ;

    start_trans_conf.id_tag_info.val.iti_val->status.key = id_tag_info_field_names[id_tag_info_status] ;
    start_trans_conf.id_tag_info.val.iti_val->status.val.str_val = iti_status ;

    start_trans_conf.transaction_id.key = start_transaction_conf_field_names[start_transaction_conf_transaction_id] ;
}

int make_ocpp_start_transaction_req_message(char *buf, char *message_id, raw_start_transaction_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[START_TRANSACTION_INDEX].action ;

    start_trans_req.connector_id.key = start_transaction_req_field_names[start_transaction_req_connector_id] ;
    start_trans_req.connector_id.val.int_val = rreq->connector_id ;

    start_trans_req.id_tag.key = start_transaction_req_field_names[start_transaction_req_id_tag] ;
    start_trans_req.id_tag.val.str_val = rreq->id_tag ;

    start_trans_req.meter_start.key = start_transaction_req_field_names[start_transaction_req_meter_start] ;
    start_trans_req.meter_start.val.int_val = rreq->meter_start ;

    start_trans_req.reservation_id.key = start_transaction_req_field_names[start_transaction_req_reservation_id] ;
    start_trans_req.reservation_id.val.int_val = rreq->reservation_id ;

    start_trans_req.timestamp.key = start_transaction_req_field_names[start_transaction_req_timestamp] ;
    start_trans_req.timestamp.val.str_val = rreq->timestamp ;

    object = json_object_new_object() ;
    json_object_object_add(object, start_trans_req.connector_id.key, json_object_new_int(start_trans_req.connector_id.val.int_val)) ;
    json_object_object_add(object, start_trans_req.id_tag.key, json_object_new_string(start_trans_req.id_tag.val.str_val)) ;
    json_object_object_add(object, start_trans_req.meter_start.key, json_object_new_int(start_trans_req.meter_start.val.int_val)) ;
    json_object_object_add(object, start_trans_req.reservation_id.key, json_object_new_int(start_trans_req.reservation_id.val.int_val)) ;
    json_object_object_add(object, start_trans_req.timestamp.key, json_object_new_string(start_trans_req.timestamp.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_start_transaction_conf_message(char *buf, char *message_id, raw_start_transaction_conf *rconf) {
    ocpp_callresult_message message ;
    json_object *object, *iti ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    start_trans_conf.id_tag_info.key = start_transaction_conf_field_names[start_transaction_conf_id_tag_info] ;
    start_trans_conf.id_tag_info.val.iti_val = &id_tag_inf ;

    start_trans_conf.id_tag_info.val.iti_val->expiry_date.key = id_tag_info_field_names[id_tag_info_expiry_date] ;
    start_trans_conf.id_tag_info.val.iti_val->expiry_date.val.str_val = rconf->id_tag_info->expiry_date ;

    start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.key = id_tag_info_field_names[id_tag_info_parient_id_tag] ;
    start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val = rconf->id_tag_info->parent_id_tag ;

    start_trans_conf.id_tag_info.val.iti_val->status.key = id_tag_info_field_names[id_tag_info_status] ;
    start_trans_conf.id_tag_info.val.iti_val->status.val.str_val = rconf->id_tag_info->status ;

    start_trans_conf.transaction_id.key = start_transaction_conf_field_names[start_transaction_conf_transaction_id] ;
    start_trans_conf.transaction_id.val.int_val = rconf->transaction_id ;

    object = json_object_new_object() ;
    iti = json_object_new_object() ;
    json_object_object_add(iti, start_trans_conf.id_tag_info.val.iti_val->expiry_date.key, json_object_new_string(start_trans_conf.id_tag_info.val.iti_val->expiry_date.val.str_val)) ;
    json_object_object_add(iti, start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.key, json_object_new_string(start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val)) ;
    json_object_object_add(iti, start_trans_conf.id_tag_info.val.iti_val->status.key, json_object_new_string(start_trans_conf.id_tag_info.val.iti_val->status.val.str_val)) ;

    json_object_object_add(object, start_trans_conf.id_tag_info.key, iti) ;
    json_object_object_add(object, start_trans_conf.transaction_id.key, json_object_new_int(start_trans_conf.transaction_id.val.int_val)) ;

    printf("%s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\",  %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_start_transaction_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, start_trans_req.connector_id.key) ;
    start_trans_req.connector_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, start_trans_req.id_tag.key) ;
    strcpy(start_trans_req.id_tag.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, start_trans_req.meter_start.key) ;
    start_trans_req.meter_start.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, start_trans_req.reservation_id.key) ;
    start_trans_req.reservation_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, start_trans_req.timestamp.key) ;
    strcpy(start_trans_req.timestamp.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_start_transaction_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value, *iti ;

    iti = json_object_object_get(object, start_trans_conf.id_tag_info.key) ;

    value = json_object_object_get(iti, start_trans_conf.id_tag_info.val.iti_val->expiry_date.key) ;
    strcpy(start_trans_conf.id_tag_info.val.iti_val->expiry_date.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(iti, start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.key) ;
    strcpy(start_trans_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(iti, start_trans_conf.id_tag_info.val.iti_val->status.key) ;
    strcpy(start_trans_conf.id_tag_info.val.iti_val->status.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, start_trans_conf.transaction_id.key) ;
    start_trans_conf.transaction_id.val.int_val = json_object_get_int(value) ;

    json_object_put(object) ;
    return 0 ;
}

int do_start_transaction_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_start_transaction_req rreq ;
    char id_tag_buf[STRING_20_TYPE_LENGTH + 1], timestamp_buf[DATE_TIME_LENGTH+ 1] ;

    make_message_id(message_id) ;

    rreq.connector_id = 1 ;
    rreq.id_tag = id_tag_buf ;
    rreq.meter_start = 10 ;
    rreq.reservation_id = 12 ;
    rreq.timestamp = timestamp_buf ;

    strcpy(id_tag_buf, "charlie") ;
    get_future_date(timestamp_buf, 0) ;

    make_ocpp_start_transaction_req_message(user_data_buffer.resp_buf, message_id, &rreq) ;
    strcpy(conf_act.message_id, message_id) ;
    conf_act.func = do_start_transaction_conf ;

    return 0 ;
}

int do_start_transaction_conf(ocpp_callresult_message *resp) {
    printf("do start transaction conf : %s\n", resp->payload) ;
    return 0 ;
}

int do_start_transaction_error(ocpp_callerror_message *msg) {
    return 0 ;    
}
