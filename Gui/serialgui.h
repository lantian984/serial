#ifndef SERIALGUI_H
#define SERIALGUI_H

#include <QWidget>
#include <QStringList>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class SerialGui;
}

class SerialGui : public QWidget
{
    Q_OBJECT
private:

    const QStringList baudList = {"9600","115200","921600"};
    const QStringList parityCheckList = {"无","奇校验","偶校验"};
    const QStringList stopBitList = {"1","1.5","2"};
    const QStringList dataBitList = {"8","7","6","5"};

    QString port;       //串口号
    QString baudRate;    //波特率
    QString parit;      //奇偶校验
    QString stopBit;    //停止位
    QString dataBit;    //数据位
private:
    explicit SerialGui(QWidget *parent = nullptr);
    ~SerialGui();

    void setPort(QString value);
    void setBautdRate(QString value);
    void setParit(QString value);
    void setStopBit(QString value);
    void setDataBit(QString value);
    void getSerialInfo();

public:
    QString getPort();
    QString getBautdRate();
    QString getParit();
    QString getStopBit();
    QString getDataBit();

public:
    static SerialGui *construction()
    {
        if (_serialGuiObj == nullptr)
        {
            _serialGuiObj = new SerialGui;
        }
        return _serialGuiObj;
    }

    static void deleteConstruction()
    {
        delete _serialGuiObj;
        _serialGuiObj = nullptr;
    }

signals:
    void serialGuiSerialOpenSinles( QString port, QString baudRate,QString parit,
                                    QString stopBit,QString dataBit);
    void serialGuiSerialCloseSinles();
    void serialGuiSerialSendSignals(QString value);
    void serialGuiSerialHexSignals(bool value);
    void serialGuiSerialOpenResultSignals(bool value);
private slots:
    void on_serialOpen_clicked();

    void on_serialClose_clicked();

    void on_serialSend_clicked();

    void on_hexCBox_stateChanged(int arg1);

public slots:
    void serialGuiSerialOpenResultSlots(bool value);
    void serialGuiShowText(QByteArray value);
private:
    Ui::SerialGui *ui;
    QStringList* list;
    static SerialGui* _serialGuiObj;
};



#define serialGui (SerialGui::construction())
#define deleteSerialGui() (SerialGui::deleteConstruction())
#endif // SERIALGUI_H
