/*
 * sprite.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: Harry_000
 */

#include "sprite.h"
using namespace std;

Sprite::Sprite(Config config):m_bg_color(config.bg_color),m_fg_color(config.fg_color),m_height (config.height),m_width (config.width),m_position(Coord(config.x,config.y)),m_pLcd (config.pLcd){}

void Sprite::clean(){
	this->m_pLcd->SetRegion(libsc::Lcd::Rect(m_position.x,m_position.y,m_width,m_height));
	this->m_pLcd->ClearRegion();
}

void Sprite::draw(){
	this->m_pLcd->SetRegion(libsc::Lcd::Rect(m_position.x,m_position.y,m_width,m_height));
	this->m_pLcd->FillColor(m_fg_color);
}

Coord Sprite::getPosition(){
	return this->m_position;
}


void Sprite::setPosition(Coord coord){
	this->m_position = coord;
}

void Sprite::setPosition(int x,int y){
	this->m_position = Coord(x,y);
}
