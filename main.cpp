#include <QCoreApplication>
#include <pjsua2.hpp>
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

/* libcreation */
    pj::Endpoint ep;
    ep.libCreate();
    pj::EpConfig epCfg;
    ep.libInit(epCfg);


/* device listing */

    int res = 0;

    pj::AudDevManager& audioDevMngr = ep.audDevManager();

//audio device is private!!!
//    pj::AudDevManager newManager;

    DriverAndName dev[2];
    // print available devices into log
    try {
        const pj::AudioDevInfoVector& audioDevs = audioDevMngr.enumDev();
        for (unsigned int i = 0U; i < audioDevs.size(); ++i) {
            std::cout           << "AudioDev " << i
                               << " name:" << audioDevs.at(i)->name
                               << " drv:" << audioDevs.at(i)->driver
                               << " ins:" << audioDevs.at(i)->inputCount
                               << " outs: " << audioDevs.at(i)->outputCount
                               << " sampl: " << audioDevs.at(i)->defaultSamplesPerSec
                               << " caps:"  << audioDevs.at(i)->caps
                               << std::endl;
            //hardcoded the first device ( HW device , not default NVIDIA and INTEL on my pc )
            {
                const char* s = audioDevs.at(i)->name.c_str();
                if ( strstr(s, "(hw:0,0)" ) != NULL ) {
                    dev[0].driver = audioDevs.at(i)->driver;
                    dev[0].name = audioDevs.at(i)->name;
                } else if ( strstr(s, "(hw:1,3)") != NULL ) {
                    dev[1].driver = audioDevs.at(i)->driver;
                    dev[1].name = audioDevs.at(i)->name;
                } else {
                    //nothing
                }
            }

        }
    } catch (pj::Error &err) {
        std::cout << err.info() << std::endl;
        res = -1;
    }


    try {
        ep.libStart();
    } catch ( pj::Error& ex)
    {

    }


    std::cout << "****************dev0: " << dev[0].name << " Driver: "
              << dev[0].driver << std::endl;

    std::cout << "****************dev1: " << dev[1].name << " Driver: "
              << dev[1].driver << std::endl;





}
#if 0

    //now lookup to retrieve the id
        try {

            int id1 = audioDevMngr.lookupDev(dev[0].driver, dev[0].name);
            int id2 = audioDevMngr.lookupDev(dev[1].driver, dev[1].name);

           // audioDevMngr.setPlaybackDev(id1);
           // audioDevMngr.setCaptureDev(id1);


            {




                int clock_rate = CLOCK_RATE;
                int channel_count = NCHANNELS;
                int samples_per_frame = NSAMPLES;
                int bits_per_sample = NBITS;

/** view this!!! **/
//http://comments.gmane.org/gmane.comp.voip.pjsip/17779
//http://comments.gmane.org/gmane.comp.voip.pjsip/12084
//http://pjsip.pjsip.narkive.com/1Zrk8xTa/pjmedia-splitcomb-how-add-channels-to-bridge

                pj_caching_pool cp;

                pj_pool_t *pool  =      NULL;

                pj_pool_t* players_pool = NULL;
                pj_pool_t* recorders_pool = NULL;

                pjmedia_conf *conf_bridges[4] = { 0 } ;
                pj_status_t status ;
                int res = 0;
                //alloc the pool factory
                pj_caching_pool_init(&cp, &pj_pool_factory_default_policy, 0);

                pool = pj_pool_create(&cp.factory,
                                      "default",
                                      4000,
                                      4000,
                                      NULL);


                pjsua_set_no_snd_dev();


                pjmedia_snd_port *sound_ports[PJSUA_MAX_PLAYERS + PJSUA_MAX_RECORDERS ] = { 0 };


                int devs = 0;




                unsigned int id1, id2;

                for(id1 = 0; id1 < PJSUA_MAX_PLAYERS; ++id1 )
                {
                    //master port info
                    pjmedia_snd_port *snd = NULL;
                    pjsua_conf_port_info masterPortInfo;

                    status = pjsua_conf_get_port_info(id1, &masterPortInfo);
                    if ( status == PJ_SUCCESS )
                    {
                        printf("Master port is OK... \n");
                        for (id2 = 0; id2 < PJSUA_MAX_RECORDERS; ++id2 )
                        {
                            status = pjmedia_snd_port_create(pool, id1, id2,
                                                            masterPortInfo.clock_rate,
                                                             1,
                                                             1 * masterPortInfo.samples_per_frame,
                                                             masterPortInfo.bits_per_sample, 0,
                                                             &snd);

                            if ( status == PJ_SUCCESS )
                            {
                                sound_ports[devs] = snd;
                                devs++;
                            }

                        }//!for
                    }
                }//!for







                for(i=0; i < PJSUA_MAX_PLAYERS; i++)
                {
                    pjmedia_snd_port* tmp = NULL;
                    status = pjmedia_snd_port_create_player(players_pool, i, clock_rate,
                                                     channel_count, samples_per_frame,
                                                     bits_per_sample,
                                                     0, &tmp);

                    if ( status == PJ_SUCCESS ) {
                        const pjmedia_snd_dev_info* dinfo = pjmedia_snd_get_dev_info(i);
                        players[devs++] = tmp;
                    }
                }

                MY_PJ_TEST( status == PJ_SUCCESS );

                devs = 0;
                for(i=0; i < PJSUA_MAX_RECORDERS; i++)
                {
                    pjmedia_snd_port* tmp = NULL;
                    status = pjmedia_snd_port_create_rec(recorders_pool,i, clock_rate,
                                                     channel_count, samples_per_frame,
                                                     bits_per_sample,
                                                     0, &tmp);



                    if ( status == PJ_SUCCESS ) {
                        const pjmedia_snd_dev_info* dinfo = pjmedia_snd_get_dev_info(i);
                        recorders[devs++] = tmp;
                    }
                }


                MY_PJ_TEST( status == PJ_SUCCESS );

                unsigned int it;

                //test cration of conf bridges
                for(it=0; it < 4; ++it) {
                    status = pjmedia_conf_create(pool,
                                                 PJSUA_MAX_CONF_PORTS,
                                                 clock_rate,
                                                 channel_count,
                                                 samples_per_frame,
                                                 bits_per_sample,
                                                 PJMEDIA_CONF_NO_DEVICE,
                                                 &conf_bridges[it]);

                   MY_PJ_TEST( status == PJ_SUCCESS );
                } //!for


                pjmedia_port *newPort = pjmedia_conf_get_master_port(conf_bridges[0]);
                //status = pjmedia_snd_port_connect(players[0], newPort);
                MY_PJ_TEST( status == PJ_SUCCESS );


            }//end scope

            std::cout << "DEV1: " << "ID: " << id1 << std::endl;
            std::cout << "DEV2: " << "ID: " << id2 << std::endl;


        } catch ( pj::Error& ex) {

        }

}
#endif
