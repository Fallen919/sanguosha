#include "daweiwuwang.h"
#include "gamemanager.h"
daweiwuwang::daweiwuwang()
    : m_wujiangming{"大魏吴王"}
    , m_tili{4}
    , m_tilishangxian{4}
    , m_shili{wujiang::Wei}
    , m_shoupaishangxian{4}
    , m_xingbie{wujiang::Nan}
    , is_usejineng1{false}
    , ji_neng_shengyushu{1}
{}

void daweiwuwang::jineng1(
    player *p, QObject *gObj)
{
    GameManager *g = qobject_cast<GameManager *>(gObj); // 类型转换
    if (!g)
        return;
    if (ji_neng_shengyushu > 0 && p->isbaohan("Chu_Pai_Jie_Duan")) {
        // 制衡：弃置任意张牌，然后摸等量的牌
        is_usejineng1 = true;
        ji_neng_shengyushu--;
        // 通知UI进入制衡模式
        emit zhihengUsed();
        qDebug() << "大魏吴王发动技能【制衡】";
    }
}

void daweiwuwang::jineng2()
{
    int i = 0;
}

void daweiwuwang::jineng3()
{
    int i = 0;
}

void daweiwuwang::executeZhiheng(
    QList<card *> cardsToDiscard, QObject *gObj)
{
    qWarning() << "制衡";
    GameManager *g = qobject_cast<GameManager *>(gObj); // 类型转换
    // 从GameManager获取当前玩家
    player *currentPlayer = g->getdangqianplayer();
    if (!currentPlayer) {
        qWarning() << "制衡: 无效的玩家";
        return;
    }

    int discardCount = cardsToDiscard.size();

    // 弃置选中的牌
    for (card *c : cardsToDiscard) {
        // 从玩家手牌中移除
        qDebug() << "手牌剩余:" << currentPlayer->getcards().size();
        currentPlayer->removeCard(c);

        // 从GameManager的手牌列表中移除（仅对玩家1）
        if (currentPlayer->getmynum() == 1) {
            g->removeCard(c);
        }

        // 移动到弃牌堆
        g->moveCardToDiscard(c);
    }
    qDebug() << "手牌剩余:" << currentPlayer->getcards().size();

    // 摸等量的牌
    if (discardCount > 0 && currentPlayer->getcards().size() != 0) {
        currentPlayer->mopai(discardCount, g);
        emit cardsDiscardedForZhiheng(discardCount);
        qDebug() << "制衡: 弃置" << discardCount << "张牌，摸" << discardCount << "张牌";
    }
    //多模一张
    if (discardCount > 0 && currentPlayer->getcards().size() == 0) {
        currentPlayer->mopai(discardCount + 1, g);
        emit cardsDiscardedForZhiheng(discardCount);
        qDebug() << "制衡: 弃置" << discardCount << "张牌，摸" << discardCount + 1 << "张牌";
    }

    // 重置状态
    is_usejineng1 = false;
    ji_neng_shengyushu--;
}
