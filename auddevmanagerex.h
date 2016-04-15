#pragma once
#ifndef AUDDEVMANAGEREX_H
#define AUDDEVMANAGEREX_H
#include <pjsua2/media.hpp>

//този клас ще разшири функционалността на AudDevManager
//като добави допълнителен хардверен дивайс, освен
//текущата кепчър/рекординг медиа
//suffix "Ex" за конвенция ( Extra функционалност  )

//ако пачваме оригиналния lib то тогава ще добавим тази функционалност
//в дефолтния ауддевманагер

//предекларации ако има нужда от помощни класове
class AudDevManagerEx;
class AudioMediaEx;

///I can use the defauilt AudioMedia class

class AudioMediaEx : public pj::AudioMedia
{
public:
    virtual ~AudioMediaEx();
protected:
    explicit AudioMediaEx();
protected:
    int                 m_id;
private:
    pj_caching_pool     m_cachePool;
    pj_pool_t*          m_pool;
};


class AudDevManagerEx
{
///ако се добавят нови методи статиците да са най-отгоре
///static:
public:
///!end statics


///ctors and dtors
public:

    //ще композираме клас, който има AudDevManager като дефолт и можем да го достъпваме
    //с гетер метод, нашия клас ще има малка и сбита функционалност за регистрацията на
    // <Line2> ексклузивно
    //Инстанции от нашия клас могат да регистрират нови Capture и Playback медии
    //добре е да слагаме инстанциите на медиите в листа на
    AudDevManagerEx(pj::AudDevManager& parent);
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



    /**
        Disconnect the main conference bridge from any sound devices,
        and let application connect the bridge to it's own sound device/master port.
        Returns:
            The port interface of the conference bridge, so that application can connect
        this to it's own sound device or master port.
    **/
    virtual void connectToDevice1(void);
    virtual void connectToDevice2(void);



private:
    //помощен клас за създаване на нова медиа
    //за защита не го показваме в трансалционните юнити или хедъри
    //нека да е прайвит и енкожурнат в Ех класа за да може потребителя
    //да не го достъпва.
    class DevAudioMediaEx : public pj::AudioMedia
    {
    public:
        explicit DevAudioMediaEx();
        ~DevAudioMediaEx();
    };

public:
///ако искам да достъпя дефолтния манагер това е функцията, или стандартния достъп
///през Ендпоинт-а

     pj::AudDevManager& getDefaultAudioManager(void);
private:
    int getActiveDevEx(bool is_capture) const throw (pj::Error);

    //оригинало има медиа лист от обекти,
    //които мога да достъвам от парент класа, но на мен ми трябва само едно устройство
    //за <Line2>


    pj::AudioMedia*         m_dev1;


    //медиини портове:
    pjmedia_port*       m_port1;
    pjmedia_port*       m_port2;

    pj::AudDevManager&      m_defaultManager;

};


#endif // AUDDEVMANAGEREX_H
