

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include "soundplayer.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sstream>

#define	PIN_1		1
#define	PIN_2		2
#define	PIN_3		3
#define	PIN_4		4
#define	PIN_5		5
#define	PIN_6		6


SoundPlayer *sp;

std::string getFilePath(int pin)
{
   std::string mediadir = "/media";
    DIR *media;
    DIR *stick;
    DIR *pinDir;
    struct dirent *ent;
    struct stat st;
    std::stringstream path;
    path << mediadir;
    media = opendir(mediadir.c_str());
    while((ent = readdir(media)) != NULL)
    {
        const std::string file_name = ent->d_name;
        const std::string full_file_name = mediadir + "/" + file_name;

        //get the dirent that isn't . or ..
        if (file_name[0] == '.')
            continue;
        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;
        if (is_directory){
            //create the full string
            path << "/" << file_name;
        }
    }
    std::cout << "sstream after media =" << path.str() <<std::endl;
    
    

    stick = opendir(path.str().c_str());
    while ((ent = readdir(stick)) != NULL) {
        const std::string file_name = ent->d_name;
        const std::string full_file_name = path.str() + "/" + file_name;
        char pinchar [1];
        sprintf(pinchar, "%d", pin);
        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory){
             if(strcmp(file_name.c_str(), pinchar) == 0)
             {
                  std::cout << "found the numbered dir" << std::endl;
                 path << "/" << file_name;
             }
        }
            continue;

    }
       std::cout << "path aaafter pindirr " << path.str() << std::endl;

    pinDir = opendir(path.str().c_str());
    while ((ent = readdir(pinDir)) != NULL) {
        const std::string file_name = ent->d_name;
        const std::string full_file_name = path.str() + "/" + file_name;
        char pinchar [1];
        sprintf(pinchar, "%d", pin);
        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory){
             continue;
        }else{
            path << "/" << file_name;
	    continue;
	}
    }
       std::cout << "path aaafter getting file " << path.str() << std::endl;
return path.str();//"/media/E0D2-9615/1/1A.wav";

}


void handlePinPress(int pin)
{
    std::cout << "Handling Pin press" << pin << std::endl;

    std::string path = getFilePath(pin);

    sp->run(path);

    //
}

void pinOnePressed()
{
handlePinPress(1);
}
void pinTwoPressed()
{
handlePinPress(2);
}
void pinThreePressed()
{
handlePinPress(3);
}
void pinFourPressed()
{
handlePinPress(4);
}
void pinFivePressed()
{
handlePinPress(5);
}
void pinSixPressed()
{
handlePinPress(6);
}

int main(){
    std::cout << "starting the soundplayer" << std::endl;
    sp = new SoundPlayer();

    if (wiringPiSetup () < 0)
    {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
      return 1 ;
    }

    pinMode (PIN_1, INPUT) ;
    pinMode (PIN_2,  INPUT) ;
    pinMode (PIN_3,  INPUT) ;
    pinMode (PIN_4,  INPUT) ;
    pinMode (PIN_5,  INPUT) ;
    pinMode (PIN_6,  INPUT) ;


    if (wiringPiISR (PIN_1, INT_EDGE_FALLING, &pinOnePressed) < 0)
    {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
      return 1 ;
    }
    if (wiringPiISR (PIN_2, INT_EDGE_FALLING, &pinTwoPressed) < 0)
    {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
      return 1 ;
    }
    if (wiringPiISR (PIN_3, INT_EDGE_FALLING, &pinThreePressed) < 0)
    {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
      return 1 ;
    }
    if (wiringPiISR (PIN_4, INT_EDGE_FALLING, &pinFourPressed) < 0)
    {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
      return 1 ;
    }
    if (wiringPiISR (PIN_5, INT_EDGE_FALLING, &pinFivePressed) < 0)
    {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
      return 1 ;
    }
    if (wiringPiISR (PIN_6, INT_EDGE_FALLING, &pinSixPressed) < 0)
    {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
      return 1 ;
    }
    for(;;){

        /* test code */
        std::string in;
        std::cin >> in;
        int num = atoi(in.c_str());
        std::cout << "entered: "<< num;
        handlePinPress(num);

         std::cout << "loop again" << std::endl;


    }
    return 0;
}




