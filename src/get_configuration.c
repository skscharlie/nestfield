#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_get_configuration_req_message() {
    get_config_req.key.key = get_configuration_req_field_name[get_configuration_req_key] ;
    // array size를 알 수 없으므로 지금은 initialize 할 수 없슴.
}

void init_get_configuration_conf_message() {
    get_config_conf.configuration_key.key = get_configuration_conf_field_names[get_configuration_conf_configuration_key] ;
    // array size를 알 수 없으므로 지금은 initialize할 수 없슴.

    get_config_conf.unknown_key.key = get_configuration_conf_field_names[get_configuration_conf_unknown_key] ;
    // array size를 알 수 없으므로 지금은 initializwe할 수 없슴.
}

int make_ocpp_get_configuration_req_message(char *buf, char *message_id, raw_get_configuration_req *rreq) {
    ocpp_call_message message ;
    json_object *object, *arr ;
    char **pptr, **ptr ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[GET_CONFIGURATION_INDEX].action ;

    get_config_req.key.key = get_configuration_req_field_name[get_configuration_req_key] ;
    get_config_req.number_of_key = rreq->number_of_key ;
    get_config_req.key.val.ppstr_val = (char **)malloc(get_config_req.number_of_key * sizeof(char *)) ;

    pptr = get_config_req.key.val.ppstr_val ;
    ptr = rreq->key ;
    for(int i = 0 ; i < get_config_req.number_of_key ; i++, ptr++, pptr++) {
        *pptr = *ptr ;
    }

    object = json_object_new_object() ;
    arr = json_object_new_array() ;
    pptr = get_config_req.key.val.ppstr_val ;
    for(int i = 0 ; i < get_config_req.number_of_key ; i++, pptr++) {
        json_object_array_add(arr, json_object_new_string(*pptr)) ;
    }
    json_object_object_add(object, get_config_req.key.key, arr) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    free(get_config_req.key.val.ppstr_val) ;
    json_object_put(object) ;
    return 0 ;
}

int make_ocpp_get_configuration_conf_message(char *buf, char *message_id, raw_get_configuration_conf *rconf) {
    ocpp_callresult_message message ;
    json_object *object, *kv, *arr_kv, *uk, *arr_uk ;
    key_value *kv_ptr ;
    raw_key_value *rkv_ptr ;
    char **ppuk, **pruk ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    get_config_conf.configuration_key.key = get_configuration_conf_field_names[get_configuration_conf_configuration_key] ;
    get_config_conf.number_of_configuration_key = rconf->number_of_configuration_key ;
    get_config_conf.configuration_key.val.kv_val = (key_value *)malloc(get_config_conf.number_of_configuration_key * sizeof(key_value)) ;

    kv_ptr = get_config_conf.configuration_key.val.kv_val ;
    rkv_ptr = rconf->configuration_key ;
    for(int i = 0 ; i < get_config_conf.number_of_configuration_key ; i++, kv_ptr++, rkv_ptr++) {
        kv_ptr->key.key = key_value_field_names[key_value_key] ;
        kv_ptr->key.val.str_val = rkv_ptr->key ;

        kv_ptr->readonly.key = key_value_field_names[key_value_readonly] ;
        kv_ptr->readonly.val.b_val = rkv_ptr->readonly ;

        kv_ptr->value.key = key_value_field_names[key_value_value] ;
        kv_ptr->value.val.str_val = rkv_ptr->value ;
    }

    get_config_conf.unknown_key.key = get_configuration_conf_field_names[get_configuration_conf_unknown_key] ;
    get_config_conf.number_of_unknown_key = rconf->number_of_unknown_key ;
    get_config_conf.unknown_key.val.ppstr_val = (char **)malloc(get_config_conf.number_of_unknown_key * sizeof(char *)) ;

    ppuk = get_config_conf.unknown_key.val.ppstr_val ;
    pruk = rconf->unknown_key ;
    for(int i = 0 ; i < get_config_conf.number_of_unknown_key ; i++, ppuk++, pruk++) {
        *ppuk = *pruk ;
    }

    object = json_object_new_object() ;
    arr_kv = json_object_new_array_ext(get_config_conf.number_of_configuration_key) ;
    kv_ptr = get_config_conf.configuration_key.val.kv_val ;
    for(int i = 0 ; i < get_config_conf.number_of_configuration_key ; i++, kv_ptr++) {
        kv = json_object_new_object() ;
        json_object_object_add(kv, kv_ptr->key.key, json_object_new_string(kv_ptr->key.val.str_val)) ;
        json_object_object_add(kv, kv_ptr->readonly.key, json_object_new_boolean(kv_ptr->readonly.val.b_val)) ;
        json_object_object_add(kv, kv_ptr->value.key, json_object_new_string(kv_ptr->value.val.str_val)) ;

        json_object_array_add(arr_kv, kv) ;
    }

    arr_uk = json_object_new_array_ext(get_config_conf.number_of_unknown_key) ;
    ppuk = get_config_conf.unknown_key.val.ppstr_val ;
    for(int i = 0 ; i < get_config_conf.number_of_unknown_key ; i++, ppuk++) {
        json_object_array_add(arr_uk, json_object_new_string(*ppuk)) ;
    }

    json_object_object_add(object, get_config_conf.configuration_key.key, arr_kv) ;
    json_object_object_add(object, get_config_conf.unknown_key.key, arr_uk) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;

    free(get_config_conf.configuration_key.val.kv_val) ;
    free(get_config_conf.unknown_key.val.ppstr_val) ;
    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_get_configuration_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value, *arr_key ;
    char **ppk, *pval ;

    get_config_req.key.key = get_configuration_req_field_name[get_configuration_req_key] ;
    arr_key = json_object_object_get(object, get_config_req.key.key) ;

    if(arr_key != NULL) {
        get_config_req.number_of_key = json_object_array_length(arr_key) ;
        get_config_req.key.val.ppstr_val = (char **)malloc(get_config_req.number_of_key * sizeof(char *)) ;

        ppk = get_config_req.key.val.ppstr_val ;
        for(int i = 0 ; i < get_config_req.number_of_key ; i++, ppk++) {
            value = json_object_array_get_idx(arr_key, i) ;
            pval = (char *)json_object_get_string(value) ;

            *ppk = (char *)malloc(strlen(pval) + 1) ;
            strcpy(*ppk, pval) ;
        }
    }
    else {
        get_config_req.number_of_key = 0 ;
    }

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_get_configuration_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value, *kv, *arr_kv, *uk, *arr_uk ;
    key_value *kv_ptr ;
    char **ppuk ;
    const char *pval ;

    get_config_conf.configuration_key.key = get_configuration_conf_field_names[get_configuration_conf_configuration_key] ;
    arr_kv = json_object_object_get(object, get_config_conf.configuration_key.key) ;
    get_config_conf.number_of_configuration_key = json_object_array_length(arr_kv) ;
    get_config_conf.configuration_key.val.kv_val = (key_value *)malloc(get_config_conf.number_of_configuration_key * sizeof(key_value)) ;

    kv_ptr = get_config_conf.configuration_key.val.kv_val ;
    for(int i = 0 ; i < get_config_conf.number_of_configuration_key ; i++, kv_ptr++) {
        kv = json_object_array_get_idx(arr_kv, i) ;

        kv_ptr->key.key = key_value_field_names[key_value_key] ;
        value = json_object_object_get(kv, kv_ptr->key.key) ;
        pval = json_object_get_string(value) ;
        kv_ptr->key.val.str_val = (char *)malloc(strlen(pval) + 1) ;
        strcpy(kv_ptr->key.val.str_val, pval) ;

        kv_ptr->readonly.key = key_value_field_names[key_value_readonly] ;
        value = json_object_object_get(kv, kv_ptr->readonly.key) ;
        kv_ptr->readonly.val.b_val = json_object_get_boolean(value) ;

        kv_ptr->value.key = key_value_field_names[key_value_value] ;
        value = json_object_object_get(kv, kv_ptr->value.key) ;
        pval = json_object_get_string(value) ;
        kv_ptr->value.val.str_val = (char *)malloc(strlen(pval) + 1) ;
        strcpy(kv_ptr->value.val.str_val, pval) ;
    }

    get_config_conf.unknown_key.key = get_configuration_conf_field_names[get_configuration_conf_unknown_key] ;
    arr_uk = json_object_object_get(object, get_config_conf.unknown_key.key) ;
    get_config_conf.number_of_unknown_key = json_object_array_length(arr_uk) ;
    get_config_conf.unknown_key.val.ppstr_val = (char **)malloc(get_config_conf.number_of_unknown_key * sizeof(char *)) ;

    ppuk = get_config_conf.unknown_key.val.ppstr_val ;
    for(int i = 0 ; i < get_config_conf.number_of_unknown_key ; i++, ppuk++) {
        value = json_object_array_get_idx(arr_uk, i) ;
        pval = json_object_get_string(value) ;

        *ppuk = (char *)malloc(strlen(pval) + 1) ;
        strcpy(*ppuk, pval) ;
    }

    json_object_put(object) ;
    return 0 ;
}

int do_get_configuration(ocpp_call_message *req, char *resp) {
    raw_get_configuration_conf rconf ;
    char *key[3], *unkey[2], *value[3] ;
    char unknown_key_buf[2][STRING_50_TYPE_LENGTH + 1] ;
    raw_key_value rkv[3] ;
    char key_buf[3][STRING_50_TYPE_LENGTH +1], value_buf[3][STRING_500_TYPE_LENGTH + 1] ;

    init_get_configuration_req_message() ;
    parse_ocpp_get_configuration_req_message(req->payload) ;

    if(get_config_req.number_of_key == 0)
        return 0 ;

    strcpy(unknown_key_buf[0], get_config_req.key.val.ppstr_val[0]) ;
    strcpy(unknown_key_buf[1], get_config_req.key.val.ppstr_val[3]) ;
    rconf.unknown_key = unkey ;
    for(int i = 0 ; i < 2 ; i++)
        unkey[i] = unknown_key_buf[i] ;

    rconf.configuration_key = rkv ;
    for(int i = 0 ; i < 3 ; i++) {
        key[i] = key_buf[i] ;
        value[i] = value_buf[i] ;
    }

    rkv[0].key = key[0] ;
    rkv[0].readonly = true ;
    rkv[0].value = value[0] ;

    rkv[1].key = key[1] ;
    rkv[1].readonly = true ;
    rkv[1].value = value[1] ;

    rkv[2].key = key[2] ;
    rkv[2].readonly = false ;
    rkv[2].value = value[2] ;

    strcpy(key_buf[0], get_config_req.key.val.ppstr_val[1]) ;
    strcpy(key_buf[1], get_config_req.key.val.ppstr_val[2]) ;
    strcpy(key_buf[2], get_config_req.key.val.ppstr_val[4]) ;

    strcpy(value_buf[0], "configuration value 1") ;
    strcpy(value_buf[1], "configuration vlaue 2") ;
    strcpy(value_buf[2], "configuration value 3") ;
    
    rconf.number_of_configuration_key = 3 ;
    rconf.number_of_unknown_key = 2 ;

    // free allocated memory
    free(get_config_req.key.val.ppstr_val) ;

    make_ocpp_get_configuration_conf_message(resp, req->message_id, &rconf) ;
    
    return 0 ;
}
