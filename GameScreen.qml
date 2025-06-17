// GameScreen.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: gameArea
    width: 1280
    height: 720
    signal backToMenu()

    // 1. 背景
    AnimatedImage {
           anchors.fill: parent
           source: "/root/Sanguosha/beijing.gif"  // 确保路径正确
           playing: true  // 自动播放
           fillMode: Image.PreserveAspectCrop  // 填充方式
       }
    // 2. 牌堆区域
    Item {
        id: deckArea
        width: 150; height: 200
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin: 50
        }

        // 牌堆背面
        Image {
            id: deckBack
            source: "qrc:/paibei.webp"
            width: 120; height: 180
            anchors.centerIn: parent

            // 牌堆剩余数量
            Text {
                anchors.centerIn: parent
                text: "30" // 实际值应从C++获取
                color: "white"
                font { bold: true; pixelSize: 24 }
                style: Text.Outline; styleColor: "black"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: drawCard()
            }
        }

        // 弃牌堆
        Image {
            id: discardPile
            source: "qrc:/paibei.webp"
            width: 120; height: 180
            anchors {
                left: deckBack.right
                verticalCenter: deckBack.verticalCenter
                leftMargin: 20
            }
        }
    }

    // 3. 手牌区域
    Item {
        id: handArea
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            bottomMargin: 20
        }
        height: 200

        // 使用Flow布局自动调整卡牌位置
        Flow {
            id: handCardsFlow
            anchors.centerIn: parent
            spacing: -40 // 重叠效果
            width: parent.width - 100

            // 使用Repeater动态创建卡牌
            Repeater {
                id: handCardsRepeater
                model: ListModel { id: handCardsModel }

                delegate: CardItem {
                    cardName: model.name
                    cardSuit: model.suit
                    isNewCard: model.isNew
                    onPlayCard: handleCardPlay(index)

                    // 移除新卡牌标记
                    Component.onCompleted: {
                        if (isNewCard) {
                            handCardsModel.setProperty(index, "isNew", false);
                        }
                    }
                }
            }
        }
    }

    // 4. 玩家区域
    Row {
        id: playersArea
        anchors {
            top: deckArea.bottom
            left: parent.left
            right: parent.right
            bottom: handArea.top
            margins: 20
        }
        spacing: 20

        Repeater {
            model: 2// 4个玩家
            delegate: PlayerArea {
                width: (playersArea.width - playersArea.spacing * 3) / 4
                height: playersArea.height
                playerName: "Player " + (index + 1)
                health: 4
            }
        }
    }

    // 5. 功能按钮
    Button {
        text: "结束回合"
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: 20
        }
    }
    Button {
        text: "退出"
        onClicked: Qt.quit()
        anchors{
            left: parent.left
            bottom: parent.bottom
            margins:20
        }
    }
    // 6. 抽牌函数
    function drawCard() {
        // 实际应从C++获取卡牌数据
        const cardData = getRandomCardData();
        cardData.isNew = true; // 标记为新卡牌

        // 添加到模型
        handCardsModel.append(cardData);
    }

    // 7. 辅助函数
    function getRandomCardData() {
        const names = ["Sha", "Shan", "Tao", "Jiu"];
        const suits = ["Hei_Tao", "Hong_Tao", "Mei_Hua", "Fang_Kuai"];
        return {
            name: names[Math.floor(Math.random() * names.length)],
            suit: suits[Math.floor(Math.random() * suits.length)],
            point: Math.floor(Math.random() * 13) + 1,
            isNew: false
        };
    }

    function handleCardPlay(index) {
        console.log("出牌:", handCardsModel.get(index).name);
        handCardsModel.remove(index);
    }
}
