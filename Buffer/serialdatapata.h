#ifndef SERIALDATAPATA_H
#define SERIALDATAPATA_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QThread>

class SerialDataPata : public QObject
{
    Q_OBJECT
public:
    explicit SerialDataPata(QObject *parent = nullptr);
    ~SerialDataPata();
public:
    static SerialDataPata *construction()
    {
        if (_serialDataPataObj == nullptr)
        {
            _serialDataPataObj = new SerialDataPata;
        }
        return _serialDataPataObj;
    }

    static void deleteConstruction()
    {
        delete _serialDataPataObj;
        _serialDataPataObj = nullptr;
    }

signals:
    void serialDataPataSendSignal(QByteArray value);
    void finished();//完成信号
public slots:
    void serialDataPataAppendSlost(QByteArray value);
    void serialDataPataUnpakeSlost();
private:
    static SerialDataPata* _serialDataPataObj;
    QByteArray* dataByteArray;
};

#define serialDataPata (SerialDataPata::construction())
#define deleteSerialDataPata() (SerialDataPata::deleteConstruction())

#endif // SERIALDATAPATA_H
