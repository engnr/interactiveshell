#ifndef INTERACTIVECOMMAND_H
#define INTERACTIVECOMMAND_H

#include <QObject>

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

private:
    QList<InteractiveCommand *> m_commands;
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // INTERACTIVECOMMAND_H
