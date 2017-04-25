#ifndef SERVO_H
#define SERVO_H

//Class definition for servo motors
class SERVO
{
public:
    //Default constructor
    SERVO(int fd);
    int maestroGetPosition(int fd, unsigned char channel);
    int maestroSetTarget(int fd, unsigned char channel, unsigned short target);
    //Destructor
    ~SERVO();
};
        
#endif /* SERVO_H */