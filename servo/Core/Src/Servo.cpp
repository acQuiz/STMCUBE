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
    frame[0] = SERVO_FRAME_HEADER;
    frame[1] = SERVO_FRAME_HEADER;
    frame[2] = id;
    frame[3] = 0x0a; // packet len
    frame[4] = SERVO_FRAME_WRITE; // instruction
    frame[5] = 0x29; // reg address
    frame[6] = acc_to_raw(_acc); // acceleration
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
    uint16_t raw_position = uint16_t( _degree * SERVO_POSITION_RESOLUTION / SERVO_ANGEL_POSITION_RANGE_MAX );

    check_limits(raw_position);


    return raw_position;
}

void Servo::check_limits(uint16_t& _raw_position)
{
	if( _raw_position > SERVO_RAW_POSITION_MAX)
	{
		_raw_position = SERVO_RAW_POSITION_MAX;
	}
	else if( _raw_position < SERVO_RAW_POSITION_MIN)
	{
		_raw_position < SERVO_RAW_POSITION_MIN;
	}
	else if(_raw_position == SERVO_POSITION_INVALID1)
		{
			_raw_position--;
		}

	else if(_raw_position == SERVO_POSITION_INVALID2)
		{
			_raw_position--;
		}
}

//void Servo::set_memory(const uint8_t* _data, const uint8_t_length)
//{
//	uint8_t frame_length = _data_length + 7;
//
//	uint8_t* frame = new uint8_t[frame_length];
//	frame[0] = SERVO_FRAME_HEADER;
//	frame[1] = SERVO_FRAME_HEADER;
//	frame[2] = id;
//	frame[3] = SERVO_FRAME_WRITE;
//	frame[4] = _data_lenght + 3;// packet lenght
//	//frame[5] =
//
//	for(int i = 0 ; i < frame_lenght ; i++)
//	{
//		frame[i+6] = _data[i];
//	}
//	frame[frame_length -1]= calculate_checksum(frame_length,frame);
//	mcu_uart5_transmit(frame, frame_length);
//
//
//}
uint16_t Servo::acc_to_raw(const double _acc)
{
    uint16_t _raw_acc = uint16_t(_acc);
    check_limits_acceleration(_raw_acc);


    return _raw_acc;
}

void Servo::check_limits_acceleration(uint16_t& _raw_acc)
	{
	if( _raw_acc > SERVO_RAW_ACC_MAX)
		{
		_raw_acc = SERVO_RAW_ACC_MAX;
		}
	else if( _raw_acc < SERVO_RAW_ACC_MIN)
		{
		_raw_acc < SERVO_RAW_ACC_MIN;
		}
	}












