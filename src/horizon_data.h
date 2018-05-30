#ifndef HORIZON_DATA_H
#define HORIZON_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//the data we take from the telnet requests
#define LINE_SIZE 128
#define CHAR_SPLIT_VALUE 40

enum class HORIZON_TYPES
{
	RADIUS_KM,
	VELOCITY_X_Y,
	MASS,
	SURFACE_GRAVITY,
	ECCENTRICITY,
	INCLINATION,
	TYPE_SIZE
};

//these are the ids used on horizon telnet request
enum HORIZON_BODY_IDS
{
	SUN = 10,
	MERCURY = 199,
	VENUS = 299,
	EARTH = 399,
	MOON = 301,
	MARS = 499,
	JUPITER = 599,
	SATURN = 699,
	URANUS = 799,
	NEPTUNE = 899,
	PLUTO = 999,
	ID_SIZE
};

char* horizon_body_get(HORIZON_BODY_IDS hb);

static char* search_data_str[] = 
{
	"radius",
	"V(1,0)",
	"Mass",
	"Surface gravity",
	"Eccentricity",
	"Inclination"
};

typedef struct horizon_data
{
	//id used for the horizon sys
	uint16_t body_id;
	//Radius (IAU), km
	float radius;
	//V(1,0)
	float visual_magnitude;
	//Surface gravity
	float surface_gravity;
	//Mass, 10^20 kg
	float mass;
	//parameter that determines the amount by which its orbit around another body deviates from a perfect circle
	float orbital_eccentricity;
	//measures the tilt of an object's orbit around a celestial body
	float orbital_inclination;
} horizon_data;

void remove_char(char* str, char garbage);
void horizon_data_zero(horizon_data* hd);
void horizon_data_upload(horizon_data* hd, HORIZON_TYPES hd_id, float v);
float horizon_data_find_value(char* str);
void horizon_data_split(char* l, char* out1, char* out2);
int horizon_data_find(char* l, int* hd_id);
horizon_data horizon_data_get(uint16_t id, char* buffer);

#endif
