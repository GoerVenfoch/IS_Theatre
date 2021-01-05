#ifndef ADDPERFORMANCEACTOR_H
#define ADDPERFORMANCEACTOR_H

#include <QDialog>

namespace Ui {
class addPerformanceActors;
}

class addPerformanceActor : QDialog
{
    Q_OBJECT
public:
    enum Type { Create, Edit};
    explicit addPerformanceActor(QString performance, QString role, Type type, QWidget *parent = nullptr);
    ~addPerformanceActor();

private:
    Ui::addPerformanceActors *mUi;
    QString m_performance;
    QString m_role;
};

#endif // ADDPERFORMANCEACTOR_H
