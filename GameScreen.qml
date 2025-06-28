
// import QtQuick
// import QtQuick.Controls
// import QtQuick.Layouts
// import Sanguosha.Resources

// Item {
//     id: gameArea
//     width: 1280
//     height: 720
//     signal backToMenu()

//     property ListModel handCardsModel: ListModel {}
//     property var topDiscardCard: ({})
//     property int selectedCardIndex: -1
//     property int selectedPlayerIndex: -1

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

//         // 牌堆
//         Image {
//             id: deckBack
//             source: "qrc:/paibei.webp"
//             width: 120; height: 180
//             anchors.centerIn: parent

//             Text {
//                 anchors.centerIn: parent
//                 text: gameManager ? gameManager.deckCount : "0"
//                 color: "white"
//                 font { bold: true; pixelSize: 24 }
//                 style: Text.Outline; styleColor: "black"
//             }

//             MouseArea {
//                 anchors.fill: parent
//                 onClicked: {
//                     if (gameManager) {
//                         gameManager.drawCard();
//                     }
//                 }
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
//                 model: handCardsModel

//                 delegate: CardItem {
//                     cardName: model.name
//                     cardSuit: model.suit
//                     point: model.point
//                     cardIndex: index
//                     isNewCard: model.isNew
//                     isSelected: index === gameArea.selectedCardIndex

//                     onPlayCard: {
//                         if (gameManager) {
//                             gameManager.playCard(index);
//                         }
//                         gameArea.selectedCardIndex = -1;
//                     }

//                     onDiscardCard: {
//                         if (gameManager) {
//                             gameManager.discardCard(index);
//                         }
//                         gameArea.selectedCardIndex = -1;
//                     }

//                     onCancelTargetSelection: {
//                         if (gameManager) {
//                             gameManager.cancelTargetSelection();
//                         }
//                     }

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
//                 id: playerDelegate
//                 width: (playersArea.width - playersArea.spacing * 3) / 4
//                 height: playersArea.height
//                 playerName: "Player " + (index + 1)
//                 health: 4
//                 playerIndex: index
//                 isSelectable: gameManager && gameManager.isSelectingTarget

//                 onSelected: function(playerIdx) {
//                     console.log("玩家区域点击:", playerIdx)
//                     gameManager.selectTargetPlayer(playerIdx);
//                     resetTargetSelection();
//                 }

//                 // 判定区
//                 Row {
//                     anchors {
//                         top: parent.top
//                         horizontalCenter: parent.horizontalCenter
//                         topMargin: -30
//                     }
//                     spacing: 5
//                     visible: gameManager && gameManager.hasJudgeCards(playerIndex)

//                     Repeater {
//                         model: gameManager ? gameManager.getJudgeCards(playerIndex) : []

//                         delegate: Image {
//                             width: 40; height: 60
//                             source: CardResources.cardFrontImages[modelData.name] ||
//                                     CardResources.cardFrontImages.default
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     // 5. 功能按钮
//     Row {
//         anchors {
//             bottom: parent.bottom
//             horizontalCenter: parent.horizontalCenter
//             bottomMargin: 20
//         }
//         spacing: 20

//         Button {
//             text: "洗牌"
//             onClicked: {
//                 if (gameManager) {
//                     gameManager.shuffleDeck();
//                 }
//             }
//         }

//         Button {
//             text: "结束回合"
//             onClicked: {
//                 if (gameManager) {
//                     gameManager.endTurn();
//                 }
//             }
//         }

//         Button {
//             text: "退出"
//             onClicked: Qt.quit()
//         }
//     }

//     // 6. 选择卡牌函数
//     function selectCard(index) {
//         if (selectedCardIndex === index) {
//             selectedCardIndex = -1;
//             resetTargetSelection();
//             return;
//         }
//         selectedCardIndex = index;
//     }

//     // 7. 响应游戏管理器信号
//     Connections {
//         target: gameManager

//         function onCardAdded(cardData) {
//             handCardsModel.append({
//                 name: cardData.name,
//                 suit: cardData.suit,
//                 point: cardData.point,
//                 type: cardData.type,
//                 isNew: true
//             });
//         }

//         function onCardRemoved(index) {
//             if (index >= 0 && index < handCardsModel.count) {
//                 handCardsModel.remove(index);

//                 if (gameArea.selectedCardIndex === index) {
//                     gameArea.selectedCardIndex = -1;
//                     resetTargetSelection();
//                 }
//                 else if (gameArea.selectedCardIndex > index) {
//                     gameArea.selectedCardIndex--;
//                 }
//             }
//         }

//         function onCardPlayed(cardData) {
//             console.log("卡牌被使用:", cardData.name);

//             if (cardData.type === "Ji_Ben" ||
//                 cardData.name === "Wu_Zhongshengyou" ||
//                 cardData.name === "Nan_Manruqin") {
//                 gameManager.moveCardToDiscard(cardData);
//             }
//             else if (cardData.name === "Shan_Dian" ||
//                      cardData.name === "Le_Busishu") {
//                 gameManager.moveCardToJudgeArea(1, cardData);
//             }
//         }

//         function onCardDiscarded(cardData) {
//             console.log("卡牌被弃置:", cardData.name);
//             if (gameManager) {
//                 gameArea.topDiscardCard = gameManager.getTopDiscardCard();
//             }
//         }

//         function onCardMovedToDiscard(cardData) {
//             console.log("卡牌进入弃牌堆:", cardData.name);
//             if (gameManager) {
//                 gameArea.topDiscardCard = gameManager.getTopDiscardCard();
//             }
//         }

//         function onDiscardPileChanged(count) {
//             if (gameManager) {
//                 gameArea.topDiscardCard = gameManager.getTopDiscardCard();
//             }
//         }

//         function onTurnEnded(playerIndex) {
//             console.log("玩家", playerIndex, "回合结束");
//             if (gameManager) {
//                 gameManager.resolveJudgeCards(playerIndex);
//             }
//         }

//         function onTargetSelectionStarted(cardIndex) {
//             console.log("目标选择开始，卡牌索引:", cardIndex);
//             for (var i = 0; i < playersArea.children.length; i++) {
//                 var playerArea = playersArea.children[i];
//                 if (playerArea && playerArea.playerIndex !== undefined) {
//                     playerArea.isSelectable = true;
//                 }
//             }
//             cancelButton.visible = true;
//         }

//         function onTargetSelectionCanceled() {
//             resetTargetSelection();
//         }

//         function onCardPlayedWithTarget(cardIndex, playerIndex) {
//             resetTargetSelection();
//         }

//         // 新增：响应手牌重置信号
//         function onHandCardsReset() {
//             console.log("手牌重置");
//             handCardsModel.clear();
//             var handCards = gameManager.getHandCards();
//             for (var i = 0; i < handCards.length; i++) {
//                 var cardData = handCards[i];
//                 handCardsModel.append({
//                     name: cardData.name,
//                     suit: cardData.suit,
//                     point: cardData.point,
//                     type: cardData.type,
//                     isNew: false
//                 });
//             }
//         }
//     }

//     // 取消按钮
//     Button {
//         id: cancelButton
//         anchors {
//             top: parent.top
//             right: parent.right
//             margins: 20
//         }
//         text: "取消选择"
//         visible: false

//         background: Rectangle {
//             color: "#FF5722"
//             radius: 5
//             border.width: 1
//             border.color: "white"
//         }

//         contentItem: Text {
//             text: parent.text
//             color: "white"
//             horizontalAlignment: Text.AlignHCenter
//             verticalAlignment: Text.AlignVCenter
//             font.bold: true
//         }

//         onClicked: {
//             gameManager.cancelTargetSelection();
//             resetTargetSelection();
//         }
//     }

//     // 8. 初始化游戏
//     Component.onCompleted: {
//         if (gameManager) {
//             var handCards = gameManager.getHandCards();
//             for (var i = 0; i < handCards.length; i++) {
//                 var cardData = handCards[i];
//                 handCardsModel.append({
//                     name: cardData.name,
//                     suit: cardData.suit,
//                     point: cardData.point,
//                     type: cardData.type,
//                     isNew: false
//                 });
//             }

//             topDiscardCard = gameManager.getTopDiscardCard();
//         }
//     }

//     // 处理玩家选择
//     function handlePlayerSelected(index) {
//         console.log("玩家选择:", index);
//         gameManager.selectTargetPlayer(index);
//         resetTargetSelection();
//     }

//     // 重置目标选择状态
//     function resetTargetSelection() {
//         console.log("重置目标选择状态");
//         for (var i = 0; i < playersArea.children.length; i++) {
//             var playerArea = playersArea.children[i];
//             if (playerArea && playerArea.playerIndex !== undefined) {
//                 playerArea.isSelectable = false;
//                 playerArea.isSelected = false;
//             }
//         }

//         cancelButton.visible = false;
//         selectedPlayerIndex = -1;
//     }
// }
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
    property var topDiscardCard: ({})
    property int selectedCardIndex: -1
    property int selectedPlayerIndex: -1

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

                    onCancelTargetSelection: {
                        if (gameManager) {
                            gameManager.cancelTargetSelection();
                        }
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
                id: playerDelegate
                width: (playersArea.width - playersArea.spacing * 3) / 4
                height: playersArea.height
                playerName: "Player " + (index + 1)
                health: 4
                playerIndex: index
                isSelectable: gameManager && gameManager.isSelectingTarget

                onSelected: function(playerIdx) {
                    console.log("玩家区域点击:", playerIdx)
                    gameManager.selectTargetPlayer(playerIdx);
                    resetTargetSelection();
                }

                // 判定区
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
            resetTargetSelection();
            return;
        }
        selectedCardIndex = index;
    }

    // 7. 响应游戏管理器信号
    Connections {
        target: gameManager

        function onCardAdded(cardData) {
            // 使用深拷贝创建新对象
            var newCard = JSON.parse(JSON.stringify(cardData));
            handCardsModel.append({
                name: newCard.name,
                suit: newCard.suit,
                point: newCard.point,
                type: newCard.type,
                isNew: true
            });
        }

        function onCardRemoved(index) {
            if (index >= 0 && index < handCardsModel.count) {
                handCardsModel.remove(index);

                if (gameArea.selectedCardIndex === index) {
                    gameArea.selectedCardIndex = -1;
                    resetTargetSelection();
                }
                else if (gameArea.selectedCardIndex > index) {
                    gameArea.selectedCardIndex--;
                }
            }
        }

        function onCardPlayed(cardData) {
            console.log("卡牌被使用:", cardData.name);
        }

        function onCardDiscarded(cardData) {
            console.log("卡牌被弃置:", cardData.name);
            if (gameManager) {
                gameArea.topDiscardCard = gameManager.getTopDiscardCard();
            }
        }

        function onCardMovedToDiscard(cardData) {
            console.log("卡牌进入弃牌堆:", cardData.name);
            if (gameManager) {
                gameArea.topDiscardCard = gameManager.getTopDiscardCard();
            }
        }

        function onDiscardPileChanged(count) {
            if (gameManager) {
                gameArea.topDiscardCard = gameManager.getTopDiscardCard();
            }
        }

        function onTurnEnded(playerIndex) {
            console.log("玩家", playerIndex, "回合结束");
            if (gameManager) {
                gameManager.resolveJudgeCards(playerIndex);
            }
        }

        function onTargetSelectionStarted(cardIndex) {
            console.log("目标选择开始，卡牌索引:", cardIndex);
            for (var i = 0; i < playersArea.children.length; i++) {
                var playerArea = playersArea.children[i];
                if (playerArea && playerArea.playerIndex !== undefined) {
                    playerArea.isSelectable = true;
                }
            }
            cancelButton.visible = true;
        }

        function onTargetSelectionCanceled() {
            resetTargetSelection();
        }

        function onCardPlayedWithTarget(cardIndex, playerIndex) {
            resetTargetSelection();
        }

        // 新增：响应手牌重置信号
        function onHandCardsReset() {
            console.log("手牌重置");
            handCardsModel.clear();
            var handCards = gameManager.getHandCards();
            for (var i = 0; i < handCards.length; i++) {
                // 深拷贝卡牌数据
                var cardData = JSON.parse(JSON.stringify(handCards[i]));
                handCardsModel.append({
                    name: cardData.name,
                    suit: cardData.suit,
                    point: cardData.point,
                    type: cardData.type,
                    isNew: false
                });
            }
        }
    }

    // 取消按钮
    Button {
        id: cancelButton
        anchors {
            top: parent.top
            right: parent.right
            margins: 20
        }
        text: "取消选择"
        visible: false

        background: Rectangle {
            color: "#FF5722"
            radius: 5
            border.width: 1
            border.color: "white"
        }

        contentItem: Text {
            text: parent.text
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
        }

        onClicked: {
            gameManager.cancelTargetSelection();
            resetTargetSelection();
        }
    }

    // 8. 初始化游戏
    Component.onCompleted: {
        if (gameManager) {
            var handCards = gameManager.getHandCards();
            for (var i = 0; i < handCards.length; i++) {
                // 深拷贝卡牌数据
                var cardData = JSON.parse(JSON.stringify(handCards[i]));
                handCardsModel.append({
                    name: cardData.name,
                    suit: cardData.suit,
                    point: cardData.point,
                    type: cardData.type,
                    isNew: false
                });
            }

            topDiscardCard = gameManager.getTopDiscardCard();
        }
    }

    // 处理玩家选择
    function handlePlayerSelected(index) {
        console.log("玩家选择:", index);
        gameManager.selectTargetPlayer(index);
        resetTargetSelection();
    }

    // 重置目标选择状态
    function resetTargetSelection() {
        console.log("重置目标选择状态");
        for (var i = 0; i < playersArea.children.length; i++) {
            var playerArea = playersArea.children[i];
            if (playerArea && playerArea.playerIndex !== undefined) {
                playerArea.isSelectable = false;
                playerArea.isSelected = false;
            }
        }

        cancelButton.visible = false;
        selectedPlayerIndex = -1;
    }
}
