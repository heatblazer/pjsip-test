#ifndef AUDDEVMANAGEREX_H
#define AUDDEVMANAGEREX_H

#include <pjsua2/media.hpp>


//този клас ще разшири функционалността на AudDevManager
//като добави допълнителен хардверен дивайс, освен
//текущата кепчър/рекординг медиа

class AudDevManagerEx : public pj::AudDevManager
{
public:
    pj::AudioMedia& getCaptureDevMediaEx(void) throw (pj::Error);



protected:

    AudDevManagerEx();
    virtual ~AudDevManagerEx();

private:
    //помощен клас за създаване на нова медиа
    //за защита не го показваме в трансалционните юнити или хедъри
    //нека да е прайвит и енкожурнат в Ех класа за да може потребителя
    //да не го достъпва.
    class DevAudioMediaEx : public pj::AudioMedia
    {
    public:
        DevAudioMediaEx();
        ~DevAudioMediaEx();
    };
private:
    //оригинало има медиа лист от обекти,
    //които мога да достъвам от парент класа
    pj::AudioMedia* m_mediaEx;

};


#endif // AUDDEVMANAGEREX_H
