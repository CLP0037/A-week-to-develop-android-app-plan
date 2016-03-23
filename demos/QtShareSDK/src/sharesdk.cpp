#include "sharesdk.h"

#include "sharesdk_p.h"

ShareSDK ShareSDK::shareSDK;

ShareSDK::ShareSDK(QObject *parent) :
    QObject(parent),
    d_ptr(new ShareSDKPrivate)
{

}

ShareSDK::~ShareSDK()
{
    delete d_ptr;
}

void ShareSDK::showShare(const QString &title,
                         const QString &titleUrl,
                         const QString &text,
                         const QString &imageUrl,
                         const QString &url,
                         const QString &comment,
                         const QString &site,
                         const QString &siteUrl,
                         const QString &venueName,
                         const QString &venueDescription)
{
    d_ptr->showShare(title, titleUrl, text, imageUrl, url, comment, site, siteUrl, venueName, venueDescription);
}

QObject *ShareSDK::singletonProvider(QQmlEngine *, QJSEngine *)
{
    return &shareSDK;
}


