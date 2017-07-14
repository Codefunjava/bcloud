// Copyright (c) 2017 LiuLang. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef BCLOUD_BASE_JSON_UTIL_H
#define BCLOUD_BASE_JSON_UTIL_H

#include <QString>
#include <QVariant>

namespace bcloud {

QVariant GetJsonItem(const QByteArray& content, const QString& path);

}  // namespace bcloud

#endif  // BCLOUD_BASE_JSON_UTIL_H
