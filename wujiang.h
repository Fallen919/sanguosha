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

    Q_INVOKABLE void settili(int num);
    Q_INVOKABLE int gettili();

    Q_INVOKABLE void settilishangxian(int num);
    Q_INVOKABLE int gettilishangxian();

    Q_INVOKABLE void setshoupaishu(int sp);
    Q_INVOKABLE int getshoupaishu();

    Q_INVOKABLE void setshoupaishangxian(int num);
    Q_INVOKABLE int getshoupaishangxian();

    Q_INVOKABLE void setwujiangshili(WujiangShili sl);
    Q_INVOKABLE WujiangShili getwujiangshili();

    Q_INVOKABLE void setxingbie(Xingbie xb);
    Q_INVOKABLE Xingbie getxingbie();

    Q_INVOKABLE void setwujiangming(std::string wjm);
    Q_INVOKABLE std::string getwujiangming();

    Q_INVOKABLE void virtual jineng1();

    Q_INVOKABLE void virtual jineng2();

    Q_INVOKABLE void virtual jineng3();

protected:
    std::string m_wujiangming;
    int m_tili;
    int m_tilishangxian;
    int m_shoupaishu;
    int m_shoupaishangxian;
    WujiangShili m_shili;
    Xingbie m_xingbie;

signals:
};
