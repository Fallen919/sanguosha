#include "carddex.h"
#include <algorithm>
#include <random>
#include <chrono>
Carddex::Carddex (QObject *parent) : QObject{parent}{
    initcarddex();
    xipai();
    std::cout << "sb" << std::endl;
    //std::cout << m_paidui.size() << std ::endl;
}

void Carddex::add(
    card *cd)
{
    m_paidui.append(cd);
}

void Carddex::initcarddex()
{
    add(new card{card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_7});
    add(new card{card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_8});
    add(new card{card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_8});
    add(new card{card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_9});
    add(new card{card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_9});
    add(new card{card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_10});
    add(new card{card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_10});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_2});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_3});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_4});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_5});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_6});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_7});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_8});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_8});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_9});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_9});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_10});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_10});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_J});
    add(new card{card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_J});
    add(new card{card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_6});
    add(new card{card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_7});
    add(new card{card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_8});
    add(new card{card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_9});
    add(new card{card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_10});
    add(new card{card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_K});
    add(new card{card::Sha, card::Ji_Ben, card::Hong_Tao, card::Card_10});
    add(new card{card::Sha, card::Ji_Ben, card::Hong_Tao, card::Card_10});
    add(new card{card::Sha, card::Ji_Ben, card::Hong_Tao, card::Card_J});
    add(new card{card::Huo_Sha, card::Ji_Ben, card::Hong_Tao, card::Card_4});
    add(new card{card::Huo_Sha, card::Ji_Ben, card::Hong_Tao, card::Card_7});
    add(new card{card::Huo_Sha, card::Ji_Ben, card::Hong_Tao, card::Card_10});
    add(new card{card::Huo_Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_4});
    add(new card{card::Huo_Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_5});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Mei_Hua, card::Card_5});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Mei_Hua, card::Card_6});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Mei_Hua, card::Card_7});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Mei_Hua, card::Card_8});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_4});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_5});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_6});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_7});
    add(new card{card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_8});
    add(new card{card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_2});
    add(new card{card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_2});
    add(new card{card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_8});
    add(new card{card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_9});
    add(new card{card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_J});
    add(new card{card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_Q});
    add(new card{card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_K});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_2});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_2});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_3});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_4});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_5});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_6});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_6});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_7});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_7});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_8});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_8});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_9});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_10});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_10});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_J});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_J});
    add(new card{card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_J});
    add(new card{card::Tao, card::Ji_Ben, card::Fang_Kuai, card::Card_2});
    add(new card{card::Tao, card::Ji_Ben, card::Fang_Kuai, card::Card_3});
    add(new card{card::Tao, card::Ji_Ben, card::Fang_Kuai, card::Card_Q});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_3});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_4});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_5});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_6});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_6});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_7});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_8});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_9});
    add(new card{card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_Q});
    add(new card{card::Jiu, card::Ji_Ben, card::Mei_Hua, card::Card_3});
    add(new card{card::Jiu, card::Ji_Ben, card::Mei_Hua, card::Card_9});
    add(new card{card::Jiu, card::Ji_Ben, card::Fang_Kuai, card::Card_9});
    add(new card{card::Jiu, card::Ji_Ben, card::Hei_Tao, card::Card_3});
    add(new card{card::Jiu, card::Ji_Ben, card::Hei_Tao, card::Card_9});
    add(new card{card::Wu_Zhongshengyou, card::Jing_Nang, card::Hong_Tao, card::Card_7});
    add(new card{card::Wu_Zhongshengyou, card::Jing_Nang, card::Hong_Tao, card::Card_8});
    add(new card{card::Wu_Zhongshengyou, card::Jing_Nang, card::Hong_Tao, card::Card_9});
    add(new card{card::Wu_Zhongshengyou, card::Jing_Nang, card::Hong_Tao, card::Card_J});
    add(new card{card::Wu_Gufengdeng, card::Jing_Nang, card::Hong_Tao, card::Card_3});
    add(new card{card::Wu_Gufengdeng, card::Jing_Nang, card::Hong_Tao, card::Card_4});
    add(new card{card::Tao_yuanjieyi, card::Jing_Nang, card::Hong_Tao, card::Card_A});
    add(new card{card::Wan_jianqifa, card::Jing_Nang, card::Hong_Tao, card::Card_A});
    add(new card{card::Huo_Gong, card::Jing_Nang, card::Hong_Tao, card::Card_2});
    add(new card{card::Huo_Gong, card::Jing_Nang, card::Hong_Tao, card::Card_3});
    add(new card{card::Huo_Gong, card::Jing_Nang, card::Fang_Kuai, card::Card_Q});
    add(new card{card::Nan_Manruqin, card::Jing_Nang, card::Hei_Tao, card::Card_7});
    add(new card{card::Nan_Manruqin, card::Jing_Nang, card::Hei_Tao, card::Card_K});
    add(new card{card::Nan_Manruqin, card::Jing_Nang, card::Mei_Hua, card::Card_7});
    add(new card{card::Jie_Daosharen, card::Jing_Nang, card::Mei_Hua, card::Card_Q});
    add(new card{card::Jie_Daosharen, card::Jing_Nang, card::Mei_Hua, card::Card_K});
    add(new card{card::Bing_Niangchunduan, card::Jing_Nang, card::Mei_Hua, card::Card_4});
    add(new card{card::Bing_Niangchunduan, card::Jing_Nang, card::Hei_Tao, card::Card_10});
    add(new card{card::Le_Busishu, card::Jing_Nang, card::Mei_Hua, card::Card_6});
    add(new card{card::Le_Busishu, card::Jing_Nang, card::Hong_Tao, card::Card_6});
    add(new card{card::Le_Busishu, card::Jing_Nang, card::Hei_Tao, card::Card_6});
    add(new card{card::Jue_Dou, card::Jing_Nang, card::Mei_Hua, card::Card_A});
    add(new card{card::Jue_Dou, card::Jing_Nang, card::Fang_Kuai, card::Card_A});
    add(new card{card::Jue_Dou, card::Jing_Nang, card::Hei_Tao, card::Card_A});
    add(new card{card::Wu_Xiekeji, card::Jing_Nang, card::Mei_Hua, card::Card_Q});
    add(new card{card::Wu_Xiekeji, card::Jing_Nang, card::Mei_Hua, card::Card_K});
    add(new card{card::Wu_Xiekeji, card::Jing_Nang, card::Hong_Tao, card::Card_A});
    add(new card{card::Wu_Xiekeji, card::Jing_Nang, card::Hong_Tao, card::Card_K});
    add(new card{card::Wu_Xiekeji, card::Jing_Nang, card::Fang_Kuai, card::Card_Q});
    add(new card{card::Wu_Xiekeji, card::Jing_Nang, card::Hei_Tao, card::Card_J});
    add(new card{card::Wu_Xiekeji, card::Jing_Nang, card::Hei_Tao, card::Card_K});
    add(new card{card::Guo_Hechaiqiao, card::Jing_Nang, card::Hei_Tao, card::Card_3});
    add(new card{card::Guo_Hechaiqiao, card::Jing_Nang, card::Hei_Tao, card::Card_4});
    add(new card{card::Guo_Hechaiqiao, card::Jing_Nang, card::Mei_Hua, card::Card_3});
    add(new card{card::Guo_Hechaiqiao, card::Jing_Nang, card::Mei_Hua, card::Card_4});
    add(new card{card::Guo_Hechaiqiao, card::Jing_Nang, card::Hei_Tao, card::Card_Q});
    add(new card{card::Guo_Hechaiqiao, card::Jing_Nang, card::Hong_Tao, card::Card_Q});
    add(new card{card::Shun_Shouqianyang, card::Jing_Nang, card::Hei_Tao, card::Card_3});
    add(new card{card::Shun_Shouqianyang, card::Jing_Nang, card::Hei_Tao, card::Card_4});
    add(new card{card::Shun_Shouqianyang, card::Jing_Nang, card::Hei_Tao, card::Card_J});
    add(new card{card::Shun_Shouqianyang, card::Jing_Nang, card::Fang_Kuai, card::Card_3});
    add(new card{card::Shun_Shouqianyang, card::Jing_Nang, card::Fang_Kuai, card::Card_4});
    add(new card{card::Tie_Suolianhuan, card::Jing_Nang, card::Hei_Tao, card::Card_J});
    add(new card{card::Tie_Suolianhuan, card::Jing_Nang, card::Hei_Tao, card::Card_Q});
    add(new card{card::Tie_Suolianhuan, card::Jing_Nang, card::Mei_Hua, card::Card_10});
    add(new card{card::Tie_Suolianhuan, card::Jing_Nang, card::Mei_Hua, card::Card_J});
    add(new card{card::Tie_Suolianhuan, card::Jing_Nang, card::Mei_Hua, card::Card_Q});
    add(new card{card::Tie_Suolianhuan, card::Jing_Nang, card::Mei_Hua, card::Card_K});
    add(new card{card::Shan_Dian, card::Jing_Nang, card::Hei_Tao, card::Card_A});
    add(new card{card::Shan_Dian, card::Jing_Nang, card::Hong_Tao, card::Card_Q});
    add(new card{card::Zhu_Geliannv, card::Zhuang_Bei, card::Mei_Hua, card::Card_A});
    add(new card{card::Zhu_Geliannv, card::Zhuang_Bei, card::Fang_Kuai, card::Card_A});
    add(new card{card::Ci_Xiongshuanggujian, card::Zhuang_Bei, card::Hei_Tao, card::Card_2});
    add(new card{card::Han_Bingjian, card::Zhuang_Bei, card::Hei_Tao, card::Card_2});
    add(new card{card::Fang_Tianhuaji, card::Zhuang_Bei, card::Fang_Kuai, card::Card_Q});
    add(new card{card::Zhu_Queyushan, card::Zhuang_Bei, card::Fang_Kuai, card::Card_A});
    add(new card{card::Zhang_Bashemao, card::Zhuang_Bei, card::Hei_Tao, card::Card_Q});
    add(new card{card::Gu_Dingdao, card::Zhuang_Bei, card::Hei_Tao, card::Card_A});
    add(new card{card::Guan_Shifu, card::Zhuang_Bei, card::Fang_Kuai, card::Card_5});
    add(new card{card::Qi_Linggong, card::Zhuang_Bei, card::Hong_Tao, card::Card_5});
    add(new card{card::Qing_Longyanyuedao, card::Zhuang_Bei, card::Hei_Tao, card::Card_5});
    add(new card{card::Qing_Gangjian, card::Zhuang_Bei, card::Hei_Tao, card::Card_6});
    add(new card{card::Ba_Guazhen, card::Zhuang_Bei, card::Hei_Tao, card::Card_2});
    add(new card{card::Ba_Guazhen, card::Zhuang_Bei, card::Mei_Hua, card::Card_2});
    add(new card{card::Teng_Jia, card::Zhuang_Bei, card::Hei_Tao, card::Card_2});
    add(new card{card::Teng_Jia, card::Zhuang_Bei, card::Mei_Hua, card::Card_2});
    add(new card{card::Ren_Wangdun, card::Zhuang_Bei, card::Mei_Hua, card::Card_2});
    add(new card{card::Bai_Yingshizi, card::Zhuang_Bei, card::Mei_Hua, card::Card_A});
    add(new card{card::Fang_Yuma, card::Zhuang_Bei, card::Mei_Hua, card::Card_5});
    add(new card{card::Fang_Yuma, card::Zhuang_Bei, card::Hei_Tao, card::Card_5});
    add(new card{card::Fang_Yuma, card::Zhuang_Bei, card::Hong_Tao, card::Card_K});
    add(new card{card::Fang_Yuma, card::Zhuang_Bei, card::Fang_Kuai, card::Card_K});
    add(new card{card::Jing_Gongma, card::Zhuang_Bei, card::Hong_Tao, card::Card_5});
    add(new card{card::Jing_Gongma, card::Zhuang_Bei, card::Fang_Kuai, card::Card_K});
    add(new card{card::Jing_Gongma, card::Zhuang_Bei, card::Hei_Tao, card::Card_K});
}

int Carddex::count() const {
    return m_paidui.size();
}


void Carddex::xipai() {
    std::cout << "洗牌前 - m_paidui大小: " << m_paidui.size()
              << ", m_qipaidui大小: " << m_qipaidui.size() << std::endl;

    m_paidui.append(m_qipaidui);
    m_qipaidui.clear();

    std::cout << "洗牌后 - m_paidui大小: " << m_paidui.size()
              << "m_qipaidui大小:" << m_qipaidui.size() << std::endl;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_paidui.begin(), m_paidui.end(), std::default_random_engine(seed));
}
QVariant Carddex::drawCard() {
    emit countChanged(count()); // 通知 QML 牌堆数量变化

    QVariantMap cardData;

    card *drawnCard = m_paidui.first();
    cardData["name"] = drawnCard->NewGetName();
    cardData["suit"] = drawnCard->getSuit();
    cardData["point"] = drawnCard->getPoint();
    cardData["type"] = drawnCard->getType();

    qDebug() << "抽到的卡牌信息:";
    qDebug() << "名称:" << cardData["name"].toString();
    qDebug() << "花色:" << cardData["suit"].toString();
    qDebug() << "点数:" << cardData["point"].toInt();
    qDebug() << "类型:" << cardData["type"].toString();


    return cardData;

}

card *Carddex::mopai()
{
    if (m_paidui.isEmpty()) {
        if (!m_qipaidui.isEmpty())
            Carddex::xipai();
    }
    Carddex::drawCard();
    card *cd = m_paidui.takeFirst();
    return cd;
}
int Carddex::discardCount() const {
    return m_qipaidui.size();
}
void Carddex::jinruqipaidui(
    card *cd)
{
    m_qipaidui.append(cd);
    emit discardCountChanged(discardCount());
}
void Carddex::addToDiscardPile(
    card *cd)
{
    m_qipaidui.append(cd);
    emit discardCountChanged(discardCount());
}

card *Carddex::removeFromDiscardPile(
    int index)
{
    if (index < 0 || index >= m_qipaidui.size()) {
        // 返回无效卡牌
    }
    card *c = m_qipaidui.takeAt(index);
    emit discardCountChanged(discardCount());
    return c;
}

QList<card *> Carddex::getDiscardPile() const
{
    return m_qipaidui;
}

QList<card *> Carddex::getpaidui()
{
    return m_paidui;
}

QList<card *> Carddex::getqipaidui()
{
    return m_qipaidui;
}

QVariantMap Carddex::getTopDiscardCard() {
    QVariantMap cardData;

    if (m_qipaidui.isEmpty()) {
        return cardData;
    }

    card *topCard = m_qipaidui.last();
    cardData["name"] = topCard->NewGetName();
    cardData["suit"] = topCard->getSuit();
    cardData["point"] = topCard->getPoint();
    cardData["type"] = topCard->getType();

    return cardData;
}
bool Carddex::playCard(const QVariantMap &cardData) {
    // 这里实现卡牌效果逻辑
    QString cardName = cardData["name"].toString();
    qDebug() << "Playing card:" << cardName;
    return true;
}
