#ifndef PLOTDATAPACK_H
#define PLOTDATAPACK_H

#include <QObject>
#include <QMetaType>
#include <QDebug>
#include "Json/json.h"
#include <QThread>

class Axis
{

private:
    double x_axis;
    double y_axis;
    double z_axis;
    int index;
public:
    Axis();
    Axis(QString x,QString y,QString z);
    void setXAxis(QString x);
    void setYAxis(QString y);
    void setZAxis(QString z);
    void setIndex(int t);
    double getXAxis();
    double getYAxis();
    double getZAxis();
    int getIndex();
};






class PlotDataPack : public QObject
{
    Q_OBJECT
private:
    explicit PlotDataPack(QObject *parent = nullptr);
    ~PlotDataPack();
public:
    static PlotDataPack *construction()
    {
        if (_plotDataPackObj == nullptr)
        {
            _plotDataPackObj = new PlotDataPack;
        }
        return _plotDataPackObj;
    }

    static void deleteConstruction()
    {
        delete _plotDataPackObj;
        _plotDataPackObj = nullptr;
    }
signals:
    void plotDatoUpdateSignels(Axis axis);
    void finished();//完成信号
public slots:
    void plotDatoPackUnPackSlots(QByteArray value);
private:
    static PlotDataPack* _plotDataPackObj;
    int index;
};


#define plotDataPack (PlotDataPack::construction())
#define deletePlotDataPack() (PlotDataPack::deleteConstruction())

#endif // PLOTDATAPACK_H
