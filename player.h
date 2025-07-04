#pragma once
#include <vector>
#include "cards.h"
#include "zhuangbeiqu.h"
#include <QList>
#include <QObject>
#include "judgearea.h"
#include "wujiang.h"
#include <QHash>
class GameManager;
class player : public QObject
{
    Q_OBJECT
public:
    explicit player(QObject *parent = nullptr);

    //玩家数
    Q_INVOKABLE void setwanjiashu(int num);
    Q_INVOKABLE int getwanjiashu();

    //玩家编号
    Q_INVOKABLE void setmynum(int num);
    Q_INVOKABLE int getmynum();

    //设置距离
    Q_INVOKABLE void setjuli(GameManager *g);
    Q_INVOKABLE int getjuli(player *p1, player *p2);

    //判定区
    Q_INVOKABLE void addjudg(card *c);
    Q_INVOKABLE judgearea *getjudg();

    //装备区
    Q_INVOKABLE void addwuqi(card *c);
    Q_INVOKABLE void addfangju(card *c);
    Q_INVOKABLE void addjinggongma(card *c);
    Q_INVOKABLE void addfangyuma(card *c);
    Q_INVOKABLE void removewuqi();
    Q_INVOKABLE void removefangju();
    Q_INVOKABLE void removejinggongma();
    Q_INVOKABLE void removefangyuma();
    Q_INVOKABLE zhuangbeiqu *getzhuangbei();

    //武将
    Q_INVOKABLE void setwujiang(wujiang *w);
    Q_INVOKABLE wujiang *getwujiang();

    //摸牌
    Q_INVOKABLE void mopai(int num, GameManager *g);
    Q_INVOKABLE QList<card *> getcards();

    //攻击距离
    Q_INVOKABLE void setgongjijuli();
    Q_INVOKABLE int getgongjijuli();

    //设置和获得手牌上线
    Q_INVOKABLE void setshoupaishangxian(int num);
    Q_INVOKABLE int getshoupaishangxian();

    //设置和获得体力值
    Q_INVOKABLE void settili(int num);
    Q_INVOKABLE int gettili();

    //判断是否活着
    Q_INVOKABLE bool isalive();

    //受到伤害
    Q_INVOKABLE bool shoudaoshanghai(int num, const QString shanghaileixing);

    //回血
    Q_INVOKABLE bool huixue(int num);

    //设置和获得体力上限
    Q_INVOKABLE void settilishangxian(int num);
    Q_INVOKABLE int gettilishangxian();

    //添加状态
    Q_INVOKABLE void addzhuangtai(const QString zhuangtai, int num);

    //是否包含某种状态
    Q_INVOKABLE bool isbaohan(const QString zhuangtai);

    //移除某种状态
    Q_INVOKABLE void yichuzhuangtai(const QString zhuangtai);

    //出牌
    Q_INVOKABLE bool playcard(int handIndex, GameManager *g);

    //清空手牌
    Q_INVOKABLE void clearcards();

    //手牌复制成
    Q_INVOKABLE void fuzhicards(QList<card *> cds);

    Q_INVOKABLE int getPlayerIndex() const;

    Q_INVOKABLE bool hasShan() const;
    Q_INVOKABLE bool hasWuXiekeji() const;
    Q_INVOKABLE void removeCard(card *cardToRemove);
    //顺手牵羊专用
      Q_INVOKABLE void addCard(card *cd);  // 添加卡牌到手牌

private:
    int m_wanjiashu;         //玩家数
    int m_mynum;             //玩家编号
    QList<card *> m_cards;   //手牌
    wujiang m_wujiang;       //武将
    judgearea m_judg;        //判定区
    zhuangbeiqu m_zhuangbei; //装备区
    std::vector<int> m_juli; //与其他玩家的距离
    int m_gongjijuli;        //攻击范围
    int m_tili;              //体力
    int m_tilishangxian;     //体力上线
    int m_shoupaishu;        //手牌数
    int m_shoupaishangxian;  //手牌上线
    QHash<QString, int> m_zhuangtai; //玩家的状态


signals:
    void playerselced(player *p);
    void shoudaoshanghai(int num);         //受到伤害时发出信号
    void huifuxueliang(int num);           //回血时发出信号
    void jinrubinsi();                     //进入濒死阶段时发出信号
    void addzt(const QString zhuangtai);   //添加状态时发出信号
    void yichuzt(const QString zhuangtai); //移除状态时发出信号
};
