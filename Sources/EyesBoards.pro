QT += widgets
QT += texttospeech

unix: INCLUDEPATH += ../stream_engine_linux_3.0.4.6031/include
win32: INCLUDEPATH += ../stream_engine_windows_x64_4.1.0.3/include

SOURCES += \
    Board/Board.cpp \
    Board/BoardCursor.cpp \
    Board/BoardError.cpp \
    Board/BoardFrame.cpp \
    Board/BoardFunction.cpp \
    Board/BoardGenerator.cpp \
    Board/BoardOptions.cpp \
    Board/BoardSignals.cpp \
    Functions/FunctionBoardNavigation.cpp \
    Functions/FunctionManager.cpp \
    Functions/FunctionSay.cpp \
    Functions/IFunction.cpp \
    WWidgets/WAnchor.cpp \
    WWidgets/WFrame.cpp \
    WWidgets/WLabel.cpp \
    WWidgets/WPushButton.cpp \
    WWidgets/WWidget.cpp \
    mafenetre.cpp \
    main.cpp \
    Tobiidget.cpp

HEADERS += \
    Board/Board.h \
    Board/BoardCursor.h \
    Board/BoardError.h \
    Board/BoardFrame.h \
    Board/BoardFunction.h \
    Board/BoardGenerator.h \
    Board/BoardOptions.h \
    Board/BoardSignals.h \
    Functions/FunctionBoardNavigation.h \
    Functions/FunctionManager.h \
    Functions/FunctionSay.h \
    Functions/IFunction.h \
    WWidgets/WAnchor.h \
    WWidgets/WFrame.h \
    WWidgets/WLabel.h \
    WWidgets/WPushButton.h \
    WWidgets/WWidget.h \
    mafenetre.h \
    Tobiidget.h

unix: LIBS += -L$$PWD/../stream_engine_linux_3.0.4.6031/lib/x64/ -ltobii_stream_engine
win32: LIBS += -L$$PWD/../stream_engine_windows_x64_4.1.0.3/lib/tobii/ -ltobii_stream_engine

unix: INCLUDEPATH += $$PWD/../stream_engine_linux_3.0.4.6031/lib/x64
win32: INCLUDEPATH += $$PWD/../stream_engine_windows_x64_4.1.0.3/lib/x64

unix: DEPENDPATH += $$PWD/../stream_engine_linux_3.0.4.6031/lib/x64
win32: DEPENDPATH += $$PWD/../stream_engine_windows_x64_4.1.0.3/lib/x64
