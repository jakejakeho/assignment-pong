/*
 * platform.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: Harry_000
 */

#include "score.h"
using namespace std;

Score::Score(libsc::Lcd* pLcd, bool isTop):Sprite(myConfig::GetSpriteConfig(pLcd->kGreen,Lcd::kWhite,6,4,4,isTop?0:155,pLcd)){}

void Score::render(){
	const static int initX = 114;
	for(int i = 0; i < score; i++){
		this->m_position = Coord(initX - (i * 10), m_position.y);
		draw();
	}
}

void Score::addScore(){
	if(score + 1 <= 3){
		score++;
		render();
	}
}
