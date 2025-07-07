#include "player.h"
#include "gamemanager.h"
player::player(
    QObject *parent)
    : QObject{parent}
    , m_wujiang{nullptr}
{
    setgongjijuli();
}

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
    // m_juli.push_back(0);
    // int num = m_mynum;
    // for (int i = 1; i <= m_wanjiashu; ++i) {
    //     if (i == m_mynum)
    //         continue;
    //     std::list<player *>::iterator it = g->getplayers().begin();
    //     while ((*it)->getmynum() != i)
    //         ++it;
    //     int jl = 0;
    //     jl = std::min(abs(i - m_mynum), abs(m_wanjiashu - (i - m_mynum)));
    //     if (!(m_zhuangbei.getjinggongma().isEmpty()))
    //         m_juli.push_back(jl - 1);
    //     if (!((*it)->m_zhuangbei.getfangyuma().isEmpty()))
    //         m_juli.push_back(jl + 1);
    // }
    m_juli.clear();      // 清空原有距离数据
    m_juli.push_back(0); // [0] 表示自己到自己的距离

    // 遍历所有其他玩家（1到总玩家数）
    for (int targetNum = 1; targetNum <= m_wanjiashu; ++targetNum) {
        if (targetNum == m_mynum)
            continue; // 跳过自己

        // 找到目标玩家对象
        player *targetPlayer = nullptr;
        for (auto p : g->getplayers()) {
            if (p->getmynum() == targetNum) {
                targetPlayer = p;
                break;
            }
        }
        if (!targetPlayer)
            continue; // 安全保护

        // 计算基础环形距离
        int directDist = abs(targetNum - m_mynum);
        int ringDist = std::min(directDist, m_wanjiashu - directDist);
        int finalDist = ringDist;

        // 进攻马效果（减少距离）
        if (!m_zhuangbei.getjinggongma().isEmpty()) {
            finalDist = (finalDist > 1) ? finalDist - 1 : 1;
        }

        // 防御马效果（增加距离）
        if (!targetPlayer->getzhuangbei()->getfangyuma().isEmpty()) {
            finalDist += 1;
        }

        // 存储计算后的距离
        m_juli.push_back(finalDist);
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

void player::setwujiang(
    wujiang *w)
{
    if (m_wujiang) {
        m_wujiang->deleteLater(); // 安全删除现有武将
    }
    m_wujiang = w;

    if (w) {
        w->setParent(this); // 设置父对象，由Qt管理生命周期

        // 更新玩家属性
        settili(w->gettili());
        settilishangxian(w->gettilishangxian());
        setshoupaishangxian(w->getshoupaishangxian());
    }
}

wujiang *player::getwujiang()
{
    return m_wujiang;
}

void player::mopai(
    int num, GameManager *g)
{
    for (int i = 0; i < num; ++i) {
        m_cards.append(g->drawCard());
        }
        if (g->getdangqianplayer()->getmynum() == 1) {
            g->fuzhicards(m_cards);
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

bool player::playcard(
    int handIndex, GameManager *g)
{
    // if (handIndex < 0 || handIndex >= m_cards.size())
    //     return false;

    // card *cd = m_cards[handIndex];
    // if (cd->xiaoguo(this, this, g)) {
    //     // 只从玩家手牌中移除，不处理弃牌逻辑
    //     m_cards.removeAt(handIndex);
    //     return true;
    // }
    // return false;
    if (handIndex < 0 || handIndex >= m_cards.size())
        return false;

    card *cd = m_cards[handIndex];
    if (cd->xiaoguo(this, this, g)) {
        // 确保卡牌从玩家手牌中移除
        m_cards.removeAt(handIndex);
        // 通知GameManager同步手牌状态
        if (g && g->getdangqianplayer() == this) {
            //g->removeCard(cd);
        }
        return true;
    }
    return false;
}

void player::clearcards()
{
    m_cards.clear();
}

void player::fuzhicards(
    QList<card *> cds)
{
    clearcards();
    qWarning() << "负责前有:" << m_cards.size();
    m_cards.append(cds);
    qWarning() << "负责后有:" << m_cards.size();
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

void player::removeCard(
    card *cardToRemove)
{
    for (int i = 0; i < m_cards.size(); ++i) {
        if (m_cards[i] == cardToRemove) {
            m_cards.removeAt(i);
            return;
        }
    }
    qWarning() << "要移除的卡牌不在玩家手牌中";
}

QString player::getwujiangming() const
{
    if (m_wujiang) {
        return QString::fromStdString(m_wujiang->getwujiangming());
    }
    return "";
}

player::~player()
{
    delete m_wujiang;
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
