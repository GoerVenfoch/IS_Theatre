#include "cast.h"
#include <QMessageBox>
#include "ui_cast.h"
#include "addactor.h"

cast::cast(User &user, QWidget *parent) :
QDialog(parent),
mUi(new Ui::cast),
m_user(user)
{
    mUi->setupUi(this);
    setWindowTitle("Актерский состав");
    mUi->tableActers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    if (m_user.status() == User::Viewer)
    {
        mUi->add->hide();
        mUi->edit->hide();
        mUi->remove->hide();
    }

    QFile file(Config::fileActor);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);

        int row = 0;
        while (!ist.atEnd()) {
            Actors actor;
            ist >> actor;
            m_actor.append(actor);
            QTableWidgetItem *item_firstName = new QTableWidgetItem(actor.firstName());
            QTableWidgetItem *item_secondName = new QTableWidgetItem(actor.secondName());
            QTableWidgetItem *item_born = new QTableWidgetItem(actor.born().toString("d-MMMM-yyyy"));

            mUi->tableActers->insertRow(row);
            mUi->tableActers->setItem(row, 0, item_firstName);
            mUi->tableActers->setItem(row, 1, item_secondName);
            mUi->tableActers->setItem(row, 2, item_born);
            row++;
        }
    }
}

cast::~cast()
{
    delete mUi;
}


void cast::loadActors()
{
    m_actor.clear();

    QFile file(Config::fileActor);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);

        while (!ist.atEnd()) {
            Actors actor;
            ist >> actor;
            m_actor.append(actor);
        }
    }

    int row = 0;
    foreach (const Actors &actor, m_actor)
    {
        QTableWidgetItem *item_firstName = new QTableWidgetItem(actor.firstName());
        QTableWidgetItem *item_secondName = new QTableWidgetItem(actor.secondName());
        QTableWidgetItem *item_born = new QTableWidgetItem(actor.born().toString("d-MMMM-yyyy"));

        mUi->tableActers->insertRow(row);
        mUi->tableActers->setItem(row, 0, item_firstName);
        mUi->tableActers->setItem(row, 1, item_secondName);
        mUi->tableActers->setItem(row, 2, item_born);
        row++;
    }
}

void cast::on_tableActers_cellActivated(int row)
{
    QMessageBox aboutActor;

    aboutActor.setWindowTitle("О актере");
    aboutActor.setIcon(QMessageBox::Information);
    aboutActor.setStandardButtons(QMessageBox::Ok);
    aboutActor.setText(tr("Фамилия:       %1 <br>"
                       "Имя:           %2 <br>"
                       "Дата рождения: %3 <br>")
            .arg(m_actor[row].firstName()).arg(m_actor[row].secondName())
                                          .arg(m_actor[row].born().toString("d-MMMM-yyyy")));
}

void cast::on_add_clicked()
{
    Actors actor;
    addActor dialog(actor, addActor::Create, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        m_actor.append(actor);

        QTableWidgetItem *item_firstName = new QTableWidgetItem(actor.firstName());
        QTableWidgetItem *item_secondName = new QTableWidgetItem(actor.secondName());
        QTableWidgetItem *item_born = new QTableWidgetItem(actor.born().toString("d-MMMM-yyyy"));

        int row = mUi->tableActers->rowCount();
        mUi->tableActers->insertRow(row);
        mUi->tableActers->setItem(row, 0, item_firstName);
        mUi->tableActers->setItem(row, 1, item_secondName);
        mUi->tableActers->setItem(row, 2, item_born);
    }
}

void cast::on_edit_clicked()
{
    int currentRow = mUi->tableActers->currentRow();
    if (currentRow != -1) {
        Actors &actor = m_actor[currentRow];
        addActor dialog(actor, addActor::Edit, this);
        dialog.setWindowTitle(windowTitle());

        if (dialog.exec() == QDialog::Accepted)
        {
            m_actor[currentRow] = actor;

            QFile read_file(Config::fileActor);
            if (read_file.open(QIODevice::ReadOnly)) {
                QFile write_file("buf_file_actor");
                write_file.open(QIODevice::WriteOnly);

                QDataStream read_ist(&read_file);
                QDataStream write_ist(&write_file);

                int count = 0;
                while (!read_ist.atEnd()) {
                    Actors buf_actor;
                    read_ist >> buf_actor;
                    if (count++ == currentRow)
                    {
                        buf_actor = actor;
                    }
                    write_ist << buf_actor;
                }
                read_file.close();
                read_file.remove();

                write_file.close();
                write_file.rename(Config::fileActor);
            }

            mUi->tableActers->item(currentRow, 0)->setText(actor.firstName());
            mUi->tableActers->item(currentRow, 1)->setText(actor.secondName());
            mUi->tableActers->item(currentRow, 2)->setText(actor.born().toString("d-MMMM-yyyy"));
        }
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один актер!");
    }
}

void cast::on_remove_clicked()
{
    int currentRow = mUi->tableActers->currentRow();
    if (currentRow != -1) {
        m_actor.removeAt(currentRow);

        QFile read_file(Config::fileActor);
        if (read_file.open(QIODevice::ReadOnly))
        {
            QFile write_file("buf_file_actor");
            write_file.open(QIODevice::WriteOnly);

            QDataStream read_ist(&read_file);
            QDataStream write_ist(&write_file);

            int countReads = 0;
            while (!read_ist.atEnd()) {
                Actors buf_actor;
                read_ist >> buf_actor;

                if (countReads++ != currentRow)
                {
                    write_ist << buf_actor;
                }
            }
            read_file.close();
            read_file.remove();
            write_file.close();
            write_file.rename(Config::fileActor);
        }
        mUi->tableActers->removeRow(currentRow);
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один актер!");
    }
}
