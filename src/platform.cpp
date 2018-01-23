/*
 * platform.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: Harry_000
 */

#include "platform.h"
using namespace std;

Platform::Platform(libsc::Lcd* pLcd):Sprite(Config::GetSpriteConfig(0x0000,0xffff,30,4,10,10,pLcd)){}

void Platform::moveLeft(){
	if(m_position.x >= 0)
		this->m_position = Coord(m_position.x - 1, m_position.y);
}

void Platform::moveRight(){
	if(m_position.x <= 120)
		this->m_position = Coord(m_position.x + 1, m_position.y);
}

void Platform::render(){
	clean();
	draw();
}
