#include "managingtickets.h"
#include "menucasher.h"

ManagingTickets::ManagingTickets(QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::ManagingTicket)
{
    mUi->setupUi(this);
    setWindowTitle("Управление билетами");
    mUi->tableTickets->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    loadTicket();
    loadPoster();
}

ManagingTickets::~ManagingTickets()
{
    delete mUi;
}

const QList<Ticket> &ManagingTickets::listTicket() const
{
    return m_listTicket;
}

void ManagingTickets::loadTicket()
{
    m_listTicket.clear();

    QFile file(Config::fileTicket);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);

        while (!ist.atEnd()) {
            Ticket ticket;
            ist >> ticket;
            m_listTicket.append(ticket);
        }
    }
    int row = 0;
    QString rowInt, placeInt;
    foreach (const Ticket &ticket, m_listTicket)
    {
        placeInt.setNum(ticket.place());
        rowInt.setNum(ticket.row());
        QTableWidgetItem *item_firstName = new QTableWidgetItem(ticket.firstName());
        QTableWidgetItem *item_secondName = new QTableWidgetItem(ticket.secondName());
        QTableWidgetItem *item_fatherName = new QTableWidgetItem(ticket.fatherName());
        QTableWidgetItem *item_phone = new QTableWidgetItem(ticket.phone());
        QTableWidgetItem *item_combobox = new QTableWidgetItem(ticket.comboString());
        QTableWidgetItem *item_row = new QTableWidgetItem(rowInt);
        QTableWidgetItem *item_place = new QTableWidgetItem(placeInt);

        mUi->tableTickets->insertRow(row);
        mUi->tableTickets->setItem(row, 0, item_firstName);
        mUi->tableTickets->setItem(row, 1, item_secondName);
        mUi->tableTickets->setItem(row, 2, item_fatherName);
        mUi->tableTickets->setItem(row, 3, item_phone);
        mUi->tableTickets->setItem(row, 4, item_combobox);
        mUi->tableTickets->setItem(row, 5, item_row);
        mUi->tableTickets->setItem(row, 6, item_place);
        row++;
    }
}

void ManagingTickets::loadPoster()
{
    m_listPoster.clear();

    QFile file(Config::filePosters);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);

        while (!ist.atEnd()) {
            Posters poster;
            ist >> poster;
            m_listPoster.append(poster);
        }
    }
}

void ManagingTickets::menuCashier(int row)
{
    const Ticket &ticket = m_listTicket[row];
    int sizePoster = m_listPoster.size();
    Posters post;
    for (int i = 0; i < sizePoster; i++)
    {
        if (ticket.performance() == m_listPoster[i].namePerformance())
        {
            post = m_listPoster[i];
            break;
        }
        else
        {
            post.namePerformance() = "Афиши нет";
        }
    }
    Posters &poster = post;
        MenuCasher dialog(row, poster, ticket, this);
    dialog.setWindowTitle(Config::nameApplication);
    dialog.exec();

    QFile read_file(Config::fileTicket);
    if (read_file.open(QIODevice::ReadOnly))
    {
        QFile write_file("buf_file_ticket");
        write_file.open(QIODevice::WriteOnly);

        QDataStream read_ist(&read_file);
        QDataStream write_ist(&write_file);

        int countReads = 0;
        while (!read_ist.atEnd()) {
            Ticket buf_ticket;
            read_ist >> buf_ticket;

            if (countReads++ != row)
            {
                write_ist << buf_ticket;
            }
        }
        read_file.close();
        read_file.remove();
        write_file.close();
        write_file.rename(Config::fileTicket);
    }
    mUi->tableTickets->removeRow(row);
}

void ManagingTickets::on_tableTickets_cellDoubleClicked(int row)
{
    ManagingTickets::menuCashier(row);
}
