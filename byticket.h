#ifndef BYTICKET_H
#define BYTICKET_H

#include <QDialog>
#include "ticket.h"

namespace Ui {
class Ticket;
}

class ByTicket : public QDialog
{
    Q_OBJECT

public:
    explicit ByTicket(Ticket &ticket, QWidget *parent = nullptr);
    ~ByTicket();

private:
    Ui::Ticket *mUi;
    Ticket &m_ticket;
public slots:
    void accept();
};

#endif // BYTICKET_H
