#include <stdio.h>
#include <string.h>
#include <json.h>
#include "ocpp.h"

/*
 * 상대방에서 받은 json메시지를 parsing할 때 json library의 특성상 library에서 return 받은 char * 는 
 * json_object_put 을 했을 때 memory가 free가 되어 사용할 수 없게 됨
 * 그래서 미리 buffer를 잡아 놓고 copy 해서 사용해야하므로 initialize를 함.
 */
void init_send_local_list_req_message() {
    send_local_lst_req.list_version.key = send_local_list_req_field_names[send_local_list_req_list_version] ;
    //value type 이 integer이므로 initialize할 필요가 없슴.

    send_local_lst_req.local_authorization_list.key = send_local_list_req_field_names[send_local_list_req_local_authorization_list] ;
    //authorization list array 의 size를 모르므로 아직 initialize할 수 있는 상태가 아님

    send_local_lst_req.update_type.key = send_local_list_req_field_names[send_local_list_req_update_type] ;
    send_local_lst_req.update_type.val.str_val = sllr_update_type ;
}

void init_send_local_list_conf_message() {
    send_local_lst_conf.status.key = send_local_list_conf_field_name[send_local_list_conf_status] ;
    send_local_lst_conf.status.val.str_val = sllc_status ;
}

int make_ocpp_send_local_list_req_message(char *buf, char *message_id, raw_send_local_list_req *rreq) {
    ocpp_call_message message ;
    json_object *object, *lal, *joad, *joiti ;
    authorization_data *ad ;
    raw_authorization_data *rad ;
    id_tag_info *iti_buf ;
    int i ;

    message.message_type = MESSAGE_TYPE_CALL ;
    message.message_id = message_id ;
    message.action = central_system_initiated_actions[SEND_LOCAL_LIST_INDEX].action ;

    send_local_lst_req.list_version.key = send_local_list_req_field_names[send_local_list_req_list_version] ;
    send_local_lst_req.list_version.val.int_val = rreq->list_version ;

    if(rreq->number_of_authorization_data > 0) {
        send_local_lst_req.local_authorization_list.key = send_local_list_req_field_names[send_local_list_req_local_authorization_list] ;
        // authorization data pointer를 가지는 array size만큼 memeory 할당
        send_local_lst_req.local_authorization_list.val.autho_data = (authorization_data *)malloc(rreq->number_of_authorization_data * sizeof(authorization_data)) ;
        iti_buf = (id_tag_info *)malloc(rreq->number_of_authorization_data * sizeof(id_tag_info)) ;

        ad = send_local_lst_req.local_authorization_list.val.autho_data ;
        rad = rreq->local_authorization_list ;
        for(i = 0 ; i < rreq->number_of_authorization_data ; i++, ad++, rad++) {
            ad->id_tag.key = authorization_data_field_names[authorization_data_id_tag] ;
            ad->id_tag.val.str_val = rad->id_tag ;

            if(rad->id_tag_info != NULL) {
                ad->id_tag_info.key = authorization_data_field_names[authorization_data_id_tag_info] ;
                ad->id_tag_info.val.iti_val = &iti_buf[i] ;
                ad->id_tag_info.val.iti_val->expiry_date.key = id_tag_info_field_names[id_tag_info_expiry_date] ;
                ad->id_tag_info.val.iti_val->expiry_date.val.str_val = rad->id_tag_info->expiry_date ;

                ad->id_tag_info.val.iti_val->parent_id_tag.key = id_tag_info_field_names[id_tag_info_parient_id_tag] ;
                ad->id_tag_info.val.iti_val->parent_id_tag.val.str_val = rad->id_tag_info->parent_id_tag ;

                ad->id_tag_info.val.iti_val->status.key = id_tag_info_field_names[id_tag_info_status] ;
                ad->id_tag_info.val.iti_val->status.val.str_val = rad->id_tag_info->status ;
            }
        }
    }

    send_local_lst_req.update_type.key = send_local_list_req_field_names[send_local_list_req_update_type] ;
    send_local_lst_req.update_type.val.str_val = rreq->update_type ;

    object = json_object_new_object() ;
    json_object_object_add(object, send_local_lst_req.list_version.key, json_object_new_int(send_local_lst_req.list_version.val.int_val)) ;

    ad = send_local_lst_req.local_authorization_list.val.autho_data ;
    lal = json_object_new_array_ext(rreq->number_of_authorization_data) ;
    for(i = 0 ; i < rreq->number_of_authorization_data ; i++, ad++) {
        joad = json_object_new_object() ;
        json_object_object_add(joad, ad->id_tag.key, json_object_new_string(ad->id_tag.val.str_val)) ;

        joiti = json_object_new_object() ;
        json_object_object_add(joiti, ad->id_tag_info.val.iti_val->expiry_date.key, json_object_new_string(ad->id_tag_info.val.iti_val->expiry_date.val.str_val)) ;
        json_object_object_add(joiti, ad->id_tag_info.val.iti_val->parent_id_tag.key, json_object_new_string(ad->id_tag_info.val.iti_val->parent_id_tag.val.str_val)) ;
        json_object_object_add(joiti, ad->id_tag_info.val.iti_val->status.key, json_object_new_string(ad->id_tag_info.val.iti_val->status.val.str_val)) ;

        json_object_object_add(joad, ad->id_tag_info.key, joiti) ;
        json_object_array_add(lal,joad) ;
    }

    json_object_object_add(object, send_local_lst_req.local_authorization_list.key, lal) ;
    json_object_object_add(object, send_local_lst_req.update_type.key, json_object_new_string(send_local_lst_req.update_type.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", \"%s\", %s]", message.message_type, message.message_id, message.action, json_object_to_json_string(object)) ;

    json_object_put(object) ;
    free(send_local_lst_req.local_authorization_list.val.autho_data) ;
    return 0 ;
}

int make_ocpp_send_local_list_conf_message(char *buf, char *message_id, char *status) {
    ocpp_callresult_message message ;
    json_object *object ;

    message.message_type = MESSAGE_TYPE_CALLRESULT ;
    message.message_id = message_id ;

    send_local_lst_conf.status.key = send_local_list_conf_field_name[send_local_list_conf_status] ;
    send_local_lst_conf.status.val.str_val = status ;

    object = json_object_new_object() ;
    json_object_object_add(object, send_local_lst_conf.status.key, json_object_new_string(send_local_lst_conf.status.val.str_val)) ;

    printf("result json : %s\n", json_object_to_json_string(object)) ;
    sprintf(buf, "[%d, \"%s\", %s]", message.message_type, message.message_id, json_object_to_json_string(object)) ;
    json_object_put(object) ;

    return 0 ;
}

int parse_ocpp_send_local_list_req_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *arr, *value, *ad, *iti ;
    authorization_data *pauth_data ;
    int arr_len ;

    value = json_object_object_get(object, send_local_lst_req.list_version.key) ;
    send_local_lst_req.list_version.val.int_val = json_object_get_int(value) ;

    arr = json_object_object_get(object, send_local_lst_req.local_authorization_list.key) ;
    if(arr != NULL) {
        arr_len = json_object_array_length(arr) ;
        send_local_lst_req.number_of_authrization_data = arr_len ;

        /*
        * send_local_lst_req의 사용이 끝나면 반드시 send_local_lst_req.local_authorization_list.val.autho_data 를 free해 줘야 함.
        */
        send_local_lst_req.local_authorization_list.val.autho_data = (authorization_data *)malloc(arr_len * sizeof(authorization_data)) ;
        pauth_data = send_local_lst_req.local_authorization_list.val.autho_data ;

        for(int i = 0 ; i < arr_len ; i++, pauth_data++) {
            ad = json_object_array_get_idx(arr, i) ;

            pauth_data->id_tag.key = authorization_data_field_names[authorization_data_id_tag] ;
            pauth_data->id_tag.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;

            value = json_object_object_get(ad, pauth_data->id_tag.key) ;
            strcpy(pauth_data->id_tag.val.str_val, json_object_get_string(value)) ;

            pauth_data->id_tag_info.key = authorization_data_field_names[authorization_data_id_tag_info] ;
            iti = json_object_object_get(ad, pauth_data->id_tag_info.key) ;
            if(iti != NULL) {
                pauth_data->id_tag_info.key = authorization_data_field_names[authorization_data_id_tag_info] ;
                pauth_data->id_tag_info.val.iti_val = (id_tag_info *)malloc(sizeof(id_tag_info)) ;

                pauth_data->id_tag_info.val.iti_val->expiry_date.key = id_tag_info_field_names[id_tag_info_expiry_date] ;
                value = json_object_object_get(iti, pauth_data->id_tag_info.val.iti_val->expiry_date.key) ;
                if(value != NULL) {
                    pauth_data->id_tag_info.val.iti_val->expiry_date.val.str_val = (char *)malloc(DATE_TIME_LENGTH + 1) ;

                    strcpy(pauth_data->id_tag_info.val.iti_val->expiry_date.val.str_val, json_object_get_string(value)) ;
                }

                pauth_data->id_tag_info.val.iti_val->parent_id_tag.key = id_tag_info_field_names[id_tag_info_parient_id_tag] ;
                value = json_object_object_get(iti, pauth_data->id_tag_info.val.iti_val->parent_id_tag.key) ;
                if(value != NULL) {
                    pauth_data->id_tag_info.val.iti_val->parent_id_tag.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;

                    strcpy(pauth_data->id_tag_info.val.iti_val->parent_id_tag.val.str_val, json_object_get_string(value)) ;
                }

                pauth_data->id_tag_info.val.iti_val->status.key = id_tag_info_field_names[id_tag_info_status] ;
                pauth_data->id_tag_info.val.iti_val->status.val.str_val = (char *)malloc(STRING_20_TYPE_LENGTH + 1) ;

                value = json_object_object_get(iti, pauth_data->id_tag_info.val.iti_val->status.key) ;
                strcpy(pauth_data->id_tag_info.val.iti_val->status.val.str_val, json_object_get_string(value)) ;
            }
        }
    }
    else
        send_local_lst_req.number_of_authrization_data = 0 ;

    value = json_object_object_get(object, send_local_lst_req.update_type.key) ;
    strcpy(send_local_lst_req.update_type.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int parse_ocpp_send_local_list_conf_message(char *data) {
    json_object *object = json_tokener_parse(data) ;
    json_object *value ;

    value = json_object_object_get(object, send_local_lst_conf.status.key) ;
    strcpy(send_local_lst_conf.status.val.str_val, json_object_get_string(value)) ;

    json_object_put(object) ;
    return 0 ;
}

int do_send_local_list(ocpp_call_message *req, char *resp) {
    init_send_local_list_req_message() ;
    parse_ocpp_send_local_list_req_message(req->payload) ;

    make_ocpp_send_local_list_conf_message(resp, req->message_id, update_status_values[update_status_accepted]) ;
    return 0 ;
}
