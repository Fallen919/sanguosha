#pragma once
#include "card.h"
#include <QObject>
#include <list>
class judgearea : public QObject
{
    Q_OBJECT
public:
    explicit judgearea(QObject *parent = nullptr);

    Q_INVOKABLE void addjudgarea(card c);
    Q_INVOKABLE std::list<card> getjudgarea();

private:
    std::list<card> m_judgarea;
signals:
};
