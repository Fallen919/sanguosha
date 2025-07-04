#include "player.h"
#include "gamemanager.h"

player::player(QObject *parent)
    : QObject{parent}
{
    setgongjijuli();
}

void player::setwanjiashu(int num)
{
    m_wanjiashu = num;
}

int player::getwanjiashu()
{
    return m_wanjiashu;
}

void player::setmynum(int num)
{
    m_mynum = num;
}

int player::getmynum()
{
    return m_mynum;
}

void player::setjuli(GameManager *g)
{
    m_juli.push_back(0);
    int num = m_mynum;
    for (int i = 1; i <= m_wanjiashu; ++i) {
        if (i == m_mynum)
            continue;
        std::list<player *>::iterator it = g->getplayers().begin();
        while ((*it)->getmynum() != i)
            ++it;
        int jl = 0;
        jl = std::min(abs(i - m_mynum), abs(m_wanjiashu - (i - m_mynum)));
        if (!(m_zhuangbei.getjinggongma().isEmpty()))
            m_juli.push_back(jl - 1);
        if (!((*it)->m_zhuangbei.getfangyuma().isEmpty()))
            m_juli.push_back(jl + 1);
    }
}

int player::getjuli(player *p1, player *p2)
{
    int num = abs(p1->getmynum() - p2->getmynum());
    return m_juli[num];
}

void player::addjudg(card *c)
{
    m_judg.addjudgarea(c);
}

judgearea *player::getjudg()
{
    return &m_judg;
}

void player::addwuqi(card *c)
{
    m_zhuangbei.addwuqi(c);
}

void player::addfangju(card *c)
{
    m_zhuangbei.addfangju(c);
}

void player::addjinggongma(card *c)
{
    m_zhuangbei.addjinggongma(c);
}

void player::addfangyuma(card *c)
{
    m_zhuangbei.addfangyuma(c);
}

void player::removewuqi()
{
    m_zhuangbei.removewuqi();
}

void player::removefangju()
{
    m_zhuangbei.removefangju();
}

void player::removejinggongma()
{
    m_zhuangbei.removejinggongma();
}

void player::removefangyuma()
{
    m_zhuangbei.removefangyuma();
}

zhuangbeiqu *player::getzhuangbei()
{
    return &m_zhuangbei;
}

QList<card *> player::getcards()
{
    return m_cards;
}

void player::setwujiang(wujiang *w)
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

void player::mopai(int num, GameManager *g)
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

bool player::shoudaoshanghai(int num, const QString shanghaileixing)
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

bool player::huixue(int num)
{
    if (num + m_tili >= m_tilishangxian) {
        num = m_tilishangxian - m_tili;
        m_tili = m_tilishangxian;
    } else
        m_tili += num;

    emit huifuxueliang(num);
    return true; // 修复：添加返回值
}

void player::addzhuangtai(const QString zhuangtai, int num)
{
    m_zhuangtai[zhuangtai] = num;
    emit addzt(zhuangtai);
}

bool player::isbaohan(const QString zhuangtai)
{
    return m_zhuangtai.contains(zhuangtai);
}

void player::yichuzhuangtai(const QString zhuangtai)
{
    m_zhuangtai.remove(zhuangtai);
    emit yichuzt(zhuangtai);
}

bool player::playcard(int handIndex, GameManager *g)
{
    if (handIndex < 0 || handIndex >= m_cards.size())
        return false;

    card *cd = m_cards[handIndex];
    if (cd->xiaoguo(this, this, g)) {
        // 只从玩家手牌中移除，不处理弃牌逻辑
        m_cards.removeAt(handIndex);
        return true;
    }
    return false;
}

void player::clearcards()
{
    m_cards.clear();
}

void player::fuzhicards(QList<card *> cds)
{
    clearcards();
    m_cards.append(cds);
}

int player::getPlayerIndex() const
{
    return m_mynum;
}

bool player::hasShan() const
{
    for (card *c : m_cards) {
        if (c->getName() == card::Shan) {
            return true;
        }
    }
    return false;
}

bool player::hasWuXiekeji() const
{
    for (card *c : m_cards) {
        if (c->getName() == card::Wu_Xiekeji) {
            return true;
        }
    }
    return false;
}

void player::removeCard(card *cardToRemove)
{
    for (int i = 0; i < m_cards.size(); ++i) {
        if (m_cards[i] == cardToRemove) {
            m_cards.removeAt(i);
            return;
        }
    }
    qWarning() << "要移除的卡牌不在玩家手牌中";
}

void player::settilishangxian(int num)
{
    m_tilishangxian = num;
}

int player::gettilishangxian()
{
    return m_tilishangxian;
}

void player::setshoupaishangxian(int num)
{
    m_shoupaishangxian = num;
}

int player::getshoupaishangxian()
{
    return m_shoupaishangxian;
}

void player::settili(int num)
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
void player::addCard(card *cd)
{
    if (cd) {
        m_cards.append(cd);
        qDebug() << "玩家" << m_mynum << "获得了卡牌:" << cd->NewGetNameString();
    }
}
