#ifndef DESCRIPTIONS_H
# define DESCRIPTIONS_H

# include <stdint.h>

# undef swap

# include <vector>
# include <string>
#include "npc.h"

typedef struct dungeon dungeon_t;

uint32_t parse_descriptions(dungeon_t *d);

uint32_t print_descriptions(dungeon_t *d);

uint32_t destroy_descriptions(dungeon_t *d);


typedef enum object_type {
    objtype_no_type,
    objtype_WEAPON,
    objtype_OFFHAND,
    objtype_RANGED,
    objtype_LIGHT,
    objtype_ARMOR,
    objtype_HELMET,
    objtype_CLOAK,
    objtype_GLOVES,
    objtype_BOOTS,
    objtype_AMULET,
    objtype_RING,
    objtype_SCROLL,
    objtype_BOOK,
    objtype_FLASK,
    objtype_GOLD,
    objtype_AMMUNITION,
    objtype_FOOD,
    objtype_WAND,
    objtype_CONTAINER
} object_type_t;
class items {
public:
    std::string name, description;
    object_type_t type;
    uint32_t color;
    dice hit, damage, dodge, defence, weight, speed, attribute, value;
    bool artifact;
    uint32_t rarity;
    int descID = -3;
    pair_t position;
    char getSymbol()
    {
        switch(type)
        {
            case objtype_WEAPON:
                return '|';
            case objtype_OFFHAND:
                return ')';
            case objtype_RANGED:
                return '}';
            case objtype_ARMOR:
                return '[';
            case objtype_HELMET:
                return ']';
            case objtype_CLOAK:
                return '(';
            case objtype_GLOVES:
                return '{';
            case objtype_BOOTS:
                return '\\';
            case objtype_RING:
                return '=';
            case objtype_AMULET:
                return '"';
            case objtype_LIGHT:
                return '_';
            case objtype_SCROLL:
                return '~';
            case objtype_BOOK:
                return '?';
            case objtype_FLASK:
                return '!';
            case objtype_GOLD:
                return '$';
            case objtype_AMMUNITION:
                return '/';
            case objtype_FOOD:
                return ',';
            case objtype_WAND:
                return'-';
            case objtype_CONTAINER:
                return '%';
            default:
                return '*';
        }
    }
};
extern const char object_symbol[];

class monster_description {
public:
    bool inDungeon = false;
    std::string name, description;
    char symbol;
    std::vector<uint32_t> color;
    uint32_t abilities;
    dice speed, hitpoints, damage;
    uint32_t rarity;

    monster_description() : name(), description(), symbol(0), color(0),
                            abilities(0), speed(), hitpoints(), damage(),
                            rarity(0) {
    }

    void set(const std::string &name,
             const std::string &description,
             const char symbol,
             const std::vector<uint32_t> &color,
             const dice &speed,
             const uint32_t abilities,
             const dice &hitpoints,
             const dice &damage,
             const uint32_t rarity);

    std::ostream &print(std::ostream &o);

    npc *getAsNPC() {
        npc *c = new npc;
        c->name = name;
        c->damage = damage;
        c->symbol = symbol;
        c->description = description;
        c->color = color;
        c->hitpoints = hitpoints;
        c->rarity = rarity;
        c->abilities = abilities;
        c->speed = speed;
        return c;
    }
};

class object_description {

public:
    bool inDungeon = false;
    std::string name, description;
    object_type_t type;
    uint32_t color;
    dice hit, damage, dodge, defence, weight, speed, attribute, value;
    bool artifact;
    uint32_t rarity;



    object_description() : name(), description(), type(objtype_no_type),
                           color(0), hit(), damage(),
                           dodge(), defence(), weight(),
                           speed(), attribute(), value(),
                           artifact(false), rarity(0) {
    }

    void set(const std::string &name,
             const std::string &description,
             const object_type_t type,
             const uint32_t color,
             const dice &hit,
             const dice &damage,
             const dice &dodge,
             const dice &defence,
             const dice &weight,
             const dice &speed,
             const dice &attrubute,
             const dice &value,
             const bool artifact,
             const uint32_t rarity);

    std::ostream &print(std::ostream &o);

    /* Need all these accessors because otherwise there is a *
     * circular dependancy that is difficult to get around.  */


    inline const std::string &get_name() const { return name; }

    inline const std::string &get_description() const { return description; }

    inline const object_type_t get_type() const { return type; }

    inline const uint32_t get_color() const { return color; }

    inline const dice &get_hit() const { return hit; }

    inline const dice &get_damage() const { return damage; }

    inline const dice &get_dodge() const { return dodge; }

    inline const dice &get_defence() const { return defence; }

    inline const dice &get_weight() const { return weight; }

    inline const dice &get_speed() const { return speed; }

    inline const dice &get_attribute() const { return attribute; }

    inline const dice &get_value() const { return value; }

    items *getAsObj() {
        items *o = new items;
        o->name = get_name();
        o->description = get_description();
        o->type = get_type();
        o->color = get_color();
        o-> hit = get_hit();
        o->damage = get_damage();
        o->dodge = get_dodge();
        o->defence = get_defence();
        o->weight = get_weight();
        o->speed = get_speed();
        o->attribute = get_attribute();
        o->value = get_value();
        o->artifact = artifact;
        o->rarity = rarity;
        return o;
    }
};

std::ostream &operator<<(std::ostream &o, monster_description &m);

std::ostream &operator<<(std::ostream &o, object_description &od);

#endif
