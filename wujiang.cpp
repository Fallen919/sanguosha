#include "wujiang.h"

wujiang::wujiang(
    QObject *parent)
    : QObject{parent}
{}

void wujiang::settili(
    int num)
{
    m_tili = num;
}

int wujiang::gettili()
{
    return m_tili;
}

void wujiang::settilishangxian(
    int num)
{
    m_tilishangxian = num;
}

int wujiang::gettilishangxian()
{
    return m_tilishangxian;
}

void wujiang::setshoupaishu(
    int sp)
{
    m_shoupaishu = sp;
}

int wujiang::getshoupaishu()
{
    return m_shoupaishu;
}

void wujiang::setshoupaishangxian(
    int num)
{
    m_shoupaishangxian = num;
}

int wujiang::getshoupaishangxian()
{
    return m_shoupaishangxian;
}

void wujiang::setwujiangshili(
    WujiangShili sl)
{
    m_shili = sl;
}

void wujiang::setxingbie(
    Xingbie xb)
{
    m_xingbie = xb;
}

void wujiang::setwujiangming(
    std::string wjm)
{
    m_wujiangming = wjm;
}

void wujiang::jineng1() {}

void wujiang::jineng2() {}

void wujiang::jineng3() {}

void wujiang::executeZhiheng(
    QList<card *> cardsToDiscard, QObject *gObj)
{
    qWarning() << "制衡";
}

wujiang::~wujiang()
{
    int i = 0;
}

wujiang::Xingbie wujiang::getxingbie()
{
    return m_xingbie;
}

wujiang::WujiangShili wujiang::getwujiangshili()
{
    return m_shili;
}
