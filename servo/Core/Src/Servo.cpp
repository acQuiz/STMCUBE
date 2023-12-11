/*
 * servo.cpp
 *
 *  Created on: Nov 30, 2023
 *      Author: bogda
 */

#include "Servo.h"

Servo::Servo(const uint8_t _id) : id(_id){
	// TODO Auto-generated constructor stub
}

Servo::~Servo() {
	// TODO Auto-generated destructor stub
}

void Servo::set_position(double _cmd_pos_degree, double _vel, double _acc )
{
    uint8_t frame[14];
    frame[0] = 0xff;
    frame[1] = 0xff;
    frame[2] = id;
    frame[3] = 0x0a; // packet len
    frame[4] = 0x03; // instruction
    frame[5] = 0x29; // reg address
    frame[6] = 254; // acceleration


    frame[7] = degrees_to_raw(_cmd_pos_degree);
    frame[8] = ( degrees_to_raw(_cmd_pos_degree) >> 8 );
    frame[9] = 0x00;
    frame[10] = 0x00;
    frame[11] = 8000;
    frame[12] = 8000 >> 8;
    frame[13] = calculate_checksum(14, frame);

    mcu_uart5_transmit(frame, 14);
}

uint8_t Servo::calculate_checksum(uint8_t len, uint8_t frame[]) {
	uint8_t checksum = 0;
	for(int i = 2; i< len - 1; i++) {
		checksum += frame[i];
	}
	checksum = ~(checksum);
	return checksum;
}

uint16_t Servo::degrees_to_raw(const double _degree)
{
    uint16_t raw = uint16_t( _degree * 4096.0 / 360.0 );
    return raw;
}
