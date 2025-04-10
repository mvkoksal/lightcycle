#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

// You can adjust the frame rate to change the game speed. The demo runs at 4 frames per second.
#define FRAME_RATE 4
#define WIDTH 37
#define LENGTH 27

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

void print_grid(int grid[WIDTH * LENGTH]) {
  for (int i = 0; i < WIDTH * LENGTH; i++){
    int row = i / WIDTH;
    int col = i % WIDTH;
    // Empty spaces
    if (grid[i] == 0) {
      attron(COLOR_PAIR(0));
      mvprintw(row, 2*col, "  ");
      attroff(COLOR_PAIR(0));
    // Player 1
    } else if (grid[i] == 1) {
      attron(COLOR_PAIR(1));
      mvprintw(row, 2*col, "  ");
      attroff(COLOR_PAIR(1));
    // Player 2
    } else if (grid[i] == 2) {
      attron(COLOR_PAIR(2));
      mvprintw(row, 2*col, "  ");
      attroff(COLOR_PAIR(2));
    } else if (grid[i] == 3) {
      attron(COLOR_PAIR(3));
      mvprintw(row, 2*col, "  ");
      attroff(COLOR_PAIR(3));
    }
  }
}

void print_default_grid(int grid[WIDTH * LENGTH]) {
  for (int i=0; i < WIDTH*LENGTH; i++) {
    grid[i] = 0;
  }
  // Top border
  for (int i=0; i < WIDTH; i++) {
    grid[i] = 3;
  }
  // Bottom border
  for (int i=(LENGTH-1)*37; i<WIDTH*LENGTH; i++) {
    grid[i] = 3;
  }
  //Left border
  for (int i=0; i<=(LENGTH-1)*37; i+=37) {
    grid[i] = 3;
  }
  //Right border
  for (int i=36; i<WIDTH*LENGTH; i+=37) {
    grid[i] = 3;
  }
}

void white_box () {
  attron(COLOR_PAIR(3));
  for (int k=12; k < 17; k ++) {
  for (int i=12; i < 24; i++) {
    mvprintw(k, 2*i, "  ");
  }
  }
  attroff(COLOR_PAIR(3));
}

int main() {
  // Set up ncurses
  initscr();              // Initialize the standard window
  noecho();               // Don't display keys when they are typed
  nodelay(stdscr, true);  // Set up non-blocking input with getch()
  keypad(stdscr, true);   // Allow arrow keys
  curs_set(false);        // Hide the cursor

  // Tell ncurses to initialize color support
  start_color();

// Color pair 0 is white text on a black background
  init_pair(0, COLOR_WHITE, COLOR_BLACK);

  // Color pair 1 is white text on a yellow background
  init_pair(1, COLOR_WHITE, COLOR_YELLOW);

  // Color pair 2 is white text on a blue background
  init_pair(2, COLOR_WHITE, COLOR_BLUE);

  // Color pair 3 is black text on a white background;
  init_pair(3, COLOR_BLACK, COLOR_WHITE);

  // Color pair 4 is red text on a red background; REMOVE THIS ONCE DONE
  init_pair(4, COLOR_RED, COLOR_RED);

  int cursor1_x = 1;
  int cursor1_y = 17;
  int cursor2_x = 25;
  int cursor2_y = 17;
  // Calculate the cursor index in the maze array.
  int cursor1_index;
  int cursor2_index;
  char dir1 = 'd'; //down
  char dir2 = 'u'; //up

  int winner=100; 
  // 0 - tie; 1 - player1; 2 - player2
  // we set winner to something other than 0 1 or 2.


  int grid[WIDTH * LENGTH];
  print_default_grid (grid);


  bool running = true;
  while (running) {
    int input = getch();

    while (input != ERR) {
      if (input == ' ') {
        // Quit
        running = false;
      
      // Set curser1 direction
      } else if (input == KEY_UP) {
      dir1 = 'u';
      } else if (input == KEY_DOWN) {
      dir1 = 'd';
      } else if (input == KEY_LEFT) {
      dir1 = 'l';
      } else if (input == KEY_RIGHT) {
      dir1 = 'r';

      // Set cursor2 direction
      } else if (input == 'w') {
      dir2 = 'u';
      } else if (input == 's') {
      dir2 = 'd';
      } else if (input == 'a') {
      dir2 = 'l';
      } else if (input == 'd') {
      dir2 = 'r';
      }

    input = getch();
    }

    if (winner == 0) {
      attron(COLOR_PAIR(3));
      white_box();
      mvprintw(13, 2*15, "Tie game!");
      mvprintw(15, 2*13, "Press space to exit.");
      attroff(COLOR_PAIR(3));
      continue;
    } else if (winner == 1) {
      attron(COLOR_PAIR(3));
      white_box();
      mvprintw(13, 2*15, "Yellow wins!");
      mvprintw(15, 2*13, "Press space to exit.");
      attroff(COLOR_PAIR(3));
      continue;
    } else if (winner == 2) {
      attron(COLOR_PAIR(3));
      white_box();
      mvprintw(13, 2*15, "Blue wins!");
      mvprintw(15, 2*13, "Press space to exit.");
      attroff(COLOR_PAIR(3));
      continue;
    }

    cursor1_index = (cursor1_x * WIDTH) + cursor1_y;
    cursor2_index = (cursor2_x * WIDTH) + cursor2_y;
  
    grid[cursor1_index] = 1;
    grid[cursor2_index] = 2;

    // MOVE PLAYER1
    if (dir1 == 'u') {
    // Move the cursor up
    cursor1_x--;

    } else if (dir1 == 'd') {
    // Move the cursor down
    cursor1_x++;
  
    } else if (dir1 == 'l') {
    // Move the cursor left
    cursor1_y--;

    } else if (dir1 == 'r') {
    // Move the cursor right
    cursor1_y++;
    }

    //MOVE PLAYER2
    if (dir2 == 'u') {
    // Move the cursor up
    cursor2_x--;

    } else if (dir2 == 'd') {
    // Move the cursor down
    cursor2_x++;
  
    } else if (dir2 == 'l') {
    // Move the cursor left
    cursor2_y--;

    } else if (dir2 == 'r') {
    // Move the cursor right
    cursor2_y++;
    }

    cursor1_index = (cursor1_x * WIDTH) + cursor1_y;
    cursor2_index = (cursor2_x * WIDTH) + cursor2_y;

    if (grid[cursor1_index] != 0 && grid[cursor2_index] != 0) {
      winner = 0;
    } else if (grid[cursor1_index] != 0 && grid[cursor2_index] == 0) {
      winner = 2;
    } else if (grid[cursor1_index] == 0 && grid[cursor2_index] != 0) {
      winner = 1;
    }

  print_grid(grid);


  refresh();
  sleep_ms(1000 / FRAME_RATE);

  }

  // Shut down
  endwin();
}
