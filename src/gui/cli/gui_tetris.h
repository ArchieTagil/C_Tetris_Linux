#ifndef GUI_DEFINES_TETRIS
#define GUI_DEFINES_TETRIS
/// @brief Code of ESC button on the keyboard
#define ESC 27

/// @brief Code of ENTER button on the keyboard
#define ENTER 10

#include <ncurses.h>
#include "../../brick_game/tetris/tetris.h"

/** @brief Init the ncurses screen.
 *  @return return nothing.
 */
void win_init();

/** @brief Draw graphic interface.
 *  @return return nothing.
 */
void print_overlay();

/** @brief Draw running line before game.
 *  @return return nothing.
 */
void print_running_line();

/** @brief Draw GameInfo_t object field on the screen.
 *  @return return nothing.
 */
void print_state(GameInfo_t game_info);

/** @brief Draw some rectangle on the screen from the top left position to the bottom right.
 *  @param top_y - top y position.
 *  @param left_x - left x position.
 *  @param bottom_y - bottom y position.
 *  @param right_x - right x position.
 *  @return return nothing.
 */
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

/** @brief Catch user action while game state isn't equal EXIT and call do_loop_logic in every frame of game.
 *  @return return nothing.
 */
void game_loop();

/** @brief Perform 1 step of program through updateCurrentState() function or show information about Pause or GameOver according the current state.
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @param state - pointer to the single instanse of tetris state
 *  @return nothing
 */
void do_loop_logic(const tetris_state *state, GameInfo_t *game_info);

/** @brief Clear graphical representation of field
 *  @return return nothing.
 */
void clear_window();

/** @brief Print additional information about game in the right part of game window.
 *  @param game_info - single instanse of GameInfo_t object. 
 *  @return nothing
 */
void update_counters(GameInfo_t game_info);

#endif