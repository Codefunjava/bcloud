// Copyright (c) 2017 LiuLang. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "services/pcs.h"

#include <QDebug>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "base/json_util.h"

namespace bcloud {

namespace {

const char kPassportUrl[] = "https://passport.baidu.com/v2/api/";

}  // namespace

Pcs::Pcs(QObject* parent) :
    QObject(parent),
    network_manager_(new QNetworkAccessManager(this)) {
  this->setObjectName("Pcs");
}

Pcs::~Pcs() {

}

void Pcs::checkLoginState(const QString& username) {
  if (!cookie_inited_) {
    cookie_inited_ = true;
    username_ = username;

    // Get BaiduId.
    const QString url = QString("%1?getapi&tpl=mn&apiver=v3&tt=%2"
                                "&class=login&logintype=basicLogin")
        .arg(kPassportUrl).arg(0);

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply* reply = network_manager_->get(request);
    connect(reply, &QNetworkReply::finished,
            this, &Pcs::onGetBaiduId);
    // TODO(LiuLang): Handle request errors.

  } else {
    // TODO
  }
}

void Pcs::printCookieJar() {
  QNetworkCookieJar* cookie_jar = network_manager_->cookieJar();
  QList<QNetworkCookie> cookies =
      cookie_jar->cookiesForUrl(QUrl(kPassportUrl));
  qDebug() << "cookie jar:" << cookies;
}

void Pcs::onGetBaiduId() {
  qDebug() << "onGetBaiduId()";
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender());
  // Cookies in http reply headers has been saved in cookie jar.
  reply->deleteLater();

  // Get token.
  const QString url = QString("%1?getapi&tpl=pp&apiver=v3&tt=%2"
                              "&class=login&logintype=basicLogin")
      .arg(kPassportUrl).arg(0);

  QNetworkRequest request;
  request.setUrl(QUrl(url));
  QNetworkReply* next_reply = network_manager_->get(request);
  connect(next_reply, &QNetworkReply::finished,
          this, &Pcs::onGetToken);
}

void Pcs::onGetToken() {
  qDebug() << "onGetToken()";
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender());
  const QByteArray body = reply->readAll();
  reply->deleteLater();

  qDebug() << "token body:" << body;
  const QVariant token = GetJsonItem(body, "data.token");
  if (token.isValid()) {
    token_ = token.toString();
    qDebug() << "token:" << token_;

    // Get UBI.
    const QString url = QString("%1?loginhistory&tpl=pp&apiver=v3&tt=%2"
                                "&token=%3")
        .arg(kPassportUrl).arg(0).arg(token_);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply* next_reply = network_manager_->get(request);
    connect(next_reply, &QNetworkReply::finished,
            this, &Pcs::onGetUbi);
  } else {
    qWarning() << "Failed to get token";
    emit this->onCheckLoginState(false);
  }
}

void Pcs::onGetUbi() {
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender());
  // Cookies are stored in cookie jar.
  reply->deleteLater();

  // Check login.
}


}  // namespace bcloud