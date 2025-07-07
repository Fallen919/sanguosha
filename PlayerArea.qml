
import QtQuick
import QtQuick.Controls

Item {
    id: playerArea
    property string playerName
    property int health
    property int playerIndex
    property bool isSelectable: false
    property bool isSelected: false
    property var gameManager: null // 确保声明gameManager属性

    // 明确定义信号处理器
    signal selected(int playerIndex)
    signal zhihengRequested()

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

    // 技能按钮容器
    Column {
        id: skillButtons
        anchors {
            top: parent.top
            right: parent.right
            margins: 5
        }
        spacing: 5

        // 制衡按钮
        Button {
            id: skillButton
            width: 40
            height: 30
            text: "制衡"
            visible: playerIndex === 0 // 只对玩家1显示

            background: Rectangle {
                color: "#FF9800"
                radius: 5
            }

            onClicked: {
                // 发出制衡请求信号
                playerArea.zhihengRequested();
            }
        }

        // 苦肉按钮
        Button {
            id: kurouButton
            width: 40
            height: 30
            text: "苦肉"
            visible: playerIndex === 0 // 只对玩家1显示

            background: Rectangle {
                color: "#FF5722" // 橙色
                radius: 5
            }

            onClicked: {
                console.log("苦肉按钮点击");

                if (playerArea.gameManager) {
                    console.log("gameManager有效");

                    // 获取当前玩家
                    var currentPlayer = playerArea.gameManager.getdangqianplayer();

                    if (currentPlayer) {
                        console.log("当前玩家:", currentPlayer.getmynum());

                        // 获取武将名称
                        var wujiangName = currentPlayer.getwujiangming();
                        console.log("武将名称:", wujiangName);

                        // 检查是否是黄盖
                        if (wujiangName === "黄盖") {
                            console.log("发动黄盖的苦肉技能");

                            // 确保玩家有足够体力
                            if (currentPlayer.gettili() > 0) {
                                // 获取武将对象
                                var wujiang = currentPlayer.getwujiang();
                                // 发动技能
                                wujiang.jineng1(currentPlayer, playerArea.gameManager);
                                console.log("苦肉技能已触发");
                            } else {
                                console.log("体力不足，无法发动苦肉技能");
                            }
                        } else {
                            console.log("当前武将不是黄盖");
                        }
                    } else {
                        console.log("未找到当前玩家");
                    }
                } else {
                    console.log("gameManager无效");
                }
            }
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
            text: playerName
            color: "white"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Outline; styleColor: "black"
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
