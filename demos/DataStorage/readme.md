# Qt For Android 数据存储

> 作者：qyvlik

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

以下为部分摘要：

`QSettings::group` 对应到 `Settings::category`，`QSettings::setValue` 中的 `name` 参数对应到 `Settings` 中的属性。从上述代码可以看出，一个设置在一个应用中是全局唯一的，使用前缀以及名称进行区别。

`QSettings::group` 对应到 `Settings::category`，`QSettings::setValue` 中的 `name` 参数对应到 `Settings` 中的属性。

详细内容查看 [Qt For Android 设置](TestSettings\readme.md)。

## 数据库操作

`QML` 提供了一个 `QtQuick.LocalStorage` 模块，用以操作 `sqlite` 数据库。不支持异步。

这个模块实现了 [w3c 的 Web Database 标准](http://www.w3.org/TR/2009/WD-webdatabase-20091029/)。

所以可以参考[HTML5本地存储——Web SQL Database](http://www.cnblogs.com/dolphinX/p/3405335.html)。

> 由于Web SQL Database规范已经被废弃，原因说的很清楚，当前的 SQL 规范采用 SQLite 的 SQL 方言，而作为一个标准，这是不可接受的，每个浏览器都有自己的实现这还搞毛的标准。

当然，在 `QML` 的世界里大可不必担心这个。统一的实现标准，表现出来的平台无关性。

详细内容查看 [Qt For Android 数据库操作](LocalStorage\readme.md)。

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


