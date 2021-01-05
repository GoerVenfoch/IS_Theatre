#include "addperformanceactor.h"
#include "ui_addPerformanceActor.h"

addPerformanceActor::addPerformanceActor(, Type type, QWidget *parent) :
    QDialog(parent),
    m_performance(performance),
    mUi(new Ui::addPerformanceActors),
    m_role(role)
{
    mUi->setupUi(this);

    if (type == Edit) {
        mUi->mainLabel->setText("РЕДАКТИРОВАНИЕ АКТЕРА");
        mUi->firstName->setText();
        mUi->author->setText(m_performance->Author());
        mUi->producer->setText(m_performance->Producer());
    }
    else {
        mUi->mainLabel->setText("ДОБАВЛЕНИЕ АКТЕРА");
    }
}

addPerformanceActor::~addPerformanceActor()
{

}
