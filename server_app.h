/*
 * listener.h
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#ifndef SERVER_APP_H_
#define SERVER_APP_H_

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <qt5/QtCore/qchar.h>
#include "user_record.h"

/**
 * Server logic
 */
class server_app : public QTcpServer {
	Q_OBJECT
public:
	/**
   * Initialize with port
   */
  server_app(quint16 port);

  virtual ~server_app();

	/**
	 * Connect and run. This method is blocking.
	 */
	void run();

protected:
  void incomingConnection(qintptr socketDescriptor) override;
signals:
	/**
   * Emitted on socket error
	 */
	void io_error(QTcpSocket::SocketError socketError);

	/**
	 * Emitted when a valid record is received.
	 */
	void receive(const user_record_ptr&);

	/**
	 * Emitted upon a parse error.
	 */
	void parse_error(const QString& what);
private:
	/**
	 * Serve on a background thread.
	 */
	void serve(qintptr socket_descriptor);

	quint16 m_port;
};

#endif /* SERVER_APP_H_ */
