#ifndef SERIALTOOL_H
#define SERIALTOOL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtDebug>
#include <QThread>
class SerialTool : public QObject
{
    Q_OBJECT
private:
    explicit SerialTool(QObject *parent = nullptr);
    ~SerialTool();

    void setPort();
    void setBautdRate();
    void setParit();
    void setStopBit();
    void setDataBit();
    char ConvertHexChar(char ch);
    void StringToHex(QString str, QByteArray &senddata);
    bool getHexFlag();

public:
    static SerialTool *construction()
    {
        if (_serialToolObj == nullptr)
        {
            _serialToolObj = new SerialTool;
        }
        return _serialToolObj;
    }

    static void deleteConstruction()
    {
        delete _serialToolObj;
        _serialToolObj = nullptr;
    }


signals:

    void finished();//完成信号
    void serialToolSerialOpenResult(bool value);
    void serialToolSreialReadResult(QByteArray value);
public slots:
    void serialToolSerialOpenSlos(QString port, QString baudRate, QString parit, QString stopBit, QString dataBit);
    void serialToolSerialCloseSlos();
    void serialToolWrite(QString value);
    void serialToolRead();
    void serialToolHexFlagSlots(bool value);
private:

    static SerialTool* _serialToolObj;
    QSerialPort* serial = nullptr;
    QString port;
    QString baudRate;
    QString parit;
    QString stopBit;
    QString dataBit;

    bool hexFlag = false;
};


#define serialTool (SerialTool::construction())
#define deleteSerialTool() (SerialTool::deleteConstruction())

#endif // SERIALTOOL_H
