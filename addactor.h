#ifndef ADDACTOR_H
#define ADDACTOR_H

#include <QDialog>
#include "actors.h"
#include "performance.h"

namespace Ui {
class addActor;
}

class addActor : public QDialog
{
    Q_OBJECT
public:
    enum Type { Create, Edit};
    explicit addActor(Actors &actor, Type type, QWidget *parent = nullptr);
    ~addActor();
    const Actors &getActor();
    bool isActorExists(const QString firstname, const QString secondname);
    bool isPerformanceExists(const QString namePerformance);
    void loadPerformance();

private:
    Ui::addActor *mUi;
    Actors &m_actor;
    Type m_type;
    QList<QString> m_listActor;
    QList<Performance> m_listPerformance;

public slots:
    void accept();

private slots:
    void on_createActor_clicked();
    void on_listPerformance_cellDoubleClicked(int row);
    void on_delActor_clicked();
};

#endif // ADDACTOR_H
