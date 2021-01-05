#include "managingusers.h"
#include "add_user.h"

#include "config.h"
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

#include <QDebug>

managingUsers::managingUsers(QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::managingUsers)
{
    mUi->setupUi(this);

    QFile file(Config::fileUsers);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream ist(&file);
        int row = 0;
        while (!ist.atEnd())
        {
            User user;
            ist >> user;
            m_listUsers.append(user);

            QTableWidgetItem *item_login = new QTableWidgetItem(user.login());
            QTableWidgetItem *item_status = new QTableWidgetItem(user.statusString());

            mUi->tableUsers->insertRow(row);
            mUi->tableUsers->setItem(row, 0, item_login);
            mUi->tableUsers->setItem(row, 1, item_status);
            row++;
        }
    }
}

managingUsers::~managingUsers()
{
    delete mUi;
}

void managingUsers::UpDownStatus()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    int currentRow = mUi->tableUsers->currentRow();
    if (currentRow != -1)
    {
        const QString login = mUi->tableUsers->item(currentRow, 0)->text();
        const QString status = mUi->tableUsers->item(currentRow, 1)->text();

        if (status == "Администратор" && countAdmins() <= 1)
        {
            QMessageBox::warning(this, windowTitle(),"Ошибка: не удалось повысить/понизить пользователя!");
            return;
        }

        QFile read_file(Config::fileUsers);
        if (read_file.open(QIODevice::ReadOnly))
        {
            QFile write_file("buf_file_users");
            write_file.open(QIODevice::WriteOnly);

            QDataStream read_ist(&read_file);
            QDataStream write_ist(&write_file);

            while (!read_ist.atEnd())
            {
                User user;
                read_ist >> user;

                if (user.login() == login)
                {
                    if (btn->objectName() == "buttonUpStatus")
                    {
                        if (!user.upStatus())
                        {
                            QMessageBox::warning(this, windowTitle(),
                                                 "Ошибка: невозможно повысить статус!\n"
                                                 "Установлен максимальный уровень статуса.");
                        }
                    }
                    else {
                        if (!user.downStatus())
                        {
                            QMessageBox::warning(this, windowTitle(),
                                                 "Ошибка: невозможно понизить статус!\n"
                                                 "Установлен минимальный уровень статуса.");
                        }
                    }

                    mUi->tableUsers->item(currentRow, 1)->setText(user.statusString());
                }
                write_ist << user;
            }
            read_file.close();
            read_file.remove();
            write_file.close();
            write_file.rename(Config::fileUsers);
        }
    }
    else QMessageBox::warning(this, windowTitle(),"Ошибка: не удалось повысить/понизить пользователя!");
}

void managingUsers::on_buttonDeleteUser_clicked()
{
    int currentRow = mUi->tableUsers->currentRow();
    if (currentRow != -1)
    {
        const QString login = mUi->tableUsers->item(currentRow, 0)->text();
        const QString status = mUi->tableUsers->item(currentRow, 1)->text();

        if (status == "Администратор" && countAdmins() <= 1)
        {
            QMessageBox::warning(this, windowTitle(),"Ошибка: не удалось повысить/понизить пользователя!");
            return;
        }
        mUi->tableUsers->removeRow(currentRow);

        QFile read_file(Config::fileUsers);
        if (read_file.open(QIODevice::ReadOnly))
        {
            QFile write_file("buf_file_users");
            write_file.open(QIODevice::WriteOnly);

            QDataStream read_ist(&read_file);
            QDataStream write_ist(&write_file);

            while (!read_ist.atEnd())
            {
                User user;
                read_ist >> user;
                if (user.login() != login) write_ist << user;
            }
            read_file.close();
            read_file.remove();
            write_file.close();
            write_file.rename(Config::fileUsers);
        }
    }
    else QMessageBox::warning(this, windowTitle(),"Ошибка: не удалось удалить пользователя!");
}

void managingUsers::on_buttonAddUser_clicked()
{
    Add_User dialog(this);
    dialog.setWindowTitle(windowTitle());

    if (dialog.exec() == QDialog::Accepted)
    {
        const User &user = dialog.getUser();
        QFile file(Config::fileUsers);
        file.open(QIODevice::Append);
        QDataStream ost(&file);
        ost << user;

        QTableWidgetItem *item_login = new QTableWidgetItem(user.login());
        QTableWidgetItem *item_status = new QTableWidgetItem(user.statusString());

        int row = mUi->tableUsers->rowCount();
        mUi->tableUsers->insertRow(row);
        mUi->tableUsers->setItem(row, 0, item_login);
        mUi->tableUsers->setItem(row, 1, item_status);
    }
}

int managingUsers::countAdmins() const
{
    QFile file(Config::fileUsers);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream ist(&file);
        int count = 0;
        while (!ist.atEnd())
        {
            User user;
            ist >> user;
            if (user.status() == User::Admin) count++;
        }
        return count;
    }
    else return 0;
}

void managingUsers::on_lineFind_textChanged(const QString &text)
{
    QStringList listStr = text.split(" ");
    listStr.removeAll(QString());

    for (int i = 0; i < m_listUsers.size(); i++) mUi->tableUsers->showRow(i);
    int row = 0;
    foreach (const User &user, m_listUsers)
    {
        int count = 0;
        foreach (const QString &str, listStr) if (user.login().contains(str) || user.statusString().contains(str)) count++;
        if (count != listStr.size()) mUi->tableUsers->hideRow(row);
        row++;
    }
}
