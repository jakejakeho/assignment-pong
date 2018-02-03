/*
 * platform.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: Harry_000
 */

#include "platform.h"
using namespace std;

Platform::Platform(libsc::Lcd* pLcd, bool isTop):Sprite(myConfig::GetSpriteConfig(0x0000,0xffff,30,4,49,isTop?5:151,pLcd)){}

void Platform::moveLeft(){
	if(m_position.x > 4){
		clean();
		this->m_position = Coord(m_position.x - 4, m_position.y);
	}
}

void Platform::moveRight(){
	if(m_position.x < 94){
		clean();
		this->m_position = Coord(m_position.x + 4, m_position.y);
	}
}

void Platform::render(){

	draw();
}
