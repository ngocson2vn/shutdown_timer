#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/reboot.h>

int main(int argc, char** argv) {
  int TARGET_HOUR = 8;
  int TARGET_MIN = 30;
  if (argc > 2) {
    TARGET_HOUR = atoi(argv[1]);
    TARGET_MIN = atoi(argv[2]);
  }
  printf("Target shutdown time: %02d:%02d\n", TARGET_HOUR, TARGET_MIN);

  while (1) {
    time_t raw_time = time(NULL);

    // Convert to the local time structure
    struct tm* t = localtime(&raw_time);

    printf("Now: %02d/%02d/%04d %02d:%02d:%02d\n", 
           t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, 
           t->tm_hour, t->tm_min, t->tm_sec);

    if (t->tm_hour == TARGET_HOUR && t->tm_min >= TARGET_MIN && t->tm_min < TARGET_MIN + 15) {
      printf("Shutdown at: %02d/%02d/%04d %02d:%02d:%02d\n", 
             t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, 
             t->tm_hour, t->tm_min, t->tm_sec);

      // Triggers an ungraceful kernel halt/shutdown
      reboot(RB_HALT); 
    }

    fflush(stdout);
    fflush(stderr);
    sleep(30);
  }

  return 0;
}