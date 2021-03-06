/*******************************************************************************
* File Name: Therm.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the ThermistorCalc
*  Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Therm.h"


/*******************************************************************************
* Function Name: Therm_GetResistance
********************************************************************************
*
* Summary:
*  The digital values of the voltages across the reference resistor and the
*  thermistor are passed to this function as parameters. The function returns
*  the resistance, based on the voltage values.
*
* Parameters:
*  vReference: the voltage across the reference resistor;
*  vThermistor: the voltage across the thermistor.
*  The ratio of these two voltages is used by this function. Therefore, the
*  units for both parameters must be the same.
*
* Return:
*  The return value is the resistance across the thermistor. The value returned
*  is the resistance in Ohms.
*
*******************************************************************************/
uint32 Therm_GetResistance(int16 vReference, int16 vThermistor)
                                      
{
    int32 resT;
    int16 temp;

    /* Calculate thermistor resistance from the voltages */
    resT = Therm_REF_RESISTOR * ((int32)vThermistor);
    if (vReference < 0)
    {
        temp = -vReference;
        temp = (int16)((uint16)((uint16)temp >> 1u));
        temp = -temp;
    }
    else
    {
        temp = (int16)((uint16)((uint16)vReference >> 1u));
    }
    resT += temp;
    resT /= vReference;

    /* The ordering of Reference resistor value is specifically designed to keep the result from overflowing */
    return ((uint32)((uint32)resT << Therm_REF_RES_SHIFT));
}


/*******************************************************************************
* Function Name: Therm_GetTemperature
********************************************************************************
*
* Summary:
*  The value of the thermistor resistance is passed to this function as a
*  parameter. The function returns the temperature, based on the resistance
*  value. The method used to calculate the temperature is dependent on whether
*  Equation or LUT was selected in the Customizer.
*
* Parameters:
*  resT: the resistance across the thermistor in Ohms.
*
* Return:
*  The return value is the temperature in 1/100ths of degrees C. For example,
*  the return value is 2345, when the actual temperature is 23.45 degrees C.
*
*******************************************************************************/
int16 Therm_GetTemperature(uint32 resT) 
{
    int16 tempTR;
    static const uint32 CYCODE Therm_LUT[] = { 68237u, 66603u, 65013u, 63466u, 61959u, 60494u, 59066u, 57677u, 56325u,
 55008u, 53725u, 52477u, 51261u, 50076u, 48923u, 47799u, 46704u, 45638u, 44599u, 43586u, 42600u, 41638u, 40701u, 39788u,
 38898u, 38030u, 37184u, 36360u, 35556u, 34772u, 34007u, 33262u, 32535u, 31826u, 31134u, 30459u, 29801u, 29159u, 28532u,
 27921u, 27325u, 26743u, 26175u, 25620u, 25079u, 24551u, 24036u, 23532u, 23041u, 22561u, 22093u, 21635u, 21189u, 20752u,
 20326u, 19910u, 19504u, 19107u, 18719u, 18340u, 17970u, 17608u, 17254u, 16909u, 16571u, 16241u, 15919u, 15604u, 15296u,
 14995u, 14700u, 14412u, 14131u, 13856u, 13587u, 13324u, 13066u, 12815u, 12568u, 12328u, 12092u, 11862u, 11637u, 11416u,
 11200u, 10989u, 10783u, 10581u, 10383u, 10189u, 10000u, 9815u, 9633u, 9456u, 9282u, 9111u, 8945u, 8782u, 8622u, 8465u,
 8312u, 8162u, 8015u, 7871u, 7730u, 7592u, 7457u, 7325u, 7195u, 7068u, 6943u, 6821u, 6702u, 6585u, 6470u, 6357u, 6247u,
 6139u, 6033u, 5929u, 5827u, 5728u, 5630u, 5534u, 5440u, 5348u, 5257u, 5169u, 5082u, 4997u, 4913u, 4831u, 4751u, 4672u,
 4595u, 4519u, 4444u, 4371u, 4300u, 4230u, 4161u, 4093u, 4027u, 3962u, 3898u, 3835u, 3773u, 3713u, 3654u, 3596u, 3538u,
 3482u, 3427u, 3373u, 3320u, 3268u, 3217u, 3167u, 3117u, 3069u, 3022u, 2975u, 2929u, 2884u, 2840u, 2796u, 2754u, 2712u,
 2671u, 2630u, 2590u, 2551u, 2513u, 2475u, 2438u, 2402u, 2366u, 2331u, 2296u, 2263u, 2229u, 2196u, 2164u, 2133u, 2101u,
 2071u, 2041u, 2011u, 1982u, 1954u, 1925u, 1898u, 1871u, 1844u, 1818u, 1792u, 1766u, 1741u, 1717u, 1693u, 1669u };


    #if (Therm_IMPLEMENTATION == Therm_EQUATION_METHOD)

        float32 stEqn;
        float32 logrT;

        /* Calculate thermistor resistance from the voltages */
        #if(!CY_PSOC3)
            logrT = (float32)log((float64)resT);
        #else
            logrT = log((float32)resT);
        #endif  /* (!CY_PSOC3) */

        /* Calculate temperature from the resistance of thermistor using Steinhart-Hart Equation */
        #if(!CY_PSOC3)
            stEqn = (float32)(Therm_THA + (Therm_THB * logrT) + 
                             (Therm_THC * pow((float64)logrT, (float32)3)));
        #else
            stEqn = (float32)(Therm_THA + (Therm_THB * logrT) + 
                             (Therm_THC * pow(logrT, (float32)3)));
        #endif  /* (!CY_PSOC3) */

        tempTR = (int16)((float32)((((1.0 / stEqn) - Therm_K2C) * (float32)Therm_SCALE) + 0.5));

    #else /* Therm_IMPLEMENTATION == Therm_LUT_METHOD */

        uint16 mid;
        uint16 first = 0u;
        uint16 last = Therm_LUT_SIZE - 1u;

        /* Calculate temperature from the resistance of thermistor by using the LUT */
        while (first < last)
        {
            mid = (first + last) >> 1u;

            if ((0u == mid) || ((Therm_LUT_SIZE - 1u) == mid) || (resT == Therm_LUT[mid]))
            {
                last = mid;
                break;
            }
            else if (Therm_LUT[mid] > resT)
            {
                first = mid + 1u;
            }
            else /* (Therm_LUT[mid] < resT) */
            {
                last = mid - 1u;
            }
        }

        /* Calculation the closest entry in the LUT */
        if ((Therm_LUT[last] > resT) && (last < (Therm_LUT_SIZE - 1u)) &&
           ((Therm_LUT[last] - resT) > (resT - Therm_LUT[last + 1u])))
        {
            last++;
        }
        else if ((Therm_LUT[last] < resT) && (last > 0u) &&
                ((Therm_LUT[last - 1u] - resT) < (resT - Therm_LUT[last])))
        {
            last--;
        }
        else
        {
            /* Closest entry in the LUT already found */
        }

        tempTR = Therm_MIN_TEMP + (int16)((uint16)(last * Therm_ACCURACY));

    #endif /* (Therm_IMPLEMENTATION == Therm_EQUATION_METHOD) */

    return (tempTR);
}


/* [] END OF FILE */
