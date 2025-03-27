#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

// You can adjust the frame rate to change the game speed. The demo runs at 4 frames per second.
#define FRAME_RATE 4

/**
 * Sleep for a given number of milliseconds
 * \param   ms  The number of milliseconds to sleep for
 */
void sleep_ms(size_t ms) {
  struct timespec ts;
  size_t rem = ms % 1000;
  ts.tv_sec = (ms - rem) / 1000;
  ts.tv_nsec = rem * 1000000;

  // Sleep repeatedly as long as nanosleep is interrupted
  while (nanosleep(&ts, &ts) != 0) {}
}

int main() {
  // Set up ncurses
  initscr();              // Initialize the standard window
  noecho();               // Don't display keys when they are typed
  nodelay(stdscr, true);  // Set up non-blocking input with getch()
  keypad(stdscr, true);   // Allow arrow keys
  curs_set(false);        // Hide the cursor

  // TODO: Implement the lightcycle game using a game loop

  // Shut down
  endwin();
}
