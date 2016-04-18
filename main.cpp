#include <QCoreApplication>
#include <pjsua2/endpoint.hpp>
#include <pjsua2/media.hpp>


using namespace pj;
//minimal SUA2 test

int main(int argc, char **argv)
{
    QCoreApplication qapp(argc, argv);

    Endpoint ep;

    EpConfig epCfg;

    epCfg.uaConfig.userAgent = "pjsua++-test";

    ep.libCreate();
    ep.libInit(epCfg);
    ep.libStart();

    AudDevManager& adm = ep.audDevManager();

    int line1 = adm.getCaptureDev();
    pj::AudioMedia& media1 = adm.getCaptureDevMedia();

    int line2= adm.getCaptureDevEx();
    pj::AudioMedia& media2= adm.getCaptureDevMediaEx();
   // dummy_foo_bar();

    ep.libDestroy();


    qapp.exec();

}


