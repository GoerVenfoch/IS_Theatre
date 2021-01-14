#include <QtTest>
#include "user.h"

class TESTUSER : public QObject
{
    Q_OBJECT

private slots:
    void test_default_constructor();
    void test_init_constructor();
    void test_set_data();
    void test_get_set();
    void test_get_list_status();
    void test_up_status();
    void test_down_status();
};

void TESTUSER::test_default_constructor()
{
    User user;
    QCOMPARE(user.login(), "");
    QCOMPARE(user.password(), "");
}
void TESTUSER::test_init_constructor()
{
    User user("TEST1", "TEST2", User::Status::Admin);
    QCOMPARE(user.login(), "TEST1");
    QCOMPARE(user.password(), "TEST2");
    QCOMPARE(user.status(), User::Status::Admin);
}
void TESTUSER::test_set_data()
{
    User user;
    user.setData("TEST1", "TEST2", User::Status::Admin);
    QCOMPARE(user.login(), "TEST1");
    QCOMPARE(user.password(), "TEST2");
    QCOMPARE(user.status(), User::Status::Admin);
}
void TESTUSER::test_get_set()
{
    User user;
    user.setLogin("TEST1");
    user.setPassword("TEST2");
    user.setStatus(User::Status::Admin);
    QCOMPARE(user.login(), "TEST1");
    QCOMPARE(user.password(), "TEST2");
    QCOMPARE(user.status(), User::Status::Admin);
}
void TESTUSER::test_get_list_status()
{
    auto list = User::getListStatus();
    QCOMPARE(list[User::Status::Admin], "Администратор");
    QCOMPARE(list[User::Status::Cashier], "Кассир");
    QCOMPARE(list[User::Status::Viewer], "Зритель");
}
void TESTUSER::test_up_status()
{
    User user("TEST1", "TEST2", User::Status::Viewer);
    QCOMPARE(user.status(), User::Status::Viewer);
    QCOMPARE(user.upStatus(), true);
    QCOMPARE(user.status(), User::Status::Cashier);
    QCOMPARE(user.upStatus(), true);
    QCOMPARE(user.status(), User::Status::Admin);
    QCOMPARE(user.upStatus(), false);
}
void TESTUSER::test_down_status()
{
    User user("TEST1", "TEST2", User::Status::Admin);
    QCOMPARE(user.status(), User::Status::Admin);
    QCOMPARE(user.downStatus(), true);
    QCOMPARE(user.status(), User::Status::Cashier);
    QCOMPARE(user.downStatus(), true);
    QCOMPARE(user.status(), User::Status::Viewer);
    QCOMPARE(user.downStatus(), false);
}

QTEST_APPLESS_MAIN(TESTUSER)

#include "tst_testuser.moc"
