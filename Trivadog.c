#include "Trivadog.h"

Trivadog* AddHostel(Trivadog* td, const Hostel* ht)
{
	// add hostel to the Trivadog app:
	// if the Trivadog app is null - td = has one hostel which is the hostel we need to add
	// if the hostel already exist in the Trivadog app - we don't need to do anything
	// else - increase by one the hostel array, and then add the hostel

	// td is null
	if (td == NULL)
	{
		td = (struct Trivadog*)malloc(sizeof(struct Trivadog)); // try allocate memory for the Trivadog app
		if (td == NULL)
		{
			// if failed, free the memory and return null
			return NULL;
		}
		td->hostels = (struct Hostel**)malloc(sizeof(struct Hostel*)); // try allocate memory for the hostels pointer
		if (td->hostels == NULL)
		{
			// if failed, release the memory and return null
			free(td);
			return NULL;
		}
		// if seceeded, fill the hostel as needed
		td->num_of_hostels = 1;
		struct Hostel* temp = DuplicateHostel(ht);
		if (temp == NULL)
		{
			free(td->hostels);
			free(td);
			return NULL;
		}
		td->hostels[0] = temp;
		return td;
	}

	// if td exists but he doesn't have hostels yet, we create a new pointer to the hostels and add the new hostel to there
	if (td->hostels == NULL)
	{
		td->hostels = (struct Hostel**)malloc(sizeof(struct Hostel*)); // try allocate memory for the hostels pointer
		if (td->hostels == NULL)
		{
			// if failed, release the memory and return null
			free(td);
			return NULL;
		}
		// if seceeded, fill the hostel as needed
		td->num_of_hostels = 1;
		struct Hostel* temp = DuplicateHostel(ht);
		if (temp == NULL) 
		{ 
			free(td->hostels);
			free(td);
			return NULL;
		}
		td->hostels[0] = temp;
		return td;
	}

	int flag = 0; // check if the hostel already in the Trivadog app (1 - yes, 0 - no)
	int i;
	for (i = 0; i < td->num_of_hostels; i++)
	{
		// check if the hostel exists in the Trivadog app
		if (strcmp(td->hostels[i]->hostel_name, ht->hostel_name) == 0)
		{
			flag = 1;
		}
	}

	// if the hostel exists in the Trivadog app, return td
	if (flag == 1)
	{
		return td;
	}

	// the hostel doesn't exists
	struct Hostel** hostelsP = td->hostels;
	// try to allocate more memory for the new hostel
	td->hostels = (struct Hostel**)realloc(td->hostels, (td->num_of_hostels + 1) * sizeof(struct Hostel*));
	if (td->hostels == NULL)
	{
		// if failed, return null
		td->hostels = hostelsP;
		return NULL;
	}
	++(td->num_of_hostels);
	struct Hostel* temp = DuplicateHostel(ht);
	if (temp == NULL) 
	{ 
		free(td->hostels);
		free(td);
		return NULL; 
	}
	td->hostels[td->num_of_hostels - 1] = temp; // duplicate the data from the room to the hostel
	return td;
}

void SortByName(Trivadog* td)
{
	/// <summary>
	/// this function sort all the hostels in the Trivadog app by name (from lowest to biggest)
	/// </summary>
	/// <param name="td"></param>

	Hostel* temp = NULL; // temp variable for switching the names 
	for (int i = 0; i < td->num_of_hostels - 1; i++)
	{
		for (int j = i + 1; j < td->num_of_hostels; j++)
		{
			// strcmp > 0 if the ASCII value of the first unmatched character is greater than the second
			if (strcmp(td->hostels[i]->hostel_name, td->hostels[j]->hostel_name) > 0)
			{
				temp = DuplicateHostel(td->hostels[i]);
				td->hostels[i] = DuplicateHostel(td->hostels[j]);
				td->hostels[j] = DuplicateHostel(temp);
				if (td->hostels[i] == NULL || td->hostels[j] == NULL) { return; }
			}
		}
	}
}

void SortByRate(Trivadog* td)
{
	// sort the hostels in td by rate from biggest to lowest
	Hostel* temp = NULL; // temp variable for switching the names 
	for (int i = 0; i < td->num_of_hostels - 1; i++)
	{
		for (int j = i + 1; j < td->num_of_hostels; j++)
		{
			// strcmp > 0 if the ASCII value of the first unmatched character is greater than the second
			if (td->hostels[i]->rate < td->hostels[j]->rate)
			{
				temp = DuplicateHostel(td->hostels[i]);
				td->hostels[i] = DuplicateHostel(td->hostels[j]);
				td->hostels[j] = DuplicateHostel(temp);
				if (td->hostels[i] == NULL || td->hostels[j] == NULL) { return; }
			}
		}
	}

}

int GetTotalAvailableRooms(Trivadog* td, const char* type)
{
	//counts how many rooms of the type are in this trivadog
	int count = 0;//counting rooms
	for (int i = 0; i < (*td).num_of_hostels; i++)
	{
		count += GetAvailableRooms(td->hostels[i], type);
	}
	return count;
}

int* GetTotalAvailableRoomsInArr(Trivadog* td, char** arr_type, int size)
{
	//counts how many rooms of each type in arr_type are in this trivadog
	int* numRooms = malloc(size * sizeof(int));
	// if memory allocation failed, free the memory and return null
	if (numRooms == NULL)
	{
		return NULL;
	}
	char** t = arr_type;
	for (int i = 0; i < size; i++)
	{
		*(numRooms + i) = GetTotalAvailableRooms(td, *t);
		t++;
	}
	return numRooms;
}

void FreeTrivadog(Trivadog* td)
{
	// free memory used by trivadog
	for (int i = 0; i < (*td).num_of_hostels; i++)
	{
		FreeHostel(td->hostels[i]);
	}
	free(td->hostels);
	free(td);
}

Trivadog* DuplicateTrivadog(const Trivadog* source)
{
	// duplicate the trivadog app to a new one and return pointer to the new one
	struct Trivadog* td = (struct Trivadog*)malloc(sizeof(struct Trivadog)); // try allocate memory for the new Trivadog app
	if (td == NULL)
	{
		// if failed, free the memory and return null
		return NULL;
	}
	td->hostels = (struct Hostel**)malloc(source->num_of_hostels * sizeof(struct Hostel*)); // try allocate memory for the hostels pointer
	if (td->hostels == NULL)
	{
		// if failed, release the memory and return null
		free(td);
		return NULL;
	}
	// if seceeded, fill the hostel as needed
	td->num_of_hostels = source->num_of_hostels;
	int i;
	for (i = 0; i < td->num_of_hostels; i++)
	{
		Hostel* temp = DuplicateHostel(source->hostels[i]);
		if (temp == NULL)
		{
			free(td->hostels);
			free(td);
			return NULL;
		}
		td->hostels[i] = temp; // duplicate each hostel to the new trivadog app
	}
	return td;
}