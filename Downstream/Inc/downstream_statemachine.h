/*
 * downstream_statemachine.h
 *
 *  Created on: 2/08/2015
 *      Author: Robert Fisk
 */

#ifndef INC_DOWNSTREAM_STATEMACHINE_H_
#define INC_DOWNSTREAM_STATEMACHINE_H_


#include "usbh_def.h"
#include "downstream_spi.h"


typedef enum
{
	STATE_DEVICE_NOT_READY,
	STATE_DEVICE_READY,			//Go here if HOST_USER_CLASS_ACTIVE callback arrives first
	STATE_WAIT_DEVICE_READY,	//Go here if COMMAND_INTERFACE_NOTIFY_DEVICE message arrives first
	STATE_ACTIVE,
	STATE_ERROR
} DownstreamStateTypeDef;



#define DOWNSTREAM_STATEMACHINE_FREAKOUT				\
	do {												\
		LED_Fault_SetBlinkRate(LED_FAST_BLINK_RATE);	\
		DownstreamState = STATE_ERROR;					\
		return;											\
} while (0);




void Downstream_InitStateMachine(void);
void Downstream_HostUserCallback(USBH_HandleTypeDef *phost, uint8_t id);
void Downstream_PacketProcessor(DownstreamPacketTypeDef* receivedPacket);
void Downstream_PacketProcessor_ErrorReply(DownstreamPacketTypeDef* replyPacket);
void Downstream_PacketProcessor_ClassReply(DownstreamPacketTypeDef* replyPacket);
void Downstream_PacketProcessor_SetErrorState(void);
void Downstream_PacketProcessor_FreakOut(void);


#endif /* INC_DOWNSTREAM_STATEMACHINE_H_ */
