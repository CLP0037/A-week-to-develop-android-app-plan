#include "callnativegallery.h"
#include <QtDebug>

#ifdef  Q_OS_ANDROID

#include <QAndroidActivityResultReceiver>
#include <QtAndroid>
#include <QAndroidJniEnvironment>

#define Q_SAFE_CALL_JAVA {                  \
    QAndroidJniEnvironment env;             \
    if(env->ExceptionCheck()) {             \
    qDebug() << "have a java exception";    \
    env->ExceptionDescribe();               \
    env->ExceptionClear();                  \
    }                                       \
    }


class CallNativeGallery;
class GalleryResultReceiver: public QAndroidActivityResultReceiver
{
public:
    explicit GalleryResultReceiver()
    { }


    void handleActivityResult(int receiverRequestCode,
                              int resultCode,
                              const QAndroidJniObject &data)
    {
        if(resultCode == -1 && GalleryResultReceiver::ReceiverRequestCode == receiverRequestCode) {
            if(data.isValid()) {
                // android/net/Uri
                // android/net/Uri getData()
                QAndroidJniObject uri = data.callObjectMethod("getData", "()Landroid/net/Uri;");
                notify->finished(getLocalPathFromUri(uri));
            } else {
                notify->error("Data isn't valid");
            }
        } else {
            notify->error(QString("resultCode:%1, Data: %2").arg(resultCode).arg(data.toString()));
        }
    }

    QString getLocalPathFromUri(const QAndroidJniObject& uri) {
        // uri: Landroid/net/Uri;
        // [url](http://stackoverflow.com/questions/34163437/qt-and-android-gallery-mediastore-using-qandroidjniobject)

        QAndroidJniObject dadosAndroid
                = QAndroidJniObject::getStaticObjectField(
                    "android/provider/MediaStore$MediaColumns",
                    "DATA",
                    "Ljava/lang/String;");

        QAndroidJniEnvironment env;
        jobjectArray projecao
                = (jobjectArray)env->NewObjectArray(1,
                                                    env->FindClass("java/lang/String"),
                                                    NULL);

        jobject projacaoDadosAndroid
                = env->NewStringUTF(dadosAndroid.toString().toStdString().c_str());

        env->SetObjectArrayElement(projecao, 0, projacaoDadosAndroid);

        QAndroidJniObject contentResolver
                = QtAndroid::androidActivity()
                .callObjectMethod("getContentResolver",
                                  "()Landroid/content/ContentResolver;");

        QAndroidJniObject cursor
                = contentResolver.callObjectMethod("query",
                                                   "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;",
                                                   uri.object<jobject>(), projecao, NULL, NULL, NULL);

        jint columnIndex = cursor.callMethod<jint>("getColumnIndex",
                                                   "(Ljava/lang/String;)I",
                                                   dadosAndroid.object<jstring>());

        cursor.callMethod<jboolean>("moveToFirst", "()Z");

        QAndroidJniObject resultado
                = cursor.callObjectMethod("getString",
                                          "(I)Ljava/lang/String;",
                                          columnIndex);

        QString imagemCaminho = "file://" + resultado.toString();

        return imagemCaminho;
    }

    static const int ReceiverRequestCode;
    CallNativeGallery* notify;
};

const int GalleryResultReceiver::ReceiverRequestCode = 1;

#endif

CallNativeGallery::CallNativeGallery(QObject *parent) : QObject(parent)
{

}

static GalleryResultReceiver* galleryResultReceiver = new GalleryResultReceiver();

void CallNativeGallery::openGallery()
{
#ifdef  Q_OS_ANDROID
    // android.content.Intent.ACTION_GET_CONTENT

    QAndroidJniObject action = QAndroidJniObject::getStaticObjectField(
                "android/content/Intent",
                "ACTION_GET_CONTENT",
                "Ljava/lang/String;");

    QAndroidJniObject intent("android/content/Intent",
                             "(Ljava/lang/String;)V",
                             action.object<jstring>());
    Q_SAFE_CALL_JAVA

    // Intent setType(String type)
    QAndroidJniObject type = QAndroidJniObject::fromString("image/*");
    intent.callObjectMethod("setType",
                            "(Ljava/lang/String;)Landroid/content/Intent;",
                            type.object<jstring>());

    Q_SAFE_CALL_JAVA

    galleryResultReceiver->notify = this;


    QtAndroid::startActivity(intent,
                             GalleryResultReceiver::ReceiverRequestCode,
                             galleryResultReceiver);



#endif
}

