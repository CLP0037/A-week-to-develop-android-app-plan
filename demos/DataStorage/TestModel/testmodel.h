#ifndef TESTMODEL_H
#define TESTMODEL_H

#include <QAbstractListModel>
#include <QList>

class Dao
{
public:
    explicit Dao(const QString& name, int age);
    Dao(const Dao& other);
    Dao& operator=(const Dao& other);
    virtual ~Dao();

    QString name() const;
    void setName(const QString &name);

    int age() const;
    void setAge(int age);

private:
    QString m_name;
    int m_age;
};

class TestModel : public QAbstractListModel
{
    Q_OBJECT
 public:
    enum Roles{
        NameRole = Qt::UserRole + 1,
        AgeRole
    };

    TestModel(QObject* parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void addDao(const QString& name, int age);
    Q_INVOKABLE void sort();

private:
    QList<Dao> m_datas;
};




#endif // TESTMODEL_H
