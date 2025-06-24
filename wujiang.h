#pragma once

#include <QObject>

class wujiang : public QObject
{
    Q_OBJECT
public:
    explicit wujiang(QObject *parent = nullptr);

    enum WujiangShili {
        WjBegin,
        Wei,
        Shu,
        Wu,
        Qun,
        WjEnd,
    };

    enum Xingbie {
        XingbieBegin,
        Nan,
        Nv,
        XingbieEnd,
    };

    //设置和获得体力值
    Q_INVOKABLE void settili(int num);
    Q_INVOKABLE int gettili();

    //设置和获得体力上限
    Q_INVOKABLE void settilishangxian(int num);
    Q_INVOKABLE int gettilishangxian();

    //设置和获得手牌数
    Q_INVOKABLE void setshoupaishu(int sp);
    Q_INVOKABLE int getshoupaishu();

    //设置和获得手牌上线
    Q_INVOKABLE void setshoupaishangxian(int num);
    Q_INVOKABLE int getshoupaishangxian();

    //武将势力
    Q_INVOKABLE void setwujiangshili(WujiangShili sl);
    Q_INVOKABLE WujiangShili getwujiangshili();

    //武将性别
    Q_INVOKABLE void setxingbie(Xingbie xb);
    Q_INVOKABLE Xingbie getxingbie();

    //武将名字
    Q_INVOKABLE void setwujiangming(std::string wjm);
    Q_INVOKABLE std::string getwujiangming();

    //技能
    Q_INVOKABLE void virtual jineng1();

    Q_INVOKABLE void virtual jineng2();

    Q_INVOKABLE void virtual jineng3();

protected:
    std::string m_wujiangming; //武将名
    int m_tili;                //体力
    int m_tilishangxian;       //体力上限
    int m_shoupaishu;          //手牌数
    int m_shoupaishangxian;    //手牌上线
    WujiangShili m_shili;      //势力
    Xingbie m_xingbie;         //性别

signals:
};
