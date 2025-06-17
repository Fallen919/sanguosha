#pragma once

#include <QPainter>
#include <QObject>
#include "card.h"
#include "player.h"
#include <QMouseEvent>

class cardPanel : public QObject
{
    Q_OBJECT
public:
    explicit cardPanel(QObject *parent = nullptr);

    //设置卡片图案和查看
    void setImage(QPixmap &front, QPixmap &back);
    QPixmap getImage();

    //设置正面和查看是否为卡牌正面
    void setFrontSide(bool flag);
    bool isFrontSide();

    //选择卡牌和看卡牌是否被选择
    void setSeclected(bool flag);
    bool isSelected();

    //卡牌信息
    void setCard(card &card);
    card getCard();

    //设置玩家和查看玩家
    void setOwner(player *player);
    player *getOwner();

protected:
    void paintEvent(QPaintEvent *event);
    //鼠标点击处理
    void mousePressEvent(QMouseEvent *event);

signals:

private:
    QPixmap m_front;
    QPixmap m_back;
    bool m_isfront;
    bool m_isSelect;
    card m_card;
    player *m_owner;
};
