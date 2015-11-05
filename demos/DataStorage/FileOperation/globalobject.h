#ifndef GLOBALOBJECT_H
#define GLOBALOBJECT_H

#include <QObject>
#include <QJSValue>

class QQmlEngine;

class Foo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int age WRITE setAge READ age NOTIFY ageChanged)
public:
    explicit Foo(QObject* parent = 0);
    ~Foo();
    int age() const;
    void setAge(int age);

signals:
    void ageChanged(int age);
private:
    int m_age;
};

class GlobalObject : public QObject
{
    Q_OBJECT
public:
    explicit GlobalObject(QObject *parent = 0);
    Q_INVOKABLE Foo* newFooObject();
    Q_INVOKABLE QObject* newQObject();
};

#endif // GLOBALOBJECT_H
