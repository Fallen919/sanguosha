#include "player.h"
#include "gamemanager.h"

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

void player::setjuli(
    GameManager *g)
{
    int num = m_mynum;
    for (int i = 0; i < m_wanjiashu; ++i) {
        std::list<player *>::iterator it = g->getplayers().begin();
        std::list<player *>::iterator t = g->getplayers().end();
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

QList<card> player::getcards()
{
    return m_cards;
}

void player::setwujiang(
    wujiang *w)
{
    m_wujiang.settili(w->gettili());
    m_wujiang.settilishangxian(w->gettilishangxian());
    m_wujiang.setshoupaishu(w->getshoupaishu());
    m_wujiang.setshoupaishangxian(w->getshoupaishangxian());
    m_wujiang.setwujiangming(w->getwujiangming());
    m_wujiang.setwujiangshili(w->getwujiangshili());
    m_wujiang.setxingbie(w->getxingbie());
}

wujiang *player::getwujiang()
{
    return &m_wujiang;
}

void player::mopai(
    int num, GameManager *g)
{
    //if (m_mynum == g->getdangqianplayer()->getmynum())
    for (int i = 0; i < num; ++i) {
        m_cards.append(g->drawCard());
        if (m_mynum == 1) {
            g->gethandcards().clear();
            g->gethandcards().append(m_cards);
        }
    }
}

void player::setgongjijuli()
{
    m_gongjijuli = 0;
    if (m_zhuangbei.getwuqi().getName() == card::Ci_Xiongshuanggujian
        || m_zhuangbei.getwuqi().getName() == card::Han_Bingjian
        || m_zhuangbei.getwuqi().getName() == card::Gu_Dingdao
        || m_zhuangbei.getwuqi().getName() == card::Qing_Gangjian) {
        m_gongjijuli += 2;
    }
    if (m_zhuangbei.getwuqi().getName() == card::Guan_Shifu
        || m_zhuangbei.getwuqi().getName() == card::Qing_Longyanyuedao
        || m_zhuangbei.getwuqi().getName() == card::Zhang_Bashemao) {
        m_gongjijuli += 3;
    }
    if (m_zhuangbei.getwuqi().getName() == card::Zhu_Queyushan
        || m_zhuangbei.getwuqi().getName() == card::Fang_Tianhuaji) {
        m_gongjijuli += 4;
    }
    if (m_zhuangbei.getwuqi().getName() == card::Qi_Linggong) {
        m_gongjijuli += 5;
    }
}

int player::getgongjijuli()
{
    return m_gongjijuli;
}

void player::playcard(
    int handIndex, GameManager *g)
{
    g->playCard(handIndex);
}
