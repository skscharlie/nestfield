#ifndef SECC_ACTIONS_H
#define SECC_ACTIONS_H

typedef struct {
    int secc_action ;
    int number_of_ocpp_actions ;
    char *ocpp_actions[5] ;
} secc_ocpp_actions ;

struct ocpp_comm_buff {
    int command ;
    int connector_id ;
    char data[128] ;
} ;

#endif