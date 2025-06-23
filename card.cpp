#include "card.h"
#include "player.h"
card::CardName card::nameFromString(const QString& name) {
    card temp;
    for (int i = CardName::Name_Begin + 1; i < CardName::Name_End; i++) {
        temp.setName(static_cast<CardName>(i)); // 使用公共 setter 方法
        if (temp.NewGetNameString().trimmed() == name.trimmed()) {
            return static_cast<CardName>(i);
        }
    }
    return Name_Begin;
}

card::CardSuit card::suitFromString(const QString& suit) {
    card temp;
    for (int i = CardSuit::Suit_Begin + 1; i < CardSuit::Suit_End; i++) {
        temp.setSuit(static_cast<CardSuit>(i)); // 使用公共 setter 方法
        if (temp.getSuitString().trimmed() == suit.trimmed()) {
            return static_cast<CardSuit>(i);
        }
    }
    return Suit_Begin;
}

card::CardType card::typeFromString(const QString& type) {
    card temp;
    for (int i = CardType::Type_Begin + 1; i < CardType::Type_End; i++) {
        temp.setType(static_cast<CardType>(i)); // 使用公共 setter 方法
        if (temp.getTypeString().trimmed() == type.trimmed()) {
            return static_cast<CardType>(i);
        }
    }
    return Type_Begin;
}

void card::setPoint(int point) {
    // 将整数转换为 CardPoint 枚举值
    m_point = static_cast<CardPoint>(point);
}

void card::xiaoguo(
    card c)
{
    if (c.getName() == Sha) {
    }
    if (c.getName() == Shan) {
    }
    if (c.getName() == Tao) {
    }
    if (c.getName() == Jiu) {
    }
    if (c.getName() == Lei_Sha) {
    }
    if (c.getName() == Huo_Sha) {
    }
    if (c.getName() == Wu_Zhongshengyou) {
    }
    if (c.getName() == Wu_Gufengdeng) {
    }
    if (c.getName() == Tao_yuanjieyi) {
    }
    if (c.getName() == Wan_jianqifa) {
    }
    if (c.getName() == Huo_Gong) {
    }
    if (c.getName() == Nan_Manruqin) {
    }
    if (c.getName() == Jie_Daosharen) {
    }
    if (c.getName() == Bing_Niangchunduan) {
    }
    if (c.getName() == Le_Busishu) {
    }
    if (c.getName() == Jue_Dou) {
    }
    if (c.getName() == Wu_Xiekeji) {
    }
    if (c.getName() == Guo_Hechaiqiao) {
    }
    if (c.getName() == Shun_Shouqianyang) {
    }
    if (c.getName() == Tie_Suolianhuan) {
    }
    if (c.getName() == Shan_Dian) {
    }
    if (c.getName() == Zhu_Geliannv) {
    }
    if (c.getName() == Ci_Xiongshuanggujian) {
    }
    if (c.getName() == Han_Bingjian) {
    }
    if (c.getName() == Fang_Tianhuaji) {
    }
    if (c.getName() == Zhu_Queyushan) {
    }
    if (c.getName() == Zhang_Bashemao) {
    }
    if (c.getName() == Gu_Dingdao) {
    }
    if (c.getName() == Guan_Shifu) {
    }
    if (c.getName() == Qi_Linggong) {
    }
    if (c.getName() == Qing_Longyanyuedao) {
    }
    if (c.getName() == Qing_Gangjian) {
    }
    if (c.getName() == Ba_Guazhen) {
    }
    if (c.getName() == Teng_Jia) {
    }
    if (c.getName() == Ren_Wangdun) {
    }
    if (c.getName() == Bai_Yingshizi) {
    }
    if (c.getName() == Fang_Yuma) {
    }
    if (c.getName() == Jing_Gongma) {
    }
}
void card::setSuit(CardSuit suit)
{
    m_suit = suit;
}

void card::setName(CardName name)
{
    m_name = name;
}

void card::setType(CardType type)
{
    m_type = type;
}

void card::setName(const QString& name) {
    m_name = nameFromString(name);
}

void card::setSuit(const QString& suit) {
    m_suit = suitFromString(suit);
}

void card::setType(const QString& type) {
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

card::card() {}

card::card(CardName name, CardType type, CardSuit suit, CardPoint point)
{
    m_suit = suit;
    m_point = point;
    m_name = name;
    m_type = type;
}
