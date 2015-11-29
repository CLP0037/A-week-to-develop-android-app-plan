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

详细内容查看 [Qt For Android 数据模型](TestModel\readme.md)。

## 文件存储

### 纯的QML实现文件的下载和保存

#### 图片

`bool Item::grabToImage(callback, targetSize)`

例子：

```
// reslut is ItemGrabResult type
source.grabToImage(function(result) {
                       // 不能是 file:// 开头
                       result.saveToFile("something.png");
                   },Qt.size(50, 50));
```

可以直接将图片以指定的路径和大小保存。

成功返回 `true`。

#### 文本文件

```

    function saveText(filename, contentText) {
        var xhr = new XMLHttpRequest;
        xhr.onreadystatechange = function() {
            if (xhr.readyState == XMLHttpRequest.HEADERS_RECEIVED) {
                console.log(xhr.getAllResponseHeaders());
            } else if (xhr.readyState == XMLHttpRequest.DONE) {
                console.log(xhr.getAllResponseHeaders());
            }
        };
        xhr.open("PUT", filename);
        xhr.send(contentText.toString());
        xhr.open("PUT", filename);
        xhr.send(contentText.toString());
    }
```

将获取到的 `save_data` 保存到本地路径。

但是 `XMLHttpRequest` 的 `DELETE` 方法是不能删除本地一个文件的。

~~上诉方法无法在 Qt 5.5.0 通过。Qt 官方应该认为其是个漏洞，不允许文件的创建和写操作。~~

修复了这个问题，`xhr.open` 和 `xhr.send` 两次，就可以向本地路径新建一个文件并写入数据了。

#### 二进制文件

其他二进制文件暂时无法通过 `QML` 的 `XMLHttpRequest` 来处理。

### C++ 文件操作

在 C++ 中，文件操作接口就相对丰富了。

请查阅 `QIODevice` 及其派生子类。

详细内容查看 [Qt For Android 文件存储](FileOperation\readme.md)。

## 网络

### QML XMLHttpRequest

[W3C XMLHttpRequest 标准](http://www.w3.org/TR/XMLHttpRequest/)。

`XMLHttpRequest` 的 W3C 接口描述如下：

```
[NoInterfaceObject]
interface XMLHttpRequestEventTarget : EventTarget {
    // event handlers
    attribute EventHandler onloadstart;
    attribute EventHandler onprogress;
    attribute EventHandler onabort;
    attribute EventHandler onerror;
    attribute EventHandler onload;
    attribute EventHandler ontimeout;
    attribute EventHandler onloadend;
};

interface XMLHttpRequestUpload : XMLHttpRequestEventTarget {

};

enum XMLHttpRequestResponseType {
    "",
    "arraybuffer",
    "blob",
    "document",
    "json",
    "text"
};

[Constructor]
interface XMLHttpRequest : XMLHttpRequestEventTarget {
    // event handler
    attribute EventHandler onreadystatechange;

    // states
    const unsigned short UNSENT = 0;
    const unsigned short OPENED = 1;
    const unsigned short HEADERS_RECEIVED = 2;
    const unsigned short LOADING = 3;
    const unsigned short DONE = 4;
    readonly attribute unsigned short readyState;

    // request
    void open(ByteString method, [EnsureUTF16] DOMString url);
    void open(ByteString method, 
             [EnsureUTF16] DOMString url, 
             boolean async, 
             optional [EnsureUTF16] DOMString? username = null, 
             optional [EnsureUTF16] DOMString? password = null);
    void setRequestHeader(ByteString header, ByteString value);
    attribute unsigned long timeout;
    attribute boolean withCredentials;
    readonly attribute XMLHttpRequestUpload upload;
    void send(optional (ArrayBufferView or Blob or Document or [EnsureUTF16] DOMString or FormData)? data = null);
    void abort();

    // response
    readonly attribute unsigned short status;
    readonly attribute ByteString statusText;
    ByteString? getResponseHeader(ByteString header);
    ByteString getAllResponseHeaders();
    void overrideMimeType(DOMString mime);
    attribute XMLHttpRequestResponseType responseType;
    readonly attribute any response;
    readonly attribute DOMString responseText;
    readonly attribute Document? responseXML;
};
```

在 `QML` 中只实现了 XMLHttpRequest Level 1 标准。


