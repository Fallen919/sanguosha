#include "gamemanager.h"
#include <QDebug>
#include "player.h"
GameManager::GameManager(
    QObject *parent)
    : QObject(parent)
{
    m_carddex.xipai();
    player *p = new player(this);
    player *p1 = new player(this);
    player *p2 = new player(this);
    GameManager::setplayers(p);
    GameManager::setplayers(p1);
    GameManager::setplayers(p2);
    p->settili(4);
    p->settilishangxian(4);
    p1->settili(4);
    p1->settilishangxian(4);
    p2->settili(4);
    p2->settilishangxian(4);
    p->setmynum(1);
    p1->setmynum(2);
    p2->setmynum(3);
    std::list<player *>::iterator it = m_player.begin();
    for (int i = 0; i < 3; ++i, ++it) {
        m_dangqianplayer = *it;
        (*it)->mopai(4, this);
    }
    m_dangqianplayer = p;
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
    //emit handCardsReset();
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
    // 检查卡牌是否需要选择目标
    if (playedCard->requiresTarget()) {
        m_selectedCardIndex = handIndex;
        m_isSelectingTarget = true;
        emit targetSelectionStarted(handIndex);
        emit isSelectingTargetChanged(true);
        return; // 不立即出牌，等待目标选择
    }
    if (m_dangqianplayer->playcard(handIndex, this)) {
        if (m_dangqianplayer->getmynum() == 1) {
            qWarning() << "当前玩家的手牌数:" << m_dangqianplayer->getcards().size();
            qWarning() << "我的手牌数:" << m_playerHand.size();
            m_playerHand.clear();
            m_playerHand.append(m_dangqianplayer->getcards());
            //emit handCardsReset();
            //m_dangqianplayer->fuzhicards(m_playerHand);
            qWarning() << "当前玩家的手牌数:" << m_dangqianplayer->getcards().size();
        }

        QVariantMap cardData;
        cardData["name"] = playedCard->NewGetName();
        cardData["suit"] = playedCard->getSuit();
        cardData["point"] = playedCard->getPoint();
        cardData["type"] = playedCard->getType();
        //emit handCardsReset();
        emit cardRemoved(handIndex);
        emit cardPlayed(cardData); // 发出卡牌使用信号，但卡牌尚未进入弃牌堆

        emit cardDiscarded(cardData);
    }
    // 注意：这里不再立即将卡牌加入弃牌堆
    // 卡牌的具体处理（是否进入弃牌堆）由后续逻辑决定
}

void GameManager::discardCard(
    int handIndex)
{
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

    //emit handCardsReset();
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
int GameManager::discardPileCount() const
{
    return m_carddex.discardCount();
}
//弃牌堆顶
QVariantMap GameManager::getTopDiscardCard()
{
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

void GameManager::selectTargetPlayer(
    int playerIndex)
{
    if (!m_isSelectingTarget || m_selectedCardIndex < 0) {
        qWarning() << "不在目标选择模式";
        return;
    }

    if (playerIndex < 0 || playerIndex >= m_player.size()) {
        qWarning() << "无效玩家索引:" << playerIndex;
        return;
    }

    // 获取目标玩家 - 安全方式
    auto it = m_player.begin();
    std::advance(it, playerIndex);

    if (it == m_player.end()) {
        qWarning() << "玩家迭代器越界";
        return;
    }

    player *t = *it;
    if (!t) {
        qWarning() << "目标玩家为空";
        return;
    }

    // 获取当前玩家
    player *p = getdangqianplayer();
    if (!p) {
        qWarning() << "当前玩家为空";
        return;
    }

    // 获取卡牌
    card *playedCard = m_playerHand.at(m_selectedCardIndex);
    if (!playedCard) {
        qWarning() << "选择的卡牌为空";
        return;
    }

    // 执行卡牌效果
    bool success = playedCard->xiaoguo(p, t, this);

    if (success) {
        // 移除手牌
        m_playerHand.removeAt(m_selectedCardIndex);
        emit cardRemoved(m_selectedCardIndex);

        // 移动卡牌到弃牌堆（如果不是装备牌或延时锦囊）
        if (playedCard->getTypeString() != "Zhuang_Bei"
            && playedCard->NewGetNameString() != "Shan_Dian"
            && playedCard->NewGetNameString() != "Le_Busishu"
            && playedCard->NewGetNameString() != "Bing_Niangchunduan") {
            moveCardToDiscard(playedCard);
        }
    }

    // 重置状态
    m_isSelectingTarget = false;
    m_selectedCardIndex = -1;
    emit isSelectingTargetChanged(false);
    emit cardPlayedWithTarget(m_selectedCardIndex, playerIndex);
}

void GameManager::cancelTargetSelection()
{
    m_isSelectingTarget = false;
    m_selectedCardIndex = -1;
    emit isSelectingTargetChanged(false);
    emit targetSelectionCanceled();
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

bool GameManager::requiresTarget(
    int handIndex)
{
    if (handIndex < 0 || handIndex >= m_playerHand.size()) {
        return false;
    }
    return m_playerHand.at(handIndex)->requiresTarget();
}

void GameManager::startTargetSelection(
    int cardIndex)
{
    m_selectedCardIndex = cardIndex;
    m_isSelectingTarget = true;
    emit targetSelectionStarted(cardIndex);
    emit isSelectingTargetChanged(true);
}
