#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

int proc_change_configuration_req(char *req, char *resp) ;

int change_configuration_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_change_configuration_req rreq ;
    char key_buf[STRING_50_TYPE_LENGTH + 1], value_buf[STRING_500_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;
    strcpy(key_buf, "key") ;
    strcpy(value_buf, "value") ;
    rreq.key = key_buf ;
    rreq.value = value_buf ;

    make_ocpp_change_configuration_req_message(req_buf, message_id, &rreq) ;

    proc_change_configuration_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_change_configuration_conf_message() ;
    parse_ocpp_change_configuration_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", change_config_conf.status.key, change_config_conf.status.val.str_val) ;
    
    return 0 ;
}

int proc_change_configuration_req(char *req, char *resp) {
    ocpp_call_message msg ;

    parse_req_message(req, &msg) ;
    init_change_configuration_req_message() ;
    parse_ocpp_change_configuration_req_message(msg.payload) ;

    make_ocpp_change_configuration_conf_message(resp, msg.message_id, configuration_status_values[configuration_status_accepted]) ;

    return 0 ;
}