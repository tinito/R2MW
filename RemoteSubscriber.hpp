#ifndef __REMOTESUBSCRIBER_HPP__
#define __REMOTESUBSCRIBER_HPP__

#include "ch.h"
#include "BaseMessage.hpp"
#include "BasePublisher.hpp"
#include "LocalPublisher.hpp"
#include "BaseSubscriber.hpp"

class RemoteSubscriber : public BaseSubscriber {
private:
	// TODO: this should depend on the Transport, typedef needed.
	uint16_t _id;
protected:
	RemoteSubscriber * _next;
	RemoteSubscriber * _next_notify;
public:
	RemoteSubscriber(const char *, size_t, uint8_t *, BaseMessage *,  uint32_t);
	RemoteSubscriber * next(void);
	void next(RemoteSubscriber *);
	void link(RemoteSubscriber *);
	RemoteSubscriber *notify(BaseMessage *);
	RemoteSubscriber *notify(BaseMessage *, int &);
	void subscribe(LocalPublisher *);
	void id(uint16_t id);
	uint16_t id(void);
};

#endif /* __REMOTESUBSCRIBER_HPP__ */
