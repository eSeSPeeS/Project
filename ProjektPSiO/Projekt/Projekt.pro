TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "D:\Studia\Semestr2\PSiO\SFML-2.5.1\include"

LIBS += -L"D:\Studia\Semestr2\PSiO\SFML-2.5.1\lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        animatedsprite.cpp \
        bullet.cpp \
        main.cpp \
        things.cpp

HEADERS += \
    animatedsprite.h \
    bullet.h \
    things.h
