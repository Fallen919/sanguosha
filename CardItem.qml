
import QtQuick
import QtQuick.Controls
import Sanguosha.Resources

Item {
    id: root
    width: 120; height: 180
    property string cardName
    property string cardSuit
    property int point: 0
    property bool isNewCard: false
    property bool isSelected: false
    property int cardIndex: -1
    property bool requiresTarget: false
    property bool isResponseCard: false
    // 新增: 制衡模式属性
    property bool isSelectableForZhiheng: false
    property bool isSelectedForZhiheng: false

    signal playCard()
    signal discardCard()
    signal cancelTargetSelection()

    states: [
        State {
            name: "drawing"
            PropertyChanges { target: root; scale: 0.8; opacity: 0 }
        },
        State {
            name: "inHand"
            PropertyChanges { target: root; scale: 1; opacity: 1 }
        },
        State {
            name: "hovered"
            PropertyChanges { target: root; y: -30 }
        },
        State {
            name: "selected"
            PropertyChanges { target: root; y: -40; z: 10 }
            PropertyChanges { target: actionButtons; visible: true }
        },
        State {
            name: "response"
            PropertyChanges { target: root; scale: 1.1; z: 20 }
            PropertyChanges { target: cardImage; opacity: 1.0 }
        }
    ]

    onPlayCard: {
        if (gameManager) {
            gameManager.playCard(cardIndex);
        }
    }

    onDiscardCard: {
        if (gameManager) {
            gameManager.discardCard(cardIndex);
        }
    }

    onCancelTargetSelection: {
        if (gameManager) {
            gameManager.cancelTargetSelection();
        }
    }

    transitions: [
        Transition {
            from: "drawing"; to: "inHand"
            ParallelAnimation {
                NumberAnimation { properties: "scale,opacity"; duration: 500; easing.type: Easing.OutBack }
                NumberAnimation { property: "y"; duration: 300; easing.type: Easing.OutQuad }
            }
        },
        Transition {
            from: "*"; to: "hovered"
            NumberAnimation { property: "y"; duration: 200 }
        },
        Transition {
            to: "selected"
            ParallelAnimation {
                NumberAnimation { property: "y"; duration: 200; to: -40 }
                NumberAnimation { property: "z"; duration: 200; to: 10 }
            }
        },
        Transition {
            to: "response"
            NumberAnimation { property: "scale"; duration: 200; to: 1.1 }
            NumberAnimation { property: "z"; duration: 200; to: 20 }
        },
        // 新增：从选中状态返回普通状态的过渡
        Transition {
            from: "selected"; to: "inHand"
            ParallelAnimation {
                NumberAnimation { property: "y"; duration: 200; to: 0 }
                NumberAnimation { property: "z"; duration: 200; to: 1 }
            }
            onRunningChanged: {
                if (!running) {
                    // 动画完成后重置状态
                    root.state = "inHand";
                }
            }
        }
    ]

    onIsSelectedChanged: {
        if (isSelected) {
            state = "selected"
            // 检查卡牌是否需要目标
            requiresTarget = gameManager ? gameManager.requiresTarget(cardIndex) : false;

            // 如果需要目标，自动触发目标选择
            if (requiresTarget && gameManager) {
                gameManager.startTargetSelection(cardIndex);
            }
        } else {
            state = "inHand"
        }
    }

    Image {
        id: cardImage
        anchors.fill: parent
        source: CardResources.cardFrontImages[cardName] || CardResources.cardFrontImages.default

        // 选中边框
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border {
                width: 3;
                color: isSelected ? "gold" : (isResponseCard ? "green" : "transparent")
            }
            radius: 5
        }

        // 制衡模式下的选中效果
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border {
                width: isSelectedForZhiheng ? 3 : 0;
                color: "cyan"
            }
            radius: 5
            visible: isSelectableForZhiheng
        }

        // 花色标记
        Image {
            id: cardsuit
            width: 20; height: 20
            anchors { top: parent.top; right: parent.right; margins: 5 }
            source: CardResources.suitColors[cardSuit] || CardResources.suitColors.default
        }

        // 点数标记
        Text {
            id: pointText
            anchors { top: parent.top; left: parent.left; margins: 5 }
            text: point
            font.pixelSize: 20
            color: "black"
        }
    }

    // 操作按钮区域
    Item {
        id: actionButtons
        anchors {
            top: cardImage.bottom
            horizontalCenter: cardImage.horizontalCenter
            topMargin: 20
        }
        width: parent.width
        height: 50
        visible: false
        z: 100

        // 添加背景使按钮更明显
        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.7
            radius: 5
            border.color: "white"
            border.width: 1
        }

        Row {
            anchors.centerIn: parent
            spacing: 15

            // 出牌按钮（始终显示）
            Button {
                id: playCardButton
                text: "出牌"
                width: 80
                height: 30
                onClicked: {
                    console.log("出牌按钮点击:", cardIndex)
                    root.playCard();
                    root.state = "inHand";
                }
                background: Rectangle {
                    color: "#2196F3" // 蓝色
                    radius: 5
                }
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
            }

            // 取消/弃牌按钮
            Button {
                text: requiresTarget ? "取消" : "弃牌"
                width: 80
                height: 30
                onClicked: {
                    if (requiresTarget) {
                        console.log("取消目标选择:", cardIndex)
                        root.cancelTargetSelection();
                    } else {
                        console.log("弃牌按钮点击:", cardIndex)
                        root.discardCard();
                    }
                    root.state = "inHand";
                }
                background: Rectangle {
                    color: requiresTarget ? "#FF9800" : "#F44336" // 橙色或红色
                    radius: 5
                }
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
            }
        }
    }

    // 在卡牌下方添加临时文本指示器
    Text {
        anchors {
            top: cardImage.bottom
            horizontalCenter: cardImage.horizontalCenter
            topMargin: 5
        }
        text: {
            if (isSelected) {
                return requiresTarget ? "请选择目标" : "已选中";
            } else if (isResponseCard) {
                return "可响应";
            } else if (isSelectableForZhiheng) {
                return isSelectedForZhiheng ? "已选为制衡" : "可选为制衡";
            }
            return ""
        }
        color: requiresTarget ? "#4CAF50" : (isResponseCard ? "green" : (isSelectableForZhiheng ? "cyan" : "yellow"))
        font.bold: true
        font.pixelSize: 16
        style: Text.Outline
        styleColor: "black"
        visible: true
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            if (gameArea.isZhihengMode) {
                // 制衡模式下的点击行为
                gameArea.toggleCardForZhiheng(cardIndex);
            } else if (isResponseCard) {
                // 在响应状态下，直接打出这张牌作为响应
                console.log("打出响应牌:", cardIndex);
                if (gameManager) {
                    gameManager.playResponseCard(cardIndex);
                }
            } else {
                console.log("卡牌点击:", cardIndex)
                gameArea.selectCard(cardIndex);
            }
        }
        onEntered: if (!isSelected) root.state = "hovered"
        onExited: if (!isSelected) root.state = "inHand"
    }

    Component.onCompleted: {
        if (isNewCard) {
            root.state = "drawing";
            root.state = "inHand";
        }
    }
}
