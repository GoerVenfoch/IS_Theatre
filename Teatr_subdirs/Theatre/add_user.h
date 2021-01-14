#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>
#include "user.h"

namespace Ui {
class Add_User;
}

class Add_User : public QDialog
{
    Q_OBJECT

public:
    explicit Add_User(QWidget *parent = nullptr);
    ~Add_User();
    const User &getUser() const;

private:
    Ui::Add_User *mUi;
    User m_user;

public slots:
    void accept();
    bool isLoginExists(const QString &login);
};

#endif // ADD_USER_H
