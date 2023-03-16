#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFont>
#include <QFontDatabase>
#include <QList>
#include <QSurface>
#include <QScreen>
#include <QQmlComponent>
#include <QQuickWindow>
#include <key_press_emitter.h>

#include <config.h>

#ifdef RASPBERRY_PI
#include <dash.h>
#include <dash_new.h>
#else
#include <dash_host.h>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QList<QScreen *> screens = app.screens();
    qDebug("Application sees %d screens", screens.count());
    for (auto screen : screens) {
        qDebug() << "Screen: " << screen;
        qDebug() << screen->physicalSize();
        qDebug() << screen->availableSize();
        qDebug() << screen->availableSize();
    }

    QFontDatabase::addApplicationFont(":/fonts/HandelGothReg.ttf");
    QFont mFont;
    mFont.setFamily("Handel Gothic");
    app.setFont(mFont);

    //Setup QML
    QQmlApplicationEngine engine;
    QQmlContext * ctxt = engine.rootContext();

    // Initialize Dash
#ifdef RASPBERRY_PI
    //Dash * dash = new Dash(&app, ctxt); //old style dash
    DashNew * dash = new DashNew(&app, ctxt); // new scheme with sensor source -> sensor -> gauge -> model
    ctxt->setContextProperty("RASPBERRY_PI", QVariant(true));
    QObject::connect(dash, &DashNew::keyPress, [&engine](QKeyEvent * ev) {
        if (ev != nullptr) {
            QCoreApplication::postEvent(engine.rootObjects().first(), ev);
        }
    });

    dash->init();

    // load main.qml
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // connect quit
    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));

    if (screens.count() > 1) {
        QQuickWindow * accessoryWindow = engine.rootObjects()[0]->findChild<QQuickWindow *>("accessoryScreen");

        QScreen * screen = screens[1];
        screen->setOrientationUpdateMask(Qt::PortraitOrientation);

        accessoryWindow->setScreen(screen);
        accessoryWindow->setProperty("visible", true);
    }
#else
    DashHost * dash = new DashHost(&app, ctxt);
    ctxt->setContextProperty("RASPBERRY_PI", QVariant(false));

    QObject::connect(dash, &DashHost::keyPress, [&engine](QKeyEvent * ev) {
        if (ev != nullptr) {
            qDebug() << ev;
            QCoreApplication::postEvent(engine.rootObjects().first(), ev);
        }
    });

    dash->init();

    // load main.qml
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // connect quit
    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));

    QQuickWindow * accessoryWindow = engine.rootObjects()[0]->findChild<QQuickWindow *>("accessoryScreen");
    accessoryWindow->setWidth(480);
    accessoryWindow->setHeight(800);
    accessoryWindow->setProperty("visible", true);
#endif
    // Start Dash
    dash->start();

    return app.exec();
}
