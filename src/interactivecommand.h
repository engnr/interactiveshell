#ifndef INTERACTIVECOMMAND_H
#define INTERACTIVECOMMAND_H

#include <QObject>
#include "colors.h"

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
    void print(const QString &message, int spaces = 0);
    void printLine(const QString &message, int spaces = 0);
    QString ask(const QString &question, int spaces = 0);
    bool yes(const QString &statement);
    bool no(const QString &statement);
    void mute();
    void unmute();
    bool isMuted() const;
    void setColor(const Color &color);
    void setColors(const Colors &colors);
    void clearColor();

private:
    QList<InteractiveCommand *> m_commands;
    bool m_muted;
    QtMessageHandler m_oldMessageHandler;
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // INTERACTIVECOMMAND_H
