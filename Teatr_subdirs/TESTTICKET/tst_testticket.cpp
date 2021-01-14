#include <QtTest>
#include "ticket.h"

class TESTTICKET : public QObject
{
    Q_OBJECT

private slots:
    void test_default_constructor();
    void test_init_constructor();
    void test_set_data();
    void test_get_set();
    void test_get_list_combo();
};

void TESTTICKET::test_default_constructor()
{
    Ticket ticket;
    QCOMPARE(ticket.performance(), "");
    QCOMPARE(ticket.firstName(), "");
    QCOMPARE(ticket.secondName(), "");
    QCOMPARE(ticket.fatherName(), "");
    QCOMPARE(ticket.phone(), "");
    QCOMPARE(ticket.row(), 0);
    QCOMPARE(ticket.place(), 0);
}

void TESTTICKET::test_init_constructor()
{
    Ticket ticket("TEST1", "TEST2", "TEST3", "TEST3", "TEST5", Ticket::Combo::Amfiteatr, 1, 1);
    QCOMPARE(ticket.performance(), "TEST1");
    QCOMPARE(ticket.firstName(), "TEST2");
    QCOMPARE(ticket.secondName(), "TEST3");
    QCOMPARE(ticket.fatherName(), "TEST3");
    QCOMPARE(ticket.phone(), "TEST5");
    QCOMPARE(ticket.combobox(), Ticket::Combo::Amfiteatr);
    QCOMPARE(ticket.row(), 1);
    QCOMPARE(ticket.place(), 1);
}

void TESTTICKET::test_set_data()
{
    Ticket ticket;
    ticket.setData("TEST1", "TEST2", "TEST3", "TEST4", "TEST5", Ticket::Combo::Amfiteatr, 1, 1);
    QCOMPARE(ticket.performance(), "TEST1");
    QCOMPARE(ticket.firstName(), "TEST2");
    QCOMPARE(ticket.secondName(), "TEST3");
    QCOMPARE(ticket.fatherName(), "TEST4");
    QCOMPARE(ticket.phone(), "TEST5");
    QCOMPARE(ticket.combobox(), Ticket::Combo::Amfiteatr);
    QCOMPARE(ticket.row(), 1);
    QCOMPARE(ticket.place(), 1);
}

void TESTTICKET::test_get_set()
{
    Ticket ticket;
    ticket.setperformance("TEST1");
    ticket.setfirstName("TEST2");
    ticket.setsecondName("TEST3");
    ticket.setfatherName("TEST3");
    ticket.setphone("TEST5");
    ticket.setcombobox(Ticket::Combo::Amfiteatr);
    ticket.setrow(1);
    ticket.setplace(1);
    QCOMPARE(ticket.performance(), "TEST1");
    QCOMPARE(ticket.firstName(), "TEST2");
    QCOMPARE(ticket.secondName(), "TEST3");
    QCOMPARE(ticket.fatherName(), "TEST3");
    QCOMPARE(ticket.phone(), "TEST5");
    QCOMPARE(ticket.combobox(), Ticket::Combo::Amfiteatr);
    QCOMPARE(ticket.row(), 1);
    QCOMPARE(ticket.place(), 1);
}

void TESTTICKET::test_get_list_combo()
{
    auto list = Ticket::getListCombo();
    QCOMPARE(list[Ticket::Combo::Amfiteatr], "Амфитеатр");
    QCOMPARE(list[Ticket::Combo::Parter], "Партер");
    QCOMPARE(list[Ticket::Combo::Loga1], "Ложа №1");
    QCOMPARE(list[Ticket::Combo::Loga2], "Ложа №2");
    QCOMPARE(list[Ticket::Combo::Loga3], "Ложа №3");
}

QTEST_APPLESS_MAIN(TESTTICKET)

#include "tst_testticket.moc"
