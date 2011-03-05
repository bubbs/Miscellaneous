//// Tetris for LDMud : v2.6.1.
//
// Originally, Tetris for LPMud - 3.2.1.
// Bubbs is bored and ought to be doing something more worthwhile.
// Bubbs started this on 22/Feb/1997.  Today is not a good day.


/// v2.6.1: Bubbs@BrightSword, 16/Jul/2010.
// Fixed bug which reset game flags and call-back, following unsuspend().

/// v2.6: Bubbs@BrightSword, 02/Apr/2008.
// Made 'Game Over' message flash.
// Further revisions to defintions and macros to improve portability.
// Added USER_TIME() and FORMAT_TIME() macros.
// Converted PAGERD to more generic PAGE_TEXT(X, T) defintion.

/// v2.5.4: Bubbs@BrightSword, 23/May/2007.
// Added SUBST(), CAN_SEE_USER(), CAN_USE_ANSI() and USER_OPTIONS() macros,
// with definition based on mudlib.  Made use of the new macros.
// Tweaked colour_data mapping structure.
// Tweaked draw_block() and DBL_ definitions.
// Revamped versions to three-tier system.
// Added blank lines to separate logic (increase readability).
// Other minor syntactical changes.
// Added TETRIS_ORIGINAL definition.

/// v2.5.3: Bubbs@BrightSword, 28/Sep/2006.
// Tweaked level display to show 'Insane' in insane mode.
// Tweaked printf() usage.
// Tweaked argument handling; added '&' support.

/// v2.5.2: Bubbs@BrightSword, 27/June/2006.
// Added page_text() function to handle text paging.
// Implemented very basic internal text pager.

/// v2.5.1: Bubbs@BrightSword, 14/Feb/2006.
// Moved user->query_real_name() lfun usage to USER_NAME() macro.
// Fixed sort order in main("list").

/// v2.5: Bubbs@TimeWaste, 21/Dec/2005.
// Added G_SUSPEND_ID to track the suspend ID (when SUSPENDD defined).

/// v2.4: Bubbs@TimeWaste, 25/Mar/2005.
// Mat did some refactoring of the display code, added display_help().
// If SUSPENDD is defined, the "suspend" command uses SUSPENDD->suspend() to suspend
// games, and the unsuspend() method can resume the game.  Lightweight support.

/// v2.3: Bubbs@TimeWaste, 09/Mar/2005.
// Fixed bug in stop_watch_game() which prevented it working.
// Enhanced callback support; completed games pass the score data.
// Modified 'Press a key' to 'Press space', so the key buffer can
// be emptied properly.

/// v2.2: Bubbs@TimeWaste, 27/Feb/2005.
// Added main("scores!...") non-paged scores output support.
// Modified last_scores handling; now indexed by rank not name.
// Mat: The guide is now printed in bold.

/// v2.1: Mat@TimeWaste, 22/Feb/2005.
// Added commands '@' and '$', to add a line and a level, respectively.
// Added option '-I' ('insane') to start game at level 10.
// Bubbs: Fixed stop_watch_game(); no more spurious messages.

/// v2.0: Bubbs@TimeWaste, 20/Feb/2005.
// Added last_scores, main("last") to view, currently they last for 4 weeks.

/// v1.4.3 (v2.0b): Bubbs@TimeWaste, 10/Feb/2005.
// Added main("scores [!]me today") score browser option.
// Smartened banner display when no scores.
// Added F_DEBUG option, and -D command line option to enable.
// Improved rotate_block() logic; blocks now pivot nicely.
// Added key buffer logic to end_game(), so it clears the key buffer.
// Simplified draw_block() signiture, and usage.
// Added a draw_block(user, 1) before the add_line() call(s).

/// v1.4.2 (v2.0a): Bubbs@TimeWaste, 07/Feb/2005.
// Optimised draw_block() a bit.
// Added a fake input_to() in watch_game(), to suppress user prompt.
// end_game() now remove_input_to()s the fake input_to for each watcher.
// Added query_score_info(); simplified show_scores() and browse_scores().
// Added main("top <num>") option for show_scores().
// Added a stop_watch_game(0) to start_game().
// Added a direction parameter to rotate_block().
// Added 'unrotate' reverse rotation command, keys 8 and NumPad-5.
// Added regex and use_pager arguments to browse_scores().
// Added main("scores [!][all|me|today|<regex>]") score browser option.

/// v1.4.1: Bubbs@TimeWaste, 06/Feb/2005.
// Added main() and help() methods, to provide a command line interface.
// Now makes use of input_to.h for input_to() flags.
// Added checks to critical calls to ensure create() is called.
// Overhauled start_game(): can now pass game flags as argument; returns 1 on
// success; rationalised game failure logic (busy detection or 2 callbacks).
// Added command line options to control definable options, and user
// environmental variable support to provide per user default options.
// Commented mudlib dependancies.

/// v1.4: Bubbs@TimeWaste, 05/Feb/2005.
// Added browse_scores() to view all scores.
// Increased number of MAX_HIGH_SCORES, and decreased MIN_HIGH_SCORE value.
// Added manynew definitions for mapping values, and changed code appropriately.
// Added G_DURATION to games, game duration, added HS_DURATION to high scores.
// Added HS_BLOCKS block count to high scores.
// Added G_BLOCKS and G_DURATION to main game display.
// Modified colour_string(), adding no-colour and foreground/background options.
// Added F_COLOUR, modified colour calls, and colour toggle command.
// Simplified and smartened show_scores() and browse_scores().

/// v1.3.9: Bubbs@TimeWaste, 03/Feb/2005.
// Updated formatting and started using LDMud syntax.
// Now counts total blocks (doesn't show them though).
// Basic support for watching games.
// Added query_player_data() to query game data.

/// v1.3.8: Mat@TimeWaste, 02/Feb/2005.
// Fixed a legacy problem that could make a game have no heartbeat.
// When lines are added at level 10 only 1 line is added.
// Previously, 2 lines were added which made the game degenerate
// a little too quickly.

/// v1.3.7: Bubbs@ShadowGate, 21/March/2002.
// Previously unlogged: Added culmulative block statistics.
// Made block stats display in base block colour.

/// v1.3.6: Bubbs@ShadowGate, 19/June/2001.
// Twiddled with colour settings: now draw spaces with coloured backgrounds.
// Needed to tidy colour_string() mechanism.
// Blocks are now drawn with double width, so that the base unit looks square
// (on a standard 25x80 display), making rotation look more natural.
// Consequently, adjusted other displayed items.

/// v1.3.5: Bubbs@ShadowGate, 10/Feb/2001.
// Added draw_games(), display of other current tetris games.

/// v1.3.4: Bubbs@ShadowGate, 19/Jan/2001.
// Revamped high scores.  Added 'Rank' to score.
// Added 'Guide' and toggle.

/// v1.3.3: Bubbs@ShadowGate, 12/Jan/2001.
// Improved key/command recognition mechanism.
// Added cursor key commands.
// Improved colour code.

/// v1.3.2: Bubbs@ShadowGate, 10/Apr/2000.
// Played with some new block types
// Added colour blocks.

/// v1.3.1: Bubbs@Timewarp, 02/Mar/1997.
// Finished the game properly; it's now playable.

/// v1.0: Bubbs@Timewarp, 22/Feb/1997.
// Initial thoughts;
// board display, block display, input_to() loop.



/// Driver dependancy:
//   Critical:
//     LDMud 3.2.11+

/// MUDlib dependancies:
// Critical:
//   * use of input_to(, INPUT_IGNORE_BANG) privilege violation;
//     - a minor change to master::privilege_violation() may be required.
// Major:
//   * lfun user->query_real_name() is used to determine unique user name;
//     - a new definition for the USER_NAME() macro may be required.
//   * lfuns user->query_invis() and user->query_level() are used to check
//     if a wizard is invisible, used in main("list");
//     - a new definition of the CAN_SEE_USER() macro may be required.
// Minor:
//   * SUBST() simple string substitution macro;
//     - explode/implode default definition is provided.
//   * CAN_USE_ANSI() 'user ANSI code switch' macro;
//     - default definition assumes all users can see ANSI codes.
//   * USER_OPTIONS() 'default user options' macro;
//     - retrieve default game options for a user.
//   * PAGE_TEXT() macro in browse_scores();
//     - defalts to a basic, internal text pager.
//   * Optional USER_TIME() 'local user time' macro;
//     - score times displayed in the mud timezone, not the user timezone.
//   * Optional FIND_PLAYER() 'find_player()' macro;
//     - defaults to old LPC 'find_player()' efun.
//   * Optional FORMAT_TIME() 'time format' macro;
//     - negligible loss of message detail in main("last").


#if defined(TIMEWARP)
// Timewarp style mudlib.

#include <daemons.h>           // For PAGERD and SUSPENDD.
#include <input_to.h>

#define CAN_USE_ANSI(U)        (((U)->query_env_var("ansi")) != 0)
#define CAN_SEE_USER(U, W)     (!wizardp((W)) || !((W)->query_invis()) || (to_int((W)->query_wiz_level()) <= to_int((U)->query_wiz_level())))
#define FIND_PLAYER(N)         (_find_player((N), 1))
#define FORMAT_TIME(T)         (format_time((T)))
#define USER_TIME(U, T)        (user_time((U), (T)))
#define PAGE_TEXT(X, T)        (PAGERD->page_text((X), (T), 0, 0, "$more_opts"))
#define SUBST(S, T, R)         (subst((S), (T), (R)))

#define TETRIS_ORIGINAL        "*tetris_original"
#define SCORE_FILE             "data/misc/tetris_scores2"

#elif defined(DUNE)
// Dune style mudlib.

#include <sys/input_to.h>

#define CAN_USE_ANSI(U)        (((U)->query_env_var("ansi")) != 0)
#define CAN_SEE_USER(U, W)     (!wizardp((W)) || !((W)->query_invis()) || (to_int((W)->query_wiz_level()) <= to_int((U)->query_wiz_level())))
#define FORMAT_TIME(T)         (format_time((T), 1))
#define USER_TIME(U, T)        (localtime((U), (T)))
#define SUBST(S, T, R)         (subst((S), (T), (R)))

#if __FILE__ == "players/bubbs/stuff/tetrisd2.c"
#define PAGERD                 "players/bubbs/stuff/pagerd"
#define PAGE_TEXT(X, T)        (PAGERD->page_text((X), (T), 0, 0, "$more_opts"))
#else
#define PAGE_TEXT(X, T)        (this_player()->more_string((strlen((T)) ? ({ "[" +(T) +"]", }) : ({ })) +(X), 0, 0, 0))
#endif

#define SUSPENDD               "obj/cmds/wizard/tasks"
#define TETRIS_ORIGINAL        "*tetris_original"

#if __FILE__ == "players/bubbs/stuff/tetrisd2.c"
#define SCORE_FILE             "players/bubbs/stuff/tetris_scores2"
#else
#define SCORE_FILE             "data/daemons/tetris_scores"
#endif

#else
// Unknown mudlib.

#include <sys/input_to.h>

//#define TETRIS_ORIGINAL        "tetris_original"

#endif


// Tetris version number.
#define TETRIS_VERSION         "v2.6.1"

// Command line usage.
#define CMD_USAGE              "Usage: tetris [-bcgInr&0 | help | last | list | scores [!][<regx>] | top [<rank>] | watch <name> | watch off]\n"

#if !defined(SCORE_FILE)
// Save file for scores.
// Undefine to ignore (no persistant high scores).
#define SCORE_FILE             __DIR__ "tetris_scores"
#endif

#if !defined(MAX_HIGH_SCORES)
// Maximum number of high scores to be stored.
// Undefine to ignore (all scores are stored).
//#define MAX_HIGH_SCORES        25
//#define MAX_HIGH_SCORES        100
#define MAX_HIGH_SCORES        1000
#endif

#if !defined(MIN_HIGH_SCORE)
// Minimum score to qualify as high score.
// Undefine to ignore (all scores qualify).
#define MIN_HIGH_SCORE         2000
//#define MIN_HIGH_SCORE         10000
#endif

#if !defined(LAST_SCORE_AGE)
// Last scores stay for this long (in seconds).
//#define LAST_SCORE_AGE         (24 *60 *60)     // a day.
//#define LAST_SCORE_AGE         (2 *24 *60 *60)  // 2 days.
//#define LAST_SCORE_AGE         (7 *24 *60 *60)  // 7 days.
#define LAST_SCORE_AGE         (28 *24 *60 *60)   // 28 days.
#endif

#if !defined(USER_NAME)
// The unique name of user U.
#define USER_NAME(U)           ((string)((U)->query_real_name()))
#endif

#if !defined(CAN_USE_ANSI)
// Determine if the user U can accept ANSI screen control codes.
#define CAN_USE_ANSI(U)        (1)
#endif

#if !defined(CAN_SEE_USER)
// Determine if the user U see the user W.
#define CAN_SEE_USER(U, W)     (!((W)->query_invis()) || (to_int((W)->query_level()) <= to_int((U)->query_level())))
#endif

#if !defined(FIND_PLAYER)
// How to find a player named N.
#define FIND_PLAYER(N)         (find_player((N)))
#endif

#if !defined(PAGE_TEXT)
#define PAGE_TEXT(X, T)        (page_text(0, (T), (X))
#endif

#if !defined(SUBST)
// Substitute: search a String for a Term, and Replace it.
#define SUBST(S, T, R)         (implode(explode((S), (T)), (R)))
#endif

#if !defined(USER_OPTIONS)
// Get the user U's default tetris command options.
#define USER_OPTIONS(U)        ((string)((U)->query_env_var("tetris_opts")))
#endif

#if !defined(USER_TIME)
#define USER_TIME(U, T)        (T)
#endif


#if !defined(PAGE_TEXT_LENGTH)
// Page length for internal text pager.
#define PAGE_TEXT_LENGTH       20
#endif

// Board dimensions.  The screen layout assumes 16x10.
#define BOARD_HEIGHT           16
#define BOARD_WIDTH            10

// cmds mapping values.
#define C_ACTION               0      // Action to perform.
#define C_FLAGS                1      // Flags defining when the action can be performed.

#define C_WIDTH                (C_FLAGS +1)       // Currently not used.

// games mapping values.
#define G_BOARD                0      // State of play.
#define G_LINES                1      // Number of lines.
#define G_SCORE                2      // Score.
#define G_LEVEL                3      // Current level.
#define G_RANK                 4      // Current rank.
#define G_BLOCKS               5      // Number of blocks.
#define G_CURR_NAME            6      // Name of current block.
#define G_CURR_DEFN            7      // Current block definition.
#define G_CURR_VAL             8      // Score for placing current block.
#define G_X_COORD              9      // x co-ordinate of current block.
#define G_Y_COORD              10     // y co-ordinate of current block.
#define G_TURN                 11     // Turn counter; reset every new level.
#define G_NEXT_NAME            12     // Name of next block.
#define G_NEXT_DEFN            13     // Next block definition.
#define G_NEXT_VAL             14     // Score for placing next block.
#define G_FLAGS                15     // Game state flags.
#define G_STATS                16     // Mapping: block_name: frequency.
#define G_DURATION             17     // Approximate time spent in play.
#define G_WATCHERS             18     // Object array of watching users.
#define G_SUSPEND_ID           19     // ID of suspended game.
#define G_CALLBACK             20     // Called when finished.

#define G_WIDTH                (G_CALLBACK +1)

// Game state / command flags.
#define F_NORMAL               0x000  // Normal command flag.
#define F_PAUSED               0x001  // Indicates game is paused.
#define F_GAME_OVER            0x002  // Indicates game is over.
#define F_SHOW_NEXT            0x004  // Toggle 'Next Block' display.
#define F_SHOW_GUIDE           0x008  // Toggle "++++" position guide.
#define F_NOISE                0x010  // Toggle "\a" display
#define F_SWAP_ROTATION        0x020  // Toggle rotation direction.
#define F_COLOUR               0x040  // Toggle colour output.
#define F_DEBUG                0x080  // Indicates game is in debug mode.
#define F_INSANE               0x100  // Start in 'insane' mode (level 10).

#if !defined(DEFAULT_FLAGS)
#define DEFAULT_FLAGS          (F_SHOW_NEXT | F_SHOW_GUIDE | F_NOISE | F_COLOUR)
#endif

// blocks mapping values.
#define B_VALUE                0      // The points value for the block.
#define B_DEFN                 1      // String array definiing block shape.

#define B_WIDTH                (B_DEFN +1)        // Currently not used.

// colour_data mapping values.
#define CD_CHARACTER           0      // The base character of the colour.
#define CD_COLOUR              1      // The ANSI code of the colour (minus 3- or 4- prefix).
#define CD_BRIGHT              2      // Indicates that the colour is bright.

#define CD_WIDTH               (CD_BRIGHT +1)     // Currently not used.

// High score array indices.
#define HS_NAME                0      // User name.
#define HS_SCORE               1      // Total score.
#define HS_LINES               2      // Number of lines.
#define HS_LEVEL               3      // Level attained.
#define HS_DATE                4      // Time/date finished.
#define HS_BLOCKS              5      // Total number of blocks.
#define HS_DURATION            6      // Approximate game length.

#define HS_SIZE                (HS_DURATION +1)   // Currently not used.

// draw_block() flags.
#define DBL_PLOT               0x001  // Draw block.
#define DBL_UNPLOT             0x002  // Clear/undraw block.


/// Tetris variables.

nosave mapping  cmds;          // Keyboard commands.
nosave mapping  games;         // Current active games.
nosave mapping  blocks;        // Block definitions.
nosave mapping  colour_data;   // Coloured block data.

mixed*          high_scores;   // Ordered array of high score data.
mapping         last_scores;   // Last score for each user, indexed by rank.


/// Tetris method prototypes.

int             main           (string str);
void            help           ();
string          query_cmd_help ();

varargs int     start_game     (mixed flags, mixed callback);

static void     end_game       (string character, string buffer);
static void     do_cmd         (string character, string buffer);
static void     fix_block      (object user);
static void     new_block      (object user);
static void     move_block     (object user, int dx, int dy);
static void     rotate_block   (object user, int reverse);
static void     drop_block     (object user);
static string   colour_string  (string str, int do_colour, int background);
static void     add_line       (object user);
static void     tell_game      (object user, string mesg);
static void     redraw_line    (object user, int line);
static void     redraw_screen  (object user);
static void     draw_games     (object user);
static void     draw_block     (object user, int draw_flags);
static int      valid_move     (object user, string* block, int nx, int ny);
static void     display_help   (object user, int mode);

void            show_scores    (int position);
void            browse_scores  (string regex, int use_pager);
static void     page_text      (string response, string title, string* text);
string*         query_scores   ();

int             watch_game     (object user);
int             stop_watch_game(object user);


/// Tetris methods.

// Initialise everything in sight.
void create() {
  cmds = ([
    "\003" :  "quit";       F_PAUSED | F_GAME_OVER,
    "\b"   :  "redraw";     F_PAUSED,
    "\t"   :  "colour";     F_PAUSED,
    "\n"   :  "fall";       F_NORMAL,
    "\012" :  "redraw";     F_PAUSED,
    "\r"   :  "fall";       F_NORMAL,
    "\018" :  "redraw";     F_PAUSED,
    "\026" :  "suspend";    F_PAUSED,
    "\e"   :  "build_key";  F_PAUSED | F_GAME_OVER,
    "\e\e" :  "quit";       F_PAUSED | F_GAME_OVER,
    "\e["  :  "build_key";  F_PAUSED | F_GAME_OVER,
    "\e[A" :  "rotate";     F_NORMAL,
    "\e[B" :  "fall";       F_NORMAL,
    "\e[C" :  "right";      F_NORMAL,
    "\e[D" :  "left";       F_NORMAL,
    "\e[G" :  "unrotate";   F_NORMAL,
    "\e[4" :  "build_key";  F_PAUSED | F_GAME_OVER,
    "\e[4~":  "drop";       F_NORMAL,
    " "    :  "drop";       F_NORMAL,
    "!"    :  "suspend";    F_PAUSED,
    "@"    :  "add_line";   F_PAUSED,
    "$"    :  "add_level";  F_PAUSED,
    "A"    :  "left";       F_NORMAL,
    "B"    :  "noise";      F_PAUSED,
    "C"    :  "colour";     F_PAUSED,
    "D"    :  "right";      F_NORMAL,
    "F"    :  "fall";       F_NORMAL,
    "G"    :  "guide";      F_PAUSED,
    "J"    :  "left";       F_NORMAL,
    "K"    :  "rotate";     F_NORMAL,
    "L"    :  "right";      F_NORMAL,
    "N"    :  "next";       F_PAUSED,
    "P"    :  "pause";      F_PAUSED,
    "Q"    :  "quit";       F_PAUSED | F_GAME_OVER,
    "R"    :  "rotation";   F_PAUSED,
    "S"    :  "rotate";     F_NORMAL,
    "U"    :  "unrotate";   F_NORMAL,
    "X"    :  "quit";       F_PAUSED | F_GAME_OVER,
    "Z"    :  "suspend";    F_PAUSED,
    "*"    :  "guide";      F_PAUSED,
    "+"    :  "pause";      F_PAUSED,
    ","    :  "drop";       F_NORMAL,
    "-"    :  "next";       F_PAUSED,
    "/"    :  "rotation";   F_PAUSED,
    "0"    :  "fall";       F_NORMAL,
    "2"    :  "drop";       F_NORMAL,
    "4"    :  "left";       F_NORMAL,
    "5"    :  "rotate";     F_NORMAL,
    "6"    :  "right";      F_NORMAL,
    "7"    :  "left";       F_NORMAL,
    "8"    :  "unrotate";   F_NORMAL,
    "9"    :  "right";      F_NORMAL,
    "a"    :  "left";       F_NORMAL,
    "b"    :  "noise";      F_PAUSED,
    "c"    :  "colour";     F_PAUSED,
    "d"    :  "right";      F_NORMAL,
    "f"    :  "fall";       F_NORMAL,
    "g"    :  "guide";      F_PAUSED,
    "j"    :  "left";       F_NORMAL,
    "k"    :  "rotate";     F_NORMAL,
    "l"    :  "right";      F_NORMAL,
    "n"    :  "next";       F_PAUSED,
    "p"    :  "pause";      F_PAUSED,
    "q"    :  "quit";       F_PAUSED | F_GAME_OVER,
    "r"    :  "rotation";   F_PAUSED,
    "s"    :  "rotate";     F_NORMAL,
    "u"    :  "unrotate";   F_NORMAL,
    "x"    :  "quit";       F_PAUSED | F_GAME_OVER,
    "z"    :  "suspend";    F_PAUSED,
    "\127" :  "redraw";     F_PAUSED,
  ]);
  games = ([:G_WIDTH ]);
  blocks = ([
    "I":  30;  ({ "rrrr",        }),
    "L":  40;  ({ "mmm",  "m  ", }),
    "T":  35;  ({ "bbb",  " b ", }),
    "R":  40;  ({ "yyy",  "  y", }),
    "#":  40;  ({ "cc",   "cc",  }),
    "Z":  50;  ({ "oo ",  " oo", }),
    "S":  50;  ({ " gg",  "gg ", }),
  ]);
  colour_data = ([
    " ":  " ";  0;  0,
    "n":  "#";  0;  0,
    "r":  " ";  1;  0,
    "g":  " ";  2;  0,
    "o":  " ";  3;  0,
    "y":  " ";  7;  0,
    "b":  " ";  4;  0,
    "m":  " ";  5;  0,
    "c":  " ";  6;  0,
    "w":  " ";  7;  0,
    "*":  " ";  (: 1 +random(7) :);  0,
  ]);
  last_scores = ([:HS_SIZE ]);

#if defined(SCORE_FILE)
  restore_object(SCORE_FILE);
#endif
  if (!pointerp(high_scores))
    high_scores = ({ });
  if (sizeof(high_scores)) {
    for(int index = sizeof(high_scores); index-- > 0; )
      switch(sizeof(high_scores[index])) {
        case HS_NAME:
        case HS_SCORE:
          // rejected.
          high_scores[index..index] = ({ });
        break;
        case HS_LINES:
        case HS_LEVEL:
        case HS_DATE:
        case HS_BLOCKS:
        case HS_DURATION:
          // accepted with changes.
          high_scores[index] += allocate(HS_SIZE -sizeof(high_scores[index]));
        break;
        case HS_SIZE:
        default:
          // accepted as stands.
        break;
      }
  }
  else
    high_scores = ({ });
}


// Make the blocks fall, and add lines.
void heart_beat() {
  int s = sizeof(games);
  if (!s)
    set_heart_beat(0);

  foreach(object user : games) {
    if (query_input_pending(user) != this_object())
      games[user, G_FLAGS] |= F_PAUSED;
    if (games[user, G_FLAGS] & (F_PAUSED | F_GAME_OVER))
      continue;

    games[user, G_TURN]++;
    games[user, G_DURATION] += 2;
    tell_game(user,
      sprintf("\e[21;1HTime  %02d:%02ds",
        games[user, G_DURATION] /60, games[user, G_DURATION] %60));

    if ((games[user, G_LEVEL] > 1) &&
        !(games[user, G_TURN] %(45 -(4 *games[user, G_LEVEL])))) {
      draw_block(user, DBL_UNPLOT);
      add_line(user);
//    if (games[user, G_LEVEL] >= 9)
//      add_line(user);
      for(int l = 0; l < BOARD_HEIGHT; l++)
        redraw_line(user, l);
      draw_block(user, DBL_PLOT);
    }

    string* block = games[user, G_CURR_DEFN];
    int     x     = games[user, G_X_COORD];
    int     y     = games[user, G_Y_COORD];
    if (!valid_move(user, block, x, y +1)) {
      fix_block(user);
      new_block(user);
//    if (games[user, G_FLAGS] & F_GAME_OVER)
//      continue;
    }
    else {
      draw_block(user, DBL_UNPLOT);
      games[user, G_Y_COORD] = ++y;
      draw_block(user, DBL_PLOT);
    }
  }
}


// Main interface method; primary entry point.
int main(string str) {
  if ((str == "-?") || (str == "usage"))
    return notify_fail(CMD_USAGE);

  else if (str && !strstr(str, "original")) {
    notify_fail("tetris: " TETRIS_ORIGINAL " not found.\n");
#if defined(TETRIS_ORIGINAL)
    return command(TETRIS_ORIGINAL +str[8..], this_player());
#endif
  }

  else if (str == "help") {
    help();
    return 1;
  }

  else if (str == "last") {
    foreach(int rank : last_scores)
      if ((time() - last_scores[rank, HS_DATE]) > LAST_SCORE_AGE)
        m_delete(last_scores, rank);

#if defined(FORMAT_TIME)
    string recently = "in the last " +FORMAT_TIME(LAST_SCORE_AGE);
#else
    string recently = "recently";
#endif
    int    size     = sizeof(last_scores);

    if (!size) {
      write("tetris: Noone has played " +recently +".\n");
      return 1;
    }

    write("tetris: " +size +" player" +((size == 1) ? " has" : "s have") +" played " +recently +":\n"
          " Name         Level  Score  Rank  Lines  Blocks  Duration  Time  Date\n");

    int* ranks = sort_array(m_indices(last_scores), (: last_scores[$1, HS_SCORE] < last_scores[$2, HS_SCORE] :));
    foreach(int rank : ranks) {
#if defined(USER_TIME)
      string time_ended = ctime(USER_TIME(this_player(), last_scores[rank, HS_DATE]));
#else
      string time_ended = ctime(last_scores[rank, HS_DATE]);
#endif
      printf(" %-12s  %2d    %5d  %4s  %4d  %5d     %02d:%02ds   %s %s/%s/%s\n",
        capitalize(last_scores[rank, HS_NAME]),
        last_scores[rank, HS_LEVEL],
        last_scores[rank, HS_SCORE],
        (rank < 0) ? "" : to_string(rank +1),
        last_scores[rank, HS_LINES], last_scores[rank, HS_BLOCKS],
        last_scores[rank, HS_DURATION] /60, last_scores[rank, HS_DURATION] %60,
        time_ended[11..15], time_ended[8..9], time_ended[4..6], time_ended[22..23]);
    }
    return 1;
  }

  else if (str == "list") {
    object* us   = filter(m_indices(games), (: CAN_SEE_USER($1, $2) :), this_player());
    int     size = sizeof(us);

    if (!size) {
      write("tetris: Noone currently playing.\n");
      return 1;
    }

    write("tetris: " +size +" player" +((size == 1) ? " is" : "s are") +" currently playing:\n"
          " Name         Level  Score  Rank  Lines  Blocks  Duration\n");

    us = sort_array(us, (: USER_NAME($2) > USER_NAME($1) :));
    foreach(object user : us)
      printf(" %-12s  %2d    %5d  %4s  %4d  %5d     %02d:%02ds%s%s\n",
        capitalize(USER_NAME(user)), games[user, G_LEVEL], games[user, G_SCORE],
        (games[user, G_RANK] == -1) ? "" : to_string(games[user, G_RANK] +1),
        games[user, G_LINES], games[user, G_BLOCKS],
        games[user, G_DURATION] /60, games[user, G_DURATION] %60,
        (games[user, G_FLAGS] & F_PAUSED) ? " (paused)" : "",
        (games[user, G_FLAGS] & F_GAME_OVER) ? " (game over)" : "");
    return 1;
  }

  else if ((str == "scores") || (str == "high scores") || (str == "browse")) {
    browse_scores(0, 1);
    return 1;
  }

  else if (str == "scores!") {
    browse_scores(0, 0);
    return 1;
  }

  else if (str && (!strstr(str, "scores") || !strstr(str, "browse"))) {
    string pattern   = trim(str[6..]);
    int    use_pager = (member(pattern, '!') != 0);
    if (!use_pager)
      pattern = SUBST(pattern, "!", "");
    switch(pattern) {
      case "all":
        pattern = 0;
      break;
      case "me":
        pattern = "  " +capitalize(USER_NAME(this_player())) +" ";
      break;
      case "me today":
#if defined(USER_TIME)
        pattern = ctime(USER_TIME(this_player(), time()));
#else
        pattern = ctime();
#endif
        pattern = " " +pattern[8..9] +"/" +pattern[4..6] +"/" +pattern[22..23]
          +"  " +capitalize(USER_NAME(this_player())) +" ";
      break;
      case "today":
#if defined(USER_TIME)
        pattern = ctime(USER_TIME(this_player(), time()));
#else
        pattern = ctime();
#endif
        pattern = " " +pattern[8..9] +"/" +pattern[4..6] +"/" +pattern[22..23] +" ";
      break;
    }

    browse_scores(pattern, use_pager);
    return 1;
  }

  else if ((str == "top") || (str == "top scores")) {
    show_scores(-1);
    return 1;
  }

  else if (str && !strstr(str, "top ")) {
    int num = to_int(trim(str[4..]));
    if (num < 1)
      return notify_fail("tetris: Unable to display scores; requires a rank number.\n");

    show_scores(num -1);
    return 1;
  }

  else if ((str == "watch off") || (str == "off")) {
    int ok = stop_watch_game(0);
    if (ok)
      write("tetris: Stopped watching game.\n");
    else
      write("tetris: Unable to stop watching game.\n");
    return 1;
  }

  else if (str && !strstr(str, "watch ")) {
    string name = trim(str[6..]);
    object user = FIND_PLAYER(name);
    if (!user)
      return notify_fail("tetris: Player \"" +name +"\" not found.\n");
    if (!CAN_USE_ANSI(this_player()))
      return notify_fail("tetris: You must set \"ansi\" to watch tetris.\n");

    int ok = watch_game(user);
    if (!ok)
      write("tetris: Unable to start watching game.\n");
    return 1;
  }

  string env_var = USER_OPTIONS(this_player());
  string opts    = "&";

  if (strlen(str) && !member(str, '-')) {
    int pos = member(str, ' ');
    if (pos != -1) {
      opts = str[1..pos -1];
      str  = trim(str[pos..]);
    }
    else {
      opts = str[1..];
      str  = 0;
    }
  }

  int options = 0;
  for(opts = opts[0..]; strlen(opts); opts = opts[1..])
    switch(opts[0]) {
      case 'D':  options |= F_DEBUG;          break;
      case 'b':  options |= F_NOISE;          break;
      case 'c':  options |= F_COLOUR;         break;
      case 'g':  options |= F_SHOW_GUIDE;     break;
      case 'I':  options |= F_INSANE;         break;
      case 'n':  options |= F_SHOW_NEXT;      break;
      case 'r':  options |= F_SWAP_ROTATION;  break;
      case '0':  options = 0;                 break;
      case '&':
        if (stringp(env_var))
          opts = opts[..0] +SUBST(env_var, "&", "") +opts[1..];
        else
          options |= DEFAULT_FLAGS;
      break;
      default :
        write("tetris: Ignored unknown option '" +opts[0..0] +"'.\n");
      break;
    }

  if (strlen(str))
    return notify_fail(CMD_USAGE);

  if (start_game(options))
    return 1;
  return 0;
}


// Display command help text.
void help() {
  write(query_cmd_help());
}


// Command help text.
string query_cmd_help() {
  return CMD_USAGE
         "With no argument, start, or resume, a game of Tetris.\n"
         "Game options may be specified at the command line, or changed in-game.\n"
#if defined(TIMEWARP) || defined(DUNE)
         "You may store your personal preferences in the \"tetris_opts\" variable.\n"
#endif
         "The game options available are:\n"
         "  b  (default on)   Turns on noise mode.\n"
         "  c  (default on)   Turns on colour mode.\n"
         "  g  (default on)   Turns on 'block guide' display.\n"
         "  I  (default off)  Start the game at level 10.\n"
         "  n  (default on)   Turns on 'next block' display.\n"
         "  r  (default off)  Swaps direction of rotation.\n"
         "  &                 Includes the default arguments.\n"
         "  0                 Clears previously selected options.\n"
         "The other arguments perform specific actions:\n"
         "  help              Shows this help text.\n"
         "  last              Displays information on the most recent games.\n"
         "  list              Displays information on current active games.\n"
         "  scores [!]        Browses all stored scores, '!' suppresses pager.\n"
         "  scores [!]<regx>  Browses filtered stored scores, '!' suppress pager.\n"
         "                    Special filters \"me\", \"today\", \"me today\".\n"
         "  top               Displays the top scores.\n"
         "  top <rank>        Displays the top scores, and around <rank>.\n"
         "  watch <name>      Starts watching the named game.\n"
         "  watch off         Stops watching all games.\n"
         "";
}


// Start playing; secondary entry point.
// int start_game();
// int start_game(closure callback);
// int start_game(closure callback, int flags);
// int start_game(int flags);
// int start_game(int flags, closure callback);
varargs int start_game(varargs mixed* args) {
  if (!cmds)
    create();

  closure callback = 0;
  int     flags    = DEFAULT_FLAGS;

  switch(sizeof(args)) {
    case 0:
    break;
    case 1:
      if (closurep(args[0]))
        callback = (closure)(args[0]);
      else if (intp(args[0]))
        flags = (int)(args[0]);
      else
        raise_error("start_game(): Bad type to argument 1.\n");
    break;
    case 2:
      if (closurep(args[0])) {
        callback = (closure)(args[0]);
        if (intp(args[1]))
          flags = (int)(args[1]);
        else
          raise_error("start_game(): Bad type to argument 2.\n");
      }
      else if (intp(args[0])) {
        flags = (int)(args[0]);
        if (closurep(args[1]))
          callback = (closure)(args[1]);
        else
          raise_error("start_game(): Bad type to argument 2.\n");
      }
      else
        raise_error("start_game(): Bad type to argument 1.\n");
    break;
    default:
      raise_error("start_game(): Too many arguments specified.\n");
    break;
  }

  object user = this_player();
  if (query_input_pending(user) || query_editing(user)) {
    write("You are too busy to play tetris.\n");
    return 0;
  }

  if (!CAN_USE_ANSI(user)) {
    write("You must set \"ansi\" to play tetris.\n");
    return 0;
  }

  if (member(games, user)) {
    if (callback) {
      if (games[user, G_CALLBACK])
        return 0;
      games[user, G_CALLBACK] = callback;
    }
    games[user, G_FLAGS] = flags;
#if defined(SUSPENDD)
    games[user, G_SUSPEND_ID] = -1;
#endif
    redraw_screen(user);
    input_to("do_cmd", INPUT_NOECHO | INPUT_CHARMODE | INPUT_IGNORE_BANG, "");
    return 1;
  }

  stop_watch_game(0);
  games[user, G_BOARD]      = allocate(BOARD_HEIGHT, " " *BOARD_WIDTH);
  games[user, G_SCORE]      = 0;
  games[user, G_LINES]      = 0;
  games[user, G_LEVEL]      = (flags & F_INSANE) ? 10 : 1;
  games[user, G_RANK]       = -1;
  games[user, G_BLOCKS]     = 0;
  string curr_block = m_indices(blocks)[random(sizeof(blocks))];
  games[user, G_CURR_NAME]  = curr_block;
  games[user, G_CURR_DEFN]  = blocks[curr_block, B_DEFN];
  games[user, G_CURR_VAL]   = blocks[curr_block, B_VALUE];
  games[user, G_X_COORD]    = to_int(to_float(BOARD_WIDTH - strlen(blocks[curr_block, B_DEFN][0])) /2);
  games[user, G_Y_COORD]    = 0;
  games[user, G_TURN]       = 0;
  string next_block = m_indices(blocks)[random(sizeof(blocks))];
  games[user, G_NEXT_NAME]  = next_block;
  games[user, G_NEXT_DEFN]  = blocks[next_block, B_DEFN];
  games[user, G_NEXT_VAL]   = blocks[next_block, B_VALUE];
  games[user, G_FLAGS]      = flags;
  games[user, G_STATS]      = ([ ]);
  games[user, G_DURATION]   = 0;
  games[user, G_WATCHERS]   = ({ });
#if defined(SUSPENDD)
  games[user, G_SUSPEND_ID] = -1;
#endif
  games[user, G_CALLBACK]   = callback;

  redraw_screen(user);
  if (sizeof(games) == 1)
    set_heart_beat(1);
  input_to("do_cmd", INPUT_NOECHO | INPUT_CHARMODE | INPUT_IGNORE_BANG, "");

  return 1;
}


// Terminate the game.
static void end_game(string character, string buffer) {
  object user     = this_player();
  string key_defn = sprintf("%s%s", buffer, character);

  if (cmds[key_defn, C_ACTION] == "build_key") {
    input_to("end_game", INPUT_NOECHO | INPUT_CHARMODE | INPUT_IGNORE_BANG, key_defn);
    return;
  }

  else if (key_defn != " ") {
    input_to("end_game", INPUT_NOECHO | INPUT_CHARMODE | INPUT_IGNORE_BANG, "");
    return;
  }

  map(filter(games[user, G_WATCHERS], #'objectp), #'remove_input_to, "continue_watch_game");

  int qualify = 1;
#if defined(MIN_HIGH_SCORE)
  qualify = (games[user, G_SCORE] > MIN_HIGH_SCORE);
#endif
  int rank = -1;
  if (qualify) {
    rank = -1;
    int s = sizeof(high_scores);
    for(int i = 0; (i < s) && (rank == -1); i++)
      if (games[user, G_SCORE] > high_scores[i][HS_SCORE])
        rank = i;
#if defined(MAX_HIGH_SCORES)
    qualify = ((rank == -1) ? s : rank) < MAX_HIGH_SCORES;
#endif
  }

  mixed* score       = allocate(HS_SIZE);
  score[HS_NAME]     = USER_NAME(user);
  score[HS_SCORE]    = games[user, G_SCORE];
  score[HS_LINES]    = games[user, G_LINES];
  score[HS_LEVEL]    = games[user, G_LEVEL];
  score[HS_DATE]     = time();
  score[HS_BLOCKS]   = games[user, G_BLOCKS];
  score[HS_DURATION] = games[user, G_DURATION];

  if (qualify) {
    if (rank == -1) {
      high_scores += ({ score, });
      rank = sizeof(high_scores);
    }
    else
      high_scores[rank..rank] = ({ score, high_scores[rank], });
#if defined(MAX_HIGH_SCORES)
    high_scores = high_scores[0..MAX_HIGH_SCORES -1];
    if (rank == sizeof(high_scores))
      rank = -1;
#endif
  }

#if 0
  mapping ls = ([:HS_SIZE ]);
  foreach(int score_rank : last_scores)
    if (last_scores[score_rank, HS_NAME] != score[HS_NAME]) {
      int sr = score_rank;
      if (qualify && (score_rank >= rank))
        sr++;
      else
        for(rank = -1; member(last_scores, rank); rank--);
      m_add(ls, sr);
      for(int lsi = 0; lsi < HS_SIZE; lsi++)
        ls[sr, lsi] = last_scores[score_rank, lsi];
    }
  last_scores = ls;
  apply(#'m_add, last_scores, rank, score);
#else
  if (!qualify)
    for(rank = -1; member(last_scores, rank); rank--);
  foreach(int last_rank : last_scores)
    if (last_scores[last_rank, HS_NAME] == score[HS_NAME])
      m_delete(last_scores, last_rank);
  apply(#'m_add, last_scores, rank, score);
#endif

#if defined(SCORE_FILE)
  save_object(SCORE_FILE);
#endif
  write("\e[H\e[m\e[2J");
  closure callback = games[user, G_CALLBACK];
  m_delete(games, this_player());

  show_scores(rank);
  if (callback)
    funcall(callback, score);
}


// Handle keyboard input.
static void do_cmd(string character, string buffer) {
  object user     = this_player();
  string key_defn = sprintf("%s%s", buffer, character);

  if (cmds[key_defn, C_ACTION] != "build_key")
    buffer = "";

  int flags       = games[user, G_FLAGS] & (F_PAUSED | F_GAME_OVER);
  if (!flags || (flags & cmds[key_defn, C_FLAGS])) {
    switch(cmds[key_defn, C_ACTION]) {
      case 0:           // Unmapped key.
        // Ignore.
      break;
      case "build_key": // Build key.
        buffer = sprintf("%s%s", buffer, character);
      break;
      case "left":      // Move left.
        move_block(user, -1, 0);
      break;
      case "rotate":    // Rotate.
        rotate_block(user, 0);
      break;
      case "right":     // Move right.
        move_block(user, 1, 0);
      break;
      case "drop":      // Drop.
        drop_block(user);
      break;
      case "fall":      // Fall.
        move_block(user, 0, 1);
      break;
      case "unrotate":  // Reverse rotate.
        rotate_block(user, F_SWAP_ROTATION);
      break;
      case "redraw":    // Redraw screen.
        redraw_screen(user);
      break;
      case "quit":      // Quit.
        end_game(" ", "");
        return;
      break;
      case "colour":    // Colour display toggle.
        games[user, G_FLAGS] ^= F_COLOUR;
        redraw_screen(user);
      break;
      case "guide":     // Show Guide toggle.
        games[user, G_FLAGS] ^= F_SHOW_GUIDE;
        tell_game(user,
          sprintf("\e[%d;%dH%s\e[H",
            5 +BOARD_HEIGHT,
            15 +(2 *games[user, G_X_COORD]),
            ((games[user, G_FLAGS] & F_SHOW_GUIDE) ? "+" : "-") *(2 *strlen(games[user, G_CURR_DEFN][0]))));
      break;
      case "next":      // Show next toggle.
        games[user, G_FLAGS] ^= F_SHOW_NEXT;
        string outp = "";
        for(int index = sizeof(games[user, G_NEXT_DEFN]); index-- > 0; )
          outp += "\e[" +(9 +index) +";2H"
            +((games[user, G_FLAGS] & F_SHOW_NEXT) ?
              colour_string(sprintf("%|4s", games[user, G_NEXT_DEFN][index]), games[user, G_FLAGS] & F_COLOUR, 1) :
              "        ");

        tell_game(user, outp +"\e[H");
      break;
      case "pause":     // Pause toggle.
        games[user, G_FLAGS] ^= F_PAUSED;
        tell_game(user,
          "\e[0;21H" +((games[user, G_FLAGS] & F_PAUSED) ? "Paused!" : "Tetris!") +"\e[H");
      break;
      case "noise":     // Noise toggle.
        games[user, G_FLAGS] ^= F_NOISE;
      break;
      case "rotation":  // Swap rotation toggle.
        games[user, G_FLAGS] ^= F_SWAP_ROTATION;
      break;
      case "suspend":   // Suspend.
        tell_game(user, "\e[H\e[0m\e[2JTetris suspended.\n");
        games[user, G_FLAGS] |= F_PAUSED;
        if (games[user, G_CALLBACK])
          funcall(games[user, G_CALLBACK], 0);
#if defined(SUSPENDD)
        else {
          outp = "Tetris [" +((flags & F_INSANE) ? "insane" : ("l" +games[user, G_LEVEL])) +"/" +games[user, G_SCORE] +"pts]";
          int sid = (int)(SUSPENDD->suspend(outp, this_object()));
          games[user, G_SUSPEND_ID] = sid;
        }
#endif
        return;
      break;
      case "add_line":  // Add a random line to the bottom of the field.
        add_line(user);
        redraw_screen(user);
      break;
      case "add_level": // Increment level (difficulty) by 1.
        if (games[user, G_LEVEL] < 10) {
          games[user, G_LEVEL]++;
          tell_game(user, "\e[3;8H" +games[user, G_LEVEL]);
        }
      break;
      default:          // Undefined command.
        tell_game(user,
          sprintf("\e[0m\e[HTetris: Unrecognised command %Q\e[H", cmds[key_defn, C_ACTION]));
      break;
    }
  }
  else if (games[user, G_FLAGS] & F_GAME_OVER) {
    tell_game(user,
      "\e[9;11H"  "+---------------------------+"
      "\e[10;11H" "|                           |"
      "\e[11;11H" "|        \e[5mGame Over!\e[25m         |"
      "\e[12;11H" "|                           |"
      "\e[13;11H" "|  Press space to continue  |"
      "\e[14;11H" "|                           |"
      "\e[15;11H" "+---------------------------+"
      "\e[0m"
      "\e[H");
    input_to("end_game", INPUT_NOECHO | INPUT_CHARMODE | INPUT_IGNORE_BANG, buffer);
    return;
  }

  // Need to check for stopped block/full lines.
  // Eh ?
  input_to("do_cmd", INPUT_NOECHO | INPUT_CHARMODE | INPUT_IGNORE_BANG, buffer);
}


// Fix the active block in place, score, and remove lines.
static void fix_block(object user) {
  // First, merge the current block into the board.
  string* block = games[user, G_CURR_DEFN];
  int     x     = games[user, G_X_COORD];
  int     y     = games[user, G_Y_COORD];
  int     depth = sizeof(block);
  int     width = strlen(block[0]);

  for(int d = 0; d < depth; d++)
    for(int w = 0; w < width; w++)
      if (games[user, G_BOARD][y +d][x +w] == ' ')
        games[user, G_BOARD][y +d][x +w] = block[d][w];

  games[user, G_STATS][games[user, G_CURR_NAME]]++;
  games[user, G_BLOCKS]++;

  // Check for any filled lines, moving the rest down.
  int num_lines = 0;    // Count of number of lines completed.
  int redraw_to = 0;    // Line to redraw 'up' to.

  for(int i = 0; i < BOARD_HEIGHT; i++)
    if (strlen(SUBST(games[user, G_BOARD][i], " ", "")) == BOARD_WIDTH) {
      num_lines++;
      redraw_to = i;
      games[user, G_BOARD][i..i] = ({ });
      games[user, G_BOARD] = ({ " " *BOARD_WIDTH, }) +games[user, G_BOARD];
    }

  if (num_lines > 0) {  // Filled 'num_lines' lines.
    if (games[user, G_FLAGS] & F_NOISE)
      tell_object(user, "\a" *num_lines);

    // Score for scoring lines.
    switch(num_lines) {
      case 1:  games[user, G_SCORE] += 100;  break;
      case 2:  games[user, G_SCORE] += 200;  break;
      case 3:  games[user, G_SCORE] += 300;  break;
      case 4:  games[user, G_SCORE] += 500;  break;
    }

    // Bonus if ALL lines blank.
    if (redraw_to == BOARD_HEIGHT-1)
      games[user, G_SCORE] += 100;

    games[user, G_LINES] += num_lines;
    for(int i = 0; i <= redraw_to; i++)
      redraw_line(user, i);

    tell_game(user,
      "\e[3;23H" +games[user, G_LINES]);
    if ((games[user, G_LEVEL] < 10) && (games[user, G_LINES] >= (10 *games[user, G_LEVEL]))) {
      games[user, G_LEVEL]++;
      games[user, G_TURN] = random(games[user, G_LEVEL]);

      tell_game(user, "\e[3;8H" +games[user, G_LEVEL]);
    }
  }

  // Score for placing the piece.
  games[user, G_SCORE] += games[user, G_CURR_VAL];

  // Calculate new rank.  Has it gone up or down ?
  int num_scores = sizeof(high_scores);
#if defined(MIN_HIGH_SCORE)
  if (games[user, G_SCORE] < MIN_HIGH_SCORE)
    games[user, G_RANK] = -1;
  else
#endif
  if (!num_scores)
    games[user, G_RANK] = 0;
  else if (games[user, G_SCORE] < high_scores[num_scores -1][HS_SCORE])
    games[user, G_RANK] = num_scores -1;
  else {
    int rank = -1;
    for(int i = 0; (i < num_scores) && (rank == -1); i++)
      if (games[user, G_SCORE] > high_scores[i][HS_SCORE])
        rank = i;

    if (rank == -1)
#if defined(MAX_HIGH_SCORES)
      rank = (num_scores < MAX_HIGH_SCORES) ? num_scores : -1;
#else
      rank = num_scores;
#endif
    else
      games[user, G_RANK] = rank;
  }

  tell_game(user,
    sprintf("\e[3;38H%-6d"
            "\e[3;53H%s    "
            "\e[%d;14H+-%*'-'c",
      games[user, G_SCORE],
      (games[user, G_RANK] == -1) ? "none" : to_string(games[user, G_RANK] +1),
      5+BOARD_HEIGHT, 2 *BOARD_WIDTH, '+'));

  string* block_names = sort_array(m_indices(games[user, G_STATS]), (: $3[$1] < $3[$2] :), games[user, G_STATS]);
  for(int i = min(8, sizeof(block_names)); i-- > 0; ) {
    string stat = sprintf("%3s  %5d", block_names[i], games[user, G_STATS][block_names[i]]);
    if (games[user, G_FLAGS] & F_COLOUR) {
      string col_str = SUBST(implode(blocks[block_names[i], B_DEFN], ""), " ", "");
      stat = SUBST(colour_string(col_str[random(strlen(col_str))..][0..0], F_COLOUR, 0), "  ", stat);
    }
    tell_game(user, "\e[" +(13 +i) +";1H" +stat);
  }

  if (games[user, G_BLOCKS])
    tell_game(user, sprintf("\e[20;1HTotal%5d", games[user, G_BLOCKS]));
  tell_game(user, "\e[H");
}


// Affix the active block to the board, score and count and remove completed
// lines, then, create the new active block and place it on the board.
static void new_block(object user) {
  // Then move the next block to current block.
  string* block = games[user, G_NEXT_DEFN];
  games[user, G_CURR_NAME] = games[user, G_NEXT_NAME];
  games[user, G_CURR_DEFN] = block;
  games[user, G_CURR_VAL]  = games[user, G_NEXT_VAL];

  // Determine its' position at the top of the board.
  int x = to_int(to_float(BOARD_WIDTH -strlen(block[0])) /2);
  int y = 0;

  // If the block cannot be placed; game over.
  if (!valid_move(user, block, x, y)) {
    games[user, G_FLAGS] |= F_GAME_OVER;
    return;
  }

  // Set the position.
  games[user, G_X_COORD] = x;
  games[user, G_Y_COORD] = y;

  // Draw the block.
  draw_block(user, DBL_PLOT);

  // Select a new next block.
  string block_name = m_indices(blocks)[random(sizeof(blocks))];
  games[user, G_NEXT_NAME] = block_name;
  games[user, G_NEXT_DEFN] = blocks[block_name, B_DEFN];
  games[user, G_NEXT_VAL]  = blocks[block_name, B_VALUE];

  // Draw the next, if required.
  if (games[user, G_FLAGS] & F_SHOW_NEXT) {
    // And display the next block.
    int w = sizeof(block);
    block = games[user, G_NEXT_DEFN];
    int d = sizeof(block);
    if (w < d)
      w = d;
    for(; w-- > 0; )
      tell_game(user,"\e[" +(9 +w) +";2H"
        +((w < d) ?
          colour_string(sprintf("%|4s", block[w]), games[user, G_FLAGS] & F_COLOUR, 1) :
          "        "));
  }

  tell_game(user, "\e[H");
}


// Add an incomplete line of 'bits and pieces' from the bottom.
static void add_line(object user) {
  if (strlen(SUBST(games[user, G_BOARD][0], " ", ""))) {
    games[user, G_FLAGS] |= F_GAME_OVER;
    return;
  }

  string line = "*" *BOARD_WIDTH;
  // Insert one space, to guarentee that the line is incomplete.
  line[random(BOARD_WIDTH)] = ' ';

  // Add some more, maybe.
  for(int i = 0; i < BOARD_WIDTH; i++)
    if (!random(14 - games[user, G_LEVEL]))
      line[i] = ' ';

  games[user, G_BOARD] = games[user, G_BOARD][1..] +({ line, });

  // Whoever called this needs to redraw.
  if (games[user, G_FLAGS] & F_NOISE)
    tell_object(user, "\a");
}


// Move the active block around.
static void move_block(object user, int dx, int dy) {
  string* block = games[user, G_CURR_DEFN];
  int     nx    = games[user, G_X_COORD] + dx;
  int     ny    = games[user, G_Y_COORD] + dy;
  // Check that block can move into new position.
  if (valid_move(user, block, nx, ny)) {
    draw_block(user, DBL_UNPLOT);
    games[user, G_X_COORD] = nx;
    games[user, G_Y_COORD] = ny;
    draw_block(user, DBL_PLOT);
  }
}


// Rotate the active block.
static void rotate_block(object user, int reverse) {
  string* block = games[user, G_CURR_DEFN];
  mixed*  def   = map(map(block, #'to_array), #'-, ({ 0, }));

  // The next couple of lines 'rotate' the block definition by 90 degrees.
  if (reverse ^(games[user, G_FLAGS] & F_SWAP_ROTATION))
    def = transpose_array(sort_array(def, #'+));
  else
    def = sort_array(transpose_array(def), #'+);

  string* rot_block = map(def, #'to_string);

  // Apply an offset to the block, so it pivots nicely.
  int x      = games[user, G_X_COORD];
  int y      = games[user, G_Y_COORD];
  int offset = (sizeof(rot_block) - sizeof(block)) /2;
  if (offset) {
    x = min(max(x +offset, 0), BOARD_WIDTH -1);
    y = min(max(y -offset, 0), BOARD_HEIGHT -1);
  }

  // Need to check we can rotate the block.
  if (valid_move(user, rot_block, x, y)) {
    draw_block(user, DBL_UNPLOT);
    games[user, G_CURR_DEFN] = rot_block;
    games[user, G_X_COORD]   = x;
    games[user, G_Y_COORD]   = y;
    draw_block(user, DBL_PLOT);
  }
}


// Drop the active block into the board.
static void drop_block(object user) {
  draw_block(user, DBL_UNPLOT);

  string* block = games[user, G_CURR_DEFN];
  int     x     = games[user, G_X_COORD];
  int     y     = games[user, G_Y_COORD];

  while(valid_move(user, block, x, y+1))
    y++;
  games[user, G_Y_COORD] = y;

  draw_block(user, DBL_PLOT);
  fix_block(user);
  new_block(user);
}


// Check if the active block can be moved.
static int valid_move(object user, string* block, int nx, int ny) {
  if ((nx < 0) || (ny < 0))
    return 0;

  int depth = sizeof(block);
  if ((ny +depth) > BOARD_HEIGHT)
    return 0;

  int width = strlen(block[0]);
  if ((nx +width) > BOARD_WIDTH)
    return 0;

  string* board = map(games[user, G_BOARD][ny..ny +depth -1], #'[..], nx, nx +width -1);
  int     valid = 1;

  for(int d = 0; (d < depth) && valid; d++)
    for(int w = 0; (w < width) && valid; w++)
      valid = ((block[d][w] == ' ') || (board[d][w] == ' '));
  return valid;
}


// Send a message to a game (to the player and any watchers).
static void tell_game(object user, string mesg) {
  tell_object(user, mesg);
  if (!member(games, user))
    return;

  games[user, G_WATCHERS] = filter(filter(games[user, G_WATCHERS], #'objectp), #'interactive);
  map(games[user, G_WATCHERS], #'tell_object, mesg);
}


// Draw, or clear, the active block somewhere on the board.
static void draw_block(object user, int draw_flags) {
  string* block  = games[user, G_CURR_DEFN];
  int     depth  = sizeof(block);
  int     width  = strlen(block[0]);
  int     x      = games[user, G_X_COORD];
  int     y      = games[user, G_Y_COORD];
  string* board  = map(games[user, G_BOARD][y..y + depth -1], #'[..], x, x +width -1);
  string  output = "";
  mixed * colour_block =
    map(map(block, #'explode, ""), #'map, #'colour_string, games[user, G_FLAGS] & F_COLOUR, 1);

  for(int d = 0; d < depth; d++)
    for(int w = 0; w < width; w++)
      //if ((board[d][w] == ' ') || (draw_flags & DBL_UNPLOT))
      if (board[d][w] == ' ')
        output += "\e[" +(5  +y +d) +";" +(15 +(2 *(x +w))) +"H" +((draw_flags & DBL_UNPLOT) ? "  " : colour_block[d][w]);

  if (games[user, G_FLAGS] & F_SHOW_GUIDE)
    output += "\e[" +(5 +BOARD_HEIGHT) +";" +(15 +(2 *x)) +"H"
      +((draw_flags & DBL_UNPLOT) ? ("\e[0m" +("--" *width)) : ("\e[1m" +("++" *width) +"\e[0m"));

  tell_game(user, output +"\e[H");
}


// Redraw the whole screen.
static void redraw_screen(object user) {
  tell_game(user,
    sprintf("\e[H"    // Send cursor home.
            "\e[0m"   // Turn off screen attributes.
            "\e[2J"   // Erase entire screen.
            "                    %s\n"
            "\n"
            "Level: %-6s  Lines: %-6d  Score: %-6d   Rank: %s\n"
            "\n",
      (games[user, G_FLAGS] & F_PAUSED) ? "Paused!" : "Tetris!",
      (games[user, G_FLAGS] & F_INSANE) ? "Insane" : to_string(games[user, G_LEVEL]),
      games[user, G_LINES],
      games[user, G_SCORE],
      (games[user, G_RANK] == -1) ? "none" : to_string(games[user, G_RANK] +1)));

  for(int i = 0; i < BOARD_HEIGHT; i++)
    redraw_line(user, i);
  tell_game(user,
    sprintf("\e[%d;14H+-%*'-'c", 5 +BOARD_HEIGHT, 2 *BOARD_WIDTH, '+'));
  draw_block(user, DBL_PLOT);
  if (games[user, G_FLAGS] & F_SHOW_NEXT)
    for(int i = sizeof(games[user, G_NEXT_DEFN]); i-- > 0; )
      tell_game(user,
        sprintf("\e[%d;2H%s",
          9 +i,
          colour_string(sprintf("%|4s", games[user, G_NEXT_DEFN][i]), games[user, G_FLAGS] & F_COLOUR, 1)));

  string* block_names = sort_array(m_indices(games[user, G_STATS]), (: $3[$1] < $3[$2] :), games[user, G_STATS]);
  for(int i = min(8, sizeof(block_names)); i-- > 0; ) {
    string stat = sprintf("%3s  %5d", block_names[i], games[user, G_STATS][block_names[i]]);
    if (games[user, G_FLAGS] & F_COLOUR) {
      string col_str = SUBST(implode(blocks[block_names[i], B_DEFN], ""), " ", "");
      stat = SUBST(colour_string(col_str[random(strlen(col_str))..][0..0], F_COLOUR, 0), "  ", stat);
    }
    tell_game(user, "\e[" +(13 +i) +";1H" +stat);
  }

  if (games[user, G_BLOCKS])
    tell_game(user,
      sprintf("\e[20;1HTotal%5d", games[user, G_BLOCKS]));
  tell_game(user,
    sprintf("\e[21;1HTime  %02d:%02ds",
      games[user, G_DURATION] / 60, games[user, G_DURATION] % 60));
  tell_game(user, "\e[5;1H"    "Tetris " TETRIS_VERSION
                  "\e[7;1H"    "Next Block"
                  "\e[12;1H"   "Block Stats");

  display_help(user, 0);
  tell_game(user, "\e[H");
}


// Display the help text.
static void display_help(object user, int mode) {
  int* x = 0;
  // At some point, somebody might come up with a way to nicely display help
  // in vs. mode.  For now, assume no help is needed.
//if (mode == MODE_VS_LEFT || mode == MODE_VS_RIGHT)
//  return;
  x = allocate(15, BOARD_WIDTH +28);
  x[0] += 8;

  tell_game(user,
    apply(#'sprintf, "\e[5;%dH"   "Keys"
                     "\e[7;%dH"   "left    4  A  J  Left"
                     "\e[8;%dH"   "up      5  S  K  Rotate"
                     "\e[9;%dH"   "right   6  D  L  Right"
                     "\e[10;%dH"  "enter   down  0  Fall"
                     "\e[11;%dH"  "space   ,  2     Drop"
                     "\e[13;%dH"  "P       +        Pause"
                     "\e[15;%dH"  "N       -        Toggle Next"
                     "\e[14;%dH"  "C       tab      Toggle Colour"
                     "\e[16;%dH"  "G       *        Toggle Guide"
                     "\e[17;%dH"  "R       /        Toggle Rotation"
                     "\e[18;%dH"  "B                Toggle Noise"
                     "\e[19;%dH"  "delete  ^L ^R    Redraw Screen"
                     "\e[20;%dH"  "Z       !  ^Z    Suspend"
                     "\e[21;%dH"  "Q       X  ^C    Quit", x));
  return;
}


// Redraw a specific line of the board.
static void redraw_line(object user, int line) {
  tell_game(user,
    "\e[" +(5 +line) +";14H|" +colour_string(games[user, G_BOARD][line], games[user, G_FLAGS] & F_COLOUR, 1) +"|");
  return;
}


// Apply (or not) colour to a string, making it suitable for display.
static string colour_string(string str, int do_colour, int background) {
  string outp = "";
  int    size = strlen(str);

  if (!do_colour) {
    outp = str;
    for(int index = size; index-- > 0; )
      outp[index..index] = outp[index..index] +outp[index..index];
    return outp;
  }

  int colour = 0;
  int bright = 0;
  for(int index = 0; index < size; index++) {
    string new_char = 0;
    int new_colour = 0;
    int new_bright = 0;
    if (member(colour_data, str[index..index])) {
      new_char   = funcall(colour_data[str[index..index], CD_CHARACTER]);
      new_colour = funcall(colour_data[str[index..index], CD_COLOUR]);
      new_bright = funcall(colour_data[str[index..index], CD_BRIGHT]);
    }
    else {
      new_char   = str[index..index];
      new_colour = 0;
      new_bright = 0;
    }
    outp += sprintf("%s%s%s%s",
      // bright
      (bright ?
        (new_bright ? ""      : "\e[0m") :
        (new_bright ? "\e[1m" : ""     )),
      // colour
      (new_colour ?
        (!colour ?
          sprintf("\e[%dm", (background ? 40 : 30) +new_colour) :
          ((colour == new_colour) ?
            "" :
            sprintf("\e[%dm", (background ? 40 : 30) +new_colour))) :
        (!colour ? "" :
          (new_bright ? "\e[1m" : "\e[0m"))),
      new_char, new_char);
    bright = new_bright;
    colour = new_colour;
  }
//if (colour || bright)
  outp += "\e[0m";

  return outp;
}


// Currently not used.
// Display a summary of all other current games.
static void draw_games(object user) {
  object* us = m_indices(games);

  for(int index = sizeof(us); index-- > 0; ) {
    if (us[index] == user)
      us[index] = 0;
    else if (games[us[index], G_FLAGS] & (F_PAUSED | F_GAME_OVER))
      us[index] = 0;
  }

  us -= ({ 0, });
  int size = sizeof(us);
  if (size) {
    size = min(size, 4);
    for(int index = 0; index < size; index++) {
      int s = sizeof(games[us[index], G_BOARD]);
      for(int i = 0; i < s; i++) {
        string rem = SUBST(games[us[index], G_BOARD][i], " ", "");
        if (strlen(rem))
          rem = rem[random(strlen(rem))..][0..0];
        tell_game(user,
          sprintf("\e[%d;%dH%s",
            5 +i, 40 +(9 *index),
            (rem == "") ? "  " : colour_string(rem, games[user, G_FLAGS] & F_COLOUR, 1)));
      }

      tell_game(user,
        sprintf("\e[21;%dH%-7.7s\e[22;%dH%d",
          40 +(9 *index),
          capitalize(USER_NAME(us[index])),
          40 +(9 *index),
          games[us[index], G_LINES]));
    }
  }
}


// Start this_player() watching a game.
int watch_game(object user) {
  if (!cmds)
    create();

  if (!member(games, user))
    return 0;

  foreach(object u : games)
    games[u, G_WATCHERS] -= ({ this_player(), 0, });

  tell_game(user,
    "\e[0m\e[H" +capitalize(USER_NAME(this_player())) +" starts watching the game.\e[H");
  if (member(games[user, G_WATCHERS], this_player()) == -1)
    games[user, G_WATCHERS] += ({ this_player(), });
  redraw_screen(user);

  // LDMud 3.2.11-dev.707 doesn't handle remove_input_to() on CHARMODE input_to()s nicely.
  //input_to("continue_watch_game", INPUT_NOECHO | INPUT_CHARMODE | INPUT_IGNORE_BANG);
  input_to("continue_watch_game");
  return 1;
}


// Stop this_player() watching a game.
int stop_watch_game(object user) {
  if (!cmds)
    create();

  if (!user)
    return sizeof(filter(m_indices(games), #'stop_watch_game)) != 0;

  if (!user) {
    object* us = m_indices(games);
    for(int index = sizeof(us); (index-- > 0) && !user; )
      if (member(games[us[index], G_WATCHERS], this_player()) != -1)
        user = us[index];
  }

  if (!user || !member(games, user) ||
      (member(games[user, G_WATCHERS], this_player()) == -1))
    return 0;

  games[user, G_WATCHERS] -= ({ this_player(), 0, });
  write("\e[H\e[m\e[2J");
  tell_game(user,
    "\e[0m\e[H" +capitalize(USER_NAME(this_player())) +" stops watching the game.\e[H");
  return 1;
}


// Display a particular score, or the top scores.
void show_scores(int position) {
  if (!cmds)
    create();

  if (position < 0)
    position = -1;

  string header = "Tetris " TETRIS_VERSION ": Scores";
  switch(position) {
    case 0:
      header = "Tetris " TETRIS_VERSION ": *Supreme* *Score*";
    break;
    case 1..4:
      header = "Tetris " TETRIS_VERSION ": Excellent Score!";
    break;
    case 5..9:
      header = "Tetris " TETRIS_VERSION ": Great Score!";
    break;
    case 10..19:
      header = "Tetris " TETRIS_VERSION ": Good Score!";
    break;
    default:
      header = "Tetris " TETRIS_VERSION ": Top Scores";
    break;
  }

  string* output = query_scores();
  int     width  = strlen(output[0]);
  printf("%|*s\n"
         "%|*s\n"
         "%|*s\n"
         "\n",
    width, header,
    width, "-" *(strlen(header) +4),
    width, trim(output[0]));

  int size = sizeof(high_scores);
  if (!size)
    return;

  if ((position != -1) && (position < size))
    output[position +2] = "\e[1m*" +output[position +2][1..] +"\e[0m";
  write(implode(output[2..min(10, size) +1], "\n") +"\n");

  int start = max(position -4, 10);
  if (start > 10)
    printf("%|*s\n",

      width, "-" *(strlen(header) +4));
  write(implode(output[start +2..min(start +10, size) +1], "\n") +"\n");
}


// View all,or some, of the scores.
void browse_scores(string regex, int use_pager) {
  if (!cmds)
    create();

  int size = sizeof(high_scores);
  if (!size)
    write("Tetris " TETRIS_VERSION ": No scores found.\n");

  else {
    string* scores = query_scores();
    if (regex && strlen(regex)) {
      regex = regreplace(regex, "[a-zA-Z]",
        (: "[" +upper_case($1) +lower_case($1) +"]" :), 1);
      if (catch(scores = scores[0..1] +regexp(scores[2..], regex); nolog)) {
        write("tetris: Bad regular expression.\n");
        return;
      }
    }

    int    s      = sizeof(scores) -2;
    string header = "Tetris " TETRIS_VERSION ": " +size +" Top Score" +((size == 1) ? "" : "s")
      +((s == size) ? "" : (" (" +s +" shown)"));

    if (!s)
      write(header +".\n");
    else if (use_pager && (s > PAGE_TEXT_LENGTH))
      PAGE_TEXT(scores, header);
    else
      write(header +":\n" +implode(scores, "\n") +"\n");
  }
}


// Simple text pager.
static void page_text(string response, string title, string* text) {
  if (response && (member("QqXx\03", response[0]) != -1))
    return;

  write("[" +title +"]\n" +implode(text[..PAGE_TEXT_LENGTH -1], "\n") +"\n");
  text = text[PAGE_TEXT_LENGTH..];
  int size = sizeof(text);
  if (!size)
    return;

  write(title +" (" +size +" remaining): ");
  input_to(#'page_text, 0, title, text);
}


// Format high_scores nicely.
string* query_scores() {
  if (!cmds)
    create();

  int size = sizeof(high_scores);
  string* output = allocate(2 +size);

  if (size)
    output[0] = " Rank  Time  Date       Name          Score   Level  Lines  Blocks  Duration ";
  else
    output[0] = "                              No scores found.";
  output[1] = "";

  for(int index = 0; index < size; index++) {
#if defined(USER_TIME)
    string time_ended = ctime(USER_TIME(this_player(), high_scores[index][HS_DATE]));
#else
    string time_ended = ctime(high_scores[index][HS_DATE]);
#endif
    output[2 +index] = sprintf(" %|4d  %s %s/%s/%s  %-12s %6d     %|2d   %4d   %5s    %s",
      1 +index,
      time_ended[11..15], time_ended[8..9], time_ended[4..6], time_ended[22..23],
      capitalize(high_scores[index][HS_NAME]),
      high_scores[index][HS_SCORE],
      high_scores[index][HS_LEVEL],
      high_scores[index][HS_LINES],
      high_scores[index][HS_BLOCKS] ? to_string(high_scores[index][HS_BLOCKS]) : "",
      high_scores[index][HS_DURATION] ?
        sprintf("%02d:%02ds", high_scores[index][HS_DURATION] /60, high_scores[index][HS_DURATION] %60) :
        "");
  }

  return output;
}


// Accessor methods;

mixed*  query_high_scores() { if (!cmds) create(); return deep_copy(high_scores); }
mapping query_last_scores() { return deep_copy(last_scores); }
object* query_players()     { if (!cmds) create(); return m_indices(games); }
string  query_version()     { return TETRIS_VERSION; }


// Mudlib and driver integration methods;

#if defined(SUSPENDD)
void unsuspend(int id, object this, object me) {
//  if ((this_player() != this_interactive()) || !member(games, this_player()))
//    return;
  if ((this_player() != this_interactive()) || !member(games, this_player()) ||
      (id != games[this_player(), G_SUSPEND_ID]))
    return;

  apply(#'start_game,
    ({ games[this_player(), G_FLAGS], }) +allocate(games[this_player(), G_CALLBACK] && 1, games[this_player(), G_CALLBACK]));
}
#endif

int deny_update() {
  return (sizeof(games) != 0);
}

int clean_up(int arg) {
  if (!sizeof(games))
    destruct(this_object());
  return 0;
}


// Obsolete utility methods.

//void delete_high_score(int pos) {
//  high_scores = high_scores[0..pos-1] +high_scores[pos+1..];
//  save_object(SCORE_FILE);
//}


//mapping update_last_scores() {
//  foreach(mixed name : last_scores)
//    if (stringp(name)) {
//      int rank = last_scores[name, HS_NAME];
//      if (rank == -1)
//        for(; member(last_scores, rank); rank--);
//
//      last_scores[name, HS_NAME] = name;
//      mixed* score = allocate(HS_SIZE);
//      score[HS_NAME]     = name;
//      score[HS_SCORE]    = last_scores[name, HS_SCORE];
//      score[HS_LINES]    = last_scores[name, HS_LINES];
//      score[HS_LEVEL]    = last_scores[name, HS_LEVEL];
//      score[HS_DATE]     = last_scores[name, HS_DATE];
//      score[HS_BLOCKS]   = last_scores[name, HS_BLOCKS];
//      score[HS_DURATION] = last_scores[name, HS_DURATION];
//      m_delete(last_scores, name);
//      apply(#'m_add, last_scores, rank, score);
//    }
//
//  save_object(SCORE_FILE);
//}


