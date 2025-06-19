#pragma once
#include "wujiang.h"
#include "gamejieduan.h"
class daweiwuwang : public wujiang
{
    Q_OBJECT
public:
    daweiwuwang();

    Q_INVOKABLE void virtual jineng1(gamejieduan *l);

    Q_INVOKABLE void virtual jineng2();

    Q_INVOKABLE void virtual jineng3();

private:
    std::string m_wujiangming;
    int m_tili;
    int m_tilishangxian;
    int m_shoupaishu;
    int m_shoupaishangxian;
    wujiang::WujiangShili m_shili;
    wujiang::Xingbie m_xingbie;
    bool is_usejineng1;
};
