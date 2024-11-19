#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

#define NUMBER_OF_CHARGING_SCHEDULE_PERIOD      3

int proc_get_composite_schedule_req(char *req, char *resp) ;

int get_composite_schedule_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_get_composite_schedule_req rreq ;
    char charging_rate_unit_buf[STRING_20_TYPE_LENGTH + 1] ;
    charging_schedule_period *csp_ptr ;

    make_message_id(message_id) ;

    rreq.connector_id = 1 ;
    rreq.duration = 10 ;
    rreq.charging_rate_unit = charging_rate_unit_buf ;

    strcpy(charging_rate_unit_buf, charging_rate_unit_type_values[charging_rate_unit_type_w]) ;

    make_ocpp_get_composite_schedule_req_message(req_buf, message_id, &rreq) ;

    proc_get_composite_schedule_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_get_composite_schedule_conf_message() ;
    parse_ocpp_get_composite_schedule_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", get_comp_sche_conf.status.key, get_comp_sche_conf.status.val.str_val) ;
    printf("key : %s, value : %d\n", get_comp_sche_conf.connector_id.key, get_comp_sche_conf.connector_id.val.int_val) ;
    printf("key : %s, value %s\n", get_comp_sche_conf.schedule_start.key, get_comp_sche_conf.schedule_start.val.str_val) ;
    printf("key : %s.%s, value : %d\n", get_comp_sche_conf.charging_schedule.key, 
                                        get_comp_sche_conf.charging_schedule.val.cs_val->duration.key, 
                                        get_comp_sche_conf.charging_schedule.val.cs_val->duration.val.int_val) ;
    printf("key : %s.%s, value : %s\n", get_comp_sche_conf.charging_schedule.key,
                                        get_comp_sche_conf.charging_schedule.val.cs_val->start_schedule.key,
                                        get_comp_sche_conf.charging_schedule.val.cs_val->start_schedule.val.str_val) ;
    printf("key : %s.%s, value : %s\n", get_comp_sche_conf.charging_schedule.key,
                                        get_comp_sche_conf.charging_schedule.val.cs_val->charging_rate_unit.key,
                                        get_comp_sche_conf.charging_schedule.val.cs_val->charging_rate_unit.val.str_val) ;
    printf("key : %s.%s, value : %d\n", get_comp_sche_conf.charging_schedule.key,
                                        get_comp_sche_conf.charging_schedule.val.cs_val->min_charging_rate.key,
                                        get_comp_sche_conf.charging_schedule.val.cs_val->min_charging_rate.val.int_val) ;

    csp_ptr = get_comp_sche_conf.charging_schedule.val.cs_val->charging_schedule_period.val.csp_val ;
    for(int i = 0 ; i < get_comp_sche_conf.charging_schedule.val.cs_val->number_of_charging_schedule_period ; i++, csp_ptr++) {
        printf("key : %s.%s.%s, value : %d\n", get_comp_sche_conf.charging_schedule.key,
                                            get_comp_sche_conf.charging_schedule.val.cs_val->charging_schedule_period.key,
                                            csp_ptr->start_period.key,
                                            csp_ptr->start_period.val.int_val) ;
        printf("key : %s.%s.%s, value : %d\n", get_comp_sche_conf.charging_schedule.key,
                                            get_comp_sche_conf.charging_schedule.val.cs_val->charging_schedule_period.key,
                                            csp_ptr->number_phases.key,
                                            csp_ptr->number_phases.val.int_val) ;
        printf("key : %s.%s.%s, value : %f\n", get_comp_sche_conf.charging_schedule.key,
                                            get_comp_sche_conf.charging_schedule.val.cs_val->charging_schedule_period.key,
                                            csp_ptr->limit.key,
                                            csp_ptr->limit.val.dbl_val) ;
    
    }

    free(get_comp_sche_conf.charging_schedule.val.cs_val->charging_schedule_period.val.csp_val) ;
    return 0 ;
}

int proc_get_composite_schedule_req(char *req, char *resp) {
    ocpp_call_message msg ;
    raw_get_composite_schedule_conf rconf ;
    char schedule_start_buf[DATE_TIME_LENGTH + 1] ;
    raw_charging_schedule rcs ;
    char start_schedule_buf[DATE_TIME_LENGTH + 1] ;
    raw_charging_schedule_period rcsp[NUMBER_OF_CHARGING_SCHEDULE_PERIOD], *rcsp_ptr ;

    parse_req_message(req, &msg) ;
    parse_ocpp_get_composite_schedule_req_message(msg.payload) ;

    get_future_date(schedule_start_buf, 10) ;
    get_future_date(start_schedule_buf, 20) ;

    rconf.connector_id = get_comp_sche_req.connector_id.val.int_val ;
    rconf.status = get_composite_schedule_status_values[get_composite_schedule_status_accepted] ;
    rconf.schedule_start = schedule_start_buf ;
    rconf.charging_schedule = &rcs ;
    rcs.charging_schedule_period = rcsp ;

    rcs.duration = 10 ;
    rcs.charging_rate_unit = charging_rate_unit_type_values[charging_rate_unit_type_a] ;
    rcs.start_schedule = start_schedule_buf ;
    rcs.min_charging_rate = 100 ;
    rcs.number_of_charging_schedule_period = NUMBER_OF_CHARGING_SCHEDULE_PERIOD ;

    rcsp_ptr = rcs.charging_schedule_period ;
    for(int i = 0 ; i < rcs.number_of_charging_schedule_period ; i++, rcsp_ptr++) {
        rcsp_ptr->start_period = 30 ;
        rcsp_ptr->number_phases = 3 ;
        rcsp_ptr->limit = 100 ;
    }
    make_ocpp_get_composite_schedule_conf_message(resp, msg.message_id, &rconf) ;

    return 0 ;
}