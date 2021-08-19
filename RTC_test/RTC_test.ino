/****************************************************************************/
//  Function: Set time and get the time from RTC chip(DS1307) and display
//        it on the serial monitor.
//  Hardware: Grove - RTC
//  Arduino IDE: Arduino-1.0
//  Author:  FrankieChu
//  Date:    Jan 19,2013
//  Version: v1.0
//  by www.seeedstudio.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
/****************************************************************************/
#include <Wire.h>
#include "DS1307.h"

DS1307 clk;//define a object of DS1307 class
void setup() {
    Serial.begin(115200);
    clk.begin();
//    clk.fillByYMD(2021, 8, 19); //Jan 19,2013
//    clk.fillByHMS(14, 35, 15); //15:28 30"
//    clk.fillDayOfWeek(MON);//Saturday
//    clk.setTime();//write time to the RTC chip
}
void loop() {
    printTime();
}
/*Function: Display time on the serial monitor*/
void printTime() {
    clk.getTime();
    Serial.print(clk.hour, DEC);
    Serial.print(":");
    Serial.print(clk.minute, DEC);
    Serial.print(":");
    Serial.print(clk.second, DEC);
    Serial.print("  ");
    Serial.print(clk.month, DEC);
    Serial.print("/");
    Serial.print(clk.dayOfMonth, DEC);
    Serial.print("/");
    Serial.print(clk.year + 2000, DEC);
    Serial.print(" ");
    Serial.print(clk.dayOfMonth);
    Serial.print("*");
    switch (clk.dayOfWeek) { // Friendly printout the weekday
        case MON:
            Serial.print("MON");
            break;
        case TUE:
            Serial.print("TUE");
            break;
        case WED:
            Serial.print("WED");
            break;
        case THU:
            Serial.print("THU");
            break;
        case FRI:
            Serial.print("FRI");
            break;
        case SAT:
            Serial.print("SAT");
            break;
        case SUN:
            Serial.print("SUN");
            break;
    }
    Serial.println(" ");
    
}
