#ifndef  __CLI_H_
#define	 __CLI_H_

#define CLI_PROMPT		"WWJ>"
#define	MAX_COMMANDS	30
#define	MAX_BUF_LEN		64
#define	MAX_HISTORY		8

struct cli_command {
	/** The name of the CLI command */
	char *name;
	/** The help text associated with the command */
	char *help;
	/** The function that should be invoked for this command. */
	void (*function) (int argc, char **argv);
};

extern luat_rtos_task_handle task_cli_handle;

/* User func */
void CliPrintCmdList(void);

#endif

