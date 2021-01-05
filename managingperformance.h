#ifndef MANAGINGPERFORMANCE_H
#define MANAGINGPERFORMANCE_H

#include <QDialog>
#include "performance.h"
#include "user.h"
#include "config.h"

namespace Ui {
class managingPerformance;
}
class managingPerformance : public QDialog
{
    Q_OBJECT

public:
    explicit managingPerformance(User &user, QWidget *parent = nullptr);
    ~managingPerformance();

private slots:
    void on_addPerformance_clicked();
    void on_editPerformance_clicked();
    void on_removePerformance_clicked();

    void on_lineFindPerformance_textChanged(const QString &text);

private:
    Ui::managingPerformance *mUi;
    QList<Performance> m_listPerformance;
    User &m_user;

    void loadPerformance();
};

#endif // MANAGINGPERFORMANCE_H
