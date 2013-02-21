#include "ch.hpp"

#include "Middleware.hpp"

#include "hal.h"
#include "board.h"

#include "BasePublisher.hpp"

BasePublisher::BasePublisher(const char * t, size_t msg_size) {
	_topic = t;
	chPoolInit(&_pool, msg_size, NULL);
}

const char * BasePublisher::topic(void) {
	return _topic;
}

BaseMessage * BasePublisher::alloc(void) {
	BaseMessage * msg;

	chSysLock();
	msg = allocI();
	chSysUnlock();

	return msg;
}

BaseMessage * BasePublisher::allocI(void) {
	BaseMessage * msg;

	msg = (BaseMessage *) chPoolAllocI(&_pool);

	/* reset reference count */
	if (msg != NULL)
		msg->reset();

	return msg;
}

void BasePublisher::release(BaseMessage* msg) {
	chSysLock();

	/* if the reference count is reduced to zero then free the memory */
	if (msg->dereference()) {
		chPoolAddI(&_pool, msg);
	}

	chSysUnlock();
}

void BasePublisher::releaseI(BaseMessage* msg) {
	/* if the reference count is reduced to zero then free the memory */
	if (msg->dereference()) {
		if ((int)msg % 2)
			while(1);
		chPoolAddI(&_pool, msg);
	}
}
