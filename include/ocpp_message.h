#ifndef OCPP_MESSAGE_H
#define OCPP_MESSAGE_H

#include <stdbool.h>
#include "ocpp.h"

typedef struct {
    int message_type ;
    char *message_id ;
    char *action ;
    char *payload ;
} ocpp_call_message ;

typedef struct {
    int message_type ;
    char *message_id ;
    char *payload ;
} ocpp_callresult_message ;

typedef struct {
    int message_type ;
    char *message_id ;
    char *error_code ;
    char *error_description ;
    char *error_details ;
} ocpp_callerror_message ;

typedef struct {
    char req_buf[4096] ;
    char resp_buf[4096] ;
} user_data ;

typedef struct {
    message_field id_tag ;
} authorize_req ;

typedef struct {
    message_field id_tag_info ;
} authorize_conf ;

typedef struct {
    message_field charge_box_serial_number ;
    message_field charge_point_model ;
    message_field charge_point_serial_number ;
    message_field charge_point_vendor ;
    message_field firmware_version ;
    message_field iccid ;
    message_field imsi ;
    message_field meter_serial_number ;
    message_field meter_type ;
} boot_notification_req ;

typedef struct {
    char *charge_box_serial_number ;
    char *charge_point_model ;
    char *charge_point_serial_number ;
    char *charge_point_vendor ;
    char *firmaware_version ;
    char *iccid ;
    char *imsi ;
    char *meter_serial_number ;
    char *meter_type ;
} raw_boot_notification_req ;

typedef struct {
    message_field current_time ;
    message_field interval ;
    message_field status ;
} boot_notification_conf ;

typedef struct {
    char *current_time ;
    int interval ;
    char *status ;
} raw_boot_notification_conf ;

typedef struct {
    message_field reservation_id ;
} cancel_reservation_req ;

typedef struct {
    message_field status ;
} cancel_reservation_conf ;

typedef struct {
    message_field connector_id ;
    message_field type ;
} change_availability_req ;

typedef struct {
    int connector_id ;
    char *type ;
} raw_change_availability_req ;

typedef struct {
    message_field status ;
} change_availability_conf ;

typedef struct {
    message_field key ;
    message_field value ;
} change_configuration_req ;

typedef struct {
    char *key ;
    char *value ;
} raw_change_configuration_req ;

typedef struct {
    message_field status ;
} change_configuration_conf ;

typedef struct {

} clear_cache_req ;

typedef struct {
    message_field status ;
} clear_cache_conf ;

typedef struct {
    message_field id ;
    message_field connector_id ;
    message_field charging_profile_purpose ;
    message_field stack_level ;
} clear_charging_profile_req ;

typedef struct {
    int id ;
    int connector_id ;
    char *charging_profile_purpose ;
    int stack_level ;
} raw_clear_charging_profile_req ;

typedef struct {
    message_field status ;
} clear_charging_profile_conf ;

typedef struct {
    message_field vendor_id ;
    message_field message_id ;
    message_field data ;
} data_transfer_req ;

typedef struct {
    char *vendor_id ;
    char *message_id ;
    char *data ;
} raw_data_transfer_req ;

typedef struct {
    message_field status ;
    message_field data ;
} data_transfer_conf ;

typedef struct {
    char *status ;
    char *data ;
} raw_data_transfer_conf ;

typedef struct {
    message_field status ;
} diagnostics_status_notification_req ;

typedef struct {

} diagnostics_status_notifidation_conf ;

typedef struct {
    message_field status ;
} firmware_status_notification_req ;

typedef struct {

} firmware_status_notification_conf ;

typedef struct {
    message_field connector_id ;
    message_field duration ;
    message_field charging_rate_unit ;
} get_composite_schedule_req ;

typedef struct {
    int connector_id ;
    int duration ;
    char *charging_rate_unit ;
} raw_get_composite_schedule_req ;

typedef struct {
    message_field status ;
    message_field connector_id ;
    message_field schedule_start ;
    message_field charging_schedule ;
} get_composite_schedule_conf ;

typedef struct {
    char *status ;
    int connector_id ;
    char *schedule_start ;
    raw_charging_schedule *charging_schedule ;
} raw_get_composite_schedule_conf ;

typedef struct {
    message_field key ;
    int number_of_key ;
} get_configuration_req ;

typedef struct {
    char **key ;
    int number_of_key ;
} raw_get_configuration_req ;

typedef struct {
    message_field configuration_key ;
    message_field unknown_key ;
    int number_of_configuration_key ;
    int number_of_unknown_key ;
} get_configuration_conf ;

typedef struct {
    raw_key_value *configuration_key ;
    char **unknown_key ;
    int number_of_configuration_key ;
    int number_of_unknown_key ;
} raw_get_configuration_conf ;

typedef struct {
    message_field location ;
    message_field retries ;
    message_field retry_interval ;
    message_field start_time ;
    message_field stop_time ;
} get_diagnostics_req ;

typedef struct {
    char *location ;
    int retries ;
    int retry_interval ;
    char *start_time ;
    char *stop_time ;
} raw_get_diagnostics_req ;

typedef struct {
    message_field file_name ;
} get_diagnostics_conf ;

typedef struct {

} get_local_list_version_req ;

typedef struct {
    message_field list_version ;
} get_local_list_version_conf ;

typedef struct {

} heartbeat_req ;

typedef struct {
    message_field current_time ;
} heartbeat_conf ;

typedef struct {
    message_field connector_id ;
    message_field transaction_id ;
    message_field meter_value ;
    int number_of_meter_value ;
} meter_values_req ;

typedef struct {
    int connector_id ;
    int transaction_id ;
    raw_meter_value *meter_value ;
    int number_of_meter_value ;
} raw_meter_values_req ;

typedef struct {

} meter_values_conf ;

typedef struct {
    message_field connector_id ;
    message_field id_tag ;
    message_field charging_profile ;
} remote_start_transaction_req ;

typedef struct {
    int connector_id ;
    char *id_tag ;
    raw_charging_profile *charging_profile ;
} raw_remote_start_transaction_req ;

typedef struct {
    message_field status ;
} remote_start_transaction_conf ;

typedef struct {
    message_field transaction_id ;
} remote_stop_transaction_req ;

typedef struct {
    message_field status ;
} remote_stop_transaction_conf ;

typedef struct {
    message_field connector_id ;
    message_field expiry_date ;
    message_field id_tag ;
    message_field parent_id_tag ;
    message_field reservation_id ;
} reserve_now_req ;

typedef struct {
    int connector_id ;
    char *expiry_date ;
    char *id_tag ;
    char *parent_id_tag ;
    int reservation_id ;
} raw_reserve_now_req ;

typedef struct {
    message_field status ;
} reserve_now_conf ;

typedef struct {
    message_field type ;
} reset_req ;

typedef struct {
    message_field status ;
} reset_conf ;

typedef struct {
    message_field list_version ;
    message_field local_authorization_list ;
    message_field update_type ;
    int number_of_authrization_data ;
} send_local_list_req ;

typedef struct {
    int list_version ;
    raw_authorization_data *local_authorization_list ;
    char *update_type ;
    int number_of_authorization_data ;
} raw_send_local_list_req ;

typedef struct {
    message_field status ;
} send_local_list_conf ;

typedef struct {
    message_field connector_id ;
    message_field cs_charging_profiles ;
} set_charging_profile_req ;

typedef struct {
    int connector_id ;
    raw_charging_profile *cs_charging_profiles ;
} raw_set_charging_profile_req ;

typedef struct {
    message_field status ;
} set_charging_profile_conf ;

typedef struct {
    message_field connector_id ;
    message_field id_tag ;
    message_field meter_start ;
    message_field reservation_id ;
    message_field timestamp ;
} start_transaction_req ;

typedef struct {
    int connector_id ;
    char *id_tag ;
    int meter_start ;
    int reservation_id ;
    char *timestamp ;
} raw_start_transaction_req ;

typedef struct {
    message_field id_tag_info ;
    message_field transaction_id ;
} start_transaction_conf ;

typedef struct {
    raw_id_tag_info *id_tag_info ;
    int transaction_id ;
} raw_start_transaction_conf ;

typedef struct {
    message_field connector_id ;
    message_field error_code ;
    message_field info ;
    message_field status ;
    message_field timestamp ;
    message_field vendor_id ;
    message_field vendor_error_code ;
} status_notification_req ;

typedef struct {
    int connector_id ;
    char *error_code ;
    char *info ;
    char *status ;
    char *timestamp ;
    char *vendor_id ;
    char *vendor_error_code ;
} raw_status_notification_req ;

typedef struct {

} status_notification_conf ;

typedef struct {
    message_field id_tag ;
    message_field meter_stop ;
    message_field timestamp ;
    message_field transaction_id ;
    message_field reason ;
    message_field transaction_data ;
    int number_of_transaction_data ;
} stop_transaction_req ;

typedef struct {
    char *id_tag ;
    int meter_stop ;
    char *timestamp ;
    int transaction_id ;
    char *reason ;
    raw_meter_value *transaction_data ;
    int number_of_transaction_data ;
} raw_stop_transaction_req ;

typedef struct {
    message_field id_tag_info ;
} stop_transaction_conf ;

typedef struct {
    raw_id_tag_info *id_tag_info ;
} raw_stop_transaction_conf ;

typedef struct {
    message_field requested_message ;
    message_field connector_id ;
} trigger_message_req ;

typedef struct {
    char *requested_message ;
    int connector_id ;
} raw_trigger_message_req ;

typedef struct {
    message_field status ;
} trigger_message_conf ;

typedef struct {
    message_field connector_id ;
} unlock_connector_req ;

typedef struct {
    message_field status ;
} unlock_connector_conf ;

typedef struct {
    message_field location ;
    message_field retries ;
    message_field retrieve_date ;
    message_field retry_interval ;
} update_firmware_req ;

typedef struct {
    char *location ;
    int retries ;
    char *retrieve_date ;
    int retry_interval ;
} raw_update_firmware_req ;

typedef struct {

} update_firmware_conf ;

#endif