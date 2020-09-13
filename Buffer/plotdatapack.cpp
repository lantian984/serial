#include "plotdatapack.h"

PlotDataPack *PlotDataPack::_plotDataPackObj = nullptr;

PlotDataPack::PlotDataPack(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Axis>("Axis");
    index = 0;
}

PlotDataPack::~PlotDataPack()
{

}

void PlotDataPack::plotDatoPackUnPackSlots(QByteArray value)
{
    Json json;

    json.setJsonByteArray(value);

    QStringList x_list = { "X_axis"};
    QString x_axis = json.getValueFromJson(x_list);
    QStringList y_list = { "Y_axis"};
    QString y_axis = json.getValueFromJson(y_list);
    QStringList z_list = { "Z_axis"};
    QString z_axis = json.getValueFromJson(z_list);
    //qDebug() << "X_axis" << x_axis <<"Y_axis"  << y_axis<<"Z_axis" << z_axis;
    if(x_axis.isEmpty() || y_axis.isEmpty() || z_axis.isEmpty()){
        return;
    }
    index++;
    Axis axis(x_axis,y_axis,z_axis);
    axis.setIndex(index);
    emit plotDatoUpdateSignels(axis);
    qDebug() << "PlotDataPack" << value;
    qDebug()<<"PlotDataPack ID:" <<QThread::currentThreadId();
}




Axis::Axis()
{

}

Axis::Axis(QString x, QString y, QString z)
{
    x_axis = x.toDouble();
    y_axis = y.toDouble();
    z_axis = z.toDouble();
}

void Axis::setXAxis(QString x)
{
    x_axis = x.toDouble();
}

void Axis::setYAxis(QString y)
{
    y_axis = y.toDouble();
}

void Axis::setZAxis(QString z)
{
    z_axis = z.toDouble();
}

void Axis::setIndex(int t)
{
    index = t;
}

double Axis::getXAxis()
{
    return x_axis;
}

double Axis::getYAxis()
{
    return y_axis;
}

double Axis::getZAxis()
{
    return z_axis;
}

int Axis::getIndex()
{
    return index;
}



