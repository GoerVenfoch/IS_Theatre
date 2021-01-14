#ifndef CAST_H
#define CAST_H

#include "actors.h"
#include "config.h"
#include "user.h"
#include <QDialog>
#include <QFile>

namespace Ui {
class cast;
}
class cast : public QDialog
{
    Q_OBJECT

public:
    explicit cast(User &user, QWidget *parent = nullptr);
    ~cast();

void loadActors();

private slots:
void on_tableActers_cellActivated(int row);
void on_add_clicked();
void on_edit_clicked();
void on_remove_clicked();

private:
    Ui::cast *mUi;
    User &m_user;
    QList<Actors> m_actor;
};

#endif // CAST_H
