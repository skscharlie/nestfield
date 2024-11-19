#include <stdio.h>
#include <string.h>
#include <json.h>
#include <sqlite3.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_status_notification_req_message() {
    status_noti_req.connector_id.key = status_notification_req_field_names[status_notification_req_connector_id] ;

    status_noti_req.error_code.key = status_notification_req_field_names[status_notification_req_error_code] ;
    status_noti_req.error_code.val.str_val = snr_error_code ;

    status_noti_req.info.key = status_notification_req_field_names[status_notification_req_info] ;
    status_noti_req.info.val.str_val = snr_info ;

    status_noti_req.status.key = status_notification_req_field_names[status_notification_req_status] ;
    status_noti_req.status.val.str_val = snr_status ;

    status_noti_req.timestamp.key = status_notification_req_field_names[status_notification_req_timestamp] ;
    status_noti_req.timestamp.val.str_val = snr_timestamp ;

    status_noti_req.vendor_id.key = status_notification_req_field_names[status_notification_req_vendor_id] ;
    status_noti_req.vendor_id.val.str_val = snr_vendor_id ;

    status_noti_req.vendor_error_code.key = status_notification_req_field_names[status_notification_req_vendor_error_code] ;
    status_noti_req.vendor_error_code.val.str_val = snr_vendor_error_code ;
}

void init_status_notification_conf_message() {}

int make_ocpp_status_notification_req_message(char *buf, char *message_id, raw_status_notification_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[STATUS_NOTIFICATION_INDEX].action ;

    status_noti_req.connector_id.key = status_notification_req_field_names[status_notification_req_connector_id] ;
    status_noti_req.connector_id.val.int_val = rreq->connector_id ;

    status_noti_req.error_code.key = status_notification_req_field_names[status_notification_req_error_code] ;
    status_noti_req.error_code.val.str_val = rreq->error_code ;

    status_noti_req.info.key = status_notification_req_field_names[status_notification_req_info] ;
    status_noti_req.info.val.str_val = rreq->info ;

    status_noti_req.status.key = status_notification_req_field_names[status_notification_req_status] ;
    status_noti_req.status.val.str_val = rreq->status ;

    status_noti_req.timestamp.key = status_notification_req_field_names[status_notification_req_timestamp] ;
    status_noti_req.timestamp.val.str_val = rreq->timestamp ;

    status_noti_req.vendor_id.key = status_notification_req_field_names[status_notification_req_vendor_id] ;
    status_noti_req.vendor_id.val.str_val = rreq->vendor_id ;

    status_noti_req.vendor_error_code.key = status_notification_req_field_names[status_notification_req_vendor_error_code] ;
    status_noti_req.vendor_error_code.val.str_val = rreq->vendor_error_code ;

    object = json_object_new_object() ;
    json_object_object_add(object, status_noti_req.connector_id.key, json_object_new_int(status_noti_req.connector_id.val.int_val)) ;
    json_object_object_add(object, status_noti_req.error_code.key, json_object_new_string(status_noti_req.error_code.val.str_val)) ;

    if(status_noti_req.info.val.str_val != NULL)
        json_object_object_add(object, status_noti_req.info.key, json_object_new_string(status_noti_req.info.val.str_val)) ;

    json_object_object_add(object, status_noti_req.status.key, json_object_new_string(status_noti_req.status.val.str_val)) ;    
    
    if(status_noti_req.timestamp.val.str_val != NULL)
        json_object_object_add(object, status_noti_req.timestamp.key, json_object_new_string(status_noti_req.timestamp.val.str_val)) ;

    if(status_noti_req.vendor_id.val.str_val != NULL)    
        json_object_object_add(object, status_noti_req.vendor_id.key, json_object_new_string(status_noti_req.vendor_id.val.str_val)) ;    

    if(status_noti_req.vendor_error_code.val.str_val != NULL)
        json_object_object_add(object, status_noti_req.vendor_error_code.key, json_object_new_string(status_noti_req.vendor_id.val.str_val)) ;

    printf("%s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_status_notification_conf_message(char *buf, char *message_id) {
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

int parse_ocpp_status_notification_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, status_noti_req.connector_id.key) ;
    status_noti_req.connector_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, status_noti_req.error_code.key) ;
    strcpy(status_noti_req.error_code.val.str_val, json_object_get_string(value)) ;
 
    value = json_object_object_get(object, status_noti_req.info.key) ;
    if(value != NULL)
        strcpy(status_noti_req.info.val.str_val, json_object_get_string(value)) ;
 
    value = json_object_object_get(object, status_noti_req.status.key) ;
    strcpy(status_noti_req.status.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, status_noti_req.timestamp.key) ;
    if(value != NULL)
        strcpy(status_noti_req.timestamp.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, status_noti_req.vendor_id.key) ;
    if(value != NULL)
        strcpy(status_noti_req.vendor_id.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, status_noti_req.vendor_error_code.key) ;
    if(value != NULL)
        strcpy(status_noti_req.vendor_error_code.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_status_notification_conf_message(char *data) {
    return 0 ;
}

int do_status_notification_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_status_notification_req rreq ;
    char error_code_buf[STRING_25_TYPE_LENGTH + 1], info_buf[STRING_50_TYPE_LENGTH + 1], status_buf[STRING_20_TYPE_LENGTH + 1] ;
    char timestamp_buf[DATE_TIME_LENGTH + 1], vendor_id_buf[STRING_255_TYPE_LENGTH + 1], vendor_error_code_buf[STRING_50_TYPE_LENGTH + 1] ;
    char *zSql = "SELECT MAX(ROWID), ERROR_CODE, SN_INFO, SN_STATUS, SN_TIMESTAMP, VENDOR_ID, VENDOR_ERROR_CODE \
                    FROM STATUS_NOTIFICATION \
                   WHERE CONNECTOR_ID = ? ;" ;
    int ret ;

    sqlite3 *pDb ;
    sqlite3_stmt *pstmt ;
    const char *pzTail ;
    int connector_id = *(int *)ppcommand[1] ;

    printf("connector id : %d\n", connector_id) ;

    ret = sqlite3_open("test.db", &pDb) ;
    if(ret != SQLITE_OK) {
        printf("sqlite open error : %s\n", sqlite3_errmsg(pDb)) ;
        return -1 ;
    }              

    ret = sqlite3_prepare_v2(pDb, zSql, strlen(zSql), &pstmt, &pzTail) ;
    if(ret != SQLITE_OK) {
        printf("sqlite prepare error : %s\n", sqlite3_errmsg(pDb)) ;
        sqlite3_close(pDb) ;
        return -1 ;
    }   

    ret = sqlite3_bind_int(pstmt, 1, connector_id) ;
    if(ret != SQLITE_OK) {
        printf("sqlite bind error : %s\n", sqlite3_errmsg(pDb)) ;
        goto end ;
    }

    ret = sqlite3_step(pstmt) ;
    if(ret != SQLITE_ROW) {
        printf("sqlite step error : %s\n", sqlite3_errmsg(pDb)) ;
        goto end ;
    }

    if(sqlite3_column_int(pstmt, 0) == 0) {
        printf("connector id %d has no data\n", connector_id) ;
        goto end ;
    }

    make_message_id(message_id) ;

    printf("%d\n", sqlite3_column_int(pstmt, 0)) ;

    rreq.connector_id = connector_id ;
    rreq.error_code = (char *)sqlite3_column_text(pstmt, 1) ;
    rreq.info = (char *)sqlite3_column_text(pstmt, 2) ;
    rreq.status = (char *)sqlite3_column_text(pstmt, 3) ;
    rreq.timestamp = (char*)sqlite3_column_text(pstmt, 4) ;
    rreq.vendor_id = (char *)sqlite3_column_text(pstmt, 5) ;
    rreq.vendor_error_code = (char *)sqlite3_column_text(pstmt, 6) ;

    printf("error_code : %s\n", rreq.error_code) ;
    printf("into : %s\n", rreq.error_code) ;
    printf("status : %s\n", rreq.status) ;
    printf("timestamp : %s\n", rreq.timestamp) ;
    printf("vendor_id : %s\n", rreq.vendor_id) ;
    printf("vendor_error_code : %s\n", rreq.vendor_error_code) ;


    /*
    strcpy(error_code_buf, charge_point_error_code_values[charge_point_error_code_no_error]) ;
    strcpy(info_buf, "connector id #1 operate well") ;
    strcpy(status_buf, charge_point_status_values[charge_point_status_available]) ;
    get_future_date(timestamp_buf, 0) ;
    strcpy(vendor_id_buf, "") ;
    strcpy(vendor_error_code_buf, "") ;
    */

    make_ocpp_status_notification_req_message(user_data_buffer.resp_buf, message_id, &rreq) ;
    strcpy(conf_act.message_id, message_id) ;
    conf_act.func = do_status_notification_conf ;

    sqlite3_finalize(pstmt) ;
    sqlite3_close(pDb) ;

    return 0 ;

end :
    sqlite3_finalize(pstmt) ;
    sqlite3_close(pDb) ;
    return -1 ;
}

int do_status_notification_conf(ocpp_callresult_message *resp) {
    printf("do status notification conf : %s\n", resp->payload) ;

    pthread_mutex_lock(&ocpp_mutex) ;
    ocpp_comm_end = true ;
    pthread_mutex_unlock(&ocpp_mutex) ;
    return 0 ;
}

int do_status_notification_error(ocpp_callerror_message *msg) {
    return 0 ;    
}
