#ifndef PLOTGUI_H
#define PLOTGUI_H

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QPainter>
#include <QChartView>
#include <QChart>
#include <QSplineSeries>
#include <QPainter>
#include <QList>
#include <QPointF>
#include <QTimer>
#include <QDebug>
#include <QValueAxis>
#include "Buffer/plotdatapack.h"

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class PlotGui;
}

class PlotGui : public QWidget
{
    Q_OBJECT

private:
    explicit PlotGui(QWidget *parent = nullptr);
    ~PlotGui();

public:
    static PlotGui *construction()
    {
        if (_plotGuiObj == nullptr)
        {
            _plotGuiObj = new PlotGui;
        }
        return _plotGuiObj;
    }

    static void deleteConstruction()
    {
        delete _plotGuiObj;
        _plotGuiObj = nullptr;
    }
private:
    void creatPlot();
    void updateBtnStatus();
    bool getSuspendStatus();
public slots:
    void plotGuiUpdateSlots(Axis axis);
private slots:
    void on_suspendBtn_clicked();

    void on_recoverBtn_clicked();

private:
    Ui::PlotGui *ui;
    static PlotGui* _plotGuiObj;

    QValueAxis *xAxis;
    QValueAxis *yAxis;

    QSplineSeries *seriesX;
    QSplineSeries *seriesY;
    QSplineSeries *seriesZ;
    QChart *chart;

    QList<Axis> axisList;
    QList<QPointF> x_List;
    QList<QPointF> y_List;
    QList<QPointF> z_List;
    bool suspend = false;
};

#define plotGui (PlotGui::construction())
#define deletePlotGui() (PlotGui::deleteConstruction())


#endif // PLOTGUI_H
