#include "testmodel.h"

#include <QDebug>

TestModel::TestModel(QObject *parent):
    QAbstractListModel(parent)
{

}


int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_datas.length();
}


QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0)
        return QVariant();

    if (index.row() >= m_datas.count()) {
        qWarning() << "SatelliteModel: Index out of bound";
        return QVariant();
    }
    const Dao &dao = m_datas.at(index.row());
    switch (role)
    {
    case NameRole:
        return dao.name();
    case AgeRole:
        return dao.age();
    default:
        break;
    }
    return QVariant();
}


QHash<int, QByteArray> TestModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames.insert(NameRole, "NameRole");
    roleNames.insert(AgeRole, "AgeRole");
    return roleNames;
}

void TestModel::addDao(const QString &name, int age)
{
    beginResetModel();
    m_datas.append(Dao(name, age));
    endResetModel();
}

void TestModel::sort()
{
    beginResetModel();

    qDebug() << "start sort" ;

    std::sort(m_datas.begin(),
              m_datas.end(),
              [](const Dao& lhs, const Dao& rhs) -> bool {
        return lhs.age() < rhs.age();
    });

    qDebug() << "end sort" ;

    endResetModel();
}


Dao::Dao(const QString &name, int age):
    m_name(name),
    m_age(age)
{

}


Dao::Dao(const Dao &other):
    m_name(other.m_name),
    m_age(other.m_age)
{

}


Dao &Dao::operator=(const Dao &other)
{
    this->m_name = other.m_name;
    this->m_age = other.m_age;
    return *this;
}


Dao::~Dao()
{

}

QString Dao::name() const
{
    return m_name;
}


void Dao::setName(const QString &name)
{
    m_name = name;
}
int Dao::age() const
{
    return m_age;
}

void Dao::setAge(int age)
{
    m_age = age;
}

