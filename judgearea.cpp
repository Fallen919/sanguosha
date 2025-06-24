#include "judgearea.h"

judgearea::judgearea(
    QObject *parent)
    : QObject{parent}
{}

void judgearea::addjudgarea(
    card *c)
{
    m_judgarea.push_back(c);
}

std::list<card *> judgearea::getjudgarea()
{
    return m_judgarea;
}
