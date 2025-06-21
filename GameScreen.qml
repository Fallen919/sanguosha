
// import QtQuick
// import QtQuick.Controls
// import QtQuick.Layouts

// Item {
//     property alias handCardsModel: handCardsModel
//     id: gameArea
//     width: 1280
//     height: 720
//     signal backToMenu()

//     // 1. 背景
//     AnimatedImage {
//         anchors.fill: parent

//         source: "/root/Sanguosha/beijing.gif"


//         playing: true
//         fillMode: Image.PreserveAspectCrop
//     }

//     // 2. 牌堆区域
//     Item {
//         id: deckArea
//         width: 150; height: 200
//         anchors {
//             top: parent.top
//             horizontalCenter: parent.horizontalCenter
//             topMargin: 50
//         }

//         Image {
//             id: deckBack
//             source: "qrc:/paibei.webp"
//             width: 120; height: 180
//             anchors.centerIn: parent

//             Text {
//                 anchors.centerIn: parent
//                 text: cardDex.count
//                 color: "white"
//                 font { bold: true; pixelSize: 24 }
//                 style: Text.Outline; styleColor: "black"
//             }

//             MouseArea {
//                 anchors.fill: parent
//                 onClicked: {
//                     const cardData = cardDex.drawCard();
//                     cardDex.mopai();
//                     if (cardData) {
//                         handCardsModel.append({
//                             name: cardData.name,
//                             suit: cardData.suit,
//                             point: cardData.point,
//                             type: cardData.type,
//                             isNew: true
//                         });
//                     }
//                 }
//             }
//         }

//         Image {
//             id: discardPile
//             source: "qrc:/paibei.webp"
//             width: 120; height: 180
//             anchors {
//                 left: deckBack.right
//                 verticalCenter: deckBack.verticalCenter
//                 leftMargin: 20
//             }
//         }
//     }

//     // 3. 手牌区域
//     Item {
//         id: handArea
//         anchors {
//             bottom: parent.bottom
//             left: parent.left
//             right: parent.right
//             bottomMargin: 20
//         }
//         height: 200

//         Flow {
//             id: handCardsFlow
//             anchors.centerIn: parent
//             spacing: -40
//             width: parent.width - 100

//             Repeater {
//                 id: handCardsRepeater
//                 model: ListModel { id: handCardsModel }

//                 delegate: CardItem {
//                     cardName: model.name
//                     cardSuit: model.suit
//                     isNewCard: model.isNew
//                     onPlayCard: handleCardPlay(index)

//                     Component.onCompleted: {
//                         if (isNewCard) {
//                             handCardsModel.setProperty(index, "isNew", false);
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     // 4. 玩家区域
//     Row {
//         id: playersArea
//         anchors {
//             top: deckArea.bottom
//             left: parent.left
//             right: parent.right
//             bottom: handArea.top
//             margins: 20
//         }
//         spacing: 20

//         Repeater {
//             model: 2
//             delegate: PlayerArea {
//                 width: (playersArea.width - playersArea.spacing * 3) / 4
//                 height: playersArea.height
//                 playerName: "Player " + (index + 1)
//                 health: 4
//             }
//         }
//     }

//     // 5. 功能按钮
//     Button {
//         text: "洗牌"
//         anchors {
//             right: parent.right
//             bottom: parent.bottom
//             margins: 20
//         }
//         onClicked: cardDex.xipai()
//     }

//     Button {
//         text: "退出"
//         onClicked: Qt.quit()
//         anchors {
//             left: parent.left
//             bottom: parent.bottom
//             margins: 20
//         }
//     }

//     // 6. 卡牌处理函数
//     function handleCardPlay(index) {
//         var cardData = handCardsModel.get(index);
//         console.log("Playing card:", cardData.name);

//         // 调用C++逻辑处理出牌
//         if(cardDex.playCard(cardData)) {
//             handCardsModel.remove(index);
//         }
//     }


//     }
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Sanguosha.Resources

Item {
    id: gameArea
    width: 1280
    height: 720
    signal backToMenu()

    property ListModel handCardsModel: ListModel {}
    property var topDiscardCard: ({}) // 存储弃牌堆顶部卡牌
    property int selectedCardIndex: -1

    // 1. 背景
    AnimatedImage {
        anchors.fill: parent
        source: "/root/Sanguosha/beijing.gif"
        playing: true
        fillMode: Image.PreserveAspectCrop
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

        // 牌堆
        Image {
            id: deckBack
            source: "qrc:/paibei.webp"
            width: 120; height: 180
            anchors.centerIn: parent

            Text {
                anchors.centerIn: parent
                text: gameManager ? gameManager.deckCount : "0"
                color: "white"
                font { bold: true; pixelSize: 24 }
                style: Text.Outline; styleColor: "black"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (gameManager) {
                        gameManager.drawCard();
                    }
                }
            }
        }
//弃牌堆
        Image {
            id: discardPile
            source: "qrc:/paibei.webp"
            width: 120; height: 180
            anchors {
                left: deckBack.right
                verticalCenter: deckBack.verticalCenter
                leftMargin: 20
            }

            // 移除显示弃牌堆顶部卡牌的Image元素
            // 只保留显示弃牌堆数量的Text
            Text {
                anchors.centerIn: parent
                text: gameManager ? gameManager.discardPileCount : "0"
                color: "white"
                font { bold: true; pixelSize: 24 }
                style: Text.Outline; styleColor: "black"
                z: 1
            }

            // 鼠标悬停时显示完整弃牌堆
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    if (gameManager && gameManager.discardPileCount > 0) {
                        discardPilePopup.open();
                    }
                }
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

        Flow {
            id: handCardsFlow
            anchors.centerIn: parent
            spacing: -40
            width: parent.width - 100

            Repeater {
                id: handCardsRepeater
                model: handCardsModel

                delegate: CardItem {
                    cardName: model.name
                    cardSuit: model.suit
                    point: model.point
                    cardIndex: index
                    isNewCard: model.isNew
                    isSelected: index === gameArea.selectedCardIndex

                    onPlayCard: {
                        if (gameManager) {
                            gameManager.playCard(index);
                        }
                        gameArea.selectedCardIndex = -1;
                    }

                    onDiscardCard: {
                        if (gameManager) {
                            gameManager.discardCard(index);
                        }
                        gameArea.selectedCardIndex = -1;
                    }

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
            model: 2
            delegate: PlayerArea {
                width: (playersArea.width - playersArea.spacing * 3) / 4
                height: playersArea.height
                playerName: "Player " + (index + 1)
                health: 4
                playerIndex: index

                // 判定区（用于延时锦囊）
                Row {
                    anchors {
                        top: parent.top
                        horizontalCenter: parent.horizontalCenter
                        topMargin: -30
                    }
                    spacing: 5
                    visible: gameManager && gameManager.hasJudgeCards(playerIndex)

                    Repeater {
                        model: gameManager ? gameManager.getJudgeCards(playerIndex) : []

                        delegate: Image {
                            width: 40; height: 60
                            source: CardResources.cardFrontImages[modelData.name] ||
                                    CardResources.cardFrontImages.default
                        }
                    }
                }
            }
        }
    }

    // 5. 功能按钮
    Row {
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin: 20
        }
        spacing: 20

        Button {
            text: "洗牌"
            onClicked: {
                if (gameManager) {
                    gameManager.shuffleDeck();
                }
            }
        }

        Button {
            text: "结束回合"
            onClicked: {
                if (gameManager) {
                    gameManager.endTurn();
                }
            }
        }

        Button {
            text: "退出"
            onClicked: Qt.quit()
        }
    }

    // 6. 选择卡牌函数
    function selectCard(index) {
        if (selectedCardIndex === index) {
            selectedCardIndex = -1;
            return;
        }
        selectedCardIndex = index;
    }

    // 7. 响应游戏管理器信号
    Connections {
        target: gameManager

        // 添加新卡牌
        function onCardAdded(cardData) {
            handCardsModel.append({
                name: cardData.name,
                suit: cardData.suit,
                point: cardData.point,
                type: cardData.type,
                isNew: true
            });
        }

        // 移除卡牌
        function onCardRemoved(index) {
            if (index >= 0 && index < handCardsModel.count) {
                handCardsModel.remove(index);

                // 更新选中索引
                if (gameArea.selectedCardIndex === index) {
                    gameArea.selectedCardIndex = -1;
                }
                else if (gameArea.selectedCardIndex > index) {
                    gameArea.selectedCardIndex--;
                }
            }
        }

        // 卡牌被使用（可能尚未进入弃牌堆）
        function onCardPlayed(cardData) {
            console.log("卡牌被使用:", cardData.name);

            // 对于基本牌和立即生效的锦囊，立即进入弃牌堆
            if (cardData.type === "Ji_Ben" ||
                cardData.name === "Wu_Zhongshengyou" ||
                cardData.name === "Nan_Manruqin") {
                gameManager.moveCardToDiscard(cardData);
            }
            // 对于延时锦囊，进入判定区
            else if (cardData.name === "Shan_Dian" ||
                     cardData.name === "Le_Busishu") {
                // 这里需要目标选择逻辑（简化示例）
                gameManager.moveCardToJudgeArea(1, cardData); // 移动到玩家1的判定区
            }
        }

        // 卡牌被弃置（直接进入弃牌堆）
        function onCardDiscarded(cardData) {
               console.log("卡牌被弃置:", cardData.name);
               // 不再调用moveCardToDiscard()
               // 只需更新弃牌堆顶部卡牌（虽然不需要显示，但保持数据一致）
               if (gameManager) {
                   gameArea.topDiscardCard = gameManager.getTopDiscardCard();
               }
           }

           // 修改onCardMovedToDiscard信号处理器
           function onCardMovedToDiscard(cardData) {
               console.log("卡牌进入弃牌堆:", cardData.name);
               // 更新弃牌堆顶部卡牌
               if (gameManager) {
                   gameArea.topDiscardCard = gameManager.getTopDiscardCard();
               }
           }
        // 弃牌堆变化
        function onDiscardPileChanged(count) {
            // 更新弃牌堆数量
            if (gameManager) {
                gameArea.topDiscardCard = gameManager.getTopDiscardCard();
            }
        }

        // 回合结束
        function onTurnEnded(playerIndex) {
            console.log("玩家", playerIndex, "回合结束");

            // 处理判定区卡牌
            if (gameManager) {
                gameManager.resolveJudgeCards(playerIndex);
            }
        }
    }

    // 8. 初始化游戏
    Component.onCompleted: {
        if (gameManager) {
            // 初始化手牌
            var handCards = gameManager.getHandCards();
            for (var i = 0; i < handCards.length; i++) {
                var cardData = handCards[i];
                handCardsModel.append({
                    name: cardData.name,
                    suit: cardData.suit,
                    point: cardData.point,
                    type: cardData.type,
                    isNew: false
                });
            }

            // 初始化弃牌堆顶部卡牌
            topDiscardCard = gameManager.getTopDiscardCard();
        }
    }

    // 9. 弃牌堆弹窗
    Popup {
        id: discardPilePopup
        width: Math.min(800, parent.width - 40)
        height: 200
        anchors.centerIn: parent
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        background: Rectangle {
            color: "#AA000000"
            radius: 10
            border.color: "gold"
            border.width: 2
        }

        contentItem: Flow {
            id: discardPileFlow
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5

            Repeater {
                model: gameManager ? gameManager.getDiscardPile() : []

                delegate: Image {
                    width: 80; height: 120
                    source: CardResources.cardFrontImages[modelData.name] ||
                            CardResources.cardFrontImages.default
                }
            }
        }
    }
}
