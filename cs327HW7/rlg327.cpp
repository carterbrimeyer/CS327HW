#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "dungeon.h"
#include "pc.h"
#include "npc.h"
#include "move.h"
#include "utils.h"
#include "io.h"

const char *victory =
        "\n                                       o\n"
        "                                      $\"\"$o\n"
        "                                     $\"  $$\n"
        "                                      $$$$\n"
        "                                      o \"$o\n"
        "                                     o\"  \"$\n"
        "                oo\"$$$\"  oo$\"$ooo   o$    \"$    ooo\"$oo  $$$\"o\n"
        "   o o o o    oo\"  o\"      \"o    $$o$\"     o o$\"\"  o$      \"$  "
        "\"oo   o o o o\n"
        "   \"$o   \"\"$$$\"   $$         $      \"   o   \"\"    o\"         $"
        "   \"o$$\"    o$$\n"
        "     \"\"o       o  $          $\"       $$$$$       o          $  ooo"
        "     o\"\"\n"
        "        \"o   $$$$o $o       o$        $$$$$\"       $o        \" $$$$"
        "   o\"\n"
        "         \"\"o $$$$o  oo o  o$\"         $$$$$\"        \"o o o o\"  "
        "\"$$$  $\n"
        "           \"\" \"$\"     \"\"\"\"\"            \"\"$\"            \""
        "\"\"      \"\"\" \"\n"
        "            \"oooooooooooooooooooooooooooooooooooooooooooooooooooooo$\n"
        "             \"$$$$\"$$$$\" $$$$$$$\"$$$$$$ \" \"$$$$$\"$$$$$$\"  $$$\""
        "\"$$$$\n"
        "              $$$oo$$$$   $$$$$$o$$$$$$o\" $$$$$$$$$$$$$$ o$$$$o$$$\"\n"
        "              $\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""
        "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"$\n"
        "              $\"                                                 \"$\n"
        "              $\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\""
        "$\"$\"$\"$\"$\"$\"$\"$\n"
        "                                   You win!\n\n";

const char *tombstone =
        "\n\n\n\n                /\"\"\"\"\"/\"\"\"\"\"\"\".\n"
        "               /     /         \\             __\n"
        "              /     /           \\            ||\n"
        "             /____ /   Rest in   \\           ||\n"
        "            |     |    Pieces     |          ||\n"
        "            |     |               |          ||\n"
        "            |     |   A. Luser    |          ||\n"
        "            |     |               |          ||\n"
        "            |     |     * *   * * |         _||_\n"
        "            |     |     *\\/* *\\/* |        | TT |\n"
        "            |     |     *_\\_  /   ...\"\"\"\"\"\"| |"
        "| |.\"\"....\"\"\"\"\"\"\"\".\"\"\n"
        "            |     |         \\/..\"\"\"\"\"...\"\"\""
        "\\ || /.\"\"\".......\"\"\"\"...\n"
        "            |     |....\"\"\"\"\"\"\"........\"\"\"\"\""
        "\"^^^^\".......\"\"\"\"\"\"\"\"..\"\n"
        "            |......\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"......"
        "..\"\"\"\"\"....\"\"\"\"\"..\"\"...\"\"\".\n\n"
        "            You're dead.  Better luck in the next life.\n\n\n";

void usage(char *name) {
    fprintf(stderr,
            "Usage: %s [-r|--rand <seed>] [-l|--load [<file>]]\n"
            "          [-s|--save [<file>]] [-i|--image <pgm file>]\n"
            "          [-n|--nummon <count>]\n",
            name);

    exit(-1);
}

int main(int argc, char *argv[]) {
    dungeon d;
    time_t seed;
    struct timeval tv;
    int32_t i;
    uint32_t do_load, do_save, do_seed, do_image, do_save_seed, do_save_image;
    uint32_t long_arg;
    //char *save_file;
    char *load_file;
    char *pgm_file;
    //memset(&d, 0, sizeof(d));
    //printf("hi");
    //init_dungeon(&d);
    //gen_dungeon(&d);

    //printf("-----------------------------------\n%s\n", d.md->name);

    //printf("THE DESCRIPTION:\n%s", d.desc_stats[0].desc);
     // comment out of main program
    do_load = do_save = do_image = do_save_seed = do_save_image = 0;
    do_seed = 1;
    //save_file = load_file = NULL;
    d.max_monsters = MAX_MONSTERS;

    if (argc > 1) {
        for (i = 1, long_arg = 0; i < argc; i++, long_arg = 0) {
            if (argv[i][0] == '-') {
                if (argv[i][1] == '-') {
                    argv[i]++;
                    long_arg = 1;
                }
                switch (argv[i][1]) {
                    case 'n':
                        if ((!long_arg && argv[i][2]) ||
                            (long_arg && strcmp(argv[i], "-nummon")) ||
                            argc < ++i + 1 ||
                            !sscanf(argv[i], "%hu", &d.max_monsters)) {
                            usage(argv[0]);
                        }
                        break;
                    case 'r':
                        if ((!long_arg && argv[i][2]) ||
                            (long_arg && strcmp(argv[i], "-rand")) ||
                            argc < ++i + 1  ||
                            !sscanf(argv[i], "%lu", &seed)) {
                            usage(argv[0]);
                        }
                        do_seed = 0;
                        break;
                    case 'l':
                        if ((!long_arg && argv[i][2]) ||
                            (long_arg && strcmp(argv[i], "-load"))) {
                            usage(argv[0]);
                        }
                        do_load = 1;
                        if ((argc > i + 1) && argv[i + 1][0] != '-') {
                            load_file = argv[++i];
                        }
                        break;
                    case 's':
                        if ((!long_arg && argv[i][2]) ||
                            (long_arg && strcmp(argv[i], "-save"))) {
                            usage(argv[0]);
                        }
                        do_save = 1;
                        if ((argc > i + 1) && argv[i + 1][0] != '-') {
                            if (!strcmp(argv[++i], "seed")) {
                                do_save_seed = 1;
                                do_save_image = 0;
                            } else if (!strcmp(argv[i], "image")) {
                                do_save_image = 1;
                                do_save_seed = 0;
                            } else {
                                //save_file = argv[i];
                            }
                        }
                        break;
                    case 'i':
                        if ((!long_arg && argv[i][2]) ||
                            (long_arg && strcmp(argv[i], "-image"))) {
                            usage(argv[0]);
                        }
                        do_image = 1;
                        if ((argc > i + 1) && argv[i + 1][0] != '-') {
                            pgm_file = argv[++i];
                        }
                        break;
                    default:
                        usage(argv[0]);
                }
            } else {
                usage(argv[0]);
            }
        }
    }

    if (do_seed) {
        gettimeofday(&tv, NULL);
        seed = (tv.tv_usec ^ (tv.tv_sec << 20)) & 0xffffffff;
    }

    srand(seed);

    //io_init_terminal();
    init_dungeon(&d);

    if (do_load) {
        read_dungeon(&d, load_file);
    } else if (do_image) {
        read_pgm(&d, pgm_file);
    } else {
        gen_dungeon(&d);
    }

    //config_pc(&d);
    //gen_monsters(&d);
    /*
    io_display(&d);
    if (!do_load && !do_image) {
        io_queue_message("Seed is %u.", seed);
    }
    while (pc_is_alive(&d) && dungeon_has_npcs(&d) && !d.quit) {
        do_moves(&d);
    }
    io_display(&d);

    io_reset_terminal();

    if (do_save) {
        if (do_save_seed) {
            save_file = (char *) malloc(18);
            sprintf(save_file, "%ld.rlg327", seed);
        }
        if (do_save_image) {
            if (!pgm_file) {
                fprintf(stderr, "No image file was loaded.  Using default.\n");
                do_save_image = 0;
            } else {
                save_file = (char *) malloc(strlen(pgm_file) + 4);
                strcpy(save_file, pgm_file);
                strcpy(strchr(save_file, '.') + 1, "rlg327");
            }
        }
        write_dungeon(&d, save_file);

        if (do_save_seed || do_save_image) {
            free(save_file);
        }
    }

    printf("%s", pc_is_alive(&d) ? victory : tombstone);
    printf("You defended your life in the face of %u deadly beasts.\n"
           "You avenged the cruel and untimely murders of %u "
           "peaceful dungeon residents.\n",
           d.PC->kills[kill_direct], d.PC->kills[kill_avenged]);

    if (pc_is_alive(&d)) {
        character_delete(d.PC);
    }
    */
    //Disabled nCurses io to easier display file contents.

    read_monster_desc_to_dungeon(&d);
    printf("========MONSTER DESCRIPTIONS========\n");
    for(int u = 0; u < d.num_mons_desc; u++) {
        printf("Name: %s\n"
               "Symbol: %c\n"
               "Description:\n%s\n"
               "Speed Stats: %d + %d d %d\n"
               "HP Stats: %d + %d d %d\n"
               "Damage Stats: %d + %d d %d\n"
               "Rarity: %d\n"
               "Colors: %s\n"
               "Abilities Number: %d\n\n"
               "---------------------------------------------------\n", d.md[u].name, d.md[u].symbol, d.md[u].desc,
               d.md[u].speed.base, d.md[u].speed.dice, d.md[u].speed.sides,
               d.md[u].hp.base, d.md[u].hp.dice, d.md[u].hp.sides,
               d.md[u].attack_damage.base, d.md[u].attack_damage.dice, d.md[u].attack_damage.sides, d.md[u].rarity, d.md[u].colors,
               d.md[u].ability);
    }
    read_objects_desc_to_dungeon(&d);
    printf("========OBJECT DESCRIPTIONS========\n");
    for(int u = 0; u < d.num_objs_desc; u++) {
        printf("Name: %s\n"
               "Description:\n%s\n"
               "Speed Stats: %d + %d d %d\n"
               "Hit Stats: %d + %d d %d\n"
               "Damage Stats: %d + %d d %d\n"
               "Rarity: %d\n"
               "Colors: %s\n"
               "Weight: %d + %d d %d\n"
               "Value: %d + %d d %d\n"
               "Dodge: %d + %d d %d\n"
               "Defense: %d + %d d %d\n"
               "Attr: %d + %d d %d\n"
               "Art: %u\n"
               "---------------------------------------------------\n", d.od[u].name, d.od[u].desc,
               d.od[u].speed.base, d.od[u].speed.dice, d.od[u].speed.sides,
               d.od[u].hit.base, d.od[u].hit.dice, d.od[u].hit.sides,
               d.od[u].dam.base, d.od[u].dam.dice, d.od[u].dam.sides,
               d.od[u].rarity, d.od[u].colors,
               d.od[u].weight.base, d.od[u].weight.dice, d.od[u].weight.sides,
               d.od[u].val.base, d.od[u].val.dice, d.od[u].val.sides,
               d.od[u].dodge.base, d.od[u].dodge.dice, d.od[u].dodge.sides,
               d.od[u].def.base, d.od[u].def.dice, d.od[u].def.sides,
               d.od[u].attr.base, d.od[u].attr.dice, d.od[u].attr.sides, d.od[u].art);
    }
    printf("======== DONE ! ========\n");
    delete_dungeon(&d);

    return 0;
}
