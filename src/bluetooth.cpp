/*
 * bluetooth.cpp
 *
 *  Created on: 2018¦~1¤ë4¤é
 *      Author: Jake
 */
#include "bluetooth.h"

void bluetoothSend(Pit *);
bool bluetoothHandler(const Byte*, const size_t);
void bluetoothSend(Pit *){
	return;
}

void Bluetooth::SendBuffer(const Byte *buff, const int &size){
	if(this->m_bt.SendBuffer(buff, size)){
		delete[] buff;
	}
}

bool bluetoothHandler(const Byte* buff, const size_t size){

}


Bluetooth::Bluetooth():m_bt(Config::GetBluetoothConfig(), m_pit(Config::GetBluetoothPitConfig(std::function<void(Pit*)>(bluetoothSend))){
	this->EnableTimer(false);
}



void Bluetooth::EnableTimer(bool flag){
	is_timer_enabled = flag;
}





