#include "famine.h"

void		sig_segv_handler(int signum, siginfo_t *info, void *ptr)
{
	printf("SIG %d recieved\n", signum);
	if (signum != SIGINT)
		exit(0);
}

void		set_signal_handle(int sig)
{
	static struct 	sigaction _sigact[100];
	static int	i = 0;

	memset(&(_sigact[i]), 0, sizeof(_sigact[i]));
	_sigact[i].sa_sigaction = sig_segv_handler;
	_sigact[i].sa_flags = SA_SIGINFO;

	sigaction(sig, &_sigact[i], NULL);
	++i;
}

int		outputhandle(int ac, char **av)
{
	for (int i = 0; i < ac; ++i)
		if (strcmp("-sh", av[i]) == 0 || strcmp("--show", av[i]) == 0)
			return (0);
	int buf[100];
	for (int i = 0; i < 100; ++i)
	{
		pipe(&buf[i]);
		dup2(buf[i], i);      // replace stdout with output to child
	}
	
	// ALL SIGNALS THAT WRITE TO A LOG FILE
	set_signal_handle(SIGABRT);
	set_signal_handle(SIGBUS);
	set_signal_handle(SIGCHLD);
	set_signal_handle(SIGFPE);
	set_signal_handle(SIGILL);
	set_signal_handle(SIGQUIT);
	set_signal_handle(SIGPIPE);
	set_signal_handle(SIGSEGV);
	set_signal_handle(SIGSYS);
	set_signal_handle(SIGTRAP);
	set_signal_handle(SIGXCPU);
	
	//cause segfault
	//abort();
	//printf(av[1000]);
}
