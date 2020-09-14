#ifndef MAINGUI_H
#define MAINGUI_H

#include <QWidget>
#include "Gui/plotgui.h"
#include "Gui/serialgui.h"
#include "SerialTool/serialtool.h"
#include "Buffer/serialdatapata.h"
#include "Buffer/plotdatapack.h"
#include "Gui/testgui.h"
namespace Ui {
class MainGui;
}

class MainGui : public QWidget
{
    Q_OBJECT

public:
    explicit MainGui(QWidget *parent = nullptr);
    ~MainGui();

private slots:
    void on_serialBtn_clicked();

    void on_plotBtn_clicked();



    void on_testBtn_clicked();

private:
    Ui::MainGui *ui;
    QThread* serialToolthread;
    QThread* serialDatathread;
    QThread* plotDatathread;

};

#endif // MAINGUI_H
