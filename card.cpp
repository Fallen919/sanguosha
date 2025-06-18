#include "card.h"

void card::setPoint(CardPoint pt)
{
    m_point = pt;
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
