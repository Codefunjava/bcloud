// Copyright (c) 2017 LiuLang. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include <QCoreApplication>
#include "services/pcs.h"

int main(int argc, char** argv) {
  QCoreApplication app(argc, argv);

  bcloud::Pcs pcs;
  pcs.checkLoginState("demo-user");

  return app.exec();
}