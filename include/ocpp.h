#ifndef OCPP_H
#define OCPP_H

#include "ocpp_define.h"
#include "ocpp_types.h"
#include "ocpp_message.h"
#include "ocpp_enum.h"
#include "ocpp_actions.h"
#include "secc_define.h"
#include "secc_actions.h"
#include "ocpp_extern.h"
#include "secc_extern.h"

typedef struct {
    struct lws_context *context ;
    char *server_ip ;
} ocpp_argument ;

#endif