#include "card.h"
#include "player.h"
#include "gamemanager.h"
card::card(
    QObject* parent)
    : QObject{parent}
{}

card::CardName card::nameFromString(
    const QString& name)
{
    card temp;
    for (int i = CardName::Name_Begin + 1; i < CardName::Name_End; i++) {
        temp.setName(static_cast<CardName>(i)); // 使用公共 setter 方法
        if (temp.NewGetNameString().trimmed() == name.trimmed()) {
            return static_cast<CardName>(i);
        }
    }
    return Name_Begin;
}

card::CardSuit card::suitFromString(
    const QString& suit)
{
    card temp;
    for (int i = CardSuit::Suit_Begin + 1; i < CardSuit::Suit_End; i++) {
        temp.setSuit(static_cast<CardSuit>(i)); // 使用公共 setter 方法
        if (temp.getSuitString().trimmed() == suit.trimmed()) {
            return static_cast<CardSuit>(i);
        }
    }
    return Suit_Begin;
}

card::CardType card::typeFromString(
    const QString& type)
{
    card temp;
    for (int i = CardType::Type_Begin + 1; i < CardType::Type_End; i++) {
        temp.setType(static_cast<CardType>(i)); // 使用公共 setter 方法
        if (temp.getTypeString().trimmed() == type.trimmed()) {
            return static_cast<CardType>(i);
        }
    }
    return Type_Begin;
}

void card::setPoint(
    int point)
{
    // 将整数转换为 CardPoint 枚举值
    m_point = static_cast<CardPoint>(point);
}

bool card::xiaoguo(
    player* laiyuan, player* mubiao, GameManager* g)
{
    switch (m_name) {
    case Sha: {
        if (!laiyuan || !mubiao || !g)
            return false;
        if (laiyuan->getgongjijuli() < (laiyuan->getjuli(laiyuan, mubiao)))
            return false;
        if (mubiao->isbaohan("Ren_Wangdun") && this->getSuit() == "Hei_Tao"
            && this->getSuit() == "Mei_Hua")
            return false;
        if (mubiao->isbaohan("Teng_Jia"))
            return false;
        emit xuyaoxiangyingshan();
        bool ischushan = g->waitForShanResponse(mubiao, this);
        if (ischushan) {
            qDebug() << "闪响应成功，杀无效";
            return false;
        }
        if (!ischushan) {
            if (laiyuan->isbaohan("Jiu"))
                return mubiao->shoudaoshanghai(2, "Pu_Tong");
            else {
                qDebug() << "杀成功";
                return mubiao->shoudaoshanghai(1, "Pu_Tong");
            }
        }
        break;
    }

    case Shan: {
        qDebug() << "闪被作为响应牌打出";
        return true; // 表示响应成功
        break;
    }

    case Tao: {
        if (mubiao->gettili() == mubiao->gettilishangxian())
            return false;
        return mubiao->huixue(1);
        break;
    }

    case Jiu: {
        if (mubiao->isbaohan("Jiu"))
            return false;
        else
            mubiao->addzhuangtai("Jiu", 1);
        return true;
        break;
    }

    case Lei_Sha: {
        if (!laiyuan || !mubiao || !g)
            return false;
        if (laiyuan->getgongjijuli() < (laiyuan->getjuli(laiyuan, mubiao)))
            return false;
        if (mubiao->isbaohan("Ren_Wangdun") && this->getSuit() == "card::Hei_Tao"
            && this->getSuit() == "Mei_Hua")
            return false;
        emit xuyaoxiangyingshan();

        bool sfchushan = g->waitForShanResponse(mubiao, this);

        if (sfchushan) {
            qDebug() << "闪响应成功，杀无效";
            return false;
        }

        if (laiyuan->isbaohan("Jiu"))
            return mubiao->shoudaoshanghai(2, "Lei");
        else {
            qDebug() << "杀成功";
            return mubiao->shoudaoshanghai(1, "Lei");
        }
        break;
    }

    case Huo_Sha: {
        if (!laiyuan || !mubiao || !g)
            return false;
        if (laiyuan->getgongjijuli() < (laiyuan->getjuli(laiyuan, mubiao)))
            return false;
        if (mubiao->isbaohan("Ren_Wangdun") && this->getSuit() == "card::Hei_Tao"
            && this->getSuit() == "Mei_Hua")
            return false;
        emit xuyaoxiangyingshan();

        bool isschushan = g->waitForShanResponse(mubiao, this);

        if (isschushan) {
            qDebug() << "闪响应成功，杀无效";
            return false;
        }
        if (laiyuan->isbaohan("Jiu"))
            return mubiao->shoudaoshanghai(2, "Fire");
        else {
            qDebug() << "杀成功";
            return mubiao->shoudaoshanghai(1, "Fire");
        }

        break;
    }

    case Wu_Zhongshengyou: {
        emit xuyaowuxiekeji(this); // 通知需要无懈可击响应
        // 等待无懈可击响应
        bool wuxieResponded = g->waitForWuXiekejiResponse(this);

        if (wuxieResponded) {
            qDebug() << "无懈可击生效，锦囊牌无效";
            return true;
        }
        qDebug() << "无中生有成功";
        mubiao->mopai(2, g);
        return true;
        break;
    }

    case Wu_Gufengdeng: {
        break;
    }

    case Tao_yuanjieyi: {
        break;
    }

    case Wan_jianqifa:

    {
        break;
    }

    case Huo_Gong:

    {
        break;
    }

    case Nan_Manruqin:

    {
        break;
    }

    case Jie_Daosharen:

    {
        break;
    }

    case Bing_Niangchunduan: {
        mubiao->addjudg(this);
        return true;

        break;
    }

    case Le_Busishu: {
        mubiao->addjudg(this);
        return true;
        break;
    }

    case Jue_Dou:

    {
        break;
    }

    case Wu_Xiekeji:

    {
        qDebug() << "无懈可击被作为响应牌打出";
        return true;
        break;
    }

    case Guo_Hechaiqiao:

    {
        break;
    }

    case Shun_Shouqianyang:

    {
        break;
    }

    case Tie_Suolianhuan:

    {
        break;
    }

    case Shan_Dian: {
        mubiao->addjudg(this);
        return true;

        break;
    }

    case Zhu_Geliannv: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Zhu_Geliannv", 1);
        return true;

        break;
    }

    case Ci_Xiongshuanggujian: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Ci_Xiongshuanggujian", 1);
        return true;

        break;
    }

    case Han_Bingjian: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Han_Bingjian", 1);
        return true;

        break;
    }

    case Fang_Tianhuaji: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Fang_Tianhuaji", 1);
        return true;

        break;
    }

    case Zhu_Queyushan: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Zhu_Queyushan", 1);
        return true;

        break;
    }

    case Zhang_Bashemao: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Zhang_Bashemao", 1);
        return true;

        break;
    }

    case Gu_Dingdao: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Gu_Dingdao", 1);
        return true;

        break;
    }

    case Guan_Shifu: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Guan_Shifu", 1);
        return true;

        break;
    }

    case Qi_Linggong: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Qi_Linggong", 1);
        return true;

        break;
    }

    case Qing_Longyanyuedao: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Qing_Longyanyuedao", 1);
        return true;

        break;
    }

    case Qing_Gangjian: {
        if (!mubiao->getzhuangbei()->getwuqi().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getwuqi().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removewuqi();
            g->moveCardToDiscard(cd);
        }
        mubiao->addwuqi(this);
        mubiao->addzhuangtai("Qing_Gangjian", 1);
        return true;

        break;
    }

    case Ba_Guazhen: {
        if (!mubiao->getzhuangbei()->getfangju().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getfangju().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removefangju();
            g->moveCardToDiscard(cd);
        }
        mubiao->addfangju(this);
        mubiao->addzhuangtai("Ba_Guazhen", 1);
        return true;

        break;
    }

    case Teng_Jia: {
        if (!mubiao->getzhuangbei()->getfangju().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getfangju().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removefangju();
            g->moveCardToDiscard(cd);
        }
        mubiao->addfangju(this);
        mubiao->addzhuangtai("Teng_Jia", 1);
        return true;

        break;
    }

    case Ren_Wangdun: {
        if (!mubiao->getzhuangbei()->getfangju().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getfangju().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removefangju();
            g->moveCardToDiscard(cd);
        }
        mubiao->addfangju(this);
        mubiao->addzhuangtai("Ren_Wangdun", 1);
        return true;

        break;
    }

    case Bai_Yingshizi: {
        if (!mubiao->getzhuangbei()->getfangju().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getfangju().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removefangju();
            g->moveCardToDiscard(cd);
        }
        mubiao->addfangju(this);
        mubiao->addzhuangtai("Bai_Yingshizi", 1);
        return true;

        break;
    }

    case Fang_Yuma: {
        if (!mubiao->getzhuangbei()->getfangju().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getfangju().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removefangyuma();
            g->moveCardToDiscard(cd);
        }
        mubiao->addfangyuma(this);
        mubiao->addzhuangtai("Fang_Yuma", 1);
        return true;

        break;
    }

    case Jing_Gongma: {
        if (!mubiao->getzhuangbei()->getfangju().isEmpty()) {
            card* cd = mubiao->getzhuangbei()->getfangju().first();
            mubiao->yichuzhuangtai(cd->NewGetNameString());
            mubiao->removejinggongma();
            g->moveCardToDiscard(cd);
        }
        mubiao->addjinggongma(this);
        mubiao->addzhuangtai("Jing_Gongma", 1);
        return true;

        break;
    }

    default: {
        break;
    }
    }
}
void card::setSuit(
    CardSuit suit)
{
    m_suit = suit;
}

void card::setName(
    CardName name)
{
    m_name = name;
}

void card::setType(
    CardType type)
{
    m_type = type;
}

void card::setName(
    const QString& name)
{
    m_name = nameFromString(name);
}

void card::setSuit(
    const QString& suit)
{
    m_suit = suitFromString(suit);
}

void card::setType(
    const QString& type)
{
    m_type = typeFromString(type);
}

card::CardName card::getName() const
{
    return m_name;
}

// card::CardSuit card::getSuit() const
// {
//     return m_suit;
// }

// card::CardPoint card::getPoint() const
// {
//     return m_point;
// }

// card::CardType card::getType() const
// {
//     return m_type;
// }
card::card(
    CardName name, CardType type, CardSuit suit, CardPoint point)
{
    m_suit = suit;
    m_point = point;
    m_name = name;
    m_type = type;
}
