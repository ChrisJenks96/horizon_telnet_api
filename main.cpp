#include "horizon_data.h"
#include "horizon_client.h"

int main(int argc, char** argv)
{
	client_data cd;
	if (horizon_client_setup(&cd, HOST_IP, PORT_NO))
	{
		char buffer[BUFFER_SIZE];
		horizon_client_receive(&cd, horizon_body_get(HORIZON_BODY_IDS::EARTH), buffer);
		horizon_data hd = horizon_data_get(HORIZON_BODY_IDS::EARTH, buffer);	
		horizon_client_destroy(&cd);
		getchar();
	}

	return 0;
}