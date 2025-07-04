#include "gamejieduan.h"
#include "gamemanager.h"
void gamejieduan::setjieduan(
    Jieduan j)
{
    m_jieduan = j;
}

void gamejieduan::zhunbeijieduan(
    player *p, GameManager *g)
{
    p->addzhuangtai("Zhun_Bei_Jie_Duan", 1);
}

void gamejieduan::pandingjieduan(
    player *p, GameManager *g)
{
    p->yichuzhuangtai("Zhun_Bei_Jie_Duan");
    p->addzhuangtai("Pan_Ding_Jie_Duan", 1);
    if (!(p->getjudg()->getjudgarea().empty())) {
        std::list<card *>::iterator it = p->getjudg()->getjudgarea().begin();
        for (int i = 0; i < (p->getjudg()->getjudgarea().size()); ++i, ++it) {
            card *cd = (*it);
            cd->xiaoguo(p, p, g);
        }
    }
}

void gamejieduan::mopaijieduan(
    player *p, GameManager *g)
{
    p->yichuzhuangtai("Pan_Ding_Jie_Duan");
    p->addzhuangtai("Mo_Pai_Jie_Duan", 1);
    p->mopai(2, g);
}

void gamejieduan::chupaijieduan(
    player *p, GameManager *g)
{
    p->yichuzhuangtai("Mo_Pai_Jie_Duan");
    p->addzhuangtai("Chu_Pai_Jie_Duan", 1);
}

void gamejieduan::qipaijieduan(
    player *p, GameManager *g)
{
    p->yichuzhuangtai("Chu_Pai_Jie_Duan");
    p->addzhuangtai("Qi_Pai_Jie_Duan", 1);
}

void gamejieduan::jieshujieduan(
    player *p, GameManager *g)
{
    p->yichuzhuangtai("Qi_Pai_Jie_Duan");
    p->addzhuangtai("Jie_Shu_Jie_Duan", 1);
}

void gamejieduan::huihejieshu(
    player *p, GameManager *g)
{
    p->yichuzhuangtai("Jie_Shu_Jie_Duan");
}

void gamejieduan::yihuihe(
    player *p, GameManager *g)
{
    zhunbeijieduan(p, g);
    pandingjieduan(p, g);
    mopaijieduan(p, g);
    chupaijieduan(p, g);
    qipaijieduan(p, g);
    jieshujieduan(p, g);
    huihejieshu(p, g);
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
