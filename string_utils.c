//// string_utils.c
// A collection of string utility functions.
//
// Bubbs, 2007ish.  Last revision Aug/2011.


/*
** public string quote_string(string str);
**   DEPRECATED Create a printable version of a string.
**   A remnant from a part project, this is of no general use.
**
** public string* explode_words(string str);
** public string* explode_words(string str, string delim_chars);
**   Explode a string into words.
**   Returns words and word delimiters, regexplode() style.
**   For example:
**     printf("%#Q\n", explode_words("foo bar  burning\tblue\nblack\n"));
**
** public string capitalize_words(string str);
** public string capitalize_words(string str, string delim_chars);
**   Capitalize each word in string.
**   For example:
**     printf("%#Q\n", capitalize_words("happy go lucky"));
**
** public int is_word(string str);
** public int is_word(string str, string delim_chars);
**   Return non-zero if string is a word.
**   For example:
**     printf("%#Q, %#Q\n", is_word("ha"), is_word(" "));
**
** public string swap_case(string str);
**   Swap the case of a string.
**   For example:
**     printf("%#Q\n", swap_case("hAPPY bIRTHDAY"));
**
** public int     regmatch(string str, string regex);
** public string* regmatch(string str, string regex, varargs int* matches);
**   With two arguments, return non-zero if the string matches the regular expression.
**   Further arguments change the returned value to an array of specified bracketed sub-matches.
**   For example:
**     printf("%#Q\n", regmatch("hello world", "^(.*) (.*)$", 1, 2));
**     // ({ "hello", "world", }).
**
** public int regstrstr(string search, string regex);
** public int regstrstr(string search, string regex, int start_char);
**   Regular expression version of strstr().
**   For example:
**     printf("%#Q, %#Q\n", regstrstr("rabbit and black duck", " [a-z]."), regstrstr("rabbit and black duck", " [a-z].", 10));
**
** public int regstrrstr(string search, string regex);
** public int regstrrstr(string search, string regex, int start_char);
**   Regular expression version of strrstr().
**   For example:
**     printf("%#Q, %#Q\n", regstrrstr("rabbit and black duck", " [a-z]."), regstrrstr("rabbit and black duck", " [a-z].", 10));
**
** public string get_wildcard_regex(string pattern);
** public string get_wildcard_regex(0);
**   Convert a wildcard pattern into a regular expression.
**   Passing the argument 0 returns the most recently used regular expression.
**   For example:
**     printf("%#Q\n", get_wildcard_regex("*.c"));
**
** public int matches_wildcard(string word, string pattern);
**   Returns 1 when match against a wildcard pattern (0 = most recently used).
**   For example:
**     printf("%#Q\n", filter(({ "string_utils.c", "string_utils.h", }), #'matches_wildcard, "*.c"));
**
** public int wild_strstr(string search, string pattern);
** public int wild_strstr(string search, string pattern, int start_char);
**   Wildcard version of strstr().
**   For example:
**     printf("%#Q, %#Q\n", wild_strstr("barking mad", "a?"), wild_strstr("barking mad", "a?", 6));
**
** public int wild_strrstr(string search, string pattern);
** public int wild_strrstr(string search, string pattern, int start_char);
**   Wildcard version of strrstr().
**   For example:
**     printf("%#Q, %#Q\n", wild_strrstr("barking mad ", "a?"), wild_strrstr("barking mad ", "a?", 6));
**
** public int* find_term(string* text, string term);
** public int* find_term(string* text, string term, int flags);
** public int* find_term(string* text, string term, int flags, int start_line);
** public int* find_term(string* text, string term, int flags, int start_line, int start_char);
**   Find a term in an array of strings, supporting optional FIND_ flags and optional start position.
**   Returns 0 or ({ line_index, char_index, }).
**   For example:
**     string* text = explode(read_file("/"__FILE__) || "<unable to read file>", "\n");
**     printf("%#Q, %#Q\n", find_term(text, "string_utils"), find_term(text, "string_utils", FIND_BACKWARD));
**
** public int find_term_index(string* text, string term);
** public int find_term_index(string* text, string term, int flags);
** public int find_term_index(string* text, string term, int flags, int start_line);
** public int find_term_index(string* text, string term, int flags, int start_line, int start_char);
**   Like find_term(), but returns the found line index or -1 (ignores character index of match).
**   For example:
**     string* text = explode(read_file("/"__FILE__) || "<unable to read file>", "\n");
**     printf("%#Q, %#Q\n", find_term_index(text, "string_utils"), find_term_index(text, "string_utils", FIND_BACKWARD));
**     printf("%#Q\n", find_term_index(text, "string[_. ]utils", FIND_BACKWARD | FIND_MATCH_CASE | FIND_MATCH_REGEXP));
**
** public string* explode_term(string str, string term);
** public string* explode_term(string str, string term, int flags);
**   Explode a string over a term, supporting optional FIND_ flags.
**   For example:
**     printf("%#Q\n", explode_term("baa baa black sheep have you any wool", " |[aeiouy]+.", FIND_REGEXP));
**
** public int compare_numeric(string value1, string value2);
** public int compare_numeric(string value1, string value2, int flags);
** public int compare_numeric(mixed value1, mixed value2);
** public int compare_numeric(mixed value1, mixed value2, int flags);
**   Compares numeric strings - like "bag 1", "bag 10" nicely.
**   Also available - ignore case, non-numeric prefix, and/or whitespace.
**   Uses CMPNUM_ flags.  Used with sort_array() to sort (numeric) text.
**   If either argument is not a string, a normal comparison is done.
**   For example:
**     printf("%#Q\n", sort_array(({ "bottle", "bottle 20", "bag", "bag 10", "bag 1", "bag 2", "Bag 11", "BAG 5", }), #'compare_numeric));
**     printf("%#Q\n", sort_array(({ "bottle", "bottle 20", "bag", "bag 10", "bag 1", "bag 2", "Bag 11", "BAG 5", }), #'compare_numeric, CMPNUM_IGN_CASE));
**     printf("%#Q\n", sort_array(({ "bottle", "bottle 20", "bag", "bag 10", "bag 1", "bag 2", "Bag 11", "BAG 5", }), #'compare_numeric, CMPNUM_IGN_CASE | CMPNUM_IGN_PREFIX));
**
** public string strip_ansi_colour(string ansi_text);
**   Strip ANSI colour codes from a piece of text.
**   Note: Also strips XTerm 256 colour codes.
**   For example:
**     printf("%s\n", strip_ansi("\e[1mNo \e[35;41mcolours \e[35;40mhere."));
**
** public string* text_table(string* fields);
** public string* text_table(string* fields, int table_width);
** public string* text_table(string* fields, int table_width, int flags);
**   Create a table of text fields, like sprintf("%#s", ), but ignores ANSI colour codes.
**   Supports TXTTAB_ flags to modify the generation of the table.
**   For example:
**     printf("%s\n", implode(text_table(users()->short() -({ 0, }), 40), "\n"));
**
*/


//#include "string_utils.h"
//// string_utils.h
//
// Definitions for string utilities.


#if !defined(STRING_UTILS_H)
#define STRING_UTILS_H


/// string_utils mudlib configuration.

#if defined(TIMEWARP)
// Timewarp style mudlib.

#include <strings.h>
#include <term.h>

#define USER_WORD_DELIM_CHARS(U)       ((string)((U)->query_env_var("word_delim_chars")))
#define LARGE_WILDCARD_CACHE
#define EXTENDED_WILDCARDS
#define DEFAULT_TABLE_WIDTH            (GET_TERM_WIDTH(this_player()) -1)

//
#elif defined(DUNE)
// Dune style mudlib.

#include <sys/strings.h>
#include <term.h>

#define USER_WORD_DELIM_CHARS(U)       ((string)((U)->query_env_var("word_delim_chars")))
#define LARGE_WILDCARD_CACHE
#define EXTENDED_WILDCARDS
#define DEFAULT_TABLE_WIDTH            (GET_TERM_WIDTH(this_player()) -1)

//
#else
// Unknown 2.4.5 style mudlib.

#include <sys/strings.h>

// explode_words(): if defined, provide a mechanism to get user word delim chars
////#define USER_WORD_DELIM_CHARS(U)       ((string)((U)->query_env_var("word_delim_chars")))
//#define NO_USER_WORD_DELIM_CHARS

// explode_words(): default regular expression to match world delimiters.
//#define WORD_DELIM_REGEXP              "[\t -/:-@[-^_`{-~]+"

// explode_words(): additional word delimiter characters always added to user specified characters.
//#define EXTRA_WORD_DELIM_CHARS         "\n\f\r\t "

// regmatch(): match delimiter string.
// arguments containing this string will cause regmatch() sub-matching to break.
//#define REGMATCH_SUBMATCH_DELIMITER    "\n\b\a\f\e\n"

// get_wildcard_regex(): use a small wildcard cache, storing only the most recently used wildcard.
// otherwise all used (and most recent) wildcards are stored in a mapping.
//#define SMALL_WILDCARD_CACHE
////#define LARGE_WILDCARD_CACHE

// get_wildcard_regex(): extended wildcards support allows ranges and lists.
// range example: "room[0-9!4-6].c"        gives regex "room[0-9^4-6].c".
// list example : "room_{red,bl*,green}.c" gives regex "room_(red|bl.*|green)\\.c".
////#define EXTENDED_WILDCARDS
//#define NO_EXTENDED_WILDCARDS

// find_term(), explode_term(): default search flags.
//#define DEFAULT_FIND_FLAGS             FIND_WRAP

// compare_numeric(): default flags.
//#define DEFAULT_CMPNUM_FLAGS           0

// text_table(): default table flags.
//#define DEFAULT_TXTTAB_FLAGS           0

// text_table(): default table width.
//#define DEFAULT_TABLE_WIDTH            (80 -1)

// text_table(): regular expression to match VT100/ANSI colour codes.
//#define ANSI_COLOUR_CODE_REGEXP        "\e\\[[0-9]*(;[0-9]*)*m"

#endif


/// string_utils definitions.

#if !defined(USER_WORD_DELIM_CHARS)
//#define USER_WORD_DELIM_CHARS(U)       ((string)((U)->query_env_var("word_delim_chars")))
#define NO_USER_WORD_DELIM_CHARS
#endif

#if !defined(WORD_DELIM_REGEXP)
#define WORD_DELIM_REGEXP              "[\n\f\r\t -/:-@[-^_`{-~]+"
#endif

#if !defined(EXTRA_WORD_DELIM_CHARS)
#define EXTRA_WORD_DELIM_CHARS         "\n\f\r\t "
#endif

#if !defined(REGMATCH_SUBMATCH_DELIMITER)
#define REGMATCH_SUBMATCH_DELIMITER    "\n\b\a\f\e\n"
#endif

#if !defined(SMALL_WILDCARD_CACHE) && !defined(LARGE_WILDCARD_CACHE)
#define SMALL_WILDCARD_CACHE
//#define LARGE_WILDCARD_CACHE
#endif

#if !defined(EXTENDED_WILDCARDS) && !defined(NO_EXTENDED_WILDCARDS)
//#define EXTENDED_WILDCARDS
#define NO_EXTENDED_WILDCARDS
#endif

#if !defined(DEFAULT_FIND_FLAGS)
#define DEFAULT_FIND_FLAGS             FIND_WRAP
#endif

#if !defined(DEFAULT_CMPNUM_FLAGS)
#define DEFAULT_CMPNUM_FLAGS           0
#endif

#if !defined(DEFAULT_TXTTAB_FLAGS)
#define DEFAULT_TXTTAB_FLAGS           0
#endif

#if !defined(DEFAULT_TABLE_WIDTH)
#define DEFAULT_TABLE_WIDTH            (80 -1)
#endif

#if !defined(ANSI_COLOUR_CODE_REGEXP)
#define ANSI_COLOUR_CODE_REGEXP        "\e\\[[0-9]*(;[0-9]*)*m"
#endif


// check a value for an array with elements having a specific property.
#if !defined(POINTERP_MATCH)
#define POINTERP_MATCH(A, M)           (pointerp((A)) && (sizeof((A)) == sizeof(filter((A), (M)))))
//#define POINTERP_MATCH(A, M)           (funcall((: pointerp($1) && (sizeof($1) == sizeof(filter($1, $2))) :), (A), (M)))
#endif

// check a value for an array of a specific type.
#if !defined(TYPED_POINTERP)
#define TYPED_POINTERP(A, T)           (POINTERP_MATCH((A), symbol_function(trim("T") +"p")))
#endif

// format an function argument error.
#if !defined(FUNC_ARG_ERROR)
#define FUNC_ARG_ERROR(F, E)           (object_name() +"::" +(F) +"(): " +(E) +".\n")
#endif

// format an function argument type error.
#if !defined(FUNC_ARG_TYPE_ERROR)
#define FUNC_ARG_TYPE_ERROR(F, N)      (FUNC_ARG_ERROR((F), "Bad type to argument " +(N)))
#endif

// find_term(): search flags.
#define FIND_WRAP                      0b00000001  // searches wrap top/bottom (find_term() only).
#define FIND_BACKWARD                  0b00000010  // searches are performed backwards.
#define FIND_MATCH_CASE                0b00000100  // searches match case.
#define FIND_MATCH_REGEXP              0b00001000  // searches match regular expressions.
#define FIND_MATCH_WILDCARD            0b00010000  // searches match wildcards ('*' and '?').
#define FIND_MATCH_START               0b00100000  // searches match to start of line.
#define FIND_MATCH_END                 0b01000000  // searches match to end of line.

// find_term(), explode_term(): flags pertinent to cached find closures.
//#define CACHE_FIND_FLAGS               ~FIND_WRAP
#define CACHE_FIND_FLAGS               (FIND_BACKWARD | FIND_MATCH_CASE | FIND_MATCH_REGEXP | FIND_MATCH_WILDCARD | FIND_MATCH_START | FIND_MATCH_END)

// compare_numeric(): numeric string comparison flags.
#define CMPNUM_REVERSE                 0b00000001  // compare reversed (sorts backwards).
#define CMPNUM_IGN_CASE                0b00000010  // ignore case.
#define CMPNUM_IGN_PREFIX              0b00000100  // ignore non-numeric prefix.
#define CMPNUM_IGN_WHITESPACE          0b00001000  // ignore whitespace.

// text_table(): table formatting flags.
#define TXTTAB_ROW_MODE                0b00000001  // fields are formatted in rows, rather than columns.
#define TXTTAB_STRIP_ANSI              0b00000010  // fields are stripped of ANSI codes.
#define TXTTAB_CENTRE_ALIGN            0b00000100  // fields are centre aligned within their cell.
#define TXTTAB_RIGHT_ALIGN             0b00001000  // fields are right aligned within their cell.
#define TXTTAB_NO_TRIM                 0b00010000  // final output is not right-trimmed of white-space.


#endif
////


//#pragma no_shadow


/// string_utils variables.

// explode_words(), capitlize_words(): regular expression to match word delimiters.
nosave    string  _delim_regex       = WORD_DELIM_REGEXP;

// get_wildcard_regex(): wildcard to regular expression cache.
#if defined(SMALL_WILDCARD_CACHE) && !defined(LARGE_WILDCARD_CACHE)
nosave    string* _wldcd_cache       = ({ 0, 0, });
#else
nosave    mapping _wldcd_cache       = ([ ]);
#endif

// find_term(): find function cache and default flags.
nosave    mapping _find_cache        = ([ ]);
nosave    int     _find_flags        = DEFAULT_FIND_FLAGS;

// compare_numeric(): default flags.
nosave    int     _cmpnum_flags      = DEFAULT_CMPNUM_FLAGS;

// text_table(): default flags.
nosave    int     _txttab_flags      = DEFAULT_TXTTAB_FLAGS;


/// string_utils utility method prototypes.

public    string  quote_string         (string str);

public    string* explode_words        (string str, varargs string *delim_chars);
public    string  capitalize_words     (string str, varargs string *delim_chars);
public    int     is_word              (string str, varargs string* delim_chars);
public    string  swap_case            (string str);

public    mixed   regmatch             (string str, string regex, varargs int* matches);
public    int     regstrstr            (string search, string regex, varargs int* args);
public    int     regstrrstr           (string search, string regex, varargs int* args);

protected string  conv_wildcard_regex  (string pattern);
public    string  get_wildcard_regex   (string pattern);
public    int     matches_wildcard     (string word, string pattern);
public    int     wild_strstr          (string search, string pattern, varargs int* args);
public    int     wild_strrstr         (string search, string pattern, varargs int* args);

public    int*    find_term            (string* text, string term, varargs int* args);
public    int     find_term_index      (string* text, string term, varargs int* args);
public    string* explode_term         (string str, string term, varargs int* args);

public    int     compare_numeric      (mixed value1, mixed value2, varargs int* args);

public    string  strip_ansi_colour    (string ansi_text);

public    string* text_table           (string* fields, varargs int* args);


/// string_utils utility methods.

// note: implementation of quote_string() is tied to screen.c;
// it should be replaced by a more generic version.
// additionally, it needs an unquote_string() too.
// maybe the better solution is a conv_utils package.

// public string quote_string(string str);
public string quote_string(string str) {
  !stringp(str) && raise_error(FUNC_ARG_TYPE_ERROR("quote_string", 1));

  string output = "";
  int    length = strlen(str);

  for(int index = 0; index < length; index++)
    switch(str[index]) {
      case  0.. 31:  output += sprintf("^%c", str[index] +'A' -1);  break;
      case      32:  output += "SPACE";                             break;
      case 33..126:  output += str[index..index];                   break;
      case     127:  output += "^?";                                break;
      default     :  output += sprintf("\\%03d", str[index]);       break;
    }

  return output;
}


// public string* explode_words(string str);
// public string* explode_words(string str, string delim_chars);
public string* explode_words(string str, varargs string* delim_chars) {
  !stringp(str) && raise_error(FUNC_ARG_TYPE_ERROR("explode_words", 1));
  sizeof(delim_chars) && !stringp(delim_chars[0]) && raise_error(FUNC_ARG_TYPE_ERROR("explode_words", 2));

  string delim_regex = sizeof(delim_chars) && delim_chars[0];
#if defined(USER_WORD_DELIM_CHARS) && !defined(NO_USER_WORD_DELIM_CHARS)
  if (!delim_regex) {
    delim_regex = this_player() && USER_WORD_DELIM_CHARS(this_player());
    delim_regex = stringp(delim_regex) && trim(delim_regex);
  }
#endif
  delim_regex =
    delim_regex &&
    sprintf("[%s%@s]+",
      EXTRA_WORD_DELIM_CHARS,
      map(regexplode(delim_regex, "(-|\\^|\\]|\\\\)"), ([ "-": "\\-", "^": "\\^", "]": "\\]", "\\": "\\\\", ])));

  return regexplode(str, delim_regex || _delim_regex);
}


// public string capitalize_words(string str);
// public string capitalize_words(string str, string delim_chars);
public string capitalize_words(string str, varargs string* delim_chars) {
  !stringp(str) && raise_error(FUNC_ARG_TYPE_ERROR("capitalize_words", 1));
  sizeof(delim_chars) && !stringp(delim_chars[0]) && raise_error(FUNC_ARG_TYPE_ERROR("capitalize_words", 2));

  return implode(map(apply(#'explode_words, str, delim_chars), #'capitalize), "");
}


// public int is_word(string str);
// public int is_word(string str, string delim_chars);
public int is_word(string str, varargs string* delim_chars) {
  !stringp(str) && raise_error(FUNC_ARG_TYPE_ERROR("capitalize_words", 1));
  sizeof(delim_chars) && !stringp(delim_chars[0]) && raise_error(FUNC_ARG_TYPE_ERROR("capitalize_words", 2));

  return strlen(str) && (apply(#'explode_words, str, delim_chars) == 1);
}


// public string swap_case(string str);
public string swap_case(string str) {
  !stringp(str) && raise_error(FUNC_ARG_TYPE_ERROR("swap_case", 1));

  string output = copy(str);
  int    length = strlen(output);

  for(int index = 0; index < length; index++)
    switch(output[index]) {
      case 'a'..'z':
        output[index] = str[index] +'A' -'a';
      break;
      case 'A'..'Z':
        output[index] = str[index] -'A' +'a';
      break;
    }

  return output;
}


// public int     regmatch(string str, string regex);
// public string* regmatch(string str, string regex, varargs int* matches);
public mixed regmatch(string str, string regex, varargs int* matches) {
  !stringp(str)                 && raise_error(FUNC_ARG_TYPE_ERROR("regmatch", 1));
  !stringp(regex)               && raise_error(FUNC_ARG_TYPE_ERROR("regmatch", 2));
  !TYPED_POINTERP(matches, int) && raise_error(FUNC_ARG_TYPE_ERROR("regmatch", "3+"));

  string check = strlen(str) ? "" : " ";
  string match = sizeof(matches) && ("\\" +implode(map(matches, #'to_string), REGMATCH_SUBMATCH_DELIMITER +"\\"));
  return
    (regreplace(str, regex, check, 0) == check) &&
    (match ? explode(regreplace(str, regex, match, 0), REGMATCH_SUBMATCH_DELIMITER) : 1);
}


// public int regstrstr(string search, string regex);
// public int regstrstr(string search, string regex, int start_char);
public int regstrstr(string search, string regex, varargs int* args) {
  !stringp(search) && raise_error(FUNC_ARG_TYPE_ERROR("regstrstr", 1));
  !stringp(regex)  && raise_error(FUNC_ARG_TYPE_ERROR("regstrstr", 2));
  sizeof(args)     && !intp(args[0]) && raise_error(FUNC_ARG_TYPE_ERROR("regstrstr", 3));

  int pos = sizeof(args) && args[0];
  if (pos < 0)
    pos += strlen(search);

  string* bits = regexplode(search[pos..], regex);
  return (sizeof(bits) < 3) ? -1 : (pos +(strlen(bits[0]) || strlen(bits[1])));
/*
  int     result = -1;
  if (sizeof(bits) > 2) {
    //result = pos +(strlen(bits[0]) || strlen(bits[1]));
    result = pos +strlen(bits[0]);
  }
  return result;
*/
}


// public int regstrrstr(string search, string regex);
// public int regstrrstr(string search, string regex, int start_char);
public int regstrrstr(string search, string regex, varargs int* args) {
  !stringp(search) && raise_error(FUNC_ARG_TYPE_ERROR("regstrrstr", 1));
  !stringp(regex)  && raise_error(FUNC_ARG_TYPE_ERROR("regstrrstr", 2));
  sizeof(args)     && !intp(args[0]) && raise_error(FUNC_ARG_TYPE_ERROR("regstrrstr", 3));

  int pos = sizeof(args) ? args[0] : strlen(search);
  if (pos < 0)
    pos += strlen(search);

  string* bits = regexplode(search[..pos], regex);
  return (sizeof(bits) < 3) ? -1 : (pos -(strlen(bits[<1]) || strlen(bits[<2])));
}


// protected string conv_wildcard_regex(string pattern);
// raw wildcard conversion function.
// use get_wildcard_regex() for caching and extended wildcards.
protected string conv_wildcard_regex(string pattern) {
  return
    implode(map(regexplode(pattern, "\\?|\\*|\\.|\\+|\\[|\\]|\\(|\\)|\\^|\\$|\\||\\\\"),
      ([
        "?" : ".",
        "*" : ".*",
        "." : "\\.",
        "+" : "\\+",
        "[" : "\\[",
        "]" : "\\]",
        "(" : "\\(",
        ")" : "\\)",
        "^" : "\\^",
        "$" : "\\$",
        "|" : "\\|",
        "\\": "\\\\",
      ])), "");
}


// public string get_wildcard_regex(string pattern);
// public string get_wildcard_regex(0);
#if defined(SMALL_WILDCARD_CACHE) && !defined(LARGE_WILDCARD_CACHE)
public string get_wildcard_regex(string pattern) {
  !stringp(pattern ||= _wldcd_cache[0]) && raise_error(FUNC_ARG_TYPE_ERROR("get_wildcard_regex", 1));

  if (pattern != _wldcd_cache[0]) {
#if defined(EXTENDED_WILDCARDS) && !defined(NO_EXTENDED_WILDCARDS)
    string  wildcard_regex = "";

    foreach(string bit : regexplode(pattern, "{[^}]*}|\\[[^]]*\\]"))
      wildcard_regex +=
        sscanf(bit, "{%~s}") ?
          sprintf("(%s)", implode(map(explode(bit[1..<2], ","), #'conv_wildcard_regex), "|")) :
        (sscanf(bit, "[%~s!%~s]") == 2) ?
          regreplace(bit, "!", "^", 0) :
        sscanf(bit, "[%~s]") ?
          bit :
          conv_wildcard_regex(bit);

    _wldcd_cache =
      ({
        pattern,
        wildcard_regex,
      });
#else
    _wldcd_cache =
      ({
        pattern,
        conv_wildcard_regex(pattern),
      });
#endif
  }

  return _wldcd_cache[1];
}
#else
public string get_wildcard_regex(string pattern) {
  !stringp(pattern ||= _wldcd_cache[0]) && raise_error(FUNC_ARG_TYPE_ERROR("get_wildcard_regex", 1));

  _wldcd_cache[0] = pattern;
  if (!member(_wldcd_cache, pattern)) {
#if defined(EXTENDED_WILDCARDS) && !defined(NO_EXTENDED_WILDCARDS)
    string  wildcard_regex = "";

    foreach(string bit : regexplode(pattern, "{[^}]*}|\\[[^]]*\\]"))
      wildcard_regex +=
        sscanf(bit, "{%~s}") ?
          sprintf("(%s)", implode(map(explode(bit[1..<2], ","), #'conv_wildcard_regex), "|")) :
        (sscanf(bit, "[%~s!%~s]") == 2) ?
          regreplace(bit, "!", "^", 0) :
        sscanf(bit, "[%~s]") ?
          bit :
          conv_wildcard_regex(bit);

    _wldcd_cache[pattern] = wildcard_regex;
#else
    _wldcd_cache[pattern] = conv_wildcard_regex(pattern);
#endif
  }

  return _wldcd_cache[pattern];
}
#endif


// public int matches_wildcard(string word, string pattern);
public int matches_wildcard(string word, string pattern) {
  !stringp(word)    && raise_error(FUNC_ARG_TYPE_ERROR("matches_wildcard", 1));
  !stringp(pattern) && raise_error(FUNC_ARG_TYPE_ERROR("matches_wildcard", 2));

  return (sizeof(regexplode(word, "^" +get_wildcard_regex(pattern) +"$")) == 3);
}


// public int wild_strstr(string search, string pattern);
// public int wild_strstr(string search, string pattern, int start_char);
public int wild_strstr(string search, string pattern, varargs int* args) {
  !stringp(search)  && raise_error(FUNC_ARG_TYPE_ERROR("wild_strstr", 1));
  !stringp(pattern) && raise_error(FUNC_ARG_TYPE_ERROR("wild_strstr", 2));
  sizeof(args)      && !intp(args[0]) && raise_error(FUNC_ARG_TYPE_ERROR("wild_strstr", 3));

  return apply(#'regstrstr, search, get_wildcard_regex(pattern), args);
}


// public int wild_strrstr(string search, string pattern);
// public int wild_strrstr(string search, string pattern, int start_char);
public int wild_strrstr(string search, string pattern, varargs int* args) {
  !stringp(search)  && raise_error(FUNC_ARG_TYPE_ERROR("wild_strrstr", 1));
  !stringp(pattern) && raise_error(FUNC_ARG_TYPE_ERROR("wild_strrstr", 2));
  sizeof(args)      && !intp(args[0]) && raise_error(FUNC_ARG_TYPE_ERROR("wild_strrstr", 3));

  return apply(#'regstrrstr, search, get_wildcard_regex(pattern), args);
}


// public int* find_term(string* text, string term);
// public int* find_term(string* text, string term, int flags);
// public int* find_term(string* text, string term, int flags, int start_line);
// public int* find_term(string* text, string term, int flags, int start_line, int start_char);
public int* find_term(string* text, string term, varargs int* args) {
  !TYPED_POINTERP(text, string) && raise_error(FUNC_ARG_TYPE_ERROR("find_term", 1));
  !stringp(term)                && raise_error(FUNC_ARG_TYPE_ERROR("find_term", 2));
  switch(sizeof(args)) {
    case 3 :  !intp(args[2]) && raise_error(FUNC_ARG_TYPE_ERROR("find_term", 5));
    case 2 :  !intp(args[1]) && raise_error(FUNC_ARG_TYPE_ERROR("find_term", 4));
    case 1 :  !intp(args[0]) && raise_error(FUNC_ARG_TYPE_ERROR("find_term", 3));
    default:  raise_error(object_name() +"::find_term(): Too many arguments.\n");
  }

  int num_lines = sizeof(text);
  if (!num_lines)
    return 0;

  int flags      = sizeof(args) ? args[0] : _find_flags;
  int start_line = 0;
  int start_char = 0;
  switch(sizeof(args)) {
    case 0:
    case 1:
      start_line = (flags & FIND_BACKWARD) && (num_lines -1);
      start_char = (flags & FIND_BACKWARD) && num_lines && strlen(text[start_line]);
    break;
    case 2:
      start_line = min(max(0, (args[1] >= 0) ? args[1] : (num_lines -args[1])), num_lines -1);
      start_char = (flags & FIND_BACKWARD) && strlen(text[start_line]);
    break;
    case 3:
      start_line = min(max(0, (args[1] >= 0) ? args[1] : (num_lines -args[1])), num_lines -1);
      start_char = min(max(0, (args[2] >= 0) ? args[2] : (strlen(text[start_line]) -args[2])), strlen(text[start_line]));
    break;
  }

  int cache_flags = flags & CACHE_FIND_FLAGS;
  if (!member(_find_cache, cache_flags)) {
    mixed strstr_code =
      ({
        (flags & FIND_MATCH_REGEXP)   ? ((flags & FIND_BACKWARD) ? #'regstrrstr   : #'regstrstr)   :
        (flags & FIND_MATCH_WILDCARD) ? ((flags & FIND_BACKWARD) ? #'wild_strrstr : #'wild_strstr) :
                                        ((flags & FIND_BACKWARD) ? #'strrstr      : #'strstr),
        (flags & FIND_MATCH_CASE)     ? 'search : ({ #'lower_case, 'search, }),
        'term,
      });

    if (flags & FIND_MATCH_START)
      strstr_code =
        ({ #'?,
          ({ #'=, 'pos, strstr_code, }),
          -1,
          0,
        });

    if (flags & FIND_MATCH_END)
      strstr_code =
        ({ #'?,
          ({ #'||,
            ({ #'==, ({ #'=, 'pos, strstr_code, }), -1, }),
            (flags & FIND_MATCH_REGEXP) ?
              ({ #'strlen, ({ #'regreplace, ({ #'[..<], 'search, 'pos, 1, }), 'term, "", 0, }), }) :
            (flags & FIND_MATCH_WILDCARD) ?
              ({ #'strlen, ({ #'regreplace, ({ #'[..<], 'search, 'pos, 1, }), ({ #'get_wildcard_regex, 'term, }), "", 0, }), }) :
              ({ #'!=, ({ #'+, 'pos, ({ #'strlen, 'term, }), }), ({ #'strlen, 'search, }), }),
          }),
          -1,
          'pos,
        });

    //m_add(_find_cache[cache_flags], lambda(({ 'search, 'term, }), strstr_code));
    _find_cache[cache_flags] = lambda(({ 'search, 'term, }), strstr_code);
  }

  closure finder = _find_cache[cache_flags];
  string  lterm  = (flags & FIND_MATCH_CASE) ? term : lower_case(term);
  int*    find   = 0;

  if (flags & FIND_BACKWARD) {
    for(int index_line = start_line; (index_line >= 0) && !find; index_line--) {
      int find_char = funcall(finder, text[index_line], lterm, (index_line == start_line) ? start_char : strlen(text[index_line]));
      if (find_char != -1)
        find = ({ index_line, find_char, });
    }

    if (!find && (flags & FIND_WRAP))
      for(int index_line = num_lines -1; (index_line >= start_line) && !find; index_line--) {
        int find_char = funcall(finder, text[index_line], lterm, (index_line == start_line) ? start_char : strlen(text[index_line]));
        if (find_char != -1)
          find = ({ index_line, find_char, });
      }
  }
  else {
    for(int index_line = start_line; (index_line < num_lines) && !find; index_line++) {
      int find_char = funcall(finder, text[index_line], lterm, (index_line == start_line) ? start_char : 0);
      if (find_char != -1)
        find = ({ index_line, find_char, });
    }

    if (!find && (flags & FIND_WRAP))
      for(int index_line = 0; (index_line < start_line) && !find; index_line++) {
        int find_char = funcall(finder, text[index_line], lterm, (index_line == start_line) ? start_char : 0);
        if (find_char != -1)
          find = ({ index_line, find_char, });
      }
  }

  return find;
}


// public int find_term_index(string* text, string term);
// public int find_term_index(string* text, string term, int flags);
// public int find_term_index(string* text, string term, int flags, int start_line);
// public int find_term_index(string* text, string term, int flags, int start_line, int start_char);
public int find_term_index(string* text, string term, varargs int* args) {
  int* find = apply(#'find_term, text, term, args);
  return find ? find[0] : -1;
}

// public string* explode_term(string str, string term);
// public string* explode_term(string str, string term, int flags);
public string* explode_term(string str, string term, varargs int* args) {
  !stringp(str)  && raise_error(FUNC_ARG_TYPE_ERROR("explode_term", 1));
  !stringp(term) && raise_error(FUNC_ARG_TYPE_ERROR("explode_term", 2));
  sizeof(args)   && !intp(args[0]) && raise_error(FUNC_ARG_TYPE_ERROR("explode_term", 3));

  int     flags  = sizeof(args) ? args[0] : _find_flags;
  string  lstr   = (flags & FIND_MATCH_CASE) ? str  : lower_case(str);
  string  lterm  = (flags & FIND_MATCH_CASE) ? term : lower_case(term);
  string* result = 0;
  if (flags & FIND_MATCH_REGEXP)
    result = regexplode(lstr, lterm);
  else if (flags & FIND_MATCH_WILDCARD)
    result = regexplode(lstr, get_wildcard_regex(lterm));
  else {
    string* bits = explode(lstr, lterm);
    result = bits[..0];
    foreach(string bit : bits[1..])
      result += ({ bit, lterm, });
    if (!sizeof(result))
      result = allocate(3, "");
  }

  if (flags & FIND_MATCH_CASE) {
    string* bits = result;
    int     pos  = 0;

    result = ({ });
    foreach(string bit : bits) {
      int length = strlen(bit);
      result += ({ str[pos..pos +length -1], });
      pos += length;
    }
  }

  if (sizeof(result) >= 3) {
    if (flags & FIND_MATCH_START)
      result = strlen(result[0])  ? ({ implode(result, ""), }) : (result[..1] +({ implode(result[2..], ""), }));
    if (flags & FIND_MATCH_END)
      result = strlen(result[<1]) ? ({ implode(result, ""), }) : (({ implode(result[..<3], ""), }) +result[<2..]);
  }

  return result;
}


// public int compare_numeric(string value1, string value2);
// public int compare_numeric(string value1, string value2, int flags);
// public int compare_numeric(mixed value1, mixed value2);
// public int compare_numeric(mixed value1, mixed value2, int flags);
public int compare_numeric(mixed value1, mixed value2, varargs int* args) {
  sizeof(args) && !intp(args[0]) && raise_error(FUNC_ARG_TYPE_ERROR("compare_numeric", 3));

  int flags = (pointerp(args) && sizeof(args)) ? args[0] : _cmpnum_flags;
  if (stringp(value1) && stringp(value2)) {
    if (flags & CMPNUM_IGN_CASE) {
      value1 = lower_case(value1);
      value2 = lower_case(value2);
    }
    if (flags & CMPNUM_IGN_WHITESPACE) {
      value1 = regreplace(value1, "[ \t\r\n]+", " ", 1);
      value2 = regreplace(value2, "[ \t\r\n]+", " ", 1);
    }
    string prefix1 = regreplace(value1, "^([^0-9]+)(.*)$", "\\1", 0);
    string prefix2 = regreplace(value2, "^([^0-9]+)(.*)$", "\\1", 0);
    int    number1 = to_int(value1[strlen(prefix1)..]);
    int    number2 = to_int(value2[strlen(prefix2)..]);
    if (((flags & CMPNUM_IGN_PREFIX) || (prefix1 == prefix2)) && (number1 != number2))
      return (flags & CMPNUM_REVERSE) ? (number1 < number2) : (number1 > number2);
  }

  return (flags & CMPNUM_REVERSE) ? (value1 < value2) : (value1 > value2);
}


// public string strip_ansi_colour(string ansi_text);
public string strip_ansi_colour(string ansi_text) {
  !stringp(ansi_text) && raise_error(FUNC_ARG_TYPE_ERROR("strip_ansi_colour", 1));

  return regreplace(ansi_text, ANSI_COLOUR_CODE_REGEXP, "", 1);
}


// public string* text_table(string* fields);
// public string* text_table(string* fields, int table_width);
// public string* text_table(string* fields, int table_width, int table_flags);
public string* text_table(string* fields, varargs int* args) {
  !TYPED_POINTERP(fields, string)      && raise_error(FUNC_ARG_TYPE_ERROR("text_table", 1));
  sizeof(args)       && !intp(args[0]) && raise_error(FUNC_ARG_TYPE_ERROR("text_table", 2));
  (sizeof(args) > 1) && !intp(args[1]) && raise_error(FUNC_ARG_TYPE_ERROR("text_table", 3));

  int num_fields = sizeof(fields);
  if (!num_fields)
    return ({ });

  int     table_width = (sizeof(args) && args[0]) || DEFAULT_TABLE_WIDTH;
  int     table_flags = (sizeof(args) > 1) ? args[1] : _txttab_flags;
  string* stripped    = map(fields, #'strip_ansi_colour);
  int*    widths      = map(stripped, #'strlen);
  int     num_cols    = max(1, to_int(table_width /(max(widths) +1.0)));
  int     cell_width  = table_width /num_cols;
  int     num_rows    = (num_fields /num_cols) +((num_fields %num_cols) && 1);
  string* cell_fields = (table_flags & TXTTAB_STRIP_ANSI) ? stripped : fields;
  string* output      = allocate(num_rows, "");
  closure cell_align  = // (index, fields, widths, cell_width)
    (table_flags & TXTTAB_CENTRE_ALIGN) ?
      (: (" " *max(0, ($4 -$3[$1]) /2)) +$2[$1] +(" " *max(0, $4 -$3[$1] -max(0, ($4 -$3[$1]) /2))) :) :
    (table_flags & TXTTAB_RIGHT_ALIGN)  ?
      (: (" " *max(0, $4 -$3[$1])) +$2[$1] :) :
      (: $2[$1] +(" " *max(0, $4 -$3[$1])) :);

  for(int index = 0; index < num_fields; index++) {
    int row = (table_flags & TXTTAB_ROW_MODE) ? (index /num_cols) : (index %num_rows);
    output[row] += funcall(cell_align, index, cell_fields, widths, cell_width);
  }

  return (table_flags & TXTTAB_NO_TRIM) ? output : map(output, #'trim, TRIM_RIGHT);
}


////


