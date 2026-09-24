//
// Created by pawel on 22.09.2026.
//

#include "Servo.h"

constexpr s16 steps = 4096;
constexpr u32 oneStepSpeed = 68306; // exactly 68,3060109289618

/*
 Simplest GoTo function.
 angle => degreees (0 - 360)
 speedRPM => rotations per minute (0 - 449)
 acceleration => not a standard unit (0 - 150)
 */
void GoToAngle(SMS_STS& servos, u8 id, u16 angle, u16 speedRPM, u8 acceleration) {
	s16 position = angle * steps / 360 ;
	u16 speed = oneStepSpeed * speedRPM / 1000;
	servos.WritePosEx(id, position, speed, acceleration);
}

void GoToAngleClosestWay(SMS_STS& servos, u8 id, u16 angle, u16 speedRPM, u8 acceleration) {
	const s16 position = (angle * steps) / 360;
	const u16 speed = oneStepSpeed * speedRPM / 1000;

	if(servos.FeedBack(id) == -1){
		Serial.println("GetInfo error");
		return;
	}
	const int currentPosition = servos.ReadPos(-1);

	int delta =	position - currentPosition;

	if (delta > steps / 2) {
		delta -= steps;
	}

	if (delta < -steps / 2) {
		delta += steps;
	}

	if (delta >= 0) {
		servos.WritePosEx(id, position, -speed, acceleration);
	}
	else {
		servos.WritePosEx(id, position, speed, acceleration);
	}
}

void GoToAngleASAP(SMS_STS& servos, u8 id, u16 angle) {
	s16 position = angle * steps / 360 ;
	servos.WritePosEx(id, position, 3073, 0);
}

void GoToAngleClosestWayASAP(SMS_STS& servos, u8 id, u16 angle) {
	const s16 position = angle * steps / 360 ;

	if(servos.FeedBack(id) == -1){
		Serial.println("GetInfo error");
		return;
	}
	const int currentPosition = servos.ReadPos(-1);

	int delta =	position - currentPosition;

	if (delta > steps / 2) {
		delta -= steps;
	}

	if (delta < -steps / 2) {
		delta += steps;
	}

	if (delta >= 0) {
		servos.WritePosEx(id, position, -3073, 0);
	}
	else {
		servos.WritePosEx(id, position, 3073, 0);
	}
}

ServoInfo GetInfo(SMS_STS& servos, u8 id) {
	if(servos.FeedBack(id)!=-1){
		ServoInfo servo;
		servo.Pos = servos.ReadPos(-1);
		servo.Speed = servos.ReadSpeed(-1);
		servo.Load = servos.ReadLoad(-1);
		servo.Voltage = servos.ReadVoltage(-1);
		servo.Temper = servos.ReadTemper(-1);
		servo.Move = servos.ReadMove(-1);
		servo.Current = servos.ReadCurrent(-1);
		return servo;
	}
	Serial.println("GetInfo error");
	return {};
}


// ze strony 360 stopni = 4096 krokow
// https://www.waveshare.com/wiki/ST3215_Servo
// speed => kroki na skundę; 50 steps/sec≈0.732RPM; max = 3073

// trochę podejrzana stronka ale działa
// https://gitee.com/ftservo/FTServo_Linux/blob/main/examples/SMS_STS/SyncWritePos/SyncWritePos.cpp?utm_source=chatgpt.com
// acceleration => A=x*8.7deg/s^2 max = 150; im mniej tym wolniej
// A = 100 * (360/4096) = 8,7890625