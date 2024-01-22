/*
 * servo.h
 *
 *  Created on: Nov 30, 2023
 *      Author: adamc
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <vector>

#include "MCU.h"
#include "servo_defines.h"

class Servo {

	enum class ServoMemoryAddress{
		Firmware_sub_version_number	=	1,
		servo_Main_Version_Number	=	3,
		servo_sub_version_number	=	4,
		ID	=	0x5,
		Baud_rate	=	0x6,
		Return_delay	=	0x7,
		Response_status_level	=	0x8,
		Minimum_Angle_Limitation	=	0x9,
		Maximum_Angle_Limitation	=	0xB,
		Maximum_Temperature_Limit	=	0xD,
		Maximum_input_voltage	=	0xE,
		Minimum_input_voltage	=	0xF,
		Maximum_torque	=	0x10,
		phase	=	0x12,
		Unloading_condition	=	0x13,
		LED_Alarm_condition	=	0x14,
		P_Proportionality_coefficient	=	0x15,
		D_Differential_coefficient	=	0x16,
		I_Integral_coefficient	=	0x17,
		Minimum_startup_force	=	0x18,
		Clockwise_insensitive_area	=	0x1A,
		Counterclockwise_insensitive_region	=	0x1B,
		Protection_current	=	0x1C,
		Angular_resolution	=	0x1E,
		Position_correction	=	0x1F,
		Operation_mode	=	0x21,
		Protective_torque	=	0x22,
		Protection_time	=	0x23,
		Overload_torque	=	0x24,
		Speed_closed_loop_P_proportional_coefficient	=	0x25,
		Over_current_protection_time	=	0x26,
		Velocity_closed_loop_I_integral_coefficient	=	0x27,
		Torque_switch	=	0x28,
		acceleration	=	0x29,
		Target_location	=	0x2A,
		Running_time	=	0x2C,
		running_speed	=	0x2E,
		Torque_limit	=	0x30,
		Lock_mark	=	0x37,
		current_location	=	0x38,
		Current_speed	=	0x3A,
		Current_load	=	0x3C,
		Current_voltage	=	0x3E,
		Current_temperature	=	0x3F,
		Asynchronous_write_flag	=	0x40,
		Servo_status	=	0x41,
		Mobile_sign	=	0x42,
		Current_current	=	0x45
		};
typedef std::vector<uint8_t> Frame;


private:
	uint8_t id;
public:
	Servo(const uint8_t _id);
	virtual ~Servo();
	void set_position(double _cmd_pod_degree, double _vel, double _acc);

private:
	uint8_t calculate_checksum(const Frame& _frame);
	uint16_t degrees_to_raw(const double _degree);
	void check_limits(uint16_t& _raw_position);
	void check_limits_acceleration(uint16_t& _acc);
	void set_memory(const Frame& _data, const ServoMemoryAddress _address);
	uint16_t acc_to_raw(const double _acc);
};

#endif /* SERVO_H_ */

