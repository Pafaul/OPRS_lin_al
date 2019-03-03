TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    integrator.cpp \
    Arenstorph_model.cpp \
    main.cpp \
    main_test.cpp \
    white_noise.cpp \
    tvector.cpp \
    tquaternion.cpp \
    tmatrix.cpp \
    math_model.cpp \
    custom.cpp

HEADERS += \
    integrator.h \
    Arenstorph_model.h \
    math_model.h \
    white_noise.h \
    tvector.h \
    tquaternion.h \
    tmatrix.h \
    custom.h

