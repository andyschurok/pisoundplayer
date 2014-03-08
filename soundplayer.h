#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H
#include <pthread.h>
#include <string>

class SoundPlayer
{
public:
    SoundPlayer();
    ~SoundPlayer();


    bool run();

private:
    pthread_t thread;
    std::string file;
    bool running;
    static void *playSound(void* data);
};

#endif // SOUNDPLAYER_H
