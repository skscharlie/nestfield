#ifndef OCPP_ACTIONS_H
#define OCPP_ACTIONS_H

#include "ocpp.h"

typedef struct _receive_req_actions_ {
    char *action ;
    int (*func)(ocpp_call_message *, char *) ;
} receive_req_actions ;

typedef struct _send_req_actions_ {
    char *action ;
    int (*req_func)(char **) ;
    int (*conf_func)(ocpp_callresult_message *) ;
    int (*conf_error_func)(ocpp_callerror_message *) ;
} send_req_actions ;

typedef struct _field_buffers_ {
    char *field_name ;
    union {
        char *buffer ;
        int ival ;
        double dval ;
    } val ;
} field_buffers ;

/*
 * Central system에서 conf message가 왔을때 어떤 message id에 대한 conf이고
 * cont message 처리 함수를 미리 setting하기 위한 sturcture
 */

typedef struct _conf_actions_ {
    char message_id[MESSAGE_ID_LENGTH + 1] ;
    int (*func)(ocpp_callresult_message *) ;
} conf_actions ;

/*
 * terminal에서 input을 받아 처리하기 위한 structure.
 * field에 optional 값이 있으므로 number of command 가 필요함
 */
typedef struct {
    char **ppcommand ;
    int number_of_command ;
} input_command ;

#endif