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
#include "score.h"

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
    bool isMaster = false;
    bool isSlave = false;

    char mode = 'M';

    Ball ball(&lcd);
    Platform enemyPlatform(&lcd, true);
    Platform myPlatform(&lcd, false);
    Score enemyScore(&lcd, true);
    Score myScore(&lcd, false);
    Joystick js(myConfig::GetJoystickConfig(Joystick::Listener([&isMaster, &isSlave,&bt,&myPlatform, &mode](const uint8_t id, const Joystick::State state){
    	if(state == Joystick::State::kLeft && mode == 'M'){
    		mode = 'L';
    	}else if(state == Joystick::State::kRight && mode == 'M'){
    		mode = 'R';
    	}else if((state == Joystick::State::kLeft && mode == 'R') || (state == Joystick::State::kRight && mode == 'L')){
    		mode = 'M';
    	}else if(state == Joystick::State::kSelect && !isSlave && !isMaster){
    		isMaster = true;
    		bt.SendPackage({0,Bluetooth::PkgType::kStart,{}});
    		Comm* temp = &bt;
    		temp->startWait();
    	}
    })));

    Comm::Package pkg;

    bt.SetHandler(Bluetooth::PackageHandler([&isMaster,&isSlave,&led0,&led1,&led2,&led3,&bt,&pkg,&counter](Bluetooth::Package package){
    	pkg = package;
    	counter++;
    	switch((int)package.type){
    	case Bluetooth::PkgType::kStart:
    		if(!isSlave && !isMaster){
    			led0.Switch();
    			bt.SendPackage({0,Bluetooth::PkgType::kStartACK,{}});
    			isSlave = true;
    		}
			break;
    	case Bluetooth::PkgType::kStartACK:
    		if(isMaster){
    			led1.Switch();
    			Comm* temp = &bt;
    			temp->stopWait();
    			if(queue.size() > 0)
    				queue.erase(queue.begin());
    		}
    		break;
    	}
    }));
    enemyPlatform.render();
    myPlatform.render();
    myScore.addScore();
    enemyScore.addScore();
    while(1){
    	if(System::Time() != lastTime){
    		lastTime = System::Time();
    		if(lastTime % 50 == 0){
    //			char c[10];
	//			lcd.SetRegion(Lcd::Rect(0,0,100,15));
	//			sprintf(c,"size:%d!",(int)bt.queue.size());
	//			writer.WriteBuffer(c,10);
	    	    ball.move(myPlatform.getPosition().x, enemyPlatform.getPosition().x);
	    	    ball.render();
	    	    enemyPlatform.render();
	    	    myPlatform.render();
    		}
    		if(lastTime % 75 == 0){
	    	    if(mode == 'L'){
	    	    	myPlatform.moveLeft();
	    	    	myPlatform.render();
	    	    }else if(mode == 'R'){
	    	    	myPlatform.moveRight();
	    	    	myPlatform.render();
	    	    }
    		}
    	}
    }
    return 0;
}
