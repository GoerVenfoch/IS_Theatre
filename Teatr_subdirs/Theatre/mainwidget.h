#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
class User;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QWidget *m_currentWidget;

private slots:
    void slotOpenAuthorization();
    void slotOpenRegistration();
    void slotOpenStartMenu(User*);
};
#endif // MAINWIDGET_H
