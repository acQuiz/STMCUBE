/*
 * servo.cpp
 *
 *  Created on: Nov 30, 2023
 *      Author: adamc
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
	Frame frame;
    //uint8_t frame[14];


//    frame[0] = SERVO_FRAME_HEADER;
//    frame[1] = SERVO_FRAME_HEADER;
//    frame[2] = id;
//    frame[3] = 0x0a; // packet len
//    frame[4] = SERVO_FRAME_WRITE; // instruction
//    frame[5] = 0x29; // reg address
    frame.push_back( acc_to_raw( _acc ) ); // acceleration
    frame.push_back( degrees_to_raw( _cmd_pos_degree ) );
    frame.push_back( degrees_to_raw( _cmd_pos_degree ) >> 8 );
    frame.push_back( 0x00 );
    frame.push_back( 0x00 );
    frame.push_back( (uint8_t)8000 );
    frame.push_back( 8000 >> 8 );
    set_memory( frame, ServoMemoryAddress::acceleration );
//    frame.push_back( calculate_checksum(14, frame) );
//
//    mcu_uart5_transmit(frame, 14);
}

void Servo::set_P(uint8_t _value){
	Frame data = _value;
	set_memory( data, ServoMemoryAddress::P_Proportionality_coefficient);
}

void Servo::set_I(uint8_t _value){
	Frame data = _value;
	set_memory( data, ServoMemoryAddress::I_Integral_coefficient);
}

void Servo::set_D(uint8_t _value){
	Frame data = _value;
	set_memory( data, ServoMemoryAddress::D_Differential_coefficient);
}

uint8_t Servo::calculate_checksum(const Frame& _frame) {
	uint8_t checksum = 0;
	for(size_t i = 2; i< _frame.size() - 1; i++) {
		checksum += _frame[i];
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

void Servo::set_memory(const Frame& _data, const ServoMemoryAddress _address)
{
	//uint8_t frame_length = _data.size() + 7;
	Frame frame;


	//uint8_t* frame = new uint8_t[frame_length];
	frame.push_back( SERVO_FRAME_HEADER );
	frame.push_back( SERVO_FRAME_HEADER );
	frame.push_back( id );
	frame.push_back( SERVO_FRAME_WRITE );
	frame.push_back( _data.size() + 3 );// packet length
	frame.push_back( (uint8_t) _address );

	for( auto& byte : _frame)
	{
		frame.push_back( byte );
	}

	//std::copy( frame.end(), _data.begin(), _data.end() );
	//frame.insert( (std::vector<uint8_t>) _data );

//	for(int i = 0 ; i < frame_length ; i++)
//	{
//		frame[i+6] = _data[i];
//	}
	frame.push_back( calculate_checksum( frame ) );
	mcu_uart5_transmit( frame.data(), frame.size() );

	for( const auto& byte : _data )
	{
		println("%d", byte);
	}
}

uint16_t Servo::acc_to_raw(const double _acc)
{
	int _acc_int = int(_acc)*29.013;
    uint16_t _raw_acc = uint16_t(_acc_int);
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












