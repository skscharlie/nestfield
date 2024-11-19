#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_get_composite_schedule_req_message() {
    get_comp_sche_req.connector_id.key = get_composite_schedule_req_field_names[get_composite_schedule_req_connector_id] ;
    
    get_comp_sche_req.duration.key = get_composite_schedule_req_field_names[get_composite_schedule_req_duration] ;

    get_comp_sche_req.charging_rate_unit.key = get_composite_schedule_req_field_names[get_composite_schedule_req_charging_rate_unit] ;
    get_comp_sche_req.charging_rate_unit.val.str_val = gcsr_charging_rate_unit ;
}

void init_get_composite_schedule_conf_message() {
    get_comp_sche_conf.status.key = get_composite_schedule_conf_field_names[get_composite_schedule_conf_status] ;
    get_comp_sche_conf.status.val.str_val = gcsc_status ;

    get_comp_sche_conf.connector_id.key = get_composite_schedule_conf_field_names[get_composite_schedule_conf_connectoe_id] ;
    
    get_comp_sche_conf.schedule_start.key = get_composite_schedule_conf_field_names[get_composite_schedule_conf_schedule_start] ;
    get_comp_sche_conf.schedule_start.val.str_val = gcsc_schedule_start ;

    /*
     * charging schedule 은 class 이므로 charging schedule 의 값을 설정하여 composite_schedule.conf 에 넣어줌.
     */
    get_comp_sche_conf.charging_schedule.key = get_composite_schedule_conf_field_names[get_composite_schedule_conf_charging_schedule] ;
    get_comp_sche_conf.charging_schedule.val.cs_val = &charging_sched ;

    charging_sched.duration.key = charging_schedule_field_names[charging_schedule_duration] ;

    charging_sched.start_schedule.key = charging_schedule_field_names[charging_schedule_start_schedule] ;
    charging_sched.start_schedule.val.str_val = cs_start_schedule ;

    charging_sched.charging_rate_unit.key = charging_schedule_field_names[charging_schedule_charging_rate_unit] ;
    charging_sched.charging_rate_unit.val.str_val = cs_charging_rate_unit ;

    /*
     * charging schedule period array 의 size를 알 수 없으므로 지금은 initialize 할 수 없슴.
     */
    charging_sched.charging_schedule_period.key = charging_schedule_field_names[charging_schedule_charging_schedule_period] ;

    charging_sched.min_charging_rate.key = charging_schedule_field_names[charging_schedule_min_charging_rate] ;
}

int make_ocpp_get_composite_schedule_req_message(char *buf, char *message_id, raw_get_composite_schedule_req *rreq) {
    ocpp_call_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[GET_COMPOSITE_SCHEDULE_INDEX].action ;

    get_comp_sche_req.connector_id.key = get_composite_schedule_req_field_names[get_composite_schedule_req_connector_id] ;
    get_comp_sche_req.connector_id.val.int_val = rreq->connector_id ;

    get_comp_sche_req.duration.key = get_composite_schedule_req_field_names[get_composite_schedule_req_duration] ;
    get_comp_sche_req.duration.val.int_val = rreq->duration ;

    get_comp_sche_req.charging_rate_unit.key = get_composite_schedule_req_field_names[get_composite_schedule_req_charging_rate_unit] ;
    get_comp_sche_req.charging_rate_unit.val.str_val = rreq->charging_rate_unit ;

    object = json_object_new_object() ;
    json_object_object_add(object, get_comp_sche_req.connector_id.key, json_object_new_int(get_comp_sche_req.connector_id.val.int_val)) ;
    json_object_object_add(object, get_comp_sche_req.duration.key, json_object_new_int(get_comp_sche_req.duration.val.int_val)) ;
    json_object_object_add(object, get_comp_sche_req.charging_rate_unit.key, json_object_new_string(get_comp_sche_req.charging_rate_unit.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_get_composite_schedule_conf_message(char *buf, char *message_id, raw_get_composite_schedule_conf *rconf) {
    ocpp_callresult_message message ;
    json_object *object, *cs, *csp, *arr_csp ;
    charging_schedule_period *csp_ptr ;
    raw_charging_schedule_period *rcsp_ptr ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    get_comp_sche_conf.status.key = get_composite_schedule_conf_field_names[get_composite_schedule_conf_status] ;
    get_comp_sche_conf.status.val.str_val = rconf->status ;

    get_comp_sche_conf.connector_id.key = get_composite_schedule_conf_field_names[get_composite_schedule_conf_connectoe_id] ;
    get_comp_sche_conf.connector_id.val.int_val = rconf->connector_id ;

    get_comp_sche_conf.schedule_start.key = get_composite_schedule_conf_field_names[get_composite_schedule_conf_schedule_start] ;
    get_comp_sche_conf.schedule_start.val.str_val = rconf->schedule_start ;

    get_comp_sche_conf.charging_schedule.key = get_composite_schedule_conf_field_names[get_composite_schedule_conf_charging_schedule] ;
    get_comp_sche_conf.charging_schedule.val.cs_val = &charging_sched ;

    charging_sched.duration.key = charging_schedule_field_names[charging_schedule_duration] ;
    charging_sched.duration.val.int_val = rconf->charging_schedule->duration ;

    charging_sched.start_schedule.key = charging_schedule_field_names[charging_schedule_start_schedule] ;
    charging_sched.start_schedule.val.str_val = rconf->charging_schedule->start_schedule ;

    charging_sched.charging_rate_unit.key = charging_schedule_field_names[charging_schedule_charging_rate_unit] ;
    charging_sched.charging_rate_unit.val.str_val = rconf->charging_schedule->charging_rate_unit ;

    charging_sched.number_of_charging_schedule_period = rconf->charging_schedule->number_of_charging_schedule_period ;

    charging_sched.charging_schedule_period.key = charging_schedule_field_names[charging_schedule_charging_schedule_period] ;
    charging_sched.charging_schedule_period.val.csp_val = (charging_schedule_period *)malloc(charging_sched.number_of_charging_schedule_period * sizeof(charging_schedule_period)) ;

    csp_ptr = charging_sched.charging_schedule_period.val.csp_val ;
    rcsp_ptr = rconf->charging_schedule->charging_schedule_period ;

    for(int i = 0 ; i < charging_sched.number_of_charging_schedule_period ; i++, csp_ptr++, rcsp_ptr++) {
        csp_ptr->start_period.key = charging_schedule_period_field_names[charging_schedule_period_start_period] ;
        csp_ptr->start_period.val.int_val = rcsp_ptr->start_period ;

        csp_ptr->limit.key = charging_schedule_period_field_names[charging_schedule_period_limit] ;
        csp_ptr->limit.val.dbl_val = rcsp_ptr->limit ;

        csp_ptr->number_phases.key = charging_schedule_period_field_names[charging_schedule_period_number_phases] ;
        csp_ptr->number_phases.val.int_val = rcsp_ptr->number_phases ;
    }

    charging_sched.min_charging_rate.key = charging_schedule_field_names[charging_schedule_min_charging_rate] ;
    charging_sched.min_charging_rate.val.int_val = rconf->charging_schedule->min_charging_rate ;

    object = json_object_new_object() ;
    json_object_object_add(object, get_comp_sche_conf.status.key, json_object_new_string(get_comp_sche_conf.status.val.str_val)) ;
    json_object_object_add(object, get_comp_sche_conf.connector_id.key, json_object_new_int(get_comp_sche_conf.connector_id.val.int_val)) ;
    json_object_object_add(object, get_comp_sche_conf.schedule_start.key, json_object_new_string(get_comp_sche_conf.schedule_start.val.str_val)) ;

    cs = json_object_new_object() ;
    json_object_object_add(cs, charging_sched.duration.key, json_object_new_int(charging_sched.duration.val.int_val)) ;
    json_object_object_add(cs, charging_sched.start_schedule.key, json_object_new_string(charging_sched.start_schedule.val.str_val)) ;
    json_object_object_add(cs, charging_sched.charging_rate_unit.key, json_object_new_string(charging_sched.charging_rate_unit.val.str_val)) ;
    json_object_object_add(cs, charging_sched.min_charging_rate.key, json_object_new_int(charging_sched.min_charging_rate.val.int_val)) ;

    csp_ptr = charging_sched.charging_schedule_period.val.csp_val ;
    arr_csp = json_object_new_array_ext(charging_sched.number_of_charging_schedule_period) ;
    for(int i = 0 ; i < charging_sched.number_of_charging_schedule_period ; i++, csp_ptr++) {
        csp = json_object_new_object() ;
        json_object_object_add(csp, csp_ptr->start_period.key, json_object_new_int(csp_ptr->start_period.val.int_val)) ;
        json_object_object_add(csp, csp_ptr->limit.key, json_object_new_double(csp_ptr->limit.val.dbl_val)) ;
        json_object_object_add(csp, csp_ptr->number_phases.key, json_object_new_int(csp_ptr->number_phases.val.int_val)) ;

        json_object_array_add(arr_csp, csp) ;
    }

    json_object_object_add(cs, charging_sched.charging_schedule_period.key, arr_csp) ;
    json_object_object_add(object, get_comp_sche_conf.charging_schedule.key, cs) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    free(charging_sched.charging_schedule_period.val.csp_val) ;
    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_get_composite_schedule_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, get_comp_sche_req.connector_id.key) ;
    get_comp_sche_req.connector_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, get_comp_sche_req.duration.key) ;
    get_comp_sche_req.duration.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, get_comp_sche_req.charging_rate_unit.key) ;
    strcpy(get_comp_sche_req.charging_rate_unit.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_get_composite_schedule_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value, *cs, *csp, *arr_csp ;
    charging_schedule *cs_ptr ;
    charging_schedule_period *csp_ptr ;

    char path[32] ;

    value = json_object_object_get(object, get_comp_sche_conf.status.key) ;
    strcpy(get_comp_sche_conf.status.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, get_comp_sche_conf.connector_id.key) ;
    get_comp_sche_conf.connector_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, get_comp_sche_conf.schedule_start.key) ;
    strcpy(get_comp_sche_conf.schedule_start.val.str_val, json_object_get_string(value)) ;

    cs = json_object_object_get(object, get_comp_sche_conf.charging_schedule.key) ;

    cs_ptr = get_comp_sche_conf.charging_schedule.val.cs_val ;
    value = json_object_object_get(cs, cs_ptr->duration.key) ;
    cs_ptr->duration.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(cs, cs_ptr->start_schedule.key) ;
    strcpy(cs_ptr->start_schedule.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(cs, cs_ptr->charging_rate_unit.key) ;
    strcpy(cs_ptr->charging_rate_unit.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(cs, cs_ptr->min_charging_rate.key) ;
    cs_ptr->min_charging_rate.val.dbl_val = json_object_get_double(value) ;

    arr_csp = json_object_object_get(cs, cs_ptr->charging_schedule_period.key) ;
    cs_ptr->number_of_charging_schedule_period = json_object_array_length(arr_csp) ;

    cs_ptr->charging_schedule_period.val.csp_val = (charging_schedule_period *)malloc(cs_ptr->number_of_charging_schedule_period * sizeof(charging_schedule_period)) ;
    csp_ptr = cs_ptr->charging_schedule_period.val.csp_val ;
    for(int i = 0 ; i < cs_ptr->number_of_charging_schedule_period ; i++, csp_ptr++) {
        csp = json_object_array_get_idx(arr_csp, i) ;

        csp_ptr->start_period.key = charging_schedule_period_field_names[charging_schedule_period_start_period] ;
        value = json_object_object_get(csp, csp_ptr->start_period.key) ;
        csp_ptr->start_period.val.int_val = json_object_get_int(value) ;

        csp_ptr->limit.key = charging_schedule_period_field_names[charging_schedule_period_limit] ;
        value = json_object_object_get(csp, csp_ptr->limit.key) ;
        csp_ptr->limit.val.dbl_val = json_object_get_double(value) ;

        csp_ptr->number_phases.key = charging_schedule_period_field_names[charging_schedule_period_number_phases] ;
        value = json_object_object_get(csp, csp_ptr->number_phases.key) ;
        csp_ptr->number_phases.val.int_val = json_object_get_int(value) ;
    }

    json_object_put(object) ;
    return 0 ;
}

int do_get_composite_schedule(ocpp_call_message *req, char *resp) {
    raw_get_composite_schedule_conf rconf ;
    char schedule_start_buf[DATE_TIME_LENGTH + 1] ;
    raw_charging_schedule rcs ;
    char start_schedule_buf[DATE_TIME_LENGTH + 1] ;
    raw_charging_schedule_period rcsp[3], *rcsp_ptr ;

    init_get_composite_schedule_req_message() ;
    parse_ocpp_get_composite_schedule_req_message(req->payload) ;

    get_future_date(gcsc_schedule_start, 10) ;
    get_future_date(start_schedule_buf, 20) ;

    rconf.connector_id = get_comp_sche_req.connector_id.val.int_val ;
    rconf.status = get_composite_schedule_status_values[get_composite_schedule_status_accepted] ;
    rconf.schedule_start = gcsc_schedule_start ;
    rconf.charging_schedule = &rcs ;
    rcs.charging_schedule_period = rcsp ;

    rcs.duration = 10 ;
    rcs.charging_rate_unit = charging_rate_unit_type_values[charging_rate_unit_type_a] ;
    rcs.start_schedule = start_schedule_buf ;
    rcs.min_charging_rate = 100 ;
    rcs.number_of_charging_schedule_period = 3 ;

    rcsp_ptr = rcs.charging_schedule_period ;
    for(int i = 0 ; i < rcs.number_of_charging_schedule_period ; i++, rcsp_ptr++) {
        rcsp_ptr->start_period = 30 ;
        rcsp_ptr->number_phases = 3 ;
        rcsp_ptr->limit = 100 ;
    }
    make_ocpp_get_composite_schedule_conf_message(resp, req->message_id, &rconf) ;

    return 0 ;
}

