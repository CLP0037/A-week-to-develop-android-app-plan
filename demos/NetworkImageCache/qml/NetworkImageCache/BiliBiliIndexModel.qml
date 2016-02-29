import QtQuick 2.0

ListModel {
    id: listModel

    function getBiliBiliIndex() {
        var url = "http://api.bilibili.cn/index";
        var xhr = new XMLHttpRequest;
        xhr.onreadystatechange = function() {
            if(xhr.readyState == xhr.DONE) {
                var jsonObject = JSON.parse(xhr.responseText);
                listModel.fill(jsonObject)
            }
        }
        xhr.open("GET", url)
        xhr.send()
    }
    // jsonObject['type1'][0]['title']
    function fill(jsonObject) {


        for(var areaIter in jsonObject) {

            var NumberList = "012345678".split("");

            for(var n in NumberList) {
                var Iter = NumberList[n];   // '0' '1' ... '8'

                var videoItemInfo = jsonObject[areaIter][Iter]

                var i = {
                    "Area": areaIter,                              // 分区
                    "NumberId": Iter,                              // 排名
                    "AVid": videoItemInfo.aid,                     // AV 号
                    "CopyRight": videoItemInfo.copyright,          // Original=原创，copy=转载
                    "TypeId": videoItemInfo.typeid,                // 更细致分区
                    "TypeName": videoItemInfo.typename,            // 类型名
                    "Play": videoItemInfo.play,                    // 播放数
                    "Title": videoItemInfo.title,                  // 标题
                    "Subtitle": videoItemInfo.subtitle,            // 副标题，很多视频没有
                    "Review": videoItemInfo.review,                // 评论，少于浏览器看到的，包含回复
                    "Video_Review": videoItemInfo.video_review,    // 弹幕数【估计包含被清过的】
                    "Favorites": videoItemInfo.favorites,          // 收藏
                    "Mid": videoItemInfo.mid,                      // 发布者账号
                    "Author": videoItemInfo.author,                // 发布者
                    "Description": videoItemInfo.description,      // 描述
                    "Create": videoItemInfo.create,                // 发布时间
                    "Pic": videoItemInfo.pic,                      // 封面
                    "Credit": videoItemInfo.credit,                // 积分
                    "Coins": videoItemInfo.coins,                  // 硬币
                    "Duration": videoItemInfo.duration,            // 时长
                };

                listModel.append(i);

            }
        }
    }
}

