#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

#define NUMBER_OF_CHARGING_SCHEDULE_PERIOD      3
int proc_set_charging_profile_req(char *req, char *resp) ;

int set_charging_profile_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_set_charging_profile_req rreq ;
    raw_charging_profile rcp ;
    raw_charging_schedule rcs ;
    raw_charging_schedule_period rcsp[NUMBER_OF_CHARGING_SCHEDULE_PERIOD], *rcsp_ptr ;
    char charging_profile_purpose_buf[STRING_25_TYPE_LENGTH + 1] ;
    char charging_profile_kind_buf[STRING_20_TYPE_LENGTH + 1], recurrency_kind_buf[STRING_20_TYPE_LENGTH + 1] ;
    char valid_from_buf[DATE_TIME_LENGTH + 1], valid_to_buf[DATE_TIME_LENGTH + 1] ;
    char start_schedule_buf[DATE_TIME_LENGTH + 1], charging_rate_unit_buf[STRING_20_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;
    get_future_date(valid_from_buf, 1) ;
    get_future_date(valid_to_buf, 30) ;
    get_future_date(start_schedule_buf, 1) ;

    rreq.connector_id = 1 ;
    rreq.cs_charging_profiles = &rcp ;

    rcp.charging_profile_id = 1 ;
    rcp.transaction_id = make_transaction_id() ;
    rcp.stack_level = 10 ;
    rcp.charging_profile_purpose = charging_profile_purpose_buf ;
    rcp.charging_profile_kine = charging_profile_kind_buf ;
    rcp.recurrency_kind = recurrency_kind_buf ;
    rcp.valid_from = valid_from_buf ;
    rcp.valid_to = valid_to_buf ;
    rcp.charging_schedule = &rcs ;

    rcs.duration = 10 ;
    rcs.start_schedule = start_schedule_buf ;
    rcs.charging_rate_unit = charging_rate_unit_buf ;
    rcs.charging_schedule_period = rcsp ;
    rcs.min_charging_rate = 10 ;
    rcs.number_of_charging_schedule_period = NUMBER_OF_CHARGING_SCHEDULE_PERIOD ;

    rcsp_ptr = rcs.charging_schedule_period ;

    for(int i = 0 ; i < rcs.number_of_charging_schedule_period ; i++, rcsp_ptr++) {
        rcsp_ptr->number_phases = 3 ;
        rcsp_ptr->limit = 8.1 ;
        rcsp_ptr->start_period = 10 ;
    }

    strcpy(charging_profile_purpose_buf, charging_profile_purpose_type_values[charging_profile_purpose_type_charge_point_max_profile]) ;
    strcpy(charging_profile_kind_buf, charging_profile_kind_type_values[charging_profile_kind_type_absolute]) ;
    strcpy(recurrency_kind_buf, recurrency_kind_type_values[recurrency_kind_type_daily]) ;
    strcpy(charging_rate_unit_buf, charging_rate_unit_type_values[charging_rate_unit_type_a]) ;

    make_ocpp_set_charging_profile_req_message(req_buf, message_id, &rreq) ;

    proc_set_charging_profile_req(req_buf, resp_buf) ;
    parse_conf_message(resp_buf, &msg) ;
    init_set_charging_profile_conf_message() ;
    parse_ocpp_set_charging_profile_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", set_charging_prof_conf.status.key, set_charging_prof_conf.status.val.str_val) ;

    return 0 ;
}

int proc_set_charging_profile_req(char *req, char *resp) {
    ocpp_call_message msg ;
    char status_buf[STRING_20_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_set_charging_profile_req_message() ;
    parse_ocpp_set_charging_profile_req_message(msg.payload) ;

    /*
     * set_charging_prof_req message를 사용하여 processiong을 끝내고 나면
     * set_charging_prof_req message를 parse할 때 alloc 했던 charging_schecule_period를 free 해야함.
     */
    free(set_charging_prof_req.cs_charging_profiles.val.chg_prof->charging_schedule.val.cs_val->charging_schedule_period.val.csp_val) ;

    strcpy(status_buf, remote_start_stop_status_values[remote_start_stop_status_accepted]) ;
    make_ocpp_set_charging_profile_conf_message(resp, msg.message_id, status_buf) ;

    return 0 ;
}