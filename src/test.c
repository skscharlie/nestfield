
#include <stdio.h>
#include <strings.h>
#include <pthread.h>
#include <json.h>
#include <libwebsockets.h>
#include "ocpp.h"

extern int authorize_test() ;
extern int boot_notification_test() ;
extern int cancel_reservation_test() ;
extern int change_availability_test() ;
extern int change_configuration_test() ;
extern int clear_cache_test() ;
extern int clear_charging_profile_test() ;
extern int data_transfer_test() ;
extern int diagnostics_status_notification_test() ;
extern int firmware_status_notification_test() ;
extern int get_composite_schedule_test() ;
extern int get_configuration_test() ;
extern int get_diagnostics_test() ;
extern int get_local_list_version_test() ;
extern int heartbeat_test() ;
extern int meter_values_test() ;
extern int remote_start_transaction_test() ;
extern int remote_stop_transaction_test() ;
extern int reserve_now_test() ;
extern int reset_test() ;
extern int send_local_list_test() ;
extern int set_charging_profile_test() ;
extern int start_transaction_test() ;
extern int status_notification_test() ;
extern int stop_transaction_test() ;
extern int trigger_message_test() ;
extern int unlock_connector_test() ;
extern int update_firmware_test() ;
extern void *nestfield_ocpp_main() ;
extern void *ocpp_command_input() ;
extern void *secc_comm_main() ;

int main(int argc, char** argv) {
    //authorize_test() ;
    //boot_notification_test() ;
    //cancel_reservation_test() ;

    //change_availability_test() ;
    //change_configuration_test() ;
    //clear_cache_test() ;
    //clear_charging_profile_test() ;
    //data_transfer_test() ;
    //diagnostics_status_notification_test() ;
    //firmware_status_notification_test() ;
    //get_composite_schedule_test() ;
    //get_configuration_test() ;
    //get_diagnostics_test() ;
    //get_local_list_version_test() ;
    //heartbeat_test() ;
    //meter_values_test() ;
    //remote_start_transaction_test() ;
    //remote_stop_transaction_test() ;
    //reserve_now_test() ;
    //reset_test() ;
    //send_local_list_test() ;
    //set_charging_profile_test() ;
    //start_transaction_test() ;
    //status_notification_test() ;
    //stop_transaction_test() ;
    //trigger_message_test() ;
    //unlock_connector_test() ;
    //update_firmware_test() ;
    pthread_t ocpp_main_thread, ocpp_command_input_thread, secc_comm_thread ;
    ocpp_argument args ;
    struct lws_context *context ;

    if(pthread_mutex_init(&terminal_input_mutex, NULL) != 0) {
        printf("Error initializing mutex\n") ;
        return 3 ;
    }

    args.server_ip = argv[1] ;

    if(pthread_create(&ocpp_main_thread, NULL, nestfield_ocpp_main, (void *)&args) != 0) {
        printf("thread create error\n") ;
        return 1 ;
    }

    /* context 가 initialize 되는 시간을 확보해 줘야하므로 1초간 sleep */
    sleep(1) ;

    if(pthread_create(&ocpp_command_input_thread, NULL, ocpp_command_input, (void*)&args.context) != 0) {
        printf("command input thread create error\n") ;
        return 1 ;
    } 

    if(pthread_create(&secc_comm_thread, NULL, secc_comm_main, (void*)&args.context) != 0) {
        printf("secc communication thread create error\n") ;
        return 1 ;
    }

    if(pthread_join(ocpp_main_thread, NULL) != 0) {
        printf("thread join error\n") ;
        return 2 ;
    }

    if(pthread_join(ocpp_command_input_thread, NULL) != 0) {
        printf("command input thread join error\n") ;
        return 2 ;
    }

    if(pthread_join(secc_comm_thread, NULL) != 0) {
        printf("secc communication thread join error\n") ;
        return 2 ;
    }

    pthread_mutex_destroy(&terminal_input_mutex) ;

    printf("all thread exited\n") ;
    return 0 ;
}
