QT += quick

SOURCES += \
        card.cpp \
        carddex.cpp \
        cardpanel.cpp \
        cards.cpp \
        daweiwuwang.cpp \
        gamejieduan.cpp \
        gamemanager.cpp \
        judgearea.cpp \
        main.cpp \
        player.cpp \
        wujiang.cpp \
        zhuangbeiqu.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources \
    resource.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    card.h \
    carddex.h \
    cardpanel.h \
    cards.h \
    daweiwuwang.h \
    gamejieduan.h \
    gamemanager.h \
    judgearea.h \
    player.h \
    wujiang.h \
    zhuangbeiqu.h

DISTFILES += \
    CardItem.qml \
    CardResources.qml \
    GameScreen.qml \
    MainMenu.qml \
    PlayerArea.qml \
    SettingsScreen.qml \
    huosha.PNG
