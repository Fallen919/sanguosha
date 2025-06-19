#include "zhuangbeiqu.h"

zhuangbeiqu::zhuangbeiqu(
    QObject *parent)
    : QObject{parent}
{}

void zhuangbeiqu::setwuqi(
    card wq)
{
    m_wuqi = wq;
}

card zhuangbeiqu::getwuqi()
{
    return m_wuqi;
}

void zhuangbeiqu::setfangju(
    card fj)
{
    m_fangju = fj;
}

card zhuangbeiqu::getfangju()
{
    return m_fangju;
}

void zhuangbeiqu::setjinggongma(
    card jgm)
{
    m_jingongma = jgm;
}

card zhuangbeiqu::getjinggongma()
{
    return m_jingongma;
}

void zhuangbeiqu::setfangyuma(
    card fym)
{
    m_fangyuma = fym;
}

card zhuangbeiqu::getfangyuma()
{
    return m_fangyuma;
}
