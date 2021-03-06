/* ========================================
 *
 * This code is brought in part by open source code.  The rest is (C) R. Owings 2021
 * MIT license applies  Feel free to use with no guarantee for fitness for any particular purpose
 *
 * ========================================
*/
#include "project.h"
#include "ssd1306.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define DISPLAY_ADDRESS 0x3C // 011110+SA0+RW - 0x3C or 0x3D
#define BATTERY 2
#define ALTERNATOR 3
#define INSIDE 0
#define OUTSIDE 1

float volts(uint32, int);
int temperature(uint32,int);
uint32 readanalog(int);

int main(void){
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable;
    I2C_Start();
    ADC_Start();
    TX_Start();
    display_init(DISPLAY_ADDRESS);

    display_clear();    
    display_update();    
    
    float i, v1, v2, t1, t2;
    int status;
    char* v1t;
    char* v2t;
    char* t1t;
    char* t2t;
    // filled rectangles
    uint8_t color = 1;
    for( i = 0 ; i < gfx_width()/2 ; i += 3 ){
        // alternate colors
        gfx_fillRect(i, i, gfx_width()-i*2, gfx_height(), color%2);
        display_update();    
        color++;
    } 
    CyDelay(2000);
    ADC_StartConvert(); 
    char v1_text[5];
    char v2_text[5];
    char t1_text[5];
    char t2_text[5];
    uint32 v2i,v1i,t1i,t2i;
    int toggle,toggle2;
    
    toggle = 0;
    toggle2 = 0;
    
    double d;
    
    gfx_setTextColor(WHITE);
    gfx_setTextSize(4);
        
    for(;;){

        // clearing display
        display_clear(); 
        display_update(); 
        // read ADC mux 1,2,3,4
        
        //if (toggle == 0){
        //    if (toggle2 == 0){
                v1i = readanalog(BATTERY);
        //        v2i = readanalog(ALTERNATOR);
        //    }else{
                //t1i = readanalog(INSIDE);
                //t2i = readanalog(OUTSIDE);
            //convert ints to strings
           // }
            d = v1i;
            //(void)snprintf(v1_text, 5, 
            //               "B: %liC ", v1i);
            sprintf(v1_text,"%.2d", (int) d, (int) ((d - (int) d ) * 100) );
            //d = v2i;
            //sprintf(v2_text,"%d.%00u", (int) d, (int) ((d - (int) d ) * 100) );
        //}else{
         //   if (toggle2 == 0){
             //   v1 = volts(v1i,BATTERY);
         //       v2 = volts(v2i,ALTERNATOR);
         //   }else{
               // t1i = temperature(t1i, INSIDE);
               // t2i = temperature(t2i, OUTSIDE);
         //   }
           // d = v1i;
           // sprintf(v1_text,"%d.%02u", (int) d, (int) ((d - (int) d ) * 100) );
            d = ADC_CountsTo_Volts(BATTERY, v1i);
            //d = v2;
            sprintf(v2_text,"%.2d", (int) d, (int) ((d - (int) d ) * 100) );
       // }
        v1_text[4] = '\0';
        v2_text[4] = '\0';
        TX_PutString(v1_text);
        TX_PutCRLF();
        TX_PutString(v2_text);
        TX_PutCRLF();
        switch(toggle2){
            case 0:
                //toggle2 = 1;
                gfx_setCursor(0,0);
                gfx_print( "A");
                gfx_println( v1_text);
                TX_PutChar((int)v1t);
                gfx_setCursor(0,32);
                gfx_print( "V");
                gfx_println( v2_text );
                if (toggle == 1) toggle = 0; else toggle = 1;
                break;
            case 1:
            default:
                toggle2 = 0;
                gfx_setCursor(0,0);
                gfx_print( "O");
                gfx_println( t1_text );
                gfx_setCursor(0,32);
                gfx_print( "I" );
                gfx_println( t2_text );
                 if (toggle == 1) toggle = 0; else toggle = 1;
                break;
        }
        display_update(); 
        CyDelay(2000);        
    }
}
uint32 readanalog(int channel){
    //uint32 analog;
    if(0u != ADC_IsEndConversion(ADC_RETURN_STATUS)){;
        return( ADC_GetResult16(channel));
    }else{
        return (9999);
    }
}

float volts(uint32 analog, int channel){
    float v;
    v = ADC_CountsTo_Volts(channel, analog);
    // 10k / 2 k
    //(R1+R2)/R2 * Vmeasurebymicro = V measure
    v= v*(10000+2000)/2000*10;
    return v;
}

int temperature(uint32 analog, int channel){
    float t;
    //5 k bridge 
    //convert to volts from the system first
    t = ADC_CountsTo_Volts(channel, analog);
    // with 5k1 bridge resistor, convert to resistance
    analog = t*5100/(5-t);
    //t = Therm_GetTemperature(analog)*10;
    return (int)t;
}
/* [] END OF FILE */
