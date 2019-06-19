#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

	int fd = -1;
	int rc = 0;
	int rw = 0;
	size_t len = 0;

	const char *filename = "/home/cristof/.bash_history";
	const char *success_message = "~/bash_history truncated successfully\n";

	fd = open(filename, (int)O_RDWR);

	if (fd < 0){
		const char *message = "~/.bash_history file is inexistent";
		size_t len = strlen(message);	
		rw =(ssize_t)write(STDERR_FILENO, (void *)message,(size_t)len);
		return -1;
	}

	rc = ftruncate(fd, (off_t)0);

	if (rc < 0){
		const char *message = "cannot truncate ~/.bash_history";
		size_t len = (size_t)strlen(message);
		rw = (ssize_t)write(STDERR_FILENO, (void *)message, (size_t)len);
		perror((void *)NULL);
		rc = close(fd);
		if (rc < 0){
			const char *message2 = "cannot close fd for ~/.bash_history";
			size_t len = strlen(message2);
			rw = (ssize_t)write(STDERR_FILENO,(void *)message,(size_t)len);
			perror((void *)NULL);
			return -1;
		}
		return -1;
	}

	len = strlen(success_message);
	rw = (ssize_t)write(STDOUT_FILENO, (void *)success_message, (size_t)len);
	if (rw < 0){
		const char *message = "cannot write success message to stdout";
		len = strlen(message);
		write(STDERR_FILENO, (void *)message, (size_t)len);
		perror((void *)NULL);
		return -1;
	}

	return 0;
}
