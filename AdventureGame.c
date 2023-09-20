#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_DESCRIPTION_LENGTH 80

/* =============== STRUCTURES =============== */

typedef struct {
    char name[MAX_DESCRIPTION_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int north, south, east, west; //* -1 means no room to there, except that it means index of the room
    int objects[3]; //* -1 means no objects, except that it means index of the object
} Room;

typedef struct {
    char name[MAX_DESCRIPTION_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int location; //* index of room that object is in
    bool can_be_picked;
} Object;

typedef struct {
    char name[MAX_DESCRIPTION_LENGTH];
    int location; //* index of room player is in
    int objects[3]; //* -1 means no objects, except that index of object player carries with him.
    bool has_key;
    bool has_hammer;
} Player;

/* =============== STRUCTURES =============== */

int main() {
    bool game_is_on = true;

    //? Initialize Objects
    Object objects[5] = {
        {"Brick Wall", "Can be demolished with right tools", 0, false},

        {"Pressure Plate", "Should put something on heavy it", 1, false},
        {"Key", "Could open a door..", 1, true},
        
        {"Toy", "It`s heavy it might activate something..", 2, true},

        {"Sledge Hammer", "Sling it!", 3, true},
    };

    //? Initialize Rooms & Map drawing
    /* 
          Win(4)
           |
        Bedroom(0) - ChildsRoom(2) - Secret(3)
           |
        LivingRoom(1)
    */
    Room rooms[5] = {
        {"Bedroom", "Smells of paint (Bedroom)", 4, 1, 2, -1, {0, -1, -1}},
        {"Living Room", "You are in the living room", 0, -1, -1, -1, {1, 2, -1}},
        {"Childs Room", "You are in the child room", -1, -1, 3, 0, {3, -1, -1}},
        {"Secret Room", "SSH! (Secret Room)", -1, -1, -1, 2,{4, -1, -1}},
        {"Winning room", "YOU WON!", -1, 0, -1, -1, {-1, -1, -1}},
    };

    
    //? Initialize Player
    Player player = {"Player", 2, {-1, -1, -1}, false, false};
    printf("Enter name --> ");
    scanf(" %s", player.name);
    int inventory_counter = 0;
    //! Game Loop
    while(game_is_on == true){
        //system("cls");
        Room current_room = rooms[player.location];
        char action;
        
        printf("====== Actions ======\n");
        printf("Change Room (North(n), South(s), East(e), West(w)))\n");
        printf("Interact with object (F)\n");
        printf("Drop Object(G)\n");
        printf("Quit(Q)\n");
        printf("====== Actions ======\n\n");
        
        /* Printing the objects in the current room */
        printf("The objects in this room are -->\n");
        int i, found = 0;
        for (i = 0; i < 3; i++) {
            if (current_room.objects[i] != -1) {
                printf(" - %s\n", objects[current_room.objects[i]].name);
                found = 1; 
            }
        }
        if (!found) {
            printf("There are no objects in the room.\n");
        }
        found = 0; //! reseting "found`s" value for inventory check
        /* Printing the objects in the current room */

        /* Checking Inventory, if has something prints items */
        for(i = 0; i < 3; i++){
            if(player.objects[i] != -1){
                found = 1;
            }
        }
        if (found == 1){
            printf("\nYou have --> \n");
            for(i = 0; i < 3; i++){
                if(player.objects[i] != -1){
                    printf(" - %s, %s\n", objects[player.objects[i]].name, objects[player.objects[i]].description);
                }
            }
        }
        /* Checking Inventory, if has something prints items */

        printf("\nHello %s, you are in %s, what would you like to do?\n", player.name, rooms[player.location].name);
        
        scanf(" %c", &action);

        
        /* ===== ACTION TAKING PART ===== */
        switch (action)
        {
        case 'n': //! GO TO NORTH
        case 'N':
            //? Check room condition & change players location based on that
            if(current_room.north != -1){
                player.location = current_room.north;
                current_room = rooms[player.location];
                printf("%s", current_room.name);
            }else{
                printf("There is no room to the North");
            }
            break;
        case 's': //! GO TO SOUTH 
        case 'S':
            //? Check room condition & change players location based on that
            if(current_room.south != -1){
                player.location = current_room.south;
                current_room = rooms[player.location];
                printf("%s", current_room.name);
            }else{
                printf("There is no room to the South");
            }
            break;
        case 'e': //! GO TO EAST
        case 'E':
            //? Check room condition & change players location based on that 
            if(current_room.east != -1){
                if(current_room.east ==  3){ //* Secret room needs key to open
                    if(player.has_key == false){
                        printf("You must have key to go there.");
                        break;
                    }
                }
                player.location = current_room.east;
                current_room = rooms[player.location];
                printf("%s", current_room.name);
            }else{
                printf("There is no room to the East");
            }
            break;
        case 'w': //! GO TO WEST
        case 'W':
            //? Check room condition & change players location based on that
            if(current_room.west != -1){
                player.location = current_room.west;
                current_room = rooms[player.location];
                printf("%s", current_room.name);
            }else{
                printf("There is no room to the West");
            }
            break;
        case 'f': //! Pick Up ACTION --> (Picking up items)
        case 'F':
            char object_name[MAX_DESCRIPTION_LENGTH];
            printf("Which object do you want to interact with: ");

            //! UNUTMA COK ONEMLI !!!!!!!!!!!!!!!!!!
            //? Input buffer temizlemen gerekiyo yoksa scanf geciyo direk.
            while (getchar() != '\n');
            fgets(object_name, MAX_DESCRIPTION_LENGTH, stdin);
            object_name[strcspn(object_name, "\n")] = 0;
            //! UNUTMA COK ONEMLI !!!!!!!!!!!!!!!!!!

            //? Check if the object is in the room and can be picked
            int object_index = -1;
            for (i = 0; i < 3; i++) {
                if (strcmp(object_name, objects[current_room.objects[i]].name) == 0) {
                    object_index = i;
                    if(objects[current_room.objects[i]].can_be_picked == true){
                        player.objects[inventory_counter] = current_room.objects[object_index]; //* Adding item to the players inventory
                        //printf("%d, %d, %d\n", objects[current_room.objects[object_index]].location, current_room.objects[object_index], object_index); // FOR TEST PURPOSES
                        objects[rooms[player.location].objects[object_index]].location = -1;
                        rooms[player.location].objects[object_index] = -1;
                        //printf("%d, %d, %d", objects[current_room.objects[object_index]].location, current_room.objects[object_index], current_room.objects[0]); // FOR TEST PURPOSES
                        if(strcmp(object_name, objects[2].name) == 0){
                            player.has_key = true;
                        }
                        inventory_counter++;
                        break;
                    }else{
                        printf("%s", objects[current_room.objects[i]].description);
                    }
                }
            }
            if (object_index == -1){
                printf("The object %s is not in the room.\n", object_name);
            }
            break;
        case 'q': //! Quit Game
        case 'Q':
            system("cls");
            printf("Quiting the game...");
            game_is_on = false;
        default:
            break;
        }
        /* ===== ACTION TAKING PART ===== */
    }
    return 0;
}

