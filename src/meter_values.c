#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_meter_values_req_message() {
    meter_val_req.connector_id.key = meter_values_req_field_names[meter_values_req_connector_id] ;
    // value 는 integer 이므로 initialize 할 필요가 없슴.

    meter_val_req.transaction_id.key = meter_values_req_field_names[meter_values_req_transaction_id] ;
    meter_val_req.transaction_id.val.int_val = -1 ;
    // optional 이므로 -1로 initialize 

    meter_val_req.meter_value.key = meter_values_req_field_names[meter_values_req_meter_value] ;
    // meter_value는 array이고 init 시점에서 array size를 알 수 없으므로 지금 initialize할 수 없다.
}

void init_meter_values_conf_message() {}

int make_ocpp_meter_values_req_message(char *buf, char *message_id, raw_meter_values_req *rreq) {
    ocpp_call_message message ;
    json_object *object, *arr_mv, *arr_sv, *mv, *sv, *value ;
    meter_value *meter_value_ptr ;
    sampled_value *sampled_value_ptr ;
    raw_meter_value *rmvptr ;
    raw_sampled_value *rsvptr ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[METER_VALUES_INDEX].action ;

    meter_val_req.connector_id.key = meter_values_req_field_names[meter_values_req_connector_id] ;
    meter_val_req.connector_id.val.int_val = rreq->connector_id ;

    meter_val_req.transaction_id.key = meter_values_req_field_names[meter_values_req_transaction_id] ;
    meter_val_req.transaction_id.val.int_val = rreq->transaction_id ;

    meter_val_req.meter_value.key = meter_values_req_field_names[meter_values_req_meter_value] ;
    meter_val_req.meter_value.val.mtr_val = (meter_value *)malloc(rreq->number_of_meter_value * sizeof(meter_value)) ;
    meter_value_ptr = meter_val_req.meter_value.val.mtr_val ;
    rmvptr = rreq->meter_value ;

    for(int i = 0 ; i < rreq->number_of_meter_value ; i++, meter_value_ptr++, rmvptr++) {
        meter_value_ptr->timestamp.key = meter_value_field_names[meter_value_timestamp] ;
        meter_value_ptr->timestamp.val.str_val = rmvptr->timestamp ;

        meter_value_ptr->sampled_value.key = meter_value_field_names[meter_value_sampled_value] ;
        meter_value_ptr->sampled_value.val.samp_val = (sampled_value *)malloc(rmvptr->number_of_sampled_value * sizeof(sampled_value)) ;

        sampled_value_ptr = meter_value_ptr->sampled_value.val.samp_val ;
        rsvptr = rmvptr->sampled_value ;
        for(int j = 0 ; j < rreq->meter_value->number_of_sampled_value ; j++, sampled_value_ptr++, rsvptr++) {
            sampled_value_ptr->value.key = sampled_value_field_names[sampled_value_value] ;
            sampled_value_ptr->value.val.str_val = rsvptr->value ;

            sampled_value_ptr->context.key = sampled_value_field_names[sampled_value_context] ;
            sampled_value_ptr->context.val.str_val = rsvptr->context ;

            sampled_value_ptr->format.key = sampled_value_field_names[sampled_value_format] ;
            sampled_value_ptr->format.val.str_val = rsvptr->format ;

            sampled_value_ptr->measurand.key = sampled_value_field_names[sampled_value_measurand] ;
            sampled_value_ptr->measurand.val.str_val = rsvptr->measurand ;

            sampled_value_ptr->phase.key = sampled_value_field_names[sampled_value_phase] ;
            sampled_value_ptr->phase.val.str_val = rsvptr->phase ;

            sampled_value_ptr->location.key = sampled_value_field_names[sampled_value_location] ;
            sampled_value_ptr->location.val.str_val = rsvptr->location ;

            sampled_value_ptr->unit.key = sampled_value_field_names[sampled_value_unit] ;
            sampled_value_ptr->unit.val.str_val = rsvptr->unit ;
        }
    }

    object = json_object_new_object() ;
    json_object_object_add(object, meter_val_req.connector_id.key, json_object_new_int(meter_val_req.connector_id.val.int_val)) ;

    if(meter_val_req.transaction_id.val.int_val != -1)
        json_object_object_add(object, meter_val_req.transaction_id.key, json_object_new_int(meter_val_req.transaction_id.val.int_val)) ;
    
    arr_mv = json_object_new_array_ext(rreq->number_of_meter_value) ;

    meter_value_ptr = meter_val_req.meter_value.val.mtr_val ;
    for(int i = 0 ; i < rreq->number_of_meter_value ; i++, meter_value_ptr++) {
        mv = json_object_new_object() ;

        value = json_object_new_string(meter_value_ptr->timestamp.val.str_val) ;
        json_object_object_add(mv, meter_value_ptr->timestamp.key, value) ;

        arr_sv = json_object_new_array_ext(rreq->meter_value->number_of_sampled_value) ;
        sampled_value_ptr = meter_value_ptr->sampled_value.val.samp_val ;
        for(int j = 0 ; j < rreq->meter_value->number_of_sampled_value ; j++, sampled_value_ptr++) {
            sv = json_object_new_object() ;

            value = json_object_new_string(sampled_value_ptr->value.val.str_val) ;
            json_object_object_add(sv, sampled_value_ptr->value.key, value) ;

            if(sampled_value_ptr->context.val.str_val != NULL) {
                value = json_object_new_string(sampled_value_ptr->context.val.str_val) ;
                json_object_object_add(sv, sampled_value_ptr->context.key, value) ;
            }

            if(sampled_value_ptr->format.val.str_val != NULL) {
                value = json_object_new_string(sampled_value_ptr->format.val.str_val) ;
                json_object_object_add(sv, sampled_value_ptr->format.key, value) ;
            }

            if(sampled_value_ptr->measurand.val.str_val != NULL) {
                value = json_object_new_string(sampled_value_ptr->measurand.val.str_val) ;
                json_object_object_add(sv, sampled_value_ptr->measurand.key, value) ;
            }

            if(sampled_value_ptr->phase.val.str_val != NULL) {
                value = json_object_new_string(sampled_value_ptr->phase.val.str_val) ;
                json_object_object_add(sv, sampled_value_ptr->phase.key, value) ;
            }

            if(sampled_value_ptr->location.val.str_val != NULL) {
                value = json_object_new_string(sampled_value_ptr->location.val.str_val) ;
                json_object_object_add(sv, sampled_value_ptr->location.key, value) ;
            }

            if(sampled_value_ptr->unit.val.str_val != NULL) {
                value = json_object_new_string(sampled_value_ptr->unit.val.str_val) ;
                json_object_object_add(sv, sampled_value_ptr->unit.key, value) ;
            }

            json_object_array_add(arr_sv, sv) ;
        }

        json_object_object_add(mv, meter_value_ptr->sampled_value.key, arr_sv) ;
        json_object_array_add(arr_mv, mv) ;
    }

    json_object_object_add(object, meter_val_req.meter_value.key, arr_mv) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_meter_values_conf_message(char *buf, char *message_id) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    object = json_object_new_object() ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    return 0 ;
}


/*
 * allcation 한 모든 memory는 사용이 끝나면 반드시 free 해줘야함.
 */
int parse_ocpp_meter_values_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *arr_mv, *arr_sv, *mv, *sv, *value ;
    meter_value *meter_value_ptr ;
    sampled_value *sampled_value_ptr ;
    int mv_len, sv_len ;

    value = json_object_object_get(object, meter_val_req.connector_id.key) ;
    meter_val_req.connector_id.val.int_val = json_object_get_int(value) ;

    value = json_object_object_get(object, meter_val_req.transaction_id.key) ;
    if(value != NULL)
        meter_val_req.transaction_id.val.int_val = json_object_get_int(value) ;

    arr_mv = json_object_object_get(object, meter_val_req.meter_value.key) ;
    mv_len = json_object_array_length(arr_mv) ;
    meter_val_req.number_of_meter_value = mv_len ;

    meter_val_req.meter_value.val.mtr_val = (meter_value *)malloc(mv_len * sizeof(meter_value)) ;
    meter_value_ptr = meter_val_req.meter_value.val.mtr_val ;

    for(int i = 0 ; i < mv_len ; i++, meter_value_ptr++) {
        mv = json_object_array_get_idx(arr_mv, i) ;

        meter_value_ptr->timestamp.val.str_val = (char *)malloc(DATE_TIME_LENGTH + 1) ;
    
        /*
         * init_meter_values_req_message 에서 array size를 몰라서 initialize 못허였으므로 지금 해줘야함.
         */
        meter_value_ptr->timestamp.key = meter_value_field_names[meter_value_timestamp] ;
        value = json_object_object_get(mv, meter_value_ptr->timestamp.key) ;
        strcpy(meter_value_ptr->timestamp.val.str_val, json_object_get_string(value)) ;

        meter_value_ptr->sampled_value.key = meter_value_field_names[meter_value_sampled_value] ;
        arr_sv = json_object_object_get(mv, meter_value_ptr->sampled_value.key) ;
        sv_len = json_object_array_length(arr_sv) ;

        meter_value_ptr->number_of_sampled_value = sv_len ;

        meter_value_ptr->sampled_value.val.samp_val = (sampled_value *)malloc(sv_len * sizeof(sampled_value)) ;
        sampled_value_ptr = meter_value_ptr->sampled_value.val.samp_val ;
        for(int j = 0 ; j < sv_len ; j++, sampled_value_ptr++) {
            sampled_value_ptr->value.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;

            sv = json_object_array_get_idx(arr_sv, j) ;

            sampled_value_ptr->value.key = sampled_value_field_names[sampled_value_value] ;
            value = json_object_object_get(sv, sampled_value_ptr->value.key) ;
            strcpy(sampled_value_ptr->value.val.str_val, json_object_get_string(value)) ;

            sampled_value_ptr->context.key = sampled_value_field_names[sampled_value_context] ;
            value = json_object_object_get(sv, sampled_value_ptr->context.key) ;
            if(value != NULL) {
                sampled_value_ptr->context.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH +1) ;
                strcpy(sampled_value_ptr->context.val.str_val, json_object_get_string(value)) ;
            }
            else
                sampled_value_ptr->context.val.str_val = NULL ;

            sampled_value_ptr->format.key = sampled_value_field_names[sampled_value_format] ;
            value = json_object_object_get(sv, sampled_value_ptr->format.key) ;
            if(value != NULL) {
                sampled_value_ptr->format.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;
                strcpy(sampled_value_ptr->format.val.str_val, json_object_get_string(value)) ;
            }
            else
                sampled_value_ptr->format.val.str_val = NULL ;

            sampled_value_ptr->measurand.key = sampled_value_field_names[sampled_value_measurand] ;
            value = json_object_object_get(sv, sampled_value_ptr->measurand.key) ;
            if(value != NULL) {
                sampled_value_ptr->measurand.val.str_val = (char *)malloc(STRING_50_TYPE_LENGTH + 1) ;
                strcpy(sampled_value_ptr->measurand.val.str_val, json_object_get_string(value)) ;
            }
            else
                sampled_value_ptr->measurand.val.str_val = NULL ;

            sampled_value_ptr->phase.key = sampled_value_field_names[sampled_value_phase] ;
            value = json_object_object_get(sv, sampled_value_ptr->phase.key) ;
            if(value != NULL) {
                sampled_value_ptr->phase.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;
                strcpy(sampled_value_ptr->phase.val.str_val, json_object_get_string(value)) ;
            }
            else
                sampled_value_ptr->phase.val.str_val = NULL ;

            sampled_value_ptr->location.key = sampled_value_field_names[sampled_value_location] ;
            value = json_object_object_get(sv, sampled_value_ptr->location.key) ;
            if(value != NULL) {
                sampled_value_ptr->location.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;
                strcpy(sampled_value_ptr->location.val.str_val, json_object_get_string(value)) ;
            }
            else
                sampled_value_ptr->location.val.str_val = NULL ;

            sampled_value_ptr->unit.key = sampled_value_field_names[sampled_value_unit] ;
            value = json_object_object_get(sv, sampled_value_ptr->unit.key) ;
            if(value != NULL) {
                sampled_value_ptr->unit.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;
                strcpy(sampled_value_ptr->unit.val.str_val, json_object_get_string(value)) ;
            }
            else
                sampled_value_ptr->unit.val.str_val = NULL ;
        }
    }

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_meter_values_conf_message(char *data) {
    return 0 ;
}

/*
 * file에서 JSON 형식의 request를 읽어와 처리함
 */
int do_meter_values_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_meter_values_req rreq ;
    FILE *file = fopen(ppcommand[1], "r") ;
    if(file == NULL) {
        printf("Error opening file : %s", ppcommand[1]) ;
        return -1 ;
    }

    fseek(file, 0, SEEK_END) ;
    long file_size = ftell(file) ;
    rewind(file) ;

    char *buff = (char *)malloc(sizeof(char) * (file_size + 1)) ;

    fread(buff, sizeof(char), file_size, file) ;
    buff[file_size] = 0x00 ;
    fclose(file) ;

    make_message_id(message_id) ;
    sprintf(user_data_buffer.resp_buf, "[%d, \"%s\", \"%s\", %s]", MESSAGE_TYPE_CALL, message_id, charge_point_initiated_actions[METER_VALUES_INDEX].action, buff) ;

    free(buff) ;

    conf_act.func = do_meter_values_conf ;
    strcpy(conf_act.message_id, message_id) ;
    
    return 0 ;
}

int do_meter_values_conf(ocpp_callresult_message *msg) {
    return 0 ;
}

int do_meter_values_error(ocpp_callerror_message *msg) {
    return 0 ;    
}

