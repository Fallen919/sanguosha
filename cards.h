#pragma once
#include "card.h"
#include <QSet>
#include "carddex.h"
class card;
class cards
{
public:
    cards();

    //摸牌到手牌区
    Q_INVOKABLE void add(card &cd);

    //出牌
    Q_INVOKABLE void remove(card &cd, Carddex p);

    //手牌数
    Q_INVOKABLE int cardnum();

    //手牌是否为空
    Q_INVOKABLE bool isEmpty();

    //清空手牌
    Q_INVOKABLE void clear();

private:
    std::list<card> m_cards;
};
