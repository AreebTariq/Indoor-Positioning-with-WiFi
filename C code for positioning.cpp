#include "stdio.h"
#include "conio.h"
#include "string.h"
#include "math.h"

using namespace std;

#define INVALID_VALUE 0xFFFF
#define TOTAL_APS 30
#define AVAILABLE_APS 10
#define MAC_LENGTH 12
#define MAX_POWER_LEVELS 20
#define TRUE 1
#define FALSE 0
#define APS_NEEDED_FOR_CALCULATION 3
#define MAX_APS_COMBINATIONS 20

int available_aps_count = 0;

struct Coordinates
{
	float x_coordinate;
	float y_coordinate;
	float z_coordinate;
};

struct AP_combination {
	char AP1_id[2];
	char AP2_id[2];
	char AP3_id[2];
	float AP1_power;
	float AP2_power;
	float AP3_power;
	float AP1_distance;
	float AP2_distance;
	float AP3_distance;
	float combination_mean_power;
};

struct AP
{
	float x_coordinate;
	float y_coordinate;
	float z_coordinate;
	char MAC[MAC_LENGTH];
	char MAC_identifier[5];
	float n_sf;
	float faf;
	float d0;
	float Pd0;
	char floor;
	char floor_side[10];
	char id[2];
};

AP AP_list[TOTAL_APS];
Available_AP available_AP_list[AVAILABLE_APS];
Unprocessed_Available_AP unprocessed_available_AP_list[AVAILABLE_APS];
AP_combination combination_APS[MAX_APS_COMBINATIONS];
Coordinates estimated_coordinates[MAX_APS_COMBINATIONS];

struct Available_AP
{
	char mac_id[MAC_LENGTH];
	float received_power_level;
	float distance;
};

struct Unprocessed_Available_AP
{
	char mac_id[MAC_LENGTH];
	float received_power_levels[MAX_POWER_LEVELS];
};

void initialize_AP_struct(AP *access_point)
{
	access_point->x_coordinate = INVALID_VALUE;
	access_point->y_coordinate = INVALID_VALUE;
	access_point->z_coordinate = INVALID_VALUE;
	//access_point->MAC = "INVALID_VALUE";
	//mac_identifier
	access_point->n_sf = INVALID_VALUE;
	access_point->faf = INVALID_VALUE;
	access_point->d0 = INVALID_VALUE;
	access_point->Pd0 = INVALID_VALUE;
	access_point->floor = "INVALID";
	//floor
	//floor side
	//id
}

void initialize_available_AP_struct(Available_AP* access_point)
{
	access_point->received_power_level = INVALID_VALUE;
	access_point->distance = INVALID_VALUE;
	//access_point->mac_id = "INVALID_VALUE";
}

void initialize_unprocessed_available_AP_struct(Unprocessed_Available_AP* access_point)
{
	//access_point->mac_id = INVALID_VALUE;
	for (int i = 0;i < MAX_POWER_LEVELS;i++)
	{
		access_point->received_power_levels[i] = INVALID_VALUE;
	}
}

void initialize_combination_AP_struct(AP_combination* combination)
{
	//combination->AP1_id = "INVALID_VALUE";
	//combination->AP2_id = "INVALID_VALUE";
	//combination->AP3_id = "INVALID_VALUE";
	combination->AP1_power = INVALID_VALUE;
	combination->AP2_power = INVALID_VALUE;
	combination->AP3_power = INVALID_VALUE;
	combination->AP1_distance = INVALID_VALUE;
	combination->AP2_distance = INVALID_VALUE;
	combination->AP3_distance = INVALID_VALUE;
}

void initialize_coordinates(Coordinates* coordinates)
{
	coordinates->x_coordinate = INVALID_VALUE;
	coordinates->y_coordinate = INVALID_VALUE;
	coordinates->z_coordinate = INVALID_VALUE;
}

float calculate_distance_from_Pd(float power_value, char* mac_address)
{
	float distance = INVALID_VALUE;
	AP ap_data;

	initialize_AP_struct(&ap_data);
	ap_data = get_AP_from_MAC(mac_address);

	if (ap_data.id != "INVALID_VALUE")
	{
		power_value = -1 * power_value;
		power_value = power_value + ap_data.Pd0;
		power_value = power_value / 10;
		power_value = power_value / ap_data.n_sf;
		power_value = pow(10, power_value);

		distance = power_value * ap_data.d0;
	}
	else
	{
		return distance;
	}

	return distance;
}

int is_entered_mac_valid(char* mac_address)
{
	int return_value = FALSE;
	for (int i = 0; i < TOTAL_APS; i++)
	{
		if (AP_list[i].MAC == mac_address)
		{
			return_value = TRUE;
			return return_value;
		}
	}
}

AP get_AP_from_MAC(char* mac_address)
{
	AP access_point;
	initialize_AP_struct(&access_point);
	for (int i = 0; i < TOTAL_APS; i++)
	{
		if (AP_list[i].MAC == mac_address)
		{
			access_point = AP_list[i];
			break;
		}
	}
	return access_point;
}

char* get_AP_id_from_MAC(char* mac_address)
{
	char id[2];
	for (int i = 0; i < TOTAL_APS; i++)
	{
		if (AP_list[i].MAC == mac_address)
		{
			//id = AP_list[i].id;
			break;
		}
	}
	return id;
}

float get_median_power_level(float* list_of_power_levels)
{

}

void order_the_APs()
{
	//arrange access points with decreasing power levels
}

void reorder_the_combinations()
{
	//reorder by decreasing mean combination power value
}

void make_combinations_of_APs()
{
	//Available_AP temp_aps_list[];
	//function which returns the of array combinations data containing 3 MACs (struct with 3 macs, 3 power levels, 3 distances)
	//loop for first combination containing MAC

	for (int i = 0;i < MAX_APS_COMBINATIONS;i++)
	{
		if (combination_APS[i].AP1_id == "INVALID_VALUE" && combination_APS[i].AP2_id == "INVALID_VALUE" &&
			combination_APS[i].AP3_id == "INVALID_VALUE")
		{
			//combination_APS[i].AP3_id = get_AP_id_from_MAC(return_mac1);
			//combination_APS[i].AP3_id = get_AP_id_from_MAC(return_mac2);
			//combination_APS[i].AP3_id = get_AP_id_from_MAC(return_mac3);
			//combination_APS[i].AP1_power = return_power_level_1;
			//combination_APS[i].AP2_power = return_power_level_2;
			//combination_APS[i].AP3_power = return_power_level_3;
			combination_APS[i].combination_mean_power = (combination_APS[i].AP1_power + combination_APS[i].AP2_power + combination_APS[i].AP3_power) / 3;
			//combination_APS[i].AP1_distance = return_distance_1;
			//combination_APS[i].AP2_distance = return_distance_2;
			//combination_APS[i].AP3_distance = return_distance_3;
			
			break;
		}
	}

	//loop end
	for (int i = 0;i < available_aps_count;i++)
	{

	}

}

void store_power_level_for_AP(char* mac_address, float power_value)
{
	int i = 0;
	for (;i < AVAILABLE_APS; i++)
	{
		if (unprocessed_available_AP_list[i].mac_id == mac_address)
		{
			int j = 0;
			for (;j < MAX_POWER_LEVELS;j++)
			{
				if (unprocessed_available_AP_list[i].received_power_levels[j] == INVALID_VALUE)
				{
					unprocessed_available_AP_list[i].received_power_levels[j] = power_value;
					break;
				}
			}

			if (j == MAX_POWER_LEVELS)
			{
				printf("Can't store more power recording for this AP. Already enough readings available\n.");
				break;
			}
			break;
		}
	}

	if (i == AVAILABLE_APS)
	{
		printf("New AP, Adding it to list of available access points list\n");
		int k = 0;
		for (;k < AVAILABLE_APS;k++)
		{
			if (unprocessed_available_AP_list[k].mac_id == "INVALID_VALUE")
			{
				unprocessed_available_AP_list[k].mac_id = mac_address;
				unprocessed_available_AP_list[k].received_power_levels[0] = power_value;
				available_aps_count++;
				break;
			}
		}

		if (k == AVAILABLE_APS)
		{
			printf("Already enough APs available for this measurement point. Can't add more\n");
		}
	}
}

void initialize_program()
{
	for (int i = 0;i < AVAILABLE_APS;i++)
	{
		initialize_available_AP_struct(&available_AP_list[i]);
		initialize_unprocessed_available_AP_struct(&unprocessed_available_AP_list[i]);
	}

	for (int i = 0;i < MAX_APS_COMBINATIONS;i++)
	{
		initialize_combination_AP_struct(&combination_APS[i]);
	}

	for (int i = 0; i < MAX_APS_COMBINATIONS; i++)
	{
		initialize_coordinates(&estimated_coordinates[i]);
	}
}

void process_the_available_APs()
{
	char mac_value[MAC_LENGTH];
	float power_value;
	float distance;
	for (int i = 0;i < AVAILABLE_APS;i++)
	{
		if (unprocessed_available_AP_list[i].mac_id != "INVALID_VALUE")
		{
			//float valid_power_values
			//calculate the median of power levels
			available_AP_list[i].mac_id = unprocessed_available_AP_list[i].mac_id;
			//available_AP_list[i].received_power_level = median_value;
			available_AP_list[i].distance = calculate_distance_from_Pd(available_AP_list[i].received_power_level, available_AP_list[i].mac_id);
		}
	}
}

Coordinates get_AP_coordinates_from_id(char* id)
{
	Coordinates ap_coordinates;
	initialize_coordinates(&ap_coordinates);
	for (int i = 0; i < TOTAL_APS; i++)
	{
		if (AP_list[i].id == id)
		{
			ap_coordinates.x_coordinate = AP_list[i].x_coordinate;
			ap_coordinates.y_coordinate = AP_list[i].y_coordinate;
			ap_coordinates.z_coordinate = AP_list[i].z_coordinate;
			break;
		}
	}
	return ap_coordinates;
}

Coordinates get_estimated_coordinates(AP_combination* combination)
{
	Coordinates AP[APS_NEEDED_FOR_CALCULATION];
	Coordinates estimated_coordinates_values;
	
	AP[0] = get_AP_coordinates_from_id(combination->AP1_id);
	AP[1] = get_AP_coordinates_from_id(combination->AP2_id);
	AP[2] = get_AP_coordinates_from_id(combination->AP3_id);
	
	//Equation-1
	//( estimated_coordinates_values.x_coordinate - AP[0].x_coordinate )^2 +
	//( estimated_coordinates_values.y_coordinate - AP[0].y_coordinate )^2 +
	//( estimated_coordinates_values.z_coordinate - AP[0].z_coordinate )^2 = combination->AP1_distance;

	//Equation-2
	//( estimated_coordinates_values.x_coordinate - AP[1].x_coordinate )^2 +
	//( estimated_coordinates_values.y_coordinate - AP[1].y_coordinate )^2 +
	//( estimated_coordinates_values.z_coordinate - AP[1].z_coordinate )^2 = combination->AP2_distance;

	//Equation-3
	//( estimated_coordinates_values.x_coordinate - AP[2].x_coordinate )^2 +
	//( estimated_coordinates_values.y_coordinate - AP[2].y_coordinate )^2 +
	//( estimated_coordinates_values.z_coordinate - AP[2].z_coordinate )^2 = combination->AP3_distance;

	//Solution will give-> estimated_coordinates_values.x_coordinate, estimated_coordinates_values.y_coordinate, and 
	//estimated_coordinates_values.z_coordinate

	return estimated_coordinates_values;
}

float find_median(float *)
{

}
void process_combinations()
{
	Coordinates estimated_coordinates[MAX_APS_COMBINATIONS];
	float estimated_x_coordinates[MAX_APS_COMBINATIONS];
	float estimated_y_coordinates[MAX_APS_COMBINATIONS];
	float final_estimated_x, final_estimated_y;
	
	for (int i = 0; i < MAX_APS_COMBINATIONS; i++)
	{
		estimated_coordinates[i] = get_estimated_coordinates(&combination_APS[i]);
	}

	for (int j = 0; j < MAX_APS_COMBINATIONS;j++)
	{
		estimated_x_coordinates[j] = estimated_coordinates[j].x_coordinate;
		estimated_y_coordinates[j] = estimated_coordinates[j].y_coordinate;
	}

	final_estimated_x =  find_median(estimated_x_coordinates);
	final_estimated_y =  find_median(estimated_y_coordinates);

	printf("Estimated x = %f,  Estimated y = %f as per the reference origin",final_estimated_x,final_estimated_y);
}


int main()
{
	char input_mac[MAC_LENGTH];
	float input_power;

	initialize_program();

	printf("Enter the received power level or enter exit to finish the recordings\n");
	while (input_mac != "exit")
	{
		scanf("%s\n",&input_mac);

		if (input_mac == "exit" || input_mac == "Exit")
		{
			printf("Terminating the recordings\n");
			break;
		}

		int valid_mac = FALSE;
		AP received_AP;
		initialize_AP_struct(&received_AP);

		printf("Enter the power: ");
		scanf("%f\n", input_power);
		printf("Enter the corresponding MAC address: ");
		scanf("%s\n", input_mac);

		valid_mac = is_entered_mac_valid(input_mac);

		if (valid_mac == TRUE)
		{
			store_power_level_for_AP(input_mac, input_power);
		}
		else
		{
			printf("This MAC address is not part of the stored access points. Please exter next recording or enter exit\n");
		}

	}

	printf("Recording phase is completed, processing of data is started\n");
	
	process_the_available_APs();
	order_the_APs(); //maybe removed since order of APs could be unimportant, but order of combinations is important

	make_combinations_of_APs();
	reorder_the_combinations();

	process_combinations();

	return 0;
}

