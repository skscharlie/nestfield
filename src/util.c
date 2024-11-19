#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "ocpp.h"

int make_message_id(char *id) {
    int random_val ;
    struct tm *tv ;
    time_t tval ;

    tval = time(NULL) ;
    tv = localtime(&tval) ;

    srand(tval) ;
    random_val = rand() ;

    sprintf(id, "%04d%02d%02d%02d%02d%02d%022d", tv->tm_year + 1900, tv->tm_mon + 1, tv->tm_mday, tv->tm_hour, tv->tm_min, tv->tm_sec, random_val) ;
    return 0 ;
}

int make_transaction_id() {
    int random_val ;
    struct tm *tv ;
    time_t tval ;

    tval = time(NULL) ;
    tv = localtime(&tval) ;

    srand(tval) ;
    random_val = rand() ;

    return random_val ;
}

int get_future_date(char *buf, int day) {
    struct tm *tv ;
    time_t tval ;

    tval = time(NULL) ;
    tval += (time_t)(day * 24 * 3600) ;
    tv = localtime(&tval) ;
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", tv->tm_year + 1900, tv->tm_mon + 1, tv->tm_mday, tv->tm_hour, tv->tm_min, tv->tm_sec) ;
    return 0 ;
}

int get_message_type_id(char *data) {
    char *ptr_start, *ptr_end, *ptr_next ;
    char buf[10] ;

    bzero(buf, sizeof(buf)) ;

    /*
     * find message type id
     */
    ptr_start = data + 1 ;                      // skip start [
    ptr_end = strchr(ptr_start, ',') ;          // find next ,
    ptr_next = ptr_end + 1 ;                    // unique id 를 찾기위한 pointer setting
    ptr_end-- ;                                 // , 제외

    while(isspace((int)*ptr_start)) ptr_start++ ;           // 앞부분의 white space 제거
    while(isspace((int)*ptr_end)) ptr_end-- ;               // 뒷부분의 white space 제거
    
    bcopy(ptr_start, buf, ptr_end - ptr_start + 1) ;
    return (int)strtol(buf, NULL, 10) ;
}

int parse_req_message(char *data, ocpp_call_message *msg) {
    char *ptr_start, *ptr_end, *ptr_next ;

    /*
     * find message type id
     */
    ptr_start = data + 1 ;                      // skip start [
    ptr_end = strchr(ptr_start, ',') ;          // find next ,
    ptr_next = ptr_end + 1 ;                    // unique id 를 찾기위한 pointer setting
    ptr_end-- ;                                 // , 제외

    while(isspace((int)*ptr_start)) ptr_start++ ;           // 앞부분의 white space 제거
    while(isspace((int)*ptr_end)) ptr_end-- ;               // 뒷부분의 white space 제거
    *(ptr_end + 1) = '\0' ;
    msg->message_type = (int)strtol(ptr_start, NULL, 10) ;

    /*
     * find unique id
     */
    ptr_start = ptr_next ;
    ptr_end = strchr(ptr_start, ',') ;
    ptr_next = ptr_end + 1 ;
    ptr_end-- ;
    while(*ptr_start != '\"' && isspace((int)*ptr_start)) ptr_start++ ;                  // unique id를 감싸고 있는 "" 제거
    while(*ptr_end != '\"' && isspace((int)*ptr_end)) ptr_end-- ;
    *(ptr_end) = 0x00 ;
    msg->message_id = ptr_start + 1 ;

    /*
     * find action
     */
    ptr_start = ptr_next ;
    ptr_end = strchr(ptr_start, ',') ;
    ptr_next = ptr_end + 1 ;
    ptr_end-- ;
    while(*ptr_start != '\"' && isspace((int)*ptr_start)) ptr_start++ ;                  // action을 감싸고 있는 "" 제거
    while(*ptr_end != '\"' && isspace((int)*ptr_end)) ptr_end-- ;
    *(ptr_end) = 0x00 ;
    msg->action = ptr_start + 1 ;

    /*
     * find payload
     */
    ptr_start = ptr_next ;
    ptr_end = ptr_start + strlen(ptr_start) - 1 ;
    while(*ptr_start != '{') ptr_start++ ;
    while(*ptr_end != '}') ptr_end-- ;
    *(ptr_end + 1) = 0x00 ;
    msg->payload = ptr_start ;

    return 0 ;
}

int parse_conf_message(char *data, ocpp_callresult_message * msg){
    char *ptr_start, *ptr_end, *ptr_next ;

    /*
     * find message type id
     */
    ptr_start = data + 1 ;                      // skip start [
    ptr_end = strchr(ptr_start, ',') ;          // find next ,
    ptr_next = ptr_end + 1 ;                    // unique id 를 찾기위한 pointer setting
    ptr_end-- ;                                 // , 제외

    while(isspace((int)*ptr_start)) ptr_start++ ;           // 앞부분의 white space 제거
    while(isspace((int)*ptr_end)) ptr_end-- ;               // 뒷부분의 white space 제거
    *(ptr_end + 1) = 0x00 ;
    msg->message_type = (int)strtol(ptr_start, NULL, 10) ;

    /*
     * find unique id
     */
    ptr_start = ptr_next ;
    ptr_end = strchr(ptr_start, ',') ;
    ptr_next = ptr_end + 1 ;
    ptr_end-- ;
    while(*ptr_start != '\"' && isspace((int)*ptr_start)) ptr_start++ ;                  // unique id를 감싸고 있는 "" 제거
    while(*ptr_end != '\"' && isspace((int)*ptr_end)) ptr_end-- ;
    *(ptr_end) = 0x00 ;
    msg->message_id = ptr_start + 1 ;

    /*
     * find payload
     */
    ptr_start = ptr_next ;
    ptr_end = ptr_start + strlen(ptr_start) - 1 ;
    while(*ptr_start != '{') ptr_start++ ;
    while(*ptr_end != '}') ptr_end-- ;
    *(ptr_end + 1) = 0x00 ;
    msg->payload = ptr_start ;

    return 0 ;
}

int parse_error_message(char *data, ocpp_callerror_message *msg) {
    char *ptr_start, *ptr_end, *ptr_next ;

    /*
     * find message type id
     */
    ptr_start = data + 1 ;                      // skip start [
    ptr_end = strchr(ptr_start, ',') ;          // find next ,
    ptr_next = ptr_end + 1 ;                    // unique id 를 찾기위한 pointer setting
    ptr_end-- ;                                 // , 제외

    while(isspace((int)*ptr_start)) ptr_start++ ;           // 앞부분의 white space 제거
    while(isspace((int)*ptr_end)) ptr_end-- ;               // 뒷부분의 white space 제거
    *(ptr_end + 1) = '\0' ;
    msg->message_type = (int)strtol(ptr_start, NULL, 10) ;

    /*
     * find unique id
     */
    ptr_start = ptr_next ;
    ptr_end = strchr(ptr_start, ',') ;
    ptr_next = ptr_end + 1 ;
    ptr_end-- ;
    while(*ptr_start != '\"' && isspace((int)*ptr_start)) ptr_start++ ;                  // unique id를 감싸고 있는 "" 제거
    while(*ptr_end != '\"' && isspace((int)*ptr_end)) ptr_end-- ;
    *(ptr_end) = 0x00 ;
    msg->message_id = ptr_start + 1 ;

    /*
     * find error code
     */
    ptr_start = ptr_next ;
    ptr_end = strchr(ptr_start, ',') ;
    ptr_next = ptr_end + 1 ;
    ptr_end-- ;
    while(*ptr_start != '\"' && isspace((int)*ptr_start)) ptr_start++ ;                  // erroe code을 감싸고 있는 "" 제거
    while(*ptr_end != '\"' && isspace((int)*ptr_end)) ptr_end-- ;
    *(ptr_end) = 0x00 ;
    msg->error_code = ptr_start + 1 ;

    /*
     * find error description
     */
    ptr_start = ptr_next ;
    ptr_end = strchr(ptr_start, ',') ;
    ptr_next = ptr_end + 1 ;
    ptr_end-- ;
    while(*ptr_start != '\"' && isspace((int)*ptr_start)) ptr_start++ ;                  // error description을 감싸고 있는 "" 제거
    while(*ptr_end != '\"' && isspace((int)*ptr_end)) ptr_end-- ;
    *(ptr_end) = 0x00 ;
    msg->error_description = ptr_start + 1 ;

    /*
     * find error details
     */
    ptr_start = ptr_next ;
    ptr_end = ptr_start + strlen(ptr_start) - 1 ;
    while(*ptr_start != '{') ptr_start++ ;
    while(*ptr_end != '}') ptr_end-- ;
    *(ptr_end + 1) = 0x00 ;
    msg->error_details = ptr_start ;

    return 0 ;
   
}

char *trim(char *str) {
    char *end;

    // 문자열이 비어 있는지 확인
    if (str == NULL || *str == '\0')
        return str;

    // 앞의 공백을 제거
    while (isspace((unsigned char)*str))
        str++;

    // 모든 문자가 공백인 경우 빈 문자열 반환
    if (*str == '\0')
        return str;

    // 뒤의 공백을 제거
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // 새로운 널 종단 문자 추가
    *(end + 1) = '\0';

    return str;
}

void make_ci20_type_string(char *buf) {
    int random_val ;
    time_t tval ;

    tval = time(NULL) ;

    srand(tval) ;
    random_val = rand() ;

    sprintf(buf, "%020d", random_val) ;
}

void make_ci25_type_string(char *buf) {
    int random_val ;
    time_t tval ;

    tval = time(NULL) ;

    srand(tval) ;
    random_val = rand() ;

    sprintf(buf, "%025d", random_val) ;
}

void make_ci50_type_string(char *buf) {
    int random_val ;
    time_t tval ;

    tval = time(NULL) ;

    srand(tval) ;
    random_val = rand() ;

    sprintf(buf, "%050d", random_val) ;
}

void make_ci255_type_string(char *buf) {
    int random_val ;
    time_t tval ;

    tval = time(NULL) ;

    srand(tval) ;
    random_val = rand() ;

    sprintf(buf, "%0255d", random_val) ;
}

void make_ci500_type_string(char *buf) {
    int random_val ;
    time_t tval ;

    tval = time(NULL) ;

    srand(tval) ;
    random_val = rand() ;

    sprintf(buf, "%0500d", random_val) ;
}