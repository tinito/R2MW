#include "ch.hpp"

#include "BaseSubscriber.hpp"

BaseSubscriber::BaseSubscriber(const char * topic, size_t msg_size, uint8_t * buffer, BaseMessage * mail,  uint32_t size) {
	_topic = topic;
	_source = NULL;
	_buffer = buffer;
	_msg_size = msg_size;
	_size = size;
	_msg_queue = 0;
	chMBInit(&_mailbox, (msg_t *) mail, size);
}

const char * BaseSubscriber::topic(void) {
	return _topic;
}

BasePublisher * BaseSubscriber::source(void) {
	return _source;
}

BaseMessage * BaseSubscriber::get(void) {
	BaseMessage * msg;
	msg_t ret;

	chSysLock();
	ret = chMBFetchI(&_mailbox, (msg_t *) &msg);
	chSysUnlock();
	if (ret == RDY_OK)
		return msg;
	else
		return NULL;
}

void BaseSubscriber::release(BaseMessage *d) {
	_msg_queue--;
	_source->release(d);
}

void BaseSubscriber::releaseI(BaseMessage *d) {
	_msg_queue--;
	_source->releaseI(d);
}

uint16_t BaseSubscriber::size(void) {
	return _size;
}
