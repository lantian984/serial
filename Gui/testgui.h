#ifndef TESTGUI_H
#define TESTGUI_H

#include <QWidget>
#include <QTimer>
namespace Ui {
class TestGui;
}

class TestGui : public QWidget
{
    Q_OBJECT

private:
    explicit TestGui(QWidget *parent = nullptr);
    ~TestGui();
    void setValueX(int value);
    void setValueY(int value);
    void setValueZ(int value);
    int  getValueX();
    int  getValueY();
    int  getValueZ();

    void setMs(int value);
    int getMs();

public:
    static TestGui *construction()
    {
        if (_testGuiObj == nullptr)
        {
            _testGuiObj = new TestGui;
        }
        return _testGuiObj;
    }

    static void deleteConstruction()
    {
        delete _testGuiObj;
        _testGuiObj = nullptr;
    }



signals:
    void testGuiXYZSignals(QString value);


private slots:
    void on_horizontalSliderX_valueChanged(int value);

    void on_horizontalSliderY_valueChanged(int value);

    void on_horizontalSliderZ_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);
    void testGuiSendSignals();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TestGui *ui;
    static TestGui* _testGuiObj;
    int x;
    int y;
    int z;
    int ms;
    QTimer* timer;
};


#define testGui (TestGui::construction())
#define deleteTestGui() (TestGui::deleteConstruction())

#endif // TESTGUI_H
