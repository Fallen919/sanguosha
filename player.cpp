#include "player.h"

player::player(QObject *parent) : QObject{parent} {}

void player::setwanjiashu(
    int num)
{
    m_wanjiashu = num;
}

int player::getwanjiashu()
{
    return m_wanjiashu;
}

void player::setmynum(
    int num)
{
    m_mynum = num;
}

int player::getmynum()
{
    return m_mynum;
}

void player::setplayer(
    player *p)
{
    wanjia.push_back(p);
}

void player::setjuli()
{
    int num = m_mynum;
    for (int i = 0; i < m_wanjiashu; ++i) {
        std::list<player *>::iterator it = wanjia.begin();
        std::list<player *>::iterator t = wanjia.end();
        int jl = 0;
        for (int m = 0; m <= i; ++m) {
            ++it;
        }
        std::list<player *>::iterator mm = it;
        while (num != (*it)->m_mynum || num != (*t)->m_mynum) {
            ++it;
            ++t;
            ++jl;
        }
        if (m_zhuangbei.getjinggongma().getName() == card::Jing_Gongma
            && (*mm)->m_zhuangbei.getfangyuma().getName() != card::Fang_Yuma)
            m_juli[i] = jl - 1;
        else if (m_zhuangbei.getjinggongma().getName() != card::Jing_Gongma
                 && (*mm)->m_zhuangbei.getfangyuma().getName() == card::Fang_Yuma)
            m_juli[i] = jl + 1;
        else {
            m_juli[i] = jl;
        }
        it++;
    }
}

void player::setjudg(
    judgearea *j)
{
    std::list<card>::iterator it = (*j).getjudgarea().begin();
    for (int i = 0; i < (*j).getjudgarea().size(); ++i, ++it) {
        m_judg.getjudgarea().push_back((*it));
    }
}

judgearea *player::getjudg()
{
    return &m_judg;
}

void player::setzhuangbei(
    zhuangbeiqu *z)
{
    m_zhuangbei.setfangju(z->getfangju());
    m_zhuangbei.setwuqi(z->getwuqi());
    m_zhuangbei.setfangyuma(z->getfangyuma());
    m_zhuangbei.setjinggongma(z->getjinggongma());
}

zhuangbeiqu *player::getzhuangbei()
{
    return &m_zhuangbei;
}

void player::setwanjia(
    player *p)
{
    wanjia.push_back(p);
}

std::list<player *> player::getwanjia()
{
    return wanjia;
}

void player::setcards(
    cards *c)
{
    m_cards = *c;
}

cards *player::getcards()
{
    return &m_cards;
}
