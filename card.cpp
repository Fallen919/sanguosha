#include "card.h"
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
