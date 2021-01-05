#include "signin.h"

#include "config.h"
#include "user.h"
#include "ui_authorization.h"

#include <QFile>
#include <QDataStream>

SignIn::SignIn(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::SignIn)
{
    mUi->setupUi(this);
    connect(mUi->buttonCreateUser, SIGNAL(clicked()),
            this, SIGNAL(openRegistration()));
}

SignIn::~SignIn()
{
    delete mUi;
}

User *SignIn::checkUser(const QString &login, const QString &password)
{
    QFile file(Config::fileUsers);
    if (file.exists())
    {
        User *user = nullptr;
        if (!file.open(QIODevice::ReadOnly)) {
            mUi->labelError->setText("Ошибка: открытие файла невозможно!");
            return nullptr;
        }
        QDataStream ist(&file);
        while (!ist.atEnd()) {
            User buf_user;
            ist >> buf_user;
            if (buf_user.login() == login && buf_user.password() == password) {
                user = new User(buf_user);
                return user;
            }
        }
        return user;
    }
    else
        return nullptr;
}

void SignIn::on_buttonEntry_clicked()
{
    mUi->labelError->clear();
    const QString login = mUi->login->text();
    const QString password = mUi->password->text();
    if (login.isEmpty() || password.isEmpty()) {
        mUi->labelError->setText("Ошибка: заполните все поля!");
    }
    else if (login.size() < 3 || login.size() > 20) {
        mUi->labelError->setText("Ошибка: имя пользователя должено содержать от 3 до 20 символов!");
    }
    else if (password.size() < 6 || password.size() > 15) {
        mUi->labelError->setText("Ошибка: пароль должен содержать от 6 до 15 символов!");
    }
    else {
        User *user = checkUser(login, password);
        if (user == nullptr) {
            mUi->labelError->setText("Ошибка: введены неккоректные данные!");
        }
        else {
            emit succesfulEntry(user);
        }
    }
}
