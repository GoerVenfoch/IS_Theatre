#include "startMenu.h"
#include "managingusers.h"
#include "config.h"
#include "ui_startMenu.h"
#include "managingposters.h"
#include "mainwidget.h"
#include "managingtickets.h"
#include "managingperformance.h"
#include "cast.h"

#include "QMessageBox"

startMenu::startMenu(User &user, QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::startMenu),
    m_user(user)
{
    mUi->setupUi(this);
    connect(mUi->exitMenu, SIGNAL(clicked()),
            this, SIGNAL(exitMenu()));

    if (m_user.status() != User::Admin)
    {
        mUi->managing_cast->hide();
        mUi->managing_cast->hide();
        mUi->managing_performance->hide();
        mUi->managing_posters->hide();
        mUi->managing_user->hide();
    }

    if (m_user.status() == User::Viewer)
        mUi->managing_tickets->hide();

    if (m_user.status() != User::Viewer)
    {
        mUi->cast->hide();
        mUi->posters->hide();
    }
}

startMenu::~startMenu()
{
    delete mUi;
    delete &m_user;
}

void startMenu::on_managing_user_clicked()
{
    managingUsers dialog(this);
    dialog.setWindowTitle(Config::nameApplication);
    dialog.exec();
}

void startMenu::on_posters_clicked()
{
    ManagingPosters dialog(m_user, this);
    dialog.exec();
}

void startMenu::on_managing_posters_clicked()
{
    ManagingPosters dialog(m_user, this);
    dialog.exec();
}

void startMenu::on_managing_tickets_clicked()
{
    ManagingTickets dialog(this);
    dialog.exec();
}

void startMenu::on_cast_clicked()
{
    cast dialog(m_user, this);
    dialog.exec();
}

void startMenu::on_managing_performance_clicked()
{
    managingPerformance dialog(m_user, this);
    dialog.exec();
}

void startMenu::on_managing_cast_clicked()
{
    cast dialog(m_user, this);
    dialog.exec();
}
