#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include "ocpp.h"

int proc_data_transfer_req(char *req, char *resp) ;
char *data = "During downloading and installation of the firmware, the Charge Point MUST send FirmwareStatusNotification.req "
             " PDUs to keep the Central System updated with the status of the update process."
             "The Charge Point SHALL, if the new firmware image is \"valid\", install the new firmware as soon as it is able to."
             "If it is not possible to continue charging during installation of firmware, it is RECOMMENDED to wait until "
             "Charging Session has ended (Charge Point idle) before commencing installation. It is RECOMMENDED to set connectors "
             "that are not in use to UNAVAILABLE while the Charge Point waits for the Session to end." ;

int data_transfer_test() { 
    ocpp_callresult_message msg ;
    char req_buf[1024], resp_buf[1024], message_id[MESSAGE_ID_LENGTH + 1] ;
    raw_data_transfer_req rreq ;
    char vendor_id_buf[STRING_255_TYPE_LENGTH + 1], message_id_buf[STRING_50_TYPE_LENGTH + 1] ;

    make_message_id(message_id) ;

    rreq.vendor_id = vendor_id_buf ;
    rreq.message_id = message_id_buf ;
    rreq.data = data ;

    strcpy(vendor_id_buf, "charlie") ;
    make_message_id(message_id_buf) ;

    make_ocpp_data_transfer_req_message(req_buf, message_id, &rreq) ;
    proc_data_transfer_req(req_buf, resp_buf) ;

    parse_conf_message(resp_buf, &msg) ;
    init_data_transfer_conf_message() ;
    parse_ocpp_data_transfer_conf_message(msg.payload) ;

    printf("key : %s, value : %s\n", data_trans_conf.status.key, data_trans_conf.status.val.str_val) ;
    printf("key : %s, value : %s\n", data_trans_conf.data.key, data_trans_conf.data.val.str_val) ;

    free(data_trans_conf.data.val.str_val) ;

    return 0 ;
}

int proc_data_transfer_req(char *req, char *resp) {
    ocpp_call_message msg ;
    raw_data_transfer_conf rconf ;

    parse_req_message(req, &msg) ;
    init_data_transfer_req_message() ;
    parse_ocpp_data_transfer_req_message(msg.payload) ;

    free(data_trans_req.data.val.str_val) ;

    rconf.status = data_transfer_status_values[data_transfer_status_accepted] ;
    rconf.data = data ;

    make_ocpp_data_transfer_conf_message(resp, msg.message_id, &rconf) ;

    return 0 ;
}
