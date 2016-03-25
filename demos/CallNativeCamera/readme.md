# CallNativeCamera 使用文档

## 方法

+ `capture()`

打开安卓系统相机，拍照，成功后，触发 `ready`，可以获取图片在本地的路径。错误会提示错误码和错误信息。

## 信号

+ `void ready(const QString& path)`

在安卓系统相机完成拍照触发。

+ `void error(int errorCode, const QString& errorString)`

在出错时触发。

## 使用方式

c++ main 函数

```
    engine.rootContext()->setContextProperty("CallNativeCamera", new CallNativeCamera(&engine));

```

qml ：

```
    Button {
        text:"开启相机"
        onClicked: {
            capture()
        }

        function capture() {
            try {
                CallNativeCamera.ready.connect(function(path){
                    CallNativeCamera.ready.disconnect(arguments.callee);
                    console.log(path);
                    image.source  = path;
                });
                CallNativeCamera.error.connect(function(error, errorString){
                    CallNativeCamera.error.disconnect(arguments.callee);
                    console.log("errorCode:", error);
                    console.log("errorString:", errorString);
                });
                CallNativeCamera.capture();
            } catch(e) {
                console.log(e)
            }
        }
    }
```
