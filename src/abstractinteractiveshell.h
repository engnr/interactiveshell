#ifndef ABSTRACTINTERACTIVESHELL_H
#define ABSTRACTINTERACTIVESHELL_H

#include <QObject>
#include <QTextStream>

namespace Engnr {
namespace InteractiveShell {

class InteractiveCommand;

class AbstractInteractiveShell : public QObject
{
    Q_OBJECT
public:
    explicit AbstractInteractiveShell(QObject *parent = 0);
    void setPromptPrefix(const QString &prefix);
    QString promptPrefix() const;
    void setRootCommand(InteractiveCommand *rootCommand);
    void run();
    void run(const QString &command);
    void run(const QStringList &commands);

protected:
    void prompt();
    void parse(const QString &line);
    void parse(const QStringList &args);

private:

    QString m_promptPrefix;
    InteractiveCommand *m_rootCommand;
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // ABSTRACTINTERACTIVESHELL_H
