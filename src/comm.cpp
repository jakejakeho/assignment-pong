/*
 * comm.cpp
 *
 *  Created on: 2018¦~1¤ë4¤é
 *      Author: Jake
 */
#include "comm.h"

Comm::Comm():send_time(0),is_waiting_ack(false){}

Comm::~Comm(){}

void Comm::SendPackage(const Package& pkg, bool need_ack){
	queue.push_back(pkg);
	SendFirst();
}

void Comm::SendFirst(){
	this->send_time = libsc::System::Time();
	int size = 0;
	switch(queue[0].type){
		case Comm::PkgType::kStart:
			size = 3;
			break;
		case Comm::PkgType::kStartACK:
			size = 3;
			break;
		case Comm::PkgType::kMasterPlatform:
			size = 4;
			break;
		case Comm::PkgType::kMasterPlatformACK:
			size = 3;
			break;
		case Comm::PkgType::kSlavePlatform:
			size = 4;
			break;
		case Comm::PkgType::kSlavePlatformACK:
			size = 3;
			break;
		case Comm::PkgType::kReflection:
			size = 5;
			break;
		case Comm::PkgType::kReflectionACK:
			size = 3;
			break;
		case Comm::PkgType::kLocation:
			size = 5;
			break;
		case Comm::PkgType::kLocationACK:
			size = 3;
			break;
		case Comm::PkgType::kResult:
			size = 4;
			break;
		case Comm::PkgType::kResultACK:
			size = 3;
			break;
		}
	Byte* buff = new Byte[queue[0].type]
	Sendbuffer();
	if((int)queue[0].type % 2 == 0){
		this->is_waiting_ack = true;
	}
}

void Comm::BuildBufferPackage(){
	Package pkg;
	pkg.frame_id = buffer[0];
	pkg.type = (Comm::PkgType)buffer[1];
	switch((int)pkg.type){
	case Comm::PkgType::kStart:
		pkg.data = {};
		break;
	case Comm::PkgType::kStartACK:
		pkg.data = {};
		break;
	case Comm::PkgType::kMasterPlatform:
		pkg.data = {buffer[2]};
		break;
	case Comm::PkgType::kMasterPlatformACK:
		pkg.data = {};
		break;
	case Comm::PkgType::kSlavePlatform:
		pkg.data = {buffer[2]};
		break;
	case Comm::PkgType::kReflection:
		pkg.data = {buffer[2],buffer[3]};
		break;
	case Comm::PkgType::kReflectionACK:
		pkg.data = {};
		break;
	case Comm::PkgType::kLocation:
		pkg.data = {buffer[2], buffer[3]};
		break;
	case Comm::PkgType::kLocationACK:
		pkg.data = {};
		break;
	case Comm::PkgType::kResult:
		pkg.data = {buffer[2]};
		break;
	case Comm::PkgType::kResultACK:
		pkg.data = {};
		break;
	}
}

bool Comm::Listener(const Byte* buff, const size_t size){
	for(int i = 0; i< (int)size; i++){
		Byte temp = buff[i];
		buffer.push_back(temp);
	}
	this->BuildBufferPackage();
	return true;
}

