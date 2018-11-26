#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *setDir(char dir[], char *device) {
	char dir1[] = "/sys/bus/w1/devices/";
	char dir2[] = "/w1_slave";
  strcat(dir, dir1);
  strcat(dir, device);
	strcat(dir, dir2);

	printf("%p\n", &dir);


  return dir;
}

int readSensor(char dir[]) {
	FILE *fd;
	int n;
	char buf[101];
	int t = 0;
	int i;

	fd = fopen(dir, "r");

	if (fd  == (FILE *)NULL) {
 		perror("Temperature sensor cannot be found");
		(void) exit(1);
 	}
	n = fread(buf, 1, 100, fd);
 	if(n == 0) {
 		perror("Read fails!");
 		exit(1);
 	}
 	buf[n] = '\0';
	/*
 	fprintf(stdout, "Read '%s'\n", buf);
	*/
	for (i = 0; i < 5; i++) {
		char nChar = buf[n-6 + i];
		int num = nChar - '0';
		num *= pow(10, 4-i);
		t += num;
	}

 	(void) fclose(fd);

	return t;
}

void usage() {

}

void tempread(char *device, int verbose) {
 	int t = readSensor(device);
  printf("%d", t);
}

int main(int argc, char *argv[]) {
  char dir[100];
  char *device = "28-03184177f1ff";
  int verbose = 0;

  /* process the arguments */
  argc--; argv++;
  while(argc > 0) {
    printf("%d %s\n", argc, argv[0]);
    if(!strcmp("-v", argv[0])) {
      verbose = 1;
    } else if(!strcmp("-d", argv[0])) {
        if(argc == 0)
        usage();
        argc--; argv++;
        device = argv[0];
    } else
      usage();
    argc--; argv++;
  }

	dir = *setDir(dir, device);
  printf("%s\n", setDir(dir, device));
  tempread(dir, verbose);
  return 0;
}
