#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_set_charging_profile_req_message() {
    set_charging_prof_req.connector_id.key = set_charging_profile_req_field_names[set_charging_profile_req_connector_id] ;
    // value type이 integer이므로 initialize할 필요가 없슴

    set_charging_prof_req.cs_charging_profiles.key = set_charging_profile_req_field_names[set_charging_profile_req_cs_charging_profile] ;
    set_charging_prof_req.cs_charging_profiles.val.chg_prof = &charging_prof ;

    charging_prof.charging_profile_id.key = charging_profile_field_names[charging_profile_charging_profile_id] ;
    // value type이 integer이므로 initialize할 필요가 없슴

    charging_prof.transaction_id.key = charging_profile_field_names[charging_profile_transaction_id] ;
    // value type이 integer이므로 initialize할 필요가 없슴

    charging_prof.stack_level.key = charging_profile_field_names[charging_profile_stack_level] ;
    // value type이 integer이므로 initialize할 필요가 없슴

    charging_prof.charging_profile_purpose.key = charging_profile_field_names[charging_profile_charging_profile_purpose] ;
    charging_prof.charging_profile_purpose.val.str_val = cp_charging_profile_purpose ;

    charging_prof.charging_profile_kind.key = charging_profile_field_names[charging_profile_charging_profile_kind] ;
    charging_prof.charging_profile_kind.val.str_val = cp_charging_profile_kind ;

    charging_prof.recurrency_kind.key = charging_profile_field_names[charging_profile_recurrency_kind] ;
    charging_prof.recurrency_kind.val.str_val = cp_recurrency_kind ;

    charging_prof.valid_from.key = charging_profile_field_names[charging_profile_valid_from] ;
    charging_prof.valid_from.val.str_val = cp_valid_from ;

    charging_prof.valid_to.key = charging_profile_field_names[charging_profile_valid_to] ;
    charging_prof.valid_to.val.str_val = cp_valid_to ;

    charging_prof.charging_schedule.key = charging_profile_field_names[charging_profile_charging_schedule] ;
    charging_prof.charging_schedule.val.cs_val = &charging_sched ;

    charging_sched.duration.key = charging_schedule_field_names[charging_schedule_duration] ;
    // value type이 integer이므로 initialize할 필요가 없슴

    charging_sched.start_schedule.key = charging_schedule_field_names[charging_schedule_start_schedule] ;
    charging_sched.start_schedule.val.str_val = cs_start_schedule ;

    charging_sched.charging_rate_unit.key = charging_schedule_field_names[charging_schedule_charging_rate_unit] ;
    charging_sched.charging_rate_unit.val.str_val = cs_charging_rate_unit ;

    charging_sched.charging_schedule_period.key = charging_schedule_field_names[charging_schedule_charging_schedule_period] ;
    // charging sehedule period array 의 size를 알 수 없으므로 initialize할 수 없슴.
}

void init_set_charging_profile_conf_message() {
    set_charging_prof_conf.status.key = set_charging_profile_conf_field_name[set_charging_profile_conf_status] ;
    set_charging_prof_conf.status.val.str_val = rstc_status ;
}

int make_ocpp_set_charging_profile_req_message(char *buf, char *message_id, raw_set_charging_profile_req *rreq) {
    ocpp_call_message message ;
    json_object *object, *cp, *cs, *csp, *arr_csp ;
    charging_schedule_period *csp_ptr ;
    raw_charging_schedule_period *rcsp_ptr ;

    set_charging_prof_req.connector_id.key = set_charging_profile_req_field_names[set_charging_profile_req_connector_id] ;
    set_charging_prof_req.connector_id.val.int_val = rreq->connector_id ;

    set_charging_prof_req.cs_charging_profiles.key = set_charging_profile_req_field_names[set_charging_profile_req_cs_charging_profile] ;
    set_charging_prof_req.cs_charging_profiles.val.chg_prof = &charging_prof ;

    charging_prof.charging_profile_id.key = charging_profile_field_names[charging_profile_charging_profile_id] ;
    charging_prof.charging_profile_id.val.int_val = rreq->cs_charging_profiles->charging_profile_id ;

    charging_prof.transaction_id.key = charging_profile_field_names[charging_profile_transaction_id] ;
    charging_prof.transaction_id.val.int_val = rreq->cs_charging_profiles->transaction_id ;

    charging_prof.stack_level.key = charging_profile_field_names[charging_profile_stack_level] ;
    charging_prof.stack_level.val.int_val = rreq->cs_charging_profiles->stack_level ;

    charging_prof.charging_profile_purpose.key = charging_profile_field_names[charging_profile_charging_profile_purpose] ;
    charging_prof.charging_profile_purpose.val.str_val = rreq->cs_charging_profiles->charging_profile_purpose ;

    charging_prof.charging_profile_kind.key = charging_profile_field_names[charging_profile_charging_profile_kind] ;
    charging_prof.charging_profile_kind.val.str_val = rreq->cs_charging_profiles->charging_profile_kine ;

    charging_prof.recurrency_kind.key = charging_profile_field_names[charging_profile_recurrency_kind] ;
    charging_prof.recurrency_kind.val.str_val = rreq->cs_charging_profiles->recurrency_kind ;

    charging_prof.valid_from.key = charging_profile_field_names[charging_profile_valid_from] ;
    charging_prof.valid_from.val.str_val = rreq->cs_charging_profiles->valid_from ;

    charging_prof.valid_to.key = charging_profile_field_names[charging_profile_valid_to] ;
    charging_prof.valid_to.val.str_val = rreq->cs_charging_profiles->valid_to ;

    charging_prof.charging_schedule.key = charging_profile_field_names[charging_profile_charging_schedule] ;
    charging_prof.charging_schedule.val.cs_val = &charging_sched ;

    charging_sched.duration.key = charging_schedule_field_names[charging_schedule_duration] ;
    charging_sched.duration.val.int_val = rreq->cs_charging_profiles->charging_schedule->duration ;

    charging_sched.start_schedule.key = charging_schedule_field_names[charging_schedule_start_schedule] ;
    charging_sched.start_schedule.val.str_val = rreq->cs_charging_profiles->charging_schedule->start_schedule ;

    charging_sched.charging_rate_unit.key = charging_schedule_field_names[charging_schedule_charging_rate_unit] ;
    charging_sched.charging_rate_unit.val.str_val = rreq->cs_charging_profiles->charging_schedule->charging_rate_unit ;

    charging_sched.min_charging_rate.key = charging_schedule_field_names[charging_schedule_min_charging_rate] ;
    charging_sched.min_charging_rate.val.dbl_val = rreq->cs_charging_profiles->charging_schedule->min_charging_rate ;

    charging_sched.charging_schedule_period.key = charging_schedule_field_names[charging_schedule_charging_schedule_period] ;
    charging_sched.number_of_charging_schedule_period = rreq->cs_charging_profiles->charging_schedule->number_of_charging_schedule_period ;
    charging_sched.charging_schedule_period.val.csp_val = (charging_schedule_period *)malloc(charging_sched.number_of_charging_schedule_period * sizeof(charging_schedule_period)) ;

    csp_ptr = charging_sched.charging_schedule_period.val.csp_val ;
    rcsp_ptr = rreq->cs_charging_profiles->charging_schedule->charging_schedule_period ;

    for(int i = 0 ; i < charging_sched.number_of_charging_schedule_period ; i++, csp_ptr++, rcsp_ptr++) {
        csp_ptr->start_period.key = charging_schedule_period_field_names[charging_schedule_period_start_period] ;
        csp_ptr->start_period.val.int_val = rcsp_ptr->start_period ;

        csp_ptr->limit.key = charging_schedule_period_field_names[charging_schedule_period_limit] ;
        csp_ptr->limit.val.dbl_val = rcsp_ptr->limit ;

        csp_ptr->number_phases.key = charging_schedule_period_field_names[charging_schedule_period_number_phases] ;
        csp_ptr->number_phases.val.int_val = rcsp_ptr->number_phases ;
    }

    object = json_object_new_object() ;
    json_object_object_add(object, set_charging_prof_req.connector_id.key, json_object_new_int(set_charging_prof_req.connector_id.val.int_val)) ;

    cp = json_object_new_object() ;
    json_object_object_add(cp, charging_prof.charging_profile_id.key, json_object_new_int(charging_prof.charging_profile_id.val.int_val)) ;
    json_object_object_add(cp, charging_prof.transaction_id.key, json_object_new_int(charging_prof.transaction_id.val.int_val)) ;
    json_object_object_add(cp, charging_prof.stack_level.key, json_object_new_int(charging_prof.stack_level.val.int_val)) ;
    json_object_object_add(cp, charging_prof.charging_profile_purpose.key, json_object_new_string(charging_prof.charging_profile_purpose.val.str_val)) ;
    json_object_object_add(cp, charging_prof.charging_profile_kind.key, json_object_new_string(charging_prof.charging_profile_kind.val.str_val)) ;
    json_object_object_add(cp, charging_prof.recurrency_kind.key, json_object_new_string(charging_prof.recurrency_kind.val.str_val)) ;
    json_object_object_add(cp, charging_prof.valid_from.key, json_object_new_string(charging_prof.valid_from.val.str_val)) ;
    json_object_object_add(cp, charging_prof.valid_to.key, json_object_new_string(charging_prof.valid_to.val.str_val)) ;

    cs =json_object_new_object() ;
    json_object_object_add(cs, charging_sched.duration.key, json_object_new_int(charging_sched.duration.val.int_val)) ;
    json_object_object_add(cs, charging_sched.start_schedule.key, json_object_new_string(charging_sched.start_schedule.val.str_val)) ;
    json_object_object_add(cs, charging_sched.charging_rate_unit.key, json_object_new_string(charging_sched.charging_rate_unit.val.str_val)) ;
    json_object_object_add(cs, charging_sched.min_charging_rate.key, json_object_new_int(charging_sched.min_charging_rate.val.dbl_val)) ;

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
    json_object_object_add(cp, charging_prof.charging_schedule.key, cs) ;
    json_object_object_add(object, set_charging_prof_req.cs_charging_profiles.key, cp) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    free(set_charging_prof_req.cs_charging_profiles.val.chg_prof->charging_schedule.val.cs_val->charging_schedule_period.val.csp_val) ;
    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_set_charging_profile_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    object = json_object_new_object() ;
    set_charging_prof_conf.status.key = set_charging_profile_conf_field_name[set_charging_profile_conf_status] ;
    json_object_object_add(object, set_charging_prof_conf.status.key, json_object_new_string(status)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_set_charging_profile_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value, *cp, *cs, *csp, *arr_csp ;
    charging_profile *cp_ptr ;
    charging_schedule *cs_ptr ;
    charging_schedule_period *csp_ptr ;

    value = json_object_object_get(object, set_charging_prof_req.connector_id.key) ;
    set_charging_prof_req.connector_id.val.int_val = json_object_get_int(value) ;

    cp_ptr = set_charging_prof_req.cs_charging_profiles.val.chg_prof ;
    cp = json_object_object_get(object, set_charging_prof_req.cs_charging_profiles.key) ;
 
    value = json_object_object_get(cp, cp_ptr->charging_profile_id.key) ;
    cp_ptr->charging_profile_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(cp, cp_ptr->transaction_id.key) ;
    cp_ptr->transaction_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(cp, cp_ptr->stack_level.key) ;
    cp_ptr->stack_level.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(cp, cp_ptr->charging_profile_purpose.key) ;
    strcpy(cp_ptr->charging_profile_purpose.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(cp, cp_ptr->charging_profile_kind.key) ;
    strcpy(cp_ptr->charging_profile_kind.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(cp, cp_ptr->recurrency_kind.key) ;
    strcpy(cp_ptr->recurrency_kind.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(cp, cp_ptr->valid_from.key) ;
    strcpy(cp_ptr->valid_from.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(cp, cp_ptr->valid_to.key) ;
    strcpy(cp_ptr->valid_to.val.str_val, json_object_get_string(value)) ;

    cs_ptr = cp_ptr->charging_schedule.val.cs_val ;
    cs = json_object_object_get(cp, cp_ptr->charging_schedule.key) ;

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

int parse_ocpp_set_charging_profile_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, set_charging_prof_conf.status.key) ;
    strcpy(set_charging_prof_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_set_charging_profile(ocpp_call_message *req, char *resp) {
    init_set_charging_profile_req_message() ;
    parse_ocpp_set_charging_profile_req_message(req->payload) ;

    make_ocpp_set_charging_profile_conf_message(resp, req->message_id, charging_profile_status_values[charging_profile_status_accepted]) ;
    return 0 ;
}