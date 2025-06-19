#pragma once
#include "card.h"
#include <QObject>

class zhuangbeiqu : public QObject
{
    Q_OBJECT
public:
    explicit zhuangbeiqu(QObject *parent = nullptr);

    Q_INVOKABLE void setwuqi(card wq);
    Q_INVOKABLE card getwuqi();

    Q_INVOKABLE void setfangju(card fj);
    Q_INVOKABLE card getfangju();

    Q_INVOKABLE void setjinggongma(card jgm);
    Q_INVOKABLE card getjinggongma();

    Q_INVOKABLE void setfangyuma(card fym);
    Q_INVOKABLE card getfangyuma();

private:
    card m_wuqi;
    card m_fangju;
    card m_jingongma;
    card m_fangyuma;

signals:
};
