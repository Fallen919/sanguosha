
// import QtQuick
// import QtQuick.Controls

// Item {
//     id: playerArea
//     property string playerName
//     property int health
//     property int playerIndex
//     property bool isSelectable: false
//     property bool isSelected: false
//     property string wujiangName: "" // 存储武将名称

//     // 明确定义信号处理器
//     signal selected(int playerIndex)
//     signal zhihengRequested()
//     signal kurouRequested() // 新增苦肉信号

//     onIsSelectableChanged: {
//         if (isSelectable) {
//             state = "selectable";
//         } else {
//             state = "";
//             isSelected = false;
//         }
//     }

//     onIsSelectedChanged: {
//         if (isSelected) {
//             state = "selected";
//         } else if (isSelectable) {
//             state = "selectable";
//         } else {
//             state = "";
//         }
//     }

//     states: [
//         State {
//             name: "selectable"
//             PropertyChanges {
//                 target: highlight
//                 visible: true
//                 color: "yellow"
//                 opacity: 0.5
//             }
//         },
//         State {
//             name: "selected"
//             PropertyChanges {
//                 target: highlight
//                 visible: true
//                 color: "gold"
//                 opacity: 0.8
//             }
//         }
//     ]

//     Rectangle {
//         id: highlight
//         anchors.fill: parent
//         radius: 10
//         visible: false
//         color: "transparent"
//     }

//     MouseArea {
//         anchors.fill: parent
//         onClicked: {
//             if (playerArea.isSelectable) {
//                 playerArea.isSelected = true;
//                 playerArea.selected(playerIndex);
//             }
//         }
//     }

//     // 技能按钮 - 制衡（仅孙权可见）
//     Button {
//         id: skillButton
//         anchors {
//             top: parent.top
//             right: parent.right
//             margins: 5
//         }
//         width: 40
//         height: 30
//         text: "制衡"
//         visible: playerIndex === 0 && wujiangName === "大魏吴王" // 只对玩家1且武将是孙权时显示

//         background: Rectangle {
//             color: "#FF9800"
//             radius: 5
//         }

//         onClicked: {
//             // 发出制衡请求信号
//             playerArea.zhihengRequested();
//         }
//     }

//     // 技能按钮 - 苦肉（仅黄盖可见）
//     Button {
//         id: kurouButton
//         anchors {
//             top: parent.top
//             right: skillButton.left // 放在制衡按钮左边
//             margins: 5
//         }
//         width: 40
//         height: 30
//         text: "苦肉"
//         visible: playerIndex === 0 && wujiangName === "黄盖" // 只对玩家1且武将是黄盖时显示

//         background: Rectangle {
//             color: "#E91E63" // 粉色背景
//             radius: 5
//         }

//         onClicked: {
//             // 发出苦肉请求信号
//             playerArea.kurouRequested();
//         }
//     }

//     Column {
//         anchors.centerIn: parent
//         spacing: 10

//         Image {
//             source: "qrc:/xcm2.jpg"
//             width: 80; height: 80
//             anchors.horizontalCenter: parent.horizontalCenter
//         }

//         Text {
//             text: playerName
//             color: "white"
//             font.bold: true
//             anchors.horizontalCenter: parent.horizontalCenter
//             style: Text.Outline; styleColor: "black"
//         }

//         Row {
//             spacing: 5
//             anchors.horizontalCenter: parent.horizontalCenter

//             Repeater {
//                 model: health
//                 delegate: Image {
//                     source: "qrc:/hongtao.webp"
//                     width: 20; height: 20
//                 }
//             }
//         }

//         Row {
//             spacing: 5
//             anchors.horizontalCenter: parent.horizontalCenter

//             Image {
//                 source: "qrc:/zhuangbei/zhugeliannu"
//                 width: 40; height: 40
//             }

//             Image {
//                 source: "qrc:/images/armor.png"
//                 width: 40; height: 40
//             }
//         }
//     }

//     Rectangle {
//         anchors.fill: parent
//         color: "transparent"
//         border { width: 2; color: "#4CAF50" }
//         radius: 10
//     }
// }
import QtQuick
import QtQuick.Controls

Item {
    id: playerArea
    property string playerName
    property int health
    property int playerIndex
    property bool isSelectable: false
    property bool isSelected: false
    property string wujiangName: "" // 存储武将名称

    // 明确定义信号处理器
    signal selected(int playerIndex)
    signal zhihengRequested()
    signal kurouRequested() // 新增苦肉信号

    onIsSelectableChanged: {
        if (isSelectable) {
            state = "selectable";
        } else {
            state = "";
            isSelected = false;
        }
    }

    onIsSelectedChanged: {
        if (isSelected) {
            state = "selected";
        } else if (isSelectable) {
            state = "selectable";
        } else {
            state = "";
        }
    }

    states: [
        State {
            name: "selectable"
            PropertyChanges {
                target: highlight
                visible: true
                color: "yellow"
                opacity: 0.5
            }
        },
        State {
            name: "selected"
            PropertyChanges {
                target: highlight
                visible: true
                color: "gold"
                opacity: 0.8
            }
        }
    ]

    Rectangle {
        id: highlight
        anchors.fill: parent
        radius: 10
        visible: false
        color: "transparent"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (playerArea.isSelectable) {
                playerArea.isSelected = true;
                playerArea.selected(playerIndex);
            }
        }
    }

    // 技能按钮 - 制衡（仅孙权可见）
    Button {
        id: skillButton
        anchors {
            top: parent.top
            right: parent.right
            margins: 5
        }
        width: 40
        height: 30
        text: "制衡"
        visible: playerIndex === 0 && wujiangName === "大魏吴王" // 只对玩家1且武将是孙权时显示

        background: Rectangle {
            color: "#FF9800"
            radius: 5
        }

        onClicked: {
            // 发出制衡请求信号
            playerArea.zhihengRequested();
        }
    }

    // 技能按钮 - 苦肉（仅黄盖可见）
    Button {
        id: kurouButton
        anchors {
            top: parent.top
            right: skillButton.visible ? skillButton.left : parent.right // 动态调整位置
            margins: 5
        }
        width: 40
        height: 30
        text: "苦肉"
        visible: playerIndex === 0 && wujiangName === "黄盖" // 只对玩家1且武将是黄盖时显示

        background: Rectangle {
            color: "#E91E63" // 粉色背景
            radius: 5
        }

        onClicked: {
            // 发出苦肉请求信号
            playerArea.kurouRequested();
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        Image {
            source: "qrc:/xcm2.jpg"
            width: 80; height: 80
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: playerName + (wujiangName ? "\n(" + wujiangName + ")" : "")
            color: "white"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Outline; styleColor: "black"
            horizontalAlignment: Text.AlignHCenter
        }

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

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border { width: 2; color: "#4CAF50" }
        radius: 10
    }
}
