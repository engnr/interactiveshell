#include <QString>
#include <QtTest>

#include "interactivecommand.h"

using namespace Engnr::InteractiveShell;


class SlotCommandTest : public QObject
{
    Q_OBJECT

public:
    SlotCommandTest();

private Q_SLOTS:

private:
};

SlotCommandTest::SlotCommandTest()
{
}


QTEST_APPLESS_MAIN(SlotCommandTest)

#include "tst_slotcommandtest.moc"
