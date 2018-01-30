/*
 * main.cpp
 *
 * Author: 
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <cassert>
#include <cstring>
#include <string>
#include <libbase/k60/mcg.h>
#include <libsc/system.h>

#include <libsc/led.h>
#include <libsc/k60/jy_mcu_bt_106.h>
#include "libsc/led.h"
#include "libsc/joystick.h"
#include "libsc/st7735r.h"
#include "libsc/battery_meter.h"
#include "libsc/k60/jy_mcu_bt_106.h"
#include "libbase/k60/pit.h"
#include "libsc/lcd_typewriter.h"
#include "bluetooth.h"
#include "comm.h"
#include "ball.h"
#include "platform.h"

namespace libbase
{
    namespace k60
    {

        Mcg::Config Mcg::GetMcgConfig()
        {
            Mcg::Config config;
            config.external_oscillator_khz = 50000;
            config.core_clock_khz = 150000;
            return config;
        }

    }
}

using libsc::System;
using namespace libsc;
using namespace libbase::k60;

Led *pLed = nullptr;

bool Listener(const unsigned char*, const unsigned int){
	if(pLed)pLed->Switch();
	return 1;
}

char *str = "";

int main() {
    System::Init();

    Led led0(myConfig::GetLedConfig(0));
    Led led1(myConfig::GetLedConfig(1));
    Led led2(myConfig::GetLedConfig(2));
    Led led3(myConfig::GetLedConfig(3));
    pLed = &led0;

    led0.SetEnable(1);
    led1.SetEnable(1);
    led2.SetEnable(1);
    led3.SetEnable(1);


    St7735r lcd(myConfig::GetLcdConfig());
    LcdTypewriter writer(myConfig::GetWriterConfig(&lcd));
    LcdConsole console(myConfig::GetConsoleConfig(&lcd));
    lcd.SetRegion(Lcd::Rect(0,0,128,160));
    lcd.FillColor(lcd.kWhite);

    Bluetooth bt;

    int counter = 0;
    uint32_t lastTime = 0;

    Ball ball(&lcd);
    Platform platform(&lcd);
    Joystick js(myConfig::GetJoystickConfig(Joystick::Listener([&platform](const uint8_t id, const Joystick::State state){
    	if(state == Joystick::State::kLeft){
    		platform.moveLeft();
       		platform.render();
    	}else if(state == Joystick::State::kRight){
    		platform.moveRight();
       		platform.render();
    	}
    })));

    Comm::Package pkg;

    bt.SetHandler(Bluetooth::PackageHandler([&led0,&led1,&led2,&led3,&bt,&pkg,&counter](Bluetooth::Package package){
    	pkg = package;
    	counter++;
    	switch((int)package.type){
    	case Bluetooth::PkgType::kStart:
    		led0.Switch();
    		bt.SendPackage({0,Bluetooth::PkgType::kStartACK,{}});
			break;
    	case Bluetooth::PkgType::kStartACK:
    		led1.Switch();
    		Comm* temp = &bt;
    		temp->stopWait();
    		break;
    	}

    }));
    bt.SendPackage({0,Bluetooth::PkgType::kStart,{}});
    //bt.SendPackage({0,Bluetooth::PkgType::kLocation,{1,2}});
    platform.render();
    while(1){
    	if(System::Time() != lastTime){
    		lastTime = System::Time();
    		if(lastTime % 50 == 0){
    			bt.SendPackage({0,Bluetooth::PkgType::kStart,{}});
    //			char c[10];
	//			lcd.SetRegion(Lcd::Rect(0,0,100,15));
	//			sprintf(c,"size:%d!",(int)bt.queue.size());
	//			writer.WriteBuffer(c,10);
	    	    ball.move();
	    	    ball.render();
    		}
    	}
    }
    return 0;
}
