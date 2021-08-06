/*
    Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "ResourceRequest.h"

#include "BlobUrlConversion.h"
#include "NetworkingContext.h"
#include "ThirdPartyCookiesQt.h"

#include <QNetworkRequest>
#include <QUrl>

#if USE(HTTP2)
#include <QSslSocket>
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
#include <QHttp2Configuration>
#endif
#endif // USE(HTTP2)

namespace WebCore {

// The limit can be found in qhttpnetworkconnection.cpp.
// To achieve the best result we want WebKit to schedule the jobs so we
// are using the limit as found in Qt. To allow Qt to fill its queue
// and prepare jobs we will schedule two more downloads.
// Per TCP connection there is 1 current processed, 3 possibly pipelined
// and 2 ready to re-fill the pipeline.
unsigned initializeMaximumHTTPConnectionCountPerHost()
{
    return 6 * (1 + 3 + 2);
}

static QUrl toQUrl(const URL& url)
{
    if (url.protocolIsBlob())
        return convertBlobToDataUrl(url);
    return url;
}

static inline QByteArray stringToByteArray(const String& string)
{
    if (string.is8Bit())
        return QByteArray(reinterpret_cast<const char*>(string.characters8()), string.length());
    return QString(string).toLatin1();
}

#if USE(HTTP2)
bool ResourceRequest::alpnIsSupported()
{
	/* gameblabla */
	/*
    // Before QTBUG-65903 is implemented there is no better way than to check OpenSSL version
    return QSslSocket::sslLibraryVersionNumber() > 0x10002000L &&
        QSslSocket::sslLibraryVersionString().startsWith(QLatin1String("OpenSSL"));*/
    return 0;
}

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
static QHttp2Configuration createHttp2Configuration()
{
    QHttp2Configuration params;
    params.setServerPushEnabled(true);
    return params;
}
#endif

#endif

QNetworkRequest ResourceRequest::toNetworkRequest(NetworkingContext *context) const
{
    QNetworkRequest request;
    const URL& originalUrl = url();
    request.setUrl(toQUrl(originalUrl));
    request.setOriginatingObject(context ? context->originatingObject() : 0);

#if USE(HTTP2)
    static const bool NegotiateHttp2ForHttps = alpnIsSupported();
    if (originalUrl.protocolIs("https") && NegotiateHttp2ForHttps) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
        static const auto params = createHttp2Configuration();
        request.setHttp2Configuration(params);
#endif
        request.setAttribute(QNetworkRequest::HTTP2AllowedAttribute, true);
    }
#endif // USE(HTTP2)

    const HTTPHeaderMap &headers = httpHeaderFields();
    for (HTTPHeaderMap::const_iterator it = headers.begin(), end = headers.end();
         it != end; ++it) {
        QByteArray name = stringToByteArray(it->key);
        // QNetworkRequest::setRawHeader() would remove the header if the value is null
        // Make sure to set an empty header instead of null header.
        if (!it->value.isNull())
            request.setRawHeader(name, stringToByteArray(it->value));
        else
            request.setRawHeader(name, QByteArrayLiteral(""));
    }

    // Make sure we always have an Accept header; some sites require this to
    // serve subresources
    if (!request.hasRawHeader("Accept"))
        request.setRawHeader("Accept", "*/*");

    switch (cachePolicy()) {
    case ReloadIgnoringCacheData:
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
        break;
    case ReturnCacheDataElseLoad:
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
        break;
    case ReturnCacheDataDontLoad:
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysCache);
        break;
    case UseProtocolCachePolicy:
        // QNetworkRequest::PreferNetwork
    default:
        break;
    }

    if (!allowCookies() || !thirdPartyCookiePolicyPermits(context, url(), firstPartyForCookies())) {
        request.setAttribute(QNetworkRequest::CookieSaveControlAttribute, QNetworkRequest::Manual);
        request.setAttribute(QNetworkRequest::CookieLoadControlAttribute, QNetworkRequest::Manual);
    }

    if (!allowCookies())
        request.setAttribute(QNetworkRequest::AuthenticationReuseAttribute, QNetworkRequest::Manual);

    return request;
}

}

