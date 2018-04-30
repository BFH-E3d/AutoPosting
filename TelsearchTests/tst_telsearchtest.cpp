#include <QString>
#include <QtTest>

class TelsearchTest : public QObject
{
    Q_OBJECT

public:
    TelsearchTest();

private Q_SLOTS:
    void testCase1();
};

TelsearchTest::TelsearchTest()
{
}

void TelsearchTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TelsearchTest)

#include "tst_telsearchtest.moc"
