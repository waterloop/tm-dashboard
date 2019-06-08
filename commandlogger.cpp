#include "commandlogger.h"

CommandLogger::CommandLogger(QObject *parent) : QObject(parent){}

QString CommandLogger::getLog() {
    return m_log;
}

void CommandLogger::setLog(QString log) {
    m_log = log + "\n" + m_log;

    emit logSet();
}
