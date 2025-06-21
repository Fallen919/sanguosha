#include "gamemanager.h"
#include <QDebug>

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    // 初始化玩家手牌
    for (int i = 0; i < 4; i++) {
        card drawnCard = m_carddex.mopai();
        m_playerHand.append(drawnCard);
    }
    m_prevHand = m_playerHand; // 保存初始状态
}

void GameManager::drawCard()
{
    card drawnCard = m_carddex.mopai();
    m_playerHand.append(drawnCard);

    QVariantMap cardData;
    cardData["name"] = drawnCard.NewGetName();
    cardData["suit"] = drawnCard.getSuit();
    cardData["point"] = drawnCard.getPoint();
    cardData["type"] = drawnCard.getType();

    emit cardAdded(cardData);
    emit deckCountChanged(deckCount());

    m_prevHand = m_playerHand; // 更新状态
}

void GameManager::playCard(int handIndex) {
    if (handIndex < 0 || handIndex >= m_playerHand.size()) {
        qWarning() << "Invalid hand index:" << handIndex;
        return;
    }

    card playedCard = m_playerHand.at(handIndex);
    m_playerHand.removeAt(handIndex);

    QVariantMap cardData;
    cardData["name"] = playedCard.NewGetName();
    cardData["suit"] = playedCard.getSuit();
    cardData["point"] = playedCard.getPoint();
    cardData["type"] = playedCard.getType();

    emit cardRemoved(handIndex);
    emit cardPlayed(cardData); // 发出卡牌使用信号，但卡牌尚未进入弃牌堆

    // 注意：这里不再立即将卡牌加入弃牌堆
    // 卡牌的具体处理（是否进入弃牌堆）由后续逻辑决定
}

void GameManager::discardCard(int handIndex) {
    if (handIndex < 0 || handIndex >= m_playerHand.size()) {
        qWarning() << "Invalid hand index:" << handIndex;
        return;
    }

    card discardedCard = m_playerHand.at(handIndex);
    m_playerHand.removeAt(handIndex);

    QVariantMap cardData;
    cardData["name"] = discardedCard.NewGetName();
    cardData["suit"] = discardedCard.getSuit();
    cardData["point"] = discardedCard.getPoint();
    cardData["type"] = discardedCard.getType();

    emit cardRemoved(handIndex);
    emit cardDiscarded(cardData);

    // 直接弃置的牌立即进入弃牌堆
    moveCardToDiscard(cardData);  // 确保只有一次加入弃牌堆的操作
}
void GameManager::moveCardToDiscard(const QVariantMap &cardData) {
    card c;
    c.setName(cardData["name"].toString());
    c.setSuit(cardData["suit"].toString());
    c.setPoint(cardData["point"].toInt());
    c.setType(cardData["type"].toString());

    m_carddex.addToDiscardPile(c);
    emit cardMovedToDiscard(cardData);
    emit discardPileChanged(discardPileCount());
}
void GameManager::shuffleDeck()
{
    m_carddex.xipai();
    emit deckCountChanged(deckCount());
}
//牌堆数量
int GameManager::deckCount() const
{
    return m_carddex.count();
}
//弃牌堆数量
int GameManager::discardPileCount() const {
    return m_carddex.discardCount();
}
//弃牌堆顶
QVariantMap GameManager::getTopDiscardCard() {
    return m_carddex.getTopDiscardCard();
}

QVariantList GameManager::getHandCards() const
{
    QVariantList handCards;

    for (const card &c : m_playerHand) {
        QVariantMap cardData;
        cardData["name"] = c.NewGetName();
        cardData["suit"] = c.getSuit();
        cardData["point"] = c.getPoint();
        cardData["type"] = c.getType();
        handCards.append(cardData);
    }

    return handCards;
}

void GameManager::initHandCards()
{
    // 发送初始手牌信号
    for (const card &c : m_playerHand) {
        QVariantMap cardData;
        cardData["name"] = c.NewGetName();
        cardData["suit"] = c.getSuit();
        cardData["point"] = c.getPoint();
        cardData["type"] = c.getType();
        emit cardAdded(cardData);
    }
}
