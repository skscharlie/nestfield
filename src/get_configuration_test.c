#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <json.h>
#include "ocpp.h"

#define NUMBER_OF_KEY                   5
#define NUMBER_OF_CONFIGURATION_KEY     3
#define NUMBER_OF_UNKNOWN_KEY           2

int proc_get_configuration_req(char *req, char *resp) ;

int get_configuration_test() { 
    ocpp_callresult_message msg ;
    raw_get_configuration_req rreq ;
    key_value *pkv ;
    char **ppstr ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    char key_buf[NUMBER_OF_KEY][STRING_50_TYPE_LENGTH + 1] ;
    char *pkey[NUMBER_OF_KEY] ;

    make_message_id(message_id) ;

    rreq.key = pkey ;
    for(int i = 0 ; i < NUMBER_OF_KEY ; i++) 
        pkey[i] = key_buf[i] ;

    rreq.number_of_key = NUMBER_OF_KEY ;
    strcpy(key_buf[0], "abcdefghijklmn") ;
    strcpy(key_buf[1], "1234567890") ;
    strcpy(key_buf[2], ";lakdfj;adkfjad") ;
    strcpy(key_buf[3], "1244kdfjlhsdf0988") ;
    strcpy(key_buf[4], "mcnfndkfy;dfie8") ;
    make_ocpp_get_configuration_req_message(req_buf, message_id, &rreq) ;

    proc_get_configuration_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_get_configuration_conf_message() ;
    parse_ocpp_get_configuration_conf_message(msg.payload) ;

    pkv = get_config_conf.configuration_key.val.kv_val ;
    for(int i = 0 ; i < get_config_conf.number_of_configuration_key ; i++, pkv++) {
        printf("key : %s.%s, value : %s\n", get_config_conf.configuration_key.key, pkv->key.key, pkv->key.val.str_val) ;
        printf("key : %s.%s, value : %s\n", get_config_conf.configuration_key.key, pkv->readonly.key, (pkv->readonly.val.b_val == true) ? "true" : "false") ;
        printf("key : %s.%s, value : %s\n", get_config_conf.configuration_key.key, pkv->value.key, pkv->value.val.str_val) ;
    }

    ppstr = get_config_conf.unknown_key.val.ppstr_val ;
    for(int i = 0 ; i < get_config_conf.number_of_unknown_key ; i++, ppstr++) {
        printf("key : %s, value : %s\n", get_config_conf.unknown_key.key, *ppstr) ;
    }

    // free allocated memory
    pkv = get_config_conf.configuration_key.val.kv_val ;
    for(int i = 0 ; i < get_config_conf.number_of_configuration_key ; i++, pkv++) {
        free(pkv->key.val.str_val) ;
        free(pkv->value.val.str_val) ;
    }

    ppstr = get_config_conf.unknown_key.val.ppstr_val ;
    for(int i = 0 ; i < get_config_conf.number_of_unknown_key ; i++, ppstr++) {
        free(*ppstr) ;
    }

    free(get_config_conf.configuration_key.val.kv_val) ;
    free(get_config_conf.unknown_key.val.ppstr_val) ;

    return 0 ;
}

int proc_get_configuration_req(char *req, char *resp) {
    ocpp_call_message msg ;
    raw_get_configuration_conf rconf ;
    char *key[NUMBER_OF_CONFIGURATION_KEY], *unkey[NUMBER_OF_UNKNOWN_KEY], *value[NUMBER_OF_CONFIGURATION_KEY] ;
    char unknown_key_buf[NUMBER_OF_UNKNOWN_KEY][STRING_50_TYPE_LENGTH + 1] ;
    raw_key_value rkv[NUMBER_OF_CONFIGURATION_KEY] ;
    char key_buf[NUMBER_OF_CONFIGURATION_KEY][STRING_50_TYPE_LENGTH +1], value_buf[NUMBER_OF_CONFIGURATION_KEY][STRING_500_TYPE_LENGTH + 1] ;

    parse_req_message(req, &msg) ;
    init_get_configuration_req_message() ;
    parse_ocpp_get_configuration_req_message(msg.payload) ;

    strcpy(unknown_key_buf[0], get_config_req.key.val.ppstr_val[0]) ;
    strcpy(unknown_key_buf[1], get_config_req.key.val.ppstr_val[3]) ;
    rconf.unknown_key = unkey ;
    for(int i = 0 ; i < NUMBER_OF_UNKNOWN_KEY ; i++)
        unkey[i] = unknown_key_buf[i] ;

    rconf.configuration_key = rkv ;
    for(int i = 0 ; i < NUMBER_OF_CONFIGURATION_KEY ; i++) {
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
    
    rconf.number_of_configuration_key = NUMBER_OF_CONFIGURATION_KEY ;
    rconf.number_of_unknown_key = NUMBER_OF_UNKNOWN_KEY ;

    // free allocated memory
    free(get_config_req.key.val.ppstr_val) ;

    make_ocpp_get_configuration_conf_message(resp, msg.message_id, &rconf) ;
    return 0 ;
}
