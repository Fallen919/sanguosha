// CardResources.qml
pragma Singleton
import QtQuick

QtObject {
    property var cardFrontImages: {
        "Sha": "qrc:/sha.webp",
        "Tao":"qrc:/tao.jpg",
        "Shan":"qrc:/shan.webp",
        "Jiu":"qrc:/jiu.jpeg",
        "Sha_Hei_Tao": "qrc:/sha.webp",
        "Sha_Hong_Tao": "qrc:/sha.webp",
        "Shan_Hei_Tao": " qrc:/sha.webp",
        // 其他卡牌图片
        "default": "qrc:/images/default.png"
    }

    property var suitColors: {
        "Hei_Tao": "qrc:/heitao.webp",
        "Hong_Tao": "qrc:/hongtao.webp",
        "Mei_Hua": "qrc:/meihua.jpg",
        "Fang_Kuai": "qrc:/fangkuai.webp"
    }
}
