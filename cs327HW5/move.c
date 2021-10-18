#include "move.h"

#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include "dungeon.h"
#include "heap.h"
#include "move.h"
#include "npc.h"
#include "pc.h"
#include "character.h"
#include "utils.h"
#include "path.h"
#include "event.h"

WINDOW *monsterMenu;

void do_combat(dungeon_t *d, character_t *atk, character_t *def) {
    if (def->alive) {
        def->alive = 0;
        if (def != &d->pc) {
            d->num_monsters--;
        }
        atk->kills[kill_direct]++;
        atk->kills[kill_avenged] += (def->kills[kill_direct] +
                                     def->kills[kill_avenged]);
    }
}

void move_character(dungeon_t *d, character_t *c, pair_t next) {
    if (charpair(next) &&
        ((next[dim_y] != c->position[dim_y]) ||
         (next[dim_x] != c->position[dim_x]))) {
        do_combat(d, c, charpair(next));
    } else {
        /* No character in new position. */

        d->character[c->position[dim_y]][c->position[dim_x]] = NULL;
        c->position[dim_y] = next[dim_y];
        c->position[dim_x] = next[dim_x];
        d->character[c->position[dim_y]][c->position[dim_x]] = c;
    }
}

void do_moves(dungeon_t *d) {
    pair_t next;
    character_t *c;
    event_t *e;

    /* Remove the PC when it is PC turn.  Replace on next call.  This allows *
     * use to completely uninit the heap when generating a new level without *
     * worrying about deleting the PC.                                       */

    if (pc_is_alive(d)) {
        /* The PC always goes first one a tie, so we don't use new_event().  *
         * We generate one manually so that we can set the PC sequence       *
         * number to zero.                                                   */
        e = malloc(sizeof(*e));
        e->type = event_character_turn;
        /* Hack: New dungeons are marked.  Unmark and ensure PC goes at d->time, *
         * otherwise, monsters get a turn before the PC.                         */
        if (d->is_new) {
            d->is_new = 0;
            e->time = d->time;
        } else {
            e->time = d->time + (1000 / d->pc.speed);
        }
        e->sequence = 0;
        e->c = &d->pc;
        heap_insert(&d->events, e);
    }

    while (pc_is_alive(d) &&
           (e = heap_remove_min(&d->events)) &&
           ((e->type != event_character_turn) || (e->c != &d->pc))) {
        d->time = e->time;
        if (e->type == event_character_turn) {
            c = e->c;
        }
        if (!c->alive) {
            if (d->character[c->position[dim_y]][c->position[dim_x]] == c) {
                d->character[c->position[dim_y]][c->position[dim_x]] = NULL;
            }
            if (c != &d->pc) {
                event_delete(e);
            }
            continue;
        }

        npc_next_pos(d, c, next);
        move_character(d, c, next);

        heap_insert(&d->events, update_event(d, e, 1000 / c->speed));
    }
    bool moving = false;
    bool inMenu = false;
    int i, j;
    character_t *last = NULL;


    pair_t pcMove;
    while (!moving) {
        int32_t keypress = getch();
        switch (keypress) {
            case 'q':
            case 'Q':
                d->exit = true;
                moving = true;
                break;
            case 'y':
            case '7':
                //UPPER LEFT
                pcMove[dim_x] = d->pc.position[dim_x] - 1;
                pcMove[dim_y] = d->pc.position[dim_y] - 1;
                moving = true;
                break;
            case 'k':
            case '8':
                //UP
                pcMove[dim_x] = d->pc.position[dim_x];
                pcMove[dim_y] = d->pc.position[dim_y] - 1;
                moving = true;
                break;
            case 'u':
            case '9':
                //UPPER RIGHT
                pcMove[dim_x] = d->pc.position[dim_x] + 1;
                pcMove[dim_y] = d->pc.position[dim_y] - 1;
                moving = true;
                break;
            case 'l':
            case '6':
                //RIGHT
                pcMove[dim_x] = d->pc.position[dim_x] + 1;
                pcMove[dim_y] = d->pc.position[dim_y];
                moving = true;
                break;
            case 'n':
            case '3':
                //LOWER RIGHT
                pcMove[dim_x] = d->pc.position[dim_x] + 1;
                pcMove[dim_y] = d->pc.position[dim_y] + 1;
                moving = true;
                break;
            case 'j':
            case '2':
                //DOWN
                pcMove[dim_x] = d->pc.position[dim_x];
                pcMove[dim_y] = d->pc.position[dim_y] + 1;
                moving = true;
                break;
            case 'b':
            case '1':
                //LOWER LEFT
                pcMove[dim_x] = d->pc.position[dim_x] - 1;
                pcMove[dim_y] = d->pc.position[dim_y] + 1;
                moving = true;
                break;
            case 'h':
            case '4':
                //LEFT
                pcMove[dim_x] = d->pc.position[dim_x] - 1;
                pcMove[dim_y] = d->pc.position[dim_y];
                moving = true;
                break;
            case '>':
                //DOWN STAIRS
                if (mappair(d->pc.position) == ter_stairs_down) {
                    move(23, 0);
                    clrtoeol();
                    delete_dungeon(d);
                    init_dungeon(d);
                    gen_dungeon(d);
                    config_pc(d);
                    gen_monsters(d);
                    render_dungeon(d);
                }
                moving = false;
                break;
            case '<':
                //UP STAIRS
                if (mappair(d->pc.position) == ter_stairs_up) {
                    move(23, 0);
                    clrtoeol();
                    mvprintw(23, 1, "UP!");
                    delete_dungeon(d);
                    init_dungeon(d);
                    gen_dungeon(d);
                    config_pc(d);
                    gen_monsters(d);
                    render_dungeon(d);
                }
                moving = false;
                break;
            case ' ':
            case '.':
            case '5':
                //DO NOTHING
                pcMove[dim_x] = d->pc.position[dim_x];
                pcMove[dim_y] = d->pc.position[dim_y];
                moving = true;
                break;
            case 'm':
                //LIST MONSTERS

                inMenu = true;
                monsterMenu = newwin(21, 50, 0, 15);
                box(monsterMenu, 0, 0);
                int ySpacing = 1;
                for(i = 0; i < DUNGEON_Y; i++)
                {
                    for(j = 0; j < DUNGEON_X; j++)
                    {
                        if(d->character[i][j] != NULL && d->character[i][j]->symbol != d->pc.symbol && ySpacing < 20)
                        {
                            mvwprintw(monsterMenu, ySpacing, 15, "Monster %c at (%d, %d).  ",
                                      d->character[i][j]->symbol, d->character[i][j]->position[dim_x], d->character[i][j]->position[dim_y]);
                            ySpacing++;
                        }
                    }
                }
                for(; ySpacing < 20; ySpacing++) {
                    mvwprintw(monsterMenu, ySpacing, 15, "--------------------- ");
                }

                int loc = 1;

                wrefresh(monsterMenu);
                while (inMenu) {
                    keypress = getch();
                    switch (keypress) {
                        case KEY_UP:
                            if(loc >= 0)
                            {
                                loc--;
                                ySpacing = 1;
                                int num = 0;
                                for(i = 0; i < DUNGEON_Y; i++)
                                {
                                    for(j = 0; j < DUNGEON_X; j++)
                                    {
                                        if(d->character[i][j] != NULL && d->character[i][j]->symbol != d->pc.symbol && ySpacing < 20 && last->position != d->character[i][j]->position)
                                        {
                                            if(num > loc)
                                            {
                                                wmove(monsterMenu, ySpacing, 0);

                                                last = d->character[i][j];
                                                mvwprintw(monsterMenu, ySpacing, 15, "Monster %c at (%d, %d).  ",
                                                          d->character[i][j]->symbol, d->character[i][j]->position[dim_x], d->character[i][j]->position[dim_y]);
                                                ySpacing++;
                                            }
                                            num++;
                                        }
                                    }
                                }
                                for(; ySpacing < 20; ySpacing++) {
                                    mvwprintw(monsterMenu, ySpacing, 15, "--------------------- ");
                                }
                                wrefresh(monsterMenu);
                            }
                            break;
                        case KEY_DOWN:
                            if(loc < d->num_monsters)
                            {
                                loc++;
                                ySpacing = 1;
                                int num = 0;
                                for(i = 0; i < DUNGEON_Y; i++)
                                {
                                    for(j = 0; j < DUNGEON_X; j++)
                                    {
                                        if(d->character[i][j] != NULL && d->character[i][j]->symbol != d->pc.symbol && ySpacing < 20 && last->position != d->character[i][j]->position)
                                        {
                                            if(num > loc)
                                            {
                                                wmove(monsterMenu, ySpacing, 0);

                                                last = d->character[i][j];
                                                mvwprintw(monsterMenu, ySpacing, 15, "Monster %c at (%d, %d).  ",
                                                          d->character[i][j]->symbol, d->character[i][j]->position[dim_x], d->character[i][j]->position[dim_y]);
                                                ySpacing++;
                                            }
                                            num++;
                                        }
                                    }
                                }
                                    for(; ySpacing < 20; ySpacing++) {
                                        mvwprintw(monsterMenu, ySpacing, 15, "--------------------- ");
                                    }
                                wrefresh(monsterMenu);
                            }
                            break;
                        case 27: //ESC
                            delwin(monsterMenu);
                            render_dungeon(d);
                            refresh();
                            inMenu = false;
                            break;
                        default:
                            inMenu = true;
                            break;
                    }
                }
                moving = false;
                break;
            default:
                moving = false;
                move(23, 0);
                clrtoeol();
                mvprintw(23, 1, "Unknown key detected! (%o)", keypress);
                break;
        }
    }

    if (pc_is_alive(d) && e->c == &d->pc && moving) {
        c = e->c;
        d->time = e->time;
        /* Kind of kludgey, but because the PC is never in the queue when   *
         * we are outside of this function, the PC event has to get deleted *
         * and recreated every time we leave and re-enter this function.    */
        e->c = NULL;
        event_delete(e);
        //pc_next_pos(d, next);
        if (mappair(pcMove) != ter_wall && mappair(pcMove) != ter_wall_immutable) {
            move_character(d, c, pcMove);
            update_ui(d);
        } else {
            move(23, 0);
            clrtoeol();
            mvprintw(23, 1, "Invalid move!");
        }


        dijkstra(d);
        dijkstra_tunnel(d);
    }
}

void dir_nearest_wall(dungeon_t *d, character_t *c, pair_t dir) {
    dir[dim_x] = dir[dim_y] = 0;

    if (c->position[dim_x] != 1 && c->position[dim_x] != DUNGEON_X - 2) {
        dir[dim_x] = (c->position[dim_x] > DUNGEON_X - c->position[dim_x] ? 1 : -1);
    }
    if (c->position[dim_y] != 1 && c->position[dim_y] != DUNGEON_Y - 2) {
        dir[dim_y] = (c->position[dim_y] > DUNGEON_Y - c->position[dim_y] ? 1 : -1);
    }
}

uint32_t against_wall(dungeon_t *d, character_t *c) {
    return ((mapxy(c->position[dim_x] - 1,
                   c->position[dim_y]) == ter_wall_immutable) ||
            (mapxy(c->position[dim_x] + 1,
                   c->position[dim_y]) == ter_wall_immutable) ||
            (mapxy(c->position[dim_x],
                   c->position[dim_y] - 1) == ter_wall_immutable) ||
            (mapxy(c->position[dim_x],
                   c->position[dim_y] + 1) == ter_wall_immutable));
}

uint32_t in_corner(dungeon_t *d, character_t *c) {
    uint32_t num_immutable;

    num_immutable = 0;

    num_immutable += (mapxy(c->position[dim_x] - 1,
                            c->position[dim_y]) == ter_wall_immutable);
    num_immutable += (mapxy(c->position[dim_x] + 1,
                            c->position[dim_y]) == ter_wall_immutable);
    num_immutable += (mapxy(c->position[dim_x],
                            c->position[dim_y] - 1) == ter_wall_immutable);
    num_immutable += (mapxy(c->position[dim_x],
                            c->position[dim_y] + 1) == ter_wall_immutable);

    return num_immutable > 1;
}
