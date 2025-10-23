#ifndef QT_SERIAL_HANDLER_H
#define QT_SERIAL_HANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include "qt_screen_sensors.h"


class QtSerialHandler : public QObject
{
    Q_OBJECT
public:
    explicit QtSerialHandler(QObject *parent = nullptr);
    // Q_INVOKABLE void openPort(const QString &portName);
    // Q_INVOKABLE void closePort();
    // Q_INVOKABLE void sendMessage(const QString &msg);

signals:

private slots:
    // void onReadyRead();

private:
    // QSerialPort serial;
    // QByteArray buffer;

    // void processData(const QString &data);
};

#endif // QT_SERIAL_HANDLER_H
