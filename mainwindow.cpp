#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_tempReader(new Acquisition)
{
    ui->setupUi(this);

    this->setWindowTitle("Monitor Ton Four");

    ui->progressBar_temp->reset();

    this->init_timer();

    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(action_quitter()));
    connect(ui->comboBox_refreshTime, SIGNAL(currentTextChanged(QString)), this, SLOT(update_refresh()));
    connect(ui->checkBox_activerAlerte, SIGNAL(toggled(bool)), this, SLOT(handle_alarm_activation()));
    connect(m_tempReader, &Acquisition::value_updated, this, &MainWindow::update_temperature);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_timer()
{
    m_listInterval = QStringList() << "120" << "90" << "60" << "30" << "10" << "1";
    ui->comboBox_refreshTime->addItems(m_listInterval);

    m_refreshTime = 120;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timeout_handler);
    timer->start(m_refreshTime * 1000); // Convert to ms
}

void MainWindow::action_quitter()
{
    QCoreApplication::quit();
}

void MainWindow::update_refresh()
{
    m_refreshTime = ui->comboBox_refreshTime->currentText().toInt();
    qDebug() << m_refreshTime * 1000 << "milli-secondes \n";

    timer->stop();
    timer->start(m_refreshTime * 1000);
}

void MainWindow::handle_alarm_activation()
{
    if (ui->checkBox_activerAlerte->isChecked()) {
        m_alarmMode = ALARM_ON;
    }
    else {
        m_alarmMode = ALARM_OFF;
    }
}

void MainWindow::timeout_handler()
{
    // Step 1: Call le sub process Python pour lire la temperature, refresh label
    m_tempReader->start();

    // Step 2: Si Alerte activee, comparer et actualiser progres bar + goNogo status
}

void MainWindow::update_temperature(const QString &value)
{
    ui->label_temperature->setText(value + "deg C");
}
