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
        ep.libStart();
     } catch ( pj::Error err ) { }


    pj::AudDevManager& defMngr = ep.audDevManager();
    AudDevManagerEx exManager (defMngr);

    const pj::AudioDevInfoVector devlist = exManager.getDefaultAudioManager().enumDev();


    pj::AudioMediaPlayer* player1 = new pj::AudioMediaPlayer();
    pj::AudioMediaPlayer* player2 = new pj::AudioMediaPlayer();

    pj::AudioMediaRecorder* rec1 = new pj::AudioMediaRecorder();
    pj::AudioMediaRecorder* rec2 = new pj::AudioMediaRecorder();

    try {
        player1->createPlayer("player1.wav");
        rec1->createRecorder("recorder1.wav");

    } catch ( pj::Error ex )
    {
        std::cout << "Failed creting plyaers" << std::endl;
    }


    try {
        player2->createPlayer("player2.wav");
        rec2->createRecorder("recorder2.wav");
    } catch ( pj::Error ex )
    {
        std::cout << "Failed creting plyaers" << std::endl;
    }

    try {
        exManager.getDefaultAudioManager().setPlaybackDev(0);
    } catch ( pj::Error err ) { }

    try {
        exManager.setPlaybackDevEx(0);
    } catch ( pj::Error err ){ }


    pj::AudioMedia& media1 = exManager.getDefaultAudioManager().getPlaybackDevMedia();
    pj::AudioMedia& media2 = exManager.getPlaybackDevMediaEx();

    player1->startTransmit(exManager.getDefaultAudioManager().getPlaybackDevMedia());
  //  player2->startTransmit(exManager.getPlaybackDevMediaEx());
    ret = PJ_SUCCESS;

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

