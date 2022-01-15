#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QFont>
#include <QFile>
#include <QColor>
#include <QTextStream>
#include <QFontDatabase>
#include <QString>
#include <QtMath>
#include <QList>

#include <QNmeaPositionInfoSource>
#include <QGeoPositionInfoSource>

#include <config.h>
#include <gps_helper.h>
#include <dash.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/HandelGothReg.ttf");
    QFont mFont;
    mFont.setFamily("Handel Gothic");
    app.setFont(mFont);

    //Setup QML
    QQmlApplicationEngine engine;
    QQmlContext * ctxt = engine.rootContext();

    // Initialize Dash
    Dash * dash = new Dash(&app, ctxt);
    qDebug() << "Dash setup: " << dash;
    dash->init();

    // load main.qml
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // connect quit
    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));

    // Start Dash
    dash->start();

    return app.exec();
}
