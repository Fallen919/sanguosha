#include "cardpanel.h"

cardPanel::cardPanel(QObject *parent) : QObject{parent}
{
    m_isfront = true;
}

void cardPanel::setImage(QPixmap &front, QPixmap &back)
{
    m_front = front;
    m_back = back;
    // setFixedSize(m_front.size());
    // update();
}

QPixmap cardPanel::getImage()
{
    return m_front;
}

void cardPanel::setFrontSide(bool flag)
{
    m_isfront = flag;
}

bool cardPanel::isFrontSide()
{
    return m_isfront;
}

void cardPanel::setSeclected(bool flag)
{
    m_isSelect = flag;
}

bool cardPanel::isSelected()
{
    return m_isSelect;
}

void cardPanel::setCard(card &card)
{
    m_card = card;
}

card cardPanel::getCard()
{
    return m_card;
}

void cardPanel::setOwner(player *player)
{
    m_owner = player;
}

player *cardPanel::getOwner()
{
    return m_owner;
}

void cardPanel::paintEvent(QPaintEvent *event)
{
    // QPainter p(this);
    // if (m_isfront) {
    //     p.drawPixmap(rect(), m_front);
    // } else {
    //     p.drawPixmap(rect(), m_back);
    // }
}

void cardPanel::mousePressEvent(QMouseEvent *event) {}
