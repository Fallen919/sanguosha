#pragma once
#include "player.h"
#include <QObject>
#include "carddex.h"
#include "judgearea.h"
#include "cards.h"
class GameManager;
class gamejieduan : public QObject
{
    Q_OBJECT
public:
    explicit gamejieduan(QObject *parent = nullptr);

    enum Jieduan {
        JieduanBegin,
        Zhunbeijieduan,
        Pandingjieduan,
        Mopaijieduan,
        Chupaijieduan,
        Qipaijieduan,
        Jieshujieduan,
    };

    // Q_INVOKABLE void gamestart(player *p, Carddex *paidui);

    Q_INVOKABLE void setjieduan(Jieduan j);
    Q_INVOKABLE Jieduan getjieduan();

    Q_INVOKABLE void zhunbeijieduan(player *p);

    Q_INVOKABLE void pandingjieduan(player *p);

    Q_INVOKABLE void mopaijieduan(player *p, GameManager *g);

    Q_INVOKABLE void chupaijieduan(player *p);

    Q_INVOKABLE void qipaijieduan(player *p);

    Q_INVOKABLE void jieshujieduan(player *p);

    Q_INVOKABLE void yihuihe(player *p, GameManager *g);

    Q_INVOKABLE void yilun(player *p, GameManager *g);

private:
    Jieduan m_jieduan;

signals:
};
