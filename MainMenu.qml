import QtQuick
import QtQuick.Controls

Item {
    signal startGame()     // 开始游戏信号
    signal showSettings()  // 打开设置界面信号

    AnimatedImage {
           anchors.fill: parent
           source: "/root/Sanguosha/beijing.gif"  // 确保路径正确
           playing: true  // 自动播放
           fillMode: Image.PreserveAspectCrop  // 填充方式
       }


    Column {
        anchors.centerIn: parent

        Button {
            text: "开始游戏"
            onClicked: startGame()  // 触发 startGame
        }

        Button {
            text: "设置"
            onClicked: showSettings()  // 触发 showSettings
        }

        Button {
            text: "退出"
            onClicked: Qt.quit()
        }
    }
}
