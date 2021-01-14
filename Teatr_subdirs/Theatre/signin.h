#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include "ui_authorization.h"

class User;

namespace Ui {
class SignIn;
}

class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private:
    Ui::SignIn *mUi;

    User *checkUser(const QString &login, const QString &password);

signals:
    void openRegistration();
    void succesfulEntry(User*);

private slots:
    void on_buttonEntry_clicked();
};

#endif // SIGNIN_H
