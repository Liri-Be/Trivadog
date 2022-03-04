#include "Hostel.h"

Hostel* AddRoom(Hostel* ht, const  Room* room)
{
	// add room to the hostel:
	// if the hostel is null - ht = unknown hostel with one room which is the room we need to add
	// if the hostel already have a room with the same number - change it's info according to the new room
	// else - increase by one the room array, and then add the room

	// ht is null
	if (ht == NULL)
	{
		ht = (struct Hostel*)malloc(sizeof(struct Hostel)); // try allocate memory for the hostel
		if (ht == NULL)
		{
			// if failed, free the memory and return null
			return NULL;
		}
		ht->hostel_name = (char*)malloc((strlen("UnKnown Hostel") + 1) * sizeof(char)); // try allocate memory for the name pointer
		if (ht->hostel_name == NULL)
		{
			// if failed, release the memory and return null
			free(ht);
			return NULL;
		}
		ht->rooms = (struct Rooms**)malloc(sizeof(struct Rooms*)); // try allocate memory for the rooms pointer
		if (ht->rooms == NULL)
		{
			// if failed, release the memory and return null
			free(ht->hostel_name);
			free(ht);
			return NULL;
		}
		// if seceeded, fill the hostel as needed
		strcpy(ht->hostel_name, "UnKnown Hostel");
		ht->rate = 0;
		ht->num_of_rooms = 1;
		struct Room* r = DuplicateRoom(room);
		if (r == NULL)
		{
			free(ht->hostel_name);
			free(ht->rooms);
			free(ht);
			return NULL;
		}
		ht->rooms[0] = r; // duplicate the data from the room to the hostel
		return ht;
	}
	struct Room* r;
	int flag = 0; // check if there is a room in the hostel with the same number as room (1 - yes, 0 - no)
	int i;
	for (i = 0; i < ht->num_of_rooms; i++)
	{
		if (ht->rooms[i]->number == room->number)
		{
			flag = 1;
			break;
		}
	}

	// the hostel contains a room with the same number
	if (flag == 1)
	{
		r = DuplicateRoom(room);
		if (r == NULL)
		{
			free(ht->hostel_name);
			free(ht->rooms);
			free(ht);
			return NULL;
		}
		ht->rooms[i] = r; // duplicate the data from the room to the hostel
		return ht;
	}

	// the hostel doesn't contain a room with the same number
	struct Room** roomsP = ht->rooms;
	// try to allocate more memory for the new room
	ht->rooms = (struct Room**)realloc(ht->rooms, (ht->num_of_rooms + 1) * sizeof(struct Room*));
	if (ht->rooms == NULL)
	{
		// if failed, return null
		ht->rooms = roomsP;
		return NULL;
	}
	++(ht->num_of_rooms);
	r = DuplicateRoom(room); // duplicate the data from the room to the hostel
	if (r == NULL)
	{
		free(ht->hostel_name);
		free(ht->rooms);
		free(ht);
		return NULL;
	}
	ht->rooms[ht->num_of_rooms - 1] = r;
	return ht;
}

Hostel* DuplicateHostel(const Hostel* source)
{
	// duplicate the hostel to a new one and return pointer to the new one
	struct Hostel* ht = (struct Hostel*)malloc(sizeof(struct Hostel)); // try allocate memory for the hostel
	if (ht == NULL)
	{
		// if failed, free the memory and return null
		return NULL;
	}
	ht->hostel_name = (char*)malloc((strlen(source->hostel_name) + 1) * sizeof(char)); // try allocate memory for the name pointer
	if (ht->hostel_name == NULL)
	{
		// if failed, release the memory and return null
		free(ht);
		return NULL;
	}
	ht->rooms = (struct Rooms**)malloc(source->num_of_rooms * sizeof(struct Rooms*)); // try allocate memory for the rooms pointer
	if (ht->rooms == NULL)
	{
		// if failed, release the memory and return null
		free(ht->hostel_name);
		free(ht);
		return NULL;
	}
	// if seceeded, duplicate the source hostel to the new hostel we created
	strcpy(ht->hostel_name, source->hostel_name);
	ht->num_of_rooms = source->num_of_rooms;
	ht->rate = source->rate;
	int i;
	struct Room* r;
	for (i = 0; i < ht->num_of_rooms; i++)
	{
		r = DuplicateRoom(source->rooms[i]);
		if (r == NULL)
		{
			for (int j = i; j >= 0; j--)
			{
				free(ht->rooms[j]);
			}
			free(ht->hostel_name);
			free(ht->rooms);
			free(ht);
			return NULL;
		}
		ht->rooms[i] = r; // duplicate each room to the new hostel
	}
	return ht;
}

int GetAvailableRooms(const Hostel* ht, const char* type)
{
	//counting how many rooms of the giving type are in the hostel
	int count = 0; //counting rooms
	for (int i = 0; i < (*ht).num_of_rooms; i++)
	{
		if (!strcmp(type, ht->rooms[i]->type) && ht->rooms[i]->available == 1)
			count++;
	}
	return count;
}

void FreeHostel(Hostel* ht)
{
	//free memory of this hostel
	free(ht->hostel_name);
	for (int i = 0; i < ht->num_of_rooms; i++)
	{
		FreeRoom(ht->rooms[i]);
	}
	free(ht->rooms);
	free(ht);
}