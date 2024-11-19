#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_authorize_req_message() {
    auth_req.id_tag.key = authorization_data_field_names[authorization_data_id_tag] ;
    auth_req.id_tag.val.str_val = ac_id_tag ;
}

void init_authorize_conf_message() {
    auth_conf.id_tag_info.key = authorization_data_field_names[authorization_data_id_tag_info] ;
    auth_conf.id_tag_info.val.iti_val = &id_tag_inf ;

    auth_conf.id_tag_info.val.iti_val->expiry_date.key = id_tag_info_field_names[id_tag_info_expiry_date] ;
    auth_conf.id_tag_info.val.iti_val->expiry_date.val.str_val = iti_expiry_date ;

    auth_conf.id_tag_info.val.iti_val->parent_id_tag.key = id_tag_info_field_names[id_tag_info_parient_id_tag] ;
    auth_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val = iti_parent_id_tag ;

    auth_conf.id_tag_info.val.iti_val->status.key = id_tag_info_field_names[id_tag_info_status] ;
    auth_conf.id_tag_info.val.iti_val->status.val.str_val = iti_status ;
}

int make_ocpp_authorize_req_message(char* buf, char* message_id, char* id_tag_val) {
    ocpp_call_message message ;
    json_object *object, *val ;

    /*
     * authorize req
    */

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = charge_point_initiated_actions[AUTHORIZE_INDEX].action ;

    auth_req.id_tag.key = authorization_req_field_names[authorization_req_id_tag] ;
    auth_req.id_tag.val.str_val = id_tag_val ;

    message.payload = (char *)&auth_req ;

    object = json_object_new_object() ;
    val = json_object_new_string(auth_req.id_tag.val.str_val) ;
    json_object_object_add(object, auth_req.id_tag.key, val) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;

    return 0 ;
}

int make_ocpp_authorize_conf_message(char* buf, char* message_id, raw_id_tag_info* rinfo) {
    ocpp_callresult_message message ;
    json_object *main_object, *main_val ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    id_tag_inf.expiry_date.key = id_tag_info_field_names[id_tag_info_expiry_date] ;
    id_tag_inf.expiry_date.val.str_val = rinfo->expiry_date ;

    id_tag_inf.parent_id_tag.key = id_tag_info_field_names[id_tag_info_parient_id_tag] ;
    id_tag_inf.parent_id_tag.val.str_val = rinfo->parent_id_tag ;

    id_tag_inf.status.key = id_tag_info_field_names[id_tag_info_status] ;
    id_tag_inf.status.val.str_val = rinfo->status ;
   
    auth_conf.id_tag_info.key = authorization_conf_field_names[authorization_conf_id_tag_info] ;
    auth_conf.id_tag_info.val.iti_val = &id_tag_inf ;

    message.payload = (char *)&auth_conf ;

    main_object = json_object_new_object() ;
    main_val = json_object_new_object() ;
    json_object_object_add(main_val, id_tag_inf.expiry_date.key, json_object_new_string(id_tag_inf.expiry_date.val.str_val)) ;
    json_object_object_add(main_val, id_tag_inf.parent_id_tag.key, json_object_new_string(id_tag_inf.parent_id_tag.val.str_val)) ;
    json_object_object_add(main_val, id_tag_inf.status.key, json_object_new_string(id_tag_inf.status.val.str_val)) ;

    json_object_object_add(main_object, auth_conf.id_tag_info.key, main_val) ;

    printf("result json : %s\n", json_object_to_json_string(main_object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(main_object)) ;
    printf("result message : %s\n", buf) ;
    json_object_put(main_object) ;

    return 0 ;
}

int parse_ocpp_authorize_req_message(char* data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, auth_req.id_tag.key) ;
    strcpy(auth_req.id_tag.val.str_val, (char *)json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_authorize_conf_message(char* data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;
    char path[32] ;
 
    sprintf(path, "/%s/%s", auth_conf.id_tag_info.key, auth_conf.id_tag_info.val.iti_val->expiry_date.key) ;
    if(json_pointer_get(object, path, &value) == 0) { 
        strcpy(auth_conf.id_tag_info.val.iti_val->expiry_date.val.str_val, (char *)json_object_get_string(value)) ;
    }
    else
        auth_conf.id_tag_info.val.iti_val->expiry_date.val.str_val = NULL ;

    sprintf(path, "/%s/%s", auth_conf.id_tag_info.key, auth_conf.id_tag_info.val.iti_val->parent_id_tag.key) ;
    if(json_pointer_get(object, path, &value) == 0)
        strcpy(auth_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val, (char *)json_object_get_string(value)) ;
    else
        auth_conf.id_tag_info.val.iti_val->parent_id_tag.val.str_val = NULL ;

    sprintf(path, "/%s/%s", auth_conf.id_tag_info.key, auth_conf.id_tag_info.val.iti_val->status.key) ;
    if(json_pointer_get(object, path, &value) == 0)
        strcpy(auth_conf.id_tag_info.val.iti_val->status.val.str_val, (char *)json_object_get_string(value)) ;
    else
        auth_conf.id_tag_info.val.iti_val->status.val.str_val = NULL ;

    json_object_put(object) ;
    return 0 ;
}

/*
 * ppcommand[0] : Authorize, ppcommand[1] : id_tag
 */
int do_authorize_req(char **ppcommand) {
    char message_id[MESSAGE_ID_LENGTH + 1] ;

    make_message_id(message_id) ;
    strcpy(ac_id_tag, ppcommand[1]) ;
    make_ocpp_authorize_req_message(user_data_buffer.resp_buf, message_id, ac_id_tag) ;
    strcpy(conf_act.message_id, message_id) ;
    conf_act.func = do_authorize_conf ;

    return 0 ;
} 

int do_authorize_conf(ocpp_callresult_message *resp) {
    printf("do authorize conf : %s\n", resp->payload) ;
    return 0 ;
}

int do_authorize_conf_error(ocpp_callerror_message *error) {
    return 0 ;
}
