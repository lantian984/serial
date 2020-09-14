#include "serialdatapata.h"



SerialDataPata *SerialDataPata::_serialDataPataObj = nullptr;


SerialDataPata::SerialDataPata(QObject *parent) : QObject(parent)
{
    dataByteArray = new QByteArray();
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&SerialDataPata::serialDataPataUnpakeSlost);
    timer->start(5);
}

SerialDataPata::~SerialDataPata()
{
    delete dataByteArray;
}

void SerialDataPata::serialDataPataAppendSlost(QByteArray value)
{
    if(value.contains(0x11)){
        value.replace(0x11,"");
    }
    if(value.contains(0x13)){   //过滤不需要的字符
        value.replace(0x13,"");
    }
    if(value.contains(0x10)){
        value.replace(0x10,"");
    }

    dataByteArray->append(value);   //追加到缓存区
    //qDebug() << "serialDataPata :"<< dataByteArray->data();
    //qDebug()<<"serialDataPata ID:" <<QThread::currentThreadId();
    //serialDataPataUnpakeSlost();

}



//正常的数据： "{\"X_axis\":\"2.0\",\"Y_axis\":\"2.5\",\"Z_axis\":\"2.6\"}"
void SerialDataPata::serialDataPataUnpakeSlost()
{
    //未找到包头直接退出
    if(!dataByteArray->contains('{')){
        timer->start(5);
        return;
    }
    //找到包头
   int indexBefore = dataByteArray->indexOf('{',0);
   //删除包头前的无效数据
   if(indexBefore > 0){
       dataByteArray->remove(0,indexBefore);
       indexBefore = dataByteArray->indexOf('{',0);
   }
   //未找到包尾
   if(!dataByteArray->contains('}')){
        timer->start(5);
        return;
   }
   //找到包尾
   int indexLater = dataByteArray->indexOf('}',0);

    //提取一个完整包的数据
   QByteArray data = dataByteArray->mid(indexBefore,indexLater - indexBefore + 1);
   //qDebug() << "找到有效数据:" << QString(data);
   //提取后删除原来缓存区的数据
   dataByteArray->remove(indexBefore,indexLater - indexBefore +1);
   //qDebug()<<"serialDataPata ID:" <<QThread::currentThreadId();
   emit serialDataPataSendSignal(data);
    timer->start(5);
}
