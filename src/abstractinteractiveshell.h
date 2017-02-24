#ifndef ABSTRACTINTERACTIVESHELL_H
#define ABSTRACTINTERACTIVESHELL_H

#include <QObject>
#include <QTextStream>
#include <QSocketNotifier>

namespace Engnr {
namespace InteractiveShell {

class AbstractInteractiveShell : public QObject
{
    Q_OBJECT
public:
    explicit AbstractInteractiveShell(QObject *parent = 0);
    void setPromptPrefix(const QString &prefix);
    QString promptPrefix() const;

protected:
    void prompt();

private slots:
    void read(int);

private:
    virtual void parse(const QByteArray &line) = 0;

    QSocketNotifier m_notifier;
    QString m_promptPrefix;
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // ABSTRACTINTERACTIVESHELL_H
