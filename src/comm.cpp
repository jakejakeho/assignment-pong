/*
 * comm.cpp
 *
 *  Created on: 2018¦~1¤ë4¤é
 *      Author: Jake
 */
#include "comm.h"
#include <cstring>
Comm::Comm():send_time(0),is_waiting_ack(false){}

Comm::~Comm(){}

void Comm::SendPackage(const Package& pkg, bool need_ack){
	queue.push_back(pkg);
	SendFirst();
}

void Comm::SendFirst(){
	this->send_time = libsc::System::Time();
	int size = 0;
	Byte* buff = nullptr;
	Byte temp;
	if(queue.size == 0)
		return;
	switch(queue[0].type){
		case Comm::PkgType::kStart:
			size = 3;
			buff = new Byte[size];
			temp = 0x00;
			std::memcpy(&buff[0], &temp, 1);
			temp = Comm::PkgType::kStart;
			std::memcpy(&buff[1], &temp, 1);
			temp = Comm::BitConsts::kSTART;
			std::memcpy(&buff[2], &temp, 1);
			is_waiting_ack = true;
			break;
		case Comm::PkgType::kStartACK:
			size = 3;
			buff = new Byte[size];
			temp = 0x00;
			std::memcpy(&buff[0], &temp, 1);
			temp = Comm::PkgType::kStartACK;
			std::memcpy(&buff[1], &temp, 1);
			temp = Comm::BitConsts::kACK;
			std::memcpy(&buff[2], &temp, 1);
			break;
		case Comm::PkgType::kMasterPlatform:
			size = 4;
			is_waiting_ack = true;
			break;
		case Comm::PkgType::kMasterPlatformACK:
			size = 3;
			break;
		case Comm::PkgType::kSlavePlatform:
			size = 4;
			is_waiting_ack = true;
			break;
		case Comm::PkgType::kSlavePlatformACK:
			size = 3;
			break;
		case Comm::PkgType::kReflection:
			size = 5;
			is_waiting_ack = true;
			break;
		case Comm::PkgType::kReflectionACK:
			size = 3;
			break;
		case Comm::PkgType::kLocation:
			size = 5;
			is_waiting_ack = true;
			break;
		case Comm::PkgType::kLocationACK:
			size = 3;
			is_waiting_ack = true;
			break;
		case Comm::PkgType::kResult:
			size = 4;
			is_waiting_ack = true;
			break;
		case Comm::PkgType::kResultACK:
			size = 3;
			is_waiting_ack = true;
			break;
		}
	SendBuffer(buff,size);
	queue.clear();
}

void Comm::BuildBufferPackage(){
	Package pkg;
	std::memcpy(&pkg.frame_id, &buffer[0], 1);
	std::memcpy(&pkg.type, &buffer[1], 1);
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
		pkg.data = {};
		break;
	case Comm::PkgType::kSlavePlatformACK:
		pkg.data = {};
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
		is_waiting_ack = false;
		break;
	}
	buffer.clear();
	this->Handler(pkg);
}

bool Comm::Listener(const Byte* buff, const size_t size){
	for(int i = 0; i< (int)size; i++){
		Byte temp = buff[i];
		buffer.push_back(temp);
	}
	Byte lastElement = buffer[buffer.size() - 1];
	if(lastElement == Comm::BitConsts::kACK || lastElement == Comm::BitConsts::kEND || lastElement == Comm::BitConsts::kSTART)
		this->BuildBufferPackage();
	return true;
}

