#ifndef DUNGEON_H
# define DUNGEON_H

# include "heap.h"
# include "dims.h"
# include "character.h"
#include "npc.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DUNGEON_X              80
#define DUNGEON_Y              21
#define MIN_ROOMS              6
#define MAX_ROOMS              10
#define ROOM_MIN_X             4
#define ROOM_MIN_Y             3
#define ROOM_MAX_X             20
#define ROOM_MAX_Y             15
#define PC_VISUAL_RANGE        3
#define NPC_VISUAL_RANGE       15
#define PC_SPEED               10
#define NPC_MIN_SPEED          5
#define NPC_MAX_SPEED          20
#define MAX_MONSTERS           15
#define SAVE_DIR               ".rlg327"
#define DUNGEON_SAVE_FILE      "dungeon"
#define DUNGEON_SAVE_SEMANTIC  "RLG327-" TERM
#define DUNGEON_SAVE_VERSION   0U
#define MONSTER_DESC_FILE      "monster_desc.txt"
#define OBJECTS_DESC_FILE      "object_desc.txt"

#define mappair(pair) (d->map[pair[dim_y]][pair[dim_x]])
#define mapxy(x, y) (d->map[y][x])
#define hardnesspair(pair) (d->hardness[pair[dim_y]][pair[dim_x]])
#define hardnessxy(x, y) (d->hardness[y][x])
#define charpair(pair) (d->character_map[pair[dim_y]][pair[dim_x]])
#define charxy(x, y) (d->character_map[y][x])

enum __attribute__ ((__packed__)) terrain_type {
  ter_debug,
  ter_unknown,
  ter_wall,
  ter_wall_immutable,
  ter_floor,
  ter_floor_room,
  ter_floor_hall,
  ter_stairs,
  ter_stairs_up,
  ter_stairs_down
};

void init_dungeon(dungeon *d);
void new_dungeon(dungeon *d);
void delete_dungeon(dungeon *d);
int gen_dungeon(dungeon *d);
void render_dungeon(dungeon *d);
int write_dungeon(dungeon *d, char *file);
int read_dungeon(dungeon *d, char *file);
int read_pgm(dungeon *d, char *pgm);
void render_distance_map(dungeon *d);
void render_tunnel_distance_map(dungeon *d);
void read_monster_desc_to_dungeon(dungeon *d);
void read_objects_desc_to_dungeon(dungeon *d);

typedef struct room {
  pair_t position;
  pair_t size;
} room_t;

class pc;
class dice_stats {
public:
    int base;
    int dice;
    int sides;
};
class monster_description {
public:
    char symbol;
    dice_stats speed;
    char *name;
    char *desc = new char[1024];
    char *colors;
    dice_stats attack_damage;
    dice_stats hp;
    u_int8_t rarity;
    npc_characteristics_t ability = 0;
};
class object_description {
public:
    char *type;
    char *name;
    char *desc = new char[1024];
    char *colors;
    bool art;
    u_int8_t rarity;
    dice_stats weight;
    dice_stats hit;
    dice_stats dam;
    dice_stats attr;
    dice_stats val;
    dice_stats dodge;
    dice_stats def;
    dice_stats speed;
};
class dungeon {
 public:
  uint32_t num_rooms;
  room_t *rooms;
  terrain_type map[DUNGEON_Y][DUNGEON_X];
  /* Since hardness is usually not used, it would be expensive to pull it *
   * into cache every time we need a map cell, so we store it in a        *
   * parallel array, rather than using a structure to represent the       *
   * cells.  We may want a cell structure later, but from a performanace  *
   * perspective, it would be a bad idea to ever have the map be part of  *
   * that structure.  Pathfinding will require efficient use of the map,  *
   * and pulling in unnecessary data with each map cell would add a lot   *
   * of overhead to the memory system.                                    */
  uint8_t hardness[DUNGEON_Y][DUNGEON_X];
  uint8_t pc_distance[DUNGEON_Y][DUNGEON_X];
  uint8_t pc_tunnel[DUNGEON_Y][DUNGEON_X];
  character *character_map[DUNGEON_Y][DUNGEON_X];
  pc *PC;
  heap_t events;
  uint16_t num_monsters;
  uint16_t max_monsters;
  uint32_t character_sequence_number;
  /* Game time isn't strictly necessary.  It's implicit in the turn number *
   * of the most recent thing removed from the event queue; however,       *
   * including it here--and keeping it up to date--provides a measure of   *
   * convenience, e.g., the ability to create a new event without explicit *
   * information from the current event.                                   */
  uint32_t time;
  uint32_t is_new;
  character *desc_stats;
  uint32_t quit;
  int num_mons_desc;
  monster_description *md;
  int num_objs_desc;
  object_description *od;
};



#endif
