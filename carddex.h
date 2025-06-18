#pragma once

#include <QObject>
#include <QList>
#include <QVariant>
#include "card.h"

class Carddex : public QObject {
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged) // 牌堆数量属性

public:
 explicit Carddex(QObject *parent = nullptr);
    Q_INVOKABLE  void initcarddex();
    Q_INVOKABLE  void add( card cd);
    Q_INVOKABLE bool playCard(const QVariantMap &cardData);
    Q_INVOKABLE void xipai(); // 洗牌方法
    Q_INVOKABLE QVariant drawCard(); // 抽牌方法
    Q_INVOKABLE int count() const;   // 获取剩余牌数
    Q_INVOKABLE void jinruqipaidui(card &cd);
    Q_INVOKABLE card mopai();
signals:
    void countChanged(int newCount); // 牌数变化信号
private:
    QList<card> m_paidui;
    QList<card> m_qipaidui;
};
