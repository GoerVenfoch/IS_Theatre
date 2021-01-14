#ifndef STARTMENU_H
#define STARTMENU_H

#include "user.h"
#include "ui_startMenu.h"

namespace Ui {
class startMenu;
}

class startMenu : public QWidget
{
    Q_OBJECT
public:
    explicit startMenu(User &user, QWidget *parent = nullptr);
    ~startMenu();

private slots:
    void on_managing_user_clicked();

    void on_posters_clicked();

    void on_managing_posters_clicked();

    void on_managing_tickets_clicked();

    void on_cast_clicked();

    void on_managing_performance_clicked();

    void on_managing_cast_clicked();

signals:
    void exitMenu();
    void clickedPoster(User*);

private:
    Ui::startMenu *mUi;
    User &m_user;

};

#endif // STARTMENU_H
