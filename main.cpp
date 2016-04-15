#include <QCoreApplication>
#include <pjsua2.hpp>
#include <auddevmanagerex.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#define CLOCK_RATE  16000
#define NCHANNELS   2
#define NSAMPLES    (CLOCK_RATE * 20 / 1000)
#define NBITS       16


typedef struct {
    std::string driver;
    std::string name;
} DriverAndName;


int main(int argc, char *argv[])
{

    PJ_UNUSED_ARG(argc);
    PJ_UNUSED_ARG(argv);

    int ret = 0;
    pj::Endpoint ep;
    pj::EpConfig cfg;


    try {
        ep.libCreate();
        ep.libInit(cfg);


      //  pjsua_media_config cfg;
      //  pjsua_media_config_default(&cfg);

        pj::AudDevManager& defMngr = ep.audDevManager();
        AudDevManagerEx exManager (defMngr);

        const pj::AudioDevInfoVector devlist = exManager.getDefaultAudioManager().enumDev();

        pj::AudioMedia& am1 = exManager.getCaptureDevMediaEx();
        pj::AudioMedia& am2 = exManager.getDefaultAudioManager().getCaptureDevMedia();
       // exManager.listAllPorts();
       // exManager.connectToDevice1();
       // exManager.connectToDevice2();

        std::cout << "Devices: " << pjmedia_aud_dev_count() << std::endl;

        ret = PJ_SUCCESS;
    } catch (pj::Error & err) {
        std::cout << "Exception: " << err.info() << std::endl;
        ret = 1;
    }

    try {
        ep.libDestroy();
    } catch(pj::Error &err) {
        std::cout << "Exception: " << err.info() << std::endl;
        ret = 1;
    }

    if (ret == PJ_SUCCESS) {
        std::cout << "Success" << std::endl;
    } else {
        std::cout << "Error Found" << std::endl;
    }
    return 0;
}

