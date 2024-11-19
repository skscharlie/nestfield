#include "ocpp.h"

authorize_req auth_req ;
char ac_id_tag[STRING_20_TYPE_LENGTH + 1] ;

authorize_conf auth_conf ;
id_tag_info id_tag_inf ;
char iti_expiry_date[DATE_TIME_LENGTH + 1] ;
char iti_parent_id_tag[STRING_20_TYPE_LENGTH + 1] ;
char iti_status[STRING_20_TYPE_LENGTH + 1] ;

boot_notification_req boot_noti_req ;
char bnr_charge_box_serial_number[STRING_25_TYPE_LENGTH + 1] ;
char bnr_charge_point_motel[STRING_20_TYPE_LENGTH + 1] ;
char bnr_charge_point_serial_number[STRING_25_TYPE_LENGTH + 1] ;
char bnr_charge_point_vendor[STRING_20_TYPE_LENGTH + 1] ;
char bnr_firmaware_version[STRING_50_TYPE_LENGTH + 1] ;
char bnr_iccid[STRING_20_TYPE_LENGTH + 1] ;
char bnr_imsi[STRING_20_TYPE_LENGTH + 1] ;
char bnr_meter_serial_number[STRING_25_TYPE_LENGTH + 1] ;
char bnr_meter_type[STRING_25_TYPE_LENGTH + 1] ;

boot_notification_conf boot_noti_conf ;
char bnc_current_time[DATE_TIME_LENGTH + 1] ;
char bnc_status[STRING_20_TYPE_LENGTH + 1] ;

cancel_reservation_req cancel_res_req ;

cancel_reservation_conf cancel_res_conf ;
char crc_status[STRING_20_TYPE_LENGTH + 1] ;

change_availability_req change_avail_req ;
char car_type[STRING_20_TYPE_LENGTH + 1] ;

change_availability_conf change_avail_conf ;
char cac_status[STRING_20_TYPE_LENGTH + 1] ;

change_configuration_req change_config_req ;
char ccr_key[STRING_50_TYPE_LENGTH + 1] ;
char ccr_value[STRING_500_TYPE_LENGTH + 1] ;

change_configuration_conf change_config_conf ;
char ccc_status[STRING_20_TYPE_LENGTH + 1] ;

clear_cache_req clear_cac_req ;

clear_cache_conf clear_cac_conf ;
char ccac_status[STRING_20_TYPE_LENGTH + 1] ;

clear_charging_profile_req clear_chg_prof_req ;
char ccpr_charging_profile_purpose[STRING_25_TYPE_LENGTH + 1] ;

clear_charging_profile_conf clear_chg_prof_conf ;
char ccpc_status[STRING_20_TYPE_LENGTH + 1] ;

data_transfer_req data_trans_req ;
char dtr_vendor_id[STRING_255_TYPE_LENGTH + 1] ;
char dtr_message_id[STRING_50_TYPE_LENGTH + 1] ;

data_transfer_conf data_trans_conf ;
char dtc_status[STRING_20_TYPE_LENGTH + 1] ;

diagnostics_status_notification_req diagnostics_stat_noti_req ;
char dsnr_status[STRING_20_TYPE_LENGTH + 1] ;

diagnostics_status_notifidation_conf diagnostics_stat_noti_conf ;

firmware_status_notification_req firmware_stat_noti_req ;
char fsnr_status[STRING_20_TYPE_LENGTH + 1] ;

firmware_status_notification_conf firmware_stat_noti_conf ;

get_composite_schedule_req get_comp_sche_req ;
char gcsr_charging_rate_unit[STRING_20_TYPE_LENGTH + 1] ;

get_composite_schedule_conf get_comp_sche_conf ;
char gcsc_status[STRING_20_TYPE_LENGTH + 1] ;
char gcsc_schedule_start[DATE_TIME_LENGTH + 1] ;
charging_schedule charging_sched ;
char cs_start_schedule[DATE_TIME_LENGTH + 1] ;
char cs_charging_rate_unit[STRING_20_TYPE_LENGTH + 1] ;
charging_schedule_period charging_sched_period ;

get_configuration_req get_config_req ;
get_configuration_conf get_config_conf ;

get_diagnostics_req get_diag_req ;
char gdr_location[STRING_255_TYPE_LENGTH + 1] ;
char gdr_start_time[DATE_TIME_LENGTH + 1] ;
char gdr_stop_time[DATE_TIME_LENGTH + 1] ;
get_diagnostics_conf get_diag_conf ;
char gdc_file_name[STRING_50_TYPE_LENGTH + 1] ;

get_local_list_version_req get_ll_version_req ;
get_local_list_version_conf get_ll_version_conf ;

heartbeat_req  hbeat_req ;
heartbeat_conf hbeat_conf ;
char hc_current_time[DATE_TIME_LENGTH + 1] ;


meter_values_req meter_val_req ;
meter_value meter_val ;
char mv_timestamp[DATE_TIME_LENGTH + 1] ;
sampled_value sampled_val ;
char sv_value[STRING_20_TYPE_LENGTH + 1] ;
char sv_context[STRING_20_TYPE_LENGTH + 1] ;
char sv_format[STRING_20_TYPE_LENGTH + 1] ;
char sv_measurand[STRING_50_TYPE_LENGTH + 1] ;
char sv_phase[STRING_20_TYPE_LENGTH + 1] ;
char sv_location[STRING_20_TYPE_LENGTH + 1] ;
char sv_unit[STRING_20_TYPE_LENGTH + 1] ;
meter_values_conf meter_val_conf ;

remote_start_transaction_req remote_start_trans_req ;
char rstr_id_tag[STRING_20_TYPE_LENGTH + 1] ;
charging_profile charging_prof ;
char cp_charging_profile_purpose[STRING_25_TYPE_LENGTH + 1] ;
char cp_charging_profile_kind[STRING_20_TYPE_LENGTH + 1] ;
char cp_recurrency_kind[STRING_20_TYPE_LENGTH + 1] ;
char cp_valid_from[DATE_TIME_LENGTH + 1] ;
char cp_valid_to[DATE_TIME_LENGTH + 1] ;

remote_start_transaction_conf remote_start_trans_conf ;
char rstc_status[STRING_20_TYPE_LENGTH + 1] ;

remote_stop_transaction_req remote_stop_trans_req ;
remote_stop_transaction_conf remote_stop_trans_conf ;

reserve_now_req reserve_n_req ;
char rnr_expiry_date[DATE_TIME_LENGTH + 1] ;
char rnr_id_tag[STRING_20_TYPE_LENGTH + 1] ;
char rnr_parent_id_tag[STRING_20_TYPE_LENGTH + 1] ;
reserve_now_conf reserve_n_conf ;
char nrc_status[STRING_20_TYPE_LENGTH + 1] ;

reset_req rset_req ;
char rr_type[STRING_20_TYPE_LENGTH + 1] ;
reset_conf rset_conf ;
char rc_status[STRING_20_TYPE_LENGTH + 1] ;

send_local_list_req send_local_lst_req ;
char sllr_update_type[STRING_20_TYPE_LENGTH + 1] ;
send_local_list_conf send_local_lst_conf ;
char sllc_status[STRING_20_TYPE_LENGTH + 1] ;

set_charging_profile_req set_charging_prof_req ;
set_charging_profile_conf set_charging_prof_conf ;
char scpc_status[STRING_20_TYPE_LENGTH + 1] ;

start_transaction_req start_trans_req ;
char str_id_tag[STRING_20_TYPE_LENGTH + 1] ;
char str_timestamp[DATE_TIME_LENGTH + 1] ;
start_transaction_conf start_trans_conf ;

status_notification_req status_noti_req ;
char snr_error_code[STRING_25_TYPE_LENGTH + 1] ;
char snr_info[STRING_50_TYPE_LENGTH + 1] ;
char snr_status[STRING_20_TYPE_LENGTH + 1] ;
char snr_timestamp[DATE_TIME_LENGTH + 1] ;
char snr_vendor_id[STRING_255_TYPE_LENGTH + 1] ;
char snr_vendor_error_code[STRING_50_TYPE_LENGTH + 1] ;

stop_transaction_req stop_trans_req ;
char str_reason[STRING_20_TYPE_LENGTH + 1] ;
stop_transaction_conf stop_trans_conf ;

trigger_message_req trigger_msg_req ;
char tmr_requested_message[STRING_50_TYPE_LENGTH + 1] ;
trigger_message_conf trigger_msg_conf ;
char tmc_status[STRING_20_TYPE_LENGTH + 1] ;

unlock_connector_req unlock_con_req ;
unlock_connector_conf unlock_con_conf ;
char ucc_status[STRING_20_TYPE_LENGTH + 1] ;

update_firmware_req update_fw_req ;
char ufr_location[STRING_255_TYPE_LENGTH + 1] ;
char ufr_retrieve_date[DATE_TIME_LENGTH + 1] ;
