#ifndef COMMANDLOGGER_H
#define COMMANDLOGGER_H

#include <QObject>

class CommandLogger : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString log READ getLog NOTIFY logSet)

public:
    explicit CommandLogger(QObject *parent = nullptr);

signals:
    void logSet();

public slots:
    void setLog(QString log);

private:
    QString m_log;
    QString getLog();
};

#endif // COMMANDLOGGER_H
