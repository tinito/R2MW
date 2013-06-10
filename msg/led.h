#ifndef __LED_H__
#define __LED_H__

#include "BaseMessage.hpp"

#define LED_ID			123
#define LED_DEBUG_ID	999
#define LED23_ID		1001
#define LED2_ID			1012
#define LED3_ID			1013
#define LED4_ID			1014


struct LEDData: public BaseMessage {
	uint8_t pin;
	bool_t set;
}__attribute__((packed));

struct LEDDataDebug: public BaseMessage {
	uint8_t pin;
	bool_t set;
	uint8_t cnt;
}__attribute__((packed));

#endif /* __LED_H__ */
