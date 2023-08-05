/* modify: Sitao Tong*/

#ifndef STRUCT_H
#define STRUCT_H

typedef struct sim Sim;
typedef struct alien Alien;

struct sim{
    double elapsed;
    void* aliens;
    double xBase;
    int score;
    double dt;
};

struct alien{
    unsigned int code;
    double x;
    double y;
    double vx;
    double vy;
    int color;
    int type;
    int points;
    Sim *sim;
};

#endif