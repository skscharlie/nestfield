#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

int proc_boot_notification_req(char *req, char *resp) ;

int boot_notification_test() {
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_boot_notification_req rreq ;
    char charge_box_serial_number_buf[STRING_25_TYPE_LENGTH + 1], charge_point_model_buf[STRING_20_TYPE_LENGTH + 1] ;
    char charge_point_serial_number_buf[STRING_25_TYPE_LENGTH + 1], charge_point_vendor_buf[STRING_20_TYPE_LENGTH + 1] ;
    char firrmware_version_buf[STRING_50_TYPE_LENGTH + 1], iccid_buf[STRING_20_TYPE_LENGTH + 1] ;
    char imsi_buf[STRING_20_TYPE_LENGTH + 1], meter_serial_number_buf[STRING_25_TYPE_LENGTH + 1] ;
    char meter_type_buf[STRING_25_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;

    rreq.charge_box_serial_number = charge_box_serial_number_buf ;
    rreq.charge_point_model = charge_point_model_buf ;
    rreq.charge_point_serial_number = charge_point_serial_number_buf ;
    rreq.charge_point_vendor = charge_point_vendor_buf ;
    rreq.firmaware_version = firrmware_version_buf ;
    rreq.iccid = iccid_buf ;
    rreq.imsi = imsi_buf ;
    rreq.meter_serial_number = meter_serial_number_buf ;
    rreq.meter_type = meter_type_buf ;

    make_ci25_type_string(charge_box_serial_number_buf) ;
    make_ci20_type_string(charge_point_model_buf) ;
    make_ci25_type_string(charge_point_serial_number_buf) ;
    make_ci20_type_string(charge_point_vendor_buf) ;
    make_ci50_type_string(firrmware_version_buf) ;
    make_ci20_type_string(iccid_buf) ;
    make_ci20_type_string(imsi_buf) ;
    make_ci25_type_string(meter_serial_number_buf) ;
    make_ci25_type_string(meter_type_buf) ;

    make_ocpp_boot_notification_req_message(req_buf, message_id, &rreq) ;

    proc_boot_notification_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_boot_notification_conf_message() ;
    parse_ocpp_boot_notification_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", boot_noti_conf.current_time.key, boot_noti_conf.current_time.val.str_val) ;
    printf("key : %s, value : %d\n", boot_noti_conf.interval.key, boot_noti_conf.interval.val.int_val) ;
    printf("key : %s, value : %s\n", boot_noti_conf.status.key, boot_noti_conf.status.val.str_val) ;

    return 0 ;
}

int proc_boot_notification_req(char *req, char *resp) {
    ocpp_call_message msg ;
    raw_boot_notification_conf rconf ;
    char current_time_buf[DATE_TIME_LENGTH + 1], status_buf[MAX_STATUS_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_boot_notification_req_message() ;
    parse_ocpp_boot_notification_req_message(msg.payload) ;

    get_future_date(current_time_buf, 0) ;
    strcpy(status_buf, registration_status_values[registration_status_accepted]) ;

    rconf.current_time = current_time_buf ;
    rconf.status = status_buf ;
    rconf.interval = 60 ;

    make_ocpp_boot_notification_conf_message(resp, msg.message_id, &rconf) ;
    return 0 ;
}