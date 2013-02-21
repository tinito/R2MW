#ifndef __BASESUBSCRIBER_HPP__
#define __BASESUBSCRIBER_HPP__

#include "ch.h"
#include "BaseMessage.hpp"
#include "BasePublisher.hpp"

typedef void (*callback_t)(BaseMessage *);

class BaseSubscriber {
protected:
	const char * _topic;
	BasePublisher * _source;
	Mailbox _mailbox;
	uint8_t * _buffer;
	// FIXME da rimuovere
	uint32_t _msg_size;
	uint16_t _size;
	uint16_t _msg_queue;
public:
	BaseSubscriber(const char * topic, size_t msg_size, uint8_t * buffer, BaseMessage * mail,  uint32_t size);
	const char * topic(void);
	BasePublisher * source(void);
	BaseSubscriber *last(void);
	BaseMessage *get(void);
	void release(BaseMessage *);
	void releaseI(BaseMessage *);
	uint16_t size(void);
};

#endif
