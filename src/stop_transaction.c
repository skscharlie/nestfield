#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_stop_transaction_req_message() {
    stop_trans_req.id_tag.key = stop_transaction_req_field_names[stop_transaction_req_id_tag] ;
    stop_trans_req.id_tag.val.str_val = str_id_tag ;

    stop_trans_req.meter_stop.key = stop_transaction_req_field_names[stop_transaction_req_meter_stop] ;
    // value는 integer이므로 initialize할 필요가 없슴.

    stop_trans_req.timestamp.key = stop_transaction_req_field_names[stop_transaction_req_timestamp] ;
    stop_trans_req.timestamp.val.str_val = str_timestamp ;

    stop_trans_req.transaction_id.key = stop_transaction_req_field_names[stop_transaction_req_transaction_id] ;
    // values 는 integer 이므로 initialize 할 필요가 없슴.

    stop_trans_req.reason.key = stop_transaction_req_field_names[stop_transaction_req_reason] ;
    stop_trans_req.reason.val.str_val = str_reason ;

    stop_trans_req.transaction_data.key = stop_transaction_req_field_names[stop_transaction_req_transaction_data] ;
    // transaction_data는 array이고 init 시점에서 array size를 알 수 없으므로 지금 initialize할 수 없다.
}

void init_stop_transaction_conf_message() {
    stop_trans_conf.id_tag_info.key = stop_transaction_conf_field_name[stop_transaction_conf_id_tag_info] ;
    stop_trans_conf.id_tag_info.val.iti_val = &id_tag_inf ;

    stop_trans_conf.id_tag_info.val.iti_val->expiry_date.key = id_tag_info_field_names[id_tag_info_expiry_date] ;
    stop_trans_conf.id_tag_info.val.iti_val->expiry_date.val.str_val = iti_expiry_date ;

    stop_trans_conf.id_tag_info.val.iti_val->status.key = id_tag_info_field_names[id_tag_info_status] ;
    stop_trans_conf.id_tag_info.val.iti_val->status.val.str_val = iti_status ;

    stop_trans_conf.id_tag_info.val.iti_val->parent_id_tag.key = id_tag_info_field_names[id_tag_info_parient_id_tag] ;
    stop_trans_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val = iti_parent_id_tag ;
}

int make_ocpp_stop_transaction_req_message(char *buf, char *message_id, raw_stop_transaction_req *rreq) {
    ocpp_call_message message ;
    json_object *object, *arr_mv, *arr_sv, *mv, *sv, *value ;
    meter_value *transaction_data_ptr ;
    sampled_value *sampled_value_ptr ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[STOP_TRANSACTION_INDEX].action ;

    stop_trans_req.id_tag.key = stop_transaction_req_field_names[stop_transaction_req_id_tag] ;
    stop_trans_req.id_tag.val.str_val = rreq->id_tag ;

    stop_trans_req.meter_stop.key = stop_transaction_req_field_names[stop_transaction_req_meter_stop] ;
    stop_trans_req.meter_stop.val.int_val = rreq->meter_stop ;

    stop_trans_req.timestamp.key = stop_transaction_req_field_names[stop_transaction_req_timestamp] ;
    stop_trans_req.timestamp.val.str_val = rreq->timestamp ;

    stop_trans_req.transaction_id.key = stop_transaction_req_field_names[stop_transaction_req_transaction_id] ;
    stop_trans_req.transaction_id.val.int_val = rreq->transaction_id ;

    stop_trans_req.reason.key = stop_transaction_req_field_names[stop_transaction_req_reason] ;
    stop_trans_req.reason.val.str_val = rreq->reason ;

    stop_trans_req.transaction_data.key = stop_transaction_req_field_names[stop_transaction_req_transaction_data] ;
    stop_trans_req.transaction_data.val.mtr_val = (meter_value *)malloc(rreq->number_of_transaction_data * sizeof(meter_value)) ;
    transaction_data_ptr = stop_trans_req.transaction_data.val.mtr_val ;

    for(int i = 0 ; i < rreq->number_of_transaction_data ; i++, transaction_data_ptr++) {
        transaction_data_ptr->timestamp.key = meter_value_field_names[meter_value_timestamp] ;
        transaction_data_ptr->timestamp.val.str_val = rreq->transaction_data->timestamp ;

        transaction_data_ptr->sampled_value.key = meter_value_field_names[meter_value_sampled_value] ;
        transaction_data_ptr->sampled_value.val.samp_val = (sampled_value *)malloc(rreq->transaction_data->number_of_sampled_value * sizeof(sampled_value)) ;

        sampled_value_ptr = transaction_data_ptr->sampled_value.val.samp_val ;
        for(int j = 0 ; j < rreq->transaction_data->number_of_sampled_value ; j++, sampled_value_ptr++) {
            sampled_value_ptr->value.key = sampled_value_field_names[sampled_value_value] ;
            sampled_value_ptr->value.val.str_val = rreq->transaction_data->sampled_value->value ;

            sampled_value_ptr->context.key = sampled_value_field_names[sampled_value_context] ;
            sampled_value_ptr->context.val.str_val = rreq->transaction_data->sampled_value->context ;

            sampled_value_ptr->format.key = sampled_value_field_names[sampled_value_format] ;
            sampled_value_ptr->format.val.str_val = rreq->transaction_data->sampled_value->format ;

            sampled_value_ptr->measurand.key = sampled_value_field_names[sampled_value_measurand] ;
            sampled_value_ptr->measurand.val.str_val = rreq->transaction_data->sampled_value->measurand ;

            sampled_value_ptr->phase.key = sampled_value_field_names[sampled_value_phase] ;
            sampled_value_ptr->phase.val.str_val = rreq->transaction_data->sampled_value->phase ;

            sampled_value_ptr->location.key = sampled_value_field_names[sampled_value_location] ;
            sampled_value_ptr->location.val.str_val = rreq->transaction_data->sampled_value->location ;

            sampled_value_ptr->unit.key = sampled_value_field_names[sampled_value_unit] ;
            sampled_value_ptr->unit.val.str_val = rreq->transaction_data->sampled_value->unit ;
        }
    }

    object = json_object_new_object() ;
    json_object_object_add(object, stop_trans_req.id_tag.key, json_object_new_string(stop_trans_req.id_tag.val.str_val)) ;
    json_object_object_add(object, stop_trans_req.meter_stop.key, json_object_new_int(stop_trans_req.meter_stop.val.int_val)) ;
    json_object_object_add(object, stop_trans_req.timestamp.key, json_object_new_string(stop_trans_req.timestamp.val.str_val)) ;
    json_object_object_add(object, stop_trans_req.transaction_id.key, json_object_new_int(stop_trans_req.transaction_id.val.int_val)) ;
    json_object_object_add(object, stop_trans_req.reason.key, json_object_new_string(stop_trans_req.reason.val.str_val)) ;
    
    arr_mv = json_object_new_array_ext(rreq->number_of_transaction_data) ;

    transaction_data_ptr = stop_trans_req.transaction_data.val.mtr_val ;
    for(int i = 0 ; i < rreq->number_of_transaction_data ; i++, transaction_data_ptr++) {
        mv = json_object_new_object() ;

        value = json_object_new_string(transaction_data_ptr->timestamp.val.str_val) ;
        json_object_object_add(mv, transaction_data_ptr->timestamp.key, value) ;

        arr_sv = json_object_new_array_ext(rreq->transaction_data->number_of_sampled_value) ;
        sampled_value_ptr = transaction_data_ptr->sampled_value.val.samp_val ;
        for(int j = 0 ; j < rreq->transaction_data->number_of_sampled_value ; j++, sampled_value_ptr++) {
            sv = json_object_new_object() ;
            value = json_object_new_string(sampled_value_ptr->value.val.str_val) ;
            json_object_object_add(sv, sampled_value_ptr->value.key, value) ;

            value = json_object_new_string(sampled_value_ptr->context.val.str_val) ;
            json_object_object_add(sv, sampled_value_ptr->context.key, value) ;

            value = json_object_new_string(sampled_value_ptr->format.val.str_val) ;
            json_object_object_add(sv, sampled_value_ptr->format.key, value) ;

            value = json_object_new_string(sampled_value_ptr->measurand.val.str_val) ;
            json_object_object_add(sv, sampled_value_ptr->measurand.key, value) ;

            value = json_object_new_string(sampled_value_ptr->phase.val.str_val) ;
            json_object_object_add(sv, sampled_value_ptr->phase.key, value) ;

            value = json_object_new_string(sampled_value_ptr->location.val.str_val) ;
            json_object_object_add(sv, sampled_value_ptr->location.key, value) ;

            value = json_object_new_string(sampled_value_ptr->unit.val.str_val) ;
            json_object_object_add(sv, sampled_value_ptr->unit.key, value) ;

            json_object_array_add(arr_sv, sv) ;
        }

        json_object_object_add(mv, transaction_data_ptr->sampled_value.key, arr_sv) ;
        json_object_array_add(arr_mv, mv) ;
    }

    json_object_object_add(object, stop_trans_req.transaction_data.key, arr_mv) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    
    transaction_data_ptr = stop_trans_req.transaction_data.val.mtr_val ;
    for(int i = 0 ; i < stop_trans_req.number_of_transaction_data ; i++, transaction_data_ptr++) {
        free(transaction_data_ptr->sampled_value.val.samp_val) ;
    }
    return 0 ;
}

int make_ocpp_stop_transaction_conf_message(char *buf, char *message_id, raw_stop_transaction_conf *rconf) {
    ocpp_callresult_message message ;
    json_object *object, *iti ;
    id_tag_info *piti ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    stop_trans_conf.id_tag_info.key = stop_transaction_conf_field_name[stop_transaction_conf_id_tag_info] ;
    stop_trans_conf.id_tag_info.val.iti_val = &id_tag_inf ;

    piti = stop_trans_conf.id_tag_info.val.iti_val ;

    piti->expiry_date.key = id_tag_info_field_names[id_tag_info_expiry_date] ;
    piti->expiry_date.val.str_val = rconf->id_tag_info->expiry_date ;

    piti->parent_id_tag.key = id_tag_info_field_names[id_tag_info_parient_id_tag] ;
    piti->parent_id_tag.val.str_val = rconf->id_tag_info->parent_id_tag ;

    piti->status.key = id_tag_info_field_names[id_tag_info_status] ;
    piti->status.val.str_val = rconf->id_tag_info->status ;

    object = json_object_new_object() ;
    iti = json_object_new_object() ;

    json_object_object_add(iti, piti->expiry_date.key, json_object_new_string(piti->expiry_date.val.str_val)) ;
    json_object_object_add(iti, piti->parent_id_tag.key, json_object_new_string(piti->parent_id_tag.val.str_val)) ;
    json_object_object_add(iti, piti->status.key, json_object_new_string(piti->status.val.str_val)) ;

    json_object_object_add(object, stop_trans_conf.id_tag_info.key, iti) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}


/*
 * allocation 한 모든 memory는 사용이 끝나면 반드시 free 해줘야함.
 */
int parse_ocpp_stop_transaction_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *arr_mv, *arr_sv, *mv, *sv, *value ;
    meter_value *transaction_data_ptr ;
    sampled_value *sampled_value_ptr ;
    int mv_len, sv_len ;

    value = json_object_object_get(object, stop_trans_req.id_tag.key) ;
    stop_trans_req.id_tag.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, stop_trans_req.meter_stop.key) ;
    stop_trans_req.meter_stop.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, stop_trans_req.timestamp.key) ;
    strcpy(stop_trans_req.timestamp.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(object, stop_trans_req.transaction_id.key) ;
    stop_trans_req.transaction_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, stop_trans_req.reason.key) ;
    strcpy(stop_trans_req.reason.val.str_val, json_object_get_string(value)) ;

    arr_mv = json_object_object_get(object, stop_trans_req.transaction_data.key) ;
    mv_len = json_object_array_length(arr_mv) ;
    stop_trans_req.number_of_transaction_data = mv_len ;

    stop_trans_req.transaction_data.val.mtr_val = (meter_value *)malloc(mv_len * sizeof(meter_value)) ;
    transaction_data_ptr = stop_trans_req.transaction_data.val.mtr_val ;

    for(int i = 0 ; i < mv_len ; i++, transaction_data_ptr++) {
        mv = json_object_array_get_idx(arr_mv, i) ;

        transaction_data_ptr->timestamp.val.str_val = (char *)malloc(DATE_TIME_LENGTH + 1) ;
    
        /*
         * init_stop_transaction_req_message 에서 array size를 몰라서 initialize 못허였으므로 지금 해줘야함.
         */
        transaction_data_ptr->timestamp.key = meter_value_field_names[meter_value_timestamp] ;
        value = json_object_object_get(mv, transaction_data_ptr->timestamp.key) ;
        strcpy(transaction_data_ptr->timestamp.val.str_val, json_object_get_string(value)) ;

        transaction_data_ptr->sampled_value.key = meter_value_field_names[meter_value_sampled_value] ;
        arr_sv = json_object_object_get(mv, transaction_data_ptr->sampled_value.key) ;
        sv_len = json_object_array_length(arr_sv) ;

        transaction_data_ptr->number_of_sampled_value = sv_len ;

        transaction_data_ptr->sampled_value.val.samp_val = (sampled_value *)malloc(sv_len * sizeof(sampled_value)) ;
        sampled_value_ptr = transaction_data_ptr->sampled_value.val.samp_val ;
        for(int j = 0 ; j < sv_len ; j++, sampled_value_ptr++) {
            sampled_value_ptr->value.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;
            sampled_value_ptr->context.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH +1) ;
            sampled_value_ptr->format.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;
            sampled_value_ptr->measurand.val.str_val = (char *)malloc(STRING_50_TYPE_LENGTH + 1) ;
            sampled_value_ptr->phase.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;
            sampled_value_ptr->location.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;
            sampled_value_ptr->unit.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;

            sv = json_object_array_get_idx(arr_sv, j) ;

            sampled_value_ptr->value.key = sampled_value_field_names[sampled_value_value] ;
            value = json_object_object_get(sv, sampled_value_ptr->value.key) ;
            strcpy(sampled_value_ptr->value.val.str_val, json_object_get_string(value)) ;

            sampled_value_ptr->context.key = sampled_value_field_names[sampled_value_context] ;
            value = json_object_object_get(sv, sampled_value_ptr->context.key) ;
            strcpy(sampled_value_ptr->context.val.str_val, json_object_get_string(value)) ;

            sampled_value_ptr->format.key = sampled_value_field_names[sampled_value_format] ;
            value = json_object_object_get(sv, sampled_value_ptr->format.key) ;
            strcpy(sampled_value_ptr->format.val.str_val, json_object_get_string(value)) ;

            sampled_value_ptr->measurand.key = sampled_value_field_names[sampled_value_measurand] ;
            value = json_object_object_get(sv, sampled_value_ptr->measurand.key) ;
            strcpy(sampled_value_ptr->measurand.val.str_val, json_object_get_string(value)) ;

            sampled_value_ptr->phase.key = sampled_value_field_names[sampled_value_phase] ;
            value = json_object_object_get(sv, sampled_value_ptr->phase.key) ;
            strcpy(sampled_value_ptr->phase.val.str_val, json_object_get_string(value)) ;

            sampled_value_ptr->location.key = sampled_value_field_names[sampled_value_location] ;
            value = json_object_object_get(sv, sampled_value_ptr->location.key) ;
            strcpy(sampled_value_ptr->location.val.str_val, json_object_get_string(value)) ;

            sampled_value_ptr->unit.key = sampled_value_field_names[sampled_value_unit] ;
            value = json_object_object_get(sv, sampled_value_ptr->unit.key) ;
            strcpy(sampled_value_ptr->unit.val.str_val, json_object_get_string(value)) ;
        }
    }

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_stop_transaction_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value, *iti ;

    iti = json_object_object_get(object, stop_trans_conf.id_tag_info.key) ;
    
    value = json_object_object_get(iti, stop_trans_conf.id_tag_info.val.iti_val->expiry_date.key) ;
    strcpy(stop_trans_conf.id_tag_info.val.iti_val->expiry_date.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(iti, stop_trans_conf.id_tag_info.val.iti_val->parent_id_tag.key) ;
    strcpy(stop_trans_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val, json_object_get_string(value)) ;

    value = json_object_object_get(iti, stop_trans_conf.id_tag_info.val.iti_val->status.key) ;
    strcpy(stop_trans_conf.id_tag_info.val.iti_val->status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;

    return 0 ;
}

void static init_raw_req_message(raw_stop_transaction_req *rreq) {
    raw_meter_value *prmv ;
    raw_sampled_value *prsv ;

    prmv = rreq->transaction_data ;
    for(int i = 0 ; i < rreq->number_of_transaction_data ; i++, prmv++) {
        get_future_date(rreq->transaction_data->timestamp, 0) ;
        
        prsv = prmv->sampled_value ;
        for(int j = 0 ; j < prmv->number_of_sampled_value ; j++, prsv++) {
            strcpy(prsv->value, "100.2345") ;
            strcpy(prsv->context, reading_context_values[reading_context_interruption_begin]) ;
            strcpy(prsv->format, value_format_values[value_format_raw]) ;
            strcpy(prsv->measurand, measurand_values[measurand_current_export]) ;
            strcpy(prsv->phase, phase_values[phase_L1_L2]) ;
            strcpy(prsv->location, location_values[location_body]) ;
            strcpy(prsv->unit, unit_of_measure_values[unit_of_measure_A]) ;
        }
    }
}

#define NUMBER_OF_TRANSACTION_DATA       2
#define NUMBER_OF_SAMPLED_VALUE     2

int do_stop_transaction_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_stop_transaction_req rreq ;
    raw_meter_value rmv[NUMBER_OF_TRANSACTION_DATA], *prmv ;
    raw_sampled_value rsv[NUMBER_OF_SAMPLED_VALUE], *prsv ;
    char id_tag_buf[STRING_20_TYPE_LENGTH + 1], ts_buf[DATE_TIME_LENGTH + 1], reason_buf[STRING_20_TYPE_LENGTH + 1] ;
    char timestamp_buf[NUMBER_OF_TRANSACTION_DATA][DATE_TIME_LENGTH + 1], value_buf[NUMBER_OF_SAMPLED_VALUE][STRING_20_TYPE_LENGTH + 1] ;
    char context_buf[NUMBER_OF_SAMPLED_VALUE][STRING_20_TYPE_LENGTH + 1] ;
    char format_buf[NUMBER_OF_SAMPLED_VALUE][STRING_20_TYPE_LENGTH + 1], measurand_buf[NUMBER_OF_SAMPLED_VALUE][STRING_50_TYPE_LENGTH + 1] ;
    char phase_buf[NUMBER_OF_SAMPLED_VALUE][STRING_20_TYPE_LENGTH + 1] ;
    char location_buf[NUMBER_OF_SAMPLED_VALUE][STRING_20_TYPE_LENGTH + 1], unit_buf[NUMBER_OF_SAMPLED_VALUE][STRING_20_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;

    rreq.id_tag = id_tag_buf ;
    rreq.meter_stop = 10 ;
    rreq.timestamp = ts_buf ;
    rreq.transaction_id = make_transaction_id() ;
    rreq.reason = reason_buf ;
    rreq.number_of_transaction_data = NUMBER_OF_TRANSACTION_DATA ;

    strcpy(id_tag_buf, "charlie") ;
    get_future_date(ts_buf, 0) ;
    strcpy(reason_buf, reason_values[reason_local]) ;

    rreq.transaction_data = rmv ;
    prmv = rreq.transaction_data ;
    for(int i = 0 ; i < NUMBER_OF_TRANSACTION_DATA ; i++, prmv++) {
        prmv->timestamp = timestamp_buf[i] ;
        prmv->number_of_sampled_value = NUMBER_OF_SAMPLED_VALUE ;
        
        prmv->sampled_value = rsv ;
        prsv = prmv->sampled_value ;
        for(int j = 0 ; j < NUMBER_OF_SAMPLED_VALUE ; j++, prsv++) {
            prsv->value = value_buf[j] ;
            prsv->context = context_buf[j] ;
            prsv->format = format_buf[j] ;
            prsv->measurand = measurand_buf[j] ;
            prsv->phase = phase_buf[j] ;
            prsv->location = location_buf[j] ;
            prsv->unit = unit_buf[j] ;
        }
    }

    init_raw_req_message(&rreq) ;

    make_ocpp_stop_transaction_req_message(user_data_buffer.resp_buf, message_id, &rreq) ;
    strcpy(conf_act.message_id, message_id) ;
    conf_act.func = do_start_transaction_conf ;

    return 0 ;
}

int do_stop_transaction_conf(ocpp_callresult_message *resp) {
    printf("do stop transaction conf : %s\n", resp->payload) ;
    return 0 ;
}

int do_stop_transaction_error(ocpp_callerror_message *msg) {
    return 0 ;    
}
