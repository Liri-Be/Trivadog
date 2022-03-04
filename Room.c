#include "Room.h"

Room* CreateNewRoom(int _number, float _cost, int _available, const char* _type)
{
	// create new room with the data we got as varibales
	struct Room* r = (struct Room*)malloc(sizeof(struct Room)); // try allocate memory for the room pointer
	if (r == NULL)
	{
		// if failed, release the memory and return null
		return NULL;
	}
	r->type = (char*)malloc((strlen(_type) + 1) * sizeof(char)); // try allocate memory for the type pointer
	if (r->type == NULL)
	{
		// if failed, release the memory and return null
		free(r);
		return NULL;
	}
	// if seceeded, fill the room with the data from the user
	r->number = _number;
	r->cost_for_night = _cost;
	r->available = _available;
	strcpy(r->type, _type);
	return r; // return the room
}

Room* DuplicateRoom(const Room* source)
{
	// create new room with the data from the room we got - duplicate the room
	struct Room* r = CreateNewRoom(source->number, source->cost_for_night, source->available, source->type);
	return r; // return the room
}

void FreeRoom(Room* rm)
{
	free(rm->type);
	free(rm);
}