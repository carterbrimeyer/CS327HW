#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "dungeon.h"
#include "path.h"

# define rand_range(min, max) ((rand() % (((max) + 1) - (min))) + (min))

#define SetBit(data,y)    data |= (1 << y)


void usage(char *name)
{
  fprintf(stderr,
          "Usage: %s [-r|--rand <seed>] [-l|--load [<file>]]\n"
          "          [-s|--save [<file>]] [-i|--image <pgm file>]\n"
          "          [-n]--nummon <num>\n",
          name);

  exit(-1);
}

void initializeMonsters(dungeon_t *d, int num)
{
    int i;

    if(num > MONSTERS_MAX)
    {
        d->numMonsters = MONSTERS_MAX;
    }
    else if(num < 2)
    {
        d->numMonsters = num;
    }
    else
    {
        d->numMonsters = rand_range(2, MONSTERS_MAX);
    }



    for(i = 0; i < d->numMonsters; i++)
    {
        d->monsters[i].behavior = 0x00;
        if(rand_range(0, 1))
        {
            SetBit(d->monsters[i].behavior, 0);
        }
        if(rand_range(0, 1))
        {
            SetBit(d->monsters[i].behavior, 1);
        }
        if(rand_range(0, 1))
        {
            SetBit(d->monsters[i].behavior, 2);
        }
        if(rand_range(0, 1))
        {
            SetBit(d->monsters[i].behavior, 3);
        }

        d->monsters[i].speed = rand_range(5, 20);
        d->monsters[i].icon = bitToHex(d->monsters[i].behavior);


        int randRoom = rand_range(0, d->num_rooms - 1);

        d->monsters[i].position[dim_x] = (d->rooms[randRoom].position[dim_x] +
                                          (rand() % d->rooms[randRoom].size[dim_x]));
        d->monsters[i].position[dim_y] = (d->rooms[randRoom].position[dim_y] +
                                          (rand() % d->rooms[randRoom].size[dim_y]));
        while(d->pc.position[dim_x] == d->monsters[i].position[dim_x] && d->monsters[i].position[dim_y] == d->pc.position[dim_x]) {
            d->monsters[i].position[dim_x] = (d->rooms[randRoom].position[dim_x] +
                                              (rand() % d->rooms[randRoom].size[dim_x]));
            d->monsters[i].position[dim_y] = (d->rooms[randRoom].position[dim_y] +
                                              (rand() % d->rooms[randRoom].size[dim_y]));
        }

        d->monsters[i].prevTile = ter_floor_room;
        //printf("\nroom at %d, %d\n", d->rooms[randRoom].position[dim_x], d->rooms[randRoom].position[dim_y]);
        d->map[d->monsters[i].position[dim_y]][d->monsters[i].position[dim_x]] = ter_enemy;
    }
    //printf("\nNUM: %u\n", d->monsters[0].behavior);
}
int monsterLOS(dungeon_t *d, monster m)
{
    int i;
    bool los = true;
    for(i = -5; i < 5; i++)
    {
        if(m.position[dim_x] + i > 1 && m.position[dim_x] + i < DUNGEON_X )
        {
            if(d->map[m.position[dim_y]][m.position[dim_x] + i] == ter_floor || d->map[m.position[dim_y]][m.position[dim_x] + i] == ter_floor_room || d->map[m.position[dim_y]][m.position[dim_x] + i] == ter_floor_hall)
            {
                if(los && d->pc.position[dim_x] == m.position[dim_x] + i && d->pc.position[dim_y] == m.position[dim_y])
                {
                    return 1;
                }
            }
            else
            {
                los = false;
            }
        }
        if(m.position[dim_y] + i > 1 && m.position[dim_x] + i < DUNGEON_Y)
        {
            if(d->map[m.position[dim_y + i]][m.position[dim_x]] == ter_floor || d->map[m.position[dim_y + i]][m.position[dim_x] + i] == ter_floor_room || d->map[m.position[dim_y + i]][m.position[dim_x] + i] == ter_floor_hall)
            {
                if(los && d->pc.position[dim_x] == m.position[dim_x] && d->pc.position[dim_y] == m.position[dim_y] + i)
                {
                    return 1;
                }
            }
            else
            {
                los = false;
            }
        }
    }
    return 0;
}

void monsterMove(dungeon_t *d, monster m)
{
    //int j, k;

    bool move = false;
        /*bool intel = BitVal(m.behavior, 0) == 1,
                tele = BitVal(m.behavior, 1) == 1,
                tunnel = BitVal(m.behavior, 2) == 1,
                erratic = BitVal(m.behavior, 3) == 1;
        int x = m.position[dim_x], y = m.position[dim_y];*/
        pair_t goToLoc;
        /*if(erratic && rand_range(0, 1) == 1) {
            if(tunnel)
            {
                for(j = -1; j < 2; j++)
                {
                    for(k = -1; k < 2; k++)
                    {
                        if(d->map[y + j][x + k] != ter_wall_immutable && rand_range(0, 5) == 0)
                        {
                            goToLoc[dim_x] = x + k;
                            goToLoc[dim_y] = y + j;
                            move = true;
                        }
                    }
                }
            }
            else
            {
                for(j = -1; j < 2; j++)
                {
                    for(k = -1; k < 2; k++)
                    {
                        if((d->map[y + j][x + k] == ter_floor || d->map[y + j][x + k] == ter_floor_room || d->map[y + j][x + k] == ter_floor_hall) && rand_range(0, 5) == 0)
                        {
                            goToLoc[dim_x] = x + k;
                            goToLoc[dim_y] = y + j;
                            move = true;
                        }
                    }
                }

            }
        }
        else if(tele)
        {
            if(intel)
            {
                if(tunnel)
                {
                    int shortest = 254;
                    for(j = -1; j < 2; j++)
                    {
                        for(k = -1; k < 2; k++)
                        {
                            if(d->pc_tunnel[y + j][x + k] < shortest)
                            {
                                goToLoc[dim_x] = x + k;
                                goToLoc[dim_y] = y + j;
                                move = true;
                            }
                        }
                    }
                }
                else
                {
                    int shortest = 255;
                    for(j = -1; j < 2; j++)
                    {
                        for(k = -1; k < 2; k++)
                        {
                            if(d->pc_distance[y + j][x + k] < shortest) //&& d->map[y + j][x + k] != ter_wall)
                            {
                                //printf("\nMon at: %d, %d\nchecking %d, %d", m.position[dim_x], m.position[dim_y], x + k, y + j);
                                goToLoc[dim_x] = x + k;
                                goToLoc[dim_y] = y + j;
                                shortest = d->pc_distance[y + j][x + k];
                                move = true;
                            }
                        }
                        //printf("\nshortest: %d", shortest);
                    }
                }
            }
            else
            {
                int shortest = 254;
                for(j = -1; j < 2; j++)
                {
                    for(k = -1; k < 2; k++)
                    {
                        if((d->map[y + j][x + k] == ter_floor || d->map[y + j][x + k] == ter_floor_room || d->map[y + j][x + k] == ter_floor_hall) && d->pc_distance[y + j][x + k] <= shortest)
                        {
                            shortest = d->pc_distance[y + j][x + k];
                            goToLoc[dim_x] = x + k;
                            goToLoc[dim_y] = y + j;
                            move = true;
                            if(rand_range(0, 1) == 0)
                            {
                                j += 5;
                                k += 5;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if(monsterLOS(d, m))
            {
                if (intel) {
                    int shortest = 255;
                    for (j = -1; j < 2; j++) {
                        for (k = -1; k < 2; k++) {
                            if (d->pc_distance[y + j][x + k] < shortest) {
                                goToLoc[dim_x] = x + k;
                                goToLoc[dim_y] = y + j;
                                shortest = d->pc_distance[y + j][x + k];
                                move = true;
                            }
                        }
                    }
                }
            }
                else if(tunnel)
                {
                    if(d->pc.position[dim_y] < 10 + m.position[dim_y] && d->pc.position[dim_y] > m.position[dim_y] - 10 && d->pc.position[dim_x] < 10 + m.position[dim_x] && d->pc.position[dim_x] > m.position[dim_x] - 10 )
                    {
                        for(j = -1; j < 2; j++)
                        {
                            for(k = -1; k < 2; k++)
                            {
                                if(d->map[y + j][x + k] != ter_wall_immutable && rand_range(0, 5) == 0)
                                {
                                    goToLoc[dim_x] = x + k;
                                    goToLoc[dim_y] = y + j;
                                    move = true;
                                }
                            }
                        }
                    }
                }
                else if(monsterLOS(d, m))
                {
                    int shortest = 254;
                    for(j = -1; j < 2; j++)
                    {
                        for(k = -1; k < 2; k++)
                        {
                            if((d->map[y + j][x + k] == ter_floor || d->map[y + j][x + k] == ter_floor_room || d->map[y + j][x + k] == ter_floor_hall) && d->pc_distance[y + j][x + k] <= shortest)
                            {
                                shortest = d->pc_distance[y + j][x + k];
                                goToLoc[dim_x] = x + k;
                                goToLoc[dim_y] = y + j;
                                move = true;
                                if(rand_range(0, 1) == 0)
                                {
                                    j += 5;
                                    k += 5;
                                }
                            }
                        }
                    }
                }
        }*/
        goToLoc[dim_x] = 15;
        goToLoc[dim_y] = rand_range(2, 18);
        move = true;
        if(move)
        {
            d->map[m.position[dim_y]][m.position[dim_x]] = ter_floor;
            m.prevTile = d->map[goToLoc[dim_y]][goToLoc[dim_x]];

            m.position[dim_y] = goToLoc[dim_y];
            m.position[dim_x] = goToLoc[dim_x];

            d->map[goToLoc[dim_y]][goToLoc[dim_x]] = ter_enemy;
        }
}

int main(int argc, char *argv[])
{
  dungeon_t d;
  time_t seed;
  int numMon = 0;
  struct timeval tv;
  uint32_t i;
  uint32_t do_load, do_save, do_seed, do_image, do_save_seed, do_save_image;
  uint32_t long_arg;
  char *save_file;
  char *load_file;
  char *pgm_file;

  /* Quiet a false positive from valgrind. */
  memset(&d, 0, sizeof (d));
  
  /* Default behavior: Seed with the time, generate a new dungeon, *
   * and don't write to disk.                                      */
  do_load = do_save = do_image = do_save_seed = do_save_image = 0;
  do_seed = 1;
  save_file = load_file = NULL;

  /* The project spec requires '--load' and '--save'.  It's common  *
   * to have short and long forms of most switches (assuming you    *
   * don't run out of letters).  For now, we've got plenty.  Long   *
   * forms use whole words and take two dashes.  Short forms use an *
    * abbreviation after a single dash.  We'll add '--rand' (to     *
   * specify a random seed), which will take an argument of it's    *
   * own, and we'll add short forms for all three commands, '-l',   *
   * '-s', and '-r', respectively.  We're also going to allow an    *
   * optional argument to load to allow us to load non-default save *
   * files.  No means to save to non-default locations, however.    *
   * And the final switch, '--image', allows me to create a dungeon *
   * from a PGM image, so that I was able to create those more      *
   * interesting test dungeons for you.                             */
 
 if (argc > 1) {
    for (i = 1, long_arg = 0; i < argc; i++, long_arg = 0) {
      if (argv[i][0] == '-') { /* All switches start with a dash */
        if (argv[i][1] == '-') {
          argv[i]++;    /* Make the argument have a single dash so we can */
          long_arg = 1; /* handle long and short args at the same place.  */
        }
        switch (argv[i][1]) {
        case 'r':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-rand")) ||
              argc < ++i + 1 /* No more arguments */ ||
              !sscanf(argv[i], "%lu", &seed) /* Argument is not an integer */) {
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
            /* There is another argument, and it's not a switch, so *
             * we'll treat it as a save file and try to load it.    */
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
            /* There is another argument, and it's not a switch, so *
             * we'll save to it.  If it is "seed", we'll save to    *
	     * <the current seed>.rlg327.  If it is "image", we'll  *
	     * save to <the current image>.rlg327.                  */
	    if (!strcmp(argv[++i], "seed")) {
	      do_save_seed = 1;
	      do_save_image = 0;
	    } else if (!strcmp(argv[i], "image")) {
	      do_save_image = 1;
	      do_save_seed = 0;
	    } else {
	      save_file = argv[i];
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
            /* There is another argument, and it's not a switch, so *
             * we'll treat it as a save file and try to load it.    */
            pgm_file = argv[++i];
          }
          break;
            case 'n':
                if ((!long_arg && argv[i][2]) ||
                    (long_arg && strcmp(argv[i], "-nummon")) ||
                    argc < ++i + 1) {
                    numMon = atoi(argv[i + 1]);
                }
                break;
        default:
          usage(argv[0]);
        }
      } else { /* No dash */
        usage(argv[0]);
      }
    }
  }

  if (do_seed) {
    /* Allows me to generate more than one dungeon *
     * per second, as opposed to time().           */
    gettimeofday(&tv, NULL);
    seed = (tv.tv_usec ^ (tv.tv_sec << 20)) & 0xffffffff;
  }

  printf("Seed is %ld.\n", seed);
  srand(seed);

  init_dungeon(&d);

  if (do_load) {
    read_dungeon(&d, load_file);
  } else if (do_image) {
    read_pgm(&d, pgm_file);
  } else {
    gen_dungeon(&d);
  }

  if (!do_load) {
    /* Set a valid position for the PC */
    d.pc.position[dim_x] = (d.rooms[0].position[dim_x] +
                            (rand() % d.rooms[0].size[dim_x]));
    d.pc.position[dim_y] = (d.rooms[0].position[dim_y] +
                            (rand() % d.rooms[0].size[dim_y]));
  }

  printf("PC is at (y, x): %d, %d\n",
         d.pc.position[dim_y], d.pc.position[dim_x]);

  render_dungeon(&d);

  dijkstra(&d);
  dijkstra_tunnel(&d);
  //render_distance_map(&d);
  //render_tunnel_distance_map(&d);
  //render_hardness_map(&d);
  //render_movement_cost_map(&d);

  if (do_save) {
    if (do_save_seed) {
       /* 10 bytes for number, plus dot, extention and null terminator. */
      save_file = malloc(18);
      sprintf(save_file, "%ld.rlg327", seed);
    }
    if (do_save_image) {
      if (!pgm_file) {
	fprintf(stderr, "No image file was loaded.  Using default.\n");
	do_save_image = 0;
      } else {
	/* Extension of 3 characters longer than image extension + null. */
	save_file = malloc(strlen(pgm_file) + 4);
	strcpy(save_file, pgm_file);
	strcpy(strchr(save_file, '.') + 1, "rlg327");
      }
    }
    write_dungeon(&d, save_file);

    if (do_save_seed || do_save_image) {
      free(save_file);
    }
  }

  initializeMonsters(&d, numMon);


  while(true)
  {
      for(i = 0; i < d.numMonsters; i++)
      {
          monsterMove(&d, d.monsters[i]);
          //printf("\n!\n");
      }

      //render_distance_map(&d);
      render_dungeon(&d);
      //
      usleep(250000);

  }


  delete_dungeon(&d);

  return 0;
}
