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
        if (!(m_zhuangbei.getjinggongma().isEmpty()))
            m_juli[i] = jl - 1;
        if (!((*mm)->m_zhuangbei.getfangyuma().isEmpty()))
            m_juli[i] = jl + 1;
        it++;
    }
}

int player::getjuli(
    player *p1, player *p2)
{
    int num = abs(p1->getmynum() - p2->getmynum());
    return m_juli[num];
}

void player::addjudg(
    card *c)
{
    m_judg.addjudgarea(c);
}

judgearea *player::getjudg()
{
    return &m_judg;
}

void player::addwuqi(
    card *c)
{
    m_zhuangbei.addwuqi(c);
}

void player::addfangju(
    card *c)
{
    m_zhuangbei.addfangju(c);
}

void player::addjinggongma(
    card *c)
{
    m_zhuangbei.addjinggongma(c);
}

void player::addfangyuma(
    card *c)
{
    m_zhuangbei.addfangyuma(c);
}

zhuangbeiqu *player::getzhuangbei()
{
    return &m_zhuangbei;
}

QList<card *> player::getcards()
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
    for (int i = 0; i < num; ++i) {
        m_cards.append(g->drawCard());
        }
}

void player::setgongjijuli()
{
    m_gongjijuli = 1;
    if (m_zhuangbei.getwuqi().isEmpty())
        return;
    if (m_zhuangbei.getwuqi().first()->getName() == card::Ci_Xiongshuanggujian
        || m_zhuangbei.getwuqi().first()->getName() == card::Han_Bingjian
        || m_zhuangbei.getwuqi().first()->getName() == card::Gu_Dingdao
        || m_zhuangbei.getwuqi().first()->getName() == card::Qing_Gangjian) {
        m_gongjijuli = 2;
    }
    if (m_zhuangbei.getwuqi().first()->getName() == card::Guan_Shifu
        || m_zhuangbei.getwuqi().first()->getName() == card::Qing_Longyanyuedao
        || m_zhuangbei.getwuqi().first()->getName() == card::Zhang_Bashemao) {
        m_gongjijuli = 3;
    }
    if (m_zhuangbei.getwuqi().first()->getName() == card::Zhu_Queyushan
        || m_zhuangbei.getwuqi().first()->getName() == card::Fang_Tianhuaji) {
        m_gongjijuli = 4;
    }
    if (m_zhuangbei.getwuqi().first()->getName() == card::Qi_Linggong) {
        m_gongjijuli = 5;
    }
}

int player::getgongjijuli()
{
    return m_gongjijuli;
}

bool player::shoudaoshanghai(
    int num, const QString shanghaileixing)
{
    if (m_zhuangtai.contains("Mian_Shang"))
        return false;

    if (m_zhuangtai.contains("Teng_Jia") && shanghaileixing == "Fire")
        num++;

    if (shanghaileixing == "Pu_Tong" && m_zhuangtai.contains("Mian_Yi_Pu_Tong"))
        return false;

    m_tili -= num;
    emit shoudaoshanghai(num);

    if (m_tili <= 0)
        emit jinrubinsi();
    return true;
}

bool player::huixue(
    int num)
{
    if (num + m_tili >= m_tilishangxian) {
        num = m_tilishangxian - m_tili;
        m_tili = m_tilishangxian;
    } else
        m_tili += num;
    emit huifuxueliang(num);
}

void player::addzhuangtai(
    const QString zhuangtai, int num)
{
    m_zhuangtai[zhuangtai] = num;
    emit addzt(zhuangtai);
}

bool player::isbaohan(
    const QString zhuangtai)
{
    return m_zhuangtai.contains(zhuangtai);
}

void player::yichuzhuangtai(
    const QString zhuangtai)
{
    m_zhuangtai.remove(zhuangtai);
    emit yichuzt(zhuangtai);
}

void player::playcard(
    int handIndex, GameManager *g)
{
    if (handIndex < 0 || handIndex >= m_cards.size()) {
        qWarning() << "Invalid hand index:" << handIndex;
        qWarning() << "shoupai:" << m_cards.size();
        return;
    }
    //m_cards[handIndex]->xiaoguo(this, this);
    m_cards.removeAt(handIndex);
}

void player::clearcards()
{
    m_cards.clear();
}

void player::fuzhicards(
    QList<card *> cds)
{
    clearcards();
    m_cards.append(cds);
}

void player::settilishangxian(
    int num)
{
    m_tilishangxian = num;
}

int player::gettilishangxian()
{
    return m_tilishangxian;
}

void player::setshoupaishangxian(
    int num)
{
    m_shoupaishangxian = num;
}

int player::getshoupaishangxian()
{
    return m_shoupaishangxian;
}

void player::settili(
    int num)
{
    m_tili = num;
}

int player::gettili()
{
    return m_tili;
}

bool player::isalive()
{
    if (m_tili <= 0)
        return false;
    else
        return true;
}
