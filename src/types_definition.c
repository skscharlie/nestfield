#include "ocpp.h"

/*
 * Message field names
 */
char* authorization_req_field_names[] = {"idTag"} ;
char* authorization_conf_field_names[] = {"idTagInfo"} ;

char* boot_notification_req_field_names[] = {"chargeBoxSerialNumber", "chargePointModel", "chargePointSerialNumber", "chargePointVender",
                                             "firmwareVersion", "iccid", "imsi", "meterSerialNumber", "meterType"} ;
char* boot_notification_conf_field_names[] = {"currentTime", "interval", "status"} ;

char* cancel_reservation_req_field_names[] = {"reservationId"} ;
char* cancel_reservation_conf_field_names[] = {"status"} ;

char* change_availability_req_field_names[] = {"connectorId", "type"} ;
char* change_availability_conf_field_names[] = {"status"} ;

char* change_configuration_req_field_names[] = {"key", "value"} ;
char* change_configuration_conf_field_names[] = {"status"} ;

char* clear_cache_conf_field_names[] = {"status"} ;

char* clear_charging_profile_req_field_names[] = {"id", "connectorId", "chargingProfilePurpose", "stackLevel"} ;
char* clear_charging_profile_conf_field_names[] = {"status"} ;

char* data_transfer_req_field_names[] = {"vendorId", "messageId", "data"} ;
char* data_transfer_conf_field_names[] = {"status", "data"} ;

char* diagnostics_status_notification_req_field_name[] = {"status"} ;

char* firmware_status_notification_req_field_name[] = {"status"} ;

char* get_composite_schedule_req_field_names[] = {"connectorId", "duration", "chargingRateUnit"} ;
char* get_composite_schedule_conf_field_names[] = {"status", "connectorId", "scheduleStart", "chargingSchedule"} ;

char* get_configuration_req_field_name[] = {"key"} ;
char* get_configuration_conf_field_names[] = {"configurationKey", "unknownKey"} ;

char* get_diagnostics_req_field_names[] = {"location", "retries", "retryInterval", "startTime", "stopTime"} ;
char* get_diagnostics_conf_field_name[] = {"fileName"} ;

char* get_local_list_version_conf_field_name[] = {"listVersion"} ;

char* heartbeat_conf_field_name[] = {"currentTime"} ;

char* meter_values_req_field_names[] = {"connectorId", "transactionId", "meterValue"} ;

char* remote_start_transaction_req_field_names[] = {"connectorId", "idTag", "chargingProfile"} ;
char* remote_start_transaction_conf_field_name[] = {"status"} ;

char* remote_stop_transaction_req_field_name[] = {"transactionId"} ;
char* remote_stop_transaction_conf_field_name[] = {"status"} ;

char* reserve_now_req_field_names[] = {"connectorId", "expiryDate", "idTag", "parentIdTag", "reservationId"} ;
char* reserve_now_conf_field_name[] = {"status"} ;

char* reset_req_field_name[] = {"type"} ;
char* reset_conf_field_name[] = {"status"} ;

char* send_local_list_req_field_names[] = {"listVersion", "localAuthorizationList", "updateType"} ;
char* send_local_list_conf_field_name[] = {"status"} ;

char* set_charging_profile_req_field_names[] = {"connectorId", "csChargingProfile"} ;
char* set_charging_profile_conf_field_name[] = {"status"} ;

char* start_transaction_req_field_names[] = {"connectorId", "idTag", "meterStart", "reservationId", "timestamp"} ;
char* start_transaction_conf_field_names[] = {"idTagInfo", "transactionId"} ;

char* status_notification_req_field_names[] = {"connectorId", "errorCode", "info", "status", "timestamp", "vendorId", "vendorErrorCode"} ;

char* stop_transaction_req_field_names[] = {"idTag", "meterStop", "timestamp", "transactionId", "reason", "transactionData"} ;
char* stop_transaction_conf_field_name[] = {"idTagInfo"} ;

char* trigger_message_req_field_names[] = {"requestedMessage", "connectorId"} ;
char* trigger_message_conf_field_name[] = {"status"} ;

char* unlock_connector_req_field_name[] = {"connectorId"} ;
char* unlock_connector_conf_field_name[] = {"status"} ;

char* update_firmware_req_field_names[] = {"location", "retries", "retrieve_date", "retry_interval"} ;

/*
 * Class field name
 */
char* authorization_data_field_names[] = {"idTag", "idTagInfo"} ;
char* charging_profile_field_names[] = {"chargingProfileId", "transactionId", "stackLevel", "chargingProfilePurpose", "chargingProfileKind",
                                        "recurrencyKind", "validFrom", "validTo", "chargingSchedule"} ;
char* charging_schedule_field_names[] = {"duration", "startSchedule", "chargingRateUnit", "chargingSchedulePeriod", "minChargingRate"} ;
char* charging_schedule_period_field_names[] = {"startPeriod", "limit", "numberPhases"} ;
char* id_tag_info_field_names[] = {"expiryDate", "parentIdTag", "status"} ;
char* key_value_field_names[] = {"key", "readonly", "value"} ;
char* meter_value_field_names[] = {"timestamp", "sampledValue"} ;
char* sampled_value_field_names[] = {"value", "context", "format", "measurand", "phase", "location", "unit"} ;

/*
 * Enumeration value
 */
char* authorization_status_values[] = {"Accpted", "Blocked", "Expired", "Invalid", "ConcurrentTx"} ;
char* availability_status_values[] = {"Accepted", "Rejected", "Scheduled"} ;
char* availability_type_values[] = {"Inoperative", "Operative"} ;
char* cancel_reservation_status_values[] = {"Accepted", "Rejected"} ;
char* charge_point_error_code_values[] = {"ConnectorLockFailure", "EVCommunicationError", "GroundFailure", "HighTemperature", "InternalError",
                                         "LocalListConflict", "NoError", "OtherError", "OverCurrentFailure", "OverVoltage", "PowerMeterFailure",
                                         "PowerSwitchFailure", "ReaderFailure", "ResetFailure", "UnderVoltage", "WeakSignal"} ;
char* charge_point_status_values[] = {"Available", "Preparing", "Charging", "SuspendedEVSE", "SuspendedEV", "Finishing", "Reserved", "Unavailable", "Faulted"} ;
char* charging_profile_kind_type_values[] = {"Absolute", "Recurring", "Relative"} ;
char* charging_profile_purpose_type_values[] = {"ChargePointMaxProfile", "TxDefaultProfile", "TxProfile"} ;
char* charging_profile_status_values[] = {"Accepted", "Rejected", "NotSupported"} ;
char* charging_rate_unit_type_values[] = {"W", "A"} ;
char* clear_cache_status_values[] = {"Accepted", "Rejected"} ;
char* clear_charging_profile_status_values[] = {"Accepted", "Unkonwn"} ;
char* configuration_status_values[] = {"Accepted", "Rejected", "RebootRequired", "NotSupported"} ;
char* data_transfer_status_values[] = {"Accepted", "Rejected", "UnkonwnMessageId", "UnknownVendorId"} ;
char* diagnostics_status_values[] = {"Idle", "Uploaded", "UploadFailed", "Uploading"} ;
char* firmware_status_values[] = {"Downloaded", "DownloadFailed", "Downloading", "Idle", "InstallationFailed", "Installing", "Installed"} ;
char* get_composite_schedule_status_values[] = {"Accepted", "Rejected"} ;
char* location_values[] = {"Body", "Cable", "EV", "Inlet", "Outlet"} ;
char* measurand_values[] = {"Current.Export", "Current.Import", "Current.Offered", "Energy.Active.Export.Register", "Energy.Active.Import.Register",
                            "Energy.Reactive.Export.Register", "Energy.Reactive.Import.Register", "Energy.Active.Export.Interval", 
                            "Energy.Active.Import.Interval", "Energy.Reactive.Export.Interval", "Energy.Reactive.Import.Interval",
                            "Frequency", "Power.Active.Export", "Power.Active.Export", "Power.Factor", "Power.Offered",
                            "Power.Reactive.Export", "Power.Reactive.Import", "RPM", "SoC", "Temperature", "Voltage"} ;
char* message_trigger_values[] = {"BootNotification", "diagnosticsStatusNotification", "FirmwareStatusNotification", "Heartbeat",
                                  "MeterValues", "StatusNotification"} ;
char* phase_values[] = {"L1", "L2", "L3", "N", "L1-N", "L2-N", "L3-N", "L1-L2", "L2-L3", "L3-L1"} ;
char* reading_context_values[] = {"Interruption.Begin", "Interruption.End", "Other", "Sample.Clock", "Sample.Periodic", "Transaction.Begin", "Transaction.End", "Trigger"} ;
char* reason_values[] = {"DeAuthorized", "EmergencyStop", "EVDisconnected", "HardReset", "Local", "Other", "PowerLoss", "Reboot", "Remote", "SoftReset", "UnlockCommand"} ;
char* recurrency_kind_type_values[] = {"Daily", "Weekly"} ;
char* registration_status_values[] = {"Accepted", "Pending", "Rejected"} ;
char* remote_start_stop_status_values[] = {"Accepted", "Rejected"} ;
char* reservation_status_values[] = {"Accepted", "Faulted", "Occupied", "Rejected", "Unavailable"} ;
char* reset_status_values[] = {"Accepted", "Rejected"} ;
char* reset_type_values[] = {"Hard", "Soft"} ;
char* trigger_message_status_values[] = {"Accepted", "Rejected", "NotImplemented"} ;
char* unit_of_measure_values[] = {"Wh", "kWh", "varh", "kvarh", "W", "kW", "VA", "kVA", "var", "kvar", "A", "V", "Celsius", "Fahrenheit", "K", "Percent"} ;
char* unlock_status_values[] = {"Unlocked", "UnlockFailed", "NotSupported"} ;
char* update_status_values[] = {"Accepted", "Failed", "NotSupported", "VersionMismatch"} ;
char* update_type_values[] = {"Differential", "Full"} ;
char* value_format_values[] = {"Raw", "SignedData"} ;
