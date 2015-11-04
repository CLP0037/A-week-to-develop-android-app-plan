import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.LocalStorage 2.0

ApplicationWindow {
    title: qsTr("Local Storage")
    width: 640
    height: 480
    visible: true

    Row {
        Button {
            id: button
            text: "sql operation"
            onClicked: {
                foo();
            }
        }
    }
    function foo() {
        //! 打开一个数据库
        var db = LocalStorage.openDatabaseSync("QQmlExampleDB", "1.0", "The Example QML SQL!", 1000000);

        db.transaction(
                    function(tx) {
                        // 如果不存在表就创建
                        tx.executeSql('CREATE TABLE IF NOT EXISTS Greeting(salutation TEXT, salutee TEXT)');

                        // 插入记录
                        tx.executeSql('INSERT INTO Greeting VALUES(?, ?)', [ 'hello', 'world' ]);

                        // Show all added greetings
                        //! rs is SQLResultSet type
                        var rs = tx.executeSql('SELECT * FROM Greeting');

                        var r = ""
                        for(var i = 0; i < rs.rows.length; i++) {
                            //! rs.rows is SQLResultSetRowList type
                            r += rs.rows.item(i).salutation + ", " + rs.rows.item(i).salutee + "\n"
                        }
                        console.log(r);
                    });
    }
}
