/*
 * ball.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: Harry_000
 */

#include "ball.h"
#include "config.h"
using namespace std;

void Ball::setVelocity(int v_x,int v_y){
	m_v_x = v_x;
	m_v_y = v_y;
}

void Ball::move(){
	clean();
	this->m_position = Coord(m_position.x + m_v_x, m_position.y + m_v_y);
}

void Ball::render(){
	draw();
}

void Ball::rebound(){
}

Ball::Ball(libsc::Lcd* pLcd):Sprite(myConfig::GetSpriteConfig(0xfd20,0xffff,5,5,10,10,pLcd)){}
