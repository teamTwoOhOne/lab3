#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "motor.h"
#include "lcd.h"
#include "pwm.h"
#include "timer.h"
#include "adc.h"

volatile unsigned int val = 0;


int main(void){
    SYSTEMConfigPerformance(40000000);
    int i;
    
    enableInterrupts();
    init_lcd();
    clear_lcd();
    TRISFbits.TRISF1 = 1; //Make F1 input for potentiometer
    initADC();
    char Vunit = '0';
    char Vdec[6] = {'0','0','0','0','0','0'};
    move_cursor_lcd(1,1);
    print_string_lcd('.');
    initADC();
    while(1){
        move_cursor_lcd(0,1);
        print_string_lcd(Vunit);
        move_cursor_lcd(2,1);
        print_string_lcd(Vdec);
    }
    
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    val = ADC1BUF0;
    
}
