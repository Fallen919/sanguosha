#pragma once
#include <vector>
#include "cards.h"
#include "zhuangbeiqu.h"
#include <list>
#include <QObject>
#include "judgearea.h"
class player : public QObject
{
    Q_OBJECT
public:
    explicit player(QObject *parent = nullptr);

    Q_INVOKABLE void setwanjiashu(int num);
    Q_INVOKABLE int getwanjiashu();

    Q_INVOKABLE void setmynum(int num);
    Q_INVOKABLE int getmynum();

    Q_INVOKABLE void setplayer(player *p);

    Q_INVOKABLE void setjuli();

    Q_INVOKABLE void setjudg(judgearea *j);
    Q_INVOKABLE judgearea *getjudg();

    Q_INVOKABLE void setzhuangbei(zhuangbeiqu *z);
    Q_INVOKABLE zhuangbeiqu *getzhuangbei();

    Q_INVOKABLE void setwanjia(player *p);
    Q_INVOKABLE std::list<player *> getwanjia();

    Q_INVOKABLE void setcards(cards *c);
    Q_INVOKABLE cards *getcards();

private:
    int m_wanjiashu;
    int m_mynum;
    cards m_cards;
    judgearea m_judg;
    zhuangbeiqu m_zhuangbei;
    std::vector<int> m_juli;
    std::list<player *> wanjia;

signals:
};
