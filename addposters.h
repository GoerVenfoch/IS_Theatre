#ifndef ADDPOSTERS_H
#define ADDPOSTERS_H

#include <QDialog>
class Posters;

namespace Ui {
class AddPosters;
}

class AddPosters : public QDialog
{
    Q_OBJECT
public:
        enum Type { Create, Edit};
        explicit AddPosters(Posters *poster, const QList<Posters> &listPosters, Type type, QWidget *parent = nullptr);
        ~AddPosters();

private:
    Ui::AddPosters *mUi;
    Posters *m_posters;
    const QList<Posters> &m_listPosters;
    Type m_type;

public slots:
    void accept();
};

#endif // ADDPOSTERS_H
