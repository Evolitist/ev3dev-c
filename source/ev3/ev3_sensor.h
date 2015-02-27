
/*  ev3_sensor.h was generated by yup.py (yupp) 0.8b2
    out of ev3_sensor.yu-h at 2015-02-27 15:41
 *//**
 *  \file  ev3_sensor.h (ev3_sensor.yu-h)
 *  \brief  EV3 Sensors.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#ifndef EV3_SENSOR_H
#define EV3_SENSOR_H

#ifdef  EV3_SENSOR_IMPLEMENT
#define EV3_SENSOR_EXT
#define EV3_SENSOR_EXT_INIT( dec, init ) \
	dec = init
#else
#define EV3_SENSOR_EXT extern
#define EV3_SENSOR_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup ev3_sensor Sensors
 *  \brief Access to EV3 Sensors.
 *  \see http://www.ev3dev.org/docs/sensors/
 *  \see http://www.ev3dev.org/docs/drivers/lego-sensor-class/
 *  \{
 */

#define SENSOR_DIR  "/sys/class/lego-sensor"  /**< Directory of sensors. */

/**
 *  \brief Structure of a sensor descriptor.
 */
typedef struct {
	uint8_t type_inx;  /**< Sensor type. */
	uint8_t port;  /**< Sensor EV3 port. */
	uint8_t extport;  /**< Sensor extended port. */
	uint8_t addr;  /**< Sensor address. */

} EV3_SENSOR;

#define SENSOR_DESC__LIMIT_  64  /**< Limit of sensor descriptors. */

#define SENSOR__NONE_  SENSOR_DESC__LIMIT_  /**< Sensor is not found. */

/**
 *  \brief Vector of sensor descriptors (filled by \ref ev3_sensor_init).
 */
EV3_SENSOR_EXT EV3_SENSOR ev3_sensor[ SENSOR_DESC__LIMIT_ ];

/**
 *  \brief Identifiers of sensor types.
 */
enum {
	SENSOR_TYPE__NONE_ = 0,  /* XXX: memset( 0 ) is used */

	EV3_ANALOG_XX,
	NXT_ANALOG,
	HT_NXT_COLOR,
	HT_NXT_ANGLE,
	HT_NXT_ACCEL,
	HT_NXT_BAROMETRIC,
	HT_NXT_COLOR_V2,
	HT_NXT_EOPD,
	HT_NXT_FORCE,
	HT_NXT_GYRO,
	HT_NXT_IR_LINK,
	HT_NXT_IR_RECEIVER,
	HT_NXT_PIR,
	HT_NXT_COMPASS,
	HT_NXT_MAG,
	HT_NXT_IR_SEEK_V2,
	HT_NXT_SMUX,
	HT_SUPER_PRO,
	LEGO_EV3_UART_30,
	LEGO_EV3_UART_32,
	LEGO_EV3_UART_29,
	LEGO_EV3_TOUCH,
	LEGO_EV3_UART_33,
	WEDO_HUB,
	WEDO_MOTION,
	WEDO_TILT,
	LEGO_POWER_STORAGE,
	LEGO_NXT_TOUCH,
	LEGO_NXT_LIGHT,
	LEGO_NXT_SOUND,
	LEGO_NXT_US,
	MI_XG1300L,
	MS_ABSOLUTE_IMU,
	MS_ANGLE,
	MS_EV3_SMUX,
	MS_LIGHT_ARRAY,
	MS_LINE_LEADER,
	MS_8CH_SERVO,
	MS_NXT_TOUCH_MUX,

	SENSOR_TYPE__COUNT_,  /**< Count of sensor types. */
	SENSOR_TYPE__UNKNOWN_ = SENSOR_TYPE__COUNT_
};

/**
 *  \brief Identifiers of sensor modes.
 */
enum {
	SENSOR_MODE__NONE_ = 0,

	EV3_ANALOG_XX_ANALOG,

	NXT_ANALOG_ANALOG_0,
	NXT_ANALOG_ANALOG_1,

	HT_NXT_COLOR_COLOR,
	HT_NXT_COLOR_RED,
	HT_NXT_COLOR_GREEN,
	HT_NXT_COLOR_BLUE,
	HT_NXT_COLOR_RAW,
	HT_NXT_COLOR_NORM,
	HT_NXT_COLOR_ALL,

	HT_NXT_ANGLE_ANGLE,
	HT_NXT_ANGLE_ACCEL,
	HT_NXT_ANGLE_SPEED,

	HT_NXT_ACCEL_ACCEL,
	HT_NXT_ACCEL_ALL,

	HT_NXT_BAROMETRIC_PRESS,
	HT_NXT_BAROMETRIC_TEMP,

	HT_NXT_COLOR_V2_COLOR,
	HT_NXT_COLOR_V2_RED,
	HT_NXT_COLOR_V2_GREEN,
	HT_NXT_COLOR_V2_BLUE,
	HT_NXT_COLOR_V2_WHITE,
	HT_NXT_COLOR_V2_NORM,
	HT_NXT_COLOR_V2_ALL,
	HT_NXT_COLOR_V2_RAW,

	HT_NXT_EOPD_LONG,
	HT_NXT_EOPD_SHORT,

	HT_NXT_FORCE_FORCE,

	HT_NXT_GYRO_GYRO,

	HT_NXT_IR_LINK_IRLINK,

	HT_NXT_IR_RECEIVER_1_MOTOR,
	HT_NXT_IR_RECEIVER_8_MOTOR,

	HT_NXT_PIR_PROX,

	HT_NXT_COMPASS_COMPASS,

	HT_NXT_MAG_MAG,

	HT_NXT_IR_SEEK_V2_DC,
	HT_NXT_IR_SEEK_V2_AC,
	HT_NXT_IR_SEEK_V2_DC_ALL,
	HT_NXT_IR_SEEK_V2_AC_ALL,

	HT_NXT_SMUX_MUX,

	HT_SUPER_PRO_AIN,
	HT_SUPER_PRO_DIN,
	HT_SUPER_PRO_DOUT,
	HT_SUPER_PRO_DCTRL,
	HT_SUPER_PRO_STROBE,
	HT_SUPER_PRO_LED,
	HT_SUPER_PRO_AOUT_0,
	HT_SUPER_PRO_AOUT_1,

	LEGO_EV3_UART_30_US_DIST_CM,
	LEGO_EV3_UART_30_US_DIST_IN,
	LEGO_EV3_UART_30_US_LISTEN,
	LEGO_EV3_UART_30_US_SI_CM,
	LEGO_EV3_UART_30_US_SI_IN,
	LEGO_EV3_UART_30_US_DC_CM,
	LEGO_EV3_UART_30_US_DC_IN,

	LEGO_EV3_UART_32_GYRO_ANG,
	LEGO_EV3_UART_32_GYRO_RATE,
	LEGO_EV3_UART_32_GYRO_FAS,
	LEGO_EV3_UART_32_GYRO_G_AND_A,
	LEGO_EV3_UART_32_GYRO_CAL,

	LEGO_EV3_UART_29_COL_REFLECT,
	LEGO_EV3_UART_29_COL_AMBIENT,
	LEGO_EV3_UART_29_COL_COLOR,
	LEGO_EV3_UART_29_REF_RAW,
	LEGO_EV3_UART_29_RGB_RAW,
	LEGO_EV3_UART_29_COL_CAL,

	LEGO_EV3_TOUCH_TOUCH,

	LEGO_EV3_UART_33_IR_PROX,
	LEGO_EV3_UART_33_IR_SEEK,
	LEGO_EV3_UART_33_IR_REMOTE,
	LEGO_EV3_UART_33_IR_REM_A,
	LEGO_EV3_UART_33_IR_S_ALT,
	LEGO_EV3_UART_33_IR_CAL,

	WEDO_HUB_HUB,

	WEDO_MOTION_PROX,
	WEDO_MOTION_RAW,

	WEDO_TILT_TILT,
	WEDO_TILT_TILT_AXIS,
	WEDO_TILT_RAW,

	LEGO_POWER_STORAGE_IN_VOLT,
	LEGO_POWER_STORAGE_IN_AMP,
	LEGO_POWER_STORAGE_OUT_VOLT,
	LEGO_POWER_STORAGE_OUT_AMP,
	LEGO_POWER_STORAGE_JOULE,
	LEGO_POWER_STORAGE_IN_WATT,
	LEGO_POWER_STORAGE_OUT_WATT,
	LEGO_POWER_STORAGE_ALL,

	LEGO_NXT_TOUCH_TOUCH,

	LEGO_NXT_LIGHT_REFLECT,
	LEGO_NXT_LIGHT_AMBIENT,

	LEGO_NXT_SOUND_DB,
	LEGO_NXT_SOUND_DBA,

	LEGO_NXT_US_US_DIST_CM,
	LEGO_NXT_US_US_DIST_IN,
	LEGO_NXT_US_US_SI_CM,
	LEGO_NXT_US_US_SI_IN,
	LEGO_NXT_US_US_LISTEN,

	MI_XG1300L_ANGLE,
	MI_XG1300L_SPEED,
	MI_XG1300L_ACCEL,
	MI_XG1300L_ALL,

	MS_ABSOLUTE_IMU_TILT,
	MS_ABSOLUTE_IMU_ACCEL,
	MS_ABSOLUTE_IMU_COMPASS,
	MS_ABSOLUTE_IMU_MAG,
	MS_ABSOLUTE_IMU_GYRO,
	MS_ABSOLUTE_IMU_ALL,

	MS_ANGLE_ANGLE,
	MS_ANGLE_ANGLE2,
	MS_ANGLE_SPEED,
	MS_ANGLE_ALL,

	MS_EV3_SMUX_MUX,

	MS_LIGHT_ARRAY_CAL,
	MS_LIGHT_ARRAY_RAW,

	MS_LINE_LEADER_PID,
	MS_LINE_LEADER_PID_ALL,
	MS_LINE_LEADER_CAL,
	MS_LINE_LEADER_RAW,

	MS_8CH_SERVO_V3,
	MS_8CH_SERVO_OLD,

	MS_NXT_TOUCH_MUX_TOUCH_MUX,

	SENSOR_MODE__COUNT_,  /**< Count of sensor modes. */
	SENSOR_MODE__UNKNOWN_ = SENSOR_MODE__COUNT_
};

/**
 *  \brief Identifiers of sensor commands.
 */
enum {
	SENSOR_COMMAND__NONE_ = 0,

	HT_NXT_ANGLE_RESET,

	HT_NXT_SMUX_HALT,
	HT_NXT_SMUX_DETECT,
	HT_NXT_SMUX_RUN,

	WEDO_HUB_OUT_OFF,
	WEDO_HUB_OUT_ON,
	WEDO_HUB_CLEAR_ERR,

	MI_XG1300L_RESET,
	MI_XG1300L_ACCEL_2G,
	MI_XG1300L_ACCEL_4G,
	MI_XG1300L_ACCEL_8G,

	MS_ABSOLUTE_IMU_BEGIN_COMP_CAL,
	MS_ABSOLUTE_IMU_END_COMP_CAL,
	MS_ABSOLUTE_IMU_ACCEL_2G,
	MS_ABSOLUTE_IMU_ACCEL_4G,
	MS_ABSOLUTE_IMU_ACCEL_8G,
	MS_ABSOLUTE_IMU_ACCEL_16G,

	MS_ANGLE_RESET,

	MS_LIGHT_ARRAY_CAL_WHITE,
	MS_LIGHT_ARRAY_CAL_BLACK,
	MS_LIGHT_ARRAY_SLEEP,
	MS_LIGHT_ARRAY_WAKE,
	MS_LIGHT_ARRAY_60HZ,
	MS_LIGHT_ARRAY_50HZ,
	MS_LIGHT_ARRAY_UNIVERSAL,

	MS_LINE_LEADER_CAL_WHITE,
	MS_LINE_LEADER_CAL_BLACK,
	MS_LINE_LEADER_SLEEP,
	MS_LINE_LEADER_WAKE,
	MS_LINE_LEADER_INV_COL,
	MS_LINE_LEADER_RST_COL,
	MS_LINE_LEADER_SNAP,
	MS_LINE_LEADER_60HZ,
	MS_LINE_LEADER_50HZ,
	MS_LINE_LEADER_UNIVERSAL,

	SENSOR_COMMAND__COUNT_,  /**< Count of sensor commands. */
	SENSOR_COMMAND__UNKNOWN_ = SENSOR_COMMAND__COUNT_
};

/**
 *  \brief Get "address" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_address( uint8_t sn, byte *buf );

/**
 *  \brief Get "bin_data" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_bin_data( uint8_t sn, byte *buf, size_t sz );

/**
 *  \brief Set "bin_data" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
EV3_SENSOR_EXT size_t set_sensor_bin_data( uint8_t sn, byte *value, size_t sz );

/**
 *  \brief Get "bin_data_format" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_bin_data_format( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Set "command" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_SENSOR_EXT size_t set_sensor_command( uint8_t sn, char *value );

/**
 *  \brief Get "commands" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_commands( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Get "decimals" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_decimals( uint8_t sn, dword *buf );

/**
 *  \brief Get "driver_name" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_driver_name( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Get "fw_version" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_fw_version( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Get "mode" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_mode( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Set "mode" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_SENSOR_EXT size_t set_sensor_mode( uint8_t sn, char *value );

/**
 *  \brief Get "modes" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_modes( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Get "num_values" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_num_values( uint8_t sn, dword *buf );

/**
 *  \brief Get "poll_ms" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_poll_ms( uint8_t sn, dword *buf );

/**
 *  \brief Set "poll_ms" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_SENSOR_EXT size_t set_sensor_poll_ms( uint8_t sn, dword value );

/**
 *  \brief Get "port_name" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_port_name( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Get "units" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_units( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Get "value0" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value0( uint8_t sn, float *buf );

/**
 *  \brief Get "value1" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value1( uint8_t sn, float *buf );

/**
 *  \brief Get "value2" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value2( uint8_t sn, float *buf );

/**
 *  \brief Get "value3" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value3( uint8_t sn, float *buf );

/**
 *  \brief Get "value4" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value4( uint8_t sn, float *buf );

/**
 *  \brief Get "value5" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value5( uint8_t sn, float *buf );

/**
 *  \brief Get "value6" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value6( uint8_t sn, float *buf );

/**
 *  \brief Get "value7" attribute of the sensor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value7( uint8_t sn, float *buf );

/**
 *  \brief Get "value" attribute of the sensor.
 *  \param inx Attribute index.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
	 
 *  \return Count of read bytes.
 */
EV3_SENSOR_EXT size_t get_sensor_value( uint8_t inx, uint8_t sn, int *buf );

/**
 *  \brief Get name of the specified sensor type.
 *  \param type_inx Index of the sensor type.
 *  \return Requested value.
 */
EV3_SENSOR_EXT const char *ev3_sensor_type( uint8_t type_inx );

/**
 *  \brief Get index of the sensor type.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_SENSOR_EXT uint8_t get_sensor_type_inx( uint8_t sn );

/**
 *  \brief Get indexes of the EV3 port and the extended port of the sensor.
 *  \param sn Sequence number.
 *  \param port_type_inx Port type.
 *  \param extport Buffer for the extended port index.
 *  \return EV3 port index.
 */
EV3_SENSOR_EXT uint8_t get_sensor_port_inx( uint8_t sn, uint8_t port_type_inx, uint8_t *extport );

/**
 *  \brief Get descriptor of the sensor.
 *  \param sn Sequence number.
 *  \return Pointer to the sensor descriptor.
 */
EV3_SENSOR_EXT EV3_SENSOR *ev3_sensor_desc( uint8_t sn );

/**
 *  \brief Get type from the sensor descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_SENSOR_EXT uint8_t ev3_sensor_desc_type_inx( uint8_t sn );
/**
 *  \brief Get EV3 port from the sensor descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_SENSOR_EXT uint8_t ev3_sensor_desc_port( uint8_t sn );
/**
 *  \brief Get extended port from the sensor descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_SENSOR_EXT uint8_t ev3_sensor_desc_extport( uint8_t sn );
/**
 *  \brief Get address from the sensor descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_SENSOR_EXT uint8_t ev3_sensor_desc_addr( uint8_t sn );

/**
 *  \brief Search of a sequence number of the specified sensor type.
 *  \param type_inx The sensor type.
 *  \param[out] sn Buffer for the sequence number.
 *  \param from Search initial value.
 *  \return Flag - the sensor is found.
 */
EV3_SENSOR_EXT bool ev3_search_sensor( uint8_t type_inx, uint8_t *sn, uint8_t from );

/**
 *  \brief Search of a sequence number the sensor by plug-in attributes.
 *  \param port EV3 port.
 *  \param extport Extended port.
 *  \param addr Address.
 *  \param[out] sn Buffer for the sequence number.
 *  \param from Search initial value.
 *  \return Flag - the sensor is found.
 */
EV3_SENSOR_EXT bool ev3_search_sensor_plugged_in( uint8_t port, uint8_t extport, uint8_t addr, uint8_t *sn, uint8_t from );

/**
 *  \brief Get name of the specified sensor mode.
 *  \param mode_inx Index of the sensor mode.
 *  \return Requested value.
 */
EV3_SENSOR_EXT const char *ev3_sensor_mode( uint8_t mode_inx );

/**
 *  \brief Get index of the sensor mode.
 *  \param sn Sequence number.
 *  \param type_inx Index of the sensor type.
 *  \return Requested value.
 */
EV3_SENSOR_EXT uint8_t get_sensor_mode_inx( uint8_t sn, uint8_t type_inx );

/**
 *  \brief Set mode of the sensor by index.
 *  \param sn Sequence number.
 *  \param mode_inx Index of the sensor mode.
 *  \return Count of written bytes.
 */
EV3_SENSOR_EXT size_t set_sensor_mode_inx( uint8_t sn, uint8_t mode_inx );

/**
 *  \brief Get name of the specified sensor command.
 *  \param command_inx Index of the sensor command.
 *  \return Requested value.
 */
EV3_SENSOR_EXT const char *ev3_sensor_command( uint8_t command_inx );

/**
 *  \brief Set command of the sensor by index.
 *  \param sn Sequence number.
 *  \param command_inx Index of the sensor command.
 *  \return Count of written bytes.
 */
EV3_SENSOR_EXT size_t set_sensor_command_inx( uint8_t sn, uint8_t command_inx );

/**
 *  \brief Detect connected sensors.
 *  \return The number of found sensors or -1 in case of an error.
 */
EV3_SENSOR_EXT int ev3_sensor_init( void );

/** \} */

#ifdef __cplusplus
}
#endif

#endif

