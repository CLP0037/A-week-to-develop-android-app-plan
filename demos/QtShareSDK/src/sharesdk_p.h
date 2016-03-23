#ifndef SHARESDK_P_H
#define SHARESDK_P_H

#include <QDebug>

#ifdef Q_OS_ANDROID

#include <QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>

#define Q_SAFE_CALL_JAVA {                      \
    QAndroidJniEnvironment env;                 \
    if(env->ExceptionCheck()) {                 \
    qDebug() << "have a java exception";    \
    env->ExceptionClear();                  \
    }                                           \
    }



class ShareSDKPrivate
{
public:
    ShareSDKPrivate():
        m_init(false)
    {}

    virtual ~ShareSDKPrivate()
    {}

    // Ljava/lang/String;
    // Z
    // title
    // titleUrl
    // text
    // ImageUrl
    // Url
    // Comment
    // Site
    // SiteUrl
    // VenueName
    // VenueDescription

    void showShare(const QString& title,
                   const QString& titleUrl,
                   const QString& text,
                   const QString& imageUrl,
                   const QString& url,
                   const QString& comment,
                   const QString& site,
                   const QString& siteUrl,
                   const QString& venueName,
                   const QString& venueDescription
                   )
    {
        QAndroidJniObject OnekeyShare = QAndroidJniObject("cn/sharesdk/onekeyshare/OnekeyShare");
        Q_SAFE_CALL_JAVA

        jboolean silent = !false;
        // setSilent(boolean )
        OnekeyShare.callMethod<void>("setSilent", "(Z)V", silent);
        Q_SAFE_CALL_JAVA

        // setDialogMode()
        OnekeyShare.callMethod<void>("setDialogMode");
        Q_SAFE_CALL_JAVA

        // setTitle(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setTitle",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(title).object<jstring>());
        Q_SAFE_CALL_JAVA

        // setTitleUrl(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setTitleUrl",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(titleUrl).object<jstring>());
        Q_SAFE_CALL_JAVA

        // setText(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setText",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(text).object<jstring>());
        Q_SAFE_CALL_JAVA

        // setImageUrl(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setImageUrl",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(imageUrl).object<jstring>());
        Q_SAFE_CALL_JAVA

        // setUrl(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setUrl",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(url).object<jstring>());
        Q_SAFE_CALL_JAVA

        // setComment(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setComment",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(comment).object<jstring>());
        Q_SAFE_CALL_JAVA

        // setSite(Ljava/lang/String;));
        OnekeyShare.callMethod<void>("setSite",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(site).object<jstring>());
        Q_SAFE_CALL_JAVA

        // setSiteUrl(Ljava/lang/String;));
        OnekeyShare.callMethod<void>("setSiteUrl",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(siteUrl).object<jstring>());
        Q_SAFE_CALL_JAVA

        // setVenueName(Ljava/lang/String;));
        OnekeyShare.callMethod<void>("setVenueName",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(venueName).object<jstring>());
        Q_SAFE_CALL_JAVA


        // setVenueDescription(Ljava/lang/String;));
        OnekeyShare.callMethod<void>("setVenueDescription",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString(venueDescription).object<jstring>());
        Q_SAFE_CALL_JAVA

        //////////////////////////////////////////////////////////////////////////////////////////////

        //OnekeyShare.show(Landroid/content/Context;);
        OnekeyShare.callMethod<void>("show",
                                     "(Landroid/content/Context;)V",
                                     QtAndroid::androidActivity().object<jobject>());
        Q_SAFE_CALL_JAVA


    }

    void showShare(const QString& platformToShare, bool showContentEdit) {
        initSDK(QtAndroid::androidActivity());

        QAndroidJniObject OnekeyShare = QAndroidJniObject("cn/sharesdk/onekeyshare/OnekeyShare");

        Q_SAFE_CALL_JAVA

        // setSilent(boolean )
        jboolean silent = !showContentEdit;
        OnekeyShare.callMethod<void>("setSilent", "(Z)V", silent);
        Q_SAFE_CALL_JAVA

        //        // setPlatform(Ljava/lang/String;);
        //        OnekeyShare.callMethod<void>("setPlatform",
        //                                     "(Ljava/lang/String;)V",
        //                                     QAndroidJniObject::fromString(platformToShare).object<jstring>());
        //        Q_SAFE_CALL_JAVA

        // setDialogMode()
        OnekeyShare.callMethod<void>("setDialogMode");
        Q_SAFE_CALL_JAVA

        // setTitle(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setTitle",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString("ShareSDK--Title: Hello Qt").object<jstring>());
        Q_SAFE_CALL_JAVA

        // setTitleUrl(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setTitleUrl",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString("http://qtdream.com/").object<jstring>());
        Q_SAFE_CALL_JAVA

        // setText(Ljava/lang/String;);
        OnekeyShare.callMethod<void>("setText",
                                     "(Ljava/lang/String;)V",
                                     QAndroidJniObject::fromString("ShareSDK--Text: I'm from Qt").object<jstring>());
        Q_SAFE_CALL_JAVA

        //OnekeyShare.show(Landroid/content/Context;);
        OnekeyShare.callMethod<void>("show",
                                     "(Landroid/content/Context;)V",
                                     QtAndroid::androidActivity().object<jobject>());
        Q_SAFE_CALL_JAVA


    }

protected:
    void initSDK(QAndroidJniObject context) {
        // cn.sharesdk.framework.ShareSDK
        // initSDK(android.content.Context context)

        QAndroidJniObject::callStaticMethod<void>("cn/sharesdk/framework/ShareSDK",
                                                  "initSDK",
                                                  "(Landroid/content/Context;)V",
                                                  context.object<jobject>()
                                                  );

        QAndroidJniEnvironment env;
        if(env->ExceptionCheck()) {
            qDebug() << "have a java exception";
            env->ExceptionClear();
        } else {
            m_init = true;
        }
    }

    //static const char *javaFullClassName;

private:
    bool m_init;
};

#endif

#ifndef Q_OS_ANDROID
class ShareSDKPrivate
{
public:
    void showShare(const QString& , bool ) {}
    void showShare(const QString& title,
                   const QString& titleUrl,
                   const QString& text,
                   const QString& imageUrl,
                   const QString& url,
                   const QString& comment,
                   const QString& site,
                   const QString& siteUrl,
                   const QString& venueName,
                   const QString& venueDescription
                   )
    { }
};
#endif

#endif // SHARESDK_P_H

/*
 * 		//ShareSDK快捷分享提供两个界面第一个是九宫格 CLASSIC  第二个是SKYBLUE
        oks.setTheme(OnekeyShareTheme.CLASSIC);
        // 令编辑页面显示为Dialog模式
        oks.setDialogMode();
        // 在自动授权时可以禁用SSO方式
        oks.disableSSOWhenAuthorize();
        //oks.setAddress("12345678901"); //分享短信的号码和邮件的地址
        oks.setTitle("ShareSDK--Title");
        oks.setTitleUrl("http://mob.com");
        oks.setText("ShareSDK--文本");
        //oks.setImagePath("/sdcard/test-pic.jpg");  //分享sdcard目录下的图片
        oks.setImageUrl(randomPic()[0]);
        oks.setUrl("http://www.mob.com"); //微信不绕过审核分享链接
        //oks.setFilePath("/sdcard/test-pic.jpg");  //filePath是待分享应用程序的本地路劲，仅在微信（易信）好友和Dropbox中使用，否则可以不提供
        oks.setComment("分享"); //我对这条分享的评论，仅在人人网和QQ空间使用，否则可以不提供
        oks.setSite("ShareSDK");  //QZone分享完之后返回应用时提示框上显示的名称
        oks.setSiteUrl("http://mob.com");//QZone分享参数
        oks.setVenueName("ShareSDK");
        oks.setVenueDescription("This is a beautiful place!");
        // 将快捷分享的操作结果将通过OneKeyShareCallback回调
        //oks.setCallback(new OneKeyShareCallback());
        // 去自定义不同平台的字段内容
        //oks.setShareContentCustomizeCallback(new ShareContentCustomizeDemo());
        // 在九宫格设置自定义的图标
         Bitmap logo = BitmapFactory.decodeResource(context.getResources(), R.drawable.ic_launcher);
         String label = "ShareSDK";
         OnClickListener listener = new OnClickListener() {
            public void onClick(View v) {

            }
         };
         oks.setCustomerLogo(logo, label, listener);
*/
