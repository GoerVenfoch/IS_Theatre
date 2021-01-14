#include "signup.h"

#include "config.h"
#include "user.h"
#include "ui_registration.h"

#include <QFile>
#include <QDataStream>

SignUp::SignUp(TypeRegistration typeReg, QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::SignUp)
{
    mUi->setupUi(this);
    if (typeReg == Admin)
    {
        mUi->mainLabel->setText("Регистрация администратора");
        mUi->buttonAuthorization->hide();
    }
    m_typeReg = typeReg;
    connect(mUi->buttonAuthorization, SIGNAL(clicked()),
            this, SIGNAL(openAuthorization()));
}

SignUp::~SignUp()
{
    delete mUi;
}

bool SignUp::isLoginExists(const QString &login)
{
    QFile file(Config::fileUsers);
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly))
        {
            mUi->labelError->setText("Ошибка: чтение файла невозможно!");
            return false;
        }
        QDataStream ist(&file);
        while (!ist.atEnd())
        {
            User buf_user;
            ist >> buf_user;
            if (buf_user.login() == login) return true;
        }
        return false;
    }
    else return false;
}

void SignUp::on_buttonCreate_clicked()
{
    mUi->labelError->clear();
    const QString login = mUi->login->text();
    const QString password = mUi->password->text();
    const QString repeatPassword = mUi->repeatPassword->text();

    if (login.isEmpty() || password.isEmpty() || repeatPassword.isEmpty()) mUi->labelError->setText("Ошибка: заполните все поля!");
    else if (isLoginExists(login)) { if (mUi->labelError->text().isEmpty()) mUi->labelError->setText("Ошибка: данное имя пользователя уже существует!"); }
    else if (login.size() < 3 || login.size() > 20) mUi->labelError->setText("Ошибка: имя пользователя должено содержать от 3 до 20 символов!");
    else if (password.size() < 6 || password.size() > 15) mUi->labelError->setText("Ошибка: пароль должен содержать от 6 до 15 символов!");
    else if (password != repeatPassword) mUi->labelError->setText("Ошибка: пароли не совпадают!");
    else
    {
        User user(login, password, m_typeReg == Admin ? User::Admin : User::Viewer);
        QFile file(Config::fileUsers);
        file.open(QIODevice::Append);
        QDataStream ost(&file);
        ost << user;

        emit openAuthorization();
    }
}
