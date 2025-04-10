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

// Read the array and print the grid accordingly 
void print_grid(int grid[WIDTH * LENGTH]) {
  for (int i = 0; i < WIDTH * LENGTH; i++) {
    int row = i / WIDTH;
    int col = i % WIDTH;
    // Empty spaces
    if (grid[i] == 0) {
      attron(COLOR_PAIR(0));
      mvprintw(row, 2*col, "  ");
      attroff(COLOR_PAIR(0));
    // Player 1 trail
    } else if (grid[i] == 1) {
      attron(COLOR_PAIR(1));
      mvprintw(row, 2*col, "  ");
      attroff(COLOR_PAIR(1));
    // Player 2 trail
    } else if (grid[i] == 2) {
      attron(COLOR_PAIR(2));
      mvprintw(row, 2*col, "  ");
      attroff(COLOR_PAIR(2));
    // Borders
    } else if (grid[i] == 3) {
      attron(COLOR_PAIR(3));
      mvprintw(row, 2*col, "  ");
      attroff(COLOR_PAIR(3));
    }
  }
}

// Initialize the elements of the grid array to 0
// Set the borders of the grid array to 3
void print_default_grid(int grid[WIDTH * LENGTH]) {
  // Initialize to 0
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
  // Left border
  for (int i=0; i<=(LENGTH-1)*37; i+=37) {
    grid[i] = 3;
  }
  // Right border
  for (int i=36; i<WIDTH*LENGTH; i+=37) {
    grid[i] = 3;
  }
}

// Print a white box in the middle of the grid
// to be used to display the win message on it.
void white_box () {
  attron(COLOR_PAIR(3));
  // Loop through rows
  for (int k=12; k < 17; k++) {
    // Loop through columns
    for (int i=12; i < 24; i++) {
      mvprintw(k, 2*i, "  ");
    }
  }
  attroff(COLOR_PAIR(3));
}

// Check if the game has ended, display the relevant win message
bool winner_check (int winner) {
  if (winner == 3) {
      attron(COLOR_PAIR(3));
      white_box();
      mvprintw(13, 2*15, "Tie game!");
      mvprintw(15, 2*13, "Press space to exit.");
      attroff(COLOR_PAIR(3));
      return true;
  } else if (winner == 1) {
      attron(COLOR_PAIR(3));
      white_box();
      mvprintw(13, 2*15, "Yellow wins!");
      mvprintw(15, 2*13, "Press space to exit.");
      attroff(COLOR_PAIR(3));
      return true;
  } else if (winner == 2) {
      attron(COLOR_PAIR(3));
      white_box();
      mvprintw(13, 2*15, "Blue wins!");
      mvprintw(15, 2*13, "Press space to exit.");
      attroff(COLOR_PAIR(3));
      return true;
  } else {
      return false;
  }
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

  // Initialize the two cursors' state
  int cursor1_x = 1;
  int cursor1_y = 17;
  int cursor2_x = 25;
  int cursor2_y = 17;

  // Variables storing the two cursors' indexes in the grid array
  int cursor1_index;
  int cursor2_index;

  // Variables tracking the directions of the two cursors
  // 'd' for down, 'u' for up, 'r' for right, and 'l' for left
  char dir1 = 'd'; //down
  char dir2 = 'u'; //up

  // Variable storing the winner
  // 0 - no winner; 1 - player1; 2 - player2; 3 - tie
  int winner = 0; 

  // Empty grid
  int grid[WIDTH * LENGTH];
  print_default_grid (grid);

  // Start the game loop
  bool running = true;
  while (running) {
    // Check for user input
    int input = getch();
    while (input != ERR) {
      if (input == ' ') {
        // Exit when the user presses space
        running = false;
      
      // Set the direction of curser1
      } else if (input == KEY_UP) {
      dir1 = 'u';
      } else if (input == KEY_DOWN) {
      dir1 = 'd';
      } else if (input == KEY_LEFT) {
      dir1 = 'l';
      } else if (input == KEY_RIGHT) {
      dir1 = 'r';

      // Set the direction of cursor2
      } else if (input == 'w') {
      dir2 = 'u';
      } else if (input == 's') {
      dir2 = 'd';
      } else if (input == 'a') {
      dir2 = 'l';
      } else if (input == 'd') {
      dir2 = 'r';
      }
    // Detect concurrent inputs
    input = getch();
    }

    // Pause the game if the game has ended
    if (winner_check(winner)) {
      continue;
    }
    
    // Calculate the two cursors' indexes in the grid array
    cursor1_index = (cursor1_x * WIDTH) + cursor1_y;
    cursor2_index = (cursor2_x * WIDTH) + cursor2_y;

    // Modify the grid array to store the current position of the two cursors
    // The modified grid enables the two players 
    // to leave a trail behind them as they move
    grid[cursor1_index] = 1;
    grid[cursor2_index] = 2;

    // Update the state of player1
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

    //Update the state of player2
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

     // After the state update, calculate the new indexes 
     // of both cursors in the grid array.
     // Check if the next positions are not empty spaces.
     // If they aren't, set the winner variable to end the game
    cursor1_index = (cursor1_x * WIDTH) + cursor1_y;
    cursor2_index = (cursor2_x * WIDTH) + cursor2_y;
    // Tie
    if (grid[cursor1_index] != 0 && grid[cursor2_index] != 0) {
      winner = 3;
    // Player2 wins
    } else if (grid[cursor1_index] != 0 && grid[cursor2_index] == 0) {
      winner = 2;
      // Player1 wins
    } else if (grid[cursor1_index] == 0 && grid[cursor2_index] != 0) {
      winner = 1;
    }

  print_grid(grid);

  refresh();
  
  // Pause to limit frame rate
  sleep_ms(1000 / FRAME_RATE);

  }

  // Shut down
  endwin();
}