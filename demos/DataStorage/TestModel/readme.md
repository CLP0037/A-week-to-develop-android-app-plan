# Qt For Android 数据模型

> Model/View 结构

> Model-View-Controller(MVC)， 是从Smalltalk发展而来的一种设计模式，常被用于构建用户界面。

> 经典设计模式的著作中有这样的描述：

> MVC 由三种对象组成。Model 是应用程序对象，View是它的屏幕表示，Controller定义了用户界面如何对用户输入进行响应。

> 在 MVC 之前，用户界面设计倾向于三者揉合在一起，MVC对它们进行了解耦，提高了灵活性与重用性。

> 假如把 view 与 controller 结合在一起，结果就是 model/view 结构。这个结构依然是把数据存储与数据表示进行了分离，它与 MVC 都基于同样的思想，但它更简单一些。这种分离使得在几个不同的 view 上显示同一个数据成为可能，也可以重新实现新的 view，而不必改变底层的数据结构。为了更灵活的对用户输入进行处理，引入了 delegate 这个概念。它的好处是，数据项的渲染与编程可以进行定制。

摘自 [Qt Model/View（ 一）](http://blog.csdn.net/leo115/article/details/7532677)

其他文章：

[Qt的Model/View （二）](http://blog.csdn.net/leo115/article/details/7532682)

## QML 数据模型接口

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

## QAbstractListModel

继承 `QAbstractItemModel` 或者 `QAbstractListModel`，重写一些虚函数，然后注册到 `QML` 的运行环境中，就可以获取到强大的支持。例如提供持久化数据，排序，统计等一些与业务相关的接口。

这个子类重载是三个虚函数：

```
int rowCount(const QModelIndex &parent) const;
QVariant data(const QModelIndex &index, int role) const;
QHash<int, QByteArray> roleNames() const;
```
