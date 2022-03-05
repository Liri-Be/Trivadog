# Trivadog
## Summary
Trivadog is a program that handles hostels.

## Functions
1. Create a new room.
2. Create a new hostel.
3. Add a new room to the hostel.
4. Find the number of empty rooms in the hostel.
5. Add a new hostel to trivadog (The "database" of the hotels).
6. Find the number of empty rooms in all of the hostels in trivadog.
7. Find the number of empty rooms of a specific type in all of the hostels in trivadog.
8. Sort all hostels by name.
9. Sort all hostels by rate.  

## Structs
The program uses structs for the rooms, hostels, and Trivadog.

### Room 
members (struct) - 
1. room number (```int```)
2. cost for a night (```float```)
3. is the room available (```int```, zero or one)
4. room type (```char*```)

### Hostel 
members (struct) -
1. pointer for the rooms (```Room**```)
2. number of rooms (```int```)
3. hostel name (```char*```)

### Trivadog 
members (struct) -
1. pointer for the hostels (```Hostels**```)
2. number of hostels (```int```)
