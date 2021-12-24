#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form),
    statistic(0,0,0,0,0,0,0)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void minTimeSource(std::vector<Source> &sources)
{
    std::sort(sources.begin(), sources.end(), Source::compare);
}

void Form::on_startButton_clicked()
{
    startSession();
    buildTable();
}

void Form::on_startStepModeButton_clicked()
{
    startSession();
    stepForm = 0;

    QString printable;
    QStringList headers = {"State", "Application"};
    QStringList headersVertical;
    QStringList headersVertical2;

    printable = QStringLiteral("%1").arg(statistic.getSteps().size());
    ui->allSteps_1->setText(printable);

    ui->bufferStateTable_2->setColumnCount(2);
    ui->bufferStateTable_2->setRowCount(statistic.getSizeBuff());
    ui->bufferStateTable_2->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < statistic.getSizeBuff(); i++)
    {
        printable = QStringLiteral("Buffer place %1").arg(i+1);
        headersVertical.push_back(printable);
    }
    ui->bufferStateTable_2->setVerticalHeaderLabels(headersVertical);

    ui->deviceStateTable_2->setColumnCount(2);
    ui->deviceStateTable_2->setRowCount(statistic.getDevicesQuantity());
    statistic.stepsForm();
    ui->deviceStateTable_2->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < statistic.getDevicesQuantity(); i++)
    {
        printable = QStringLiteral("Device %1").arg(i+1);
        headersVertical2.push_back(printable);
    }
    ui->deviceStateTable_2->setVerticalHeaderLabels(headersVertical2);

    ui->tabWidget->setCurrentIndex(2);
    ui->backButton_2->setEnabled(false);
    stepMode();
}


void Form::on_backButton_2_clicked()
{
    stepForm -= 1;
    stepMode();
}

void Form::on_nextButton_2_clicked()
{
    stepForm += 1;
    stepMode();
}

void Form::on_goToStep_2_clicked()
{
    stepForm = ui->enterStep_2->text().toInt() - 1;
    stepMode();
}

void Form::buildTable()
{
    QString printable;
    QStringList headers = {" Generated ", " Processed ", " Rejected ", " Reject probability ", " Time in system ", " Waiting dispersion ", " Servicing dispersion "};
    QStringList headersVertical;

    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(statistic.getSourcesQantity());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

    QTableWidgetItem * protoitem = new QTableWidgetItem();
    protoitem->setTextAlignment(Qt::AlignCenter);

    QString printableKK;
        double rejected = statistic.getRejected(), requestAmount = statistic.getAppsQantity();
        printableKK = QStringLiteral("%1").arg(rejected / requestAmount);
        ui->AverageReject->setText(printableKK);

    QString printableK2;
            double deviceUseTime = statistic.getDevicesTimeAverage(), deviceAmount = statistic.getDevicesQuantity();
            printableKK = QStringLiteral("%1").arg(deviceUseTime / deviceAmount);
            ui->AverageReject_2->setText(printableKK);

    QString printableK3;
            double timeInSys = statistic.getTimeInSysAverage(), times = statistic.getSourcesQantity();
            printableKK = QStringLiteral("%1").arg(timeInSys / times);
            ui->Average_3->setText(printableKK);

    for (int i = 0; i < statistic.getSourcesQantity(); i++)
    {
        printable = QStringLiteral("Source %1").arg(i+1);
        headersVertical.push_back(printable);

        QTableWidgetItem *item1 = protoitem->clone();
        printable = QStringLiteral("%1").arg(statistic.getProcessed(i) + statistic.getRejected(i));
        item1->setText(printable);
        ui->tableWidget->setItem(i, 0, item1);

        QTableWidgetItem *item2 = protoitem->clone();
        printable = QStringLiteral("%1").arg(statistic.getProcessed(i));
        item2->setText(printable);
        ui->tableWidget->setItem(i, 1, item2);

        QTableWidgetItem *item3 = protoitem->clone();
        p += statistic.getRejected(i);
        printable = QStringLiteral("%1").arg(statistic.getRejected(i));
        item3->setText(printable);
        ui->tableWidget->setItem(i, 2, item3);

        QTableWidgetItem *item4 = protoitem->clone();
        double rejectProb = static_cast<double>(statistic.getRejected(i)) / static_cast<double>(statistic.getProcessed(i)+statistic.getRejected(i));
        printable = QStringLiteral("%1").arg(rejectProb);
        item4->setText(printable);
        ui->tableWidget->setItem(i, 3, item4);

        QTableWidgetItem *item5 = protoitem->clone();
        printable = QStringLiteral("%1").arg(statistic.getTimeInSystem(i) / (statistic.getProcessed(i)+statistic.getRejected(i)));
        item5->setText(printable);
        ui->tableWidget->setItem(i, 4, item5);

        QTableWidgetItem *item6 = protoitem->clone();
        printable = QStringLiteral("%1").arg(static_cast<double>(statistic.getWaitingTime(i)));
        item6->setText(printable);
        ui->tableWidget->setItem(i, 5, item6);

        QTableWidgetItem *item7 = protoitem->clone();
        printable = QStringLiteral("%1").arg(statistic.getServiceTime(i));
        item7->setText(printable);
        ui->tableWidget->setItem(i, 6, item7);
    }
    ui->tableWidget->setVerticalHeaderLabels(headersVertical);

    QStringList header = {"Devise usage"};
    QStringList headerVertical;
    ui->tableWidget_2->setColumnCount(1);
    ui->tableWidget_2->setRowCount(statistic.getDevicesQuantity());
    ui->tableWidget_2->setHorizontalHeaderLabels(header);

    for (int i = 0; i < statistic.getDevicesQuantity(); i++)
    {
        printable = QStringLiteral("Device %1").arg(i+1);
        headerVertical.push_back(printable);
        QTableWidgetItem *item1 = protoitem->clone();
        printable = QStringLiteral("%1").arg(statistic.getDeviceWorkingTime(i) / statistic.getSystemTime());
        item1->setText(printable);
        ui->tableWidget_2->setItem(i, 0, item1);
    }
    ui->tableWidget_2->setVerticalHeaderLabels(headerVertical);
    ui->tabWidget->setCurrentIndex(1);
}

void Form::startSession()
{
    Statistic statistic_(ui->buffer_size->text().toInt(),
                        ui->apps_quantity->text().toInt(),
                        ui->sources_quantity->text().toInt(),
                        ui->devices_quantity->text().toInt(),
                        ui->lambda->text().toDouble(),
                        ui->A->text().toDouble(),
                        ui->B->text().toDouble());

    std::vector<Source> soursesVector;
    std::vector<Device> devicesVector;
    std::vector<appPointer> appsVector;
    Buffer buffer(statistic_.getSizeBuff());

    for (int i = 0; i < statistic_.getSourcesQantity(); i++)
    {
        Source source(i,statistic_.getLambda());
        soursesVector.push_back(source);
    }

    for (int i = 0; i < statistic_.getDevicesQuantity(); i++)
    {
        Device device(i, statistic_.getA(),statistic_.getB());
        devicesVector.push_back(device);
    }

    for (int i = 0; i < statistic_.getAppsQantity(); i++)
    {
        if (soursesVector[0].getNewGenerationTime() > soursesVector[1].getNewGenerationTime())
        {
            minTimeSource(soursesVector);
        }

        appsVector.push_back(soursesVector[0].generationApp());
    }
    std::sort(appsVector.begin(), appsVector.end(), Buffer::compare);
    std::sort(devicesVector.rbegin(), devicesVector.rend(), Device::compareNumber);

    int i = 0, j = 0;
    bool refusal = false;
    step_t step;
    step.bufferVector = std::vector<appPointer>(statistic_.getSizeBuff(), nullptr);
    step.deviceVector = std::vector<appPointer>(statistic_.getDevicesQuantity(), nullptr);
    while (statistic_.getProcessed() + statistic_.getRejected() != statistic_.getAppsQantity())
    {
        if (i != statistic_.getAppsQantity())
        {
            std::vector<int> vector = setDevicesFree(devicesVector, appsVector[i]->getStartTime());
            for (int l : vector)
            {
                devicesVector[l].isFree(appsVector[i]->getStartTime(), statistic_, step);
            }

            if (!buffer.isFull())
            {
                buffer.addApp(appsVector[i], step);
                statistic_.addStep(step);
            }

            else
            {
                refusal = true;
            }

            int k = 0;
            while (k < statistic_.getDevicesQuantity())
            {
                if (devicesVector[j].isFree(appsVector[i]->getStartTime(), statistic_, step))
                {
                    if (!buffer.isEmpty())
                    {
                        devicesVector[j].getApp(buffer.getApp(step), step);
                        statistic_.addStep(step);
                    }
                    if (refusal == true)
                    {
                        buffer.addApp(appsVector[i], step);
                        statistic_.addStep(step);
                        refusal = false;
                    }
                }
                k++;
                j++;
            }
            j = 0;

            if (refusal == true)
            {
                buffer.removeApp(appsVector[i], step);
                statistic_.rejected(buffer.getRemovedApp()->getSourceNumber());
                step.time = appsVector[i]->getStartTime();

                step.action = "Application " + std::to_string(appsVector[i]->getSourceNumber() + 1)+
                        "." + std::to_string(appsVector[i]->getAppNumber()) + " generated and replaced " +
                        "Application " + std::to_string(buffer.getRemovedApp()->getSourceNumber() + 1)+
                        "." + std::to_string(buffer.getRemovedApp()->getAppNumber()) + " ---> Application " + std::to_string(buffer.getRemovedApp()->getSourceNumber() + 1)+
                        "." + std::to_string(buffer.getRemovedApp()->getAppNumber()) + " regected.";
                statistic_.addStep(step);
                refusal = false;
            }
            i++;
        }
        else
        {
            devicesVector.at(j).isFree(statistic_, step);
            if (!buffer.isEmpty())
            {
               devicesVector.at(j).getApp(buffer.getApp(step), step);
               statistic_.addStep(step);
            }
            if (j != statistic_.getDevicesQuantity()-1)
            {
                j++;
            } else {
                j = 0;
            }
        }
    }
    statistic = statistic_;
}

void Form::stepMode()
{
    QString printable1;
    QString printable2;
    step_t step = statistic.getSteps()[stepForm];

    printable1 = QString::fromStdString(step.action);
    ui->stepText_2->setText(printable1);

    printable1 = QStringLiteral("%1").arg(step.time);
    ui->timeValue_2->setText(printable1);

    printable1 = QStringLiteral("%1").arg(stepForm + 1);
    ui->currentStep_2 ->setText(printable1);

    QTableWidgetItem * protoitem = new QTableWidgetItem();
    protoitem->setTextAlignment(Qt::AlignCenter);

    for (int i = 0; i < statistic.getSizeBuff(); i++)
    {
        QTableWidgetItem *item1 = protoitem->clone();
        QTableWidgetItem *item2 = protoitem->clone();

        if (step.bufferVector[i] == nullptr)
        {
            printable1 = QStringLiteral("Free");
            printable2 = QStringLiteral("-");
        } else {
            printable1 = QStringLiteral("Busy");
            printable2 = QStringLiteral("%1").arg(step.bufferVector[i]->getSourceNumber() + 1);
            printable2 += QStringLiteral(".%1").arg(step.bufferVector[i]->getAppNumber());
        }

        item1->setText(printable1);
        ui->bufferStateTable_2->setItem(i, 0, item1);

        item2->setText(printable2);
        ui->bufferStateTable_2->setItem(i, 1, item2);
    }

    for (int i = 0; i < statistic.getDevicesQuantity(); i++)
    {
        QTableWidgetItem *item1 = protoitem->clone();
        QTableWidgetItem *item2 = protoitem->clone();

        if (step.deviceVector[i] == nullptr)
        {
            printable1 = QStringLiteral("Free");
            printable2 = QStringLiteral("-");
        } else {
            printable1 = QStringLiteral("Works");
            printable2 = QStringLiteral("%1").arg(step.deviceVector[i]->getSourceNumber() + 1);
            printable2 += QStringLiteral(".%1").arg(step.deviceVector[i]->getAppNumber());
        }

        item1->setText(printable1);
        ui->deviceStateTable_2->setItem(i, 0, item1);

        item2->setText(printable2);
        ui->deviceStateTable_2->setItem(i, 1, item2);
    }

    if (stepForm == statistic.getSteps().size() - 1)
    {
        ui->nextButton_2->setEnabled(false);
    } else {
        ui->nextButton_2->setEnabled(true);
    }

    if (stepForm == 0)
    {
        ui->backButton_2->setEnabled(false);
    } else {
        ui->backButton_2->setEnabled(true);
    }
}

std::vector<int> Form::setDevicesFree(std::vector<Device> vector, double deviceStopTime)
{
    std::vector<Device> deviceVector;

    for (int i = 0; i < (int)vector.size(); i++)
    {
        if (vector[i].getTaskEndTime() < deviceStopTime)
        {
            deviceVector.push_back(vector[i]);
        }
    }
    std::sort(deviceVector.begin(), deviceVector.end(), Device::compareTime);

    std::vector<int> intVector;

    for (int i = 0; i < (int)deviceVector.size(); i++)
    {
        intVector.push_back(deviceVector[i].getDeviceNumber());
    }
    return intVector;
}
