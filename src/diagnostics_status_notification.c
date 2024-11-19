#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_diagnostics_status_notification_req_message() {
    diagnostics_stat_noti_req.status.key = diagnostics_status_notification_req_field_name[diagnostics_status_notification_req_status] ;
    diagnostics_stat_noti_req.status.val.str_val = dsnr_status ;
}

void init_diagnostics_status_notification_conf_message() {

}

int make_ocpp_diagnostics_status_notification_req_message(char *buf, char *message_id, char *status) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[DIAGNOSTICS_STATUS_NOTIFICATION_INDEX].action ;

    diagnostics_stat_noti_req.status.key = diagnostics_status_notification_req_field_name[diagnostics_status_notification_req_status] ;
    diagnostics_stat_noti_req.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, diagnostics_stat_noti_req.status.key, json_object_new_string(diagnostics_stat_noti_req.status.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_diagnostics_status_notification_conf_message(char *buf, char *message_id) {
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

int parse_ocpp_diagnostics_status_notification_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, diagnostics_stat_noti_req.status.key) ;
    strcpy(diagnostics_stat_noti_req.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_diagnostics_status_notification_conf_message(char *data) {
    return 0 ;
}

/*
 * ppcommand[0] : DiagnosticsStatusNotification, ppcommand[1] : status
 */
int do_diagnostics_status_notification_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;
    strcpy(dsnr_status, ppcommand[1]) ;
    make_ocpp_diagnostics_status_notification_req_message(user_data_buffer.resp_buf, message_id, dsnr_status) ;
    strcpy(conf_act.message_id, message_id) ;
    conf_act.func = do_diagnostics_status_notification_conf ;
 
    return 0 ;
}

int do_diagnostics_status_notification_conf(ocpp_callresult_message *resp) {
    printf("do diagnostics status notification : %s\n", resp->payload) ;
    return 0 ;
}

int do_diagnostics_status_notification_error(ocpp_callerror_message *msg) {
    return 0 ;    
}
