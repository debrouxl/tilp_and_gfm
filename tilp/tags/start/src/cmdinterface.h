#ifndef __CMDINTERFACE__
#define __CMDINTERFACE__

extern int cmdState;
extern int progBar;

extern void cmd_update_progbar(int size);
extern void cmd_link_progress(int type, char *name, int size);
extern void enter_command(void);

#endif
