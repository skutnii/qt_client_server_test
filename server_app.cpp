/*
 * listener.cpp
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#include "server_app.h"
#include "user_record.h"
#include <QNetworkInterface>
#include <QTcpSocket>
#include <QThreadPool>
#include <iostream>
#include <qhostaddress.h>
#include <qtmetamacros.h>

//==============================================================================

server_app::server_app(quint16 port) :
		QTcpServer{}, m_port{port} {
	connect(this, &server_app::receive, [](const user_record_ptr &rec) {
		std::cout << "Received user record (id:" << rec->id
							<< ",name:" << rec->name.toStdString()
							<< ",email:" << rec->email.toStdString() << ")" << std::endl;
	});

	connect(this, &server_app::parse_error, [](const QString &err) {
		std::cerr << "Message parse error: " << err.toStdString() << std::endl;
	});

	connect(this, &server_app::io_error,
					[this](QTcpSocket::SocketError socket_error) {
						std::cerr << "Socket I/O error: " << socket_error << std::endl;
					});
}

//==============================================================================

void server_app::run() {
	if (!listen(QHostAddress::Any, m_port)) {
		std::cout << errorString().toStdString() << std::endl;
		return;
	}

	const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

	QString address;
	for (const QHostAddress &entry : ipAddressesList) {
		if ((entry != QHostAddress::LocalHost) && entry.toIPv4Address()) {
			address = entry.toString();
			break;
		}
	}

	if (address.isEmpty())
		address = QHostAddress(QHostAddress::LocalHost).toString();

	std::cout << "Listening on " << address.toStdString() << ":"
						<< serverPort() << std::endl;
	for (;;)
		waitForNewConnection(1);
}

//==============================================================================

void server_app::incomingConnection(qintptr socket_descriptor) {
	QThreadPool::globalInstance()->start(
			[this, socket_descriptor]() { serve(socket_descriptor); });
}

//==============================================================================

server_app::~server_app() {}

//==============================================================================

void server_app::serve(qintptr socket_descriptor) {
	QTcpSocket socket;
	if (!socket.setSocketDescriptor(socket_descriptor) ||
			!socket.waitForReadyRead()) {
		emit io_error(socket.error());
		return;
	}

	QDataStream input{&socket};
	input.setVersion(QDataStream::Qt_6_0);

	/*
		Normally, the data should be small, unless someone is attacking the server.
		Since protection against such attacks has not been required explicitly,
		it is probably OK to keep everything in memory.
	*/
	QByteArray json;
	input >> json;

	socket.disconnectFromHost();

	user_record::parse_result res = user_record::from_json(json);
	if (res.has_value())
		emit receive(res.value());
	else
		emit parse_error(res.error());
}
