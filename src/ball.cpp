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

void Ball::move(int yourPlatform_x, int opponentPlatform_x){
	clean();
	m_position.x += m_v_x;
	m_position.y += m_v_y;
	rebound(yourPlatform_x, opponentPlatform_x);
}

void Ball::render(){
	draw();
}

void Ball::rebound(int yourPlatform_x, int opponentPlatform_x){
	//hit wall
	    	int contactPoint_x, contactPoint_y, dx, dy, px, py;
	    	px = m_position.x - m_v_x;
	    	py = m_position.y - m_v_y;
	    	if (m_position.x < 4 || m_position.x > 123){
	        	if (m_position.x < 4){
	        		dx = 4 - px;
	        	}
	        	else{
	        		dx = 123 - px;
	        	}
	       		dy = dx * m_v_y / m_v_x; //result should be int, floored
	       		contactPoint_x = px + dx;
	       		contactPoint_y = py + dy;
	       		m_position.x = contactPoint_x + ((m_v_x-dx)/m_v_x)*(-m_v_x);
	       		m_position.y = contactPoint_y + ((m_v_y-dy)/m_v_y)*(m_v_y);
	    		setVelocity(-m_v_x,m_v_y);
	    		return;
	    	}
	    	//hit platform
	    	if((m_position.y < 11 && opponentPlatform_x <= px && px <= opponentPlatform_x + 29) || (m_position.y > 148 && yourPlatform_x <= px && px <= yourPlatform_x + 29)){ // && (m_position.x >= )
	        	int new_v_x;
	        	if (m_position.y < 11){
	        		dy = 11 - py;
	           		new_v_x = (px-opponentPlatform_x)/2 - 7;
	        	}
	        	else{
	        		dy = 148 - py;
	           		new_v_x = (px-yourPlatform_x)/2 - 7;
	        	}
	       		dx = dy * m_v_x / m_v_y; //result should be int, floored
	       		contactPoint_x = px + dx;
	       		contactPoint_y = py + dy;
	       		m_position.x = contactPoint_x + ((m_v_x-dx)/m_v_x)*(new_v_x);
	       		m_position.y = contactPoint_y + ((m_v_y-dy)/m_v_y)*(-m_v_y);
	    		setVelocity(new_v_x,-m_v_y);
	    	}
}

Ball::Ball(libsc::Lcd* pLcd):Sprite(myConfig::GetSpriteConfig(0xfd20,0xffff,5,5,61,80,pLcd)){}
