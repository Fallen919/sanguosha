#pragma once
#include "card.h"
#include <QSet>
#include "carddex.h"
class cards
{
public:
    cards();

    //摸牌到手牌区
    Q_INVOKABLE void add(card &cd);
    Q_INVOKABLE void add(cards &cds);

    //出牌
    Q_INVOKABLE void remove(card &cd, Carddex p);
    Q_INVOKABLE void remove(cards &cds);

    //手牌数
    Q_INVOKABLE int cardnum();

    //手牌是否为空
    Q_INVOKABLE bool isEmpty();

    //清空手牌
    Q_INVOKABLE void clear();

    //某种牌是否在手牌
    Q_INVOKABLE bool contains(card &card);

    //随机取出一张牌
    Q_INVOKABLE card takeRandCard();

private:
    QSet<card> m_cards;
};
