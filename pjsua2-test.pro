QT += core
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = pjsua2-test
TEMPLATE = app

#unix builds
unix:{

    message("WARN!!! PJSIP must be linked to pthread and uuid!<-lpthread -luuid">)
    message("WARN!!! Order of static linking must be kept!")

    INCLUDEPATH += /home/ilian/projects/pjsip/install/include

    LIBS += -L/home/ilian/projects/pjsip/install/lib64/ -lpthread  -lasound -luuid \
                                                        -lpjsua2-x86_64-unknown-linux-gnu           \
                                                        -lpjsua-x86_64-unknown-linux-gnu            \
                                                        -lpjsip-ua-x86_64-unknown-linux-gnu         \
                                                        -lpjsip-simple-x86_64-unknown-linux-gnu     \
                                                        -lpjsip-x86_64-unknown-linux-gnu            \
                                                        -lpjmedia-codec-x86_64-unknown-linux-gnu    \
                                                        -lpjmedia-x86_64-unknown-linux-gnu          \
                                                        -lpjmedia-videodev-x86_64-unknown-linux-gnu \
                                                        -lpjmedia-audiodev-x86_64-unknown-linux-gnu \
                                                        -lsrtp-x86_64-unknown-linux-gnu             \
                                                        -lresample-x86_64-unknown-linux-gnu         \
                                                        -lportaudio-x86_64-unknown-linux-gnu        \
                                                        -lspeex-x86_64-unknown-linux-gnu            \
                                                        -lg7221codec-x86_64-unknown-linux-gnu       \
                                                        -lilbccodec-x86_64-unknown-linux-gnu        \
                                                        -lgsmcodec-x86_64-unknown-linux-gnu         \
                                                        -lpjnath-x86_64-unknown-linux-gnu           \
                                                        -lpjlib-util-x86_64-unknown-linux-gnu       \
                                                        -lpj-x86_64-unknown-linux-gnu

    CONFIG(debug, debug|release):{
        message("UNIX, DEBUG")
        DEFINES += _DEBUG
        DEFINES += PJMEDIA_AUDIO_DEV_HAS_ALSA
        DEFINES += TEST1

    }
    else:{
        message("UNIX, RELEASE")

    }
    #all modes
    SOURCES += main.cpp
}
else:{ message("Not Unix") }

