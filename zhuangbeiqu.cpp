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

void zhuangbeiqu::removewuqi()
{
    m_wuqi.clear();
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

void zhuangbeiqu::removefangju()
{
    m_fangju.clear();
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

void zhuangbeiqu::removejinggongma()
{
    m_jinggongma.clear();
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

void zhuangbeiqu::removefangyuma()
{
    m_fangyuma.clear();
}

QList<card *> zhuangbeiqu::getfangyuma()
{
    return m_fangyuma;
}
