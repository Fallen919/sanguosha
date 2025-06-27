#include "gamemanager.h"
#include <QDebug>
#include "player.h"
GameManager::GameManager(
    QObject *parent)
    : QObject(parent)
{
    m_carddex.xipai();
    player *p = new player(this);
    GameManager::setplayers(p);
    p->setmynum(1);
    m_dangqianplayer = p;
    std::list<player *>::iterator it = m_player.begin();
    (*it)->mopai(4, this);
}

card *GameManager::drawCard()
{
    card *drawnCard = m_carddex.mopai();
    if (m_dangqianplayer->getmynum() == 1) {
        m_playerHand.append(drawnCard);
        m_dangqianplayer->fuzhicards(m_playerHand);
    }
    qWarning() << "当前玩家号" << m_dangqianplayer->getmynum();
    qWarning() << "摸排后我手牌数:" << m_playerHand.size();
    qWarning() << "摸排后当前手牌数:" << m_dangqianplayer->getcards().size();
    QVariantMap cardData;
    cardData["name"] = drawnCard->NewGetName();
    cardData["suit"] = drawnCard->getSuit();
    cardData["point"] = drawnCard->getPoint();
    cardData["type"] = drawnCard->getType();

    emit cardAdded(cardData);
    emit deckCountChanged(deckCount());

    //m_prevHand = m_playerHand; // 更新状态
    return drawnCard;
}

void GameManager::playCard(
    int handIndex)
{
    if (handIndex < 0 || handIndex >= m_playerHand.size()) {
        qWarning() << "Invalid hand index:" << handIndex;
        qWarning() << "shoupai:" << m_playerHand.size();
        return;
    }
    card *playedCard = m_playerHand.at(handIndex);
    m_dangqianplayer->playcard(handIndex, this);
    if (m_dangqianplayer->getmynum() == 1) {
        m_playerHand.removeAt(handIndex);
        qWarning() << "当前玩家的手牌数:" << m_dangqianplayer->getcards().size();
        qWarning() << "我的手牌数:" << m_playerHand.size();
        m_dangqianplayer->fuzhicards(m_playerHand);
        qWarning() << "当前玩家的手牌数:" << m_dangqianplayer->getcards().size();
    }
    QVariantMap cardData;
    cardData["name"] = playedCard->NewGetName();
    cardData["suit"] = playedCard->getSuit();
    cardData["point"] = playedCard->getPoint();
    cardData["type"] = playedCard->getType();

    moveCardToDiscard(playedCard);
    emit cardRemoved(handIndex);
    emit cardPlayed(cardData); // 发出卡牌使用信号，但卡牌尚未进入弃牌堆

    emit cardDiscarded(cardData);
    // 注意：这里不再立即将卡牌加入弃牌堆
    // 卡牌的具体处理（是否进入弃牌堆）由后续逻辑决定
}

void GameManager::discardCard(int handIndex) {
    if (handIndex < 0 || handIndex >= m_playerHand.size()) {
        qWarning() << "Invalid hand index:" << handIndex;
        return;
    }

    card *discardedCard = m_dangqianplayer->getcards().at(handIndex);
    //card *discardedCard = m_playerHand.at(handIndex);
    //m_playerHand.removeAt(handIndex);

    QVariantMap cardData;
    cardData["name"] = discardedCard->NewGetName();
    cardData["suit"] = discardedCard->getSuit();
    cardData["point"] = discardedCard->getPoint();
    cardData["type"] = discardedCard->getType();

    emit cardRemoved(handIndex);
    emit cardDiscarded(cardData);

    // 直接弃置的牌立即进入弃牌堆
    //moveCardToDiscard(cardData);  // 确保只有一次加入弃牌堆的操作
}
void GameManager::moveCardToDiscard(
    card *c)
{
    // card *c = new card(this);
    // c->setName(cardData["name"].toString());
    // c->setSuit(cardData["suit"].toString());
    // c->setPoint(cardData["point"].toInt());
    // c->setType(cardData["type"].toString());

    QVariantMap cardData;
    cardData["name"] = c->NewGetName();
    cardData["suit"] = c->getSuit();
    cardData["point"] = c->getPoint();
    cardData["type"] = c->getType();
    m_carddex.addToDiscardPile(c);
    emit cardMovedToDiscard(cardData);
    emit discardPileChanged(discardPileCount());
}
void GameManager::shuffleDeck()
{
    m_carddex.xipai();
    emit deckCountChanged(deckCount());
}

card *GameManager::panding()
{
    card *pandingpai = m_carddex.mopai();
    return pandingpai;
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

void GameManager::setplayers(
    player *p)
{
    m_player.push_back(p);
}

std::list<player *> GameManager::getplayers()
{
    return m_player;
}

void GameManager::setdangqianplayer(
    player *p)
{
    m_dangqianplayer = p;
}

player *GameManager::getdangqianplayer()
{
    return m_dangqianplayer;
}

Carddex *GameManager::getcarddex()
{
    return &m_carddex;
}

QList<card *> GameManager::gethandcards()
{
    return m_playerHand;
}

QVariantList GameManager::getHandCards() const
{
    QVariantList handCards;

    for (const card *c : m_playerHand) {
        QVariantMap cardData;
        cardData["name"] = c->NewGetName();
        cardData["suit"] = c->getSuit();
        cardData["point"] = c->getPoint();
        cardData["type"] = c->getType();
        handCards.append(cardData);
    }

    return handCards;
}

void GameManager::initHandCards()
{
    // 发送初始手牌信号
    for (const card *c : m_playerHand) {
        QVariantMap cardData;
        cardData["name"] = c->NewGetName();
        cardData["suit"] = c->getSuit();
        cardData["point"] = c->getPoint();
        cardData["type"] = c->getType();
        emit cardAdded(cardData);
    }
}
