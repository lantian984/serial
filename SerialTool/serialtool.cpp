#include "serialtool.h"


SerialTool *SerialTool::_serialToolObj = nullptr;

SerialTool::SerialTool(QObject *parent) : QObject(parent)
{

}

SerialTool::~SerialTool()
{
    delete  serial;
}

void SerialTool::setPort()
{
    if(serial == nullptr){
        return;
    }
    if(port.isEmpty()){
        return;
    }
    serial->setPortName(port);
    qDebug() << "串口名设置为：" << port;
}

void SerialTool::setBautdRate()
{
    qint32 baud;
    if(baudRate.isEmpty()){
        return;
    }
    baud = (qint32)baudRate.toInt();
    if(serial != nullptr){
        serial->setBaudRate(baud);
        qDebug() << "波特率设置为：" << baud;
    }
}

void SerialTool::setParit()
{
    if(serial == nullptr){
        return;
    }
    if(stopBit.isEmpty()){
        return;
    }
    if(parit == "无"){
        serial->setParity(QSerialPort::NoParity);
    }else if(parit == "奇校验"){
        serial->setParity(QSerialPort::OddParity);
    }else if(parit == "偶校验"){
        serial->setParity(QSerialPort::EvenParity);
    }
     qDebug() << "校验位设置为：" << parit;
}

void SerialTool::setStopBit()
{
    if(serial == nullptr){
        return;
    }
    if(stopBit.isEmpty()){
        return;
    }
    if(stopBit == "无"){
        serial->setStopBits(QSerialPort::UnknownStopBits);
    }else if(stopBit == "1"){
        serial->setStopBits(QSerialPort::OneStop);
    }else if(stopBit == "1.5"){
        serial->setStopBits(QSerialPort::OneAndHalfStop);
    }else if(stopBit == "2"){
        serial->setStopBits(QSerialPort::TwoStop);
    }
    qDebug() << "停止位设置为：" << stopBit;
}

void SerialTool::setDataBit()
{
    if(dataBit.isEmpty()){
        return;
    }
    if(serial == nullptr){
        return;
    }
    if(dataBit == "8"){
        serial->setDataBits(QSerialPort::Data8);
    }else if(dataBit == "7"){
        serial->setDataBits(QSerialPort::Data7);
    }else if(dataBit == "6"){
        serial->setDataBits(QSerialPort::Data6);
    }else if(dataBit == "5"){
        serial->setDataBits(QSerialPort::Data5);
    }
    qDebug() << "数据位设置为：" << dataBit;
}

void SerialTool::serialToolSerialOpenSlos(QString port, QString baudRate,QString parit,
                                          QString stopBit,QString dataBit)
{
    serial = new QSerialPort();

    connect(serial,&QSerialPort::readyRead,this,&SerialTool::serialToolRead);


    this->port = port;
    this->baudRate = baudRate;
    this->parit = parit;
    this->stopBit = stopBit;
    this->dataBit = dataBit;

    setPort();          //设置串口名
    setBautdRate();          //设置波特率
    setParit();        //设置奇偶校验
    setDataBit();       //设置数据位
    setStopBit();       //设置停止位
    serial->setFlowControl(QSerialPort::NoFlowControl); //设置硬件流控制器
    if(!serial->open(QIODevice::ReadWrite)){
        //QMessageBox::about(NULL, "提示", "无法打开串口！");
        qDebug() << "无法打开串口";
        emit serialToolSerialOpenResult(false);
        return;
    }
    emit serialToolSerialOpenResult(true);

}

void SerialTool::serialToolSerialCloseSlos()
{
    serial->close();
}

void SerialTool::serialToolWrite(QString value)
{

    if(getHexFlag() != true){
        serial->write(value.toUtf8());
    }else {
        QByteArray senddata;
        StringToHex(value,senddata);
        serial->write(senddata);
    }


}

void SerialTool::serialToolRead()
{
     QByteArray buffer = serial->readAll();
    //qDebug() << "serialToolRead :"<< buffer;
    //qDebug()<<"serialToolRead ID:" <<QThread::currentThreadId();
    if(getHexFlag() != true){
        emit serialToolSreialReadResult(buffer);
    }else {
        emit serialToolSreialReadResult(buffer.toHex());
    }

}

void SerialTool::serialToolHexFlagSlots(bool value)
{
    hexFlag = value;
}

void SerialTool::StringToHex(QString str, QByteArray &senddata)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}

bool SerialTool::getHexFlag()
{
    return hexFlag;
}

char SerialTool::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
            return ch-0x30;
        else if((ch >= 'A') && (ch <= 'F'))
            return ch-'A'+10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
        else return (-1);
}


