# 启动页

**SplashScreen** 类似于 **Photoshop** 完全启动前，先展示的小窗口。

现在大部分 **APP** 都有 **Splash** 界面，下面列一下 **Splash** 页面的几个作用：

1. 展示 logo，提高公司形象

2. 初始化数据（拷贝数据到 SD）

3. 提高用户体验 

4. 连接服务器是否有新的版本等。

5. 不做任何操作，直接进入主界面

## 在Qt中为安卓应用设置 SplashScreen

实现的方式其实有三种：

1. 在安卓的 `AndroidManifest.xml` 文件中指定
2. 在 `Java` 代码中实现
3. 在 `C++` 代码中实现
4. 在 `QML` 中实现

其实最后两种，并不能算得上是真正的 **SplashScreen**。因为在进入这个 **SplashScreen** 之前，应用仍然会黑屏。

最后这两种应该作为程序的功能引导页会更好。

---

这里讲讲在第一种方法，打开 `AndroidManifest.xml`，在 `activity` 标签内添加如下代码：

```xml
<meta-data android:name="android.app.splash_screen_drawable" android:resource="@drawable/splash"/>
```

在 **Qt on Android** 项目中，打开 `android/res` 目录，对号入座，将 `splash.png` （其他图片格式也可以），放到 `drawable-*` 文件夹中。

注意对应，在 `AndroidManifest.xml` 对应的是 `@drawable/splash` 那么，在文件系统中对应的是 `android/res/drawable-*/splash.png`。

这种方式的优点是简单，但是却不能动态更新 **SplashScreen**。

---

> [android程序启动画面之Splash总结](http://www.oschina.net/question/54100_34020)

> [Android Splash界面支持用户点击 直接进入主界面](http://blog.csdn.net/lmj623565791/article/details/23613403)

> [生成一个 Qt on Android 项目]()
