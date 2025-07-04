#pragma once
#include "player.h"
#include <QObject>
#include "carddex.h"
#include "judgearea.h"
#include "cards.h"
class GameManager;
class gamejieduan : public QObject
{
    Q_OBJECT
public:
    explicit gamejieduan(QObject *parent = nullptr);

    enum Jieduan {
        JieduanBegin,
        Zhunbeijieduan,
        Pandingjieduan,
        Mopaijieduan,
        Chupaijieduan,
        Qipaijieduan,
        Jieshujieduan,
    };

    // Q_INVOKABLE void gamestart(player *p, Carddex *paidui);

    Q_INVOKABLE void setjieduan(Jieduan j);
    Q_INVOKABLE Jieduan getjieduan();

    //准备阶段
    Q_INVOKABLE void zhunbeijieduan(player *p, GameManager *g);

    //判定阶段
    Q_INVOKABLE void pandingjieduan(player *p, GameManager *g);

    //摸牌阶段
    Q_INVOKABLE void mopaijieduan(player *p, GameManager *g);

    //出牌阶段
    Q_INVOKABLE void chupaijieduan(player *p, GameManager *g);

    //弃牌阶段
    Q_INVOKABLE void qipaijieduan(player *p, GameManager *g);

    //结束阶段
    Q_INVOKABLE void jieshujieduan(player *p, GameManager *g);

    //玩家回合结束
    Q_INVOKABLE void huihejieshu(player *p, GameManager *g);

    //一回合
    Q_INVOKABLE void yihuihe(player *p, GameManager *g);

    //一轮
    Q_INVOKABLE void yilun(player *p, GameManager *g);

private:
    Jieduan m_jieduan;

signals:
};
