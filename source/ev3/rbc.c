#include "rbc.h"

#include <stdlib.h>
#include <time.h>

bool checkBack = true;

task exitWatcher()
{
	uint8_t keys = 0;
	while(1)
	{
		if(checkBack)
		{
			ev3_read_keys(&keys);
			if(keys & 32)
			{
				exit(130);
			}
		}
	}
}

void init()
{
	ev3_sensor_init();
	ev3_tacho_init();
	uint8_t sn = 0;
	while(sn < TACHO_DESC__LIMIT_)
	{
		if(ev3_tacho[sn].port != 0)
		{
			set_tacho_stop_action_inx(sn, TACHO_BRAKE);
		}
		++sn;
	}
	ev3_tasks_init();
	ev3_display_init();
	startTask(exitWatcher);
}

void uninit()
{
	uint8_t sn = 0;
	while(sn < TACHO_DESC__LIMIT_)
	{
		if(ev3_tacho[sn].port != 0)
		{
			set_tacho_stop_action_inx(sn, TACHO_BRAKE);
			set_tacho_command_inx(sn, TACHO_STOP);
		}
		++sn;
	}
	ev3_display_uninit();
}

/* **** BUTTON **** */
int getButtonPress()
{
	uint8_t keys = 0;
	ev3_read_keys(&keys);
	return keys;
}

void waitForButtonPress()
{
	uint8_t keys = 0;
	while(!keys) ev3_read_keys(&keys);
}

void setBlockBackButton(bool block)
{
	checkBack = !block;
}

/* **** SCREEN **** */
void clearDisplay()
{
	display_clear();
}

void displayClearTextLine(uint8_t line)
{
	display_clear_text_line(line);
}

void setPixel(int x, int y)
{
	display_draw_pixel(x, y, true);
}

void clearPixel(int x, int y)
{
	display_draw_pixel(x, y, false);
}

void displayTextLine(uint8_t line, const char *format, ...)
{
	display_draw_text_line(line, format);
}

void displayCenteredTextLine(uint8_t line, const char *format, ...)
{
	display_draw_centered_text_line(line, format);
}

void displayString(uint8_t line, const char *format, ...)
{
	display_draw_string(line, format);
}

/* ****  MATH  **** */
double degreesToRadians(int d)
{
	return PI * (d) / 180.0;
}

int radiansToDegrees(double r)
{
	return (int)round(180.0 * (r) / PI);
}

/*double abs(double d)
{
	return fabs(d);
}*/

int8_t sgn(double d)
{
	return d < 0 ? -1 : 1;
}

double sinDegrees(int d)
{
	return sin(degreesToRadians(d));
}

double cosDegrees(int d)
{
	return cos(degreesToRadians(d));
}

/*double random(int a, int b)
{
	return a + (rand() % b);
}*/

/* **** MOTORS **** */
TBrakeModes getMotorBrakeMode(tMotor motor)
{
	uint8_t sn;
	if(ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		switch(get_tacho_stop_action_inx(sn))
		{
			case TACHO_COAST:
				return motorCoast;
			case TACHO_BRAKE:
				return motorBrake;
			case TACHO_HOLD:
				return motorHold;
		}
	}
	return 0;
}

int getMotorEncoder(tMotor motor)
{
	uint8_t sn;
	int val = 0;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		get_tacho_position(sn, &val);
	}
	return val;
}

float getMotorRPM(tMotor motor)
{
	uint8_t sn;
	int val = 0;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		get_tacho_speed(sn, &val);
	}
	return (float)val / (float)360;
}

bool getMotorRunning(tMotor motor)
{
	uint8_t sn;
	FLAGS_T flags = TACHO_STATE__NONE_;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		get_tacho_state_flags(sn, &flags);
	}
	return flags != TACHO_STATE__NONE_;
}

int getMotorTarget(tMotor motor)
{
	uint8_t sn;
	int val = 0;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		get_tacho_position_sp(sn, &val);
	}
	return val;
}

void moveMotorTarget(tMotor motor, int position, int8_t speed)
{
	uint8_t sn;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		set_tacho_position_sp(sn, sgn(speed) * position);
		set_tacho_speed_sp(sn, speed * 10);
		set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
	}
}

void resetMotorEncoder(tMotor motor)
{
	uint8_t sn;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		set_tacho_position(sn, 0);
	}
}

void setMotorBrakeMode(tMotor motor, TBrakeModes brakeMode)
{
	uint8_t sn;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		set_tacho_stop_action_inx(sn, brakeMode);
	}
}

void setMotorReversed(tMotor motor, bool rev)
{
	uint8_t sn;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		set_tacho_polarity_inx(sn, rev ? TACHO_INVERSED : TACHO_NORMAL);
	}
}

void setMotorSpeed(tMotor motor, int8_t speed)
{
	uint8_t sn;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		set_tacho_speed_sp(sn, speed * 10);
		set_tacho_command_inx(sn, TACHO_RUN_FOREVER);
	}
}

void setMotorSync(tMotor motor1, tMotor motor2, int8_t turnRatio, int8_t speed)
{
	uint8_t sn[3] = { DESC_LIMIT, DESC_LIMIT, DESC_LIMIT };
	if (ev3_search_tacho_plugged_in(motor1, EXT_PORT__NONE_, &sn[0], 0) && ev3_search_tacho_plugged_in(motor2, EXT_PORT__NONE_, &sn[1], 0))
	{
		int speed1 = speed * 10, speed2 = speed * 10;
		if(turnRatio < 0) speed1 -= speed1 * abs(turnRatio) / 50;
		if(turnRatio > 0) speed2 -= speed2 * abs(turnRatio) / 50;
		set_tacho_speed_sp(sn[0], speed1);
		set_tacho_speed_sp(sn[1], speed2);
		multi_set_tacho_command_inx(sn, TACHO_RUN_FOREVER);
	}
}

void setMotorSyncEncoder(tMotor motor1, tMotor motor2, int8_t turnRatio, int enc, int8_t speed)
{
	uint8_t sn[3] = { DESC_LIMIT, DESC_LIMIT, DESC_LIMIT };
	if (ev3_search_tacho_plugged_in(motor1, EXT_PORT__NONE_, &sn[0], 0) && ev3_search_tacho_plugged_in(motor2, EXT_PORT__NONE_, &sn[1], 0))
	{
		int speed1 = speed * 10, speed2 = speed * 10;
		if(turnRatio < 0) speed1 -= speed1 * abs(turnRatio) / 50;
		if(turnRatio > 0) speed2 -= speed2 * abs(turnRatio) / 50;
		set_tacho_speed_sp(sn[0], speed1);
		set_tacho_speed_sp(sn[1], speed2);
		set_tacho_position_sp(sn[0], enc);
		set_tacho_position_sp(sn[1], enc * speed2 / speed1);
		multi_set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
	}
}

void setMotorSyncTime(tMotor motor1, tMotor motor2, int8_t turnRatio, int time_ms, int8_t speed)
{
	uint8_t sn[3] = { DESC_LIMIT, DESC_LIMIT, DESC_LIMIT };
	if (ev3_search_tacho_plugged_in(motor1, EXT_PORT__NONE_, &sn[0], 0) && ev3_search_tacho_plugged_in(motor2, EXT_PORT__NONE_, &sn[1], 0))
	{
		int speed1 = speed * 10, speed2 = speed * 10;
		if(turnRatio < 0) speed1 -= speed1 * abs(turnRatio) / 50;
		if(turnRatio > 0) speed2 -= speed2 * abs(turnRatio) / 50;
		set_tacho_speed_sp(sn[0], speed1);
		set_tacho_speed_sp(sn[1], speed2);
		multi_set_tacho_time_sp(sn, time_ms);
		multi_set_tacho_command_inx(sn, TACHO_RUN_TIMED);
	}
}

void setMotorTarget(tMotor motor, int position, int8_t speed)
{
	uint8_t sn;
	if (ev3_search_tacho_plugged_in(motor, EXT_PORT__NONE_, &sn, 0))
	{
		set_tacho_position_sp(sn, position);
		set_tacho_speed_sp(sn, speed * 10);
		set_tacho_command_inx(sn, TACHO_RUN_TO_ABS_POS);
	}
}

/* **** SENSOR **** */
/* ---- SYSTEM ---- */


/* ----  USER  ---- */
tSensor findSensor(INX_T type)
{
	uint8_t sn = 0;
	ev3_search_sensor(type, &sn, sn);
	switch(ev3_sensor[sn].port)
	{
		case INPUT_1: return S1;
		case INPUT_2: return S2;
		case INPUT_3: return S3;
		case INPUT_4: return S4;
	}
	return 0;
}	

int getSensorValue(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0))
	{
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getColorAmbient(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_COLOR) != LEGO_EV3_COLOR_COL_AMBIENT)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_COLOR_COL_AMBIENT);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getColorName(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_COLOR) != LEGO_EV3_COLOR_COL_COLOR)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_COLOR_COL_COLOR);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getColorReflected(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_COLOR) != LEGO_EV3_COLOR_COL_REFLECT)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_COLOR_COL_REFLECT);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getColorRed(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_COLOR) != LEGO_EV3_COLOR_RGB_RAW)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_COLOR_RGB_RAW);
		}
		get_sensor_value0(sn, &val);
		val = val * 255 / 1023;
	}
	return (int)round(val);
}

int getColorGreen(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_COLOR) != LEGO_EV3_COLOR_RGB_RAW)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_COLOR_RGB_RAW);
		}
		get_sensor_value1(sn, &val);
		val = val * 255 / 1023;
	}
	return (int)round(val);
}

int getColorBlue(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_COLOR) != LEGO_EV3_COLOR_RGB_RAW)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_COLOR_RGB_RAW);
		}
		get_sensor_value2(sn, &val);
		val = val * 255 / 1023;
	}
	return (int)round(val);
}

void getColorRGB(tSensor sensor, int *red, int *green, int *blue)
{
	uint8_t sn;
	float r = 0, g = 0, b = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_COLOR) != LEGO_EV3_COLOR_RGB_RAW)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_COLOR_RGB_RAW);
		}
		get_sensor_value0(sn, &r);
		get_sensor_value1(sn, &g);
		get_sensor_value2(sn, &b);
		*red = (int)round(r * 255 / 1023);
		*green = (int)round(g * 255 / 1023);
		*blue = (int)round(b * 255 / 1023);
	}
}

float getUSDistance(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_US)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_US) != LEGO_EV3_US_US_DIST_CM)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_US_US_DIST_CM);
		}
		get_sensor_value0(sn, &val);
		val /= 10;
	}
	return val;
}

int getGyroHeading(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_GYRO)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_GYRO) != LEGO_EV3_GYRO_GYRO_ANG && get_sensor_mode_inx_of_type(sn, LEGO_EV3_GYRO) != LEGO_EV3_GYRO_GYRO_G_AND_A)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_GYRO_GYRO_G_AND_A);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getGyroRate(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_GYRO)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_GYRO) != LEGO_EV3_GYRO_GYRO_RATE && get_sensor_mode_inx_of_type(sn, LEGO_EV3_GYRO) != LEGO_EV3_GYRO_GYRO_G_AND_A)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_GYRO_GYRO_G_AND_A);
		}
		get_sensor_value1(sn, &val);
	}
	return (int)round(val);
}

void resetGyro(tSensor sensor)
{
	uint8_t sn;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_GYRO)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_GYRO) == LEGO_EV3_GYRO_GYRO_ANG && get_sensor_mode_inx_of_type(sn, LEGO_EV3_GYRO) == LEGO_EV3_GYRO_GYRO_G_AND_A)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_GYRO_GYRO_RATE);
			set_sensor_mode_inx(sn, LEGO_EV3_GYRO_GYRO_G_AND_A);
		}
	}
}

int getIRDistance(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_IR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_IR) != LEGO_EV3_IR_IR_PROX)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_IR_IR_PROX);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getIRBeaconDirection(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_IR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_IR) != LEGO_EV3_IR_IR_SEEK)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_IR_IR_SEEK);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getIRBeaconChannelDirection(tSensor sensor, uint8_t channel)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_IR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_IR) != LEGO_EV3_IR_IR_SEEK)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_IR_IR_SEEK);
		}
		switch(channel)
		{
			case 1: get_sensor_value0(sn, &val); break;
			case 2: get_sensor_value2(sn, &val); break;
			case 3: get_sensor_value4(sn, &val); break;
			case 4: get_sensor_value6(sn, &val); break;
		}
	}
	return (int)round(val);
}

int getIRBeaconStrength(tSensor sensor)
{
	uint8_t sn;
	float val = -128;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_IR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_IR) != LEGO_EV3_IR_IR_SEEK)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_IR_IR_SEEK);
		}
		get_sensor_value1(sn, &val);
	}
	return (int)round(val);
}

int getIRBeaconChannelStrength(tSensor sensor, uint8_t channel)
{
	uint8_t sn;
	float val = -128;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_IR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_IR) != LEGO_EV3_IR_IR_SEEK)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_IR_IR_SEEK);
		}
		switch(channel)
		{
			case 1: get_sensor_value1(sn, &val); break;
			case 2: get_sensor_value3(sn, &val); break;
			case 3: get_sensor_value5(sn, &val); break;
			case 4: get_sensor_value7(sn, &val); break;
		}
	}
	return (int)round(val);
}

int getIRRemoteButtons(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_IR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_IR) != LEGO_EV3_IR_IR_REMOTE)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_IR_IR_REMOTE);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getIRRemoteChannelButtons(tSensor sensor, uint8_t channel)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_IR)
	{
		if(get_sensor_mode_inx_of_type(sn, LEGO_EV3_IR) != LEGO_EV3_IR_IR_REMOTE)
		{
			set_sensor_mode_inx(sn, LEGO_EV3_IR_IR_REMOTE);
		}
		switch(channel)
		{
			case 1: get_sensor_value0(sn, &val); break;
			case 2: get_sensor_value1(sn, &val); break;
			case 3: get_sensor_value2(sn, &val); break;
			case 4: get_sensor_value3(sn, &val); break;
		}
	}
	return (int)round(val);
}

int getTouchValue(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == LEGO_EV3_TOUCH)
	{
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getIRSACDirection(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_IR_SEEK_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_IR_SEEK_V2) != HT_NXT_IR_SEEK_V2_AC && get_sensor_mode_inx_of_type(sn, HT_NXT_IR_SEEK_V2) != HT_NXT_IR_SEEK_V2_AC_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_IR_SEEK_V2_AC_ALL);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

void getIRSACStrength(tSensor sensor, int *d1, int *d2, int *d3, int *d4, int *d5)
{
	uint8_t sn;
	float s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_IR_SEEK_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_IR_SEEK_V2) != HT_NXT_IR_SEEK_V2_AC_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_IR_SEEK_V2_AC_ALL);
		}
		get_sensor_value1(sn, &s1);
		get_sensor_value2(sn, &s2);
		get_sensor_value3(sn, &s3);
		get_sensor_value4(sn, &s4);
		get_sensor_value5(sn, &s5);
		*d1 = (int)round(s1);
		*d2 = (int)round(s2);
		*d3 = (int)round(s3);
		*d4 = (int)round(s4);
		*d5 = (int)round(s5);
	}
}

int getIRSDCDirection(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_IR_SEEK_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_IR_SEEK_V2) != HT_NXT_IR_SEEK_V2_DC && get_sensor_mode_inx_of_type(sn, HT_NXT_IR_SEEK_V2) != HT_NXT_IR_SEEK_V2_DC_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_IR_SEEK_V2_DC_ALL);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

void getIRSDCStrength(tSensor sensor, int *d1, int *d2, int *d3, int *d4, int *d5)
{
	uint8_t sn;
	float s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_IR_SEEK_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_IR_SEEK_V2) != HT_NXT_IR_SEEK_V2_DC_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_IR_SEEK_V2_DC_ALL);
		}
		get_sensor_value1(sn, &s1);
		get_sensor_value2(sn, &s2);
		get_sensor_value3(sn, &s3);
		get_sensor_value4(sn, &s4);
		get_sensor_value5(sn, &s5);
		*d1 = (int)round(s1);
		*d2 = (int)round(s2);
		*d3 = (int)round(s3);
		*d4 = (int)round(s4);
		*d5 = (int)round(s5);
	}
}

int getHTColorName(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR) != HT_NXT_COLOR_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_ALL);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getHTColorRed(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR) != HT_NXT_COLOR_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_ALL);
		}
		get_sensor_value1(sn, &val);
	}
	return (int)round(val);
}

int getHTColorGreen(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR) != HT_NXT_COLOR_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_ALL);
		}
		get_sensor_value2(sn, &val);
	}
	return (int)round(val);
}

int getHTColorBlue(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR) != HT_NXT_COLOR_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_ALL);
		}
		get_sensor_value3(sn, &val);
	}
	return (int)round(val);
}

void getHTColorRGB(tSensor sensor, int *red, int *green, int *blue)
{
	uint8_t sn;
	float r = 0, g = 0, b = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR) != HT_NXT_COLOR_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_ALL);
		}
		get_sensor_value1(sn, &r);
		get_sensor_value2(sn, &g);
		get_sensor_value3(sn, &b);
		*red = (int)round(r);
		*green = (int)round(g);
		*blue = (int)round(b);
	}
}

int getHTColor2Name(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR_V2) != HT_NXT_COLOR_V2_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_V2_ALL);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getHTColor2Red(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR_V2) != HT_NXT_COLOR_V2_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_V2_ALL);
		}
		get_sensor_value1(sn, &val);
	}
	return (int)round(val);
}

int getHTColor2Green(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR_V2) != HT_NXT_COLOR_V2_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_V2_ALL);
		}
		get_sensor_value2(sn, &val);
	}
	return (int)round(val);
}

int getHTColor2Blue(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR_V2) != HT_NXT_COLOR_V2_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_V2_ALL);
		}
		get_sensor_value3(sn, &val);
	}
	return (int)round(val);
}

void getHTColor2RGB(tSensor sensor, int *red, int *green, int *blue)
{
	uint8_t sn;
	float r = 0, g = 0, b = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COLOR_V2)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_COLOR_V2) != HT_NXT_COLOR_V2_ALL)
		{
			set_sensor_mode_inx(sn, HT_NXT_COLOR_V2_ALL);
		}
		get_sensor_value1(sn, &r);
		get_sensor_value2(sn, &g);
		get_sensor_value3(sn, &b);
		*red = (int)round(r);
		*green = (int)round(g);
		*blue = (int)round(b);
	}
}

int getHTAngle(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_ANGLE)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_ANGLE) != HT_NXT_ANGLE_ANGLE)
		{
			set_sensor_mode_inx(sn, HT_NXT_ANGLE_ANGLE);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getHTAngleAccumulated(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_ANGLE)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_ANGLE) != HT_NXT_ANGLE_ANGLE_ACC)
		{
			set_sensor_mode_inx(sn, HT_NXT_ANGLE_ANGLE_ACC);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

int getHTAngleSpeed(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_ANGLE)
	{
		if(get_sensor_mode_inx_of_type(sn, HT_NXT_ANGLE) != HT_NXT_ANGLE_SPEED)
		{
			set_sensor_mode_inx(sn, HT_NXT_ANGLE_SPEED);
		}
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

void resetHTAngle(tSensor sensor)
{
	uint8_t sn;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_ANGLE)
	{
		set_sensor_command_inx(sn, HT_NXT_ANGLE_RESET);
	}
}

int getHTCompassHeading(tSensor sensor)
{
	uint8_t sn;
	float val = 0;
	if (ev3_search_sensor_plugged_in(sensor, EXT_PORT__NONE_, &sn, 0) && ev3_sensor[sn].type_inx == HT_NXT_COMPASS)
	{
		get_sensor_value0(sn, &val);
	}
	return (int)round(val);
}

/* ****  SOUND **** */
void playTone(int freq, int timeMs)
{
	speaker_play_tone(freq, timeMs);
}

void playImmediateTone(int freq, int timeMs)
{
	speaker_play_tone(freq, timeMs);
}

void setSoundVolume(int vol)
{
	speaker_set_volume(vol);
}

int getSoundVolume()
{
	return speaker_get_volume();
}

/* ****  TASKS **** */
void abortTimeslice()
{
	task_yield();
}

void stopAllTasks()
{
	task_stop_all();
}

void startTask(task (*task_func)(void*))
{
	task_start(task_func);
}

void stopTask(task (*task_func)(void*))
{
	task_stop(task_func);
}

/* **** TIMING **** */
void delay(unsigned long int ms)
{
	if(ms == 0) return;
	struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void delay_us(unsigned long int us)
{
	if(us == 0) return;
	struct timespec ts;
    ts.tv_sec = us / 1000000;
    ts.tv_nsec = (us % 1000000) * 1000;
    nanosleep(&ts, NULL);
}

void delay_ns(unsigned long int ns)
{
	if(ns == 0) return;
	struct timespec ts;
	ts.tv_sec = 0;
    ts.tv_nsec = ns;
    nanosleep(&ts, NULL);
}
