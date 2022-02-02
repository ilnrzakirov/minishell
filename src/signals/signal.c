
#include "../../includes/minishell.h"

void    sigint_func(int sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
        rl_redisplay();
        write(2, "  \n", 3);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void    sigquit(int sig)
{
    (void)sig;
    printf("Quit: %d\n", sig);
}

void    sigint_proc(int sig)
{
    if (sig == SIGINT)
    {
        write(2, "\n", 1);
    }
}

void    init_signal_chaild(t_data *data)
{
    if (signal(SIGQUIT, sigquit))
        data->exit_code = 131;
    if (signal(SIGINT, sigint_proc))
        data->exit_code = 1;
}

void    init_signal_h(t_data *data)
{
    if (signal(SIGQUIT, SIG_IGN))
        data->exit_code = 1;
    signal(SIGINT, sigint_func);
}