#include "zhuangbeiqu.h"

zhuangbeiqu::zhuangbeiqu(
    QObject *parent)
    : QObject{parent}
{}

void zhuangbeiqu::addwuqi(
    card *wq)
{
    m_wuqi.append(wq);
}

QList<card *> zhuangbeiqu::getwuqi()
{
    return m_wuqi;
}

void zhuangbeiqu::addfangju(
    card *fj)
{
    m_fangju.append(fj);
}

QList<card *> zhuangbeiqu::getfangju()
{
    return m_fangju;
}

void zhuangbeiqu::addjinggongma(
    card *jgm)
{
    m_jinggongma.append(jgm);
}

QList<card *> zhuangbeiqu::getjinggongma()
{
    return m_jinggongma;
}

void zhuangbeiqu::addfangyuma(
    card *fym)
{
    m_fangyuma.append(fym);
}

QList<card *> zhuangbeiqu::getfangyuma()
{
    return m_fangyuma;
}
