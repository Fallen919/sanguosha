// CardItem.qml
import QtQuick
import QtQuick.Controls
import Sanguosha.Resources


Item {
    id: root
    width: 120; height: 180
    property string cardName
    property string cardSuit
    property bool isNewCard: false  // 标记新卡牌

    signal playCard()

    // 卡牌状态管理
    states: [
        State {
            name: "drawing"
            PropertyChanges { target: root; scale: 0.8; opacity: 0 }
            AnchorChanges { target: root; anchors.horizontalCenter: undefined }
        },
        State {
            name: "inHand"
            PropertyChanges { target: root; scale: 1; opacity: 1 }
            AnchorChanges { target: root; anchors.horizontalCenter: undefined }
        },
        State {
            name: "hovered"
            PropertyChanges { target: root; y: -30 }
        }
    ]
//摸牌动画
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
        }
    ]

    Image {
        id: cardImage
        anchors.fill: parent
        source: CardResources.cardFrontImages[cardName] || CardResources.cardFrontImages.default
         // source: "qrc:/sha.webp"
        Image {
               id: cardsuit
               width: 20; height: 20
               anchors { top: parent.top; right: parent.right; margins: 5 }
               source: CardResources.suitColors[cardSuit] || CardResources.suitColors.default

}
        Rectangle{
            id:points
            width: 0;height: 0
            anchors.top:parent.top
            anchors.left:parent.left;
            anchors.margins: 5
            Text {
                id: p
                text: gameArea.handCardsModel.get(index).point
            }
        }

        // 花色标记
        // Rectangle {
        //     width: 20; height: 20
        //     radius: 10
        //     color: CardResources.suitColors[cardSuit] || "gray"
        //     anchors { top: parent.top; right: parent.right; margins: 5 }
        //     border { width: 1; color: "white" }
        // }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: playCard()
        onEntered: root.state = "hovered"
        onExited: root.state = "inHand"
    }

    Component.onCompleted: {
        if (isNewCard) {
            root.state = "drawing";
            root.state = "inHand";
        }
    }
}
