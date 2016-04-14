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



#define MY_PJ_TEST(EXPR) do {   \
        if ( EXPR ) {           \
                res = 1;        \
            } else {            \
                res = -1;       \
            }                   \
     } while ( 0 );             \


typedef struct {
    std::string driver;
    std::string name;
} DriverAndName;

int main(int argc, char *argv[])
{

    int ret = 0;
    pj::Endpoint ep;

    try {
        ep.libCreate();

        pj::AudDevManager& pMngr = ep.audDevManager();


        const pj::AudioDevInfoVector& audioDevs = pMngr.enumDev();
        for (unsigned int i = 0U; i < audioDevs.size(); ++i) {
            std::cout          << "AudioDev " << i
                               << " name:" << audioDevs.at(i)->name
                               << " drv:" << audioDevs.at(i)->driver
                               << " ins:" << audioDevs.at(i)->inputCount
                               << " outs: " << audioDevs.at(i)->outputCount
                               << " sampl: " << audioDevs.at(i)->defaultSamplesPerSec
                               << " caps:"  << audioDevs.at(i)->caps;
        }

        ret = PJ_SUCCESS;
    } catch (pj::Error & err) {
        std::cout << "Exception: " << err.info() << std::endl;
        ret = 1;
    }


    return 0;

}
