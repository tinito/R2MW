#include "ch.hpp"

#include "Middleware.hpp"

RemoteSubscriber::RemoteSubscriber(const char * topic, size_t msg_size,
		uint8_t * buffer, BaseMessage * mail, uint32_t size) : BaseSubscriber(topic, msg_size, buffer, mail, size) {
	_next = NULL;
	_next_notify = NULL;
	_id = 999;
}

RemoteSubscriber * RemoteSubscriber::next(void) {
	return _next;
}

void RemoteSubscriber::next(RemoteSubscriber * next) {
	_next = next;
}

void RemoteSubscriber::link(RemoteSubscriber * sub) {
	_next_notify = sub;
}

/* called from within lock */
RemoteSubscriber * RemoteSubscriber::notify(BaseMessage *msg) {
	int n;
	return this->notify(msg, n);
}

RemoteSubscriber * RemoteSubscriber::notify(BaseMessage *msg, int &n) {
	Middleware & mw = Middleware::instance();

	if(_msg_queue < size()) {
		mw.transport().send(this, msg, _msg_size);
		msg->reference();
		_msg_queue++;
		n++;
	}

	return _next_notify;
}

void RemoteSubscriber::subscribe(LocalPublisher * publisher) {
	_source = publisher;
	publisher->subscribe(this, _buffer, chMBSizeI(&_mailbox));
}

void RemoteSubscriber::id(uint16_t id) {
	_id = id;
}

uint16_t RemoteSubscriber::id(void) {
	return _id;
}

