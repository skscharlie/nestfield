#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t terminal_input_mutex, secc_mutex, ocpp_mutex ;
bool terminal_input_valid, secc_data_valid, ocpp_comm_end, secc_comm_end ; 
char shared_data[4096] ;
