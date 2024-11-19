GCC := gcc

TARGET := tmptest

SECC_TEST := secc_test

OBJS_DIR := ../objs

INC := -I../include -I/opt/local/include

OBJS += test.o types_definition.o util.o actions.o authorize.o boot_notification.o message_definition.o \
		authorize_test.o boot_notification_test.o cancel_reservation.o cancel_reservation_test.o \
		change_availability.o change_availability_test.o change_configuration.o change_configuration_test.o \
		clear_cache.o clear_cache_test.o clear_charging_profile.o clear_charging_profile_test.o \
		data_transfer.o data_transfer_test.o diagnostics_status_notification.o diagnostics_status_notification_test.o \
		firmware_status_notification.o firmware_status_notification_test.o get_composite_schedule.o \
		get_composite_schedule_test.o get_configuration.o get_configuration_test.o get_diagnostics.o \
		get_diagnostics_test.o get_local_list_version.o get_local_list_version_test.o heartbeat.o \
		heartbeat_test.o meter_values.o meter_values_test.o remote_start_transaction.o remote_start_transaction_test.o \
		remote_stop_transaction.o remote_stop_transaction_test.o reserve_now.o reserve_now_test.o \
		reset.o reset_test.o send_local_list.o send_local_list_test.o set_charging_profile.o set_charging_profile_test.o \
		start_transaction.o start_transaction_test.o status_notification.o status_notification_test.o \
		stop_transaction.o stop_transaction_test.o trigger_message.o trigger_message_test.o unlock_connector.o \
		unlock_connector_test.o update_firmware.o update_firmware_test.o nestfield_ocpp.o ocpp_thread.o command_input.o \
		secc_comm.o

REAL_OBJS += $(patsubst %.o, ${OBJS_DIR}/%.o, ${OBJS})

all: ${TARGET}

${OBJS_DIR}/%.o: ./%.c
	${GCC}  -c -o "$@" "$<" ${INC} `pkg-config json-c --cflags` `pkg-config libwebsockets --cflags`

${TARGET}: ${REAL_OBJS}
	${GCC} ${REAL_OBJS} -o ${TARGET} -lpthread `pkg-config json-c --libs` `pkg-config libwebsockets --libs` -lsqlite3

${SECC_TEST} : secc_test.c 
	${GCC} secc_test.c -o secc_test ${INC} -lsqlite3

