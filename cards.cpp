#include "cards.h"
#include <QRandomGenerator>

cards::cards() {}

void cards::add(card &cd)
{
    m_cards.insert(cd);
}

void cards::add(cards &cds)
{
    m_cards.unite(cds.m_cards);
}

cards &cards::operator<<(card &cd)
{
    add(cd);
    return *this;
}

cards &cards::operator<<(cards &cds)
{
    add(cds);
    return *this;
}

void cards::remove(card &cd)
{
    m_cards.remove(cd);
}

void cards::remove(cards &cds)
{
    m_cards.subtract(cds.m_cards);
}

int cards::cardnum()
{
    return m_cards.size();
}

bool cards::isEmpty()
{
    return m_cards.isEmpty();
}

void cards::clear()
{
    m_cards.clear();
}

bool cards::contains(card &cd)
{
    return m_cards.contains(cd);
}

card cards::takeRandCard()
{
    int num = QRandomGenerator::global()->bounded(m_cards.size());
    QSet<card>::const_iterator it = m_cards.begin();
    for (int i = 0; i < num; ++i, ++it)
        ;
    card cd = *it;
    m_cards.erase(it);
    return cd;
}
