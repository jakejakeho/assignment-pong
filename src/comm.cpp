/*
 * comm.cpp
 *
 *  Created on: 2018¦~1¤ë4¤é
 *      Author: Jake
 */
#include "comm.h"

Comm::Comm():send_time(0),is_waiting_ack(false)){}

Comm::~Comm(){}

void Comm::SendPackage(const Package& pkg, bool need_ack){
	this->queue.push_back(pkg);
	this->send_time = libsc::System::Time();
	if(need_ack){
		is_waiting_ack = true;
		while(this->is_waiting_ack){
			switch((int)this->queue[0].type){
				case PkgType::kStart:
					Byte *buff = new Byte[3];
					buff[0] = (Byte)0;
					buff[1] = (Byte)PkgType::kStart;
					buff[2] = (Byte)BitConsts::kSTART;
					SendBuffer(buff, 3);
					break;
			}
		}
	}else{
		switch((int)this->queue[0].type){
			case PkgType::kStart:
				Byte *buff = new Byte[3];
				buff[0] = (Byte)0;
				buff[1] = (Byte)PkgType::kStart;
				buff[2] = (Byte)BitConsts::kSTART;
				SendBuffer(buff, 3);
				break;
		}
	}
}

void Comm::SendFirst(){

}


