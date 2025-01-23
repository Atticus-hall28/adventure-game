#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Global variables
int stage = 0;
bool locked = true;
bool dev = true;

//  0 name tag, 1 uniform, 2 wrench, 3 omega nametag, 4 hotdog, 5 hotdog on a
//  stick, 6 pipe, 7 diveing suit, 8 medkit.
int items[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char *item_names[] = {"name tag",      "uniform",     "large wrench",
                      "omega nametag", "hotdog",      "hotdog on a stick",
                      "metal",         "diving suit", "explosives"};
// info for boat stuff
// https://www.usni.org/magazines/naval-history-magazine/2018/december/bullseye-navigating-within-ship

// Cross platform sleep function
void sleeper(double seconds) {
  if (dev != true) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else // POSIX
    struct timespec req, rem;
    req.tv_sec = (time_t)seconds;
    req.tv_nsec = (seconds - req.tv_sec) * 1000000000L;
    int ret;
    do {
      ret = nanosleep(&req, &rem);
      if (ret == -1) {
        req = rem;
      }
    } while (ret == -1);
#endif
  }
}
/*
void print_ellipsis(uint num) {
  printf("\n");
  for (int i = 0; i < num; i++) {
    printf("\r");
    sleeper(0.5);
    printf(".");
    sleeper(0.5);
    printf(".");
    sleeper(0.5);
    printf(".");
  }
}
*/
void remove_newline(char *str) { str[strlen(str) - 1] = '\0'; }

int ask(char *str, char *expected_values[]) {
  char input[64];
  char valid_input[64];

  valid_input[0] = '\0';
  input[0] = '\0';

  int num_strings = 0;
  while (expected_values[num_strings] != NULL) {
    num_strings++;
  }

  for (int j = 0; j < num_strings; j++) {
    strcat(valid_input, expected_values[j]);
    strcat(valid_input, ", ");
  }
  if (strlen(valid_input) > 2)
    valid_input[strlen(valid_input) - 2] = '\0';

  printf("\033[0;34m%s \033[0m(%s) \n", str, valid_input);

  while (true) {
    // gets input
    fgets(input, sizeof(input), stdin);

    // removes newline
    int length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') {
      input[length - 1] = '\0';
    }

    // validates input
    for (int i = 0; i < num_strings; i++) {
      if (strcmp(input, expected_values[i]) == 0) {
        return i;
      }
    }

    printf("\033[0;33minvalid intput, valid inputs are:\033[0m (%s)\n",
           valid_input);
  }
}

int main(void) {
  int answer;
  char str_answer[64];
  char name[64];
  int captan_favor = 0;

start:
  for (int i = 0; i < 10; i++) {
    items[i] = 0;
  }
  locked = 1;

  // start of intro
  printf("yesterday, you signed up to join the crew of posiden's hand as an "
         "engineer, the ship is "
         "experimental submarine designed to enter the rift that formed in the "
         "atlantic ocean a year ago. \nIt was a well-paying job but there are "
         "many of things I'm not being told\n\n");
  sleeper(5);
  printf("you cut that thought short, as you arrive to the docks where your "
         "home for the next few months is moored.\n\n");
  // printf("");

  char *values[10] = {"yes", "no", NULL};
  answer = ask("Do you your mind and look for another job?", values);

  // printf("\n%d\n", answer);

  if (answer == 0) {
    printf("\033[1;35m\nENDING 1 \033[0m\n\nYou decide to return home and look "
           "for "
           "another job.\n");
    goto end;
  }
  if (answer == 1) {
    printf("\nyou decide to enter the massive submarine and begin your "
           "journey.\n");
  }
  sleeper(1);
  printf("you climb into the hatch which quickly seals behind you, infront of "
         "you stands the captain, a man with short hair and a large beard.\n"
         "He says 'welcome aboard, I'm captain jones,\033[0;34m what is your "
         "name?\033[0m'\n");

  fgets(name, sizeof(name), stdin);
  remove_newline(name);

  printf("%s, huh? well, nice to meet you, I'm glad you're here.\n\n", name);
  printf("His pleasant demeanor changes as he says 'there are a couple rules "
         "you need to follow, ");
  sleeper(1);
  printf("\nfirstly, you must carry your id card on your "
         "person at all times, ");
  sleeper(2);
  printf("\nsecondly do not question the captain,");
  sleeper(3);
  printf(
      "\nand I can not stress this enough, do not enter any room marked "
      "with an omega' \nhe points to a sign titled 'EXAMPLE', below the title "
      "is shows this symbol: Ω");
  sleeper(5);
  printf("\n\nHis pleasant demeanor return as he says 'well anyways your going "
         "to need to get situated with this place, first we need to get you an "
         "id card and your uniform.'\n");
  sleeper(1);
  printf(
      "he starts walking down the main hall and asks you to follow him.\n\n");
  sleeper(2);
  printf("after a few seconds you reach a door with a sign that reads "
         "'equipment' and you both enter\n");
  sleeper(1);
  printf("he walks over to a closet with around 20 identical uniforms of "
         "varying sizes\n"
         "he pulls one out, and says 'this looks like your size right?', you "
         "nod your head in agreement\n");
  sleeper(2);
  printf("next he walks over to a large machine type in a few letters\n\n");
  sleeper(2);
  printf(
      "after a few seconds a small metal name tag with '%s' writen on it with "
      "bold black letters\n",
      name);
  sleeper(2);
  printf("he hands you the name tag and uniform and tells you to get changed "
         "behind the curtain  in the corner of the room\n\n");
  items[0] = 1;
  items[1] = 1;
  sleeper(3);
  printf("after you get changed the captain explains' your name tag is also a "
         "keycard of sorts,if you go up to a door your authorizied to enter it "
         "will unlock, if you try to open a door your not authorized to enter "
         "it will not unlock and your attempt will be logged.\n");
  sleeper(5);
  values[0] = "cafeteria";
  values[1] = "your room";
  values[2] = "mechanical";
  values[3] = NULL;

  int tour = true;
  while (tour) {
    answer = ask("where do you want to go next?", values);
    printf("I'll take you there right now\n");
    if (answer == 0) {

      sleeper(3);
      printf("the captain leads to the cafeteria and you enter. In the back "
             "there is a large pile of\033[0;32m hotdogs.\033[0m ");
      char *hotdog_options[64] = {"yes", "no"};
      int hotdog_answer =
          ask("your not hungry right now, do you take on for later",
              hotdog_options);
      if (hotdog_answer == 0) {
        items[4]++;
      }
      printf("you currently have\033[0;32m %d %s \033[0m\n", items[4],
             item_names[4]);
      sleeper(2);
    } else if (answer == 1) {
      char *room_options[64] = {"rest", "continue"};
      printf("you and the captain enter your room and see a bed, a desk, and a "
             "bedside table\nthe captain asks'"
             "you want to");
      int room_answer =
          ask(" continue the tour or get some rest?", room_options);

      if (room_answer == 0) {
        printf("he responds' I guess I'll leave you here, the bathroom is just "
               "across the hall if you need it.\n");
        sleeper(1);
        tour = false;

      } else if (room_answer == 1) {
        printf("he responds' Sure, we can continue the tour then.\n");
      }
    } else if (answer == 2) {
      printf("the captain leads you to the mechanical room and you enter. In "
             "the back there two large turbines"
             " emiting a low humming noise.\n");
      printf("this room is where you will be working on the submarine, you "
             "will be working on the reactor, generator, and life suport "
             "systems running\n");
      if (items[2] == 0) {
        char *mechanical_options[64] = {"yes", "no"};
        sleeper(1);
        printf("you see a\033[0;32m %s\033[0m on the ground, ", item_names[2]);
        int mechanical_answer = ask("do you pick it up?", mechanical_options);
        if (mechanical_answer == 0) {
          sleeper(1);
          printf(
              "you pick up the\033[0;32m %s\033[0m and put it in your pocket\n",
              item_names[2]);
          items[2] = 1;
        } else {
          printf("you leave the\033[0;32m %s\033[0m on the ground\n",
                 item_names[2]);
        }
      }
    }
  }

  // tourend:
  printf("captain leaves the room and you quickly fall asleep\n");

  sleeper(1);

  printf("you wake up the next morning to the a speaker in your room anouncing "
         "'please report to the bridge to meet with the capitan'\n");

  locked = false;
  sleeper(2);
  values[0] = "bridge";
  values[1] = "stay asleep";
  values[2] = NULL;
  answer = ask("where do you want to go?\n", values);

  if (answer == 1) {
    printf("\033[1;35m\nENDING 2\033[0m\n\n");
    printf("you sleep for another hour and wake up to the captain yelling at "
           "you\n\n");
    sleeper(0.5);
    printf("he exclames 'if you can't be bothered to get up you don't belong "
           "on this crew\n"
           "we are still docked exit through the main hatch and don't come "
           "back'\n");
    goto end;
  }
  printf("you meet up with the capitan and he tells you to go to the "
         "mechanical room and prepare to go out to sea\n");
  sleeper(1);
  printf("you walk to the mechanical room and start the primary reactor\n");
  sleeper(2);
  printf("as the reactor starts all the ligths in the room qickly turn off and "
         "back on as the power system shifts from the auxiliary "
         "reactor to the main one\n\n");
  sleeper(1);
  printf("as this happens you hear the door to the mechanical room unlock and "
         "relock\n");
  sleeper(4);
  printf(
      "the capitan anounces 'we are now ready to leave port', at the same time "
      "you feel a jolt as the exerimental engines rapidly accelerate\n");

  printf("you exit the mechanical room, ");

  values[0] = "break room";
  values[1] = "your room";
  values[2] = NULL;

  answer = ask("where do you want to go?", values);
  if(answer==0){
    printf("you go to the break room and ")
  }





  
  fprintf(
      stderr,
      "\033[0;31m\nERROR: the ended was not intended to be reached this way\n");
  // return 1;
end:
  values[0] = "yes";
  values[1] = "no";
  values[2] = NULL;
  answer = ask("would you like to play again?", values);

  if (answer == 0) {
    printf("\033[2J\033[H");
    goto start;
  }

  return 0;
}