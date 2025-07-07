#include "zhangfei.h"

zhangfei::zhangfei()
    : m_wujiangming{"张飞"}
    , m_tili{4}
    , m_tilishangxian{4}
    , m_shili{wujiang::Shu}
    , m_shoupaishangxian{4}
    , m_xingbie{wujiang::Nan}
{}

void zhangfei::jineng1(
    player *p, GameManager *g)
{
    p->addzhuangtai("Wu_Xian_Sha", 1);
}

void zhangfei::jineng2() {}

void zhangfei::jineng3() {}
