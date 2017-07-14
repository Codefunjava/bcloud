// Copyright (c) 2017 LiuLang. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "base/json_util.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace bcloud {

QVariant GetJsonItem(const QByteArray& content, const QString& path) {
  const QStringList parts = path.split('.');
  QVariant result = QVariant::Invalid;

  QByteArray purified(content);
  purified.replace("'", "\"");
  QJsonDocument document(QJsonDocument::fromJson(purified));
  if (!document.isEmpty() && document.isObject()) {
    QJsonObject object = document.object();
    QJsonValue value;
    bool ok = true;
    for (const QString& part : parts) {
      if (object.contains(part)) {
        value = object.value(part);
        object = value.toObject();
      } else {
        ok = false;
        break;
      }
    }
    if (ok) {
      result = value.toVariant();
    }
  } else {
    qCritical() << "document is invalid" << document.isEmpty();
  }

  return result;
}

}  // namespace bcloud