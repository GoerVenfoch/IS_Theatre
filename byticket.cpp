#include "byticket.h"
#include "ui_ByTicket.h"
#include <QFile>
#include "config.h"

ByTicket::ByTicket(Ticket &ticket, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Ticket),
    m_ticket(ticket)
{
    mUi->setupUi(this);
    setWindowTitle("Покупка билета");
}

ByTicket::~ByTicket()
{
    delete mUi;
}

void ByTicket::accept()
{
    const QString performance = mUi->performanceedit->text();
    const QString firstName = mUi->firstNameedit->text();
    const QString secondName = mUi->secondNameedit->text();
    const QString fatherName = mUi->fatherNameedit->text();
    const QString phone = mUi->phoneedit->text();
    int row = mUi->row->value();
    int place = mUi->place->value();
    int combobox = mUi->comboBox->currentIndex();

    if (firstName == "" || secondName == "" || fatherName == "" || phone == "" || row == 0 || place == 0) {
        mUi->labelerror->setText("Ошибка: заполните все поля!");
    }
    else {
        m_ticket.setData(performance, firstName, secondName, fatherName, phone, Ticket::Combo(combobox), row, place);
        QFile file(Config::fileTicket);
        file.open(QIODevice::Append);
        QDataStream ost(&file);
        ost << m_ticket;
        QDialog::accept();
    }
}
