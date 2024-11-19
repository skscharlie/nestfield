#ifndef OCPP_TYPES_H
#define OCPP_TYPES_H

#include <stdbool.h>
#include "ocpp.h"

typedef struct _message_field_ message_field ;
typedef struct _id_tag_info_ id_tag_info ;
typedef struct _charging_schedule_ charging_schedule ;
typedef struct _charging_schedule_period_ charging_schedule_period ;
typedef struct _key_value_ key_value ;
typedef struct _sampled_value_ sampled_value ;
typedef struct _charging_profile_ charging_profile ;
typedef struct _meter_value_ meter_value ;
typedef struct _authorization_data_ authorization_data ;

typedef struct _raw_charging_schedule_ raw_charging_schedule ;
typedef struct _raw_charging_schedule_period_ raw_charging_schedule_period ;
typedef struct _raw_sampled_value_ raw_sampled_value ;
typedef struct _raw_id_tag_info_ raw_id_tag_info ;

struct _message_field_ {
    char *key ;
    union {
        int int_val ;
        bool b_val ;
        float dbl_val ;
        char *str_val ;
        char **ppstr_val ;
        id_tag_info *iti_val ;
        charging_schedule *cs_val ;
        charging_schedule_period *csp_val ;
        key_value *kv_val ;
        sampled_value *samp_val ;
        meter_value *mtr_val ;
        charging_profile *chg_prof ;
        authorization_data *autho_data ;
    } val ;
} ;

struct _authorization_data_ {
    message_field id_tag ;
    message_field id_tag_info ;
} ;

typedef struct {
    char *id_tag ;
    raw_id_tag_info *id_tag_info ;
} raw_authorization_data ;

struct _charging_profile_ {
    message_field charging_profile_id ;
    message_field transaction_id ;
    message_field stack_level ;
    message_field charging_profile_purpose ;
    message_field charging_profile_kind ;
    message_field recurrency_kind ;
    message_field valid_from ;
    message_field valid_to ;
    message_field charging_schedule ;
} ;

typedef struct {
    int charging_profile_id ;
    int transaction_id ;
    int stack_level ;
    char *charging_profile_purpose ;
    char *charging_profile_kine ;
    char *recurrency_kind ;
    char *valid_from ;
    char *valid_to ;
    raw_charging_schedule *charging_schedule ;
} raw_charging_profile ;

struct _charging_schedule_ {
    message_field duration ;
    message_field start_schedule ;
    message_field charging_rate_unit ;
    message_field charging_schedule_period ;
    message_field min_charging_rate ;
    int number_of_charging_schedule_period ;
} ;

struct _raw_charging_schedule_ {
    int duration ;
    char *start_schedule ;
    char *charging_rate_unit ;
    raw_charging_schedule_period *charging_schedule_period ;
    double min_charging_rate ;
    int number_of_charging_schedule_period ;
} ;

struct _charging_schedule_period_{
    message_field start_period ;
    message_field limit ;
    message_field number_phases ;
} ;

struct _raw_charging_schedule_period_ {
    int start_period ;
    double limit ;
    int number_phases ;
} ;

struct _id_tag_info_ {
    message_field expiry_date ;
    message_field parent_id_tag ;
    message_field status ; 
} ;

struct _raw_id_tag_info_ {
    char *expiry_date ;
    char *parent_id_tag ;
    char *status ;
} ;

struct _key_value_ {
    message_field key ;
    message_field readonly ;
    message_field value ;
} ;

typedef struct {
    char *key ;
    bool readonly ;
    char *value ;
} raw_key_value ;


struct _meter_value_ {
    message_field timestamp ;
    message_field sampled_value ;
    int number_of_sampled_value ;
} ;

typedef struct {
    char *timestamp ;
    raw_sampled_value *sampled_value ;
    int number_of_sampled_value ;
} raw_meter_value ;

struct _sampled_value_ {
    message_field value ;
    message_field context ;
    message_field format ;
    message_field measurand ;
    message_field phase ;
    message_field location ;
    message_field unit ;
} ;

struct _raw_sampled_value_ {
    char *value ;
    char *context ;
    char *format ;
    char *measurand ;
    char *phase ;
    char *location ;
    char *unit ;
} ;

#endif