/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED.h
    @author   ktown

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2016, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#ifndef _Adafruit_FeatherOLED_H_
#define _Adafruit_FeatherOLED_H_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Adafruit_FeatherOLED : public Adafruit_SSD1306
{
  protected:
    float   _battery;
    float   _percentage;
    bool    _batteryIcon;
    bool    _batteryVisible;
    bool    _voltageVisible;
    bool    _batteryLow;
    bool    _alternate;

    void renderBattery    ( void );

  public:
    enum
    {
      FOLED_BATTERYICON_NONE      = 0,       // Displays volts
      FOLED_BATTERYICON_THREEBAR  = 1
    };

    // Constructor
    Adafruit_FeatherOLED ( int reset = -1 ) : Adafruit_SSD1306(reset)
    {
      _battery            = 0.0F;
      _batteryIcon        = true;
      _batteryVisible     = true;
      _voltageVisible     = true;
      _batteryLow    = false;
      _alternate          = true;
    }

    void setBattery          ( float vbat, float pbat )     { _battery = vbat; _percentage = pbat;}
    void setBatteryVisible   ( bool enable )    { _batteryVisible = enable; }
    void setBatteryIcon      ( bool enable )    { _batteryIcon = enable; }
    void setVoltageVisible   ( bool enable )    { _voltageVisible = enable; }
    void setBatteryLow       ( bool enable )    { _batteryLow = enable; if(!enable){_alternate = true;}}

    void init          ( void );
    void clearMsgArea  ( void );
};

#endif /* _Adafruit_FeatherOLED_H_ */
