/*
 * servo.h
 *
 *  Created on: Nov 30, 2023
 *      Author: bogda
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "MCU.h"
#include "servo_defines.h"

class Servo {
private:
	uint8_t id;
public:
	Servo(const uint8_t _id);
	virtual ~Servo();
	void set_position(double _cmd_pod_degree, double _vel, double _acc);

private:
	uint8_t calculate_checksum(uint8_t len, uint8_t frame[]);
	uint16_t degrees_to_raw(const double _degree);
	void check_limits(uint16_t& _raw_position);
};

#endif /* SERVO_H_ */
