#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "card.h"
#include "cards.h"
#include "paidui.h"
#include "carddex.h"
int main(int argc, char *argv[])
{
    qmlRegisterType<card>("Sanguosha.Core", 1, 0, "Card");

      qmlRegisterSingletonType(QUrl("qrc:/CardResources.qml"), "Sanguosha.Resources", 1, 0, "CardResources");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Carddex cardDex;
    engine.rootContext()->setContextProperty("cardDex", &cardDex);
   const QUrl url(QUrl::fromLocalFile("/root/sanguosha111/sha/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
