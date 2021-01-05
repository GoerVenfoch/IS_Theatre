#include "menucasher.h"
#include "ui_MenuCashier.h"
#include "byticket.h"

MenuCasher::MenuCasher(int row, Posters &poster, const Ticket &ticket, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::MenuCasher),
    m_ticket(ticket),
    m_poster(poster),
    m_rowTicket(row)
{
    mUi->setupUi(this);
    mUi->performance->setText(poster.namePerformance());
    mUi->countViewer->setText(QString::number(m_poster.countSeats() - m_poster.countFreeSeats()));
    int countFreePlace = m_poster.countFreeSeats();
    if (countFreePlace == 0)
    {
        mUi->countFreePlace->setText("Увы, мест нет. Возвращайтесь через 3 000 лет!");
        mUi->buttonBuyTicket->setEnabled(false);
    }
    else mUi->countFreePlace->setText(QString::number(countFreePlace));
}

MenuCasher::~MenuCasher()
{
    delete mUi;
}

void MenuCasher::on_buttonBuyTicket_clicked()
{
        int countFreePlace = mUi->countFreePlace->text().toInt(), countViewer = mUi->countViewer->text().toInt();
        countFreePlace--, countViewer++;
        if (countFreePlace == 0)
        {
            mUi->countFreePlace->setText("А мест то нет!");
            mUi->buttonBuyTicket->setEnabled(false);
        }
        else
        {
            mUi->countFreePlace->setText(QString::number(countFreePlace));
            mUi->countViewer->setText(QString::number(countViewer));
        }
        mUi->buttonBuyTicket->setEnabled(false);
}

void MenuCasher::on_buttonHandOverTicket_clicked()
{
        int countFreePlace = mUi->countFreePlace->text().toInt(), countViewer = mUi->countViewer->text().toInt();
        countFreePlace++, countViewer--;
        if (countFreePlace == 0)
        {
            mUi->countFreePlace->setText("НЕТ МЕСТ");
            mUi->buttonBuyTicket->setEnabled(false);
        }
        else
        {
            mUi->countFreePlace->setText(QString::number(countFreePlace));
            mUi->countViewer->setText(QString::number(countViewer));
        }
        mUi->buttonHandOverTicket->setEnabled(false);
}
