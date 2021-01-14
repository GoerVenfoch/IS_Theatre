#ifndef MENUCASHER_H
#define MENUCASHER_H

#include <QDialog>
#include "ticket.h"
#include "posters.h"
class Poster;

namespace Ui {
class MenuCasher;
}

class MenuCasher : public QDialog
{
    Q_OBJECT
public:
    explicit MenuCasher(int row, Posters &poster, const Ticket &ticket, QWidget *parent = nullptr);
    ~MenuCasher();

private slots:
    void on_buttonBuyTicket_clicked();
    void on_buttonHandOverTicket_clicked();

private:
    Ui::MenuCasher *mUi;
    const Ticket &m_ticket;
    Posters &m_poster;
    int m_rowTicket;
};

#endif // MENUCASHER_H
