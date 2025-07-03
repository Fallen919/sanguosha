#include "gamemanager.h"
#include <QDebug>
#include "player.h"
#include <QEventLoop>
#include <QTimer>
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
    p1->setjuli(this);
    p2->setjuli(this);
    p->setjuli(this);
    p->setwanjiashu(3);
    p1->setwanjiashu(3);
    p2->setwanjiashu(3);
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
            qWarning() << "当前玩家的手牌数:" << m_dangqianplayer->getcards().size();
        }

        QVariantMap cardData;
        cardData["name"] = playedCard->NewGetName();
        cardData["suit"] = playedCard->getSuit();
        cardData["point"] = playedCard->getPoint();
        cardData["type"] = playedCard->getType();
        emit cardRemoved(handIndex);
        emit cardPlayed(cardData); // 发出卡牌使用信号，但卡牌尚未进入弃牌堆
        emit cardDiscarded(cardData);
    }
}

void GameManager::discardCard(
    int handIndex)
{
    if (handIndex < 0 || handIndex >= m_playerHand.size()) {
        qWarning() << "Invalid hand index:" << handIndex;
        return;
    }

    card *discardedCard = m_dangqianplayer->getcards().at(handIndex);
    QVariantMap cardData;
    cardData["name"] = discardedCard->NewGetName();
    cardData["suit"] = discardedCard->getSuit();
    cardData["point"] = discardedCard->getPoint();
    cardData["type"] = discardedCard->getType();

    emit cardRemoved(handIndex);
    emit cardDiscarded(cardData);
}
void GameManager::moveCardToDiscard(
    card *c)
{
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

    // 修复1：添加索引范围检查
    if (playerIndex < 0 || playerIndex >= m_player.size()) {
        qWarning() << "无效玩家索引:" << playerIndex;
        return;
    }

    // 修复2：安全获取玩家指针
    auto it = m_player.begin();
    std::advance(it, playerIndex);

    if (it == m_player.end()) { // 新增边界检查
        qWarning() << "玩家迭代器越界";
        return;
    }

    player *t = *it;
    if (!t) { // 新增空指针检查
        qWarning() << "目标玩家为空";
        return;
    }

    // 修复3：统一使用当前玩家指针
    player *p = getdangqianplayer();
    if (!p) {
        qWarning() << "当前玩家为空";
        return;
    }

    card *playedCard = m_playerHand.at(m_selectedCardIndex);
    if (!playedCard) {
        qWarning() << "选择的卡牌为空";
        return;
    }

    // 修复4：移除冗余代码（响应处理已独立）
    bool success = playedCard->xiaoguo(p, t, this);
    if (success) {
        m_playerHand.removeAt(m_selectedCardIndex);
        emit cardRemoved(m_selectedCardIndex);

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

void GameManager::removecard(
    card *c)
{
    for (int i = 0; i < m_playerHand.size(); ++i) {
        if (m_playerHand[i] == c) {
            m_playerHand.removeAt(i);
            return;
        }
    }
    qWarning() << "要移除的卡牌不在玩家手牌中";
}

bool GameManager::waitForShanResponse(
    player *targetPlayer, card *sourceCard)
{
    qDebug() << "等待玩家" << targetPlayer->getPlayerIndex() << "响应闪";

    // 设置响应状态
    m_currentResponseType = ShanResponse;
    m_currentResponseCard = sourceCard;
    m_currentResponseTarget = targetPlayer;
    m_responseReceived = false;

    // 通知需要闪响应
    emit requireShanResponse(targetPlayer);

    // 创建事件循环等待响应
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);
    connect(this, &GameManager::responseReceived, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(15000); // 15秒超时

    loop.exec();

    // 重置响应状态
    m_currentResponseType = NoResponse;
    m_currentResponseCard = nullptr;
    m_currentResponseTarget = nullptr;

    return m_responseResult;
}

bool GameManager::waitForWuXiekejiResponse(
    card *sourceCard)
{
    qDebug() << "等待无懈可击响应";

    m_currentResponseType = WuXiekejiResponse;
    m_currentResponseCard = sourceCard;
    m_currentResponseTarget = nullptr;
    m_responseReceived = false;

    // 通知需要无懈可击响应
    emit requireWuXiekejiResponse(sourceCard);

    // 创建事件循环等待响应
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);
    connect(this, &GameManager::responseReceived, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(15000); // 15秒超时

    loop.exec();

    // 重置响应状态
    m_currentResponseType = NoResponse;
    m_currentResponseCard = nullptr;
    m_currentResponseTarget = nullptr;

    // 发出响应结束信号
    emit wuXiekejiResponseFinished();

    return m_responseResult;
}

void GameManager::respondToCard(
    card *responseCard, player *responder)
{
    if (!m_responseReceived) {
        qDebug() << "玩家" << responder->getPlayerIndex()
                 << "打出响应牌:" << responseCard->NewGetNameString();

        // 处理不同类型的响应
        switch (m_currentResponseType) {
        case ShanResponse:
            if (responseCard->getName() == card::Shan) {
                m_responseResult = true; // 闪响应成功
                m_responseReceived = true;

                // 将响应牌移动到弃牌堆
                int i = 0;
                for (i = 0; i < m_playerHand.size(); ++i) {
                    if (m_playerHand[i] == responseCard) {
                        return;
                    }
                }
                playCard(i);
                moveCardToDiscard(responseCard);
                responder->removeCard(responseCard);
                if (m_dangqianplayer->getmynum() == 1) {
                    m_playerHand.clear();
                    m_playerHand.append(m_dangqianplayer->getcards());
                }

                emit responseReceived(responseCard, responder);
            }
            break;

        case WuXiekejiResponse:
            if (responseCard->getName() == card::Wu_Xiekeji) {
                m_responseResult = true; // 无懈可击响应成功
                m_responseReceived = true;

                // 将响应牌移动到弃牌堆
                int k = 0;
                for (k = 0; k < m_playerHand.size(); ++k) {
                    if (m_playerHand[k] == responseCard) {
                        return;
                    }
                }
                playCard(k);
                moveCardToDiscard(responseCard);
                responder->removeCard(responseCard);
                if (m_dangqianplayer->getmynum() == 1) {
                    removecard(responseCard);
                    m_playerHand.clear();
                    m_playerHand.append(m_dangqianplayer->getcards());
                }

                // 无效化原始卡牌
                if (m_currentResponseCard) {
                    m_currentResponseCard->setInvalidated(true);
                }

                emit responseReceived(responseCard, responder);
            }
            break;

        default:
            qWarning() << "无效的响应类型";
            break;
        }
    } else {
        qWarning() << "响应已收到，忽略额外响应";
    }
}

void GameManager::playResponseCard(
    int cardIndex)
{
    if (cardIndex < 0 || cardIndex >= m_playerHand.size()) {
        qWarning() << "Invalid response card index:" << cardIndex;
        return;
    }

    card *responseCard = m_playerHand[cardIndex];
    player *responder = getdangqianplayer();

    respondToCard(responseCard, responder);
}
