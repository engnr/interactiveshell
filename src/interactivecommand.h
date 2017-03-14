#ifndef INTERACTIVECOMMAND_H
#define INTERACTIVECOMMAND_H

#include <QObject>
#include "colors.h"
#include <QDebug>

namespace Engnr {
namespace InteractiveShell {

class InteractiveCommand : public QObject
{
    Q_OBJECT
public:
    explicit InteractiveCommand(QObject *parent = 0);
    void addCommand(InteractiveCommand *command);
    void removeCommand(InteractiveCommand *command);
    bool parse(QStringList args);
    QString name() const;

    virtual void run();
    virtual QString description() const;

public slots:
    void helpCommand();
    QString helpHelp();

protected:
    void print(const QString &message, int spaces = 0) const;
    void printLine(const QString &message, int spaces = 0) const;
    QDebug say() const;
    void say(const QString &message) const;
    void say(const QString &message, const Color &color) const;
    void say(const QString &message, const Colors &colors) const;
    QString ask(const QString &question, int spaces = 0);
    bool yes(const QString &statement);
    bool no(const QString &statement);
    void mute();
    void unmute();
    bool isMuted() const;
    void setColor(const Color &color);
    void setColors(const Colors &colors);
    void clearColor();
    QString sh(const QString &shellCommand);

private:
    bool runMethod(const QString &commandString, const QStringList &args);
    bool runCommand(const QString &commandString, const QStringList &args);
    bool invokeMethod(const QMetaMethod &method, const QStringList &args);
    bool checkMethodName(const QMetaMethod &method, const QString &command);
    bool checkArguments(const QMetaMethod &method, const QStringList &args);

    QList<InteractiveCommand *> m_commands;
    bool m_muted;
    QtMessageHandler m_oldMessageHandler;
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // INTERACTIVECOMMAND_H
