/*
 * bluetooth.cpp
 *
 *  Created on: 2018¦~1¤ë4¤é
 *      Author: Jake
 */
#include "bluetooth.h"

void isr(Pit *);
bool bluetoothHandler(const Byte*, const size_t);
void isr(libbase::k60::Pit *){
	return;
}

bool bluetoothHandler(const Byte*, const size_t){
	return true;
}
Bluetooth::Bluetooth():m_bt(Config::GetBluetoothConfig(std::function<bool(const Byte *data, const size_t size)>(bluetoothHandler))), m_pit(Config::GetBluetoothPitConfig(std::function<void(Pit*)>(isr))){}



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



