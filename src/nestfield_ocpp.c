#include <libwebsockets.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <json.h>
#include "ocpp.h"

static struct lws *web_socket = NULL;

#define USER_DATA_SIZE      4096
user_data user_data_buffer ;
static char input_command_buff[USER_DATA_SIZE] ;

#define EXAMPLE_TX_BUFFER_BYTES 4096

static void process_call_message(user_data *data) {
	ocpp_call_message call_msg ;
	ocpp_callresult_message callresult_msg ;
	ocpp_callerror_message callerror_msg ;

	parse_req_message(data->req_buf, &call_msg) ;

	for(int i = 0 ; i < central_system_initiated_actions_length ; i++) {
		if(strcmp(central_system_initiated_actions[i].action, call_msg.action) == 0)
			central_system_initiated_actions[i].func(&call_msg, data->resp_buf) ;
	}

}

static void process_callresult_message(user_data *data) {
	ocpp_callresult_message msg ;

	parse_conf_message(data->req_buf, &msg) ;

	if(strcmp(conf_act.message_id, msg.message_id) == 0) {
		conf_act.func(&msg) ;
	}
	else {
		printf("Invalid message id : (%s) : (%s)\n", conf_act.message_id, msg.message_id) ;
	}
}

static void process_callerror_message(user_data *data) {}

static int callback_example( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
    unsigned char *p ;

    lwsl_notice("event occurred : %d\n", reason) ;
	switch( reason )
	{
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
            lwsl_notice("connection established\n") ;
//			lws_callback_on_writable( wsi );
			break;

		case LWS_CALLBACK_CLIENT_RECEIVE:
		{
			const struct lws_protocols *proto ;
			user_data *proto_user_data ;
			int message_type_id ;
			/* Handle incomming messages here. */
			proto = lws_get_protocol(wsi) ;
			proto_user_data = (user_data *)proto->user ;
			bzero(proto_user_data->req_buf, USER_DATA_SIZE + 1) ;
			memcpy(proto_user_data->req_buf, in, len) ;
			lwsl_notice("received: %s\n", proto_user_data->req_buf) ;

			message_type_id = get_message_type_id(proto_user_data->req_buf) ;
			if(message_type_id == MESSAGE_TYPE_CALL)
				process_call_message(proto_user_data) ;
			else if(message_type_id == MESSAGE_TYPE_CALLRESULT)
				process_callresult_message(proto_user_data) ;
			else if(message_type_id == MESSAGE_TYPE_CALLERROR)
				process_callerror_message(proto_user_data) ;
			else {
				lwsl_notice("invalid message_type_id : %d\n", message_type_id) ;
			}

            lws_callback_on_writable(wsi) ;

			break ;
		}

		case LWS_CALLBACK_CLIENT_WRITEABLE:
		{
			const struct lws_protocols *proto ;
			user_data *proto_user_data ;

			proto = lws_get_protocol(wsi) ;
			proto_user_data = (user_data *)proto->user ;
            lwsl_notice("client writeable : %s\n", proto_user_data->resp_buf) ;
			if(strlen(proto_user_data->resp_buf) != 0) {
				lws_write(wsi, (unsigned char *)proto_user_data->resp_buf, strlen(proto_user_data->resp_buf), LWS_WRITE_TEXT) ;
				bzero(proto_user_data->resp_buf, strlen(proto_user_data->resp_buf)) ;
			}
//			lws_write( wsi, (unsigned char *)proto_user_data->resp_buf, strlen(proto_user_data->req_buf), LWS_WRITE_TEXT );
 //           lws_callback_on_writable(wsi) ;
			break;
		}

		case LWS_CALLBACK_CLIENT_CLOSED:
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
			web_socket = NULL;
			break;

		default:
			break;
	}

	return 0 ;
}

enum protocols
{
	PROTOCOL_EXAMPLE = 0,
	PROTOCOL_COUNT
};

static struct lws_protocols protocols[] =
{
    {
        .name                  = "example-protocol", /* Protocol name*/
        .callback              = callback_example,   /* Protocol callback */
        .per_session_data_size = 0,                  /* Protocol callback 'userdata' size */
        .rx_buffer_size        = 0,                  /* Receve buffer size (0 = no restriction) */
        .id                    = 0,                  /* Protocol Id (version) (optional) */
        .user                  = (void *)&user_data_buffer,          /* 'User data' ptr, to access in 'protocol callback */
        .tx_packet_size        = 0                   /* Transmission buffer size restriction (0 = no restriction) */
    },
    LWS_PROTOCOL_LIST_TERM /* terminator */
};

void* nestfield_ocpp_main(void *arg)
{
	struct lws_context_creation_info info;
    int use_ssl ;
	struct ocpp_comm_buff oc_buff ;

	memset( &info, 0, sizeof(info) );

	info.port = CONTEXT_PORT_NO_LISTEN; /* we do not run any server */
	info.protocols = protocols;
	info.gid = -1;
	info.uid = -1;
	info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

	use_ssl = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;


	struct lws_context *context = lws_create_context( &info );
	//*(struct lws_context **)arg = context ;
	((ocpp_argument *)arg)->context = context ;

	time_t old = 0;
	while( 1 )
	{
		struct timeval tv;
		gettimeofday( &tv, NULL );

		/* Connect if we are not connected to the server. */
		if( !web_socket && tv.tv_sec != old )
		{
			struct lws_client_connect_info ccinfo;
			memset(&ccinfo, 0, sizeof(ccinfo));
			
			ccinfo.context = context;
			ccinfo.address = ((ocpp_argument *)arg)->server_ip ;
			ccinfo.port = 8443;
			ccinfo.path = "/wstest?chargePointId=1";
            ccinfo.ssl_connection = use_ssl ;
			ccinfo.host = lws_canonical_hostname( context );
			ccinfo.origin = "origin";
			ccinfo.protocol = protocols[PROTOCOL_EXAMPLE].name;
            ccinfo.ietf_version_or_minus_one = -1 ;
            ccinfo.pwsi = &web_socket ;
			
			web_socket = lws_client_connect_via_info(&ccinfo);
		}

		pthread_mutex_lock(&terminal_input_mutex) ;
		if(terminal_input_valid == true) {
			terminal_input_valid = false ;
			strcpy(input_command_buff, shared_data) ;
			pthread_mutex_unlock(&terminal_input_mutex) ;

			process_input_command(input_command_buff) ;

			lws_callback_on_writable(web_socket) ;
		}
		else 
			pthread_mutex_unlock(&terminal_input_mutex) ;

		pthread_mutex_lock(&secc_mutex) ;
		if(secc_data_valid == true) {
			secc_data_valid = false ;
			memcpy(&oc_buff, shared_data, sizeof(oc_buff)) ;
			pthread_mutex_unlock(&secc_mutex) ;
			process_secc_data(&oc_buff, web_socket, context) ;
			
	//		lws_callback_on_writable(web_socket) ;
		}
		else
			pthread_mutex_unlock(&secc_mutex) ;

		/**
		if( tv.tv_sec > old )
		{
            lwsl_notice("tv_sec : %ld, old = %ld\n", tv.tv_sec, old) ;
			lws_callback_on_writable( web_socket );
			old = tv.tv_sec + 5 ;
		}
		*/

		lwsl_notice("service in\n") ;
		lws_service( context, /* timeout_ms = */ 250 ); /* NOTE: since v3.2, timeout_ms may be set to '0', since it internally ignored */
		lwsl_notice("service out\n") ;
	}

	lws_context_destroy( context );

	return NULL ;
}
