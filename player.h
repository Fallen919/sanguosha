#pragma once
#include <vector>
#include "cards.h"
#include "zhuangbeiqu.h"
#include <QList>
#include <QObject>
#include "judgearea.h"
#include "wujiang.h"
class GameManager;
class player : public QObject
{
    Q_OBJECT
public:
    explicit player(QObject *parent = nullptr);

    Q_INVOKABLE void setwanjiashu(int num);
    Q_INVOKABLE int getwanjiashu();

    Q_INVOKABLE void setmynum(int num);
    Q_INVOKABLE int getmynum();

    Q_INVOKABLE void setjuli(GameManager *g);

    Q_INVOKABLE void setjudg(judgearea *j);
    Q_INVOKABLE judgearea *getjudg();

    Q_INVOKABLE void setzhuangbei(zhuangbeiqu *z);
    Q_INVOKABLE zhuangbeiqu *getzhuangbei();

    Q_INVOKABLE void setwujiang(wujiang *w);
    Q_INVOKABLE wujiang *getwujiang();

    Q_INVOKABLE void mopai(int num, GameManager *g);
    Q_INVOKABLE QList<card> getcards();

    Q_INVOKABLE void setgongjijuli();
    Q_INVOKABLE int getgongjijuli();

    Q_INVOKABLE void playcard(int handIndex, GameManager *g);

private:
    int m_wanjiashu;
    int m_mynum;
    QList<card> m_cards;
    wujiang m_wujiang;
    judgearea m_judg;
    zhuangbeiqu m_zhuangbei;
    std::vector<int> m_juli;
    int m_gongjijuli;

signals:
    void playerselced(player *p);
};
