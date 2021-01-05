#include "managingposters.h"
#include "ui_Managing_Posters.h"

#include "config.h"
#include "user.h"
#include "addposters.h"
#include "byticket.h"

#include <QFile>
#include <QDataStream>
#include <QMessageBox>

#include <QDebug>

ManagingPosters::ManagingPosters(User &user, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::ManagingPosters),
    m_user(user)
{
    mUi->setupUi(this);
    mUi->tablePerformance->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    connect(mUi->tablePerformance, SIGNAL(cellActivated(int, int)),
            this, SLOT(descriptionPRM(int, int)));

    if (m_user.status() != User::Viewer)
    {
        mUi->buyTicket->hide();
        setWindowTitle("Управление афишами");
    }
    else
    {
        mUi->addPoster->hide();
        mUi->removePoster->hide();
        mUi->editPoster->hide();
        setWindowTitle("Афиши");
    }

    loadPosters();
    loadPerformance();
}

ManagingPosters::~ManagingPosters()
{
    delete mUi;
    delete &m_user;
}

void ManagingPosters::descriptionPRM(int row, int /*column*/)
{   
    for (int i = 0, size_performance = m_listPerformance.size(); i < size_performance; i++)
    {
        if (m_listPosters[row].namePerformance() == m_listPerformance[i].NamePerformance())
        {
            const Performance &performance = m_listPerformance[i];
            QMessageBox aboutDlg(this);
            aboutDlg.setTextFormat(Qt::RichText);
            aboutDlg.setWindowTitle(tr("About %1").arg(performance.NamePerformance()));
            aboutDlg.setIcon(QMessageBox::Information);
            aboutDlg.setText(tr("Автор спектакля: %1 <br>"
                                "Продюсер спектакля: %2 <br> "
                                "Актеры, участвующие в спектакле: <br>")
                             .arg(performance.Author()).arg(performance.Producer()));

            aboutDlg.exec();
            size_performance = 0;
        }
    }
}

void ManagingPosters::loadPosters()
{
    m_listPosters.clear();

    QFile file(Config::filePosters);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);

        while (!ist.atEnd()) {
            Posters poster;
            ist >> poster;
            m_listPosters.append(poster);
        }
    }

    int row = 0;
    foreach (const Posters &poster, m_listPosters)
    {
        QTableWidgetItem *item_NamePerformance = new QTableWidgetItem(poster.namePerformance());
        QTableWidgetItem *item_date = new QTableWidgetItem(poster.datePerformance().toString("d-MMMM-yyyy"));
        QTableWidgetItem *item_time = new QTableWidgetItem(poster.timePerformance().toString("hh:mm"));
        QTableWidgetItem *item_countSeats = new QTableWidgetItem(QString::number(poster.countSeats()));
        QTableWidgetItem *item_countFreeSeats = new QTableWidgetItem(QString::number(poster.countFreeSeats()));

        mUi->tablePerformance->insertRow(row);
        mUi->tablePerformance->setItem(row, 0, item_NamePerformance);
        mUi->tablePerformance->setItem(row, 1, item_date);
        mUi->tablePerformance->setItem(row, 2, item_time);
        mUi->tablePerformance->setItem(row, 3, item_countSeats);
        mUi->tablePerformance->setItem(row, 4, item_countFreeSeats);
        row++;
    }
}

void ManagingPosters::loadPerformance()
{
    m_listPerformance.clear();

    QFile file(Config::filePerformance);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);

        while (!ist.atEnd()) {
            Performance performance;
            ist >> performance;
            m_listPerformance.append(performance);
        }
    }
}

/*void ManagingPosters::on_lineFindPosters_textChanged(const QString &text)
{
    QStringList listStr = text.split(" ");
    listStr.removeAll(QString());

    for (int i = 0; i < m_listPosters.size(); i++) {
        mUi->tablePerformance->showRow(i);
    }

    int row = 0;
    foreach (const Posters &poster, m_listPosters)
    {
        int count = 0;
        foreach (const QString &str, listStr) {
            if (poster.namePerformance().contains(str))
            {
                count++;
            }
        }
        if (count != listStr.size()) {
            mUi->tablePerformance->hideRow(row);
        }
        row++;
    }
}*/

const QList<Posters> &ManagingPosters::listPosters() const
{
    return m_listPosters;
}

const QList<Performance> &ManagingPosters::listPerformance() const
{
    return m_listPerformance;
}

void ManagingPosters::on_addPoster_clicked()
{
    Posters poster;
    AddPosters dialog(&poster, m_listPosters, AddPosters::Create, this);
    dialog.setWindowTitle(windowTitle());

    if (dialog.exec() == QDialog::Accepted)
    {
        m_listPosters.append(poster);

        QFile file(Config::filePosters);
        file.open(QIODevice::Append);
        QDataStream ost(&file);
        ost << poster;

        QTableWidgetItem *item_NamePerformance = new QTableWidgetItem(poster.namePerformance());
        QTableWidgetItem *item_date = new QTableWidgetItem(poster.datePerformance().toString("d-MMMM-yyyy"));
        QTableWidgetItem *item_time = new QTableWidgetItem(poster.timePerformance().toString("hh:mm"));
        QTableWidgetItem *item_countSeats = new QTableWidgetItem(QString::number(poster.countSeats()));
        QTableWidgetItem *item_countFreeSeats = new QTableWidgetItem(QString::number(poster.countFreeSeats()));

        int row = mUi->tablePerformance->rowCount();
        mUi->tablePerformance->insertRow(row);
        mUi->tablePerformance->setItem(row, 0, item_NamePerformance);
        mUi->tablePerformance->setItem(row, 1, item_date);
        mUi->tablePerformance->setItem(row, 2, item_time);
        mUi->tablePerformance->setItem(row, 3, item_countSeats);
        mUi->tablePerformance->setItem(row, 4, item_countFreeSeats);
    }
}


void ManagingPosters::on_removePoster_clicked()
{
    int currentRow = mUi->tablePerformance->currentRow();
    if (currentRow != -1) {
        m_listPosters.removeAt(currentRow);

        QFile read_file(Config::filePosters);
        if (read_file.open(QIODevice::ReadOnly))
        {
            QFile write_file("buf_file_posters");
            write_file.open(QIODevice::WriteOnly);

            QDataStream read_ist(&read_file);
            QDataStream write_ist(&write_file);

            int countReads = 0;
            while (!read_ist.atEnd()) {
                Posters buf_posters;
                read_ist >> buf_posters;

                if (countReads++ != currentRow)
                {
                    write_ist << buf_posters;
                }
            }
            read_file.close();
            read_file.remove();
            write_file.close();
            write_file.rename(Config::filePosters);
        }
        mUi->tablePerformance->removeRow(currentRow);
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбрана ни одна афиша!");
    }
}

void ManagingPosters::on_editPoster_clicked()
{
    int currentRow = mUi->tablePerformance->currentRow();
    if (currentRow != -1) {
        Posters poster = m_listPosters[currentRow];
        AddPosters dialog(&poster, m_listPosters, AddPosters::Edit, this);
        dialog.setWindowTitle(windowTitle());

        if (dialog.exec() == QDialog::Accepted)
        {
            m_listPosters[currentRow] = poster;

            QFile read_file(Config::filePosters);
            if (read_file.open(QIODevice::ReadOnly)) {
                QFile write_file("buf_file_poster");
                write_file.open(QIODevice::WriteOnly);

                QDataStream read_ist(&read_file);
                QDataStream write_ist(&write_file);

                int countSeats = 0;
                while (!read_ist.atEnd()) {
                    Posters buf_poster;
                    read_ist >> buf_poster;

                    if (countSeats++ == currentRow)
                    {
                        buf_poster = poster;
                    }

                    write_ist << buf_poster;
                }
                read_file.close();
                read_file.remove();

                write_file.close();
                write_file.rename(Config::filePosters);
            }
            poster.setCountFreeSeats(poster.countFreeSeats() - 1);

            mUi->tablePerformance->item(currentRow, 0)->setText(poster.namePerformance());
            mUi->tablePerformance->item(currentRow, 1)->setText(poster.datePerformance().toString("d-MMMM-yyyy"));
            mUi->tablePerformance->item(currentRow, 2)->setText(poster.timePerformance().toString("hh:mm"));
            mUi->tablePerformance->item(currentRow, 3)->setText(QString::number(poster.countSeats()));
            mUi->tablePerformance->item(currentRow, 4)->setText(QString::number(poster.countFreeSeats()));
        }
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбрана ни одна афиша!");
    }
}

void ManagingPosters::on_buyTicket_clicked()
{
    Ticket ticket;
    ByTicket dialog(ticket, this);
    dialog.setWindowTitle("Покупка билета");
    dialog.exec();
}
