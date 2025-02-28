/******************************************************************************
WMM_Tinier.cpp
WMM_Tinier Arduino Library C++ source
David Armstrong
Version 1.0.0 - August 6, 2021
https://github.com/DavidArmstrong/WMM_Tinier

Resources:
Uses math.h for math function
Refer to https://github.com/miniwinwm/WMM_Tiny

Development environment specifics:
Arduino IDE 1.8.15

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example.
Distributed as-is; no warranty is given.
******************************************************************************/

// include this library's description file
#include "WMM_Tinier.h"
#include "wmm.c"

// Need the following define for SAMD processors
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

// Public Methods //////////////////////////////////////////////////////////
// Start by doing any setup, and verifying that doubles are supported
bool WMM_Tinier::begin(void)
{
    wmm_init();
    return true;
}

float WMM_Tinier::decimalDegrees(int degrees, int minutes, float seconds)
{
    int sign = 1;
    if (degrees < 0)
    {
        degrees = -degrees;
        sign = -1;
    }
    if (minutes < 0)
    {
        minutes = -minutes;
        sign = -1;
    }
    if (seconds < 0)
    {
        seconds = -seconds;
        sign = -1;
    }
    double decDeg = degrees + (minutes / 60.0) + (seconds / 3600.);
    return decDeg * sign;
}

void WMM_Tinier::printDegMinSecs(float n)
{
    bool sign = (n < 0.);
    if (sign)
        n = -n;
    long lsec = n * 360000.0;
    long deg = lsec / 360000;
    long min = (lsec - (deg * 360000)) / 6000;
    float secs = (lsec - (deg * 360000) - (min * 6000)) / 100.;
    if (sign)
        Serial.print("-");
    Serial.print(deg);
    Serial.print(":");
    Serial.print(min);
    Serial.print(":");
    Serial.print(abs(secs));
    Serial.print(" ");
}

void WMM_Tinier::magneticCalculation(float Altitude, float Latitude, float Longitude, uint8_t year, uint8_t month, uint8_t day)
{
    //wmm_init();
    float wmm_date = wmm_get_date(year, month, day);
    float bx, by, bz;
    E0000(Altitude, Latitude, Longitude, wmm_date, &bx, &by, &bz);
    spData.bNorth = bx;
    spData.bEast = by;
    spData.bDown = bz;
    spData.longitude = Longitude;
    spData.latitude = Latitude;
    spData.altitude = Altitude;
    spData.date = wmm_date;
    spData.bMagnitude = spData.bMagnitude = sqrt(bx * bx + by * by + bz * bz); 
}
