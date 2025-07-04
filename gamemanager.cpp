#include "gamemanager.h"
#include <QDebug>
#include "player.h"
#include <QEventLoop>
#include <QTimer>

GameManager::GameManager(QObject *parent)
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

    // 连接玩家信号
    connectPlayerSignals(p);
    connectPlayerSignals(p1);
    connectPlayerSignals(p2);

    std::list<player *>::iterator it = m_player.begin();
    for (int i = 0; i < 3; ++i, ++it) {
        m_dangqianplayer = *it;
        (*it)->mopai(4, this);
    }
    m_dangqianplayer = p;

    // 发送初始玩家信息
    emitAllPlayersInfo();
}

// 连接玩家信号到游戏管理器
void GameManager::connectPlayerSignals(player *p)
{
    connect(p, SIGNAL(shoudaoshanghai(int)), this, SLOT(onPlayerDamaged(int)));
    connect(p, SIGNAL(huifuxueliang(int)), this, SLOT(onPlayerHealed(int)));
    connect(p, SIGNAL(jinrubinsi()), this, SLOT(onPlayerDying()));
    connect(p, SIGNAL(addzt(QString)), this, SLOT(onPlayerStatusAdded(QString)));
    connect(p, SIGNAL(yichuzt(QString)), this, SLOT(onPlayerStatusRemoved(QString)));
}
// 获取单个玩家信息
QVariantMap GameManager::getPlayerInfo(int playerIndex)
{
    QVariantMap playerInfo;

    auto it = m_player.begin();
    std::advance(it, playerIndex);

    if (it != m_player.end()) {
        player *p = *it;
        playerInfo["index"] = p->getmynum() - 1; // QML中使用0-based索引
        playerInfo["name"] = QString("Player %1").arg(p->getmynum());
        playerInfo["health"] = p->gettili();
        playerInfo["maxHealth"] = p->gettilishangxian();
        playerInfo["isAlive"] = p->isalive();
        playerInfo["handCount"] = p->getcards().size();
    }

    return playerInfo;
}

// 获取所有玩家信息
QVariantList GameManager::getAllPlayersInfo()
{
    QVariantList playersInfo;

    for (auto it = m_player.begin(); it != m_player.end(); ++it) {
        player *p = *it;
        QVariantMap playerInfo;
        playerInfo["index"] = p->getmynum() - 1; // QML中使用0-based索引
        playerInfo["name"] = QString("Player %1").arg(p->getmynum());
        playerInfo["health"] = p->gettili();
        playerInfo["maxHealth"] = p->gettilishangxian();
        playerInfo["isAlive"] = p->isalive();
        playerInfo["handCount"] = p->getcards().size();
        playersInfo.append(playerInfo);
    }

    return playersInfo;
}

// 获取玩家血量
int GameManager::getPlayerHealth(int playerIndex)
{
    auto it = m_player.begin();
    std::advance(it, playerIndex);

    if (it != m_player.end()) {
        return (*it)->gettili();
    }
    return 0;
}

// 获取玩家最大血量
int GameManager::getPlayerMaxHealth(int playerIndex)
{
    auto it = m_player.begin();
    std::advance(it, playerIndex);

    if (it != m_player.end()) {
        return (*it)->gettilishangxian();
    }
    return 0;
}

// 获取玩家名称
QString GameManager::getPlayerName(int playerIndex)
{
    auto it = m_player.begin();
    std::advance(it, playerIndex);

    if (it != m_player.end()) {
        return QString("Player %1").arg((*it)->getmynum());
    }
    return "Unknown";
}

// 测试方法：对玩家造成伤害
void GameManager::testDamagePlayer(int playerIndex, int damage)
{
    auto it = m_player.begin();
    std::advance(it, playerIndex);

    if (it != m_player.end()) {
        player *p = *it;
        p->shoudaoshanghai(damage, "Pu_Tong");
        qDebug() << "测试：对玩家" << playerIndex << "造成" << damage << "点伤害";
    }
}

// 测试方法：为玩家回复血量
void GameManager::testHealPlayer(int playerIndex, int healAmount)
{
    auto it = m_player.begin();
    std::advance(it, playerIndex);

    if (it != m_player.end()) {
        player *p = *it;
        p->huixue(healAmount);
        qDebug() << "测试：为玩家" << playerIndex << "回复" << healAmount << "点血量";
    }
}

// 处理玩家受到伤害
void GameManager::onPlayerDamaged(int damage)
{
    player *p = qobject_cast<player*>(sender());
    if (p) {
        int playerIndex = p->getmynum() - 1; // 转换为0-based索引
        emit playerDamaged(playerIndex, damage);
        emit playerHealthChanged(playerIndex, p->gettili(), p->gettilishangxian());
        emitAllPlayersInfo();

        qDebug() << "玩家" << playerIndex << "受到" << damage << "点伤害，剩余血量:" << p->gettili();
    }
}

// 处理玩家回血
void GameManager::onPlayerHealed(int healAmount)
{
    player *p = qobject_cast<player*>(sender());
    if (p) {
        int playerIndex = p->getmynum() - 1;
        emit playerHealed(playerIndex, healAmount);
        emit playerHealthChanged(playerIndex, p->gettili(), p->gettilishangxian());
        emitAllPlayersInfo();

        qDebug() << "玩家" << playerIndex << "回复" << healAmount << "点血量，当前血量:" << p->gettili();
    }
}

// 处理玩家濒死
void GameManager::onPlayerDying()
{
    player *p = qobject_cast<player*>(sender());
    if (p) {
        int playerIndex = p->getmynum() - 1;
        emit playerDying(playerIndex);
        emitAllPlayersInfo();

        qDebug() << "玩家" << playerIndex << "进入濒死状态";
    }
}

// 处理玩家状态添加
void GameManager::onPlayerStatusAdded(const QString &status)
{
    player *p = qobject_cast<player*>(sender());
    if (p) {
        int playerIndex = p->getmynum() - 1;
        emit playerStatusChanged(playerIndex, status, true);
        emitAllPlayersInfo();

        qDebug() << "玩家" << playerIndex << "添加状态:" << status;
    }
}

// 处理玩家状态移除
void GameManager::onPlayerStatusRemoved(const QString &status)
{
    player *p = qobject_cast<player*>(sender());
    if (p) {
        int playerIndex = p->getmynum() - 1;
        emit playerStatusChanged(playerIndex, status, false);
        emitAllPlayersInfo();

        qDebug() << "玩家" << playerIndex << "移除状态:" << status;
    }
}

// 发送所有玩家信息更新信号
void GameManager::emitAllPlayersInfo()
{
    emit allPlayersInfoChanged(getAllPlayersInfo());
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
    return drawnCard;
}

void GameManager::playCard(int handIndex)
{
    if (handIndex < 0 || handIndex >= m_playerHand.size()) {
        qWarning() << "Invalid hand index:" << handIndex;
        return;
    }

    card *playedCard = m_playerHand.at(handIndex);

    if (playedCard->requiresTarget()) {
        m_selectedCardIndex = handIndex;
        m_isSelectingTarget = true;
        emit targetSelectionStarted(handIndex);
        emit isSelectingTargetChanged(true);
        return;
    }

    if (m_dangqianplayer->playcard(handIndex, this)) {
        // 统一处理卡牌移除逻辑
        QVariantMap cardData;
        cardData["name"] = playedCard->NewGetName();
        cardData["suit"] = playedCard->getSuit();
        cardData["point"] = playedCard->getPoint();
        cardData["type"] = playedCard->getType();

        // 直接从手牌列表移除
        m_playerHand.removeAt(handIndex);
        emit cardRemoved(handIndex);
        emit cardPlayed(cardData);

        // 特殊卡牌不进弃牌堆
        const bool isSpecialCard = playedCard->getTypeString() == "Zhuang_Bei"
                                   || playedCard->NewGetNameString() == "Shan_Dian"
                                   || playedCard->NewGetNameString() == "Le_Busishu"
                                   || playedCard->NewGetNameString() == "Bing_Niangchunduan";

        if (!isSpecialCard) {
            moveCardToDiscard(playedCard);
        }
    }
}

void GameManager::discardCard(int handIndex)
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
    m_playerHand.removeAt(handIndex);
    if (m_dangqianplayer->getmynum() == 1)
        m_dangqianplayer->removeCard(discardedCard);
    emit cardRemoved(handIndex);
    emit cardDiscarded(cardData);
}

void GameManager::moveCardToDiscard(card *c)
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

int GameManager::deckCount() const
{
    return m_carddex.count();
}

int GameManager::discardPileCount() const
{
    return m_carddex.discardCount();
}

QVariantMap GameManager::getTopDiscardCard()
{
    return m_carddex.getTopDiscardCard();
}

void GameManager::setplayers(player *p)
{
    m_player.push_back(p);
}

std::list<player *> GameManager::getplayers()
{
    return m_player;
}

void GameManager::setdangqianplayer(player *p)
{
    m_dangqianplayer = p;
}

player *GameManager::getdangqianplayer()
{
    return m_dangqianplayer;
}

void GameManager::selectTargetPlayer(int playerIndex)
{
    if (!m_isSelectingTarget || m_selectedCardIndex < 0)
        return;
    if (playerIndex < 0 || playerIndex >= m_player.size())
        return;

    auto it = m_player.begin();
    std::advance(it, playerIndex);
    player *targetPlayer = *it;
    card *playedCard = m_playerHand.at(m_selectedCardIndex);
    bool success = playedCard->xiaoguo(getdangqianplayer(), targetPlayer, this);

    if (success) {
        QVariantMap cardData;
        cardData["name"] = playedCard->NewGetName();
        cardData["suit"] = playedCard->getSuit();
        cardData["point"] = playedCard->getPoint();
        cardData["type"] = playedCard->getType();

        // 直接从手牌列表移除
        m_playerHand.removeAt(m_selectedCardIndex);
        emit cardRemoved(m_selectedCardIndex);
        emit cardPlayed(cardData);

        // 特殊卡牌不进弃牌堆
        const bool isSpecialCard = playedCard->getTypeString() == "Zhuang_Bei"
                                   || playedCard->NewGetNameString() == "Shan_Dian"
                                   || playedCard->NewGetNameString() == "Le_Busishu"
                                   || playedCard->NewGetNameString() == "Bing_Niangchunduan";

        if (!isSpecialCard) {
            moveCardToDiscard(playedCard);
        }
    }

    // 重置状态
    m_isSelectingTarget = false;
    m_selectedCardIndex = -1;
    emit isSelectingTargetChanged(false);
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

bool GameManager::requiresTarget(int handIndex)
{
    if (handIndex < 0 || handIndex >= m_playerHand.size()) {
        return false;
    }
    return m_playerHand.at(handIndex)->requiresTarget();
}

void GameManager::startTargetSelection(int cardIndex)
{
    m_selectedCardIndex = cardIndex;
    m_isSelectingTarget = true;
    emit targetSelectionStarted(cardIndex);
    emit isSelectingTargetChanged(true);
}

void GameManager::removecard(card *c)
{
    for (int i = 0; i < m_playerHand.size(); ++i) {
        if (m_playerHand[i] == c) {
            QVariantMap cardData;
            cardData["name"] = m_playerHand[i]->NewGetName();
            cardData["suit"] = m_playerHand[i]->getSuit();
            cardData["point"] = m_playerHand[i]->getPoint();
            cardData["type"] = m_playerHand[i]->getType();
            emit cardRemoved(i);
            emit cardPlayed(cardData);
            emit cardDiscarded(cardData);
            m_playerHand.removeAt(i);
            return;
        }
    }
}

bool GameManager::waitForShanResponse(player *targetPlayer, card *sourceCard)
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
    connect(this, &GameManager::cancelResponseCalled, &loop, &QEventLoop::quit);
    timer.start(15000); // 15秒超时
    loop.exec();

    // 重置响应状态
    m_currentResponseType = NoResponse;
    m_currentResponseCard = nullptr;
    m_currentResponseTarget = nullptr;

    return m_responseResult;
}

bool GameManager::waitForWuXiekejiResponse(card *sourceCard)
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
    connect(this, &GameManager::cancelResponseCalled, &loop, &QEventLoop::quit);
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

void GameManager::respondToCard(card *responseCard, player *responder)
{
    if (!m_responseReceived) {
        qDebug() << "玩家" << responder->getPlayerIndex()
            << "打出响应牌:" << responseCard->NewGetNameString();

        // 处理不同类型的响应
        switch (m_currentResponseType) {
        case ShanResponse:
            if (responseCard->getName() == card::Shan) {
                m_responseResult = true;
                m_responseReceived = true;

                // 从手牌中移除响应牌
                int index = m_playerHand.indexOf(responseCard);
                if (index != -1) {
                    m_playerHand.removeAt(index);
                    emit cardRemoved(index);
                }

                // 移动到弃牌堆
                moveCardToDiscard(responseCard);
                responder->removeCard(responseCard);

                // 同步玩家1手牌
                if (m_dangqianplayer->getmynum() == 1) {
                    m_playerHand = m_dangqianplayer->getcards();
                }

                emit responseReceived(responseCard, responder);
            }
            break;

        case WuXiekejiResponse:
            if (responseCard->getName() == card::Wu_Xiekeji) {
                m_responseResult = true;
                m_responseReceived = true;

                // 从手牌中移除响应牌
                int index = m_playerHand.indexOf(responseCard);
                if (index != -1) {
                    m_playerHand.removeAt(index);
                    emit cardRemoved(index);
                }

                // 移动到弃牌堆
                moveCardToDiscard(responseCard);
                responder->removeCard(responseCard);

                // 同步玩家1手牌
                if (m_dangqianplayer->getmynum() == 1) {
                    m_playerHand = m_dangqianplayer->getcards();
                }

                // 无效化原始卡牌
                if (m_currentResponseCard) {
                    m_currentResponseCard->setInvalidated(true);
                }

                emit responseReceived(responseCard, responder);
            }
            break;
        }
    }
}

void GameManager::playResponseCard(int cardIndex)
{
    if (cardIndex < 0 || cardIndex >= m_playerHand.size()) {
        qWarning() << "Invalid response card index:" << cardIndex;
        return;
    }

    card *responseCard = m_playerHand[cardIndex];
    player *responder = getdangqianplayer();

    respondToCard(responseCard, responder);
}

void GameManager::cancelResponse()
{
    if (!m_responseReceived) {
        qDebug() << "取消响应";
        m_responseResult = false;
        m_responseReceived = true;
        emit responseReceived(nullptr, nullptr);
        emit cancelResponseCalled();
    }
}
