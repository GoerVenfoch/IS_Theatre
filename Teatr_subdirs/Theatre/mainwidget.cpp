#include "mainwidget.h"

#include "config.h"
#include "signup.h"
#include "signin.h"
#include "startMenu.h"
#include "managingposters.h"

#include <QFile>

#include <QDebug>
#include "user.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      m_currentWidget(nullptr)
{
    setWindowTitle(Config::nameApplication);
    if (!QFile(Config::fileUsers).exists())
    {
        m_currentWidget = new SignUp(SignUp::Admin, this);
        connect(m_currentWidget, SIGNAL(openAuthorization()),
                this, SLOT(slotOpenAuthorization()));
    }
    else
    {
        m_currentWidget = new SignIn(this);
        connect(m_currentWidget, SIGNAL(openRegistration()),
                this, SLOT(slotOpenRegistration()));
        connect(m_currentWidget, SIGNAL(succesfulEntry(User*)),
                this, SLOT(slotOpenStartMenu(User*)));
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_currentWidget);
    setLayout(layout);
}

MainWidget::~MainWidget()
{
    delete m_currentWidget;
}

void MainWidget::slotOpenAuthorization()
{
    delete m_currentWidget;
    m_currentWidget = new SignIn(this);
    connect(m_currentWidget, SIGNAL(openRegistration()),
            this, SLOT(slotOpenRegistration()));
    connect(m_currentWidget, SIGNAL(succesfulEntry(User*)),
            this, SLOT(slotOpenStartMenu(User*)));
    layout()->addWidget(m_currentWidget);
}

void MainWidget::slotOpenRegistration()
{
    delete m_currentWidget;
    m_currentWidget = new SignUp(SignUp::Passenger, this);
    connect(m_currentWidget, SIGNAL(openAuthorization()),
            this, SLOT(slotOpenAuthorization()));
    layout()->addWidget(m_currentWidget);
}

void MainWidget::slotOpenStartMenu(User *user)
{
    delete m_currentWidget;
    m_currentWidget = new startMenu(*user, this);
    connect(m_currentWidget, SIGNAL(exitMenu()),
            this, SLOT(slotOpenAuthorization()));
    layout()->addWidget(m_currentWidget);
}
