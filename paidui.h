#pragma once
#include <QList>
#include "card.h"
#include "cards.h"

class paidui
{
public:
    paidui();
    void add(card cd);
    //初始化牌堆
    void initpaidui();
 Q_PROPERTY(int count READ count NOTIFY countChanged) // 牌堆数量属性
    //洗牌
    void xipai();
signals:
    void countChanged(int newCount); // 牌数变化信号
private:
    QList<card> m_paidui;
};
