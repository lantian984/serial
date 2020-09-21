#include "serialgui.h"
#include "ui_serialgui.h"
#include <QThread>
SerialGui *SerialGui::_serialGuiObj = nullptr;


SerialGui::SerialGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialGui)
{
    ui->setupUi(this);


    ui->serialBaud->addItems(baudList);
    ui->serialCheck->addItems(parityCheckList);
    ui->serialStopBit->addItems(stopBitList);
    ui->serialDataBit->addItems(dataBitList);
    getSerialInfo();

    list = new QStringList();
}

SerialGui::~SerialGui()
{
    delete list;
    delete ui;
}

void SerialGui::setPort(QString value)
{
    port = value;
}

void SerialGui::setBautdRate(QString value)
{
    baudRate = value;
}

void SerialGui::setParit(QString value)
{
    parit = value;
}

void SerialGui::setStopBit(QString value)
{
    stopBit = value;
}

void SerialGui::setDataBit(QString value)
{
    dataBit = value;
}

void SerialGui::getSerialInfo()
{
    ui->serialPort->clear();
    //获取可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->serialPort->addItem(info.portName());
    }

}

QString SerialGui::getPort()
{
    return port;
}

QString SerialGui::getBautdRate()
{
    return baudRate;
}

QString SerialGui::getParit()
{
    return parit;
}

QString SerialGui::getStopBit()
{
    return stopBit;
}

QString SerialGui::getDataBit()
{
    return dataBit;
}

void SerialGui::on_serialOpen_clicked()
{
    setPort(ui->serialPort->currentText());     //设置串口号
    setBautdRate(ui->serialBaud->currentText());    //设置波特率
    setParit(ui->serialCheck->currentText());   //设置校验
    setDataBit(ui->serialDataBit->currentText());   //设置数据位
    setStopBit(ui->serialStopBit->currentText());   //设置校验

    emit serialGuiSerialOpenSinles(getPort(),getBautdRate(),getParit(),getStopBit(),getDataBit());
}

void SerialGui::on_serialClose_clicked()
{
    ui->serialOpen->setEnabled(true);
    ui->serialClose->setEnabled(false);
    emit serialGuiSerialCloseSinles();
}

void SerialGui::serialGuiSerialOpenResultSlots(bool value)
{
    if(value != true){
         QMessageBox::about(NULL, "提示", "无法打开串口！");
         ui->serialOpen->setEnabled(true);
         ui->serialClose->setEnabled(false);
         return;
    }
    ui->serialOpen->setEnabled(false);
    ui->serialClose->setEnabled(true);
    qDebug()<<"gui线程 ID:" <<QThread::currentThreadId();
}

void SerialGui::serialGuiShowText(QByteArray value)
{
    ui->showText->clear();
    if(list->count() > 50){
        list->removeFirst();
    }
    list->append(QString(value));
    for (int i = 0;i < list->count();i++) {
           ui->showText->append(list->at(i));
    }
}

void SerialGui::on_serialSend_clicked()
{
    QString value = ui->sendText->toPlainText();
    emit serialGuiSerialSendSignals(value);
}

void SerialGui::on_hexCBox_stateChanged(int arg1)
{
    if(Qt::Checked == arg1){
        emit serialGuiSerialHexSignals(true);
    }else{
        emit serialGuiSerialHexSignals(false);
    }
}

