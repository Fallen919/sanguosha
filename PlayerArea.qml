// PlayerArea.qml
import QtQuick
import QtQuick.Controls

Item {
    id: playerArea
    property string playerName
    property int health

    Column {
        anchors.centerIn: parent
        spacing: 10

        // 玩家头像
        Image {
            source: "qrc:/xcm2.jpg"
            width: 80; height: 80
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // 玩家名字
        Text {
            text: playerName
            color: "white"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Outline; styleColor: "black"
        }

        // 血量显示
        Row {
            spacing: 5
            anchors.horizontalCenter: parent.horizontalCenter

            Repeater {
                model: health
                delegate: Image {
                    source: "qrc:/hongtao.webp"
                    width: 20; height: 20
                }
            }
        }

        // 装备区
        Row {
            spacing: 5
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                source: "qrc:/zhuangbei/zhugeliannu"
                width: 40; height: 40
            }

            Image {
                source: "qrc:/images/armor.png"
                width: 40; height: 40
            }
        }
    }

    // 边框
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border { width: 2; color: "#4CAF50" }
        radius: 10
    }
}
