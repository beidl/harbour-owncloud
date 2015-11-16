#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include <QObject>
#include <QProcess>

class ShellCommand : public QObject
{
public:
    ShellCommand(QObject *parent = 0);
    static void runCommand(QString command, QStringList args);
};

#endif // SHELLCOMMAND_H
