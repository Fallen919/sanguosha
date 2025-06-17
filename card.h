#pragma once
#include <QHashFunctions>
#include <iostream>
class card
{
public:
    //花色
    enum CardSuit {
        Suit_Begin,
        Fang_Kuai,
        Mei_Hua,
        Hong_Tao,
        Hei_Tao,
        Suit_End,
    };

    //点数
    enum CardPoint {
        Point_Begin,
        Card_A,
        Card_2,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Point_End,
    };

    //名字
    enum CardName {
        Name_Begin,
        Sha,
        Shan,
        Tao,
        Jiu,
        Huo_Sha,
        Lei_Sha,
        Wu_Zhongshengyou,
        Wu_Gufengdeng,
        Tao_yuanjieyi,
        Wan_jianqifa,
        Huo_Gong,
        Nan_Manruqin,
        Jie_Daosharen,
        Bing_Niangchunduan,
        Tie_Suolianhuan,
        Le_Busishu,
        Jue_Dou,
        Wu_Xiekeji,
        Zhu_Geliannv,
        Chi_Xiongshuanggujian,
        Han_Bingjian,
        Fang_Tianhuaji,
        Zhu_Queyushan,
        Ba_Guazhen,
        Ten_Jia,
        Ren_Wangdun,
        Bai_Yingshizi,
        Fang_Yuma,
        Jing_Gongma,
        Guo_Hechaiqiao,
        Shun_Shouqianyang,
        Shan_Dian,
        Guan_Shifu,
        Qi_Linggong,
        Qing_Longyanyuedao,
        Qing_Gangjian,
        Gu_Dingdao,
        Zhang_Bashemao,
        Name_End,
    };

    //类型
    enum CardType {
        Type_Begin,
        Ji_Ben,
        Jing_Nang,
        Zhuang_Bei,
        Type_End,
    };

    //设置属性
    void setPoint(CardPoint pt);
    void setSuit(CardSuit suit);
    void setName(CardName name);
    void setType(CardType type);

    //查看属性
    CardName getName() const;
    CardSuit getSuit() const;
    CardPoint getPoint() const;
    CardType getType() const;

    bool operator==(const card &other) const
    {
        return (m_suit == other.m_suit) && (m_point == other.m_point) && (m_name == other.m_name)
               && (m_type == other.m_type);
    }

    card();
    card(CardName name, CardType type, CardSuit suit, CardPoint point);

private:
    CardSuit m_suit;
    CardPoint m_point;
    CardName m_name;
    CardType m_type;
};

inline size_t qHash(const card &c, size_t seed = 0)
{
    return qHashMulti(seed, c.getSuit(), c.getPoint(), c.getName(), c.getType());
}
