#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

#define NUMBER_OF_TRANSACTION_DATA       2
#define NUMBER_OF_SAMPLED_VALUE     2

int proc_stop_transaction_req(char *req, char *resp) ;

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

int stop_transaction_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
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

    make_ocpp_stop_transaction_req_message(req_buf, message_id, &rreq) ;

    proc_stop_transaction_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_stop_transaction_conf_message() ;
    parse_ocpp_stop_transaction_conf_message(msg.payload) ;

    return 0 ;
}

int proc_stop_transaction_req(char *req, char *resp) {
    ocpp_call_message msg ;
    meter_value *mv ;
    sampled_value *sv ;
    raw_stop_transaction_conf rconf ;
    raw_id_tag_info riti ;
    char expiry_date_buf[DATE_TIME_LENGTH + 1], parent_id_tag_buf[STRING_20_TYPE_LENGTH + 1], status_buf[STRING_20_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_stop_transaction_req_message() ;
    parse_ocpp_stop_transaction_req_message(msg.payload) ;

    /* free allocated memory */
    mv = stop_trans_req.transaction_data.val.mtr_val ;
    for(int i = 0 ; i < stop_trans_req.number_of_transaction_data ; i++, mv++) {
        sv = mv->sampled_value.val.samp_val ;
        for(int j = 0 ; j < mv->number_of_sampled_value ; j++, sv++) {
            free(sv->value.val.str_val) ;
            free(sv->context.val.str_val) ;
            free(sv->format.val.str_val) ;
            free(sv->measurand.val.str_val) ;
            free(sv->phase.val.str_val) ;
            free(sv->location.val.str_val) ;
            free(sv->unit.val.str_val) ;
        }

        free(mv->sampled_value.val.samp_val) ;
        free(mv->timestamp.val.str_val) ;
    }

    free(stop_trans_req.transaction_data.val.mtr_val) ;

    rconf.id_tag_info = &riti ;
    rconf.id_tag_info->expiry_date = expiry_date_buf ;
    rconf.id_tag_info->parent_id_tag = parent_id_tag_buf ;
    rconf.id_tag_info->status = status_buf ;

    get_future_date(expiry_date_buf, 30) ;
    strcpy(parent_id_tag_buf, "charlies parent") ;
    strcpy(status_buf, authorization_status_values[authorization_status_accepted]) ;

    make_ocpp_stop_transaction_conf_message(resp, msg.message_id, &rconf) ;

    return 0 ;
}
