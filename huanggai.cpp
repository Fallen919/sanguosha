#include "huanggai.h"
#include "gamejieduan.h"
#include "gamemanager.h"
huanggai::huanggai()
    : m_wujiangming{"黄盖"}
    , m_tili{4}
    , m_tilishangxian{4}
    , m_shili{wujiang::Wu}
    , m_shoupaishangxian{4}
    , m_xingbie{wujiang::Nan}
{
    int i = 0;
}

void huanggai::jineng1(
    QObject *playerObj, QObject *gameManagerObj)
{
    // QObject *playerObj, QObject *gameManagerObj;
    player *p = qobject_cast<player *>(playerObj);
    GameManager *g = qobject_cast<GameManager *>(gameManagerObj);
    if (!p || !g) {
        qWarning() << "无效的玩家或游戏";
        return;
    }

    qDebug() << "发动苦肉技能";
    p->settili(p->gettili() - 1);
    p->mopai(2, g);
    emit p->playerHealthChanged(p->gettili());
    emit kurouUsed();
}

void huanggai::jineng2()
{
    int i = 0;
}

void huanggai::jineng3()
{
    int i = 0;
}

void huanggai::executeZhiheng(
    QList<card *> cardsToDiscard, QObject *g)
{}

huanggai::~huanggai()
{
    int i = 0;
}
