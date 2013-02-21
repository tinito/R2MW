#include "ch.hpp"

#include "BaseSubscriber.hpp"
#include "LocalSubscriber.hpp"
#include "LocalPublisher.hpp"

LocalSubscriber::LocalSubscriber(const char* topic, size_t msg_size,
		uint8_t* buffer, BaseMessage* mail, uint32_t size, callback_t callback) : BaseSubscriber(topic, msg_size, buffer, mail, size) {
	_next = NULL;
	_tp = currp;
	_mask = 0;
	_next_notify = NULL;
	_callback = callback;
}

LocalSubscriber * LocalSubscriber::next(void) {
	return _next;
}

void LocalSubscriber::next(LocalSubscriber* next) {
	_next = next;
}

void LocalSubscriber::link(LocalSubscriber* sub) {
	_next_notify = sub;
}

/* called from within lock */
LocalSubscriber * LocalSubscriber::notify(BaseMessage* msg, int& n) {
	/* post message to mailbox */
	if(chMBPostI(&_mailbox, (msg_t)msg) == RDY_OK) {
		chEvtSignalI(_tp, _mask);
		msg->reference();
		_msg_queue++;
		n++;
	}
	return _next_notify;
}

/* called from within lock */
LocalSubscriber * LocalSubscriber::notify(BaseMessage* msg) {
	int n;
	return this->notify(msg, n);
}

void LocalSubscriber::subscribe(LocalPublisher* pub, eventmask_t emask) {
	// TODO: ci va lock()?
	_source = pub;
	_mask = emask;
	pub->subscribe(this, _buffer, chMBSizeI(&_mailbox));
}

void LocalSubscriber::subscribe(RemotePublisher* pub, eventmask_t emask) {
	// TODO: ci va lock()?
	_source = pub;
	_mask = emask;
	pub->subscribe(this, _buffer, chMBSizeI(&_mailbox));
}

callback_t LocalSubscriber::callback(void) {
	return _callback;
}

void LocalSubscriber::callback(BaseMessage* msg) {
	_callback(msg);
}

