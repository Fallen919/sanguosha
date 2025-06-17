#pragma once
#include "card.h"
#include <QSet>
class cards
{
public:
    cards();

    //摸牌到手牌区
    void add(card &cd);
    void add(cards &cds);

    //运算符重载方便操作
    cards &operator<<(card &cd);
    cards &operator<<(cards &cds);

    //出牌
    void remove(card &cd);
    void remove(cards &cds);

    //手牌数
    int cardnum();

    //手牌是否为空
    bool isEmpty();

    //清空手牌
    void clear();

    //某种牌是否在手牌
    bool contains(card &card);

    //随机取出一张牌
    card takeRandCard();

private:
    QSet<card> m_cards;
};
