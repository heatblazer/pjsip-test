#include "auddevmanagerex.h"


//искаме нова ексклузивна медия, която отнове е сингълтон
pj::AudioMedia&     AudDevManagerEx::getCaptureDevMediaEx(void)
throw (pj::Error)
{
    if ( !m_mediaEx )
    {
        m_mediaEx = new DevAudioMediaEx;
        return *m_mediaEx;

    } else {
        return *m_mediaEx;
    }
}

//Помощен клас - НЕДОСТЪПЕН!!!
/***********************************************************************/
AudDevManagerEx::DevAudioMediaEx::DevAudioMediaEx()
{
    this->id = 0;
    registerMediaPort(NULL); //записва NULL медиа в Endpoint листа от медии
}

AudDevManagerEx::DevAudioMediaEx::~DevAudioMediaEx()
{
    this->id = PJSUA_INVALID_ID;
}
/***********************************************************************/





