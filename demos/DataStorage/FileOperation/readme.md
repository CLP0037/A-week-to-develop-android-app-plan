# Qt For Android 文件存储

> 作者：qyvlik

## 纯的QML实现文件的下载和保存

### 图片

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

### 文本文件

以下方法在 Qt 5 中无效。

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

> **上诉方法无法在 Qt 5.5.0 通过。Qt 官方应该认为其是个漏洞，不允许文件的创建和写操作。**

### 二进制文件

其他二进制文件暂时无法通过 `QML` 的 `XMLHttpRequest` 来处理。

## C++ 文件操作

在 C++ 中，文件操作接口就相对丰富了。

请查阅 `QIODevice` 及其派生子类。

## 路径

文件操作涉及路径，在安卓中，如何设置一个合理的读写路径。

**TODO**
