#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */

void init_boot_notification_req_message() {
    boot_noti_req.charge_box_serial_number.key = boot_notification_req_field_names[boot_notification_req_charge_box_serial_number] ;
    boot_noti_req.charge_box_serial_number.val.str_val = bnr_charge_box_serial_number ;

    boot_noti_req.charge_point_model.key = boot_notification_req_field_names[boot_notification_req_charge_point_model] ;
    boot_noti_req.charge_point_model.val.str_val = bnr_charge_point_motel ;

    boot_noti_req.charge_point_serial_number.key = boot_notification_req_field_names[boot_notification_req_charge_point_serial_number] ;
    boot_noti_req.charge_point_serial_number.val.str_val = bnr_charge_point_serial_number ;

    boot_noti_req.charge_point_vendor.key = boot_notification_req_field_names[boot_notification_req_charge_point_vendor] ;
    boot_noti_req.charge_point_vendor.val.str_val = bnr_charge_point_vendor ;

    boot_noti_req.firmware_version.key = boot_notification_req_field_names[boot_notification_req_firmware_version] ;
    boot_noti_req.firmware_version.val.str_val = bnr_firmaware_version ;

    boot_noti_req.iccid.key = boot_notification_req_field_names[boot_notification_req_iccid] ;
    boot_noti_req.iccid.val.str_val = bnr_iccid ;
    
    boot_noti_req.imsi.key = boot_notification_req_field_names[boot_notification_req_imsi] ;
    boot_noti_req.imsi.val.str_val = bnr_imsi ;

    boot_noti_req.meter_serial_number.key = boot_notification_req_field_names[boot_notification_req_meter_serial_number] ;
    boot_noti_req.meter_serial_number.val.str_val = bnr_meter_serial_number ;

    boot_noti_req.meter_type.key = boot_notification_req_field_names[boot_notification_req_meter_type] ;
    boot_noti_req.meter_type.val.str_val = bnr_meter_type ;
}

void init_boot_notification_conf_message() {
    boot_noti_conf.current_time.key = boot_notification_conf_field_names[boot_notification_conf_current_time] ;
    boot_noti_conf.current_time.val.str_val = bnc_current_time ;

    boot_noti_conf.interval.key = boot_notification_conf_field_names[boot_notification_conf_interval] ;

    boot_noti_conf.status.key = boot_notification_conf_field_names[boot_notification_conf_status] ;
    boot_noti_conf.status.val.str_val = bnc_status ;
}

int make_ocpp_boot_notification_req_message(char* buf, char* message_id, raw_boot_notification_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[BOOT_NOTIFICATION_INDEX].action ;

    boot_noti_req.charge_box_serial_number.key = boot_notification_req_field_names[boot_notification_req_charge_box_serial_number] ;
    boot_noti_req.charge_box_serial_number.val.str_val = rreq->charge_box_serial_number ;

    boot_noti_req.charge_point_model.key = boot_notification_req_field_names[boot_notification_req_charge_point_model] ;
    boot_noti_req.charge_point_model.val.str_val = rreq->charge_point_model ;

    boot_noti_req.charge_point_serial_number.key = boot_notification_req_field_names[boot_notification_req_charge_point_serial_number] ;
    boot_noti_req.charge_point_serial_number.val.str_val = rreq->charge_point_serial_number ;

    boot_noti_req.charge_point_vendor.key = boot_notification_req_field_names[boot_notification_req_charge_point_vendor] ;
    boot_noti_req.charge_point_vendor.val.str_val = rreq->charge_point_vendor ;

    boot_noti_req.firmware_version.key = boot_notification_req_field_names[boot_notification_req_firmware_version] ;
    boot_noti_req.firmware_version.val.str_val = rreq->firmaware_version ;

    boot_noti_req.iccid.key = boot_notification_req_field_names[boot_notification_req_iccid] ;
    boot_noti_req.iccid.val.str_val = rreq->iccid ;

    boot_noti_req.imsi.key = boot_notification_req_field_names[boot_notification_req_imsi] ;
    boot_noti_req.imsi.val.str_val = rreq->imsi ;

    boot_noti_req.meter_serial_number.key = boot_notification_req_field_names[boot_notification_req_meter_serial_number] ;
    boot_noti_req.meter_serial_number.val.str_val = rreq->meter_serial_number ;

    boot_noti_req.meter_type.key = boot_notification_req_field_names[boot_notification_req_meter_type] ;
    boot_noti_req.meter_type.val.str_val = rreq->meter_type ;

    object = json_object_new_object() ;
    if(boot_noti_req.charge_box_serial_number.val.str_val != NULL)
        json_object_object_add(object, boot_noti_req.charge_box_serial_number.key, json_object_new_string(boot_noti_req.charge_box_serial_number.val.str_val)) ;

    json_object_object_add(object, boot_noti_req.charge_point_model.key, json_object_new_string(boot_noti_req.charge_point_model.val.str_val)) ;
    
    if(boot_noti_req.charge_point_serial_number.val.str_val != NULL)
        json_object_object_add(object, boot_noti_req.charge_point_serial_number.key, json_object_new_string(boot_noti_req.charge_point_serial_number.val.str_val)) ;

    json_object_object_add(object, boot_noti_req.charge_point_vendor.key, json_object_new_string(boot_noti_req.charge_point_vendor.val.str_val)) ;
    
    if(boot_noti_req.firmware_version.val.str_val != NULL)
        json_object_object_add(object, boot_noti_req.firmware_version.key, json_object_new_string(boot_noti_req.firmware_version.val.str_val)) ;
    
    if(boot_noti_req.iccid.val.str_val != NULL)
        json_object_object_add(object, boot_noti_req.iccid.key, json_object_new_string(boot_noti_req.iccid.val.str_val)) ;
    
    if(boot_noti_req.imsi.val.str_val != NULL)
        json_object_object_add(object, boot_noti_req.imsi.key, json_object_new_string(boot_noti_req.imsi.val.str_val)) ;
    
    if(boot_noti_req.meter_serial_number.val.str_val != NULL)
        json_object_object_add(object, boot_noti_req.meter_serial_number.key, json_object_new_string(boot_noti_req.meter_serial_number.val.str_val)) ;
    
    if(boot_noti_req.meter_type.val.str_val != NULL)
        json_object_object_add(object, boot_noti_req.meter_type.key, json_object_new_string(boot_noti_req.meter_type.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;

    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;

    return 0 ;
}

int make_ocpp_boot_notification_conf_message(char * buf, char *message_id, raw_boot_notification_conf *rconf) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    boot_noti_conf.current_time.key = boot_notification_conf_field_names[boot_notification_conf_current_time] ;
    boot_noti_conf.current_time.val.str_val = rconf->current_time ;

    boot_noti_conf.interval.key = boot_notification_conf_field_names[boot_notification_conf_interval] ;
    boot_noti_conf.interval.val.int_val = rconf->interval ;

    boot_noti_conf.status.key = boot_notification_conf_field_names[boot_notification_conf_status] ;
    boot_noti_conf.status.val.str_val = rconf->status ;

    object = json_object_new_object() ;
    json_object_object_add(object, boot_noti_conf.current_time.key, json_object_new_string(boot_noti_conf.current_time.val.str_val)) ;
    json_object_object_add(object, boot_noti_conf.interval.key, json_object_new_int(boot_noti_conf.interval.val.int_val)) ;
    json_object_object_add(object, boot_noti_conf.status.key, json_object_new_string(boot_noti_conf.status.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;

    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;
    json_object_put(object) ;

    return 0 ;
}

int parse_ocpp_boot_notification_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, boot_noti_req.charge_box_serial_number.key) ;
    strcpy(boot_noti_req.charge_box_serial_number.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_req.charge_point_model.key) ;
    strcpy(boot_noti_req.charge_point_model.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_req.charge_point_serial_number.key) ;
    strcpy(boot_noti_req.charge_point_serial_number.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_req.charge_point_vendor.key) ;
    strcpy(boot_noti_req.charge_point_vendor.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_req.firmware_version.key) ;
    strcpy(boot_noti_req.firmware_version.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_req.iccid.key) ;
    strcpy(boot_noti_req.iccid.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_req.imsi.key) ;
    strcpy(boot_noti_req.imsi.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_req.meter_serial_number.key) ;
    strcpy(boot_noti_req.meter_serial_number.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_req.meter_type.key) ;
    strcpy(boot_noti_req.meter_type.val.str_val, (char *)json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;

}

int parse_ocpp_boot_notification_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, boot_noti_conf.current_time.key) ;
    strcpy(boot_noti_conf.current_time.val.str_val, (char *)json_object_get_string(value)) ;

    value = json_object_object_get(object, boot_noti_conf.interval.key) ;
    boot_noti_conf.interval.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, boot_noti_conf.status.key) ;
    strcpy(boot_noti_conf.status.val.str_val, (char *)json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

static field_buffers field_buff[] = {
    {"chargeBoxSerialNumber", bnr_charge_box_serial_number},
    {"chargePointModel", bnr_charge_point_motel},
    {"chargePointSerialNumber", bnr_charge_point_serial_number},
    {"chargePointVendor", bnr_charge_point_vendor},
    {"firmwareVersion", bnr_firmaware_version},
    {"icid", bnr_iccid},
    {"imsi", bnr_imsi},
    {"meterSerialNumber", bnr_meter_serial_number},
    {"meterType", bnr_meter_type}
} ;

int do_boot_notification_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_boot_notification_req rreq ;
    FILE *file = fopen(ppcommand[1], "r") ;
    if(file == NULL) {
        printf("Error opening file : %s", ppcommand[1]) ;
        return -1 ;
    }


    char line[1024] ;
    char *pdelimiter ;
    int length = sizeof(field_buff) / sizeof(field_buffers) ;
    while(fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0 ;
        pdelimiter = strchr(line, '=') ;
        *pdelimiter = 0 ;
        pdelimiter++ ;

        for(int i = 0 ; i < length ; i++) {
            if(strcmp(trim(line), field_buff[i].field_name) == 0) {
                strcpy(field_buff[i].val.buffer, trim(pdelimiter)) ;
                break ;
            }
        }
    }

    rreq.charge_box_serial_number = NULL ;
    rreq.charge_point_model = NULL ;
    rreq.charge_point_serial_number = NULL ;
    rreq.charge_point_vendor = NULL ;
    rreq.firmaware_version = NULL ;
    rreq.iccid = NULL ;
    rreq.imsi = NULL ;
    rreq.meter_serial_number = NULL ;
    rreq.meter_type = NULL ;

    if(strlen(bnr_charge_box_serial_number) != 0)
        rreq.charge_box_serial_number = bnr_charge_box_serial_number ;
    
    rreq.charge_point_model = bnr_charge_point_motel ;
    
    if(strlen(bnr_charge_point_serial_number) != 0)
        rreq.charge_point_serial_number = bnr_charge_point_serial_number ;

    rreq.charge_point_vendor = bnr_charge_point_vendor ;

    if(strlen(bnr_firmaware_version) != 0) 
        rreq.firmaware_version = bnr_firmaware_version ;

    if(strlen(bnr_iccid) != 0)
        rreq.iccid = bnr_iccid ;

    if(strlen(bnr_imsi) != 0)
        rreq.imsi = bnr_imsi ;

    if(strlen(bnr_meter_serial_number) != 0)
        rreq.meter_serial_number = bnr_meter_serial_number ;

    if(strlen(bnr_meter_type) != 0) 
        rreq.meter_type = bnr_meter_type ;

    make_message_id(message_id) ;
    
    make_ocpp_boot_notification_req_message(user_data_buffer.resp_buf, message_id, &rreq) ;

    conf_act.func = do_boot_notification_conf ;
    strcpy(conf_act.message_id, message_id) ;

    return 0 ;
}

int do_boot_notification_conf(ocpp_callresult_message *resp) {
    printf("do boot notification conf : %s\n", resp->payload) ;
    
    return 0 ;
}

int do_boot_notification_error(ocpp_callerror_message *error) {
    return 0 ;    
}