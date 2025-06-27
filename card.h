#pragma once
#include <QHashFunctions>
#include <iostream>
class player;
#include <QObject>
class GameManager;
class card : public QObject
{
    Q_OBJECT
public:
    explicit card(QObject *parent = nullptr);

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
        Ci_Xiongshuanggujian,
        Han_Bingjian,
        Fang_Tianhuaji,
        Zhu_Queyushan,
        Ba_Guazhen,
        Teng_Jia,
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

    //设置属性  枚举版本的 setter
    void setPoint(CardPoint pt);
    void setSuit(CardSuit suit);
    void setName(CardName name);
    void setType(CardType type);

    //查看属性
    QString NewGetNameString() const
    {
        switch (m_name) {
        case Sha:
            return "Sha";
        case Shan:
            return "Shan";
        case Tao:
            return "Tao";
        case Jiu:
            return "Jiu";
        case Huo_Sha:
            return "Huo_Sha";
        case Lei_Sha:
            return "Lei_Sha";
        case Wu_Zhongshengyou:
            return "Wu_Zhongshengyou";
        case Wu_Gufengdeng:
            return " Wu_Gufengdeng";
        case Tao_yuanjieyi:
            return "Tao_yuanjieyi";
        case Wan_jianqifa:
            return "Wan_jianqifa";
        case Huo_Gong:
            return "Huo_Gong";
        case Nan_Manruqin:
            return "Nan_Manruqin";
        case Jie_Daosharen:
            return " Jie_Daosharen";
        case Bing_Niangchunduan:
            return "Bing_Niangchunduan";
        case Tie_Suolianhuan:
            return "Tie_Suolianhuan";
        case Le_Busishu:
            return "Le_Busishu";
        case Jue_Dou:
            return "Jue_Dou";
        case Wu_Xiekeji:
            return "Wu_Xiekeji";
        case Zhu_Geliannv:
            return "Zhu_Geliannv";
        case Ci_Xiongshuanggujian:
            return "Ci_Xiongshuanggujian";
        case Han_Bingjian:
            return "Han_Bingjian";
        case Fang_Tianhuaji:
            return "Fang_Tianhuaji";
        case Zhu_Queyushan:
            return "Zhu_Queyushan";
        case Ba_Guazhen:
            return "Ba_Guazhen";
        case Teng_Jia:
            return "Teng_Jia";
        case Ren_Wangdun:
            return "Ren_Wangdun";
        case Bai_Yingshizi:
            return "Bai_Yingshizi";
        case Fang_Yuma:
            return "Fang_Yuma";
        case Jing_Gongma:
            return "Jing_Gongma";
        case Guo_Hechaiqiao:
            return "Guo_Hechaiqiao";
        case Shun_Shouqianyang:
            return "Shun_Shouqianyang";
        case Shan_Dian:
            return "Shan_Dian";
        case Guan_Shifu:
            return " Guan_Shifu";
        case Qi_Linggong:
            return "Qi_Linggong";
        case Qing_Longyanyuedao:
            return "Qing_Longyanyuedao";
        case Qing_Gangjian:
            return "Qing_Gangjian";
        case Gu_Dingdao:
            return "Gu_Dingdao";
        case Zhang_Bashemao:
            return "Zhang_Bashemao";
        default:
            return QString::number(m_name);
        }
    }

    QString getSuitString() const
    {
        switch (m_suit) {
        case Fang_Kuai:
            return "Fang_Kuai";
        case Mei_Hua:
            return "Mei_Hua";
        case Hong_Tao:
            return "Hong_Tao";
        case Hei_Tao:
            return "Hei_Tao";
        default:
            return QString::number(m_suit);
        }
    }

    QString getTypeString() const
    {
        switch (m_type) {
        case Ji_Ben:
            return "Ji_Ben";
        case Jing_Nang:
            return "Jing_Nang";
        case Zhuang_Bei:
            return "Zhuang_Bei";
        default:
            return QString::number(m_type);
        }
    }

    // 修改获取方法，返回字符串而不是枚举值
    CardName getName() const;
    QString NewGetName() const { return NewGetNameString(); }
    QString getSuit() const { return getSuitString(); }
    QString getType() const { return getTypeString(); }
    int getPoint() const { return static_cast<int>(m_point); }

    bool operator==(
        const card& other) const
    {
        return (m_suit == other.m_suit) && (m_point == other.m_point) && (m_name == other.m_name)
               && (m_type == other.m_type);
    }
    // 反向映射
    static CardName nameFromString(const QString& name);
    // 修改设置方法以接受字符串

    static CardSuit suitFromString(const QString& suit);
    static CardType typeFromString(const QString& type);
    // 字符串版本的 setter
    void setName(const QString& name);
    void setSuit(const QString& suit);
    void setType(const QString& type);
    void setPoint(int point);

    Q_INVOKABLE bool xiaoguo(player* laiyuan, player* mubiao);

    card(CardName name, CardType type, CardSuit suit, CardPoint point);

private:
    CardSuit m_suit;
    CardPoint m_point;
    CardName m_name;
    CardType m_type;

signals:
    void xuyaoxiangyingshan(); //需要响应闪
    void xunwenxiangyingwuxiekeji(); //询问是否响应无懈可击
};
