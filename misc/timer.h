#ifndef _H_TIMER
#define _H_TIMER

#include <stdio.h>
#include <sys/time.h>

/* @OSªÇ·éðæ¾ */
inline
unsigned long long gettimeval(void) {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return ((unsigned long long)tv.tv_sec)*1000000+tv.tv_usec;
}

/* AÔvªÌJn */
inline
void start_timer(unsigned int *startt) {
    *startt = (unsigned int)gettimeval();
    return;
}

/* BÔvªÌI¹ */
inline
unsigned int stop_timer(unsigned int *startt) {
    unsigned int stopt = (unsigned int)gettimeval();
    return (stopt>=*startt)?(stopt-*startt):(stopt);
}

/* CÔvªÊÌ\¦ */
#define print_timer(te) {printf("total elapsed time :%f[msec]\n", te*1.0e-3);}

#endif /*_H_TIMER*/

