#include "soundplayer.h"

#include <sstream>
#include <pthread.h>
#include <iostream>
#include <cstdlib>

SoundPlayer::SoundPlayer()
{
    this->file = std::string();
}

SoundPlayer::~SoundPlayer()
{

}


bool SoundPlayer::run(std::string path)
{
    if(this->running)
    {
            std::cerr << "VlfExperimentThread::run(): Error: thread already running!" << std::endl;
            return false;
    }
    this->file=path;
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
      system(cmd.str().c_str());


      std::cout << "SoundPlayer::execute() Finished!" << std::endl;
      sp->running = false;
      pthread_exit(NULL);
      return NULL;
 }
