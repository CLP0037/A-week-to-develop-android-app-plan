# A-week-to-develop-android-app-plan by using Qt

一周开发 Android App 计划之 Qt on Android。

修改自[一周开发Android App计划](https://github.com/fanatic-mobile-developer-for-android/A-week-to-develop-android-app-plan)。

## 开发工具&&语言

- Qt Creator
    - QML
    - C++

- Android Studio
    - Java

## 目的

- 减少转战 Android 的 Qt 程序猿重复搬运代码。
- 打造快速开发 APP 开源库，一个星期开发一个 APP 的愿望。
- 脱离苦逼加班，让程序猿提前下班跟女神去优衣库。

## 题目

1. [启动页](demos/SplashScreen/doc/readme.md)

2. [引导页](demos/Guide/doc/readme.md)

3. [PageStackWindow框架](https://github.com/GDPURJYFS/Sparrow)

4. [数据存储](demos/DataStorage/readme.md)

    - [设置保存](demos/DataStorage/TestSettings/readme.md)

    - [数据库操作](demos/DataStorage/LocalStorage/readme.md)

    - [数据模型](demos/DataStorage/TestModel/readme.md)

    - [文件存储](demos/DataStorage/FileOperation/readme.md)

    - [网络](https://github.com/qyvlik/QmlNetwork)

    - [文件读写](https://github.com/qyvlik/QmlNetwork)

5. [集成社交化插件](demos/QtShareSDK/readme.md)

    后续继续研究如何登陆与支付。

6. [缓存管理](demos/NetworkImageCache/readme.md)

7. 后台任务处理

    - [多线程处理](https://github.com/qyvlik/QmlThread)

    - 聊天图片的接收和发送

    - 后台文件下载

    - 消息推送

8. 圆角图片
    - 圆形头像
    - [csdn-寒山居士-图片圆形裁剪](http://blog.csdn.net/esonpo/article/details/37762239)

9. 多媒体处理
    - [图片选择库](demos/CallNativeCamera/readme.md)
    - 图片上传下载
    - 图片处理
    - 图片浏览（左右切换，可放大）
    - [拍照功能](demos/CallNativeCamera/readme.md)

10. 文件处理
    - 文件过滤
    - 系统分类文件路径
    - 应用缓存路径
    - 应用运行路径
    - 日志处理

11. ListView
    - 下拉更新
    - 底部加载更多
    - 跳转设置页
    - 快速返回顶部

12. 系统接口
    - 跳转拨号
    - 自动拨号
    - 跳转到信息发送界面
    - 自动发送信息
    - 检查应用是否安装

13. 自定义控件
    - 进度条
    - 自定义对话框
    - PopupWindow
    - WebView
    - [FileIO 控件](http://blog.csdn.net/esonpo/article/details/31401075)

14. 推送
    - [基于Qt移动应用的消息推送服务原理与应用](http://blog.csdn.net/esonpo/article/details/43796449)

TODO MORE...

以上对一些常见的功能点和需求进行了分类，如果你在开发当中遇到过更多的需求点，麻烦给我留言，我会添加到开源列表当中。如果你有时间也可以加入我们，把你认为可以帮助到大家的东西开源出来或者提出有效的解决方案，我会把你的成果整理出来跟大家分享。

---

其他项目：

[zkelong/QtForAndroid](https://github.com/zkelong/QtForAndroid)

[toby20130333/qt-websocket-protobuf](https://github.com/toby20130333/qt-websocket-protobuf)

> 基于nodejs后端框架与Qt前端框架使用protobuf

[antonypro/QtKeyboardRect](https://github.com/antonypro/QtKeyboardRect)

> Qt 获取安卓键盘高度示例

[Code snippets for UI programming blog http://www.joona.net](https://github.com/jpetrell/codesnippets-joona)

> 一些 QML 界面设计的代码片段

[rschiang/material](https://github.com/rschiang/material)

> QtQuick 的 material 样式控件，不过 Qt 5.7.0 的 Controls 2.0 已经有 material 样式了，并且还提供更贴切移动开发的控件~

[lvip/TwaddleMSG-desctop-](https://github.com/lvip/TwaddleMSG-desctop-)

> 看起来是个桌面软件

[Intents with Qt for Android, part 1](http://blog.qt.io/blog/2016/06/30/intents-with-qt-for-android-part-1/)

[eskilblomfeldt/recipeexample](https://github.com/eskilblomfeldt/recipeexample)

> 在 Qt for Android 上使用 Intents

[Qt on Android: How to restart your application](https://www.kdab.com/qt-on-android-how-to-restart-your-application/)

[LaurentGomila/qt-android-cmake](https://github.com/LaurentGomila/qt-android-cmake)

> A simple CMake utility for building and deploying Qt based applications on Android without QtCreator
