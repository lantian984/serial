#include "Gui\maingui.h"
#include "ui_maingui.h"


/********************************************************************************
 * 功能： 初始化
 ********************************************************************************/
static void initObjects(void)
{
    serialGui->construction();
    plotGui->construction();
    serialTool->construction();
    serialDataPata->construction();
    plotDataPack->construction();
    testGui->construction();
}
/********************************************************************************
 * 功能： 结束任务
 ********************************************************************************/
static void exitTask(void)
{

   deleteSerialDataPata();
   deleteSerialTool();
   deletePlotGui();
   deleteSerialGui();
   deleteSerialDataPata();
   testGui->construction();
}





MainGui::MainGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainGui)
{
    ui->setupUi(this);

    serialToolthread = new QThread;
    serialDatathread = new QThread;
    plotDatathread = new QThread;


    initObjects();

    ui->stackedWidget->addWidget(serialGui);
    ui->stackedWidget->addWidget(plotGui);
    ui->stackedWidget->addWidget(testGui);
    ui->stackedWidget->setCurrentWidget(serialGui);

    //serialTool->moveToThread(serialToolthread);
    //serialDataPata->moveToThread(serialDatathread);
    //plotDataPack->moveToThread(plotDatathread);
     //信号与槽绑定

    connect(serialGui,&SerialGui::serialGuiSerialOpenSinles,serialTool,&SerialTool::serialToolSerialOpenSlos);
    connect(serialGui,&SerialGui::serialGuiSerialCloseSinles,serialTool,&SerialTool::serialToolSerialCloseSlos);
    connect(serialGui,&SerialGui::serialGuiSerialSendSignals,serialTool,&SerialTool::serialToolWrite);
    connect(serialGui,&SerialGui::serialGuiSerialHexSignals,serialTool,&SerialTool::serialToolHexFlagSlots);


    connect(serialTool,&SerialTool::serialToolSerialOpenResult,serialGui,&SerialGui::serialGuiSerialOpenResultSlots);
    connect(serialTool,&SerialTool::serialToolSreialReadResult,serialDataPata,&SerialDataPata::serialDataPataAppendSlost);
    connect(serialTool,&SerialTool::serialToolSreialReadResult,serialGui,&SerialGui::serialGuiShowText);

    connect(serialDataPata,&SerialDataPata::serialDataPataSendSignal,plotDataPack,&PlotDataPack::plotDatoPackUnPackSlots);
    //connect(serialDataPata,&SerialDataPata::serialDataPataSendSignal,serialGui,&SerialGui::serialGuiShowText);


    connect(plotDataPack,&PlotDataPack::plotDatoUpdateSignels,plotGui,&PlotGui::plotGuiUpdateSlots);

    connect(testGui,&TestGui::testGuiXYZSignals,serialTool,&SerialTool::serialToolWrite);


    connect(serialDatathread,&QThread::finished,serialDataPata,&QObject::deleteLater);

    //serialToolthread->start();
    //serialDatathread->start();
    //plotDatathread->start();
}


MainGui::~MainGui()
{
    exitTask();
    serialDatathread->wait();
    serialDatathread->quit();
    delete serialToolthread;
    delete ui;
}


void MainGui::on_serialBtn_clicked()
{
     ui->stackedWidget->setCurrentWidget(serialGui);
}

void MainGui::on_plotBtn_clicked()
{
     ui->stackedWidget->setCurrentWidget(plotGui);
}


void MainGui::on_testBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(testGui);
}
