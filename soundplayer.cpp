#include "soundplayer.h"

#include <strstream>
#include <pthread.h>

SoundPlayer::SoundPlayer()
{
    this->file = std::string();
}

SoundPlayer::~SoundPlayer()
{

}


bool SoundPlayer::run()
{
    if(this->running)
    {
            std::cerr << "VlfExperimentThread::run(): Error: thread already running!" << std::endl;
            return false;
    }
     int ret = pthread_create( &this->thread, NULL, SoundPlayer::playSound, this );
     this->running = (ret == 0);
     return this->running;
}



static void *SoundPlayer::playSound(void* data)
 {
      SoundPlayer *sp = (SoundPlayer*)data;
      std::stringstream cmd;
      cmd << "aplay";
      cmd << " ";
      cmd << sp->file;
      std::cout << "playing cmd = " << cmd.str() << std::endl;
      system(cmd.str());


      std::cout << "ExperimentThread::execute() Finished!" << std::endl;
      sp->running = false;
      pthread_exit(NULL);
      return NULL;
 }
