#include "zhuangbeiqu.h"

zhuangbeiqu::zhuangbeiqu(
    QObject *parent)
    : QObject{parent}
{}

void zhuangbeiqu::setwuqi(
    card *wq)
{
    m_wuqi->setName(wq->getName());
    m_wuqi->setSuit(wq->getSuit());
    m_wuqi->setPoint(wq->getPoint());
    m_wuqi->setType(wq->getType());
}

card *zhuangbeiqu::getwuqi()
{
    return m_wuqi;
}

void zhuangbeiqu::setfangju(
    card *fj)
{
    m_fangju->setName(fj->getName());
    m_fangju->setSuit(fj->getSuit());
    m_fangju->setPoint(fj->getPoint());
    m_fangju->setType(fj->getType());
}

card *zhuangbeiqu::getfangju()
{
    return m_fangju;
}

void zhuangbeiqu::setjinggongma(
    card *jgm)
{
    m_jingongma->setName(jgm->getName());
    m_jingongma->setSuit(jgm->getSuit());
    m_jingongma->setPoint(jgm->getPoint());
    m_jingongma->setType(jgm->getType());
}

card *zhuangbeiqu::getjinggongma()
{
    return m_jingongma;
}

void zhuangbeiqu::setfangyuma(
    card *fym)
{
    m_fangyuma->setName(fym->getName());
    m_fangyuma->setSuit(fym->getSuit());
    m_fangyuma->setPoint(fym->getPoint());
    m_fangyuma->setType(fym->getType());
}

card *zhuangbeiqu::getfangyuma()
{
    return m_fangyuma;
}
