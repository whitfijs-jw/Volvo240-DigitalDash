#ifndef KEY_PRESS_EMITTER_H
#define KEY_PRESS_EMITTER_H

#include <QObject>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QKeyEvent>

class KeyPressEmitter : public QObject {
    Q_OBJECT
public:
    explicit KeyPressEmitter(QObject * parent = nullptr) :
        QObject(parent) {

    }

//    Q_INVOKABLE void keyPress(Qt::Key key) {
//        for (int i = 0; i < mEngine->rootObjects().length(); i++) {
//            QKeyEvent event = QKeyEvent(
//                        QEvent::Type::KeyPress,
//                        key,
//                        Qt::NoModifier
//                        );
//            QCoreApplication::sendEvent(mEngine->rootObjects().at(i), &event);
//        }
//    }

signals:
    Q_INVOKABLE void keyPress(Qt::Key key);
    Q_INVOKABLE void keyPressAndHold(Qt::Key key);
private:
};

#endif // KEY_PRESS_EMITTER_H
