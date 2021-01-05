#include "managingperformance.h"
#include "ui_managingPerformance.h"
#include "addperformance.h"

#include <QFile>
#include <QMessageBox>


managingPerformance::managingPerformance(User &user, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::managingPerformance),
    m_user(user)
{
    mUi->setupUi(this);
    setWindowTitle("РЕДАКТИРОВАНИЕ СПЕКТАКЛЕЙ");
    mUi->tablePerformance->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    if (m_user.status() == User::Viewer)
    {
        mUi->addPerformance->hide();
        mUi->editPerformance->hide();
        mUi->removePerformance->hide();
    }

    loadPerformance();
}

managingPerformance::~managingPerformance()
{
    delete mUi;
}

void managingPerformance::loadPerformance()
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

    int row = 0;
    foreach (const Performance &performance, m_listPerformance)
    {
        QTableWidgetItem *item_NamePerformance = new QTableWidgetItem(performance.NamePerformance());
        QTableWidgetItem *item_Author = new QTableWidgetItem(performance.Author());
        QTableWidgetItem *item_Producer = new QTableWidgetItem(performance.Producer());

        mUi->tablePerformance->insertRow(row);
        mUi->tablePerformance->setItem(row, 0, item_NamePerformance);
        mUi->tablePerformance->setItem(row, 1, item_Author);
        mUi->tablePerformance->setItem(row, 2, item_Producer);
        row++;
    }
}

void managingPerformance::on_addPerformance_clicked()
{
    Performance performance;
    AddPerformance dialog(&performance, AddPerformance::Create, this);
    dialog.setWindowTitle(windowTitle());

    if (dialog.exec() == QDialog::Accepted)
    {
        m_listPerformance.append(performance);

        QFile file(Config::filePerformance);
        file.open(QIODevice::Append);
        QDataStream ost(&file);
        ost << performance;

        QTableWidgetItem *item_NamePerformance = new QTableWidgetItem(performance.NamePerformance());
        QTableWidgetItem *item_Author = new QTableWidgetItem(performance.Author());
        QTableWidgetItem *item_Producer = new QTableWidgetItem(performance.Producer());

        int row = mUi->tablePerformance->rowCount();
        mUi->tablePerformance->insertRow(row);
        mUi->tablePerformance->setItem(row, 0, item_NamePerformance);
        mUi->tablePerformance->setItem(row, 1, item_Author);
        mUi->tablePerformance->setItem(row, 2, item_Producer);
    }
}

void managingPerformance::on_editPerformance_clicked()
{
    int currentRow = mUi->tablePerformance->currentRow();
    if (currentRow != -1) {
        Performance performance = m_listPerformance[currentRow];
        AddPerformance dialog(&performance, AddPerformance::Edit, this);
        dialog.setWindowTitle(windowTitle());

        if (dialog.exec() == QDialog::Accepted)
        {
            m_listPerformance[currentRow] = performance;

            QFile read_file(Config::filePerformance);
            if (read_file.open(QIODevice::ReadOnly)) {
                QFile write_file("buf_file_performance");
                write_file.open(QIODevice::WriteOnly);

                QDataStream read_ist(&read_file);
                QDataStream write_ist(&write_file);

                int countSeats = 0;
                while (!read_ist.atEnd()) {
                    Performance buf_performance;
                    read_ist >> buf_performance;

                    if (countSeats++ == currentRow)
                    {
                        buf_performance = performance;
                    }

                    write_ist << buf_performance;
                }
                read_file.close();
                read_file.remove();

                write_file.close();
                write_file.rename(Config::filePerformance);
            }

            mUi->tablePerformance->item(currentRow, 0)->setText(performance.NamePerformance());
            mUi->tablePerformance->item(currentRow, 1)->setText(performance.Author());
            mUi->tablePerformance->item(currentRow, 2)->setText(performance.Producer());            
        }
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один спектакль!");
    }
}

void managingPerformance::on_removePerformance_clicked()
{
    int currentRow = mUi->tablePerformance->currentRow();
    if (currentRow != -1) {
        m_listPerformance.removeAt(currentRow);

        QFile read_file(Config::filePerformance);
        if (read_file.open(QIODevice::ReadOnly))
        {
            QFile write_file("buf_file_performance");
            write_file.open(QIODevice::WriteOnly);

            QDataStream read_ist(&read_file);
            QDataStream write_ist(&write_file);

            int countReads = 0;
            while (!read_ist.atEnd()) {
                Performance buf_performance;
                read_ist >> buf_performance;

                if (countReads++ != currentRow)
                {
                    write_ist << buf_performance;
                }
            }
            read_file.close();
            read_file.remove();
            write_file.close();
            write_file.rename(Config::filePerformance);
        }
        mUi->tablePerformance->removeRow(currentRow);
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один спектакль!");
    }
}
