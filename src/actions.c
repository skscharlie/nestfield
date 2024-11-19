#include <stdio.h>
#include "ocpp.h"

receive_req_actions central_system_initiated_actions[] = {
    {"CancelReservation", do_cancel_reservation},
    {"ChangeAvailability", do_change_availability},
    {"ChangeConfiguration", do_change_configuration},
    {"ClearCache", do_clear_cache},
    {"ClearChargingProfile", do_clear_charging_profile},
    {"DataTransfer", do_data_transfer},
    {"GetCompositeSchedule", do_get_composite_schedule},
    {"GetConfiguration", do_get_configuration},
    {"GetDiagnostics", do_get_diagnostics},
    {"GetLocalListVersion", do_get_local_list_version},
    {"RemoteStartTransaction", do_remote_start_transaction},
    {"RemoteStopTransaction", do_remote_stop_transaction},
    {"ReserveNow", do_reserve_now},
    {"Reset", do_reset},
    {"SendLocalList", do_send_local_list},
    {"SetChargingProfile", do_set_charging_profile},
    {"TriggerMessage", do_trigger_message},
    {"UnlockConnectoer", do_unlock_connector},
    {"UpdateFirmware", do_update_firmware}
} ;
int central_system_initiated_actions_length = (sizeof(central_system_initiated_actions)) / sizeof(receive_req_actions) ;

send_req_actions charge_point_initiated_actions[] = {
    {"Authorize", do_authorize_req, do_authorize_conf, do_authorize_conf_error}, 
    {"BootNotification", do_boot_notification_req, do_boot_notification_conf, do_boot_notification_error},
    {"DataTransfer", do_data_transfer_req, do_data_transfer_conf, do_data_transfer_error},
    {"DiagnosticsStatusNotification", do_diagnostics_status_notification_req, do_diagnostics_status_notification_conf, do_diagnostics_status_notification_error},
    {"FirmwareStatusNotification", do_firmware_status_notification_req, do_firmware_status_notification_conf, do_firmware_status_notification_error},
    {"Heartbeat", do_heartbeat_req, do_heartbeat_conf, do_heartbeat_error},
    {"MeterValues", do_meter_values_req, do_meter_values_conf, do_meter_values_error},
    {"StartTransaction", do_start_transaction_req, do_start_transaction_conf, do_start_transaction_error},
    {"StatusNotification", do_status_notification_req, do_status_notification_conf, do_status_notification_error},
    {"StopTransaction", do_stop_transaction_req, do_stop_transaction_conf, do_stop_transaction_error}
} ;
int charge_point_initiated_actions_length = (sizeof(charge_point_initiated_actions)) / sizeof(send_req_actions) ;

conf_actions conf_act ;

secc_ocpp_actions so_actions[] = {
    {SECC_EV_CONNECTED, 3, {"StatusNotification", "StatusNotification", "StatusNotification", NULL}},
    {SECC_STATUS_NOTIFICATION, 1, {"StautsNotification", NULL}},
    {SECC_AUTHORIZE, 2, {"StatusNotification", "Authorize", NULL}},
    {SECC_START_TRANSACTION, 2, {"StatusNotification", "StartTransaction", NULL}},
    {SECC_STOP_TRANSACTION, 2, {"StatusNotification", "StopTransaction", NULL}},
    {SECC_EV_DISCONNECTED, 1, {"StatusNotification", NULL}}
} ;






