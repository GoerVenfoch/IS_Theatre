#include "addactor.h"
#include "ui_addActor.h"
#include "config.h"

#include <QFile>
#include <QDataStream>
#include <QInputDialog>

addActor::addActor(Actors &actor, Type type, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::addActor),
    m_actor(actor),
    m_type(type)
{
    mUi->setupUi(this);
    setWindowTitle("Актерский состав");
    if (m_type == Edit) {
        mUi->mainLabel->setText("РЕДАКТИРОВАНИЕ АКТРЕРА");
        mUi->firstName->setText(m_actor.firstName());
        mUi->secondName->setText(m_actor.secondName());
        mUi->born->setDate(m_actor.born());
        m_listActor = m_actor.performances();

        int row = 0;
        foreach (const QString &performance, m_actor.performances())
        {
            QTableWidgetItem *item_NamePerformance = new QTableWidgetItem(performance);

            mUi->listPerformance->insertRow(row);
            mUi->listPerformance->setItem(row, 0, item_NamePerformance);
            row++;
        }
    }
    else mUi->mainLabel->setText("ДОБАВЛЕНИЕ АКТЕРА");
}

addActor::~addActor()
{
    delete mUi;
}

const Actors &addActor::getActor()
{
    return m_actor;
}

bool addActor::isActorExists(const QString firstname, const QString secondname)
{
    QFile file(Config::fileActor);
    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly))
        {
            mUi->labelError->setText("Ошибка: чтение файла невозможно!");
            return false;
        }
        QDataStream ist(&file);

        while (!ist.atEnd())
        {
            Actors buf_actor;
            ist >> buf_actor;
            if (buf_actor.firstName() == firstname && buf_actor.secondName() == secondname) return true;
        }
        return false;
    }
    else return false;
}

void addActor::accept()
{
    QString firstName = mUi->firstName->text();
    QString secondName = mUi->secondName->text();
    QDate born = mUi->born->date();
    QList<QString> listPerformance = m_listActor;

    if (firstName == "" || secondName == "" || listPerformance.size() == 0) mUi->labelError->setText("Ошибка: заполните все поля!");
    else if (isActorExists(firstName, secondName))  mUi->labelError->setText("Ошибка: актер уже добавлен!");
    else
    {
        m_actor.setData(firstName, secondName, born, listPerformance);

        if (m_type == Create)
        {
        QFile file(Config::fileActor);
        file.open(QIODevice::Append);
        QDataStream ost(&file);
        ost << m_actor;
        }
        QDialog::accept();
    }
}

void addActor::on_createActor_clicked()
{
    QString str = QInputDialog::getText( 0,
                                         "Добавление спектакля",
                                         "Введите название спектакля: ",
                                         QLineEdit::Normal);
    m_listActor.append(str);
    QTableWidgetItem *item_actor = new QTableWidgetItem(str);
    mUi->listPerformance->insertRow(m_listActor.size() - 1);
    mUi->listPerformance->setItem(m_listActor.size() - 1, 0, item_actor);
}

void addActor::on_listPerformance_cellDoubleClicked(int row)
{
    QString str = QInputDialog::getText( 0,
                                         "Изменение спектакля",
                                         "Введите название спектакля: ",
                                         QLineEdit::Normal,
                                         m_listActor[row]);
    m_listActor[row] = str;
    mUi->listPerformance->item(row, 0)->setText(str);
}

void addActor::on_delActor_clicked()
{
    int currentRow = mUi->listPerformance->currentRow();
    if (currentRow != -1)
    {
        m_listActor.removeAt(currentRow);
        mUi->listPerformance->removeRow(currentRow);
    }
}
