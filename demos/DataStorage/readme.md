# Qt For Android 数据存储

数据存储在开发中是使用最频繁的，在这里主要介绍 Android 平台中实现数据存储的 5 种方式，分别是：

1. 使用 `SharedPreferences` 存储数据。

2. 数据库存储数据。

3. 文件存储数据。

4. 使用 `ContentProvider` 存储数据。

5. 网络存储数据。

以上文段摘自 [Android实现数据存储技术](http://www.cnblogs.com/hanyonglu/archive/2012/03/01/2374894.html)。

在 Qt For Android 开发中，恰好也有对应于上述五种数据存储的方式。

1. 设置保存。

2. 数据库操作。

3. 类似于 `ContentProvider` 的数据模型。

4. 文件存储。

5. 网络。

而且上述五种数据存储方式，都有对应的 `C++` 接口和 `QML` 接口，极大的方便了开发者的开发。本文章重点介绍 `QML` 接口。`C++` 接口会附上相关文章链接。

## 保存设置

保存设置是一款应用应该具备的功能。这里先介绍 `QML` 接口。

### Settings

```
import QtQuick.Window 2.1
import Qt.labs.settings 1.0

Window {
    id: window

    width: 800
    height: 600

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }
}
```

> 注意，`Qt.labs.settings` 模块可能在后期被移除。

上诉代码可以轻而易举的保存窗体的大小，并在下次启动时恢复窗体关闭时的大小。

通过设置 `Settings::category` 做到分组的效果。

### QSettings

> `C++` 中有 `QSettings`，`QSettings` 类提供“持久性”，平台独立的应用程序设置。意思是，程序关闭后 `QSettings` 把窗体大小，位置，用户设置的选项保存起来，下次打开程序时再重新加载。

> 如果你需要的是“非持久性” 基于内存的数据结构，可以考虑使用 `QMap<QString,QVariant>` 代替。

> 通常，对于Windows，配置信息保存在注册表中，Mac OS 是 `XML` 文件，`Unix` 是 `INI` 文件

具体用法和介绍可以查看如下文章：

[QSettings 用法（一）](http://blog.csdn.net/styyzxjq2009/article/details/8193594)

[Qt下QSettings类详解](http://yiluohuanghun.blog.51cto.com/3407300/952807)

不过需要注意的是，**不管是使用 `QML` 的 `Settings`，或者是`QSettings`，都需要设置一些应用的信息，例如应用名称，公司名称，域名，版本号等。另外，`Settings` 是基于 `QSettings` 而设计的， C++ 层面可以直接读取到 `QML` 的 `Settings`。**

```
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationDomain("github/gdpurjyfs");
    app.setOrganizationName("gdpurjyfs");
    app.setApplicationName("TestSettings");
    app.setApplicationDisplayName("TestSettings");
    app.setApplicationVersion("0.0.1");

    QSettings extraSettings;
    extraSettings.beginGroup("CPP");
    extraSettings.setValue("cppSettings", "this is cpp settings");
    extraSettings.endGroup();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // try to get settings that create in qml

    QSettings applicationWindowOption;
    // QVariant(int, 517)
    qDebug() << applicationWindowOption.value("ApplicationWindow/applicationWindowWidth");
    // "\\HKEY_CURRENT_USER\\Software\\gdpurjyfs\\TestSettings"
    qDebug() << applicationWindowOption.fileName();

    return app.exec();
}
```

```
import QtQuick 2.4
import QtQuick.Controls 1.3
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    title: qsTr("Test Settings")
    width: 640
    height: 480
    visible: true

    Settings {
        id: applicationWindowOption
        category: "ApplicationWindow"
        property alias applicationWindowWidth : window.width
        property alias applicationWindowHeight : window.height
    }

    Settings {
        id: tryToGetCPPSettings
        category: "CPP"
        property string cppSettings
    }

    Component.onCompleted: {
        try {
            // qml: tryToGetCPPSettings.cppSettings:  this is cpp settings
            console.log("tryToGetCPPSettings.cppSettings: ",
                        tryToGetCPPSettings.cppSettings);
        }catch(e){  console.log(e); }
    }
}
```

从上述代码可以看出，一个设置在一个应用中是全局唯一的，使用前缀以及名称进行区别。

`QSettings::group` 对应到 `Settings::category`，`QSettings::setValue` 中的 `name` 参数对应到 `Settings` 中的属性。从上述代码可以看出，一个设置在一个应用中是全局唯一的，使用前缀以及名称进行区别。

`QSettings::group` 对应到 `Settings::category`，`QSettings::setValue` 中的 `name` 参数对应到 `Settings` 中的属性。

## 数据库操作

### Qt Quick Local Storage

`QML` 提供了一个 `QtQuick.LocalStorage` 模块，用以操作 `sqlite` 数据库。不支持异步。

这个模块实现了 [w3c 的 Web Database 标准](http://www.w3.org/TR/2009/WD-webdatabase-20091029/)。

所以可以参考[HTML5本地存储——Web SQL Database](http://www.cnblogs.com/dolphinX/p/3405335.html)。

> 由于Web SQL Database规范已经被废弃，原因说的很清楚，当前的 SQL 规范采用 SQLite 的 SQL 方言，而作为一个标准，这是不可接受的，每个浏览器都有自己的实现这还搞毛的标准。

当然，在 `QML` 的世界里大可不必担心这个。统一的实现标准，表现出来的平台无关性。

#### 接口描述

`QtQuick.LocalStorage` 模块实现的是非异步的 Web SQL Database。

##### 打开数据库

W3C 标准描述了如下打开数据库的接口：

```
[Supplemental, NoInterfaceObject]
interface WindowDatabase {
    Database openDatabase(in DOMString name, 
                          in DOMString version, 
                          in DOMString displayName, 
                          in unsigned long estimatedSize, 
                          in optional DatabaseCallback creationCallback);
};
Window implements WindowDatabase;

[Supplemental, NoInterfaceObject]
interface WorkerUtilsDatabase {
    Database openDatabase(in DOMString name, 
                          in DOMString version, 
                          in DOMString displayName, 
                          in unsigned long estimatedSize, 
                          in optional DatabaseCallback creationCallback);
    
    DatabaseSync openDatabaseSync(in DOMString name, 
                                  in DOMString version, 
                                  in DOMString displayName, 
                                  in unsigned long estimatedSize, 
                                  in optional DatabaseCallback creationCallback);
};

WorkerUtils implements WorkerUtilsDatabase;

[Callback=FunctionOnly, NoInterfaceObject]
interface DatabaseCallback {
    void handleEvent(in Database database);
};
```

`QtQuick.LocalStorage` 模块实现了一个 `openDatabaseSync` 方法，返回数据库对象的句柄。

```
object openDatabaseSync(string name, 
                        string version, 
                        string description, 
                        int estimated_size, 
                        jsobject callback(db))
```

##### 数据库对象 DatabaseSync

同步数据库对象的 W3C 接口描述如下：

```
interface DatabaseSync {
    void transaction(in SQLTransactionSyncCallback callback);
    void readTransaction(in SQLTransactionSyncCallback callback);

    readonly attribute DOMString version;
    void changeVersion(in DOMString oldVersion, 
                       in DOMString newVersion, 
                       in optional SQLTransactionSyncCallback callback);
};

[Callback=FunctionOnly, NoInterfaceObject]
interface SQLTransactionSyncCallback {
    void handleEvent(in SQLTransactionSync transaction);
};
```

所以 `LocalStorage::openDatabaseSync` 返回的对象有 `transaction`，`readTransaction`，`changeVersion` 这些接口。

##### 执行 SQL 语句对象 SQLTransactionSync

如下是同步执行 `SQL` 语句的对象的 W3C 描述。

```
// typedef sequence<any> ObjectArray;

interface SQLTransactionSync {
    SQLResultSet executeSql(in DOMString sqlStatement, in optional ObjectArray arguments);
};
```

##### 执行 SQL 语句返回的结果对象 SQLResultSet

如下是执行 `SQL` 语句对象的返回结果的 W3C 描述。

```
interface SQLResultSet {
    readonly attribute long insertId;
    readonly attribute long rowsAffected;
    readonly attribute SQLResultSetRowList rows;
};

interface SQLResultSetRowList {
    readonly attribute unsigned long length;
    getter any item(in unsigned long index);
};
```

`SQLResultSetRowList` 可以通过 `item` 获取对应下标的数据。

##### 执行 SQL 后报错

执行 `SQL` 后报错对象的 W3C 描述。

```
interface SQLError {
    const unsigned short UNKNOWN_ERR = 0;
    const unsigned short DATABASE_ERR = 1;
    const unsigned short VERSION_ERR = 2;
    const unsigned short TOO_LARGE_ERR = 3;
    const unsigned short QUOTA_ERR = 4;
    const unsigned short SYNTAX_ERR = 5;
    const unsigned short CONSTRAINT_ERR = 6;
    const unsigned short TIMEOUT_ERR = 7;
    readonly attribute unsigned short code;
    readonly attribute DOMString message;
};
```

##### SQL 异常

执行 `SQL` 的异常对象的 W3C 描述。

```
exception SQLException {
    const unsigned short UNKNOWN_ERR = 0;
    const unsigned short DATABASE_ERR = 1;
    const unsigned short VERSION_ERR = 2;
    const unsigned short TOO_LARGE_ERR = 3;
    const unsigned short QUOTA_ERR = 4;
    const unsigned short SYNTAX_ERR = 5;
    const unsigned short CONSTRAINT_ERR = 6;
    const unsigned short TIMEOUT_ERR = 7;
    unsigned short code;
    DOMString message;
};
```


如下是在 `QML` 中测试的代码。

```
//! 打开一个数据库
var db = LocalStorage.openDatabaseSync("QQmlExampleDB", "1.0", "The Example QML SQL!", 1000000);

db.transaction(
    function(tx) {
        // 如果不存在表就创建
        tx.executeSql('CREATE TABLE IF NOT EXISTS Greeting(salutation TEXT, salutee TEXT)');

        // 插入记录
        tx.executeSql('INSERT INTO Greeting VALUES(?, ?)', [ 'hello', 'world' ]);

        // Show all added greetings
        //! rs is SQLResultSet type
        var rs = tx.executeSql('SELECT * FROM Greeting');

        var r = ""
        for(var i = 0; i < rs.rows.length; i++) {
            //! rs.rows is SQLResultSetRowList type
            r += rs.rows.item(i).salutation + ", " + rs.rows.item(i).salutee + "\n"
        }
        console.log(r);
    });
```

其次，是使用 `LocalStorage::openDatabaseSync` 打开数据库，产生的数据库文件的路径是可以通过 `QQmlEngine::offlineStoragePath` 获取。

如果是使用 `qmlscene.exe` 来运行的话，其数据库路径是 `C:\Users\Administrator\AppData\Local\QtProject\QtQmlViewer\QML\OfflineStorage\Databases`。不同电脑可能不同，仅供参考。

### QtSql

#### QSqlDatabase

常见操作：

```
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");     // 设置数据库驱动
db.setHostName("localhost");                                // 设置数据库主机名 
db.setDatabaseName("test");                                 // 设置数据库名 
db.setUserName("root");                                     // 设置数据库登入用户名 
db.setPassword("123456");                                   // 设置数据库登入密码 
db.open();                                                  // 打开数据库连接
db.close();                                                 // 释放数据库
```

##### 建立数据库文件

```
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("database.db");                              // 设置数据库文件的文件名以及路径，路径可不设置
```

##### 打开数据库并执行 SQL 操作

```
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("database.db");                              // 设置数据库文件的文件名以及路径，路径可不设置
if(!db.open()) return false;

QSqlQuery query;
//id会自动增加，因为这里不能重复，否则数据库无法修改
query.exec("create table Login(id INTEGER PRIMARY KEY autoincrement, "  
           "goods int, store int, time nvarchar(50), type int,  place nvarchar(50),temperature nvarchar(10) )");

query.exec("insert into Login values( 1,NULL , NULL,NULL, NULL,NULL,NULL )");
query.exec("insert into Login values( 2,NULL , NULL,NULL, NULL,NULL,NULL )");
query.exec("insert into Login values( 3,NULL , NULL,NULL, NULL,NULL,NULL )");
query.exec("insert into Login values( 4,NULL , NULL,NULL, NULL,NULL,NULL )");
query.exec("insert into Login values( 5,NULL , NULL,NULL, NULL,NULL,NULL )");
query.exec("insert into Login values( 6,NULL , NULL,NULL, NULL,NULL,NULL )");
```

#### QSqlQuery

常用的函数：

```
seek(int n);                // query指向结果集的第n条记录。指定当前的位置
first();                    // query指向结果集的第一条记录。
last();                     // query指向结果集的最后一条记录。
next();                     // query指向下一条记录，每执行一次该函数，便指向相邻的下一条记录。
previous();                 // query指向上一条记录，每执行一次该函数，便指向相邻的上一条记录。
record();                   // 获得现在指向的记录。
value(int n);               // 获得属性的值。与创建表的时候，列名顺序有关。
```

##### 查询

```
// 假设有 student 这个表 student(text name, int age)
query.exec(“select * from student”); 
```

这条语句执行完后，我们便获得了相应的执行结果，因为获得的结果可能不止一条记录，所以我们称之为结果集。

使用如下语句进行结果集遍历：

```
while(query.next()) {
    QString name = query.value(0).toString(); //返回"name"字段的索引值"justin",value(i)返回i字段的值，0表示name，1表示age
    int id = query.value(1).toInt();
    // query.value("age").toInt();
    // query.value("name").toString();
}
```

其他详细的文档可以参考 Qt 帮助文档，或者参考下列文章：

[Qt数据库总结](http://blog.csdn.net/styyzxjq2009/article/details/7967481)

## 数据模型

> Model/View 结构

> Model-View-Controller(MVC)， 是从Smalltalk发展而来的一种设计模式，常被用于构建用户界面。

> 经典设计模式的著作中有这样的描述：

> MVC 由三种对象组成。Model 是应用程序对象，View是它的屏幕表示，Controller定义了用户界面如何对用户输入进行响应。

> 在 MVC 之前，用户界面设计倾向于三者揉合在一起，MVC对它们进行了解耦，提高了灵活性与重用性。

> 假如把 view 与 controller 结合在一起，结果就是 model/view 结构。这个结构依然是把数据存储与数据表示进行了分离，它与 MVC 都基于同样的思想，但它更简单一些。这种分离使得在几个不同的 view 上显示同一个数据成为可能，也可以重新实现新的 view，而不必改变底层的数据结构。为了更灵活的对用户输入进行处理，引入了 delegate 这个概念。它的好处是，数据项的渲染与编程可以进行定制。

摘自 [Qt Model/View（ 一）](http://blog.csdn.net/leo115/article/details/7532677)

其他文章：

[Qt的Model/View （二）](http://blog.csdn.net/leo115/article/details/7532682)



### QML 数据模型接口

QML 中的数据模型接口有 `ListModel`，以及由 `C++` 中重写后注册到 `QML` 运行环境的 `QAbstractItemModel` 或者 `QAbstractListModel`。

QML 中的视图类有 `ListView`，`GridView` 以及 `PathView`。

这里取最常用的 `ListView` 作为例子：

```
ListView {
    anchors.fill: parent
    model: fruitModel
    delegate: Row {
        Text { text: "Fruit: " + name }
        Text { text: "Cost: $" + cost }
    }
    ListModel {
        id: fruitModel

        ListElement {
            name: "Apple"
            cost: 2.45
        }
        ListElement {
            name: "Orange"
            cost: 3.25
        }
        ListElement {
            name: "Banana"
            cost: 1.95
        }
    }
}
```

回到 `ListModel` 本身，有如下常用的方法：

```
append(jsobject dict)
clear()
object get(int index)
insert(int index, jsobject dict)
move(int from, int to, int n)
remove(int index, int count)
set(int index, jsobject dict)
setProperty(int index, string property, variant value)
sync()
```

`ListModel` 本身可以很好地和 `JSON` 交互，并且支持多线程异步操作，但是没有提供排序的接口。

### QAbstractListModel

继承 `QAbstractItemModel` 或者 `QAbstractListModel`，重写一些虚函数，然后注册到 `QML` 的运行环境中，就可以获取到强大的支持。例如提供持久化数据，排序，统计等一些与业务相关的接口。

暂未找到相关例子。

## 文件存储

### 纯的QML实现文件的下载和保存

#### 图片

`bool Item::grabToImage(callback, targetSize)`

例子：

```
// reslut is ItemGrabResult type
source.grabToImage(function(result) {
                       result.saveToFile("something.png");
                   },Qt.size(50, 50));
```

可以直接将图片以指定的路径和大小保存。

成功返回 `true`。

#### 文本文件

```
var xhr = new XMLHttpRequest;
xhr.onreadystatechange = function() {
                    if (doc.readyState == XMLHttpRequest.HEADERS_RECEIVED) {
                        console.log(doc.getAllResponseHeaders());
                    } else if (doc.readyState == XMLHttpRequest.DONE) {
                        console.log(doc.getAllResponseHeaders());
                    }
                };
xhr.open("PUT", "qml_data.txt");
var save_data = "some data from qml.";
xhr.send(save_data);
```

将获取到的 `save_data` 保存到本地路径。

但是 `XMLHttpRequest` 的 `DELETE` 方法是不能删除本地一个文件的。

#### 二进制文件

其他二进制文件暂时无法通过 `QML` 的 `XMLHttpRequest` 来处理。

### C++ 文件操作

在 C++ 中，文件操作接口就相对丰富了。

请查阅 `QIODevice` 及其派生子类。


