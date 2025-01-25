#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "acquisition.h"
#include <QMainWindow>
#include <QProcess>
#include <QStringList>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum k_alarmMode {
    ALARM_OFF,
    ALARM_ON
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_timer();
    void timeout_handler();

public slots:
    void update_temperature(const QString &value);

private slots:
    void action_quitter();
    void update_refresh();
    void handle_alarm_activation();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QStringList m_listInterval;
    int m_refreshTime;
    int m_tempAlarm;

    k_alarmMode m_alarmMode;

    Acquisition *m_tempReader;
};
#endif // MAINWINDOW_H
