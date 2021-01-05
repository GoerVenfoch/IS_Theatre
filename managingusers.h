#ifndef MANAGINGUSERS_H
#define MANAGINGUSERS_H

#include <QDialog>
#include "user.h"
#include "ui_Managing_Users.h"

namespace Ui {
class managingUsers;
}

class managingUsers : public QDialog
{
    Q_OBJECT

public:
    explicit managingUsers(QWidget *parent = nullptr);
    ~managingUsers();

private slots:
    void UpDownStatus();
    void on_buttonDeleteUser_clicked();
    void on_buttonAddUser_clicked();
    void on_lineFind_textChanged(const QString &arg1);

private:
    Ui::managingUsers *mUi;
    QList<User> m_listUsers;
    int countAdmins() const;
};

#endif // MANAGINGUSERS_H
