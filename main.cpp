#include <QCoreApplication>
#include <pjsua2.hpp>

using namespace pj;
//minimal SUA2 test

int main(int argc, char **argv)
{
    QCoreApplication qapp(argc, argv);

    Endpoint ep;

    EpConfig epCfg;

    epCfg.uaConfig.userAgent = "pjsua++-test";

    AudDevManager& adm = ep.audDevManager();


    ep.libCreate();
    ep.libInit(epCfg);
    ep.libStart();
    ep.libDestroy();


    qapp.exec();

}


