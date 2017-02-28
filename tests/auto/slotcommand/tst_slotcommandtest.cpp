#include <QString>
#include <QtTest>

#include "interactivecommand.h"

using namespace Engnr::InteractiveShell;

class BaseCommand : public InteractiveCommand
{
    Q_OBJECT
signals:
    void invoked();
};

class PublicSlotCommand : public BaseCommand
{
    Q_OBJECT
public slots:
    void checkCommand()
    {
        emit invoked();
    }
};

class PrivateSlotCommand : public BaseCommand
{
    Q_OBJECT
private slots:
    void checkCommand()
    {
        emit invoked();
    }
};

class MethodCommand : public BaseCommand
{
    Q_OBJECT
public:
    void checkCommand()
    {
        emit invoked();
    }
};



class SlotCommandTest : public QObject
{
    Q_OBJECT

public:
    SlotCommandTest();

private Q_SLOTS:
    void publicSlot();
    void publicSlot_data();
    void privateSlot();
    void method();

private:
    void verifyCommand(BaseCommand *command, const QString &commandString,
                       int invokes);
};

SlotCommandTest::SlotCommandTest()
{
}

void SlotCommandTest::publicSlot()
{
    QFETCH(QString, commandString);
    QFETCH(int, invokes);

    PublicSlotCommand *command = new PublicSlotCommand;
    verifyCommand(command, commandString, invokes);
    delete command;
}

void SlotCommandTest::publicSlot_data()
{
    QTest::addColumn<QString>("commandString");
    QTest::addColumn<int>("invokes");

    QTest::newRow("one command") << QString("check") << 1;
    QTest::newRow("two commands") << QString("check check") << 1;
    QTest::newRow("command with argument") << QString("check arg") << 1;
}

void SlotCommandTest::privateSlot()
{
    PrivateSlotCommand *command = new PrivateSlotCommand;
    verifyCommand(command, "check", 0);
    delete command;
}

void SlotCommandTest::method()
{
    MethodCommand *command = new MethodCommand;
    verifyCommand(command, "check", 0);
    delete command;
}

void SlotCommandTest::verifyCommand(BaseCommand *command, const QString &commandString, int invokes)
{
    QSignalSpy spy(command, SIGNAL(invoked()));
    QStringList args = commandString.split(" ");

    command->parse(args);
    QCOMPARE(spy.count(), invokes);
}

QTEST_APPLESS_MAIN(SlotCommandTest)

#include "tst_slotcommandtest.moc"
