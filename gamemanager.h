#pragma once

#include <QObject>
#include <QList>
#include <QVariant>
#include "card.h"
#include "carddex.h"
#include <list>

class GameManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(int deckCount READ deckCount NOTIFY deckCountChanged)
    Q_PROPERTY(int discardPileCount READ discardPileCount NOTIFY discardPileChanged)

public:
    explicit GameManager(QObject *parent = nullptr);
    static GameManager *pt();

    // 玩家操作
    Q_INVOKABLE card *drawCard();
    Q_INVOKABLE void playCard(int handIndex);
    Q_INVOKABLE void discardCard(int handIndex);
    Q_INVOKABLE void shuffleDeck(); // 洗牌

    // 卡牌状态管理
    Q_INVOKABLE void moveCardToDiscard(const QVariantMap &cardData); // 将卡牌移入弃牌堆

    // 获取游戏状态（牌堆的牌数，或者获取牌堆，手牌的信息）
    int deckCount() const;
    int discardPileCount() const;
    Q_INVOKABLE QVariantList getHandCards() const;
    Q_INVOKABLE void initHandCards();
    Q_INVOKABLE QVariantMap getTopDiscardCard();

    Q_INVOKABLE void setplayers(player *p);
    Q_INVOKABLE std::list<player *> getplayers();

    Q_INVOKABLE void setdangqianplayer(player *p);
    Q_INVOKABLE player *getdangqianplayer();

    Carddex *getcarddex();
    QList<card *> gethandcards();

signals:
    // 游戏状态
    void deckCountChanged(int count); // 牌堆数量变化
    void discardPileChanged(int count); // 弃牌堆数量变化
    void cardAdded(const QVariantMap &cardData);
    void cardRemoved(int index);
    void cardPlayed(const QVariantMap &cardData); // 卡牌被使用（锦囊牌，装备牌使用后可能尚未进入弃牌堆）
    void cardDiscarded(const QVariantMap &cardData); // 卡牌被弃置（直接进入弃牌堆）
    void cardMovedToDiscard(const QVariantMap &cardData); // 卡牌进入弃牌堆

private:
    Carddex m_carddex;
    QList<card *> m_playerHand;
    // QList<card> m_prevHand;
    std::list<player *> m_player;
    player *m_dangqianplayer;
    static GameManager *m_pt;
};
