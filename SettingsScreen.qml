import QtQuick
import QtQuick.Controls

Item {
    signal backToMenu()  // 必须声明信号

    Column {
        anchors.centerIn: parent

        Text {
            text: "设置"
            font.pixelSize: 24
        }

        Slider {
            id: volumeSlider
            Label { text: "音量"; horizontalAlignment: Text.AlignHCenter }
            from: 0
            to: 100
            value: 50
        }

        Button {
            text: "返回"
            onClicked: backToMenu()  // 触发信号
        }
    }
}
