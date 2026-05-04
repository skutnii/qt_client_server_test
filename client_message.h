/*
 * client_message.h
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#ifndef CLIENT_MESSAGE_H_
#define CLIENT_MESSAGE_H_

#include <QSharedPointer>
#include <QHostAddress>
#include "user_record.h"

/**
 * Encapsulates receiver data and the payload for sending across threads.
 */
struct client_message {
	QHostAddress host;
	quint16 port;
	user_record_ptr payload;
};

using client_message_ptr = QSharedPointer<client_message>;

#endif /* CLIENT_MESSAGE_H_ */
