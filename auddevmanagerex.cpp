#include "auddevmanagerex.h"
#include <iostream> //да се премахне по-късно


using namespace pj;
#define THIS_FILE "auddevmanagerex.cpp"



AudDevManagerEx::AudDevManagerEx(AudDevManager& parent)
    :m_defaultManager(parent),
     m_dev1(NULL),
     m_port1(NULL),
     m_port2(NULL)
{

}

AudDevManagerEx::~AudDevManagerEx()
{
    //breakpoint
}

//искаме нова ексклузивна медия, която отнове е сингълтон
void
AudDevManagerEx::setCaptureDevEx(const int capture_dev) const
throw (pj::Error)
{
    int player = getPlaybackDevEx();

    PJSUA2_CHECK_EXPR ( pjsua_set_snd_dev(capture_dev, player) );
}

pj::AudioMedia&
AudDevManagerEx::getCaptureDevMediaEx(void)
throw (pj::Error)
{
    if ( !m_dev1)
    {
        m_dev1 = new DevAudioMediaEx;
        return *m_dev1;

    } else {
        return *m_dev1;
    }
}

int
AudDevManagerEx::getPlaybackDevEx(void) const
throw (pj::Error)
{
    return getActiveDevEx(true);
}


void
AudDevManagerEx::setPlaybackDevEx(const int playback_dev) const
throw (pj::Error)
{
    int recorder = getCaptureDevEx();

    PJSUA2_CHECK_EXPR ( pjsua_set_snd_dev(recorder, playback_dev) );
}

int
AudDevManagerEx::getCaptureDevEx(void) const
throw (pj::Error)
{
    return getActiveDevEx(false);
}

pj::AudioMedia&
AudDevManagerEx::getPlaybackDevMediaEx(void)
throw (pj::Error)
{
    if ( !m_dev1 ) {
        m_dev1 = new DevAudioMediaEx;
        return *m_dev1;
    } else {
        return *m_dev1;
    }
}


void
AudDevManagerEx::connectToDevice1(void)
{
    m_port1 = (pjmedia_port*) m_defaultManager.setNoDev();

    if ( m_port1 ){
        std::cout << "OK" << std::endl;
    } else {

    }
}

void
AudDevManagerEx::connectToDevice2(void)
{
    m_port2  = (pjmedia_port*) m_defaultManager.setNoDev();

    if ( m_port2 ){
        std::cout << "OK" << std::endl;
    } else {

    }

}


//private:
int
AudDevManagerEx::getActiveDevEx(bool is_capture) const
throw (pj::Error)
{
    int capid = 0, recid = 0;
    PJSUA2_CHECK_EXPR ( pjsua_get_snd_dev(&capid, &recid) );

    if ( is_capture ) {
        return capid;
    } else {
        return recid;
    }
}


pj::AudDevManager& AudDevManagerEx::getDefaultAudioManager()
{
    return m_defaultManager;
}


//Помощен клас - НЕДОСТЪПЕН!!!
/***********************************************************************/
AudDevManagerEx::
DevAudioMediaEx::DevAudioMediaEx()
{
    this->id = 0;
    registerMediaPort(NULL); //записва NULL медиа в Endpoint листа от медии
}

AudDevManagerEx::
DevAudioMediaEx::~DevAudioMediaEx()
{
    this->id = PJSUA_INVALID_ID;
}
/***********************************************************************/

