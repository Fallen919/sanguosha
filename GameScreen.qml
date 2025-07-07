
// import QtQuick
// import QtQuick.Controls
// import QtQuick.Layouts
// import Sanguosha.Resources

// Item {
//     id: gameArea
//     anchors.fill: parent
//     signal backToMenu()

//     property ListModel handCardsModel: ListModel {}
//     property var topDiscardCard: ({})
//     property int selectedCardIndex: -1
//     property int selectedPlayerIndex: -1
//     property bool isShanRequired: false
//     property bool isWuXiekejiRequired: false
//     property int responsePlayerIndex: -1

//     // 制衡模式相关属性
//     property bool isZhihengMode: false
//     property int zhihengCardCount: 0
//     property var selectedZhihengCards: []

//     // 装备项组件
//     Component {
//         id: equipmentItemComponent

//         Item {
//             id: equipmentItem
//             width: 70
//             height: 25
//             property string equipmentType: ""
//             property string source: ""

//             Row {
//                 spacing: 5
//                 anchors.centerIn: parent

//                 Image {
//                     width: 20
//                     height: 20
//                     source: equipmentItem.source
//                 }

//                 Text {
//                     text: equipmentItem.equipmentType
//                     color: "white"
//                     font.pixelSize: 12
//                     verticalAlignment: Text.AlignVCenter
//                 }
//             }
//         }
//     }

//     // 1. 背景
//     AnimatedImage {
//         anchors.fill: parent
//         source: "/root/Sanguosha/beijing.gif"
//         playing: true
//         fillMode: Image.PreserveAspectCrop
//     }

//     // 2. 牌堆区域 - 左上角
//     Item {
//         id: deckArea
//         width: parent.width * 0.1
//         height: parent.height * 0.15
//         anchors {
//             top: parent.top
//             left: parent.left
//             topMargin: parent.height * 0.03
//             leftMargin: parent.width * 0.03
//         }

//         // 牌堆
//         Image {
//             id: deckBack
//             width: parent.width * 0.8
//             height: parent.height * 0.9
//             anchors.centerIn: parent
//             source: "qrc:/paibei.webp"

//             Text {
//                 anchors.centerIn: parent
//                 text: gameManager ? gameManager.deckCount : "0"
//                 color: "white"
//                 font {
//                     bold: true;
//                     pixelSize: parent.height * 0.15
//                 }
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
//             bottomMargin: parent.height * 0.03
//         }
//         height: parent.height * 0.25

//         Flow {
//             id: handCardsFlow
//             anchors.centerIn: parent
//             spacing: -parent.width * 0.03
//             width: parent.width * 0.9

//             Repeater {
//                 id: handCardsRepeater
//                 model: handCardsModel

//                 delegate: CardItem {
//                     width: handArea.width * 0.08
//                     height: handArea.height * 0.8
//                     cardName: model.name
//                     cardSuit: model.suit
//                     point: model.point
//                     cardIndex: index
//                     isNewCard: model.isNew
//                     isSelected: index === gameArea.selectedCardIndex
//                     isResponseCard: model.isResponseCard
//                     // 制衡模式属性
//                     isSelectableForZhiheng: model.isSelectableForZhiheng
//                     isSelectedForZhiheng: model.isSelectedForZhiheng

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
//     Item {
//         id: playersContainer
//         anchors.fill: parent

//         // 玩家2 (顶部中央)
//         PlayerArea {
//             id: player2Area
//             width: parent.width * 0.2
//             height: parent.height * 0.2
//             anchors {
//                 top: parent.top
//                 horizontalCenter: parent.horizontalCenter
//                 topMargin: parent.height * 0.1
//             }
//             playerName: "Player 2"
//             health: 4
//             playerIndex: 1
//             isSelectable: gameManager && gameManager.isSelectingTarget

//             onSelected: function(playerIdx) {
//                 console.log("玩家区域点击:", playerIdx)
//                 gameManager.selectTargetPlayer(playerIdx);
//                 resetTargetSelection();
//             }
//         }

//         // 玩家1 (右下角)
//         PlayerArea {
//             id: player1Area
//             width: parent.width * 0.2
//             height: parent.height * 0.2
//             anchors {
//                 bottom: handArea.top
//                 right: parent.right
//                 bottomMargin: parent.height * 0.03
//                 rightMargin: parent.width * 0.03
//             }
//             playerName: "Player 1 (You)"
//             health: 4
//             playerIndex: 0
//             isSelectable: gameManager && gameManager.isSelectingTarget

//             onSelected: function(playerIdx) {
//                 console.log("玩家区域点击:", playerIdx)
//                 gameManager.selectTargetPlayer(playerIdx);
//                 resetTargetSelection();
//             }

//             // 添加制衡信号处理
//             onZhihengRequested: {
//                 enterZhihengMode();
//             }

//             // 装备区
//             Column {
//                 id: equipmentArea
//                 anchors {
//                     top: parent.bottom
//                     horizontalCenter: parent.horizontalCenter
//                     topMargin: parent.height * 0.03
//                 }
//                 spacing: 5

//                 Text {
//                     text: "装备区"
//                     color: "white"
//                     font.bold: true
//                     font.pixelSize: 14
//                     anchors.horizontalCenter: parent.horizontalCenter
//                 }

//                 Grid {
//                     columns: 2
//                     spacing: 8

//                     // 武器
//                     Loader {
//                         sourceComponent: equipmentItemComponent
//                         property string equipmentType: "武器"
//                         property string source: "qrc:/zhuangbei/zhugeliannu"
//                     }

//                     // 防具
//                     Loader {
//                         sourceComponent: equipmentItemComponent
//                         property string equipmentType: "防具"
//                         property string source: "qrc:/images/armor.png"
//                     }

//                     // 进攻马
//                     Loader {
//                         sourceComponent: equipmentItemComponent
//                         property string equipmentType: "+1马"
//                         property string source: "qrc:/zhuangbei/jinggongma"
//                     }

//                     // 防御马
//                     Loader {
//                         sourceComponent: equipmentItemComponent
//                         property string equipmentType: "-1马"
//                         property string source: "qrc:/zhuangbei/fangyuma"
//                     }
//                 }
//             }
//         }
//     }

//     // 5. 功能按钮
//     Row {
//         anchors {
//             bottom: handArea.top
//             horizontalCenter: parent.horizontalCenter
//             bottomMargin: parent.height * 0.02
//         }
//         spacing: parent.width * 0.02

//         Button {
//             width: parent.width * 0.08
//             height: parent.height * 0.04
//             text: "洗牌"
//             font.pixelSize: 12
//             onClicked: {
//                 if (gameManager) {
//                     gameManager.shuffleDeck();
//                 }
//             }
//         }

//         Button {
//             width: parent.width * 0.08
//             height: parent.height * 0.04
//             text: "结束回合"
//             font.pixelSize: 12
//             onClicked: {
//                 if (gameManager) {
//                     gameManager.endTurn();
//                 }
//             }
//         }

//         Button {
//             width: parent.width * 0.08
//             height: parent.height * 0.04
//             text: "退出"
//             font.pixelSize: 12
//             onClicked: Qt.quit()
//         }
//     }

//     // 响应提示框
//     Rectangle {
//         id: responsePanel
//         anchors.centerIn: parent
//         width: parent.width * 0.25
//         height: parent.height * 0.18
//         color: "#AA000000"
//         border.color: "gold"
//         border.width: 3
//         radius: 10
//         visible: isShanRequired || isWuXiekejiRequired

//         Text {
//             id: responseText
//             anchors.top: parent.top
//             anchors.horizontalCenter: parent.horizontalCenter
//             anchors.topMargin: parent.height * 0.02
//             text: {
//                 if (isShanRequired) {
//                     return "请响应【杀】，打出一张【闪】"
//                 } else if (isWuXiekejiRequired) {
//                     return "请响应【锦囊】，打出一张【无懈可击】"
//                 }
//                 return ""
//             }
//             color: "white"
//             font.pixelSize: parent.height * 0.035
//             font.bold: true
//         }

//         Row {
//             anchors.centerIn: parent
//             spacing: parent.width * 0.02

//             Button {
//                 width: responsePanel.width * 0.3
//                 height: responsePanel.height * 0.2
//                 text: "确定响应"
//                 font.pixelSize: 12
//                 visible: (isShanRequired && currentPlayer.hasShan) ||
//                          (isWuXiekejiRequired && currentPlayer.hasWuXiekeji)
//                 onClicked: {
//                     // 进入响应模式
//                     resetResponseCards();
//                 }
//             }

//             Button {
//                 width: responsePanel.width * 0.3
//                 height: responsePanel.height * 0.2
//                 text: "取消响应"
//                 font.pixelSize: 12
//                 onClicked: {
//                     if (gameManager) {
//                         gameManager.cancelResponse();
//                     }
//                     isShanRequired = false;
//                     isWuXiekejiRequired = false;
//                     resetResponseCards();
//                 }
//             }
//         }

//         Text {
//             anchors.bottom: parent.bottom
//             anchors.horizontalCenter: parent.horizontalCenter
//             anchors.bottomMargin: parent.height * 0.015
//             text: "剩余时间: " + Math.ceil(responseTimer.remainingTime / 1000) + "秒"
//             color: "white"
//             font.pixelSize: parent.height * 0.025
//         }
//     }

//     // 制衡确认面板
//     Rectangle {
//         id: zhihengPanel
//         anchors.centerIn: parent
//         width: parent.width * 0.3
//         height: parent.height * 0.15
//         color: "#AA000000"
//         border.color: "gold"
//         border.width: 3
//         radius: 10
//         visible: isZhihengMode

//         Column {
//             anchors.centerIn: parent
//             spacing: 10

//             Text {
//                 text: "制衡: 已选择 " + zhihengCardCount + " 张牌"
//                 color: "white"
//                 font.pixelSize: parent.height * 0.035
//                 font.bold: true
//                 anchors.horizontalCenter: parent.horizontalCenter
//             }

//             Row {
//                 spacing: 20
//                 anchors.horizontalCenter: parent.horizontalCenter

//                 Button {
//                     text: "确认弃牌"
//                     width: zhihengPanel.width * 0.3
//                     height: zhihengPanel.height * 0.3
//                     onClicked: {
//                         // 执行制衡技能
//                         executeZhiheng();
//                     }

//                     background: Rectangle {
//                         color: "#4CAF50"
//                         radius: 5
//                     }
//                 }

//                 Button {
//                     text: "取消"
//                     width: zhihengPanel.width * 0.3
//                     height: zhihengPanel.height * 0.3
//                     onClicked: {
//                         // 取消制衡
//                         cancelZhiheng();
//                     }

//                     background: Rectangle {
//                         color: "#F44336"
//                         radius: 5
//                     }
//                 }
//             }
//         }
//     }

//     Timer {
//         id: responseTimer
//         interval: 1000
//         repeat: true
//         running: responsePanel.visible
//         property int remainingTime: 15000

//         onTriggered: {
//             remainingTime -= 1000;
//             if (remainingTime <= 0) {
//                 stop();
//                 if (gameManager) {
//                     gameManager.cancelResponse();
//                 }
//                 isShanRequired = false;
//                 isWuXiekejiRequired = false;
//                 resetResponseCards();
//             }
//         }

//         onRunningChanged: {
//             if (running) {
//                 remainingTime = 15000;
//             }
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
//             // 使用深拷贝创建新对象
//             var newCard = JSON.parse(JSON.stringify(cardData));
//             newCard.isResponseCard = false; // 初始化响应状态
//             // 制衡模式属性初始化
//             newCard.isSelectableForZhiheng = false;
//             newCard.isSelectedForZhiheng = false;
//             handCardsModel.append(newCard);
//         }

//         function onCardRemoved(index) {
//             if (index >= 0 || index < handCardsModel.count) {
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
//             // 更新玩家区域的可选状态
//             player1Area.isSelectable = true;
//             player2Area.isSelectable = true;
//             cancelButton.visible = true;
//         }

//         function onTargetSelectionCanceled() {
//             resetTargetSelection();
//         }

//         function onCardPlayedWithTarget(cardIndex, playerIndex) {
//             resetTargetSelection();
//         }

//         // 响应手牌重置信号
//         function onHandCardsReset() {
//             console.log("手牌重置");
//             handCardsModel.clear();
//             var handCards = gameManager.getHandCards();
//             for (var i = 0; i < handCards.length; i++) {
//                 // 深拷贝卡牌数据
//                 var cardData = JSON.parse(JSON.stringify(handCards[i]));
//                 cardData.isResponseCard = false;
//                 // 制衡模式属性初始化
//                 cardData.isSelectableForZhiheng = false;
//                 cardData.isSelectedForZhiheng = false;
//                 handCardsModel.append(cardData);
//             }
//         }

//         function onRequireShanResponse(targetPlayer) {
//             isShanRequired = true;
//             responsePlayerIndex = targetPlayer.getPlayerIndex();
//             responseTimer.start();

//             // 标记所有闪牌为可响应
//             for (var i = 0; i < handCardsModel.count; i++) {
//                 if (handCardsModel.get(i).name === "Shan") {
//                     handCardsModel.setProperty(i, "isResponseCard", true);
//                 }
//             }
//         }

//         function onRequireWuXiekejiResponse(sourceCard) {
//             isWuXiekejiRequired = true;
//             responseTimer.start();

//             // 标记所有无懈可击牌为可响应
//             for (var i = 0; i < handCardsModel.count; i++) {
//                 if (handCardsModel.get(i).name === "Wu_Xiekeji") {
//                     handCardsModel.setProperty(i, "isResponseCard", true);
//                 }
//             }
//         }

//         function onResponseReceived(responseCard, responder) {
//             isShanRequired = false;
//             isWuXiekejiRequired = false;
//             resetResponseCards();
//         }

//         function onWuXiekejiResponseFinished() {
//             isWuXiekejiRequired = false;
//             resetResponseCards();
//         }

//         // 处理取消响应信号
//         function onCancelResponseCalled() {
//             isShanRequired = false;
//             isWuXiekejiRequired = false;
//             resetResponseCards();
//         }

//         // 处理制衡技能信号
//         function onZhihengUsed() {
//             enterZhihengMode();
//         }
//     }

//     // 取消按钮
//     Button {
//         id: cancelButton
//         anchors {
//             top: parent.top
//             right: parent.right
//             margins: parent.width * 0.015
//         }
//         width: parent.width * 0.07
//         height: parent.height * 0.04
//         text: "取消选择"
//         font.pixelSize: 12
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
//             font.pixelSize: parent.height * 0.02
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
//                 // 深拷贝卡牌数据
//                 var cardData = JSON.parse(JSON.stringify(handCards[i]));
//                 cardData.isResponseCard = false;
//                 // 制衡模式属性初始化
//                 cardData.isSelectableForZhiheng = false;
//                 cardData.isSelectedForZhiheng = false;
//                 handCardsModel.append(cardData);
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
//         player1Area.isSelectable = false;
//         player2Area.isSelectable = false;
//         player1Area.isSelected = false;
//         player2Area.isSelected = false;
//         cancelButton.visible = false;
//         selectedPlayerIndex = -1;
//     }

//     // 重置响应卡牌状态
//     function resetResponseCards() {
//         for (var i = 0; i < handCardsModel.count; i++) {
//             handCardsModel.setProperty(i, "isResponseCard", false);
//         }
//     }

//     // 进入制衡模式
//     function enterZhihengMode() {
//         console.log("进入制衡模式");
//         gameArea.isZhihengMode = true;
//         gameArea.zhihengCardCount = 0;
//         gameArea.selectedZhihengCards = [];

//         // 设置所有卡牌可选
//         for (var i = 0; i < handCardsModel.count; i++) {
//             handCardsModel.setProperty(i, "isSelectableForZhiheng", true);
//         }
//     }

//     // 制衡相关函数
//     function toggleCardForZhiheng(index) {
//         if (!isZhihengMode) return;


//         var wasSelected = handCardsModel.get(index).isSelectedForZhiheng;
//         handCardsModel.setProperty(index, "isSelectedForZhiheng", !wasSelected);

//         if (!wasSelected) {

//             zhihengCardCount++;
//             selectedZhihengCards.push(index);
//         } else {

//             zhihengCardCount--;
//             var pos = selectedZhihengCards.indexOf(index);
//             if (pos !== -1) {
//                 selectedZhihengCards.splice(pos, 1);
//             }
//         }
//     }

//     function executeZhiheng() {
//         if (zhihengCardCount === 0) {
//                 cancelZhiheng();
//                 return;
//             }

//             // 获取当前玩家
//             var currentPlayer = gameManager.getdangqianplayer();
//             if (!currentPlayer) return;

//             var wujiang = currentPlayer.getwujiang();
//             if (!wujiang) return;

//             // 获取选中的卡牌指针
//             var cardsToDiscard = [];
//             for (var i = 0; i < selectedZhihengCards.length; i++) {
//                 var index = selectedZhihengCards[i];
//                 if (index >= 0 && index < handCardsModel.count) {
//                     // 从GameManager的手牌中获取卡牌指针
//                     var cardPtr = gameManager.gethandcards()[index];
//                     cardsToDiscard.push(cardPtr);
//                 }
//             }

//             // 执行制衡技能，传递GameManager实例
//             wujiang.executeZhiheng(cardsToDiscard, gameManager);

//             // 重置制衡模式
//             cancelZhiheng();
//     }

//     function cancelZhiheng() {
//         gameArea.isZhihengMode = false;
//         gameArea.zhihengCardCount = 0;
//         gameArea.selectedZhihengCards = [];

//         // 重置卡牌状态
//         for (var i = 0; i < handCardsModel.count; i++) {
//             handCardsModel.setProperty(i, "isSelectableForZhiheng", false);
//             handCardsModel.setProperty(i, "isSelectedForZhiheng", false);
//         }
//     }
// }
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Sanguosha.Resources

Item {
    id: gameArea
    anchors.fill: parent
    signal backToMenu()

    property ListModel handCardsModel: ListModel {}
    property var topDiscardCard: ({})
    property int selectedCardIndex: -1
    property int selectedPlayerIndex: -1
    property bool isShanRequired: false
    property bool isWuXiekejiRequired: false
    property int responsePlayerIndex: -1

    // 制衡模式相关属性
    property bool isZhihengMode: false
    property int zhihengCardCount: 0
    property var selectedZhihengCards: []

    // 装备项组件
    Component {
        id: equipmentItemComponent

        Item {
            id: equipmentItem
            width: 70
            height: 25
            property string equipmentType: ""
            property string source: ""

            Row {
                spacing: 5
                anchors.centerIn: parent

                Image {
                    width: 20
                    height: 20
                    source: equipmentItem.source
                }

                Text {
                    text: equipmentItem.equipmentType
                    color: "white"
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    // 1. 背景
    AnimatedImage {
        anchors.fill: parent
        source: "/root/Sanguosha/beijing.gif"
        playing: true
        fillMode: Image.PreserveAspectCrop
    }

    // 2. 牌堆区域 - 左上角
    Item {
        id: deckArea
        width: parent.width * 0.1
        height: parent.height * 0.15
        anchors {
            top: parent.top
            left: parent.left
            topMargin: parent.height * 0.03
            leftMargin: parent.width * 0.03
        }

        // 牌堆
        Image {
            id: deckBack
            width: parent.width * 0.8
            height: parent.height * 0.9
            anchors.centerIn: parent
            source: "qrc:/paibei.webp"

            Text {
                anchors.centerIn: parent
                text: gameManager ? gameManager.deckCount : "0"
                color: "white"
                font {
                    bold: true;
                    pixelSize: parent.height * 0.15
                }
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
            bottomMargin: parent.height * 0.03
        }
        height: parent.height * 0.25

        Flow {
            id: handCardsFlow
            anchors.centerIn: parent
            spacing: -parent.width * 0.03
            width: parent.width * 0.9

            Repeater {
                id: handCardsRepeater
                model: handCardsModel

                delegate: CardItem {
                    width: handArea.width * 0.08
                    height: handArea.height * 0.8
                    cardName: model.name
                    cardSuit: model.suit
                    point: model.point
                    cardIndex: index
                    isNewCard: model.isNew
                    isSelected: index === gameArea.selectedCardIndex
                    isResponseCard: model.isResponseCard
                    // 制衡模式属性
                    isSelectableForZhiheng: model.isSelectableForZhiheng
                    isSelectedForZhiheng: model.isSelectedForZhiheng

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
    Item {
        id: playersContainer
        anchors.fill: parent

        // 玩家2 (顶部中央)
        PlayerArea {
            id: player2Area
            width: parent.width * 0.2
            height: parent.height * 0.2
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
                topMargin: parent.height * 0.1
            }
            playerName: "Player 2"
            health: 4
            playerIndex: 1
            isSelectable: gameManager && gameManager.isSelectingTarget
            gameManager: gameManager // 传递gameManager实例

            onSelected: function(playerIdx) {
                console.log("玩家区域点击:", playerIdx)
                gameManager.selectTargetPlayer(playerIdx);
                resetTargetSelection();
            }
        }

        // 玩家1 (右上角)
        PlayerArea {
            id: player1Area
            width: parent.width * 0.2
            height: parent.height * 0.2
            anchors {
                bottom: handArea.top
                right: parent.right
                bottomMargin: parent.height * 0.03
                rightMargin: parent.width * 0.03
            }
            playerName: "Player 1 (You)"
            health: 4
            playerIndex: 0
            isSelectable: gameManager && gameManager.isSelectingTarget
            gameManager: gameManager // 传递gameManager实例

            onSelected: function(playerIdx) {
                console.log("玩家区域点击:", playerIdx)
                gameManager.selectTargetPlayer(playerIdx);
                resetTargetSelection();
            }

            // 添加制衡信号处理
            onZhihengRequested: {
                enterZhihengMode();
            }

            // 装备区
            Column {
                id: equipmentArea
                anchors {
                    top: parent.bottom
                    horizontalCenter: parent.horizontalCenter
                    topMargin: parent.height * 0.03
                }
                spacing: 5

                Text {
                    text: "装备区"
                    color: "white"
                    font.bold: true
                    font.pixelSize: 14
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Grid {
                    columns: 2
                    spacing: 8

                    // 武器
                    Loader {
                        sourceComponent: equipmentItemComponent
                        property string equipmentType: "武器"
                        property string source: "qrc:/zhuangbei/zhugeliannu"
                    }

                    // 防具
                    Loader {
                        sourceComponent: equipmentItemComponent
                        property string equipmentType: "防具"
                        property string source: "qrc:/images/armor.png"
                    }

                    // 进攻马
                    Loader {
                        sourceComponent: equipmentItemComponent
                        property string equipmentType: "+1马"
                        property string source: "qrc:/zhuangbei/jinggongma"
                    }

                    // 防御马
                    Loader {
                        sourceComponent: equipmentItemComponent
                        property string equipmentType: "-1马"
                        property string source: "qrc:/zhuangbei/fangyuma"
                    }
                }
            }
        }
    }

    // 5. 功能按钮
    Row {
        anchors {
            bottom: handArea.top
            horizontalCenter: parent.horizontalCenter
            bottomMargin: parent.height * 0.02
        }
        spacing: parent.width * 0.02

        Button {
            width: parent.width * 0.08
            height: parent.height * 0.04
            text: "洗牌"
            font.pixelSize: 12
            onClicked: {
                if (gameManager) {
                    gameManager.shuffleDeck();
                }
            }
        }

        Button {
            width: parent.width * 0.08
            height: parent.height * 0.04
            text: "结束回合"
            font.pixelSize: 12
            onClicked: {
                if (gameManager) {
                    gameManager.endTurn();
                }
            }
        }

        Button {
            width: parent.width * 0.08
            height: parent.height * 0.04
            text: "退出"
            font.pixelSize: 12
            onClicked: Qt.quit()
        }
    }

    // 响应提示框
    Rectangle {
        id: responsePanel
        anchors.centerIn: parent
        width: parent.width * 0.25
        height: parent.height * 0.18
        color: "#AA000000"
        border.color: "gold"
        border.width: 3
        radius: 10
        visible: isShanRequired || isWuXiekejiRequired

        Text {
            id: responseText
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: parent.height * 0.02
            text: {
                if (isShanRequired) {
                    return "请响应【杀】，打出一张【闪】"
                } else if (isWuXiekejiRequired) {
                    return "请响应【锦囊】，打出一张【无懈可击】"
                }
                return ""
            }
            color: "white"
            font.pixelSize: parent.height * 0.035
            font.bold: true
        }

        Row {
            anchors.centerIn: parent
            spacing: parent.width * 0.02

            Button {
                width: responsePanel.width * 0.3
                height: responsePanel.height * 0.2
                text: "确定响应"
                font.pixelSize: 12
                visible: (isShanRequired && currentPlayer.hasShan) ||
                         (isWuXiekejiRequired && currentPlayer.hasWuXiekeji)
                onClicked: {
                    // 进入响应模式
                    resetResponseCards();
                }
            }

            Button {
                width: responsePanel.width * 0.3
                height: responsePanel.height * 0.2
                text: "取消响应"
                font.pixelSize: 12
                onClicked: {
                    if (gameManager) {
                        gameManager.cancelResponse();
                    }
                    isShanRequired = false;
                    isWuXiekejiRequired = false;
                    resetResponseCards();
                }
            }
        }

        Text {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: parent.height * 0.015
            text: "剩余时间: " + Math.ceil(responseTimer.remainingTime / 1000) + "秒"
            color: "white"
            font.pixelSize: parent.height * 0.025
        }
    }

    // 制衡确认面板
    Rectangle {
        id: zhihengPanel
        anchors.centerIn: parent
        width: parent.width * 0.3
        height: parent.height * 0.15
        color: "#AA000000"
        border.color: "gold"
        border.width: 3
        radius: 10
        visible: isZhihengMode

        Column {
            anchors.centerIn: parent
            spacing: 10

            Text {
                text: "制衡: 已选择 " + zhihengCardCount + " 张牌"
                color: "white"
                font.pixelSize: parent.height * 0.035
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                spacing: 20
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    text: "确认弃牌"
                    width: zhihengPanel.width * 0.3
                    height: zhihengPanel.height * 0.3
                    onClicked: {
                        // 执行制衡技能
                        executeZhiheng();
                    }

                    background: Rectangle {
                        color: "#4CAF50"
                        radius: 5
                    }
                }

                Button {
                    text: "取消"
                    width: zhihengPanel.width * 0.3
                    height: zhihengPanel.height * 0.3
                    onClicked: {
                        // 取消制衡
                        cancelZhiheng();
                    }

                    background: Rectangle {
                        color: "#F44336"
                        radius: 5
                    }
                }
            }
        }
    }

    Timer {
        id: responseTimer
        interval: 1000
        repeat: true
        running: responsePanel.visible
        property int remainingTime: 15000

        onTriggered: {
            remainingTime -= 1000;
            if (remainingTime <= 0) {
                stop();
                if (gameManager) {
                    gameManager.cancelResponse();
                }
                isShanRequired = false;
                isWuXiekejiRequired = false;
                resetResponseCards();
            }
        }

        onRunningChanged: {
            if (running) {
                remainingTime = 15000;
            }
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
            newCard.isResponseCard = false; // 初始化响应状态
            // 制衡模式属性初始化
            newCard.isSelectableForZhiheng = false;
            newCard.isSelectedForZhiheng = false;
            handCardsModel.append(newCard);
        }

        function onCardRemoved(index) {
            if (index >= 0 || index < handCardsModel.count) {
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
            // 更新玩家区域的可选状态
            player1Area.isSelectable = true;
            player2Area.isSelectable = true;
            cancelButton.visible = true;
        }

        function onTargetSelectionCanceled() {
            resetTargetSelection();
        }

        function onCardPlayedWithTarget(cardIndex, playerIndex) {
            resetTargetSelection();
        }

        // 响应手牌重置信号
        function onHandCardsReset() {
            console.log("手牌重置");
            handCardsModel.clear();
            var handCards = gameManager.getHandCards();
            for (var i = 0; i < handCards.length; i++) {
                // 深拷贝卡牌数据
                var cardData = JSON.parse(JSON.stringify(handCards[i]));
                cardData.isResponseCard = false;
                // 制衡模式属性初始化
                cardData.isSelectableForZhiheng = false;
                cardData.isSelectedForZhiheng = false;
                handCardsModel.append(cardData);
            }
        }

        function onRequireShanResponse(targetPlayer) {
            isShanRequired = true;
            responsePlayerIndex = targetPlayer.getPlayerIndex();
            responseTimer.start();

            // 标记所有闪牌为可响应
            for (var i = 0; i < handCardsModel.count; i++) {
                if (handCardsModel.get(i).name === "Shan") {
                    handCardsModel.setProperty(i, "isResponseCard", true);
                }
            }
        }

        function onRequireWuXiekejiResponse(sourceCard) {
            isWuXiekejiRequired = true;
            responseTimer.start();

            // 标记所有无懈可击牌为可响应
            for (var i = 0; i < handCardsModel.count; i++) {
                if (handCardsModel.get(i).name === "Wu_Xiekeji") {
                    handCardsModel.setProperty(i, "isResponseCard", true);
                }
            }
        }

        function onResponseReceived(responseCard, responder) {
            isShanRequired = false;
            isWuXiekejiRequired = false;
            resetResponseCards();
        }

        function onWuXiekejiResponseFinished() {
            isWuXiekejiRequired = false;
            resetResponseCards();
        }

        // 处理取消响应信号
        function onCancelResponseCalled() {
            isShanRequired = false;
            isWuXiekejiRequired = false;
            resetResponseCards();
        }

        // 处理制衡技能信号
        function onZhihengUsed() {
            enterZhihengMode();
        }
    }

    // 取消按钮
    Button {
        id: cancelButton
        anchors {
            top: parent.top
            right: parent.right
            margins: parent.width * 0.015
        }
        width: parent.width * 0.07
        height: parent.height * 0.04
        text: "取消选择"
        font.pixelSize: 12
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
            font.pixelSize: parent.height * 0.02
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
                cardData.isResponseCard = false;
                // 制衡模式属性初始化
                cardData.isSelectableForZhiheng = false;
                cardData.isSelectedForZhiheng = false;
                handCardsModel.append(cardData);
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
        player1Area.isSelectable = false;
        player2Area.isSelectable = false;
        player1Area.isSelected = false;
        player2Area.isSelected = false;
        cancelButton.visible = false;
        selectedPlayerIndex = -1;
    }

    // 重置响应卡牌状态
    function resetResponseCards() {
        for (var i = 0; i < handCardsModel.count; i++) {
            handCardsModel.setProperty(i, "isResponseCard", false);
        }
    }

    // 进入制衡模式
    function enterZhihengMode() {
        console.log("进入制衡模式");
        gameArea.isZhihengMode = true;
        gameArea.zhihengCardCount = 0;
        gameArea.selectedZhihengCards = [];

        // 设置所有卡牌可选
        for (var i = 0; i < handCardsModel.count; i++) {
            handCardsModel.setProperty(i, "isSelectableForZhiheng", true);
        }
    }

    // 制衡相关函数
    function toggleCardForZhiheng(index) {
        if (!isZhihengMode) return;


        var wasSelected = handCardsModel.get(index).isSelectedForZhiheng;
        handCardsModel.setProperty(index, "isSelectedForZhiheng", !wasSelected);

        if (!wasSelected) {

            zhihengCardCount++;
            selectedZhihengCards.push(index);
        } else {

            zhihengCardCount--;
            var pos = selectedZhihengCards.indexOf(index);
            if (pos !== -1) {
                selectedZhihengCards.splice(pos, 1);
            }
        }
    }

    function executeZhiheng() {
        if (zhihengCardCount === 0) {
                cancelZhiheng();
                return;
            }

            // 获取当前玩家
            var currentPlayer = gameManager.getdangqianplayer();
            if (!currentPlayer) return;

            var wujiang = currentPlayer.getwujiang();
            if (!wujiang) return;

            // 获取选中的卡牌指针
            var cardsToDiscard = [];
            for (var i = 0; i < selectedZhihengCards.length; i++) {
                var index = selectedZhihengCards[i];
                if (index >= 0 && index < handCardsModel.count) {
                    // 从GameManager的手牌中获取卡牌指针
                    var cardPtr = gameManager.gethandcards()[index];
                    cardsToDiscard.push(cardPtr);
                }
            }

            // 执行制衡技能，传递GameManager实例
            wujiang.executeZhiheng(cardsToDiscard, gameManager);

            // 重置制衡模式
            cancelZhiheng();
    }

    function cancelZhiheng() {
        gameArea.isZhihengMode = false;
        gameArea.zhihengCardCount = 0;
        gameArea.selectedZhihengCards = [];

        // 重置卡牌状态
        for (var i = 0; i < handCardsModel.count; i++) {
            handCardsModel.setProperty(i, "isSelectableForZhiheng", false);
            handCardsModel.setProperty(i, "isSelectedForZhiheng", false);
        }
    }
}
