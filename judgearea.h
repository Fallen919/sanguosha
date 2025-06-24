#pragma once
#include "card.h"
#include <QObject>
#include <list>
class judgearea : public QObject
{
    Q_OBJECT
public:
    explicit judgearea(QObject *parent = nullptr);

    //判定区
    Q_INVOKABLE void addjudgarea(card *c);
    Q_INVOKABLE std::list<card *> getjudgarea();

private:
    std::list<card *> m_judgarea; //判定区的牌
signals:
};
