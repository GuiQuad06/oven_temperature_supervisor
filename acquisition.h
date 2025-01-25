#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <QObject>
#include <QProcess>

class Acquisition : public QObject
{
    Q_OBJECT
public:
    explicit Acquisition(QObject *parent = nullptr);
    int start();
    void read_temperature();

signals:
    void value_updated(const QString &value);

private:

    QProcess *m_acquisitionProcess;
    QString m_scriptPath;
};

#endif // ACQUISITION_H
