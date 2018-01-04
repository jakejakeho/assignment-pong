/*
 * bluetooth.cpp
 *
 *  Created on: 2018¦~1¤ë4¤é
 *      Author: Jake
 */
#include "bluetooth.h"
#include "config.h"
void bluetoothSend(Pit *);
bool bluetoothHandler(const Byte*, const size_t);
Bluetooth::Bluetooth():m_bt(JyMcuBt106(Config::GetBluetoothConfig(bluetoothHandler))),m_pit(Pit(Config::GetBluetoothPitConfig(bluetoothSend))){}
void bluetoothSend(Pit *){
	return;
}

bool bluetoothHandler(const Byte*, const size_t){
	return true;
}


void Bluetooth::EnableTimer(bool flag){
	if(this->is_timer_enabled && !flag){
		this->is_timer_enabled = false;
		return;
	}else if (this->is_timer_enabled && flag){
		this->is_timer_enabled = true;
		return;
	}else{
		return;
	}
}



