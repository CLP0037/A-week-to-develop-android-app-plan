# Qt 打开安卓相册选择图片并获取图片的本地路径

步骤如下：

1. 通过 `Intent` 打开安卓的系统相册。

    推荐使用 `QAndroidJniObject::getStaticObjectField` 获取静态字段。

    ```
        QAndroidJniObject action = QAndroidJniObject::getStaticObjectField(
                    "android/content/Intent",
                    "ACTION_GET_CONTENT",
                    "Ljava/lang/String;");
    ```

2. 用户在系统相册选择到一个图片后，在 `C++` 代码中获取到图片的 `content` 地址。

3. 通过查询得出图片的本地路径。

    ```
    Uri uri = data.getData();
    String[] proj = { MediaStore.Images.Media.DATA };
    Cursor actualimagecursor = managedQuery(uri,proj,null,null,null);
    int actual_image_column_index = actualimagecursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
    actualimagecursor.moveToFirst();
    String img_path = actualimagecursor.getString(actual_image_column_index);
    File file = new File(img_path);
    ```

    将上诉的 Java 代码转成 C++ 代码。参考 [Qt and Android Gallery - MediaStore using QAndroidJniObject](http://stackoverflow.com/questions/34163437/qt-and-android-gallery-mediastore-using-qandroidjniobject)。

---

参考资料：

[Qt and Android Gallery - MediaStore using QAndroidJniObject](http://stackoverflow.com/questions/34163437/qt-and-android-gallery-mediastore-using-qandroidjniobject)

[HOW TO OPEN ANDROID IMAGE GALLERY IN QT](http://amin-ahmadi.com/2015/12/08/how-to-open-android-image-gallery-in-qt/)

[android实现Uri获取真实路径转换成File的方法](http://news.tuxi.com.cn/kf/article/jjneh.htm)

[Thread: Converting QAndroidJniObject to jobjectArray: most elements are NULL!](http://www.qtcentre.org/threads/59193-Converting-QAndroidJniObject-to-jobjectArray-most-elements-are-NULL!)

[How to return an array from JNI to Java?](http://stackoverflow.com/questions/1610045/how-to-return-an-array-from-jni-to-java)





---










