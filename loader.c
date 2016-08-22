#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if(argc != 2) {
		printf("Linux COM loader\nUSAGE: %s file\n", argv[0]);
		return 0;
	}
	const char* path = argv[1];

	void *p;
	/* Allocate space from 0x00000 to 0x10000
	 *
	 * sudo sysctl vm.mmap_min_addr=0
	 */
	p = mmap((void*)0, 0x10000, PROT_EXEC|PROT_READ|PROT_WRITE,
			MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0);
	if(p == MAP_FAILED) {
		perror("Error in mmap()");
		return -1;
	}

	/* Load contents of hello.bin at address 0x100. We could set up PSP as
	 * well, but whatever. */
	int fd;
	fd = open(path, O_RDWR);
	if(fd == -1) {
		perror("Error in open()");
		return -1;
	}

	void *pw = (void*)0x100;
	while(1) {
		ssize_t r = read(fd, pw, 1024);
		if(r == -1) {
			perror("Error in read()");
			return -1;
		} else if(r == 0) {
			break;
		} else {
			pw += r;
		}
	}

	close(fd);

	/* Set stack pointer to end of allocated area, jump to 0x100.
	 *
	 * Note, we still have stuff from loader mapped at various addresses. */
	asm(
		"mov	$0x10000, %rsp\n"
		"jmp	0x100\n"
	);

	return 0;
}
