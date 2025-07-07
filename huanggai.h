#pragma once
#include "wujiang.h"

#include <QObject>

class player;
class GameManager;
class huanggai : public wujiang
{
    Q_OBJECT
public:
    huanggai();
    Q_INVOKABLE void virtual jineng1(QObject *playerObj, QObject *gameManagerObj);

    Q_INVOKABLE void virtual jineng2() override;

    Q_INVOKABLE void virtual jineng3() override;
    Q_INVOKABLE void executeZhiheng(QList<card *> cardsToDiscard, QObject *g) override;
    Q_INVOKABLE std::string getwujiangming() const override { return m_wujiangming; }
    virtual ~huanggai() override;

private:
    std::string m_wujiangming;
    int m_tili;
    int m_tilishangxian;
    int m_shoupaishu;
    int m_shoupaishangxian;
    wujiang::WujiangShili m_shili;
    wujiang::Xingbie m_xingbie;

signals:
    void kurouUsed(); // 苦肉技能使用信号
};
