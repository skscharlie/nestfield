#ifndef OCPP_ENUM_H
#define OCPP_ENUM_H

/*
 * Messagse field names
 */
extern char* authorization_req_field_names[] ;
enum authorization_req_field {
    authorization_req_id_tag = 0
} ;

extern char* authorization_conf_field_names[] ;
enum authorization_conf_field {
    authorization_conf_id_tag_info = 0
} ;

extern char* boot_notification_req_field_names[] ;
enum boot_notification_req_fields {
    boot_notification_req_charge_box_serial_number = 0,
    boot_notification_req_charge_point_model,
    boot_notification_req_charge_point_serial_number,
    boot_notification_req_charge_point_vendor,
    boot_notification_req_firmware_version,
    boot_notification_req_iccid,
    boot_notification_req_imsi,
    boot_notification_req_meter_serial_number,
    boot_notification_req_meter_type
} ;

extern char* boot_notification_conf_field_names[] ;
enum boot_notification_conf_fields {
    boot_notification_conf_current_time = 0,
    boot_notification_conf_interval,
    boot_notification_conf_status
} ;

extern char* cancel_reservation_req_field_names[] ;
enum cancel_reservation_req_field {
    cancel_reservation_req_reservation_id = 0
} ;

extern char* cancel_reservation_conf_field_names[] ;
enum cancel_reservation_conf_field {
    cancel_reservation_conf_status = 0
} ;

extern char* change_availability_req_field_names[] ;
enum change_availability_req_fields {
    change_availability_req_connector_id = 0,
    change_availability_req_type
} ;

extern char* change_availability_conf_field_names[] ;
enum change_availability_conf_field {
    change_availability_conf_status = 0
} ;

extern char* change_configuration_req_field_names[] ;
enum change_configuration_req_fields {
    change_configuration_req_key = 0,
    change_configuration_req_value
} ;

extern char* change_configuration_conf_field_names[] ;
enum change_configuration_conf_field {
    change_configuration_conf_status = 0
} ;

extern char* clear_cache_conf_field_names[] ;
enum clear_cache_conf_field {
    clear_cache_conf_status = 0
} ;

extern char* clear_charging_profile_req_field_names[] ;
enum clear_charging_profile_req_fields {
    clear_charging_profile_req_id = 0,
    clear_charging_profile_req_connector_id,
    clear_charging_profile_req_charging_profile_purpose,
    clear_charging_profile_req_stack_level
} ;

extern char* clear_charging_profile_conf_field_names[] ;
enum clear_charging_profile_conf_field {
    clear_charging_profile_conf_status = 0
} ;

extern char* data_transfer_req_field_names[] ;
enum data_transfer_req_fields {
    data_trans_req_vendor_id = 0,
    data_trans_req_message_id,
    data_trans_req_data
} ;

extern char* data_transfer_conf_field_names[] ;
enum data_transfer_conf_fields {
    data_trans_conf_status = 0,
    data_trans_conf_data
} ;

extern char* diagnostics_status_notification_req_field_name[] ;
enum diagnostics_status_notification_req_field {
    diagnostics_status_notification_req_status = 0
} ;

extern char* firmware_status_notification_req_field_name[] ;
enum firmware_status_notification_req_field {
    firmware_status_notification_req_status = 0
} ;

extern char* get_composite_schedule_req_field_names[] ;
enum get_composite_schedule_req_field {
    get_composite_schedule_req_connector_id = 0,
    get_composite_schedule_req_duration, 
    get_composite_schedule_req_charging_rate_unit
} ;

extern char* get_composite_schedule_conf_field_names[] ;
enum get_composite_schedule_conf_field {
    get_composite_schedule_conf_status = 0,
    get_composite_schedule_conf_connectoe_id,
    get_composite_schedule_conf_schedule_start,
    get_composite_schedule_conf_charging_schedule
} ;

extern char* get_configuration_req_field_name[] ;
enum get_configuration_req_field {
    get_configuration_req_key = 0
} ;

extern char* get_configuration_conf_field_names[] ;
enum get_configuration_conf_field {
    get_configuration_conf_configuration_key = 0,
    get_configuration_conf_unknown_key
} ;

extern char* get_diagnostics_req_field_names [] ;
enum get_diagnostics_req_field {
    get_diagnostics_req_location = 0, 
    get_diagnostics_req_retries,
    get_diagnostics_req_retry_interval,
    get_diagnostics_req_start_time,
    get_diagnostics_req_stop_time
} ;

extern char* get_diagnostics_conf_field_name[] ;
enum get_diagnostics_conf_field {
    get_diagnostics_conf_file_name = 0
} ;

extern char* get_local_list_version_conf_field_name[] ;
enum get_local_list_version_conf_field {
    get_local_list_version_conf_list_version = 0
} ;

extern char* heartbeat_conf_field_name[] ;
enum heartbeat_conf_field {
    heartbeat_conf_current_time = 0
} ;

extern char* meter_values_req_field_names[] ;
enum meter_values_req_field {
    meter_values_req_connector_id = 0,
    meter_values_req_transaction_id,
    meter_values_req_meter_value
} ;

extern char* remote_start_transaction_req_field_names[] ;
enum remote_start_transaction_req_field {
    remote_start_transaction_req_connector_id = 0,
    remote_start_transaction_req_id_tag,
    remote_start_transaction_req_charging_profile
} ;

extern char* remote_start_transaction_conf_field_name[] ;
enum remote_start_transaction_conf_field {
    remote_start_transaction_conf_status = 0
} ;

extern char* remote_stop_transaction_req_field_name[] ;
enum remote_stop_transaction_req_field {
    remote_stop_transaction_req_transaction_id = 0
} ;

extern char* remote_stop_transaction_conf_field_name[] ;
enum remote_stop_transaction_conf_field {
    remote_stop_transaction_conf_status = 0
} ;

extern char* reserve_now_req_field_names[] ;
enum reserve_now_req_field {
    reserve_now_req_connector_id = 0,
    reserve_now_req_expiry_date,
    reserve_now_req_id_tag,
    reserve_now_req_parent_id_tag,
    reserve_now_req_reseration_id
} ;

extern char* reserve_now_conf_field_name[] ;
enum reserve_now_conf_field {
    reserve_now_conf_status = 0
} ;

extern char* reset_req_field_name[] ;
enum reset_req_field {
    reset_req_type = 0
} ;

extern char* reset_conf_field_name[] ;
enum reset_conf_field {
    reset_conf_status = 0
} ;

extern char* send_local_list_req_field_names[] ;
enum send_local_list_req_field {
    send_local_list_req_list_version = 0,
    send_local_list_req_local_authorization_list,
    send_local_list_req_update_type
} ;

extern char* send_local_list_conf_field_name[] ;
enum send_local_list_conf_field {
    send_local_list_conf_status = 0
} ;

extern char* set_charging_profile_req_field_names[] ;
enum set_charging_profile_req_field {
    set_charging_profile_req_connector_id = 0,
    set_charging_profile_req_cs_charging_profile
} ;

extern char* set_charging_profile_conf_field_name[] ;
enum set_charging_profile_conf_field {
    set_charging_profile_conf_status = 0
} ;

extern char* start_transaction_req_field_names[] ;
enum start_transaction_req_field {
    start_transaction_req_connector_id = 0,
    start_transaction_req_id_tag,
    start_transaction_req_meter_start,
    start_transaction_req_reservation_id,
    start_transaction_req_timestamp
} ;

extern char* start_transaction_conf_field_names[] ;
enum start_transaction_conf_field {
    start_transaction_conf_id_tag_info = 0,
    start_transaction_conf_transaction_id
} ;

extern char* status_notification_req_field_names[] ;
enum status_notification_req_field {
    status_notification_req_connector_id = 0,
    status_notification_req_error_code,
    status_notification_req_info,
    status_notification_req_status,
    status_notification_req_timestamp,
    status_notification_req_vendor_id,
    status_notification_req_vendor_error_code
} ;

extern char* stop_transaction_req_field_names[] ;
enum stop_transaction_req_field {
    stop_transaction_req_id_tag = 0,
    stop_transaction_req_meter_stop,
    stop_transaction_req_timestamp,
    stop_transaction_req_transaction_id,
    stop_transaction_req_reason,
    stop_transaction_req_transaction_data
} ;

extern char* stop_transaction_conf_field_name[] ;
enum stop_transaction_conf_field {
    stop_transaction_conf_id_tag_info = 0
} ;

extern char* trigger_message_req_field_names[] ;
enum trigger_message_req_field {
    trigger_message_req_requested_message = 0,
    trigger_message_req_connector_id
} ;

extern char* trigger_message_conf_field_name[] ;
enum trigger_message_conf_field {
    trigger_message_conf_status = 0
} ;

extern char* unlock_connector_req_field_name[] ;
enum unlock_connector_req_field {
    unlock_connector_req_connector_id = 0
} ;

extern char* unlock_connector_conf_field_name[] ;
enum unlock_connector_conf_field {
    unlock_connector_conf_status = 0 
} ;

extern char* update_firmware_req_field_names[] ;
enum update_firmware_req_field {
    update_firmware_req_location = 0,
    update_firmware_req_retries,
    update_firmware_req_retrieve_date,
    update_firmware_req_retry_interval
} ;

/*
 * Class field
 */
extern char* authorization_data_field_names[] ;
enum authrization_data_field {
    authorization_data_id_tag = 0,
    authorization_data_id_tag_info
} ;

extern char* charging_profile_field_names[] ;
enum charging_profile_field {
    charging_profile_charging_profile_id = 0,
    charging_profile_transaction_id,
    charging_profile_stack_level,
    charging_profile_charging_profile_purpose,
    charging_profile_charging_profile_kind,
    charging_profile_recurrency_kind,
    charging_profile_valid_from,
    charging_profile_valid_to,
    charging_profile_charging_schedule
} ;

extern char* charging_schedule_field_names[] ;
enum charging_schedule_field {
    charging_schedule_duration = 0,
    charging_schedule_start_schedule,
    charging_schedule_charging_rate_unit,
    charging_schedule_charging_schedule_period,
    charging_schedule_min_charging_rate
} ;

extern char* charging_schedule_period_field_names[] ;
enum charging_schedule_period_field {
    charging_schedule_period_start_period = 0,
    charging_schedule_period_limit,
    charging_schedule_period_number_phases
} ;

extern char* id_tag_info_field_names[] ;
enum id_tag_info_field {
    id_tag_info_expiry_date = 0,
    id_tag_info_parient_id_tag,
    id_tag_info_status
} ;

extern char* key_value_field_names[] ;
enum key_value_field {
    key_value_key = 0,
    key_value_readonly,
    key_value_value
} ;

extern char* meter_value_field_names[] ;
enum meter_value_field {
    meter_value_timestamp = 0,
    meter_value_sampled_value
} ;

extern char* sampled_value_field_names[] ;
enum sampled_value_field {
    sampled_value_value = 0,
    sampled_value_context,
    sampled_value_format,
    sampled_value_measurand,
    sampled_value_phase,
    sampled_value_location,
    sampled_value_unit
} ;

/*
 * Enumeration 
*/
extern char* authorization_status_values[] ;
enum authorization_status {
    authorization_status_accepted = 0,
    authorization_status_blocked,
    authorization_status_expired,
    authorization_status_invalid,
    authorization_status_current_tx
} ;

extern char* availability_status_values[] ;
enum availability_status {
    availability_status_accepted = 0,
    availability_status_rejected,
    availability_status_scheduled
} ;

extern char* availability_type_values[] ;
enum availability_type {
    availability_type_inoperative = 0,
    availability_type_operative
} ;

extern char* cancel_reservation_status_values[] ;
enum cancel_reservation_status {
    cancel_reservation_status_accepted = 0,
    cancel_reservation_status_rejected
} ;

extern char* charge_point_error_code_values[] ;
enum charge_point_error_code {
    charge_point_error_code_connector_lock_failure = 0,
    charge_point_error_code_ev_communication_error,
    charge_point_error_code_ground_failure,
    charge_point_error_code_high_temperature,
    charge_point_error_code_internal_error,
    charge_point_error_code_local_list_conflict,
    charge_point_error_code_no_error,
    charge_point_error_code_other_error,
    charge_point_error_code_over_current_failure,
    charge_point_error_code_over_voltage,
    charge_point_error_code_power_meter_failure,
    charge_point_error_code_power_switch_failure,
    charge_point_error_code_reader_failure,
    charge_point_error_code_reset_failure,
    charge_point_error_code_under_voltage,
    charge_point_error_code_weak_signal
} ;

extern char* charge_point_status_values[] ;
enum charge_point_status {
    charge_point_status_available = 0,
    charge_point_status_preparing,
    charge_point_status_charging,
    charge_point_status_suspended_evse,
    charge_point_status_suspended_ev,
    charge_point_status_finishing,
    charge_point_status_reserved,
    charge_point_status_unavailable,
    charge_point_status_faulted
} ;

extern char* charging_profile_kind_type_values[] ;
enum charging_profile_kind_type {
    charging_profile_kind_type_absolute = 0,
    charging_profile_kind_type_recurring,
    charging_profile_kind_type_relative
} ;

extern char* charging_profile_purpose_type_values[] ;
enum charging_profile_purpose_type {
    charging_profile_purpose_type_charge_point_max_profile = 0,
    charging_profile_purpose_type_tx_default_profile,
    charging_profile_purpose_type_tx_profile
} ;

extern char* charging_profile_status_values[] ;
enum charging_profile_status {
    charging_profile_status_accepted = 0,
    charging_profile_status_rejected,
    charging_profile_status_not_supported
} ;

extern char* charging_rate_unit_type_values[] ;
enum charging_rate_unit_type {
    charging_rate_unit_type_w = 0,
    charging_rate_unit_type_a
} ;

extern char* clear_cache_status_values[] ;
enum clear_cache_status {
    clear_cache_status_accepted = 0,
    clear_cache_status_rejected
} ;

extern char* clear_charging_profile_status_values[] ;
enum clear_charging_profile_status {
    clear_charging_profile_status_accepted = 0,
    clear_charging_profile_status_unknown
} ;

extern char* configuration_status_values[] ;
enum configuration_status {
    configuration_status_accepted = 0,
    configuration_status_rejected,
    configuration_status_reboot_required,
    configuration_status_not_supported
} ;

extern char* data_transfer_status_values[] ;
enum data_transfer_status {
    data_transfer_status_accepted = 0,
    data_transfer_status_rejected,
    data_transfer_status_unknown_message_id,
    data_transfer_status_unknown_vendor_id
} ;

extern char* diagnostics_status_values[] ;
enum diagnostics_status {
    diagnostics_status_idle = 0,
    diagnostics_status_uploaded,
    diagnostics_status_upload_failed,
    diagnostics_status_uploading
} ;

extern char* firmware_status_values[] ;
enum firmware_status {
    firmware_status_downloaded = 0,
    firmware_status_download_failed,
    firmware_status_downloading,
    firmware_status_idle,
    firmware_status_installation_failed,
    firmware_status_installing,
    firmware_status_installed
} ;

extern char* get_composite_schedule_status_values[] ;
enum get_composite_schedule_status {
    get_composite_schedule_status_accepted = 0,
    get_composite_schedule_status_rejected
} ;

extern char* location_values[] ;
enum location {
    location_body = 0,
    location_cable,
    location_ev,
    location_inlet,
    location_outlet
} ;

extern char* measurand_values[] ;
enum measurand {
    measurand_current_export = 0,
    measurand_current_import,
    measurand_current_offered,
    measurand_energy_active_export_register,
    measurand_energy_active_import_register,
    measurand_energy_reactive_export_register,
    measurand_energy_reactive_import_register,
    measurand_energy_active_export_interval,
    measurand_energy_active_import_interval,
    measurand_energy_reactive_export_interval,
    measurand_energy_reactive_import_interval,
    measurand_frequency,
    measurand_power_active_export,
    measurand_power_active_import,
    measurand_power_factor,
    measurand_power_offered,
    measurand_power_reactive_export,
    measurand_power_reactive_import,
    measurand_rpm,
    measurand_soc,
    measurand_temperature,
    measurand_voltage
} ;

extern char* message_trigger_values[] ;
enum message_trigger {
    message_trigger_boot_notification = 0,
    message_trigger_diagnostics_status_notification,
    message_trigger_firmware_status_notification,
    message_trigger_heartbeat,
    message_trigger_meter_values,
    message_trigger_status_notification
} ;

extern char* phase_values[] ;
enum phase {
    phase_L1 = 0,
    phase_L2,
    phase_L3,
    phase_N,
    phase_L1_N,
    phase_L2_N,
    phase_L3_N,
    phase_L1_L2,
    phase_L2_L3,
    phase_L3_L1
} ;

extern char* reading_context_values[] ;
enum reading_context {
    reading_context_interruption_begin = 0,
    reading_context_interruption_end,
    reading_context_other,
    reading_context_sample_clock,
    reading_context_sample_periodic,
    reading_context_transaction_begin,
    reading_context_transaction_end,
    reading_context_trigger
} ;

extern char* reason_values[] ;
enum reason {
    reason_deauthorized = 0,
    reason_emergency_stop,
    reason_ev_disconnected,
    reason_hard_reset,
    reason_local,
    reason_other,
    reason_power_loss,
    reason_reboot,
    reason_remote,
    reason_soft_reset,
    reason_unlock_command
} ;

extern char* recurrency_kind_type_values[] ;
enum recurrency_kind_type {
    recurrency_kind_type_daily = 0,
    recurrency_kind_type_weekly
} ;

extern char* registration_status_values[] ;
enum registration_status {
    registration_status_accepted = 0,
    registration_status_pending,
    registration_status_rejected
} ;

extern char* remote_start_stop_status_values[] ;
enum remote_start_stop_status {
    remote_start_stop_status_accepted = 0,
    remote_start_stop_status_rejected
} ;

extern char* reservation_status_values[] ;
enum reservation_status {
    reservation_status_accepted = 0,
    reservation_status_faulted,
    reservation_status_occupied,
    reservation_status_rejected,
    reservation_status_unavasilable
} ;

extern char* reset_status_values[] ;
enum reset_status {
    reset_status_accepted = 0,
    reset_status_rejected
} ;

extern char* reset_type_values[] ;
enum reset_type {
    reset_type_hard = 0,
    reset_type_soft
} ;

extern char* trigger_message_status_values[] ;
enum trigger_message_status {
    trigger_message_status_accepted = 0,
    trigger_message_status_rejected,
    trigger_message_status_not_implemented
} ;

extern char* unit_of_measure_values[] ;
enum unit_of_measure {
    unit_of_measure_Wh = 0,
    unit_of_measure_kWh,
    unit_of_measure_varh,
    unit_of_measure_kvarh,
    unit_of_measure_W,
    unit_of_measure_kW,
    unit_of_measure_VA,
    unit_of_measure_kVA,
    unit_of_measure_var,
    unit_of_measure_kvar,
    unit_of_measure_A,
    unit_of_measure_V,
    unit_of_measure_celsius,
    unit_of_measure_fahrenheit,
    unit_of_measure_K,
    unit_of_measure_percent
} ;

extern char* unlock_status_values[] ;
enum unlock_status {
    unlock_status_unlocked = 0,
    unlock_status_unlock_failed,
    unlock_status_not_supported
} ;

extern char* update_status_values[] ;
enum update_status {
    update_status_accepted = 0,
    update_status_failed,
    update_status_not_supported,
    update_status_version_mismatch
} ;

extern char* update_type_values[] ;
enum update_type {
    update_type_differential = 0,
    update_type_full
} ;

extern char* value_format_values[] ;
enum value_format {
    value_format_raw = 0,
    value_format_signed_data
};


#endif