#include "acquisition.h"
#include "path.h"

#include <QDebug>

Acquisition::Acquisition(QObject *parent)
    : QObject{ parent }, m_acquisitionProcess(new QProcess(this))
{
    m_scriptPath = home_path + QString("/MAX31865_RPI/max31865.py");

    connect(m_acquisitionProcess, &QProcess::readyReadStandardOutput, this,
            &Acquisition::read_temperature);
}

Acquisition::~Acquisition()
{
    delete m_acquisitionProcess;
}

acq_error_t Acquisition::start()
{
    m_acquisitionProcess->start("python", QStringList() << m_scriptPath);

    if (!m_acquisitionProcess->waitForStarted()) {
        return PYTHON_ERROR;
    }
    return NO_ERROR;
}

void Acquisition::read_temperature()
{
    // Read the output from the Python script
    QString output = m_acquisitionProcess->readAllStandardOutput();
    // qDebug() << output << '\n';

    // Notify UI that temperature was acquired
    emit value_updated(output);
}
