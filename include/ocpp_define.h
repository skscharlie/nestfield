#ifndef OCPP_DEFINE_H
#define OCPP_DEFINE_H

/*
 * Message Type Definition
 */
#define MESSAGE_TYPE_CALL           2
#define MESSAGE_TYPE_CALLRESULT     3
#define MESSAGE_TYPE_CALLERROR      4

/*
 * Data Length Definition
*/
#define MESSAGE_ID_LENGTH           36
#define STRING_20_TYPE_LENGTH       20
#define STRING_25_TYPE_LENGTH       25
#define STRING_50_TYPE_LENGTH       50
#define STRING_255_TYPE_LENGTH      255
#define STRING_500_TYPE_LENGTH      500

#define DATE_TIME_LENGTH            19          //yyyy-mm-dd hh:MM:ss
#define MAX_STATUS_LENGTH           32

/*
 * Data Type Definition
 */
#define String(a, n)            char a[n]         
#define CiString(a, n)          char a[n]
#define CiString20Type(a)       char a[STRING_20_TYPE_LENGTH + 1]  
#define CiString25Type(a)       char a[STRING_25_TYPE_LENGTH + 1]
#define CiString50Type(a)       char a[STRING_50_TYPE_LENGTH + 1]
#define CiString255Type(a)      char a[STRING_255_TYPE_LENGTH + 1]
#define CiString500Type(a)      char a[STRING_500_TYPE_LENGTH + 1]

#define IdToken(a)              CiString20Type(a)

#define CANCEL_RESERVATION_INDEX                    0
#define CHANGE_AVAILABILITY_INDEX                   1
#define CHANGE_CONFIGURATION_INDEX                  2
#define CLEAR_CACHE_INDEX                           3
#define CLEAR_CHARGING_PROFILE_INDEX                4
#define CENTRAL_INITIATED_DATA_TRANSFER_INDEX       5
#define GET_COMPOSITE_SCHEDULE_INDEX                6
#define GET_CONFIGURATION_INDEX                     7
#define GET_DIAGNOSTICS_INDEX                       8
#define GET_LOCAL_LIST_VERSION_INDEX                9
#define REMOTE_START_TRANSACTION_INDEX              10
#define REMOTE_STOP_TRANSACTION_INDEX               11
#define RESERVE_NOW_INDEX                           12
#define RESET_INDEX                                 13
#define SEND_LOCAL_LIST_INDEX                       14
#define SET_CHARGING_PROFILE_INDEX                  15
#define TRIGGER_MESSAGE_INDEX                       16
#define UNLOCK_CONNECTOR_INDEX                      17
#define UPDATE_FIRMWARE_INDEX                       18

#define AUTHORIZE_INDEX                             0
#define BOOT_NOTIFICATION_INDEX                     1
#define CHARGE_POINT_INITIATED_DATA_TRANSFER_INDEX  2
#define DIAGNOSTICS_STATUS_NOTIFICATION_INDEX       3
#define FIRMWARE_STATUS_NOTIFICATION_INDEX          4
#define HEARTBEAT_INDEX                             5
#define METER_VALUES_INDEX                          6
#define START_TRANSACTION_INDEX                     7
#define STATUS_NOTIFICATION_INDEX                   8
#define STOP_TRANSACTION_INDEX                      9

#define SECC_COMM_PORT                  13001
#endif