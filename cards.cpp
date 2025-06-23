#include "cards.h"
#include <QRandomGenerator>

cards::cards() {}

void cards::add(card &cd)
{
    m_cards.push_back(cd);
}

void cards::remove(
    card &cd, Carddex p)
{
    p.jinruqipaidui(cd);
    m_cards.remove(cd);
}


int cards::cardnum()
{
    return m_cards.size();
}

bool cards::isEmpty()
{
    return m_cards.empty();
}

void cards::clear()
{
    m_cards.clear();
}

