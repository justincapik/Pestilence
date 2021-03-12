#include "famine.h"

int		calamar(char *path)
{
	DIR* dir;
	struct dirent* ent;
	char* endptr;
	char buf[512];

	if (!(dir = opendir(path))) 
	{
		return (-1);
	}

	while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
			continue;
		if (ent->d_type == DT_DIR)
		{
			printf("%s is a dir\n", ent->d_name);
			char *dirname = strjoin(path, ent->d_name);
			calamar(dirname);
		}
		if (ent->d_type == DT_REG)
			printf("%s is a file\n", ent->d_name);
	}
	return (0);
}
