#include "horizon_data.h"

char* horizon_body_get(HORIZON_BODY_IDS hb)
{
	switch(hb)
	{
		case HORIZON_BODY_IDS::EARTH:
				return "399\r\n\n";
		case HORIZON_BODY_IDS::JUPITER:
				return "599\r\n\n";
		case HORIZON_BODY_IDS::MARS:
				return "499\r\n\n";
		case HORIZON_BODY_IDS::MERCURY:
			return "199\r\n\n";
		case HORIZON_BODY_IDS::MOON:
			return "301\r\n\n";
		case HORIZON_BODY_IDS::NEPTUNE:
			return "899\r\n\n";
		case HORIZON_BODY_IDS::PLUTO:
			return "999\r\n\n";
		case HORIZON_BODY_IDS::SATURN:
			return "699\r\n\n";
		case HORIZON_BODY_IDS::SUN:
			return "10\r\n\n";
		case HORIZON_BODY_IDS::URANUS:
			return "799\r\n\n";
		case HORIZON_BODY_IDS::VENUS:
			return "299\r\n\n";
	}
}

void remove_char(char* str, char garbage) 
{
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) 
	{
        *dst = *src;
        if (*dst != garbage) 
			dst++;
    }

    *dst = 0;
}

void horizon_data_upload(horizon_data* hd, HORIZON_TYPES hd_id, float v)
{
	switch(hd_id)
	{
		case HORIZON_TYPES::MASS:
			if (hd->mass == 0.0f)
				hd->mass = v;
			break;
		case HORIZON_TYPES::ECCENTRICITY:
			if (hd->orbital_eccentricity == 0.0f)
				hd->orbital_eccentricity = v;
			break;
		case HORIZON_TYPES::INCLINATION:
			if (hd->orbital_inclination == 0.0f)
				hd->orbital_inclination = v;
			break;
		case HORIZON_TYPES::RADIUS_KM:
			if (hd->radius == 0.0f)
				hd->radius = v;
			break;
		case HORIZON_TYPES::SURFACE_GRAVITY:
			if (hd->surface_gravity == 0.0f)
				hd->surface_gravity = v;
			break;
		case HORIZON_TYPES::VELOCITY_X_Y:
			if (hd->visual_magnitude == 0.0f)
				hd->visual_magnitude = v;
			break;
	}
}

float horizon_data_find_value(char* str)
{
	char* c = strstr(str, "=");
	if (c == NULL)
		return -1;
	c = c + 1;
	remove_char(&c[0], ' ');
	return atof(c);
}

int horizon_data_find(char* l, int* hd_id)
{
	int i;
	for (i = 0; i < (int)HORIZON_TYPES::TYPE_SIZE; i++)
	{
		char* c;
		if (c = strstr(l, search_data_str[i])){
			*hd_id = i;
			return atoi(c);
		}
	}

	return -1;
}

void horizon_data_split(char* l, char* out1, char* out2)
{
	int l_len = strlen(l);
	memcpy(&out1[0], &l[0], CHAR_SPLIT_VALUE);
	out1[CHAR_SPLIT_VALUE] = 0;
	memcpy(&out2[0], &l[CHAR_SPLIT_VALUE], l_len);
	out2[l_len] = 0;
}

void horizon_data_zero(horizon_data* hd)
{
	hd->body_id = 0;
	hd->mass = 0.0f;
	hd->orbital_eccentricity = 0.0f;
	hd->orbital_inclination = 0.0f;
	hd->radius = 0.0f;
	hd->surface_gravity = 0.0f;
	hd->visual_magnitude = 0.0f;
}

horizon_data horizon_data_get(uint16_t id, char* buffer)
{
	//used to split the lines up
	char str_p1[LINE_SIZE], str_p2[LINE_SIZE];
	int hd_id, counter = 0;
	horizon_data hd;
	//zero thenumbers out
	horizon_data_zero(&hd);
	//add the body id to the data
	hd.body_id = id;
	char* line = strtok(strdup(buffer), "\n");
	while (line) 
	{
		//loop through what we're searching for
		int ch = horizon_data_find(line, &hd_id);
		if (ch > -1)
		{
			horizon_data_split(line, str_p1, str_p2);
			ch = horizon_data_find(str_p1, &hd_id);
			float val;
			if (ch > -1){
				val = horizon_data_find_value(str_p1);
				if (val != -1){
					horizon_data_upload(&hd, (HORIZON_TYPES)hd_id, val);
					counter++;
				}
			}

			ch = horizon_data_find(str_p2, &hd_id);
			if (ch > -1){
				val = horizon_data_find_value(str_p2);
				if (val != -1){
					horizon_data_upload(&hd, (HORIZON_TYPES)hd_id, val);
					counter++;
				}
			}
		}

		if (counter == (int)HORIZON_TYPES::TYPE_SIZE)
			break;

		line = strtok(NULL, "\n");
	}

	return hd;
}