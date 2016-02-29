# QML 开发神秘加成之为网络资源设置本地缓存

## 直接运行 qmlproject

体会一下图片没有本地缓存的情况下，浏览大量图片的体验，在手机上流量更是刷刷。

## 直接运行 pro

一些网络图片，在加载前就会访问本地是否有缓存，如果有，就直接拉取本地。注意 `XMLHttpRequest` 的内部实现是拥有另一个 `NetworkAccessManager`，所以这个工厂构建的 `NetworkAccessManager` 无法对 `XMLHttpReuqest` 产生作用。效果好于没有设置本地缓存的。

暂时不知是否对本地高清图片有缓存的功能（应该是没有的）。

