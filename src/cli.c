#include <stdio.h>
#include <string.h>

#include "usart.h"
#include "wrapper.h"
#include "ringbuffer.h"
#include "cli.h"
#include "str2x.h"

/* handles */
static luat_rtos_task_handle task_cli_handle;

/* extern cli commands definition */
extern int32_t cli_num;
extern struct cli_command cli[];

//Input state
#define WAIT_NORMAL    0
#define WAIT_SPEC_KEY  1
#define WAIT_FUNC_KEY  2

/* state & control */
static char	cli_state = WAIT_NORMAL;
static int	recv_num = 0;
static char	recv_buf[MAX_BUF_LEN];
static int	current_history = 0;
static int	history_count = 0;
static char	cmd_history[MAX_HISTORY][MAX_BUF_LEN];
static const char back_str[] = {0x08, ' ', 0x08, 0};

//---------------------------------------------------------------------------------------------
#define clearInputBuf()	memset(recv_buf, 0, MAX_BUF_LEN)
#define printPrompt()	usart_print(CLI_PROMPT)

//---------------------------------------------------------------------------------------------
extern void Str2Lwr(char *str);

//---------------------------------------------------------------------------------------------
static void tabComplete(char *inbuf, int *bp)
{
	int i, n, m;
	char *fm = NULL;

	usart_print("\r\n");
	/* show matching commands */
	for (i = 0, n = 0, m = 0; i < cli_num && n < cli_num; i++){
		if(cli[i].name != NULL){
			if(!strncmp(inbuf, cli[i].name, *bp)){
				m++;
				if(m == 1)
					fm = cli[i].name;
				else if(m == 2){
					usart_print("%s ", fm);
					usart_print("%s ", cli[i].name);
				}else{
					usart_print("%s ", cli[i].name);
				}
			}
			n++;
		}
	}

	/* there's only one match, so complete the line */
	if(m == 1 && fm){
		n = strlen(fm) - *bp;
		if(*bp + n < MAX_BUF_LEN){
			memcpy(inbuf + *bp, fm + *bp, n);
			*bp += n;
			inbuf[(*bp)++] = ' ';
			inbuf[*bp] = '\0';
		}
	}
	if(m>1){
		usart_print("\r\n");
	}

	/* just redraw input line */
	usart_print("\033[2K\r");
	usart_print(CLI_PROMPT);
	usart_print("%s", inbuf);
}

//---------------------------------------------------------------------------------------------
static void pushHistory(void)
{
	if(recv_num != 0){
		/* push history */
		if(history_count >= MAX_HISTORY){
			/* move history */
			int index;
			for (index = 0; index < MAX_HISTORY - 1; index ++){
				memcpy(&cmd_history[index][0], &cmd_history[index + 1][0], MAX_BUF_LEN);
			}
			memset(&cmd_history[index][0], 0, MAX_BUF_LEN);
			memcpy(&cmd_history[index][0], recv_buf, recv_num);

			/* it's the maximum history */
			history_count = MAX_HISTORY;
		}
		else{
			memset(&cmd_history[history_count][0], 0, MAX_BUF_LEN);
			memcpy(&cmd_history[history_count][0], recv_buf, recv_num);

			/* increase count and set current history position */
			history_count ++;
		}
	}
	current_history = history_count;
}

//---------------------------------------------------------------------------------------------
static int cliGetInput(void)
{
	char ch;
	while (1){
		if(usart_getchar(&ch) == 0){
			DELAY(10);
			continue;
		}

		/*
		* handle control key
		* up key  : 0x1b 0x5b 0x41
		* down key: 0x1b 0x5b 0x42
		* right key:0x1b 0x5b 0x43
		* left key: 0x1b 0x5b 0x44
		*/
		recv_buf[recv_num] = ch;
		if(ch == 0x1b){
			cli_state = WAIT_SPEC_KEY;
			continue;
		}
		else if(cli_state == WAIT_SPEC_KEY){
			if(ch == 0x5b){
				cli_state = WAIT_FUNC_KEY;
				continue;
			}
			cli_state = WAIT_NORMAL;
		}
		else if(cli_state == WAIT_FUNC_KEY){
			cli_state = WAIT_NORMAL;
			if(ch == 0x41) /* up key */
			{
				/* prev history */
				if(current_history > 0)
					current_history --;
				else
				{
					current_history = 0;
					continue;
				}
				/* copy the history command */
				memcpy(recv_buf, &cmd_history[current_history][0], MAX_BUF_LEN);
				usart_print("\033[2K\r");
				usart_print(CLI_PROMPT);
				recv_num = usart_print("%s", recv_buf);
				continue;
			}
			else if(ch == 0x42){ /* down key */
				/* next history */
				if(current_history < history_count - 1)
					current_history ++;
				else{
					/* set to the end of history */
					if(history_count != 0)
						current_history = history_count - 1;
					else
						continue;
				}

				/* copy the history command */
				memcpy(recv_buf, &cmd_history[current_history][0], MAX_BUF_LEN);
				usart_print("\033[2K\r");
				usart_print(CLI_PROMPT);
				recv_num = usart_print("%s", recv_buf);
				continue;
			}
			else if(ch == 0x44){ /* left key */
				continue;
			}
			else if(ch == 0x43){ /* right key */
				continue;
			}
		}

		if((recv_buf[recv_num] == '\r') || (recv_buf[recv_num] == '\n')){	/* end of input line */
			recv_buf[recv_num] = '\0';
			if(strlen(recv_buf) != 0){
				pushHistory();
			}
			recv_num = 0;
			return 1;
		}

		if((recv_buf[recv_num] == 0x08) || /* backspace */(recv_buf[recv_num] == 0x7f)){ /* DEL */
			if(recv_num > 0)
			{
			  (recv_num)--;
				usart_print("%s", back_str);
				//usart_tx(0x08); usart_tx(' ');usart_tx(0x08);
			}
			continue;
		}

		if(recv_buf[recv_num] == '\t'){
			recv_buf[recv_num] = '\0';
			tabComplete(recv_buf, &recv_num);
			continue;
		}

		if(recv_buf[recv_num] >= 32){
			usart_print("%c", recv_buf[recv_num]);
			recv_num++;
		}

		if(recv_num >= MAX_BUF_LEN){
			usart_print("Error: input buffer overflow\r\n");
			usart_print(CLI_PROMPT);
			recv_num = 0;
			return 0;
		}
	}
}

//---------------------------------------------------------------------------------------------
static struct cli_command *lookupCommand(char *name)
{
	int i = 0;

	while (i < cli_num){
		if(!cli[i].name){
			i++;
			continue;
		}

		/* See if partial or full match is expected */
		if(!strcmp(cli[i].name, name))
			return &cli[i];

		i++;
	}
	return NULL;
}

//---------------------------------------------------------------------------------------------
static int handleInput(void)
{
	struct {
		unsigned inArg:1;
		unsigned inQuote:1;
		unsigned done:1;
	} stat;
	static char *argv[16];
	int argc = 0;
	int i = 0;
	struct cli_command* command;

	memset((void *)&argv, 0, sizeof(argv));
	memset(&stat, 0, sizeof(stat));

	/* Convert command string into lower case */
	Str2Lwr(recv_buf);

	/* Start parse into argc, argv */
	do {
		switch (recv_buf[i]){
			case '\0':
				if(stat.inQuote){
					return 2;
				}
				stat.done = 1;
				break;

			case '"':
				if(i > 0 && recv_buf[i - 1] == '\\' && stat.inArg){
					memcpy(&recv_buf[i - 1], &recv_buf[i],strlen(&recv_buf[i]) + 1);
					--i;
					break;
				}
				if(!stat.inQuote && stat.inArg)
					break;
				if(stat.inQuote && !stat.inArg)
					return 2;
				if(!stat.inQuote && !stat.inArg){
					stat.inArg = 1;
					stat.inQuote = 1;
					argc++;
					argv[argc - 1] = &recv_buf[i + 1];
				}
				else if(stat.inQuote && stat.inArg){
					stat.inArg = 0;
					stat.inQuote = 0;
					recv_buf[i] = '\0';
				}
				break;

			case ' ':
				if(i > 0 && recv_buf[i - 1] == '\\' && stat.inArg){
					memcpy(&recv_buf[i - 1], &recv_buf[i],
					       strlen(&recv_buf[i]) + 1);
					--i;
					break;
				}
				if(!stat.inQuote && stat.inArg){
					stat.inArg = 0;
					recv_buf[i] = '\0';
				}
				break;

			default:
				if(!stat.inArg){
					stat.inArg = 1;
					argc++;
					argv[argc - 1] = &recv_buf[i];
				}
				break;
		}
	}
	while (!stat.done && ++i < MAX_BUF_LEN);

	if(stat.inQuote)
		return 2;

	if(argc < 1){
		usart_print("\r\n");
		return 1;
	}

#if 0
	/*
	 * Some comamands can allow extensions like foo.a, foo.b and hence
	 * compare commands before first dot.
	 */
	i = ((p = strchr(argv[0], '.')) == NULL) ? 0 : (p - argv[0]);
	for(j = 0; j< argc; j++)
		usart_print("\r\nargv[%d] is %s\r\n", j, argv[j]);
#endif

	command = lookupCommand(argv[0]);
	if(command == NULL){
		usart_print("\r\nUnknown Command!\r\n");
		return 0;
	}

	usart_print("\r\n");
	command->function(argc, argv);

	return 1;
}

//---------------------------------------------------------------------------------------------
void CliPrintCmdList(void)
{
	int i;
	for(i = 0; i < cli_num; i++){
		usart_print("%s\t", cli[i].name);
		if(strlen(cli[i].name) < 8)
			usart_print("\t");
		usart_print("%s\r\n", cli[i].help);
	}
}

//---------------------------------------------------------------------------------------------
static void cli_main_routine(void *param)
{
	LUAT_DEBUG_PRINT("cli_main_routine start");

	char ch = 0;
	usart_print("\r\n!!! PRESS Ctrl-C FOR CLI !!!\r\n\r\n");

	while(true){
		if(usart_getchar(&ch) == 0){
			DELAY(100);
			continue;
		}
		if( ch == 3 )
			break;
	}

	usart_print("Command         Function \r\n");
	usart_print("---------------------------------------------------------------------\r\n");
	CliPrintCmdList();
	usart_print("\r\n");
	printPrompt();

	while(1){
		if(cliGetInput() == 1){
			handleInput();
			printPrompt();
			clearInputBuf();
		}
	}
}

void task_console(void)
{
    luat_rtos_task_create(&task_cli_handle, 4*1024, 10, "task_cli", cli_main_routine, NULL, 0);
}

void cli_deinit(void)
{
	luat_rtos_task_suspend(task_cli_handle);
	luat_rtos_task_delete(task_cli_handle);
}
