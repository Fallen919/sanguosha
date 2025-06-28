
import QtQuick
import QtQuick.Controls

Item {
    id: playerArea
    property string playerName
    property int health
    property int playerIndex
    property bool isSelectable: false
    property bool isSelected: false

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
