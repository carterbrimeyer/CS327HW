#ifndef PC_H
# define PC_H

# define ITEM_SLOTS      12
# define SLOT_WEAPON     0
# define SLOT_OFFHAND    1
# define SLOT_RANGED     2
# define SLOT_ARMOR      3
# define SLOT_HELMET     4
# define SLOT_CLOAK      5
# define SLOT_GLOVES     6
# define SLOT_BOOTS      7
# define SLOT_AMULET     8
# define SLOT_LIGHT      9
# define SLOT_RING_RH    10
# define SLOT_RING_LH    11

# include <stdint.h>

# include "dims.h"
# include "character.h"
# include "dungeon.h"
# include "object.h"

class pc : public character {
 public:
  ~pc() {}
  terrain_type known_terrain[DUNGEON_Y][DUNGEON_X];
  uint8_t visible[DUNGEON_Y][DUNGEON_X];
    object *inventory[PC_MAX_INV];
    object *equipment[12];
};

void pc_delete(pc *pc);
uint32_t pc_is_alive(dungeon *d);
void config_pc(dungeon *d);
uint32_t pc_next_pos(dungeon *d, pair_t dir);
void place_pc(dungeon *d);
uint32_t pc_in_room(dungeon *d, uint32_t room);
void pc_learn_terrain(pc *p, pair_t pos, terrain_type ter);
terrain_type pc_learned_terrain(pc *p, int16_t y, int16_t x);
void pc_init_known_terrain(pc *p);
void pc_observe_terrain(pc *p, dungeon *d);
int32_t is_illuminated(pc *p, int16_t y, int16_t x);
void pc_reset_visibility(pc *p);
int pc_pickup_obj(pc *p, object *obj);
int pc_equip_obj(pc *p, int slot);
int pc_drop_obj(dungeon *d, int num);
int pc_dequip(dungeon *d, int num);
#endif
