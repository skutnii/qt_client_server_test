/*
 * client_view_model.cpp
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#include "client_view_model.h"
#include "client_message.h"
#include "user_record.h"
#include <QTcpSocket>
#include <iostream>
#include <qabstractsocket.h>
#include <qjsondocument.h>
#include <qt5/QtCore/qglobal.h>
#include <qthreadpool.h>
#include <qtypes.h>

//==============================================================================

client_view_model::client_view_model() :
		QObject{} {
	connect(this, &client_view_model::io_error, this,
					[](QTcpSocket::SocketError err) {
						std::cerr << "Socket I/O error: " << err << std::endl;
					});
}

//==============================================================================

void client_view_model::send() {
	if (!send_enabled())
		return;

	client_message_ptr message = client_message_ptr::create();
	message->host.setAddress(m_host);
	message->port = m_port.value();
	message->payload = user_record_ptr::create(m_id.value(), m_name, m_email);

	QThreadPool::globalInstance()->start([this, message]() {
		QTcpSocket socket;
		socket.connectToHost(message->host, message->port);
		if (!socket.waitForConnected()) {
			emit io_error(socket.error());
			return;
		}

		QDataStream stream{&socket};
		stream.setVersion(QDataStream::Qt_6_0);		
		stream << message->payload->json(
				QJsonDocument::JsonFormat::Compact);
		socket.disconnectFromHost();
		socket.waitForDisconnected();
	});
}

//==============================================================================

void client_view_model::set_host(const QString &host) {
	m_host = host;
	update_ui();
}

//==============================================================================

void client_view_model::set_port(const QString &port) {
	bool conv_ok;
	quint16 value = port.toUShort(&conv_ok);
	if (!conv_ok)
		m_port.reset();
	else
		m_port = value;

	update_ui();
}

//==============================================================================

void client_view_model::set_id(const QString &id) {
	bool conv_ok;
	int value = id.toInt(&conv_ok);
	if (conv_ok)
		m_id = value;
	else
		m_id.reset();

	update_ui();
}

//==============================================================================

void client_view_model::set_name(const QString &name) {
	m_name = name;
	update_ui();
}

//==============================================================================

void client_view_model::set_email(const QString &email) {
	m_email = email;
	update_ui();
}

//==============================================================================

bool client_view_model::send_enabled() const {
	if (m_host.isEmpty() || !m_port.has_value() || !m_id.has_value() ||
			m_name.isEmpty() || m_email.isEmpty())
		return false;

	return true;
}

//==============================================================================

void client_view_model::update_ui() { emit enable_send_button(send_enabled()); }
