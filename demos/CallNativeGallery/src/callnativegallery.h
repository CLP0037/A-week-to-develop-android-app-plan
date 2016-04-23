#ifndef CALLNATIVEGALLERY_H
#define CALLNATIVEGALLERY_H

#include <QObject>
#include <QString>

class CallNativeGallery : public QObject
{
    Q_OBJECT
public:
    explicit CallNativeGallery(QObject *parent = 0);

    Q_INVOKABLE void openGallery();

signals:
    void finished(QString imageList);
    void error(QString errorString);

public slots:
};

#endif // CALLNATIVEGALLERY_H
