#ifndef ADDPERFORMANCE_H
#define ADDPERFORMANCE_H

#include <QDialog>
#include "actors.h"
class Performance;

namespace Ui {
class AddPerformance;
}

class AddPerformance : public QDialog
{
    Q_OBJECT
public:
    enum Type { Create, Edit};
    explicit AddPerformance(Performance *performance, Type type, QWidget *parent = nullptr);
    ~AddPerformance();

private:
    Ui::AddPerformance *mUi;
    Performance *m_performance;
    Type m_type;
    QList<Actors> m_listActors;

public slots:
    void accept();

    void loadActers();
};

#endif // ADDPERFORMANCE_H
