#ifndef ADDPOSTERS_H
#define ADDPOSTERS_H

#include <QDialog>
#include "performance.h"

class Posters;

namespace Ui {
class AddPosters;
}

class AddPosters : public QDialog
{
    Q_OBJECT
public:
        enum Type { Create, Edit};
        explicit AddPosters(Posters &poster, const QList<Posters> &listPosters, const QList<Performance> &listperformance, Type type, QWidget *parent = nullptr);
        ~AddPosters();
        bool isPosterExists(const QString namePerformance);
        bool isPerformanceExists(const QString namePerformance);

private:
    Ui::AddPosters *mUi;
    Posters &m_posters;
    const QList<Posters> &m_listPosters;
    const QList<Performance> &m_listPerformance;
    Type m_type;

public slots:
    void accept();
};

#endif // ADDPOSTERS_H
