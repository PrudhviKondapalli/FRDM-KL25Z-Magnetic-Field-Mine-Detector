#ifndef _MAG_READINGS_H
#define _MAG_READINGS_H

#include <math.h>  // For PI constant

struct mag_readings {
    int x_raw;
    int y_raw;
    int z_raw;
    int azimuthal;
    int heading;
};

typedef struct mag_readings mag_readings;

void convert_to_signed(uint8_t *data);
void mag_read(void);
int calculate_azimuthal(int y_axis, int x_axis);
unsigned char getBearing(int azimuth);

#endif
