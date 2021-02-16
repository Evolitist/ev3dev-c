#ifndef RBC_H
#define RBC_H

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"
#include "ev3_display.h"
#include "ev3_tasks.h"
#include "ev3_speaker.h"

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	buttonNone = 0,
	buttonUp = EV3_KEY_UP,
	buttonDown = EV3_KEY_DOWN,
	buttonLeft = EV3_KEY_LEFT,
	buttonRight = EV3_KEY_RIGHT,
	buttonEnter = EV3_KEY_CENTER,
	buttonAny = EV3_KEY_UP | EV3_KEY_DOWN | EV3_KEY_LEFT | EV3_KEY_RIGHT | EV3_KEY_CENTER,
} tButton;

typedef enum {
	motorA = (uint8_t)0x1UL,
	motorB = (uint8_t)0x2UL,
	motorC = (uint8_t)0x4UL,
	motorD = (uint8_t)0x8UL,
} tMotor;

typedef enum {
	S1 = INPUT_1,
	S2 = INPUT_2,
	S3 = INPUT_3,
	S4 = INPUT_4,
} tSensor;

typedef enum TBrakeModes {
	motorCoast = TACHO_COAST,
	motorBrake = TACHO_BRAKE,
	motorHold = TACHO_HOLD,
} TBrakeModes;

typedef enum {
	DEBUG,
	INFO,
	WARN,
	ERROR,
} tLogType;

void init() __attribute__((constructor));
void uninit() __attribute__((destructor));
int getButtonPress(tButton button);

/*
 * Display
 */
void clearDisplay();
void displayClearTextLine(uint8_t line);
void setPixel(int x, int y);
void clearPixel(int x, int y);
void displayTextLine(uint8_t line, const char *format, ...) __attribute__((format (printf, 2, 3)));
void displayCenteredTextLine(uint8_t line, const char *format, ...) __attribute__((format (printf, 2, 3)));
void displayString(uint8_t line, const char *format, ...) __attribute__((format (printf, 2, 3)));

/*
 * Math
 */
#ifndef PI
	#define PI 3.14159265358979323846
#endif

double degreesToRadians(int d);
int radiansToDegrees(double r);
//double abs(double d);
int8_t sgn(double d);
double sinDegrees(int d);
double cosDegrees(int d);
//double random(int a, int b);

/*
 * Motors
 */
TBrakeModes getMotorBrakeMode(tMotor motor);
int getMotorEncoder(tMotor motor);
float getMotorEncoderAverage(tMotor motors);
float getMotorRPM(tMotor motor);
bool getMotorRunning(tMotor motors);
int getMotorTarget(tMotor motor);
void moveMotorTarget(tMotor motors, int position, int8_t speed);
void resetMotorEncoder(tMotor motors);
void setMotorBrakeMode(tMotor motors, TBrakeModes brakeMode);
void setMotorReversed(tMotor motors, bool rev);
void setMotorSpeed(tMotor motors, int8_t speed);
void setMotorSync(tMotor motors, int8_t turnRatio, int8_t speed);
void setMotorSyncEncoder(tMotor motors, int8_t turnRatio, int enc, int8_t speed);
void setMotorSyncTime(tMotor motors, int8_t turnRatio, int time_ms, int8_t speed);
void setMotorTarget(tMotor motors, int position, int8_t speed);
int getMotorPreciseEncoder(tMotor motor);
int getMotorPreciseSpeed(tMotor motor);



/*
 * Sensors
 */
 
/**
 * \brief Find sensor of specified type
 * \param type Sensor type
 * \return Port of sensor, or 0 if not found
 */
tSensor findSensor(INX_T type);

/**
 * \brief Get value of generic sensor
 * \param sensor Sensor port
 * \return Sensor value, or 0 if any error
 */
int getSensorValue(tSensor sensor);
// EV3 Color
int getColorAmbient(tSensor sensor);
int getColorName(tSensor sensor);
int getColorReflected(tSensor sensor);
int getColorRed(tSensor sensor);
int getColorGreen(tSensor sensor);
int getColorBlue(tSensor sensor);
void getColorRGB(tSensor sensor, int *red, int *green, int *blue);
// EV3 Ultrasonic
float getUSDistance(tSensor sensor);
// EV3 Gyro
int getGyroHeading(tSensor sensor);
int getGyroRate(tSensor sensor);
void resetGyro(tSensor sensor);
// EV3 Infrared
int getIRDistance(tSensor sensor);
int getIRBeaconDirection(tSensor sensor);
int getIRBeaconChannelDirection(tSensor sensor, uint8_t channel);
int getIRBeaconStrength(tSensor sensor);
int getIRBeaconChannelStrength(tSensor sensor, uint8_t channel);
int getIRRemoteButtons(tSensor sensor);
int getIRRemoteChannelButtons(tSensor sensor, uint8_t channel);
// Touch
int getTouchValue(tSensor sensor);
// HT IR Seeker V2
int getIRSACDirection(tSensor sensor);
void getIRSACStrength(tSensor sensor, int *d1, int *d2, int *d3, int *d4, int *d5);
int getIRSDCDirection(tSensor sensor);
void getIRSDCStrength(tSensor sensor, int *d1, int *d2, int *d3, int *d4, int *d5);
// HT Color
int getHTColorName(tSensor sensor);
int getHTColorRed(tSensor sensor);
int getHTColorGreen(tSensor sensor);
int getHTColorBlue(tSensor sensor);
void getHTColorRGB(tSensor sensor, int *red, int *green, int *blue);
// HT Color V2
int getHTColor2Name(tSensor sensor);
int getHTColor2Red(tSensor sensor);
int getHTColor2Green(tSensor sensor);
int getHTColor2Blue(tSensor sensor);
void getHTColor2RGB(tSensor sensor, int *red, int *green, int *blue);
// HT Angle
int getHTAngle(tSensor sensor);
int getHTAngleAccumulated(tSensor sensor);
int getHTAngleSpeed(tSensor sensor);
void resetHTAngle(tSensor sensor);
// HT Compass
int getHTCompassHeading(tSensor sensor);

/*
 * Sound
 */
void playTone(int freq, int timeMs);
void playImmediateTone(int freq, int timeMs);
void setSoundVolume(int vol);
int getSoundVolume();

/*
 * Task Control
 */
void abortTimeslice();
void stopAllTasks();
void startTask(task (*task_func)(void*));
void stopTask(task (*task_func)(void*));

/*
 * Timing
 */
void delay(unsigned long int ms);
void delay_us(unsigned long int us);
void delay_ns(unsigned long int ns);
double sysTime();

/*
 * Logging
 */
void print(tLogType type, const char *__str, ...) __attribute__((format (printf, 2, 3)));
void println(tLogType type, const char *__str, ...) __attribute__((format (printf, 2, 3)));

#ifdef __cplusplus
}
#endif

#endif

