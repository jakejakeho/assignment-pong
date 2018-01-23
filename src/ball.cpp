/*
 * ball.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: Harry_000
 */

#include "ball.h"
using namespace std;

void Ball::setVelocity(int v_x,int v_y){
	m_v_x = v_x;
	m_v_y = v_y;
}

void Ball::move(){
	this->m_position = Coord(m_position.x + m_v_x, m_position.y + m_v_y);
}

void Ball::render(){
	clean();
	draw();
}

void Ball::rebound(){
Config::
}

Ball::Ball(libsc::Lcd* pLcd):Sprite(Config::GetSpriteConfig(0xfd20,0xffff,5,5,10,10,pLcd)){}
