/*
 * client_view_model.h
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#ifndef CLIENT_VIEW_MODEL_H_
#define CLIENT_VIEW_MODEL_H_

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QSharedPointer>

/**
 * Client window logic
 */
class client_view_model : public QObject {
	Q_OBJECT
public:
	client_view_model();
	virtual ~client_view_model() = default;
	
	/**
	 * These setters update stored values with user input.
	 */
	void set_host(const QString& host);
	void set_port(const QString& port);
	void set_id(const QString& id);
	void set_name(const QString& name);
	void set_email(const QString& email);

	/**
   * Force emit the update signal.
	 */
	void update_ui();

	/**
	 * Sends data if all parameters are valid
   */
	void send();
signals:
	/**
 	 * Updates send button state
   */
	void enable_send_button(bool);

	/**
	 * Emitted upon socket error	
	 */
	void io_error(QTcpSocket::SocketError err);
private:
	/**
   * Determines whether data sending is enabled based on stored values.
	 */
	bool send_enabled() const;

	QString m_host;
	std::optional<quint16> m_port;
	std::optional<int> m_id;
	QString m_name;
	QString m_email;
};

using client_view_model_ptr = QSharedPointer<client_view_model>;

#endif /* CLIENT_VIEW_MODEL_H_ */
