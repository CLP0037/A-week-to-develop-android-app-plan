#ifndef DATATYPEBRIDGE_H
#define DATATYPEBRIDGE_H

#include <QObject>
#include <QDebug>

#include <QUrl>
#include <QDate>
#include <QSizeF>
#include <QRectF>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

#include <QVariant>             // ==> var
#include <QJSValue>             // ==> 不同的 QQmlEngine 的 QJSValue 不能互相使用

#include <QJsonValue>
#include <QJsonObject>          //
#include <QJsonArray>           // 如果要传递一个异构数组，首选这个

class MyData
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)

public:
    MyData();

    MyData(int id);

    MyData(const MyData& other);

    MyData& operator=(const MyData& other);

    bool operator==(const MyData& rhs) const;

    bool operator !=(const MyData& rhs) const;

    int id() const;

    void setId(int id);

    Q_INVOKABLE void printId();

private:
    int m_id;
};

Q_DECLARE_METATYPE(MyData)


class DataTypeBridge : public QObject
{
    Q_OBJECT
    /*
     *     bool m_isBool;
    int m_isInt;
    double m_isDouble;
    qreal m_isReal;
    QString m_isString;
    QUrl m_isUrl;
    QDate m_isDate;
    QSizeF m_isSize;
    QRectF m_isRect;
    QMatrix4x4 m_isMatrix4x4;
    QQuaternion m_isQuaternion;
    QVector2D m_isVector2D;
    QVector3D m_isVector3D;
    QVector4D m_isVector4D;
    MyData m_isMyData;
*/
    Q_PROPERTY(bool isBool READ isBool WRITE setIsBool NOTIFY isBoolChanged)
    Q_PROPERTY(int isInt READ isInt WRITE setIsInt NOTIFY isIntChanged)
    Q_PROPERTY(double isDouble READ isDouble WRITE setIsDouble NOTIFY isDoubleChanged)
    Q_PROPERTY(qreal isReal READ isReal WRITE setIsReal NOTIFY isRealChanged)
    Q_PROPERTY(QString isString READ isString WRITE setIsString NOTIFY isStringChanged)
    Q_PROPERTY(QUrl isUrl READ isUrl WRITE setIsUrl NOTIFY isUrlChanged)
    Q_PROPERTY(QDate isDate READ isDate WRITE setIsDate NOTIFY isDateChanged)
    Q_PROPERTY(QSizeF isSize READ isSize WRITE setIsSize NOTIFY isSizeChanged)
    Q_PROPERTY(QMatrix4x4 isMatrix4x4 READ isMatrix4x4 WRITE setIsMatrix4x4 NOTIFY isMatrix4x4Changed)
    Q_PROPERTY(QQuaternion isQuaternion READ isQuaternion WRITE setIsQuaternion NOTIFY isQuaternionChanged)
    Q_PROPERTY(QVector2D isVector2D READ isVector2D WRITE setIsVector2D NOTIFY isVector2DChanged)
    Q_PROPERTY(QVector3D isVector3D READ isVector3D WRITE setIsVector3D NOTIFY isVector3DChanged)
    Q_PROPERTY(QVector4D isVector4D READ isVector4D WRITE setIsVector4D NOTIFY isVector4DChanged)
    Q_PROPERTY(MyData isMyData READ isMyData WRITE setIsMyData NOTIFY isMyDataChanged)

public:
    enum EnumType {
        EnumTypeA,
        EnumTypeB,
    };
    Q_ENUM(EnumType)

    explicit DataTypeBridge(QObject *parent = 0);

    bool isBool() const;
    void setIsBool(bool isBool);

    int isInt() const;
    void setIsInt(int isInt);

    double isDouble() const;
    void setIsDouble(double isDouble);

    qreal isReal() const;
    void setIsReal(const qreal &isReal);

    QString isString() const;
    void setIsString(const QString &isString);

    QUrl isUrl() const;
    void setIsUrl(const QUrl &isUrl);

    QDate isDate() const;
    void setIsDate(const QDate &isDate);

    QSizeF isSize() const;
    void setIsSize(const QSizeF &isSize);

    QRectF isRect() const;
    void setIsRect(const QRectF &isRect);

    QMatrix4x4 isMatrix4x4() const;
    void setIsMatrix4x4(const QMatrix4x4 &isMatrix4x4);

    QQuaternion isQuaternion() const;
    void setIsQuaternion(const QQuaternion &isQuaternion);

    QVector2D isVector2D() const;
    void setIsVector2D(const QVector2D &isVector2D);

    QVector3D isVector3D() const;
    void setIsVector3D(const QVector3D &isVector3D);

    QVector4D isVector4D() const;
    void setIsVector4D(const QVector4D &isVector4D);

    MyData isMyData() const;
    void setIsMyData(const MyData &isMyData);

signals:
    void isBoolChanged();
    void isIntChanged();
    void isDoubleChanged();
    void isRealChanged();
    void isStringChanged();
    void isUrlChanged();
    void isDateChanged();
    void isSizeChanged();
    void isRectChanged();
    void isMatrix4x4Changed();
    void isQuaternionChanged();
    void isVector2DChanged();
    void isVector3DChanged();
    void isVector4DChanged();
    void isMyDataChanged();

public slots:

    Q_INVOKABLE MyData generateMyData();

private:
    bool m_isBool;
    int m_isInt;
    double m_isDouble;
    qreal m_isReal;
    QString m_isString;
    QUrl m_isUrl;
    QDate m_isDate;
    QSizeF m_isSize;
    QRectF m_isRect;
    QMatrix4x4 m_isMatrix4x4;
    QQuaternion m_isQuaternion;
    QVector2D m_isVector2D;
    QVector3D m_isVector3D;
    QVector4D m_isVector4D;
    MyData m_isMyData;
};

#endif // DATATYPEBRIDGE_H
