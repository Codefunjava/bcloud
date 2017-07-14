// Copyright (c) 2017 LiuLang. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "base/json_util.h"

#include <QDebug>

#include "base/file_util.h"
#include "third_party/gtest/include/gtest/gtest.h"

namespace bcloud {
namespace {

TEST(JsonUtil, TestGetJsonItem) {
  QByteArray content;
  ReadRawFile("/tmp/info.json", content);
//  const QByteArray content("{\"errno\": 0, \"data\": {\"token\": \"123\"}}");
  const QString path("data.token");
  const QVariant result = GetJsonItem(content, path);
  const QString token = result.toString();
  EXPECT_EQ(token.toStdString().c_str(), "123");
}

}  // namespace
}  // namespace bcloud