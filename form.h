#ifndef FORM_H
#define FORM_H

#include "application.h"
#include "source.h"
#include "buffer.h"
#include "device.h"
#include "statistic.h"
#include "step.h"

#include <QDialog>
#include <QMainWindow>
#include <QtDebug>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {class Form;}
QT_END_NAMESPACE

class Form : public QDialog
{
    Q_OBJECT

public:
    Form(QWidget *parent = nullptr);
    ~Form();

    void startSession();
    void buildTable();
    void stepMode();
    std::vector<int> setDevicesFree(std::vector<Device> vector, double deviceStopTime);

private:
    Ui::Form *ui;
    int stepForm = 0;
    double p = 0.0;
    Statistic statistic;

private slots:
    void on_startButton_clicked();
    void on_backButton_2_clicked();
    void on_nextButton_2_clicked();
    void on_startStepModeButton_clicked();
    void on_goToStep_2_clicked();
};

#endif // FORM_H
