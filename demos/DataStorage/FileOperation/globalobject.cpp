#include "globalobject.h"

#include <QQmlEngine>
#include <QDebug>

GlobalObject::GlobalObject(QObject *parent)
    : QObject(parent)
{

}

Foo *GlobalObject::newFooObject()
{
    Foo * ret = new Foo();
    QQmlEngine::setObjectOwnership(ret, QQmlEngine::JavaScriptOwnership);
    return ret;
}

QObject *GlobalObject::newQObject()
{
    QObject* object = new QObject;
    object->setObjectName("object");
    QQmlEngine::setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);
    return object;
}

Foo::Foo(QObject *parent):
    QObject(parent)
{

}


Foo::~Foo()
{
    qDebug() << "destory: " << this ;
}


int Foo::age() const
{
    return m_age;
}


void Foo::setAge(int age)
{
    if(m_age != age) {
        m_age = age;
        emit ageChanged(m_age);
    }
}

