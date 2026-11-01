#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/reboot.h>

int main(int argc, char** argv) {
  time_t raw_time = time(NULL);

  // Convert to the local time structure
  struct tm* t = localtime(&raw_time);

  // Morning schedule
  int TARGET_MORNING_H = 8;
  int TARGET_MORNING_M = 30;
  if (argc > 2) {
    TARGET_MORNING_H = atoi(argv[1]);
    TARGET_MORNING_M = atoi(argv[2]);
  }
  printf("Target shutdown morning time: %02d:%02d\n", TARGET_MORNING_H, TARGET_MORNING_M);

  // Evening schedule
  int TARGET_EVENING_H = 21;
  int TARGET_EVENING_M = 30;

  // Friday and Saturday schedule
  if (t->tm_wday == 5 || t->tm_wday == 6) {
    TARGET_EVENING_H = 22;
    TARGET_EVENING_M = 0;
  }
  printf("Target shutdown evening time: %02d:%02d\n", TARGET_EVENING_H, TARGET_EVENING_M);


  while (1) {
    time_t raw_time = time(NULL);

    // Convert to the local time structure
    struct tm* t = localtime(&raw_time);

    printf("Now: %02d/%02d/%04d %02d:%02d:%02d\n", 
           t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, 
           t->tm_hour, t->tm_min, t->tm_sec);

    if (t->tm_hour == TARGET_MORNING_H && t->tm_min >= TARGET_MORNING_M && t->tm_min < TARGET_MORNING_M + 5) {
      printf("Shutdown at: %02d/%02d/%04d %02d:%02d:%02d\n", 
             t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, 
             t->tm_hour, t->tm_min, t->tm_sec);

      // Triggers an ungraceful kernel halt/shutdown
      reboot(RB_HALT); 
    } else if (t->tm_hour == TARGET_EVENING_H && t->tm_min >= TARGET_EVENING_M && t->tm_min < TARGET_EVENING_M + 5) {
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