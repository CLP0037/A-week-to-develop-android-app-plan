#include "datatypebridge.h"

DataTypeBridge::DataTypeBridge(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<EnumType>("DataTypeBridge::EnumType");
}

bool DataTypeBridge::isBool() const
{
    return m_isBool;
}

void DataTypeBridge::setIsBool(bool isBool)
{
    if(this->m_isBool != isBool) {
        m_isBool = isBool;
        Q_EMIT isBoolChanged();
    }
}

int DataTypeBridge::isInt() const
{
    return m_isInt;
}

void DataTypeBridge::setIsInt(int isInt)
{
    if(this->m_isInt != isInt) {
        m_isInt = isInt;
        Q_EMIT isIntChanged();
    }
}

double DataTypeBridge::isDouble() const
{
    return m_isDouble;
}

void DataTypeBridge::setIsDouble(double isDouble)
{
    if(m_isDouble != isDouble) {
        m_isDouble = isDouble;
        Q_EMIT isDoubleChanged();
    }
}

qreal DataTypeBridge::isReal() const
{
    return m_isReal;
}

void DataTypeBridge::setIsReal(const qreal &isReal)
{
    if(this->m_isReal != isReal) {
        m_isReal = isReal;
        Q_EMIT isRealChanged();
    }
}

QString DataTypeBridge::isString() const
{
    return m_isString;
}

void DataTypeBridge::setIsString(const QString &isString)
{
    if(this->m_isString != isString) {
        m_isString = isString;
        Q_EMIT isStringChanged();
    }
}

QUrl DataTypeBridge::isUrl() const
{
    return m_isUrl;
}

void DataTypeBridge::setIsUrl(const QUrl &isUrl)
{
    if(m_isUrl != isUrl) {
        m_isUrl = isUrl;
        Q_EMIT isUrlChanged();
    }
}

QDate DataTypeBridge::isDate() const
{
    return m_isDate;
}

void DataTypeBridge::setIsDate(const QDate &isDate)
{
    if(this->m_isDate != isDate) {
        m_isDate = isDate;
        Q_EMIT isDateChanged();
    }
}

QSizeF DataTypeBridge::isSize() const
{
    return m_isSize;
}

void DataTypeBridge::setIsSize(const QSizeF &isSize)
{
    if(this->m_isSize != isSize) {
        m_isSize = isSize;
        Q_EMIT isSizeChanged();
    }
}

QRectF DataTypeBridge::isRect() const
{
    return m_isRect;
}

void DataTypeBridge::setIsRect(const QRectF &isRect)
{
    if(this->m_isRect != isRect) {
        m_isRect = isRect;
        Q_EMIT isRectChanged();
    }
}

QMatrix4x4 DataTypeBridge::isMatrix4x4() const
{
    return m_isMatrix4x4;
}

void DataTypeBridge::setIsMatrix4x4(const QMatrix4x4 &isMatrix4x4)
{
    if(this->m_isMatrix4x4 != isMatrix4x4){
        m_isMatrix4x4 = isMatrix4x4;
        Q_EMIT isMatrix4x4Changed();
    }
}

QQuaternion DataTypeBridge::isQuaternion() const
{
    return m_isQuaternion;
}

void DataTypeBridge::setIsQuaternion(const QQuaternion &isQuaternion)
{
    if(this->m_isQuaternion != isQuaternion) {
        m_isQuaternion = isQuaternion;
        Q_EMIT isQuaternionChanged();
    }
}

QVector2D DataTypeBridge::isVector2D() const
{
    return m_isVector2D;
}

void DataTypeBridge::setIsVector2D(const QVector2D &isVector2D)
{
    if(this->m_isVector2D != isVector2D) {
        m_isVector2D = isVector2D;
        Q_EMIT isVector2DChanged();
    }
}

QVector3D DataTypeBridge::isVector3D() const
{
    return m_isVector3D;
}

void DataTypeBridge::setIsVector3D(const QVector3D &isVector3D)
{
    if(this->m_isVector3D != isVector3D) {
        m_isVector3D = isVector3D;
        Q_EMIT isVector3DChanged();
    }
}

QVector4D DataTypeBridge::isVector4D() const
{
    return m_isVector4D;
}

void DataTypeBridge::setIsVector4D(const QVector4D &isVector4D)
{
    if(this->m_isVector4D != isVector4D) {
        m_isVector4D = isVector4D;
        Q_EMIT isVector4DChanged();
    }
}

MyData DataTypeBridge::isMyData() const
{
    return m_isMyData;
}

void DataTypeBridge::setIsMyData(const MyData &isMyData)
{
    if(this->m_isMyData != isMyData) {
        m_isMyData = isMyData;
        Q_EMIT isMyDataChanged();
    }
}

MyData DataTypeBridge::generateMyData() {
    return MyData();
}

MyData::MyData() :
    m_id(0)
{ }

MyData::MyData(int id):
    m_id(id)
{ }

MyData::MyData(const MyData &other):
    m_id(other.m_id)
{ }

MyData &MyData::operator=(const MyData &other) {
    this->m_id = other.m_id;
    return *this;
}

bool MyData::operator==(const MyData &rhs) const{
    return this->m_id == rhs.m_id;
}

bool MyData::operator !=(const MyData &rhs) const{
    return this->m_id != rhs.m_id;
}

int MyData::id() const
{ return m_id; }

void MyData::setId(int id)
{ m_id = id; }

void MyData::printId() {
    qDebug() << this->m_id;
}
