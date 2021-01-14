#include <QtTest>
#include "performance.h"

class TESTPERFORMANCE : public QObject
{
    Q_OBJECT

private slots:
    void test_default_constructor();
    void test_init_constructor();
    void test_set_data();
    void test_get_set();
};

void TESTPERFORMANCE::test_default_constructor()
{
    Performance performance;
    QCOMPARE(performance.NamePerformance(), "");
    QCOMPARE(performance.Producer(), "");
    QCOMPARE(performance.Author(), "");
}

void TESTPERFORMANCE::test_init_constructor()
{
    Performance performance("TEST1", "TEST2", "TEST3");
    QCOMPARE(performance.Author(), "TEST1");
    QCOMPARE(performance.NamePerformance(), "TEST2");
    QCOMPARE(performance.Producer(), "TEST3");
}

void TESTPERFORMANCE::test_set_data()
{
    Performance performance;
    performance.setData("TEST1", "TEST2", "TEST3");
    QCOMPARE(performance.NamePerformance(), "TEST1");
    QCOMPARE(performance.Producer(), "TEST2");
    QCOMPARE(performance.Author(), "TEST3");
}

void TESTPERFORMANCE::test_get_set()
{
    Performance performance;
    performance.setAuthor("TEST1");
    performance.setNamePerformance("TEST2");
    performance.setProduser("TEST3");
    QCOMPARE(performance.Author(), "TEST1");
    QCOMPARE(performance.NamePerformance(), "TEST2");
    QCOMPARE(performance.Producer(), "TEST3");
}

QTEST_APPLESS_MAIN(TESTPERFORMANCE)

#include "tst_testperformance.moc"
