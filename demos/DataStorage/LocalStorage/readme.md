# Qt For Android 数据库操作

> 作者：qyvlik

Qt 中的数据库操作，由于内嵌了一个 `sqlite` 数据库驱动，在普通应用中可以较为轻松地应付一些需求。

## Qt Quick Local Storage

`QML` 提供了一个 `QtQuick.LocalStorage` 模块，用以操作 `sqlite` 数据库。不支持异步。

这个模块实现了 [w3c 的 Web Database 标准](http://www.w3.org/TR/2009/WD-webdatabase-20091029/)。

所以可以参考[HTML5本地存储——Web SQL Database](http://www.cnblogs.com/dolphinX/p/3405335.html)。

> 由于Web SQL Database规范已经被废弃，原因说的很清楚，当前的 SQL 规范采用 SQLite 的 SQL 方言，而作为一个标准，这是不可接受的，每个浏览器都有自己的实现这还搞毛的标准。

当然，在 `QML` 的世界里大可不必担心这个。Qt 使用统一的实现标准，表现出来的平台无关性。

### 接口描述

`QtQuick.LocalStorage` 模块实现的是非异步的 Web SQL Database。

#### 打开数据库

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

#### 数据库对象 DatabaseSync

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

#### 执行 SQL 语句对象 SQLTransactionSync

如下是同步执行 `SQL` 语句的对象的 W3C 描述。

```
// typedef sequence<any> ObjectArray;

interface SQLTransactionSync {
    SQLResultSet executeSql(in DOMString sqlStatement, in optional ObjectArray arguments);
};
```

#### 执行 SQL 语句返回的结果对象 SQLResultSet

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

#### 执行 SQL 后报错

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

#### SQL 异常

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

## QtSql

### QSqlDatabase

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

#### 建立数据库文件

```
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("database.db");                              // 设置数据库文件的文件名以及路径，路径可不设置
```

#### 打开数据库并执行 SQL 操作

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

### QSqlQuery

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

#### 查询

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
