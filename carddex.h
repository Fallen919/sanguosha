#pragma once

#include <QObject>
#include <QList>
#include <QVariant>
#include "card.h"

class Carddex : public QObject {
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int discardCount READ discardCount NOTIFY discardCountChanged) // 弃牌堆

public:
    explicit Carddex(QObject *parent = nullptr);

    //初始化牌堆
    void initcarddex();

    //添加牌进入牌堆
    void add(card *cd);

    bool playCard(const QVariantMap &cardData);

    //洗牌
    void xipai();

    //将牌的信息输出到终端
    QVariant drawCard();

    //牌堆数量
    int count() const;

    int discardCount() const; // 获取弃牌堆数量

    //进入弃牌堆
    void jinruqipaidui(card *cd);

    //摸牌
    card *mopai();
    QVariantMap getTopDiscardCard(); // 获取弃牌堆顶部卡牌
    void addToDiscardPile(card *cd);
    card *removeFromDiscardPile(int index); //  从弃牌堆移除卡牌
    QList<card *> getDiscardPile() const;

    QList<card *> getpaidui();
    QList<card *> getqipaidui();

signals:
    void countChanged(int newCount);        // 牌数变化信号
    void discardCountChanged(int newCount); // 弃牌堆变化信号

private:
    QList<card *> m_paidui;
    QList<card *> m_qipaidui;
};
