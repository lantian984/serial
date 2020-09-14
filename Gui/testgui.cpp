#include "testgui.h"
#include "ui_testgui.h"


TestGui *TestGui::_testGuiObj = nullptr;


TestGui::TestGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestGui)
{
    ui->setupUi(this);
    timer = new QTimer();

    connect(timer,&QTimer::timeout,this,&TestGui::testGuiSendSignals);

}

TestGui::~TestGui()
{
    delete ui;
}

void TestGui::setValueX(int value)
{
    x = value;
}

void TestGui::setValueY(int value)
{
    y = value;
}

void TestGui::setValueZ(int value)
{
    z = value;
}

int TestGui::getValueX()
{
    return x;
}

int TestGui::getValueY()
{
    return y;
}

int TestGui::getValueZ()
{
    return z;
}

void TestGui::setMs(int value)
{
    ms = value;
}

int TestGui::getMs(void)
{
    return ms;
}

void TestGui::testGuiSendSignals()
{
    QString data =  QString("{\"X_axis\":\"%1\",\"Y_axis\":\"%2\",\"Z_axis\":\"%3\"}").arg(getValueX()).arg(getValueY()).arg(getValueZ());
    emit testGuiXYZSignals(data);
    timer->start(getMs());
}

void TestGui::on_horizontalSliderX_valueChanged(int value)
{
    setValueX(value);
}

void TestGui::on_horizontalSliderY_valueChanged(int value)
{
    setValueY(value);
}

void TestGui::on_horizontalSliderZ_valueChanged(int value)
{
    setValueZ(value);
}

void TestGui::on_spinBox_valueChanged(int arg1)
{
   setMs(arg1);
}

void TestGui::on_pushButton_clicked()
{
    timer->start(getMs());
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}

void TestGui::on_pushButton_2_clicked()
{
    timer->stop();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}
