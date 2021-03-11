#include "famine.h"

int		check_process(char *name, int pid)
{
	DIR* dir;
	struct dirent* ent;
	char* endptr;
	char buf[512];

	if ((name == NULL || strlen(name) == 0) && pid < 0)
		return (1);

	if (!(dir = opendir("/proc"))) {
		perror("can't open /proc");
		return (-1);
	}

	while ((ent = readdir(dir)) != NULL)
	{
		if (pid > 0 && atoi(ent->d_name) == pid)
		{
			printf("name is %s (%d)\n", ent->d_name, atoi(ent->d_name));
			return (0);
		}
		else if (name == NULL || name[0] == '\0')
			continue;

		long lpid = strtol(ent->d_name, &endptr, 10);
		if (*endptr != '\0')
			continue;

		char buff[100];
		snprintf(buf, sizeof(buf), "readlink /proc/%ld/exe", lpid);
		FILE *fp = popen(buf, "r");

		if (fp)
		{
			if (fgets(buf, sizeof(buf), fp) != NULL)
			{
				printf("result = [%s], nom = [%s]\n", buf, name);
				buff[99] = '\0';
				if (strstr((char*)buf, name) != NULL)
					return (1);
			}
			pclose(fp);
		}
	}
	return (1);
}
