#include "plotgui.h"
#include "ui_plotgui.h"

PlotGui *PlotGui::_plotGuiObj = nullptr;


PlotGui::PlotGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotGui)
{
    ui->setupUi(this);
    creatPlot();
    updateBtnStatus();
}

PlotGui::~PlotGui()
{
    delete ui;
}



void PlotGui::creatPlot()
{

    // 添加轴
    xAxis = new QValueAxis();
    yAxis = new QValueAxis();

    // 坐标轴整体
    xAxis->setRange(0, 20);
    yAxis->setRange(-5, 5);

    // 轴标题设置
    xAxis->setTitleText(QStringLiteral("时间"));
    xAxis->setTitleFont(QFont("宋体"));
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    xAxis->setTitleBrush(brush);

    // X轴标签设置
    xAxis->setLabelFormat("%.1f");
    xAxis->setLabelsAngle(45);
    xAxis->setLabelsColor(Qt::blue);
    xAxis->setLabelsEditable(true);

    // 轴线和刻度线设置
    xAxis->setTickCount(11);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    xAxis->setLinePen(pen);
    xAxis->setLineVisible(true);
    xAxis->setLinePenColor(Qt::blue);

    // 主网格线设置
    xAxis->setGridLineVisible(true);
    //xAxis->setGridLineColor(Qt::black);

    // 次刻度和次网格线设置
    xAxis->setMinorTickCount(1);
    //xAxis->setMinorGridLineColor(Qt::color1);




    seriesX = new QSplineSeries();
    seriesY = new QSplineSeries();
    seriesZ = new QSplineSeries();



    seriesX->setName("X:");
    seriesX->setUseOpenGL(true);
    seriesX->setColor(QColor(0,255,0,255));
    seriesX->setPointsVisible(true);
    seriesX->setPointLabelsVisible(false);
    seriesX->setPointLabelsFormat("@xPoint,@yPoint");
    //connect(seriesX,&QSplineSeries::hovered,this,&Plot::xHoveredHandle);


    seriesY->setName("Y:");
    seriesY->setUseOpenGL(true);
    seriesY->setColor(QColor(255,0,0,255));
    seriesY->setPointsVisible(true);
    seriesY->setPointLabelsVisible(false);
    seriesY->setPointLabelsFormat("@xPoint,@yPoint");
    //connect(seriesY,&QSplineSeries::hovered,this,&Plot::yHoveredHandle);

    seriesZ->setName("Z:");
    seriesZ->setUseOpenGL(true);
    seriesZ->setColor(QColor(0,0,255,255));
    seriesZ->setPointsVisible(true);
    seriesZ->setPointLabelsVisible(false);
    seriesZ->setPointLabelsFormat("@xPoint,@yPoint");
    //connect(seriesZ,&QSplineSeries::hovered,this,&Plot::zHoveredHandle);

    chart = new QChart();

    chart->setTitle("Simple spline chart example"); //设置标题
    chart->legend()->hide();

    chart->addSeries(seriesX);  //添加曲线
    chart->addSeries(seriesY);  //添加曲线
    chart->addSeries(seriesZ);  //添加曲线


    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);

    seriesX->attachAxis(xAxis);
    seriesX->attachAxis(yAxis);

    seriesY->attachAxis(xAxis);
    seriesY->attachAxis(yAxis);

    seriesZ->attachAxis(xAxis);
    seriesZ->attachAxis(yAxis);




    ui->plotView->setChart(chart);
    ui->plotView->setRubberBand(QChartView::NoRubberBand);
    ui->plotView->setRenderHint(QPainter::Antialiasing,true);

    //ui->plotView->show();



}

void PlotGui::updateBtnStatus()
{
    if(suspend == true){
        ui->suspendBtn->setEnabled(false);
        ui->recoverBtn->setEnabled(true);
    }

    if(suspend == false){
        ui->suspendBtn->setEnabled(true);
        ui->recoverBtn->setEnabled(false);
    }
}

bool PlotGui::getSuspendStatus()
{
    return suspend;
}

void PlotGui::plotGuiUpdateSlots(Axis axis)
{
    if(axisList.length() >= 100){
        axisList.removeFirst();
    }

    axisList.append(axis);

    if(getSuspendStatus() != true){
        if(axisList.length() >= 100){
            xAxis->setRange(axisList.first().getIndex(),axisList.last().getIndex());
        }else {
            xAxis->setRange(0,axisList.last().getIndex());
        }
        seriesX->clear();
        seriesY->clear();
        seriesZ->clear();
          for(int i = 0; i < axisList.length();i++){
            seriesX->append(QPointF(axisList.value(i).getIndex(),axisList.value(i).getXAxis()));
            seriesY->append(QPointF(axisList.value(i).getIndex(),axisList.value(i).getYAxis()));
            seriesZ->append(QPointF(axisList.value(i).getIndex(),axisList.value(i).getZAxis()));
            //seriesZ->append(QPointF(t,axisList.at(i)));
            //qDebug() << "长度:" << axisList.length();
        }
        qDebug() << "图像数据 " << "t" << axisList.last().getIndex() << "X_axis" <<  axisList.last().getXAxis()
                 <<"Y_axis"  <<  axisList.last().getYAxis() <<"Z_axis" <<  axisList.last().getZAxis();

    }

}



void PlotGui::on_suspendBtn_clicked()
{
    suspend = true;
    updateBtnStatus();
}

void PlotGui::on_recoverBtn_clicked()
{
    suspend = false;
    updateBtnStatus();
}
