/*
htop - TempMeter.c
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.

This meter written by Patrick Louis < patrick at unixhub [dot] net >.
*/

#include "TempMeter.h"

#include "CRT.h"

#include <stdlib.h>
#include <unistd.h>

int TempMeter_attributes[] ={
   TEMPERATURE
};

double getProcTempData(void) {
    double temperature;
    char buffer[100];
    FILE* fp = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);
    if(bytes_read==0 || bytes_read == sizeof(buffer))
        return 0;
    buffer[bytes_read] = '\0';
    temperature = atof(buffer)/1000;
    return temperature;
}

static void TempMeter_setValues(Meter * this, char *buffer, int len){

    double temperature = getProcTempData();
    this->values[0] = temperature;

    const char *Text;
    if (this->mode == TEXT_METERMODE) {
      Text = "%.2f degree C";
    } else {
      Text = "( %.2f C )";
    }

    snprintf(buffer, len, Text, temperature);
    return;
}

MeterType TempMeter = {
   .setValues  = TempMeter_setValues,
   .display    = NULL,
   .mode       = TEXT_METERMODE,
   .items      = 1,
   .total      = 100.0,
   .attributes = TempMeter_attributes,
   .name       = "Temperature",
   .uiName     = "Temperature",
   .caption    = "Temperature: "
};
