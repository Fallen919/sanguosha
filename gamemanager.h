#pragma once

#include <QObject>
#include <QList>
#include <QVariant>
#include "card.h"
#include "carddex.h"
#include <list>

class GameManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(
        int deckCount READ deckCount NOTIFY deckCountChanged)
    Q_PROPERTY(
        int discardPileCount READ discardPileCount NOTIFY discardPileChanged)
    Q_PROPERTY(
        bool isSelectingTarget READ isSelectingTarget NOTIFY isSelectingTargetChanged)

public:
    explicit GameManager(QObject *parent = nullptr);

    enum ResponseType { NoResponse, ShanResponse, WuXiekejiResponse };

    // 玩家操作
    Q_INVOKABLE card *drawCard();
    Q_INVOKABLE void playCard(int handIndex);
    Q_INVOKABLE void discardCard(int handIndex);
    Q_INVOKABLE void shuffleDeck(); // 洗牌

    //判定
    Q_INVOKABLE card *panding();

    // 卡牌状态管理
    Q_INVOKABLE void moveCardToDiscard(card *c); // 将卡牌移入弃牌堆

    // 获取游戏状态（牌堆的牌数，或者获取牌堆，手牌的信息）
    Q_INVOKABLE int deckCount() const;
    Q_INVOKABLE int discardPileCount() const;
    Q_INVOKABLE QVariantList getHandCards() const;
    Q_INVOKABLE void initHandCards();
    Q_INVOKABLE QVariantMap getTopDiscardCard();

    Q_INVOKABLE void setplayers(player *p);
    Q_INVOKABLE std::list<player *> getplayers();

    Q_INVOKABLE void setdangqianplayer(player *p);
    Q_INVOKABLE player *getdangqianplayer();

    Carddex *getcarddex();
    QList<card *> gethandcards();

    Q_INVOKABLE void selectTargetPlayer(int playerIndex); // 新增目标选择方法
    Q_INVOKABLE void cancelTargetSelection();             // 取消目标选择
    Q_INVOKABLE bool requiresTarget(int handIndex);       // 判断卡牌是否需要目标
    Q_INVOKABLE void startTargetSelection(int cardIndex); // 开始目标选择
    Q_INVOKABLE bool isSelectingTarget() const { return m_isSelectingTarget; }

    void removecard(card *c);

    // 响应管理
    Q_INVOKABLE bool waitForShanResponse(player *targetPlayer, card *sourceCard);
    Q_INVOKABLE bool waitForWuXiekejiResponse(card *sourceCard);
    Q_INVOKABLE void respondToCard(card *responseCard, player *responder);

    // 当前响应的卡牌和目标
    Q_INVOKABLE card *currentResponseCard() const { return m_currentResponseCard; }
    Q_INVOKABLE player *currentResponseTarget() const { return m_currentResponseTarget; }
    Q_INVOKABLE ResponseType currentResponseType() const { return m_currentResponseType; }

    Q_INVOKABLE void playResponseCard(int cardIndex);

signals:
    // 游戏状态
    void deckCountChanged(int count);   // 牌堆数量变化
    void discardPileChanged(int count); // 弃牌堆数量变化
    void cardAdded(const QVariantMap &cardData);
    void cardRemoved(int index);
    void cardPlayed(
        const QVariantMap &cardData); // 卡牌被使用（锦囊牌，装备牌使用后可能尚未进入弃牌堆）
    void cardDiscarded(const QVariantMap &cardData);                 // 卡牌被弃置（直接进入弃牌堆）
    void cardMovedToDiscard(const QVariantMap &cardData);            // 卡牌进入弃牌堆
    void targetSelectionStarted(int cardIndex);                      // 目标选择开始信号
    void targetSelectionCanceled();                                  // 目标选择取消信号
    void cardPlayedWithTarget(int cardIndex, int targetPlayerIndex); // 带目标的出牌信号
    void isSelectingTargetChanged(bool isSelecting);                 // 目标选择状态改变
    void handCardsReset();
    void requireShanResponse(player *targetPlayer);               // 需要闪响应
    void requireWuXiekejiResponse(card *sourceCard);              // 需要无懈可击响应
    void responseReceived(card *responseCard, player *responder); // 响应卡牌打出
    void wuXiekejiResponseFinished();

private:
    Carddex m_carddex;
    QList<card *> m_playerHand;
    // QList<card> m_prevHand;
    std::list<player *> m_player;
    player *m_dangqianplayer;
    int m_selectedCardIndex = -1;     // 当前选中的卡牌索引
    bool m_isSelectingTarget = false; // 是否正在选择目标
    ResponseType m_currentResponseType = NoResponse;
    card *m_currentResponseCard = nullptr;
    player *m_currentResponseTarget = nullptr;
    bool m_responseReceived = false;
    bool m_responseResult = false;
};
