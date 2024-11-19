#ifndef OCPP_EXTERN_H
#define OCPP_EXTERN_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <libwebsockets.h>
#include "ocpp.h"

extern pthread_mutex_t terminal_input_mutex, secc_mutex, ocpp_mutex ;
extern char shared_data[4096] ;
extern bool terminal_input_valid, secc_data_valid, ocpp_comm_end, secc_comm_end ;

extern user_data user_data_buffer ;

extern conf_actions conf_act ;

extern authorize_req auth_req ;
extern char ac_id_tag[] ;

extern authorize_conf auth_conf ;
id_tag_info id_tag_inf ;
char iti_expiry_date[DATE_TIME_LENGTH + 1] ;
char iti_parent_id_tag[STRING_20_TYPE_LENGTH + 1] ;
char iti_status[STRING_20_TYPE_LENGTH + 1] ;


extern boot_notification_req boot_noti_req ;
extern char bnr_charge_box_serial_number[STRING_25_TYPE_LENGTH + 1] ;
extern char bnr_charge_point_motel[STRING_20_TYPE_LENGTH + 1] ;
extern char bnr_charge_point_serial_number[STRING_25_TYPE_LENGTH + 1] ;
extern char bnr_charge_point_vendor[STRING_20_TYPE_LENGTH + 1] ;
extern char bnr_firmaware_version[STRING_50_TYPE_LENGTH + 1] ;
extern char bnr_iccid[STRING_20_TYPE_LENGTH + 1] ;
extern char bnr_imsi[STRING_20_TYPE_LENGTH + 1] ;
extern char bnr_meter_serial_number[STRING_25_TYPE_LENGTH + 1] ;
extern char bnr_meter_type[STRING_25_TYPE_LENGTH + 1] ;

extern boot_notification_conf boot_noti_conf ;
extern char bnc_current_time[DATE_TIME_LENGTH + 1] ;
extern char bnc_status[STRING_20_TYPE_LENGTH + 1] ;

extern cancel_reservation_req cancel_res_req ;
extern cancel_reservation_conf cancel_res_conf ;
extern char crc_status[STRING_20_TYPE_LENGTH + 1] ;

extern change_availability_req change_avail_req ;
extern char car_type[STRING_20_TYPE_LENGTH + 1] ;

extern change_availability_conf change_avail_conf ;
extern char cac_status[STRING_20_TYPE_LENGTH + 1] ;

extern change_configuration_req change_config_req ;
extern char ccr_key[STRING_50_TYPE_LENGTH + 1] ;
extern char ccr_value[STRING_500_TYPE_LENGTH + 1] ;

extern change_configuration_conf change_config_conf ;
extern char ccc_status[STRING_20_TYPE_LENGTH + 1] ;

extern receive_req_actions central_system_initiated_actions[] ;
extern int central_system_initiated_actions_length ;
extern send_req_actions charge_point_initiated_actions[] ;
extern int charge_point_initiated_actions_length ;

extern clear_cache_req clear_cac_req ;

extern clear_cache_conf clear_cac_conf ;
extern char ccac_status[STRING_20_TYPE_LENGTH + 1] ;

extern clear_charging_profile_req clear_chg_prof_req ;
extern char ccpr_charging_profile_purpose[STRING_25_TYPE_LENGTH + 1] ;

extern clear_charging_profile_conf clear_chg_prof_conf ;
extern char ccpc_status[STRING_20_TYPE_LENGTH + 1] ;

extern data_transfer_req data_trans_req ;
extern char dtr_vendor_id[STRING_255_TYPE_LENGTH + 1] ;
extern char dtr_message_id[STRING_50_TYPE_LENGTH + 1] ;

extern data_transfer_conf data_trans_conf ;
extern char dtc_status[STRING_20_TYPE_LENGTH + 1] ;

extern diagnostics_status_notification_req diagnostics_stat_noti_req ;
extern char dsnr_status[STRING_20_TYPE_LENGTH + 1] ;

extern diagnostics_status_notifidation_conf diagnostics_stat_noti_conf ;

extern firmware_status_notification_req firmware_stat_noti_req ;
extern char fsnr_status[STRING_20_TYPE_LENGTH + 1] ;

extern firmware_status_notification_conf firmware_stat_noti_conf ;

extern get_composite_schedule_req get_comp_sche_req ;
extern char gcsr_charging_rate_unit[STRING_20_TYPE_LENGTH + 1] ;

extern get_composite_schedule_conf get_comp_sche_conf ;
extern char gcsc_status[STRING_20_TYPE_LENGTH + 1] ;
extern char gcsc_schedule_start[DATE_TIME_LENGTH + 1] ;
extern charging_schedule charging_sched ;
extern char cs_start_schedule[DATE_TIME_LENGTH + 1] ;
extern char cs_charging_rate_unit[STRING_20_TYPE_LENGTH + 1] ;
extern charging_schedule_period charging_sched_period ;

extern get_configuration_req get_config_req ;
extern get_configuration_conf get_config_conf ;

extern get_diagnostics_req get_diag_req ;
extern char gdr_location[STRING_255_TYPE_LENGTH + 1] ;
extern char gdr_start_time[DATE_TIME_LENGTH + 1] ;
extern char gdr_stop_time[DATE_TIME_LENGTH + 1] ;
extern get_diagnostics_conf get_diag_conf ;
extern char gdc_file_name[STRING_50_TYPE_LENGTH + 1] ;

extern get_local_list_version_req get_ll_version_req ;
extern get_local_list_version_conf get_ll_version_conf ;

extern heartbeat_req  hbeat_req ;
extern heartbeat_conf hbeat_conf ;
extern char hc_current_time[DATE_TIME_LENGTH + 1] ;

extern meter_values_req meter_val_req ;
extern meter_value meter_val ;
extern char mv_timestamp[DATE_TIME_LENGTH + 1] ;
extern sampled_value sampled_val ;
extern char sv_value[STRING_20_TYPE_LENGTH + 1] ;
extern char sv_context[STRING_20_TYPE_LENGTH + 1] ;
extern char sv_format[STRING_20_TYPE_LENGTH + 1] ;
extern char sv_measurand[STRING_50_TYPE_LENGTH + 1] ;
extern char sv_phase[STRING_20_TYPE_LENGTH + 1] ;
extern char sv_location[STRING_20_TYPE_LENGTH + 1] ;
extern char sv_unit[STRING_20_TYPE_LENGTH + 1] ;
extern meter_values_conf meter_val_conf ;

extern remote_start_transaction_req remote_start_trans_req ;
extern char rstr_id_tag[STRING_20_TYPE_LENGTH + 1] ;
extern charging_profile charging_prof ;
extern char cp_charging_profile_purpose[STRING_25_TYPE_LENGTH + 1] ;
extern char cp_charging_profile_kind[STRING_20_TYPE_LENGTH + 1] ;
extern char cp_recurrency_kind[STRING_20_TYPE_LENGTH + 1] ;
extern char cp_valid_from[DATE_TIME_LENGTH + 1] ;
extern char cp_valid_to[DATE_TIME_LENGTH + 1] ;

extern remote_start_transaction_conf remote_start_trans_conf ;
extern char rstc_status[STRING_20_TYPE_LENGTH + 1] ;

extern remote_stop_transaction_req remote_stop_trans_req ;
extern remote_stop_transaction_conf remote_stop_trans_conf ;

extern reserve_now_req reserve_n_req ;
extern char rnr_expiry_date[DATE_TIME_LENGTH + 1] ;
extern char rnr_id_tag[STRING_20_TYPE_LENGTH + 1] ;
extern char rnr_parent_id_tag[STRING_20_TYPE_LENGTH + 1] ;
extern reserve_now_conf reserve_n_conf ;
extern char nrc_status[STRING_20_TYPE_LENGTH + 1] ;

extern reset_req rset_req ;
extern char rr_type[STRING_20_TYPE_LENGTH + 1] ;
extern reset_conf rset_conf ;
extern char rc_status[STRING_20_TYPE_LENGTH + 1] ;

extern send_local_list_req send_local_lst_req ;
extern char sllr_update_type[STRING_20_TYPE_LENGTH + 1] ;
extern send_local_list_conf send_local_lst_conf ;
extern char sllc_status[STRING_20_TYPE_LENGTH + 1] ;

extern set_charging_profile_req set_charging_prof_req ;
extern set_charging_profile_conf set_charging_prof_conf ;
extern char scpc_status[STRING_20_TYPE_LENGTH + 1] ;

extern start_transaction_req start_trans_req ;
extern char str_id_tag[STRING_20_TYPE_LENGTH + 1] ;
extern char str_timestamp[DATE_TIME_LENGTH + 1] ;
extern start_transaction_conf start_trans_conf ;

extern status_notification_req status_noti_req ;
extern char snr_error_code[STRING_25_TYPE_LENGTH + 1] ;
extern char snr_info[STRING_50_TYPE_LENGTH + 1] ;
extern char snr_status[STRING_20_TYPE_LENGTH + 1] ;
extern char snr_timestamp[DATE_TIME_LENGTH + 1] ;
extern char snr_vendor_id[STRING_255_TYPE_LENGTH + 1] ;
extern char snr_vendor_error_code[STRING_50_TYPE_LENGTH + 1] ;

extern stop_transaction_req stop_trans_req ;
extern char str_reason[STRING_20_TYPE_LENGTH + 1] ;
extern stop_transaction_conf stop_trans_conf ;

extern trigger_message_req trigger_msg_req ;
extern char tmr_requested_message[STRING_50_TYPE_LENGTH + 1] ;
extern trigger_message_conf trigger_msg_conf ;
extern char tmc_status[STRING_20_TYPE_LENGTH + 1] ;

extern unlock_connector_req unlock_con_req ;
extern unlock_connector_conf unlock_con_conf ;
extern char ucc_status[STRING_20_TYPE_LENGTH + 1] ;

extern update_firmware_req update_fw_req ;
extern char ufr_location[STRING_255_TYPE_LENGTH + 1] ;
extern char ufr_retrieve_date[DATE_TIME_LENGTH + 1] ;


extern int make_message_id(char *id) ;
extern int make_transaction_id() ;
extern int get_future_date(char *buf, int day) ;
extern void make_ci20_type_string(char *buf) ;
extern void make_ci25_type_string(char *buf) ;
extern void make_ci50_type_string(char *buf) ;
extern void make_ci255_type_string(char *buf) ;
extern void make_ci500_type_string(char *buf) ;


extern int parse_req_message(char *data, ocpp_call_message *msg) ;
extern int parse_conf_message(char *data, ocpp_callresult_message *msg) ;

extern void init_authorize_req_message() ;
extern void init_authorize_conf_message() ;
extern int make_ocpp_authorize_req_message(char *buf, char *message_id, char *id_tag_val) ;
extern int make_ocpp_authorize_conf_message(char *buf, char *message_ie, raw_id_tag_info *rinfo) ;
extern int parse_ocpp_authorize_req_message(char *data) ;
extern int parse_ocpp_authorize_conf_message(char *data) ;

extern void init_boot_notification_req_message() ;
extern void init_boot_notification_conf_message() ;
extern int make_ocpp_boot_notification_req_message(char* buf, char* message_id, raw_boot_notification_req *rreq) ;
extern int make_ocpp_boot_notification_conf_message(char *buf, char *message_id, raw_boot_notification_conf *rconf) ;
extern int parse_ocpp_boot_notification_req_message(char *data) ;
extern int parse_ocpp_boot_notification_conf_message(char *data) ;

extern void init_cancel_reservation_req_message() ;
extern void init_cancel_reservation_conf_message() ;
extern int make_ocpp_cancel_reservation_req_message(char *buf, char *message_id, int reservation_id) ;
extern int make_ocpp_cancel_reservation_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_cancel_reservation_req_message(char *data) ;
extern int parse_ocpp_cancel_reservation_conf_message(char *data) ;

extern void init_change_availability_req_message() ;
extern void init_change_availability_conf_message() ;
extern int make_ocpp_change_availability_req_message(char *buf, char *message_id, raw_change_availability_req *rreq) ;
extern int make_ocpp_change_availability_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_change_availability_req_message(char *data) ;
extern int parse_ocpp_change_availability_conf_message(char *data) ;

extern void init_change_configuration_req_message() ;
extern void init_change_configuration_conf_message() ;
extern int make_ocpp_change_configuration_req_message(char *buf, char *message_id, raw_change_configuration_req *rreq) ;
extern int make_ocpp_change_configuration_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_change_configuration_req_message(char *data) ;
extern int parse_ocpp_change_configuration_conf_message(char *data) ;

extern void init_clear_cache_req_message() ;
extern void init_clear_cache_conf_message() ;
extern int make_ocpp_clear_cache_req_message(char *buf, char *message_id) ;
extern int make_ocpp_clear_cache_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_clear_cache_req_message(char *data) ;
extern int parse_ocpp_clear_cache_conf_message(char *data) ;

extern void init_clear_charging_profile_req_message() ;
extern void init_clear_charging_profile_conf_message() ;
extern int make_ocpp_clear_charging_profile_req_message(char *buf, char *message_id, raw_clear_charging_profile_req *rreq) ;
extern int make_ocpp_clear_charging_profile_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_clear_charging_profile_req_message(char *data) ;
extern int parse_ocpp_clear_charging_profile_conf_message(char *data) ;

extern void init_data_transfer_req_message() ;
extern void init_data_transfer_conf_message() ;
extern int make_ocpp_data_transfer_req_message(char *buf, char *message_id, raw_data_transfer_req *rreq) ;
extern int make_ocpp_data_transfer_conf_message(char *buf, char *message_id, raw_data_transfer_conf *rconf) ;
extern int parse_ocpp_data_transfer_req_message(char *data) ;
extern int parse_ocpp_data_transfer_conf_message(char *data) ;

extern void init_diagnostics_status_notification_req_message() ;
extern void init_diagnostics_status_notification_conf_message() ;
extern int make_ocpp_diagnostics_status_notification_req_message(char *buf, char *message_id, char *status) ;
extern int make_ocpp_diagnostics_status_notification_conf_message(char *buf, char *message_id) ;
extern int parse_ocpp_diagnostics_status_notification_req_message(char *data) ;
extern int parse_ocpp_diagnostics_status_notification_conf_message(char *data) ;

extern void init_firmware_status_notification_req_message() ;
extern void init_firmware_status_notification_conf_message() ;
extern int make_ocpp_firmware_status_notification_req_message(char *buf, char *message_id, char *status) ;
extern int make_ocpp_firmware_status_notification_conf_message(char *buf, char *message_id) ;
extern int parse_ocpp_firmware_status_notification_req_message(char *data) ;
extern int parse_ocpp_firmware_status_notification_conf_message(char *data) ;


extern void init_get_composite_schedule_req_message() ;
extern void init_get_composite_schedule_conf_message() ;
extern int make_ocpp_get_composite_schedule_req_message(char *buf, char *message_id, raw_get_composite_schedule_req *rreq) ;
extern int make_ocpp_get_composite_schedule_conf_message(char *buf, char *message_id, raw_get_composite_schedule_conf *rconf) ;
extern int parse_ocpp_get_composite_schedule_req_message(char *data) ;
extern int parse_ocpp_get_composite_schedule_conf_message(char *data) ;

extern void init_get_configuration_req_message() ;
extern void init_get_configuration_conf_message() ;
extern int make_ocpp_get_configuration_req_message(char *buf, char *message_id, raw_get_configuration_req *rreq) ;
extern int make_ocpp_get_configuration_conf_message(char *buf, char *message_id, raw_get_configuration_conf *rconf) ;
extern int parse_ocpp_get_configuration_req_message(char *data) ;
extern int parse_ocpp_get_configuration_conf_message(char *data) ;

extern void init_get_diagnostics_req_message() ;
extern void init_get_diagnostics_conf_message() ;
extern int make_ocpp_get_diagnostics_req_message(char *buf, char *message_id, raw_get_diagnostics_req *rreq) ;
extern int make_ocpp_get_diagnostics_conf_message(char *buf, char *message_id, char *filename) ;
extern int parse_ocpp_get_diagnostics_req_message(char *data) ;
extern int parse_ocpp_get_diagnostics_conf_message(char *data) ;

extern void init_get_local_list_version_req_message() ;
extern void init_get_local_list_version_conf_message() ;
extern int make_ocpp_get_local_list_version_req_message(char *buf, char *message_id) ;
extern int make_ocpp_get_local_list_version_conf_message(char *buf, char *message_id, int list_version) ;
extern int parse_ocpp_get_local_list_version_req_message(char *data) ;
extern int parse_ocpp_get_local_list_version_conf_message(char *data) ;

extern void init_heartbeat_req_message() ;
extern void init_heartbeat_conf_message() ;
extern int make_ocpp_heartbeat_req_message(char *buf, char *message_id) ;
extern int make_ocpp_heartbeat_conf_message(char *buf, char *message_id, char *current_time) ;
extern int parse_ocpp_heartbeat_req_message(char *data) ;
extern int parse_ocpp_heartbeat_conf_message(char *data) ;

extern void init_meter_values_req_message() ;
extern void init_meter_values_conf_message() ;
extern int make_ocpp_meter_values_req_message(char *buf, char *message_id, raw_meter_values_req *rreq) ;
extern int make_ocpp_meter_values_conf_message(char *buf, char *message_id) ;
extern int parse_ocpp_meter_values_req_message(char *data) ;
extern int parse_ocpp_meter_values_conf_message(char *data) ;

extern void init_remote_start_transaction_req_message() ;
extern void init_remote_start_transaction_conf_message() ;
extern int make_ocpp_remote_start_transaction_req_message(char *buf, char *message_id, raw_remote_start_transaction_req *rreq) ;
extern int make_ocpp_remote_start_transaction_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_remote_start_transaction_req_message(char *data) ;
extern int parse_ocpp_remote_start_transaction_conf_message(char *data) ;

extern void init_remote_stop_transaction_req_message() ;
extern void init_remote_stop_transaction_conf_message() ;
extern int make_ocpp_remote_stop_transaction_req_message(char *buf, char *message_id, int transaction_id) ;
extern int make_ocpp_remote_stop_transaction_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_remote_stop_transaction_req_message(char *data) ;
extern int parse_ocpp_remote_stop_transaction_conf_message(char *data) ;

extern void init_reserve_now_req_message() ;
extern void init_reserve_now_conf_message() ;
extern int make_ocpp_reserve_now_req_message(char *buf, char *message_id, raw_reserve_now_req *rrq) ;
extern int make_ocpp_reserve_now_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_reserve_now_req_message(char *data) ;
extern int parse_ocpp_reserve_now_conf_message(char *data) ;

extern void init_reset_req_message() ;
extern void init_reset_conf_message() ;
extern int make_ocpp_reset_req_message(char *buf, char *message_id, char *type) ;
extern int make_ocpp_reset_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_reset_req_message(char *data) ;
extern int parse_ocpp_reset_conf_message(char *data) ;

extern void init_send_local_list_req_message() ;
extern void init_send_local_list_conf_message() ;
extern int make_ocpp_send_local_list_req_message(char *buf, char *message_id, raw_send_local_list_req *rreq) ;
extern int make_ocpp_send_local_list_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_send_local_list_req_message(char *data) ;
extern int parse_ocpp_send_local_list_conf_message(char *data) ;

extern void init_set_charging_profile_req_message() ;
extern void init_set_charging_profile_conf_message() ;
extern int make_ocpp_set_charging_profile_req_message(char *buf, char *message_id, raw_set_charging_profile_req *rreq) ;
extern int make_ocpp_set_charging_profile_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_set_charging_profile_req_message(char *data) ;
extern int parse_ocpp_set_charging_profile_conf_message(char *data) ;

extern void init_start_transaction_req_message() ;
extern void init_start_transaction_conf_message() ;
extern int make_ocpp_start_transaction_req_message(char *buf, char *message_id, raw_start_transaction_req *rreq) ;
extern int make_ocpp_start_transaction_conf_message(char *buf, char *message_id, raw_start_transaction_conf *rconf) ;
extern int parse_ocpp_start_transaction_req_message(char *data) ;
extern int parse_ocpp_start_transaction_conf_message(char *data) ;

extern void init_status_notification_req_message() ;
extern void init_status_notification_conf_message() ;
extern int make_ocpp_status_notification_req_message(char *buf, char *message_id, raw_status_notification_req *rreq) ;
extern int make_ocpp_status_notification_conf_message(char *buf, char *message_id) ;
extern int parse_ocpp_status_notification_req_message(char *data) ;
extern int parse_ocpp_status_notification_conf_message(char *data) ;

extern void init_stop_transaction_req_message() ;
extern void init_stop_transaction_conf_message() ;
extern int make_ocpp_stop_transaction_req_message(char *buf, char *message_id, raw_stop_transaction_req *rreq) ;
extern int make_ocpp_stop_transaction_conf_message(char *buf, char *message_id, raw_stop_transaction_conf *rconf) ;
extern int parse_ocpp_stop_transaction_req_message(char *data) ;
extern int parse_ocpp_stop_transaction_conf_message(char *data) ;

extern void init_trigger_message_req_message() ;
extern void init_trigger_message_conf_message() ;
extern int make_ocpp_trigger_message_req_message(char *buf, char *message_id, raw_trigger_message_req *rreq) ;
extern int make_ocpp_trigger_message_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_trigger_message_req_message(char *data) ;
extern int parse_ocpp_trigger_message_conf_message(char *data) ;

extern void init_unlock_connector_req_message() ;
extern void init_unlock_connector_conf_message() ;
extern int make_ocpp_unlock_connector_req_message(char *buf, char *message_id, int connector_id) ;
extern int make_ocpp_unlock_connector_conf_message(char *buf, char *message_id, char *status) ;
extern int parse_ocpp_unlock_connector_req_message(char *data) ;
extern int parse_ocpp_unlock_connector_conf_message(char *data) ;

extern void init_update_firmware_req_message() ;
extern void init_update_firmware_conf_message() ;
extern int make_ocpp_update_firmware_req_message(char *buf, char *message_id, raw_update_firmware_req *rreq) ;
extern int make_ocpp_update_firmware_conf_message(char *buf, char *message_id) ;
extern int parse_ocpp_update_firmware_req_message(char *data) ;
extern int parse_ocpp_update_firmware_conf_message(char *data) ;

extern int get_message_type_id(char *data) ;

/*
 * Operations Initiated by Charge Point
 */
extern int do_authorize_req(char **ppcommand) ;
extern int do_authorize_conf(ocpp_callresult_message *msg) ;
extern int do_authorize_conf_error(ocpp_callerror_message *msg) ;

extern int do_boot_notification_req(char **ppcommand) ;
extern int do_boot_notification_conf(ocpp_callresult_message *msg) ;
extern int do_boot_notification_error(ocpp_callerror_message *msg) ;

extern int do_data_transfer_req(char **ppcommand) ;
extern int do_data_transfer_conf(ocpp_callresult_message *msg) ;
extern int do_data_transfer_error(ocpp_callerror_message *msg) ;

extern int do_diagnostics_status_notification_req(char **ppcommand) ;
extern int do_diagnostics_status_notification_conf(ocpp_callresult_message *msg) ;
extern int do_diagnostics_status_notification_error(ocpp_callerror_message *msg) ;

extern int do_firmware_status_notification_req(char **ppcommand) ;
extern int do_firmware_status_notification_conf(ocpp_callresult_message *msg) ;
extern int do_firmware_status_notification_error(ocpp_callerror_message *msg) ;

extern int do_heartbeat_req(char **ppcommand) ;
extern int do_heartbeat_conf(ocpp_callresult_message *msg) ;
extern int do_heartbeat_error(ocpp_callerror_message *msg) ;

extern int do_meter_values_req(char **ppcommand) ;
extern int do_meter_values_conf(ocpp_callresult_message *msg) ;
extern int do_meter_values_error(ocpp_callerror_message *msg) ;

extern int do_start_transaction_req(char **ppcommand) ;
extern int do_start_transaction_conf(ocpp_callresult_message *msg) ;
extern int do_start_transaction_error(ocpp_callerror_message *msg) ;

extern int do_status_notification_req(char **ppcommand) ;
extern int do_status_notification_conf(ocpp_callresult_message *msg) ;
extern int do_status_notification_error(ocpp_callerror_message *msg) ;

extern int do_stop_transaction_req(char **ppcommand) ;
extern int do_stop_transaction_conf(ocpp_callresult_message *msg) ;
extern int do_stop_transaction_error(ocpp_callerror_message *msg) ;


/*
 * Operations Initiated by Central System
 */
extern int do_cancel_reservation(ocpp_call_message *msg, char *) ;
extern int do_change_availability(ocpp_call_message *msg, char *) ;
extern int do_change_configuration(ocpp_call_message *msg, char *) ;
extern int do_clear_cache(ocpp_call_message *msg, char *) ;
extern int do_clear_charging_profile(ocpp_call_message *msg, char *) ;
extern int do_data_transfer(ocpp_call_message *msg, char *) ;
extern int do_get_composite_schedule(ocpp_call_message *msg, char *) ;
extern int do_get_configuration(ocpp_call_message *msg, char *) ;
extern int do_get_diagnostics(ocpp_call_message *msg, char *) ;
extern int do_get_local_list_version(ocpp_call_message *msg, char *) ;
extern int do_remote_start_transaction(ocpp_call_message *msg, char *) ;
extern int do_remote_stop_transaction(ocpp_call_message *msg, char *) ;
extern int do_reserve_now(ocpp_call_message *msg, char *) ;
extern int do_reset(ocpp_call_message *msg, char *) ;
extern int do_send_local_list(ocpp_call_message *msg, char *) ;
extern int do_set_charging_profile(ocpp_call_message *msg, char *) ;
extern int do_trigger_message(ocpp_call_message *msg, char *) ;
extern int do_unlock_connector(ocpp_call_message *msg, char *) ;
extern int do_update_firmware(ocpp_call_message *msg, char *) ;

extern void process_input_command(char *) ;
extern void process_secc_data(struct ocpp_comm_buff *, struct lws *, struct lws_context *) ;
extern char *trim(char *) ;

#endif