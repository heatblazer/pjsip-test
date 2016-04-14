#ifndef AUDDEVMANAGEREX_H
#define AUDDEVMANAGEREX_H

#include <pjsua2/media.hpp>


//този клас ще разшири функционалността на AudDevManager
//като добави допълнителен хардверен дивайс, освен
//текущата кепчър/рекординг медиа


class AudDevManagerEx;

class AudDevManagerEx
{
//моля ако се добавят нови методи статиците да са най-отгоре
///static:
public:
///!end statics


///ctors and dtors
public:

    AudDevManagerEx(const pj::AudDevManager* parent);
    virtual ~AudDevManagerEx() ; //ще ни трябва ли дете от от този клас?


///follow the normal defins
public:
    //ще вземем по еднна плейбак и кепчър медия, и двете са сингълтони
    //също така ще ги добавим в листа на девайс менагера за да може
    //деструктора да ги изчисти когато ендпоинта го извика, тъй като
    //нямаме контрол върху разрушаването му.

    virtual pj::AudioMedia& getCaptureDevMediaEx(void) throw (pj::Error);
    virtual pj::AudioMedia& getPlaybackDevMediaEx(void) throw (pj::Error);



    virtual int     getCaptureDevEx(void) const throw (pj::Error);
    virtual void    setCaptureDevEx(const int capture_dev) const throw (pj::Error);

    virtual int     getPlaybackDevEx(void) const throw (pj::Error);
    virtual void    setPlaybackDevEx(const int playback_dev) const throw (pj::Error);




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


public:

    const pj::AudDevManager* getDefaultManager(void);
private:
    int getActiveDevEx(bool is_capture) const throw (pj::Error);

    //оригинало има медиа лист от обекти,
    //които мога да достъвам от парент класа

    //засега ще регистриам само 1 екстра дивайс за <Line2>
    pj::AudioMedia* m_dev1;

    //това е помощен указател към Endpoint мениджъра който е
    //дефолтен.
    //засега не го ползвам но може и да ми потрябва в бъдеще

    const pj::AudDevManager*      m_defaultManager;

};


#endif // AUDDEVMANAGEREX_H
