#ifndef MANAGINGPOSTERS_H
#define MANAGINGPOSTERS_H

#include "user.h"
#include "posters.h"
#include "performance.h"
#include "ui_Managing_Posters.h"
#include "ticket.h"

#include <QDialog>

namespace Ui {
class ManagingPosters;
}

class ManagingPosters : public QDialog
{
    Q_OBJECT

public:
    explicit ManagingPosters(User &user, QWidget *parent = nullptr);
    ~ManagingPosters();

    const QList<Posters> &listPosters() const;
    const QList<Performance> &listPerformance() const;

private slots:
    void descriptionPRM(int row);
    void on_addPoster_clicked();
    void on_removePoster_clicked();
    void on_editPoster_clicked();

void on_lineFindPosters_textChanged(const QString &text);

void on_buyTicket_clicked();

    private:
    Ui::ManagingPosters *mUi;
    User &m_user;
    QList<Posters> m_listPosters;
    QList<Performance> m_listPerformance;
    QList<Ticket> m_ticket;

    void loadPosters();
    void loadPerformance();

};

#endif // MANAGINGPOSTERS_H
