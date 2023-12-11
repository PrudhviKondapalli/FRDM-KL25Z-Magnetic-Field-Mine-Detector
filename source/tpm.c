/**
 * Default and User-defined libraries
 */
#include "board.h"
#include "fsl_debug_console.h"
#include "tpm.h"
#include <stdbool.h>
#include <systick.h>

/**
 * User-defined macros
 */
#define RED_MASK (1UL << 18)
#define GREEN_MASK (1UL << 19)
#define BLUE_MASK (1UL << 1)
#define PORT_B_MASK (1UL << 10)
#define PORT_D_MASK (1UL << 12)
#define RED_MASK (1UL << 18)
#define GREEN_MASK (1UL << 19)
#define BLUE_MASK (1UL << 1)

/**
 * @brief      {RGM PWM Initialization for startup before my while(1) even starts}
 * @type       {void)
 * @return     {None}
 */
void Init_RGB_LED_PWM(void)
{
  	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
  	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

  	//Configure TPM
  	//set clock source for tpm : 48Mhz as MCGFLLCLK
  	SIM->SOPT2 &= ~(SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
  	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
  	//lOAD THE COUNTER Value
  	TPM0->MOD = 255;
  	TPM2->MOD = 255;
  	//set TPM count direction to up with a divide by 2 pre-scaler
  	TPM0->SC = TPM_SC_PS(1);
  	TPM2->SC = TPM_SC_PS(1);

  	//continue operation in debug mode
  	TPM0->CONF |= TPM_CONF_DBGMODE(3);
  	TPM2->CONF |= TPM_CONF_DBGMODE(3);
  	//set channel 1 to edge aligned low true PWM
  	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; //Low-true pulses (set Output on match, clear Output on reload)
  	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; //Low-true pulses (set Output on match, clear Output on reload)
  	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; //Low-true pulses (set Output on match, clear Output on reload)
  	//set initial duty cycle
  	TPM0->CONTROLS[1].CnV = 0;
  	TPM2->CONTROLS[0].CnV = 0;
  	TPM2->CONTROLS[1].CnV = 0;
  	//Start TPM
  	TPM0->SC |= TPM_SC_CMOD(1); /*LPTPM counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter
  	clock*/
  	TPM2->SC |= TPM_SC_CMOD(1);
}


void Init_speaker_pwm(void)
{
	//TPM1_CH1//PTB1//J10-4
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
  	//Configure TPM
  	//set clock source for tpm : 48Mhz as MCGFLLCLK
  	SIM->SOPT2 &= ~(SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
  	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
  	//lOAD THE COUNTER Value
  	TPM1->MOD = 255;
  	//set TPM count direction to up with a divide by 2 pre-scaler
  	TPM1->SC = TPM_SC_PS(1);
  	//continue operation in debug mode
  	TPM1->CONF |= TPM_CONF_DBGMODE(3);
  	//set channel 1 to edge aligned low true PWM
  	TPM1->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; //Low-true pulses (set Output on match, clear Output on reload)
  	//set initial duty cycle
  	TPM1->CONTROLS[1].CnV = 0;
  	//Start TPM
  	TPM1->SC |= TPM_SC_CMOD(1); /*LPTPM counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter
  	clock*/

}

/**
 * @brief      {LED Module Initialization for startup before my while(1) even starts}
 * @type       {void)
 * @return     {None}
 */
void initLEDs()
{
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;                      //Starting Clock for Port B and  Port D
    PORTB->PCR[18] &= ~PORT_PCR_MUX_MASK;                    //Clearing the old Bit in 18th place of PCR register
    PORTB->PCR[18] |= PORT_PCR_MUX(3);                       //Setting PCR register 18th bit to to configure as GPIO
    PORTB->PCR[19] &= ~PORT_PCR_MUX_MASK;                    //Clearing the old Bit in 19th place of PCR register
    PORTB->PCR[19] |= PORT_PCR_MUX(3);                       //Setting PCR register 19th bit to to configure as GPIO
    PORTD->PCR[1] &= ~PORT_PCR_MUX_MASK;                     //Clearing the old Bit in 1st place of PCR register
    PORTD->PCR[1] |= PORT_PCR_MUX(4);                        //Setting PCR register 1st bit to to configure as GPIO
    PTB->PDDR |= RED_MASK | GREEN_MASK;
    PTD->PDDR |= BLUE_MASK;
}
