#ifndef SHARESDK_H
#define SHARESDK_H

#include <QObject>

class QQmlEngine;
class QJSEngine;
class ShareSDKPrivate;
class ShareSDK : public QObject
{
    Q_OBJECT
    explicit ShareSDK(QObject *parent = 0);

public:
    ~ShareSDK();

    Q_INVOKABLE void showShare(const QString& title,
                               const QString& titleUrl,
                               const QString& text,
                               const QString& imageUrl,
                               const QString& url,
                               const QString& comment,
                               const QString& site,
                               const QString& siteUrl,
                               const QString& venueName,
                               const QString& venueDescription
                               );

    static QObject *singletonProvider(QQmlEngine *engine = 0, QJSEngine *scriptEngine=0);

private:
    ShareSDKPrivate* d_ptr;

protected:
    static ShareSDK shareSDK;
};

#endif // SHARESDK_H
