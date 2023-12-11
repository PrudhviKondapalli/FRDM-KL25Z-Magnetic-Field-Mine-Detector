#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "I2C.h"
#include "systick.h"
#include "mag_readings.h"
#include "math.h"
#include "tpm.h"

#define DEGREE_INTERVAL 22.5
#define ROUNDING_THRESHOLD 0.5
#define M_PI (3.14159265358979323846)
#define magnetic_declination (0.95) //7deg50min

//create an instance of mag_readings
mag_readings live_mag_readings;

extern uint8_t data_buffer[6];
int16_t x_raw_initial = 0;
int16_t y_raw_initial = 0;
int16_t z_raw_initial = 0;
int16_t x= 0;
int16_t y= 0;
int16_t z= 0;

void convert_to_signed(uint8_t *data)
{
    // Combine the MSB and LSB for each axis
     x_raw_initial = (int16_t)((data[2] << 8) | data[1]);
     y_raw_initial = (int16_t)((data[4] << 8) | data[3]);
     z_raw_initial = (int16_t)((data[6] << 8) | data[5]);

    // Check and apply the sign for each axis
     x = (x_raw_initial < 32768) ? x_raw_initial : (x_raw_initial - 65536);
     y = (y_raw_initial < 32768) ? y_raw_initial : (y_raw_initial - 65536);
     z = (z_raw_initial < 32768) ? z_raw_initial : (z_raw_initial - 65536);
}

void mag_read(void)
{
	live_mag_readings.x_raw = x;
	live_mag_readings.y_raw = y;
	live_mag_readings.z_raw = z;
	live_mag_readings.azimuthal = calculate_azimuthal(y,x);
	live_mag_readings.heading = getBearing(live_mag_readings.azimuthal);
	PRINTF("x_raw is : %d\n", x);
	PRINTF("y_raw is : %d\n", y);
	PRINTF("z_raw is : %d\n", z);
	PRINTF("Azimuthal Angle is : %d\n",calculate_azimuthal(y,x));
	PRINTF("Heading is : %d\n", z);
	if(z > (-100))
	{
	  	//set initial duty cycle
	  		TPM0->CONTROLS[1].CnV = 255;
	  		TPM2->CONTROLS[0].CnV = 255;
	  		TPM2->CONTROLS[1].CnV = 255;
	  		TPM1->CONTROLS[1].CnV = 255;
	}
	else
	{
		TPM0->CONTROLS[1].CnV = 0;
		TPM2->CONTROLS[0].CnV = 0;
		TPM2->CONTROLS[1].CnV = 0;
		TPM1->CONTROLS[1].CnV = 0;
	}
}

int calculate_azimuthal(int y_axis, int x_axis)
{
	 float heading = atan2((double)y_axis,(double)x_axis) * 180.0 * 7 / 22;
	    heading += magnetic_declination;
	    return (int)heading % 360;
}


unsigned char getBearing(int azimuth) {
    double azimuthInSextants = (azimuth > -0.5) ? azimuth / DEGREE_INTERVAL : (azimuth + 360) / DEGREE_INTERVAL;
    double fractionalPart = azimuthInSextants - (int)azimuthInSextants;
    unsigned char compassSextant = 0;

    compassSextant = (fractionalPart >= ROUNDING_THRESHOLD) ? ceil(azimuthInSextants) : floor(azimuthInSextants);

    return compassSextant;
}
