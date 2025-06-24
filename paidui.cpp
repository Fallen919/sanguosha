#include "paidui.h"
#include <algorithm>
#include <random>
#include <chrono>
paidui::paidui()
{
    initpaidui();
    xipai();
    std::cout << m_paidui.size() << std ::endl;
    QList<card>::const_iterator it;

    for (it = m_paidui.constBegin(); it != m_paidui.constEnd(); ++it) {
        std::cout << it->getName() << std::endl;
    }
}

void paidui::add(card cd)
{
    m_paidui.append(cd);
}

void paidui::initpaidui()
{
    add({card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_7});
    add({card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_8});
    add({card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_8});
    add({card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_9});
    add({card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_9});
    add({card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_10});
    add({card::Sha, card::Ji_Ben, card::Hei_Tao, card::Card_10});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_2});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_3});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_4});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_5});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_6});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_7});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_8});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_8});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_9});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_9});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_10});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_10});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_J});
    add({card::Sha, card::Ji_Ben, card::Mei_Hua, card::Card_J});
    add({card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_6});
    add({card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_7});
    add({card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_8});
    add({card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_9});
    add({card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_10});
    add({card::Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_K});
    add({card::Sha, card::Ji_Ben, card::Hong_Tao, card::Card_10});
    add({card::Sha, card::Ji_Ben, card::Hong_Tao, card::Card_10});
    add({card::Sha, card::Ji_Ben, card::Hong_Tao, card::Card_J});
    add({card::Huo_Sha, card::Ji_Ben, card::Hong_Tao, card::Card_4});
    add({card::Huo_Sha, card::Ji_Ben, card::Hong_Tao, card::Card_7});
    add({card::Huo_Sha, card::Ji_Ben, card::Hong_Tao, card::Card_10});
    add({card::Huo_Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_4});
    add({card::Huo_Sha, card::Ji_Ben, card::Fang_Kuai, card::Card_5});
    add({card::Lei_Sha, card::Ji_Ben, card::Mei_Hua, card::Card_5});
    add({card::Lei_Sha, card::Ji_Ben, card::Mei_Hua, card::Card_6});
    add({card::Lei_Sha, card::Ji_Ben, card::Mei_Hua, card::Card_7});
    add({card::Lei_Sha, card::Ji_Ben, card::Mei_Hua, card::Card_8});
    add({card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_4});
    add({card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_5});
    add({card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_6});
    add({card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_7});
    add({card::Lei_Sha, card::Ji_Ben, card::Hei_Tao, card::Card_8});
    add({card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_2});
    add({card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_2});
    add({card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_8});
    add({card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_9});
    add({card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_J});
    add({card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_Q});
    add({card::Shan, card::Ji_Ben, card::Hong_Tao, card::Card_K});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_2});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_2});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_3});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_4});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_5});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_6});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_6});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_7});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_7});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_8});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_8});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_9});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_10});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_10});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_J});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_J});
    add({card::Shan, card::Ji_Ben, card::Fang_Kuai, card::Card_J});
    add({card::Tao, card::Ji_Ben, card::Fang_Kuai, card::Card_2});
    add({card::Tao, card::Ji_Ben, card::Fang_Kuai, card::Card_3});
    add({card::Tao, card::Ji_Ben, card::Fang_Kuai, card::Card_Q});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_3});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_4});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_5});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_6});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_6});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_7});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_8});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_9});
    add({card::Tao, card::Ji_Ben, card::Hong_Tao, card::Card_Q});
    add({card::Jiu, card::Ji_Ben, card::Mei_Hua, card::Card_3});
    add({card::Jiu, card::Ji_Ben, card::Mei_Hua, card::Card_9});
    add({card::Jiu, card::Ji_Ben, card::Fang_Kuai, card::Card_9});
    add({card::Jiu, card::Ji_Ben, card::Hei_Tao, card::Card_3});
    add({card::Jiu, card::Ji_Ben, card::Hei_Tao, card::Card_9});
    add({card::Wu_Zhongshengyou, card::Jing_Nang, card::Hong_Tao, card::Card_7});
    add({card::Wu_Zhongshengyou, card::Jing_Nang, card::Hong_Tao, card::Card_8});
    add({card::Wu_Zhongshengyou, card::Jing_Nang, card::Hong_Tao, card::Card_9});
    add({card::Wu_Zhongshengyou, card::Jing_Nang, card::Hong_Tao, card::Card_J});
    add({card::Wu_Gufengdeng, card::Jing_Nang, card::Hong_Tao, card::Card_3});
    add({card::Wu_Gufengdeng, card::Jing_Nang, card::Hong_Tao, card::Card_4});
    add({card::Tao_yuanjieyi, card::Jing_Nang, card::Hong_Tao, card::Card_A});
    add({card::Wan_jianqifa, card::Jing_Nang, card::Hong_Tao, card::Card_A});
    add({card::Huo_Gong, card::Jing_Nang, card::Hong_Tao, card::Card_2});
    add({card::Huo_Gong, card::Jing_Nang, card::Hong_Tao, card::Card_3});
    add({card::Huo_Gong, card::Jing_Nang, card::Fang_Kuai, card::Card_Q});
    add({card::Nan_Manruqin, card::Jing_Nang, card::Hei_Tao, card::Card_7});
    add({card::Nan_Manruqin, card::Jing_Nang, card::Hei_Tao, card::Card_K});
    add({card::Nan_Manruqin, card::Jing_Nang, card::Mei_Hua, card::Card_7});
    add({card::Jie_Daosharen, card::Jing_Nang, card::Mei_Hua, card::Card_Q});
    add({card::Jie_Daosharen, card::Jing_Nang, card::Mei_Hua, card::Card_K});
    add({card::Bing_Niangchunduan, card::Jing_Nang, card::Mei_Hua, card::Card_4});
    add({card::Bing_Niangchunduan, card::Jing_Nang, card::Hei_Tao, card::Card_10});
    add({card::Le_Busishu, card::Jing_Nang, card::Mei_Hua, card::Card_6});
    add({card::Le_Busishu, card::Jing_Nang, card::Hong_Tao, card::Card_6});
    add({card::Le_Busishu, card::Jing_Nang, card::Hei_Tao, card::Card_6});
    add({card::Jue_Dou, card::Jing_Nang, card::Mei_Hua, card::Card_A});
    add({card::Jue_Dou, card::Jing_Nang, card::Fang_Kuai, card::Card_A});
    add({card::Jue_Dou, card::Jing_Nang, card::Hei_Tao, card::Card_A});
    add({card::Wu_Xiekeji, card::Jing_Nang, card::Mei_Hua, card::Card_Q});
    add({card::Wu_Xiekeji, card::Jing_Nang, card::Mei_Hua, card::Card_K});
    add({card::Wu_Xiekeji, card::Jing_Nang, card::Hong_Tao, card::Card_A});
    add({card::Wu_Xiekeji, card::Jing_Nang, card::Hong_Tao, card::Card_K});
    add({card::Wu_Xiekeji, card::Jing_Nang, card::Fang_Kuai, card::Card_Q});
    add({card::Wu_Xiekeji, card::Jing_Nang, card::Hei_Tao, card::Card_J});
    add({card::Wu_Xiekeji, card::Jing_Nang, card::Hei_Tao, card::Card_K});
    add({card::Guo_Hechaiqiao, card::Jing_Nang, card::Hei_Tao, card::Card_3});
    add({card::Guo_Hechaiqiao, card::Jing_Nang, card::Hei_Tao, card::Card_4});
    add({card::Guo_Hechaiqiao, card::Jing_Nang, card::Mei_Hua, card::Card_3});
    add({card::Guo_Hechaiqiao, card::Jing_Nang, card::Mei_Hua, card::Card_4});
    add({card::Guo_Hechaiqiao, card::Jing_Nang, card::Hei_Tao, card::Card_Q});
    add({card::Guo_Hechaiqiao, card::Jing_Nang, card::Hong_Tao, card::Card_Q});
    add({card::Shun_Shouqianyang, card::Jing_Nang, card::Hei_Tao, card::Card_3});
    add({card::Shun_Shouqianyang, card::Jing_Nang, card::Hei_Tao, card::Card_4});
    add({card::Shun_Shouqianyang, card::Jing_Nang, card::Hei_Tao, card::Card_J});
    add({card::Shun_Shouqianyang, card::Jing_Nang, card::Fang_Kuai, card::Card_3});
    add({card::Shun_Shouqianyang, card::Jing_Nang, card::Fang_Kuai, card::Card_4});
    add({card::Tie_Suolianhuan, card::Jing_Nang, card::Hei_Tao, card::Card_J});
    add({card::Tie_Suolianhuan, card::Jing_Nang, card::Hei_Tao, card::Card_Q});
    add({card::Tie_Suolianhuan, card::Jing_Nang, card::Mei_Hua, card::Card_10});
    add({card::Tie_Suolianhuan, card::Jing_Nang, card::Mei_Hua, card::Card_J});
    add({card::Tie_Suolianhuan, card::Jing_Nang, card::Mei_Hua, card::Card_Q});
    add({card::Tie_Suolianhuan, card::Jing_Nang, card::Mei_Hua, card::Card_K});
    add({card::Shan_Dian, card::Jing_Nang, card::Hei_Tao, card::Card_A});
    add({card::Shan_Dian, card::Jing_Nang, card::Hong_Tao, card::Card_Q});
    add({card::Zhu_Geliannv, card::Zhuang_Bei, card::Mei_Hua, card::Card_A});
    add({card::Zhu_Geliannv, card::Zhuang_Bei, card::Fang_Kuai, card::Card_A});
    add({card::Chi_Xiongshuanggujian, card::Zhuang_Bei, card::Hei_Tao, card::Card_2});
    add({card::Han_Bingjian, card::Zhuang_Bei, card::Hei_Tao, card::Card_2});
    add({card::Fang_Tianhuaji, card::Zhuang_Bei, card::Fang_Kuai, card::Card_Q});
    add({card::Zhu_Queyushan, card::Zhuang_Bei, card::Fang_Kuai, card::Card_A});
    add({card::Zhang_Bashemao, card::Zhuang_Bei, card::Hei_Tao, card::Card_Q});
    add({card::Gu_Dingdao, card::Zhuang_Bei, card::Hei_Tao, card::Card_A});
    add({card::Guan_Shifu, card::Zhuang_Bei, card::Fang_Kuai, card::Card_5});
    add({card::Qi_Linggong, card::Zhuang_Bei, card::Hong_Tao, card::Card_5});
    add({card::Qing_Longyanyuedao, card::Zhuang_Bei, card::Hei_Tao, card::Card_5});
    add({card::Qing_Gangjian, card::Zhuang_Bei, card::Hei_Tao, card::Card_6});
    add({card::Ba_Guazhen, card::Zhuang_Bei, card::Hei_Tao, card::Card_2});
    add({card::Ba_Guazhen, card::Zhuang_Bei, card::Mei_Hua, card::Card_2});
    add({card::Ten_Jia, card::Zhuang_Bei, card::Hei_Tao, card::Card_2});
    add({card::Ten_Jia, card::Zhuang_Bei, card::Mei_Hua, card::Card_2});
    add({card::Ren_Wangdun, card::Zhuang_Bei, card::Mei_Hua, card::Card_2});
    add({card::Bai_Yingshizi, card::Zhuang_Bei, card::Mei_Hua, card::Card_A});
    add({card::Fang_Yuma, card::Zhuang_Bei, card::Mei_Hua, card::Card_5});
    add({card::Fang_Yuma, card::Zhuang_Bei, card::Hei_Tao, card::Card_5});
    add({card::Fang_Yuma, card::Zhuang_Bei, card::Hong_Tao, card::Card_K});
    add({card::Fang_Yuma, card::Zhuang_Bei, card::Fang_Kuai, card::Card_K});
    add({card::Jing_Gongma, card::Zhuang_Bei, card::Hong_Tao, card::Card_5});
    add({card::Jing_Gongma, card::Zhuang_Bei, card::Fang_Kuai, card::Card_K});
    add({card::Jing_Gongma, card::Zhuang_Bei, card::Hei_Tao, card::Card_K});
}

void paidui::xipai()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine engine(seed);

    for (int i = m_paidui.size() - 1; i > 0; --i) {
        std::uniform_int_distribution<int> distribution(0, i);
        int j = distribution(engine);

        std::swap(m_paidui[i], m_paidui[j]);
    }
}
