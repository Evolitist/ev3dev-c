
/*  ev3_tacho.c was generated by yup.py (yupp) 0.8b2
    out of ev3_tacho.yu-c at 2015-02-27 15:43
 *//**
 *  \file  ev3_tacho.c (ev3_tacho.yu-c)
 *  \brief  EV3 Tacho Motors.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define EV3_TACHO_IMPLEMENT

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "modp_numtoa.h"
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"

#define PATH_PREF_LEN  28
#define _ID_SPOT  "///"

#define PATH_DUTY_CYCLE  "/sys/class/tacho-motor/motor" _ID_SPOT "duty_cycle"
#define PATH_DUTY_CYCLE_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "duty_cycle_sp"
#define PATH_ENCODER_MODE  "/sys/class/tacho-motor/motor" _ID_SPOT "encoder_mode"
#define PATH_ENCODER_MODES  "/sys/class/tacho-motor/motor" _ID_SPOT "encoder_modes"
#define PATH_ESTOP  "/sys/class/tacho-motor/motor" _ID_SPOT "estop"
#define PATH_LOG  "/sys/class/tacho-motor/motor" _ID_SPOT "log"
#define PATH_POLARITY_MODE  "/sys/class/tacho-motor/motor" _ID_SPOT "polarity_mode"
#define PATH_POLARITY_MODES  "/sys/class/tacho-motor/motor" _ID_SPOT "polarity_modes"
#define PATH_PORT_NAME  "/sys/class/tacho-motor/motor" _ID_SPOT "port_name"
#define PATH_POSITION  "/sys/class/tacho-motor/motor" _ID_SPOT "position"
#define PATH_POSITION_MODE  "/sys/class/tacho-motor/motor" _ID_SPOT "position_mode"
#define PATH_POSITION_MODES  "/sys/class/tacho-motor/motor" _ID_SPOT "position_modes"
#define PATH_POSITION_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "position_sp"
#define PATH_PULSES_PER_SECOND  "/sys/class/tacho-motor/motor" _ID_SPOT "pulses_per_second"
#define PATH_PULSES_PER_SECOND_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "pulses_per_second_sp"
#define PATH_RAMP_DOWN_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "ramp_down_sp"
#define PATH_RAMP_UP_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "ramp_up_sp"
#define PATH_REGULATION_MODE  "/sys/class/tacho-motor/motor" _ID_SPOT "regulation_mode"
#define PATH_REGULATION_MODES  "/sys/class/tacho-motor/motor" _ID_SPOT "regulation_modes"
#define PATH_RESET  "/sys/class/tacho-motor/motor" _ID_SPOT "reset"
#define PATH_RUN  "/sys/class/tacho-motor/motor" _ID_SPOT "run"
#define PATH_RUN_MODE  "/sys/class/tacho-motor/motor" _ID_SPOT "run_mode"
#define PATH_RUN_MODES  "/sys/class/tacho-motor/motor" _ID_SPOT "run_modes"
#define PATH_SPEED_REGULATION_D  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_regulation_D"
#define PATH_SPEED_REGULATION_I  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_regulation_I"
#define PATH_SPEED_REGULATION_K  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_regulation_K"
#define PATH_SPEED_REGULATION_P  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_regulation_P"
#define PATH_STATE  "/sys/class/tacho-motor/motor" _ID_SPOT "state"
#define PATH_STOP_MODE  "/sys/class/tacho-motor/motor" _ID_SPOT "stop_mode"
#define PATH_STOP_MODES  "/sys/class/tacho-motor/motor" _ID_SPOT "stop_modes"
#define PATH_TIME_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "time_sp"
#define PATH_TYPE  "/sys/class/tacho-motor/motor" _ID_SPOT "type"

size_t get_tacho_duty_cycle( uint8_t sn, int *buf )
{
	char s[] = PATH_DUTY_CYCLE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t get_tacho_duty_cycle_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_DUTY_CYCLE_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_duty_cycle_sp( uint8_t sn, int value )
{
	char s[] = PATH_DUTY_CYCLE_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_encoder_mode( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_ENCODER_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_encoder_mode( uint8_t sn, char *value )
{
	char s[] = PATH_ENCODER_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_encoder_modes( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_ENCODER_MODES;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_estop( uint8_t sn, int *buf )
{
	char s[] = PATH_ESTOP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_estop( uint8_t sn, int value )
{
	char s[] = PATH_ESTOP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_log( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_LOG;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_polarity_mode( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_POLARITY_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_polarity_mode( uint8_t sn, char *value )
{
	char s[] = PATH_POLARITY_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_polarity_modes( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_POLARITY_MODES;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_port_name( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_PORT_NAME;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_position( uint8_t sn, int *buf )
{
	char s[] = PATH_POSITION;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_position( uint8_t sn, int value )
{
	char s[] = PATH_POSITION;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_position_mode( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_POSITION_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_position_mode( uint8_t sn, char *value )
{
	char s[] = PATH_POSITION_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_position_modes( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_POSITION_MODES;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_position_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_POSITION_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_position_sp( uint8_t sn, int value )
{
	char s[] = PATH_POSITION_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_pulses_per_second( uint8_t sn, int *buf )
{
	char s[] = PATH_PULSES_PER_SECOND;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t get_tacho_pulses_per_second_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_PULSES_PER_SECOND_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_pulses_per_second_sp( uint8_t sn, int value )
{
	char s[] = PATH_PULSES_PER_SECOND_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_ramp_down_sp( uint8_t sn, dword *buf )
{
	char s[] = PATH_RAMP_DOWN_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_dword( s, buf );
}

size_t set_tacho_ramp_down_sp( uint8_t sn, dword value )
{
	char s[] = PATH_RAMP_DOWN_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_dword( s, value );
}

size_t get_tacho_ramp_up_sp( uint8_t sn, dword *buf )
{
	char s[] = PATH_RAMP_UP_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_dword( s, buf );
}

size_t set_tacho_ramp_up_sp( uint8_t sn, dword value )
{
	char s[] = PATH_RAMP_UP_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_dword( s, value );
}

size_t get_tacho_regulation_mode( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_REGULATION_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_regulation_mode( uint8_t sn, char *value )
{
	char s[] = PATH_REGULATION_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_regulation_modes( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_REGULATION_MODES;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_regulation_modes( uint8_t sn, char *value )
{
	char s[] = PATH_REGULATION_MODES;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t set_tacho_reset( uint8_t sn, bool value )
{
	char s[] = PATH_RESET;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_bool( s, value );
}

size_t get_tacho_run( uint8_t sn, bool *buf )
{
	char s[] = PATH_RUN;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_bool( s, buf );
}

size_t set_tacho_run( uint8_t sn, bool value )
{
	char s[] = PATH_RUN;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_bool( s, value );
}

size_t get_tacho_run_mode( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_RUN_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_run_mode( uint8_t sn, char *value )
{
	char s[] = PATH_RUN_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_run_modes( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_RUN_MODES;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_speed_regulation_D( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED_REGULATION_D;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_speed_regulation_D( uint8_t sn, int value )
{
	char s[] = PATH_SPEED_REGULATION_D;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_speed_regulation_I( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED_REGULATION_I;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_speed_regulation_I( uint8_t sn, int value )
{
	char s[] = PATH_SPEED_REGULATION_I;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_speed_regulation_K( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED_REGULATION_K;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_speed_regulation_K( uint8_t sn, int value )
{
	char s[] = PATH_SPEED_REGULATION_K;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_speed_regulation_P( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED_REGULATION_P;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_speed_regulation_P( uint8_t sn, int value )
{
	char s[] = PATH_SPEED_REGULATION_P;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_state( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_STATE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_stop_mode( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_STOP_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_stop_mode( uint8_t sn, char *value )
{
	char s[] = PATH_STOP_MODE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_stop_modes( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_STOP_MODES;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_time_sp( uint8_t sn, dword *buf )
{
	char s[] = PATH_TIME_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_dword( s, buf );
}

size_t set_tacho_time_sp( uint8_t sn, dword value )
{
	char s[] = PATH_TIME_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_dword( s, value );
}

size_t get_tacho_type( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_TYPE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

const char *ev3_tacho_type( uint8_t type_inx )
{
	switch ( type_inx ) {
	case TACHO:
		return "tacho";
	case MINITACHO:
		return "minitacho";

	}
	return ( STR_unknown_ );
}

uint8_t get_tacho_type_inx( uint8_t sn )
{
	char buf[ 64 ];

	if ( !get_tacho_type( sn, buf, sizeof( buf ))) return ( TACHO_TYPE__NONE_ );

	if ( strcmp( buf, "tacho" ) == 0 ) return TACHO;
	if ( strcmp( buf, "minitacho" ) == 0 ) return MINITACHO;

	return ( TACHO_TYPE__UNKNOWN_ );
}

uint8_t get_tacho_port_inx( uint8_t sn, uint8_t port_type_inx, uint8_t *extport )
{
	char buf[ 32 ];

	if ( !get_tacho_port_name( sn, buf, sizeof( buf ))) return ( EV3_PORT__NONE_ );

	return ( ev3_port_inx( port_type_inx, buf, extport ));
}

EV3_TACHO *ev3_tacho_desc( uint8_t sn )
{
	if ( sn >= TACHO_DESC__LIMIT_) sn = TACHO_DESC__LIMIT_ - 1;
	return ( ev3_tacho + sn );
}

uint8_t ev3_tacho_desc_type_inx( uint8_t sn )
{
	return ( ev3_tacho_desc( sn )->type_inx );
}

uint8_t ev3_tacho_desc_port( uint8_t sn )
{
	return ( ev3_tacho_desc( sn )->port );
}

uint8_t ev3_tacho_desc_extport( uint8_t sn )
{
	return ( ev3_tacho_desc( sn )->extport );
}

bool ev3_search_tacho( uint8_t type_inx, uint8_t *sn, uint8_t from )
{
	uint8_t _sn = from;

	while ( _sn < TACHO_DESC__LIMIT_) {
		if ( ev3_tacho[ _sn ].type_inx == type_inx ) {
			*sn = _sn;
			return ( true );
		}
		++_sn;
	}
	*sn = TACHO__NONE_;
	return ( false );
}

bool ev3_search_tacho_plugged_in( uint8_t port, uint8_t extport, uint8_t *sn, uint8_t from )
{
	uint8_t _sn = from;

	while ( _sn < TACHO_DESC__LIMIT_) {
		if ( ev3_tacho[ _sn ].port == port ) {
			
			if ( extport ) {
				if ( ev3_tacho[ _sn ].extport == extport ) {
						*sn = _sn;
						return ( true );
					}
			}
			else {
				*sn = _sn;
				return ( true );
			}
		}
		++_sn;
	}
	*sn = TACHO__NONE_;
	return ( false );
}

int ev3_tacho_init( void )
{
	char list[ 256 ];
	char *p;
	uint32_t sn;
	uint8_t type_inx;
	int cnt = 0;

	memset( ev3_tacho, 0, sizeof( ev3_tacho ));

	if ( !ev3_listdir( "/sys/class/tacho-motor", list, sizeof( list ))) return ( -1 );

	p = strtok( list, " " );
	while ( p ) {
		if (( ev3_string_suffix( "motor", &p, &sn ) == 1 ) && ( sn < TACHO_DESC__LIMIT_)) {
			
			type_inx = get_tacho_type_inx( sn );
			ev3_tacho[ sn ].type_inx = type_inx;
			ev3_tacho[ sn ].port = get_tacho_port_inx( sn, PORT_TYPE__NONE_, &ev3_tacho[ sn ].extport );
			++cnt;
		}
		p = strtok( NULL, " " );
	}
	return ( cnt );
}

