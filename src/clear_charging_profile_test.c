#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

int proc_clear_charging_profile_req(char *req, char *resp) ;

int clear_charging_profile_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_clear_charging_profile_req rreq ;
    char charging_profile_purpose_buf[STRING_25_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;
    rreq.id = 1 ;
    rreq.connector_id = 1 ;
    rreq.charging_profile_purpose = charging_profile_purpose_buf ;
    rreq.stack_level = 1 ;

    strcpy(charging_profile_purpose_buf, charging_profile_purpose_type_values[charging_profile_purpose_type_charge_point_max_profile]) ;

    make_ocpp_clear_charging_profile_req_message(req_buf, message_id, &rreq) ;

    proc_clear_charging_profile_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_clear_charging_profile_conf_message() ;
    parse_ocpp_clear_charging_profile_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", clear_chg_prof_conf.status.key, clear_chg_prof_conf.status.val.str_val) ;

    return 0 ;
}

int proc_clear_charging_profile_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;
    init_clear_charging_profile_req_message() ;
    parse_ocpp_clear_charging_profile_req_message(msg.payload) ;

    make_ocpp_clear_charging_profile_conf_message(resp, msg.message_id, clear_charging_profile_status_values[clear_charging_profile_status_accepted]) ;

    return 0 ;
}
