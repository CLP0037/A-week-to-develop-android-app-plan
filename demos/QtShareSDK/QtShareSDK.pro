TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    src/sharesdk.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

android {
    QT += androidextras
}


DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/libs/MobCommons-2016.0301.1053.jar \
    android/libs/MobTools-2016.0301.1053.jar \
    android/libs/ShareSDK-Alipay-2.7.0.jar \
    android/libs/ShareSDK-Core-2.7.0.jar \
    android/libs/ShareSDK-KaiXin-2.7.0.jar \
    android/libs/ShareSDK-QQ-2.7.0.jar \
    android/libs/ShareSDK-SinaWeibo-2.7.0.jar \
    android/libs/ShareSDK-Tumblr-2.7.0.jar \
    android/libs/ShareSDK-Wechat-2.7.0.jar \
    android/libs/ShareSDK-Wechat-Core-2.7.0.jar \
    android/libs/ShareSDK-Wechat-Favorite-2.7.0.jar \
    android/libs/ShareSDK-Wechat-Moments-2.7.0.jar \
    android/assets/ShareSDK.xml \
    android/res/drawable/ssdk_oks_classic_platform_cell_back.xml \
    android/res/drawable/ssdk_oks_classic_progressbar.xml \
    android/res/values/ssdk_instapaper_strings.xml \
    android/res/values/ssdk_oks_color_drawables.xml \
    android/res/values/ssdk_oks_strings.xml \
    android/res/values/ssdk_strings.xml \
    android/res/values-en/ssdk_oks_strings.xml \
    android/res/values-en/ssdk_strings.xml \
    android/res/drawable-hdpi/ssdk_oks_ptr_ptr.png \
    android/res/drawable-xhdpi/ssdk_auth_title_back.png \
    android/res/drawable-xhdpi/ssdk_back_arr.png \
    android/res/drawable-xhdpi/ssdk_logo.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_alipay.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_bluetooth.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_check_checked.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_check_default.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_douban.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_dropbox.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_email.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_evernote.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_facebook.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_facebookmessenger.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_flickr.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_foursquare.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_googleplus.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_instagram.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_instapaper.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_kaixin.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_kakaostory.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_kakaotalk.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_laiwang.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_laiwangmoments.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_line.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_linkedin.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_mingdao.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_pinterest.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_pocket.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_qq.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_qzone.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_renren.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_shortmessage.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_sinaweibo.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_tencentweibo.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_tumblr.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_twitter.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_vkontakte.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_wechat.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_wechatfavorite.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_wechatmoments.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_whatsapp.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_yixin.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_yixinmoments.png \
    android/res/drawable-xhdpi/ssdk_oks_classic_youdao.png \
    android/res/drawable-xhdpi/ssdk_title_div.png \
    android/src/cn/sharesdk/onekeyshare/themes/classic/land/EditPageLand.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/land/FriendListPageLand.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/land/PlatformPageAdapterLand.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/land/PlatformPageLand.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/port/EditPagePort.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/port/FriendListPagePort.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/port/PlatformPageAdapterPort.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/port/PlatformPagePort.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/ClassicTheme.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/EditPage.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/FriendAdapter.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/FriendListItem.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/FriendListPage.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/IndicatorView.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/PicViewerPage.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/PlatformPage.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/PlatformPageAdapter.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/PRTHeader.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/RotateImageView.java \
    android/src/cn/sharesdk/onekeyshare/themes/classic/XView.java \
    android/src/cn/sharesdk/onekeyshare/CustomerLogo.java \
    android/src/cn/sharesdk/onekeyshare/OnekeyShare.java \
    android/src/cn/sharesdk/onekeyshare/OnekeySharePage.java \
    android/src/cn/sharesdk/onekeyshare/OnekeyShareTheme.java \
    android/src/cn/sharesdk/onekeyshare/OnekeyShareThemeImpl.java \
    android/src/cn/sharesdk/onekeyshare/ShareContentCustomizeCallback.java \
    android/src/org/gdpurjyfs/qtsharesdk/apshare/ShareEntryActivity.java \
    android/src/org/gdpurjyfs/qtsharesdk/wxapi/WXEntryActivity.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    src/sharesdk.h \
    src/sharesdk_p.h

