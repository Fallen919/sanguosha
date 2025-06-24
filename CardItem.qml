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
    property bool isSelected: false//是否选中卡牌
    property int cardIndex: -1

    // 定义信号
    signal playCard()
    signal discardCard()

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
            StateChangeScript {
                script: console.log("卡牌", cardIndex, "进入选中状态")
            }
        }
    ]

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
        }
    ]

    // 根据选中状态更新状态
    onIsSelectedChanged: {
        if (isSelected) {
            state = "selected"
            console.log("卡牌", cardIndex, "设置为选中状态")
        } else {
            state = "inHand"
            console.log("卡牌", cardIndex, "设置为正常状态")
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
                color: isSelected ? "gold" : "transparent"
            }
            radius: 5
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
        }

        Row {
            anchors.centerIn: parent
            spacing: 15

            Button {
                text: "出牌"
                width: 80
                height: 30
                onClicked: {
                    console.log("出牌按钮点击:", cardIndex)
                    root.playCard();
                    root.state = "inHand";
                }
                // 添加样式使按钮更显眼
                background: Rectangle {
                    color: "green"
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

            Button {
                text: "弃牌"
                width: 80
                height: 30
                onClicked: {
                    console.log("弃牌按钮点击:", cardIndex)
                    root.discardCard();
                    root.state = "inHand";
                }
                // 添加样式使按钮更显眼
                background: Rectangle {
                    color: "red"
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
        text: isSelected ? "已选中" : ""
        color: "yellow"
        font.bold: true
        font.pixelSize: 16
        style: Text.Outline
        styleColor: "black"
        visible: true // 始终可见，用于调试
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            console.log("卡牌点击:", cardIndex)
            gameArea.selectCard(cardIndex);
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
