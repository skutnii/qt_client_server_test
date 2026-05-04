/*
 * user_record.h
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#ifndef USER_RECORD_H_
#define USER_RECORD_H_

#include <qcontainerfwd.h>
#include <qtypes.h>
#include <QMetaType>
#include <QString>
#include <QByteArray>
#include <QSharedPointer>
#include <expected>
#include <QJsonDocument>

struct user_record;
using user_record_ptr = QSharedPointer<user_record>;

/**
 * Main data structure
 */
struct user_record {
	/**
   * User ID. 
   * Valid values are positive.
   */
	int id; 

	/** 
   * User name
   */
	QString name;

	/**
	 * User email
   */
	QString email;

	user_record(int user_id, const QString &user_name,
							const QString &user_email) :
			id{user_id}, name{user_name}, email{user_email} {}

	/**
	 * JSON serialization
   */
	QByteArray json(QJsonDocument::JsonFormat fmt) const;

	using parse_result = std::expected<user_record_ptr, QString>;

	/**
	 * JSON deserialization
   */
	static parse_result from_json(const QByteArray &json);
};

#endif /* USER_RECORD_H_ */
