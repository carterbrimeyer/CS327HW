#ifndef IO_H
# define IO_H

class dungeon;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(dungeon *d);
void io_handle_input(dungeon *d);
void io_queue_message(const char *format, ...);
void io_show_inv(dungeon *d);
void io_show_eqp(dungeon *d);
int promptUserForInvSlot(dungeon *d);
int promptUserForEqpSlot(dungeon *d);
void display_desc(dungeon *d, int num);
int look_at_monster(dungeon *d);

#endif
