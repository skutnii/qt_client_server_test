/*
 * user_record.cpp
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#include "user_record.h"
#include <QJsonDocument>
#include <expected>
#include <qcontainerfwd.h>
#include <QJsonObject>
#include <QJsonValue>
#include <qjsondocument.h>
#include <qjsonobject.h>

static const char * k_id = "id";
static const char * k_name = "name";
static const char * k_email = "email";

//==============================================================================

std::expected<user_record_ptr, QString>
user_record::from_json(const QByteArray &json) {
	QJsonParseError parse_error;
	QJsonDocument doc = QJsonDocument::fromJson(json, &parse_error);
	if (parse_error.error != QJsonParseError::NoError)
		return std::unexpected{parse_error.errorString()};

	if (!doc.isObject())
		return std::unexpected<QString>{"Invalid user record structure"};

	QJsonObject root = doc.object();
	int id_value = root.find(k_id)->toInteger(-1);
	if (id_value == -1)
		return std::unexpected<QString>{"User ID is required"};

	QJsonObject::Iterator name_it = root.find(k_name);
	if (!name_it->isString())
		return std::unexpected<QString>{"User name is required"};

	QJsonObject::const_iterator email_it = root.find(k_email);
	if (!email_it->isString())
		return std::unexpected<QString>{"User email is required"};

	return user_record_ptr::create(id_value, name_it->toString(),
																 email_it->toString());
}

//==============================================================================

QByteArray user_record::json(QJsonDocument::JsonFormat fmt) const {
	QJsonObject root;
	root[k_id] = id;
	root[k_name] = name;
	root[k_email] = email;

	QJsonDocument doc{root};
	return doc.toJson(fmt);
}
