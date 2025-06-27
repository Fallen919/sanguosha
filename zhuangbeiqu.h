#pragma once
#include "card.h"
#include <QObject>

class zhuangbeiqu : public QObject
{
    Q_OBJECT
public:
    explicit zhuangbeiqu(QObject *parent = nullptr);

    Q_INVOKABLE void addwuqi(card *wq);
    Q_INVOKABLE QList<card *> getwuqi();

    Q_INVOKABLE void addfangju(card *fj);
    Q_INVOKABLE QList<card *> getfangju();

    Q_INVOKABLE void addjinggongma(card *jgm);
    Q_INVOKABLE QList<card *> getjinggongma();

    Q_INVOKABLE void addfangyuma(card *fym);
    Q_INVOKABLE QList<card *> getfangyuma();

private:
    QList<card *> m_wuqi;
    QList<card *> m_fangju;
    QList<card *> m_jinggongma;
    QList<card *> m_fangyuma;

signals:
};
