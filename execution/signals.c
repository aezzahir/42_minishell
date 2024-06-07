// #include "../minishell.h"
// #include <signal.h>

// // Function to convert integer to string
// char *itoa(int num)
// {
//     int len = snprintf(NULL, 0, "%d", num);
//     char *str = (char *)malloc(len + 1);
//     if (str)
//     {
//         snprintf(str, len + 1, "%d", num);
//     }
//     return str;
// }

// // Signal initialization function
// void sig_init(t_signal_context *context)
// {
//     context->sigint = 0;
//     context->sigquit = 0;
//     context->pid = 0;
//     context->exit_status = 0;
// }

// // Signal handler for SIGINT
// void handle_sigint(int sig, siginfo_t *info, void *ucontext)
// {
//     (void)ucontext; // Mark ucontext as unused
//     t_signal_context *context = (t_signal_context *)info->si_value.sival_ptr;
//     (void)sig;
//     if (context->pid == 0)
//     {
//         write(STDERR_FILENO, "\b\b  ", 4);
//         write(STDERR_FILENO, "\n", 1);
//         write(STDERR_FILENO, "\033[0;36m\033[1m🤬 minishell ▸ \033[0m", 35);
//         context->exit_status = 1;
//     }
//     else
//     {
//         write(STDERR_FILENO, "\n", 1);
//         context->exit_status = 130;
//     }
//     context->sigint = 1;
// }

// // Signal handler for SIGQUIT
// void handle_sigquit(int sig, siginfo_t *info, void *ucontext)
// {
//     (void)ucontext; // Mark ucontext as unused
//     t_signal_context *context = (t_signal_context *)info->si_value.sival_ptr;
//     char *nbr;

//     nbr = itoa(sig);
//     if (nbr == NULL)
//     {
//         write(STDERR_FILENO, "Memory allocation error\n", 24);
//         return;
//     }

//     if (context->pid != 0)
//     {
//         write(STDERR_FILENO, "Quit: ", 6);
//         write(STDERR_FILENO, nbr, strlen(nbr));
//         write(STDERR_FILENO, "\n", 1);
//         context->exit_status = 131;
//         context->sigquit = 1;
//     }
//     else
//     {
//         write(STDERR_FILENO, "\b\b  \b\b", 8);
//     }

//     free(nbr);
// }

// void setup_signal_handlers(t_signal_context *context)
// {
//     (void)(* context);
//     struct sigaction sa_int, sa_quit;

//     sa_int.sa_flags = SA_SIGINFO;
//     sa_int.sa_sigaction = handle_sigint;
//     sigemptyset(&sa_int.sa_mask);

//     sa_quit.sa_flags = SA_SIGINFO;
//     sa_quit.sa_sigaction = handle_sigquit;
//     sigemptyset(&sa_quit.sa_mask);

//     sigaction(SIGINT, &sa_int, NULL);
//     sigaction(SIGQUIT, &sa_quit, NULL);
// }