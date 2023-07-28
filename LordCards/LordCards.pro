QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS += ico/myico.ico
QT += widgets

SOURCES += \
    card.cpp \
    cardlist.cpp \
    cardsound.cpp \
    main.cpp \
    maindialog.cpp \
    rulers.cpp

HEADERS += \
    card.h \
    cardlist.h \
    cardsound.h \
    maindialog.h \
    rulers.h

FORMS += \
    card.ui \
    maindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    sound/10.wav \
    sound/11.wav \
    sound/12.wav \
    sound/13.wav \
    sound/14.wav \
    sound/15.wav \
    sound/16.wav \
    sound/17.wav \
    sound/3.wav \
    sound/4.wav \
    sound/5.wav \
    sound/6.wav \
    sound/7.wav \
    sound/8.wav \
    sound/9.wav \
    sound/bkMusic.wav \
    sound/bujiao.wav \
    sound/callLord.wav \
    sound/dui10.wav \
    sound/dui11.wav \
    sound/dui12.wav \
    sound/dui13.wav \
    sound/dui14.wav \
    sound/dui15.wav \
    sound/dui3.wav \
    sound/dui4.wav \
    sound/dui5.wav \
    sound/dui6.wav \
    sound/dui7.wav \
    sound/dui8.wav \
    sound/dui9.wav \
    sound/feiji.wav \
    sound/feijidaichibang.wav \
    sound/jiaodizhu.wav \
    sound/liandui.wav \
    sound/loseMusic.wav \
    sound/noCall.wav \
    sound/passMusic.wav \
    sound/planeMusic.wav \
    sound/qiangdizhu.wav \
    sound/sandaiyi.wav \
    sound/sandaiyidui.wav \
    sound/sange.wav \
    sound/shunzi.wav \
    sound/sidaier.wav \
    sound/sidailiangdui.wav \
    sound/wangzha.wav \
    sound/win.wav \
    sound/xipai.wav \
    sound/zhadan.wav
