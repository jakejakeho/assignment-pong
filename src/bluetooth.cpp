/*
 * bluetooth.cpp
 *
 *  Created on: 2018¦~1¤ë4¤é
 *      Author: Jake
 */
#include "bluetooth.h"

void Bluetooth::SendBuffer(const Byte *buff, const int &size){
	if(!this->m_bt.SendBuffer(buff, size)){
		EnableTimer(true);
	}else{
		EnableTimer(false);
	}
	delete[] buff;
}

Bluetooth::Bluetooth():m_bt(Config::GetBluetoothConfig(std::function<bool(const Byte *data, const size_t size)>([this](const Byte* buff, const size_t size) -> bool{
	this->Listener(buff,size);
	return true;
}))), m_pit(Config::GetBluetoothPitConfig(std::function<void(Pit*)>([this](Pit*){
	if(this->IsTimerEnable()){
		this->SendFirst();
	}
}))){
	this->EnableTimer(false);
}



void Bluetooth::EnableTimer(bool flag){
	is_timer_enabled = flag;
}





