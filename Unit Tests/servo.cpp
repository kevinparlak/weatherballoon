#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
//Servo header file
#include "servo.h"

using namespace std;

//C code
#ifdef _WIN32
#define O_NOCTTY 0
#else
#include <termios.h>
#endif

//Constructor
SERVO::SERVO(int fd)
{
//    //C code
//    #ifdef _WIN32
//    #define O_NOCTTY 0
//    #else
//    #include <termios.h>
//    #endif

    //C code
    #ifdef _WIN32
        _setmode(fd, _O_BINARY);
    #else
        struct termios options;
            tcgetattr(fd, &options);
            options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
            options.c_oflag &= ~(ONLCR | OCRNL);
            options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
            tcsetattr(fd, TCSANOW, &options);
    #endif
};

//Destructor
SERVO::~SERVO()
{

};

//Position function
int SERVO::maestroGetPosition(int fd, unsigned char channel)
{
    //Find the channel the servo is connected to
    unsigned char command[] = {0x90, channel};
    //Error check for channel
    if(write(fd, command, sizeof(command)) == -1)
    {
        perror("error writing");
        return -1;
    }
 
    //Response check for channel
    unsigned char response[2];
    if(read(fd,response,2) != 2)
    {
        perror("error reading");
        return -1;
    }
    
    //Return position of the servo
    return response[0] + 256*response[1];
}

//Target function
int SERVO::maestroSetTarget(int fd, unsigned char channel, unsigned short target)
{
    //Declare position
    int position = maestroGetPosition(fd, channel);
    //Output current position
    printf("Current position is %d.\n", position);
    //Assign command to move on servo channel
    unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
    //Error check for channel
    if (write(fd, command, sizeof(command)) == -1)
    {
        perror("error writing");
        return -1;
    }
    
  return 0;
}