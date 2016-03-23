import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import Share 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt ShareSDK")


    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        TextField {
            id: title
            Layout.fillWidth: true
            placeholderText: "Input Title"
        }
        TextField {
            id: titleUrl
            Layout.fillWidth: true
            placeholderText: "Input TitleUrl"
        }
        TextField {
            id: text
            Layout.fillWidth: true
            placeholderText: "Input Text"
        }
        Button {
            text: qsTr("Share")
            onClicked: {
                /*
                const QString& title,
                const QString& titleUrl,
                const QString& text,
                const QString& imageUrl,
                const QString& url,
                const QString& comment,
                const QString& site,
                const QString& siteUrl,
                const QString& venueName,
                const QString& venueDescription
                */
                ShareSDK.showShare(title.text, titleUrl.text, text.text, "", "", "", "", "", "", "");
            }
        }
    }


}

