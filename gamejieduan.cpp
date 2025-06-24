#include "gamejieduan.h"
#include "gamemanager.h"
void gamejieduan::setjieduan(
    Jieduan j)
{
    m_jieduan = j;
}

void gamejieduan::zhunbeijieduan(
    player *p)
{}

void gamejieduan::pandingjieduan(
    player *p)
{
    if (!(p->getjudg()->getjudgarea().empty())) {
        std::list<card *>::iterator it = p->getjudg()->getjudgarea().begin();
        for (int i = 0; i < (p->getjudg()->getjudgarea().size()); ++i) {
        }
    }
}

void gamejieduan::mopaijieduan(
    player *p, GameManager *g)
{
    p->mopai(2, g);
}

void gamejieduan::chupaijieduan(
    player *p)
{}

void gamejieduan::qipaijieduan(
    player *p)
{}

void gamejieduan::jieshujieduan(
    player *p)
{}

void gamejieduan::yihuihe(
    player *p, GameManager *g)
{
    zhunbeijieduan(p);
    pandingjieduan(p);
    mopaijieduan(p, g);
    chupaijieduan(p);
    qipaijieduan(p);
    jieshujieduan(p);
}

void gamejieduan::yilun(
    player *p, GameManager *g)
{
    for (int i = 0; i < p->getwanjiashu(); ++i) {
        yihuihe(p, g);
    }
}

gamejieduan::Jieduan gamejieduan::getjieduan()
{
    return m_jieduan;
}

gamejieduan::gamejieduan(
    QObject *parent)
    : QObject{parent}
{}

// void gamejieduan::gamestart(
//     player *p, Carddex *paidui)
// {
//     std::list<player *>::iterator it = p->().begin();
//     for (int i = 0; i < p->getwanjia().size(); ++i, ++it) {
//         for (int m = 0; m < 4; ++m) {
//             card cd = paidui->mopai();
//             (*it)->getcards()->add(cd);
//         }
//     }
// }
