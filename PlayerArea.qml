import QtQuick
import QtQuick.Controls

Item {
    id: playerArea
    property string playerName: "Player"
    property int health: 4
    property int maxHealth: 4
    property int playerIndex: 0
    property bool isSelectable: false
    property bool isSelected: false
    property bool isAlive: true
    property int handCount: 0

    signal selected(int playerIndex)

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
        },
        State {
            name: "dead"
            when: !isAlive
            PropertyChanges {
                target: playerBackground
                color: "#AA333333"
            }
            PropertyChanges {
                target: playerNameText
                color: "gray"
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

    Rectangle {
        id: playerBackground
        anchors.fill: parent
        color: "transparent"
        border { width: 2; color: isAlive ? "#4CAF50" : "#666666" }
        radius: 10
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

    Column {
        anchors.centerIn: parent
        spacing: 10

        Image {
            source: "qrc:/xcm2.jpg"
            width: 80; height: 80
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: isAlive ? 1.0 : 0.5
        }

        Text {
            id: playerNameText
            text: playerName
            color: isAlive ? "white" : "gray"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Outline; styleColor: "black"
        }

        // 血量显示区域
        Row {
            spacing: 5
            anchors.horizontalCenter: parent.horizontalCenter

            Repeater {
                model: maxHealth
                delegate: Image {
                    source: index < health ? "qrc:/hongtao.webp" : "qrc:/hongtao.webp"
                    width: 20; height: 20
                    opacity: {
                        if (!isAlive) return 0.5;
                        return index < health ? 1.0 : 0.3; // 通过透明度区分满血和失血
                    }

                    // 添加血量变化动画
                    SequentialAnimation on scale {
                        id: healthChangeAnim
                        running: false
                        PropertyAnimation { to: 1.3; duration: 200 }
                        PropertyAnimation { to: 1.0; duration: 200 }
                    }

                    // 当血量变化时触发动画
                    Connections {
                        target: playerArea
                        function onHealthChanged() {
                            healthChangeAnim.restart();
                        }
                    }
                }
            }
        }

        // 血量数值显示
        Text {
            text: health + "/" + maxHealth
            color: {
                if (!isAlive) return "gray";
                if (health <= 1) return "red";
                if (health <= maxHealth/2) return "orange";
                return "white";
            }
            font.bold: true
            font.pixelSize: 14
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Outline; styleColor: "black"
        }

        // 手牌数显示
        Text {
            text: "手牌: " + handCount
            color: isAlive ? "lightblue" : "gray"
            font.pixelSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Outline; styleColor: "black"
        }

        // 装备显示（如果需要的话）
        Row {
            spacing: 5
            anchors.horizontalCenter: parent.horizontalCenter
            visible: isAlive

            Image {
                source: "qrc:/zhuangbei/zhugeliannu"
                width: 40; height: 40
                visible: false // 目前隐藏，可以根据需要显示
            }

            Image {
                source: "qrc:/images/armor.png"
                width: 40; height: 40
                visible: false // 目前隐藏，可以根据需要显示
            }
        }
    }

    // 伤害飞字效果
    Item {
        id: damageIndicator
        anchors.centerIn: parent
        width: parent.width
        height: parent.height

        Text {
            id: damageText
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 24
            color: "red"
            style: Text.Outline
            styleColor: "black"
            opacity: 0

            SequentialAnimation on y {
                id: damageAnimation
                running: false
                PropertyAnimation {
                    from: parent.height * 0.5
                    to: parent.height * 0.2
                    duration: 1000
                }
            }

            SequentialAnimation on opacity {
                id: damageOpacityAnimation
                running: false
                PropertyAnimation { to: 1.0; duration: 200 }
                PropertyAnimation { to: 1.0; duration: 600 }
                PropertyAnimation { to: 0.0; duration: 200 }
            }
        }
    }

    // 治疗飞字效果
    Item {
        id: healIndicator
        anchors.centerIn: parent
        width: parent.width
        height: parent.height

        Text {
            id: healText
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 20
            color: "green"
            style: Text.Outline
            styleColor: "black"
            opacity: 0

            SequentialAnimation on y {
                id: healAnimation
                running: false
                PropertyAnimation {
                    from: parent.height * 0.5
                    to: parent.height * 0.2
                    duration: 1000
                }
            }

            SequentialAnimation on opacity {
                id: healOpacityAnimation
                running: false
                PropertyAnimation { to: 1.0; duration: 200 }
                PropertyAnimation { to: 1.0; duration: 600 }
                PropertyAnimation { to: 0.0; duration: 200 }
            }
        }
    }

    // 显示伤害飞字的函数
    function showDamage(damage) {
        damageText.text = "-" + damage;
        damageText.y = height * 0.5;
        damageAnimation.restart();
        damageOpacityAnimation.restart();
    }

    // 显示治疗飞字的函数
    function showHeal(healAmount) {
        healText.text = "+" + healAmount;
        healText.y = height * 0.5;
        healAnimation.restart();
        healOpacityAnimation.restart();
    }

    // 更新玩家信息的函数
    function updatePlayerInfo(playerInfo) {
        playerName = playerInfo.name;
        health = playerInfo.health;
        maxHealth = playerInfo.maxHealth;
        isAlive = playerInfo.isAlive;
        handCount = playerInfo.handCount;
    }
}
