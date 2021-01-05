#ifndef MANAGINGTICKETS_H
#define MANAGINGTICKETS_H

#include "QDialog"
#include <QList>
#include "ticket.h"
#include "ui_Managing_Tickets.h"
#include "config.h"
#include "posters.h"

#include <QFile>
class Ticket;

namespace Ui {
class ManagingTicket;
}

class ManagingTickets : public QDialog
{
    Q_OBJECT

public:
    explicit ManagingTickets(QWidget *parent = nullptr);
    ~ManagingTickets();

    const QList<Ticket> &listTicket() const;
    void menuCashier(int row);

private slots:
    void on_tableTickets_cellDoubleClicked(int row);

private:
    Ui::ManagingTicket *mUi;
    QList<Ticket> m_listTicket;
    QList<Posters> m_listPoster;

    void loadTicket();
    void loadPoster();
};

#endif // MANAGINGTICKETS_H
