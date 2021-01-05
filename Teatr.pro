QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actors.cpp \
    add_user.cpp \
    addactor.cpp \
    addperformance.cpp \
    addposters.cpp \
    byticket.cpp \
    cast.cpp \
    main.cpp \
    mainwidget.cpp \
    managingperformance.cpp \
    managingposters.cpp \
    managingtickets.cpp \
    managingusers.cpp \
    menucasher.cpp \
    performance.cpp \
    posters.cpp \
    signin.cpp \
    signup.cpp \
    startMenu.cpp \
    ticket.cpp \
    user.cpp

HEADERS += \
    actors.h \
    add_user.h \
    addactor.h \
    addperformance.h \
    addposters.h \
    byticket.h \
    cast.h \
    config.h \
    mainwidget.h \
    managingperformance.h \
    managingposters.h \
    managingtickets.h \
    managingusers.h \
    menucasher.h \
    performance.h \
    posters.h \
    signin.h \
    signup.h \
    startMenu.h \
    ticket.h \
    user.h

FORMS += \
    ActorPerformance.ui \
    AddPoster.ui \
    Add_Performance.ui \
    Add_User.ui \
    ByTicket.ui \
    MamagingTickets.ui \
    Managing_Posters.ui \
    Managing_Tickets.ui \
    Managing_Users.ui \
    MenuCashier.ui \
    addActor.ui \
    authorization.ui \
    cast.ui \
    managingPerformance.ui \
    registration.ui \
    startMenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32 {
        RC_FILE += file.rc
        OTHER_FILES += file.rc
}

