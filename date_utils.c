//// date_utils.c
// Date parsing and formatting utilities.
//
// Bubbs, Aug/2011.  Last revision Sep/2011.


/*
** public mapping parse_time();
** public mapping parse_time(int time_value);
** public mapping parse_time(string time_value);
** public mapping parse_time(string time_value, string format);
**   Parses date information from time_value into a mapping, with format (default ctime() format);
**   format is simple regex with tokens YEAR MONTH DATE WEEKDAY HOUR AMPM MINUTE SECOND ZONE.
**   Returns mapping with matched date values, or 0 for failed match.
**   For example:
*      printf("%#Q, %#Q\n", parse_time(), parse_time("12:34:56 07/Aug/2009", "HOUR:MINUTE:SECOND DATE/MONTH/YEAR"));
**
** public int mktime(mapping values);
** public int mktime(int *values);
**   Compose a parse_time() or gmtime() style time into a time() style time.
**   For example:
**     printf("%#Q, %#Q\n", mktime(parse_time()), mktime(gmtime()));
**
** public string format_date();
** public string format_date(int input_time);
** public string format_date(int input_time, string output_format);
**   Format a time() style time into a date string, recognising tokens:
**     ctime date dtime full hm12 hm24  iso8601 time tod user
**     YYYY YY year MMM MM month DD ddd day dow HH hh ampm mm ss.
**   For example:
**     printf("%#Q, %#Q\n", format_time(time()), format_date(time(), "day tod"));
**
*/


/// date_utils history.

// Bubbs, 06/June/2004.
// Created functions parse_time() and mktime() as a side product of 'httpclient', which
// needs the ability to parse cookie expiry dates using a number of variable formats.

// Bubbs, 28/Feb/2007.
// Added PATTERN_LIST regexp.
// Tweaked preparation phase to avoid subst() usage.

// 02/June/2007.
// Fixed mktime().

// 02/Feb/2008.
// Added mktime(int *) to support mktime(gmtime()) usage.

// 13/Feb/2009.
// Fixed typo in CENTURY_START and corrected its' value.  Made use of CENTURY_START in mktime().
// Recoded pattern handling and month length calculation to remove a number of ugly definitions.

// 04/Apr/2010.
// Added parse_time(time()) usage.

// 18/Aug/2011.
// Fixed parse_time(0) to be parse_time(time()).  Added prototypes and restructured definitions.
// Added format_date().  Repackaged as date_utils.c.

// 03/Sep/2011.
// Tweaked parse_time() to populate WEEKDAY if possible.


//#include "date_utils.h"
//// date_utils.h
//
// Definitions for date utilities.


#if !defined(DATE_UTILS_H)
#define DATE_UTILS_H


/// date_utils mudlib portability configuration.

#if defined(TIMEWARP)
// Timewarp style mudlib.

#include <time.h>

#if __FILE__ == "secure/simul/date_utils.c"
// If installed as simul-efun module; use run-time binding on foreign simul-efuns.
#define QUERY_ZONE_OFFSET(Z)           (funcall("query_zone_offset", (Z)))
#else
#define QUERY_ZONE_OFFSET(Z)           (query_zone_offset((Z)))
#endif

#define ZONE_LIST                      "|ast|yst|pst|mst|cst|est|ast|nst|wet|pwt|bst|gmt|utc|met|cet|cest|sast|eet|awt|act|aet|nzst|nzt"

//
#elif defined(DUNE)
// Dune style mudlib.

#if __FILE__ == "secure/simul/date_utils.c"
// If installed as simul-efun module; use run-time binding on foreign simul-efuns.
#define QUERY_ZONE_OFFSET(Z)           (funcall("query_zone_offset", (Z)))
#else
#define QUERY_ZONE_OFFSET(Z)           (query_zone_offset((Z)))
#endif

#define ZONE_LIST                      "|ast|yst|pst|mst|cst|est|ast|nst|wet|pwt|bst|gmt|utc|met|cet|cest|sast|eet|awt|act|aet|nzst|nzt"

//
#else
// Unknown mudlib.

// parse_time():  Defines how to expand 2-digit years into 4-digit years.
// If the (2-digit) year is less than this, the century is '20', '19' otherwise.
// (70 is chosen since it's at the start of the epoch).
//#define CENTURY_START                  70

// parse_time(): Default date format, matches ctime().
//#define DEFAULT_PARSE_FORMAT           PARSE_CTIME_FORMAT

// parse_time(): If active (not default), used to apply mud zone offset to zone value.
////#define QUERY_ZONE_OFFSET(Z)           (query_zone_offset((Z)))
////#define QUERY_ZONE_OFFSET(Z)           (funcall("query_zone_offset", (Z)))
//#define NO_QUERY_ZONE_OFFSET

// parse_time(): List of recognised timezone names.
////#define ZONE_LIST                      "|ast|yst|pst|mst|cst|est|ast|nst|wet|pwt|bst|gmt|utc|met|cet|cest|sast|eet|awt|act|aet|nzst|nzt"
//#define ZONE_LIST                      ""

// format_date(): Default output format.
//#define DEFAULT_DATE_FORMAT            "ctime"
////#define DEFAULT_DATE_FORMAT            "full"
////#define DEFAULT_DATE_FORMAT            "iso8601"
////#define DEFAULT_DATE_FORMAT            "user"

//
#endif


/// date_utils mudlib portability definitions.

#if !defined(LPC_TIME_H_)
#include <sys/time.h>
#endif

#if !defined(CENTURY_START)
#define CENTURY_START                  70
#endif

#if !defined(DEFAULT_PARSE_FORMAT)
#define DEFAULT_PARSE_FORMAT           PARSE_CTIME_FORMAT
#endif

#if !defined(QUERY_ZONE_OFFSET) && !defined(NO_QUERY_ZONE_OFFSET)
//#define QUERY_ZONE_OFFSET(Z)           (query_zone_offset((Z)))
#define NO_QUERY_ZONE_OFFSET
#endif

#if !defined(ZONE_LIST)
//#define ZONE_LIST                      "|ast|yst|pst|mst|cst|est|ast|nst|wet|pwt|bst|gmt|utc|met|cet|cest|sast|eet|awt|act|aet|nzst|nzt"
#define ZONE_LIST                      ""
#endif

#if !defined(DEFAULT_DATE_FORMAT)
#define DEFAULT_DATE_FORMAT            "ctime"
//#define DEFAULT_DATE_FORMAT            "full"
//#define DEFAULT_DATE_FORMAT            "iso8601"
//#define DEFAULT_DATE_FORMAT            "user"
#endif


/// date_utils process definitions.

// parse_time(): Date format matching ctime().
#define PARSE_CTIME_FORMAT             "WEEKDAY MONTH DATE HOUR:MINUTE:SECOND YEAR"

// parse_time(): List of month names to recognise, in order.
#define MONTH_LIST                     "jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec"

// parse_time(): List of day names to recognise, in order.
#define DAY_LIST                       "sun|mon|tue|wed|thu|fri|sat"

// parse_time(): Date token regular expressions.
#define YEAR_REGEXP                    "([0-9][0-9][0-9][0-9]|[0-9][0-9])"
#define MONTH_REGEXP                   "(0[1-9]|1[0-2]|[1-9]|" MONTH_LIST ")"
#define DATE_REGEXP                    "(0[1-9]|[12][0-9]|3[01]|[1-9])"
#define WEEKDAY_REGEXP                 "(" DAY_LIST ")"
#define HOUR_REGEXP                    "([01][0-9]|2[0-3]|[0-9])"
#define AMPM_REGEXP                    "([ap]m)"
#define MINUTE_REGEXP                  "([0-5][0-9]|[0-9])"
#define SECOND_REGEXP                  "([0-5][0-9]|[0-9])"
#define ZONE_REGEXP                    "([-+][0-9]+\\.[0-9]*|[-+][0-9]+" ZONE_LIST ")"

// format an function argument error.
#if !defined(FUNC_ARG_ERROR)
#define FUNC_ARG_ERROR(F, E)           (object_name() +"::" +(F) +"(): " +(E) +".\n")
#endif

// format an function argument type error.
#if !defined(FUNC_ARG_TYPE_ERROR)
#define FUNC_ARG_TYPE_ERROR(F, N)      (FUNC_ARG_ERROR((F), "Bad type to argument " +(N)))
#endif


#endif
////


/// date_utils utility method prototypes.

public varargs mapping parse_time      (mixed date_text, string date_fmt);
public         int     mktime          (mixed date_values);
public varargs string  format_date     (int input_time, string output_format);


/// date_utils utility methods.

public varargs mapping parse_time(mixed date_text, string date_fmt) {
  !(intp(date_text) || stringp(date_text)) && raise_error(FUNC_ARG_TYPE_ERROR("parse_time", 1));
  !(!date_fmt       || stringp(date_fmt))  && raise_error(FUNC_ARG_TYPE_ERROR("parse_time", 2));

  // preparation.
  string  dtext    = lower_case(intp(date_text) ? ctime(date_text || time()) : date_text);
  mapping patterns =
    ([
      "YEAR"   : YEAR_REGEXP,
      "MONTH"  : MONTH_REGEXP,
      "DATE"   : DATE_REGEXP,
      "WEEKDAY": WEEKDAY_REGEXP,
      "HOUR"   : HOUR_REGEXP,
      "AMPM"   : AMPM_REGEXP,
      "MINUTE" : MINUTE_REGEXP,
      "SECOND" : SECOND_REGEXP,
      "ZONE"   : ZONE_REGEXP,
    ]);
  string *fmt_bits = regexplode(date_fmt || PARSE_CTIME_FORMAT, implode(m_indices(patterns), "|"));
  string  fmt      = "^" +implode(map(fmt_bits, (: $2[$1] || $1 :), patterns), "") +"$";
  // check format match.
  if (!strlen(dtext) || strlen(regreplace(dtext, fmt, "", 0)))
    return 0;

  // parse for individual tokens.
  mapping date_values = ([ ]);
  int     size        = sizeof(fmt_bits);
  for(int index = 1; index < size; index += 2)
    m_add(date_values, fmt_bits[index], regreplace(dtext, fmt, "\\" +((index +1) /2), 0));

  // normalise values, and sanity checks.
  if (member(date_values, "YEAR")) {
    int num = to_int(date_values["YEAR"]);
    if (strlen(date_values["YEAR"]) == 2)
      num += (num < CENTURY_START) ? 2000 : 1900;
    date_values["YEAR"] = num;
  }
  if (member(date_values, "MONTH")) {
    int num = to_int(date_values["MONTH"]);
    if (!num)
      num = member(explode(MONTH_LIST, "|"), date_values["MONTH"]) +1;
    if ((num < 1) || (num > 12))
      return 0;
    date_values["MONTH"] = num;
  }
  if (member(date_values, "DATE")) {
    int num = to_int(date_values["DATE"]);
    int ml  = 31;
//    if ((num < 1) || (num > max(MONTH_LENGTHS)))
    if ((num < 1) || (num > ml))
      return 0;
    if (member(date_values, "MONTH")) {
      int ly = 1;
      if (member(date_values, "YEAR"))
        ly = (!(date_values["YEAR"] %4) && (date_values["YEAR"] %100)) || !(date_values["YEAR"] %400);
//      int ml = (MONTH_LENGTHS)[date_values["MONTH"] -1];
//      if (ly && (date_values["MONTH"] == 2))
//        ml++;
      switch(date_values["MONTH"]) {
        case  2:
          ml = 28 +(ly && 1);
        break;
        case  4:
        case  6:
        case  9:
        case 11:
          ml = 30;
        break;
      }
      if (num > ml)
        return 0;
    }
    date_values["DATE"] = num;
  }
  int dow = -1;
  if (member(date_values, "YEAR") && member(date_values, "MONTH") && member(date_values, "DATE")) {
    int y = date_values["YEAR"];
    int m = date_values["MONTH"];
    int d = date_values["DATE"];
    // now, watch carefully.
    int m2 = (m +9) %12;
    int y2 = y -(m2 /10);
    while(y2 < 0)
      y2 += 400;
    dow  = (d +2 +(((m2 *13) +2) /5) +y2 +(y2 /4) -(y2 /100) +(y2 /400)) %7;
    // and that's magic!
  }
  if (member(date_values, "WEEKDAY")) {
    int num = member(explode(DAY_LIST, "|"), date_values["WEEKDAY"]);
    if (num == -1)
      return 0;
    // check it matches the given date...
    if ((dow != -1) && (num != dow))
      return 0;
    date_values["WEEKDAY"] = num;
  }
  else
    date_values["WEEKDAY"] = dow;
  if (member(date_values, "HOUR")) {
    int num = to_int(date_values["HOUR"]);
    if (member(date_values, "AMPM")) {
      if ((num < 1) || (num > 12))
        return 0;
      if (date_values["AMPM"] == "pm")
        num += 12;
      if (num == 24)
        num = 0;
    }
    else if ((num < 0) || (num > 23))
      return 0;
    date_values["HOUR"] = num;
  }
  if (member(date_values, "MINUTE")) {
    int num = to_int(date_values["MINUTE"]);
    if ((num < 0) || (num > 59))
      return 0;
    date_values["MINUTE"] = num;
  }
  if (member(date_values, "SECOND")) {
    int num = to_int(date_values["SECOND"]);
    if ((num < 0) || (num > 59))
      return 0;
    date_values["SECOND"] = num;
  }
#if defined(QUERY_ZONE_OFFSET) && !defined(NO_QUERY_ZONE_OFFSET)
  date_values["ZONE"] = (member(date_values, "ZONE") ? QUERY_ZONE_OFFSET(date_values["ZONE"]) : 0.0) -QUERY_ZONE_OFFSET("UTC");
#else
  date_values["ZONE"] = (member(date_values, "ZONE") ? to_float(date_values["ZONE"]) : 0.0);
#endif

  return date_values;
}


public int mktime(mixed date_values) {
#if defined(LPC_TIME_H_)
  if (pointerp(date_values) && (sizeof(date_values) == TM_MAX) && (sizeof(filter(date_values, #'intp)) == TM_MAX))
    date_values =
      ([
        "YEAR"  : date_values[TM_YEAR],
        "MONTH" : date_values[TM_MON] +1,
        "DATE"  : date_values[TM_MDAY],
        "HOUR"  : date_values[TM_HOUR],
        "MINUTE": date_values[TM_MIN],
        "SECOND": date_values[TM_SEC],
        "ZONE"  : 0,
      ]);
#endif

  !mappingp(date_values) && raise_error(FUNC_ARG_TYPE_ERROR("mktime", 1));

  int total = (date_values["YEAR"] -(1900 +CENTURY_START)) *365 *24 *60 *60;

  for(int i = 1900 +CENTURY_START; i < date_values["YEAR"]; i++)
    if ((!(i %4) && (i %100)) || !(i %400))
      total += 24 *60 *60;

//  int ly = (!(date_values["YEAR"] %4) && (date_values["YEAR"] %100)) || !(date_values["YEAR"] %400);
//  for(int i = 0; i < date_values["MONTH"] -1; i++)
//    total += (MONTH_LENGTHS[i] +(ly && (i == 1) && 1)) *24 *60 *60;
  for(int i = 1; i < date_values["MONTH"]; i++)
    switch(i) {
      case  2:
        int ly = (!(date_values["YEAR"] %4) && (date_values["YEAR"] %100)) || !(date_values["YEAR"] %400);
        total += (28 +(ly && 1)) *24 *60 *60;
      break;
      case  4:
      case  6:
      case  9:
      case 11:
        total += 30 *24 *60 *60;
      break;
      default:
        total += 31 *24 *60 *60;
      break;
    }

  total += ((date_values["DATE"] -1) *24 *60 *60) +(date_values["HOUR"] *60 *60) +(date_values["MINUTE"] *60) +date_values["SECOND"];
  total -= to_int(date_values["ZONE"] *60 *60);

  return total;
}


public varargs string format_date(int input_time, string output_format) {
  !intp(input_time)                           && raise_error(FUNC_ARG_TYPE_ERROR("format_date", 1));
  !(!output_format || stringp(output_format)) && raise_error(FUNC_ARG_TYPE_ERROR("format_date", 2));

  if (!strlen(output_format))
    return format_date(input_time, DEFAULT_DATE_FORMAT);

  string* day_names   = ({ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", });
  string* month_names = ({ 0, "January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December", });
  mapping time_value  = parse_time(input_time);
  string  output      = "";
  foreach(string token : regexplode(output_format, "ctime|date|dtime|full|hm12|hm24|iso8601|time|tod|user|YYYY|YY|year|MMM|MM|month|DD|ddd|day|dow|HH|hh|ampm|mm|ss"))
    switch(token) {
      case "ctime"  :  output += ctime(input_time);                                       break;
      case "date"   :  output += format_date(input_time, "YYYY-MM-DD");                   break;
      case "dtime"  :  output += sprintf("%d", input_time %86400);                        break;
      case "full"   :  output += format_date(input_time, "HH:mm:ss day DD/MMM/YYYY");     break;
      case "hm12"   :  output += format_date(input_time, "hh:mmampm");                    break;
      case "hm24"   :  output += format_date(input_time, "HH:mm");                        break;
      case "iso8601":  output += format_date(input_time, "YYYY-MM-DD HH:mm");             break;
      case "time"   :  output += sprintf("%d", time());                                   break;
      case "tod"    :
        switch(input_time %86400) {
          case     0..  179:  output += "Midnight";   break;
          case   180..32339:  output += "Morning";    break;
          case 32340..43019:  output += "Day";        break;
          case 43020..43379:  output += "Midday";     break;
          case 43380..64799:  output += "Afternoon";  break;
          case 64800..86219:  output += "Evening";    break;
          case 86220..86400:  output += "Midnight";   break;
          default          :  output += "Some time";  break;
        }
      break;
#if defined(GET_USER_ENV_VAR)
      case "user"   :
        output += format_date(input_time, regreplace(GET_USER_ENV_VAR(this_player(), "time_format") || "full", "user", "", 1));
      break;
#endif
      case "YYYY"   :  output += sprintf("%04d", time_value["YEAR"]);                     break;
      case "YY"     :  output += sprintf("%02d", time_value["YEAR"] %100);                break;
      case "year"   :  output += sprintf("%04d", time_value["YEAR"]);                     break;
      case "MMM"    :  output += sprintf("%3s", month_names[time_value["MONTH"]][0..2]);  break;
      case "MM"     :  output += sprintf("%02d", time_value["MONTH"]);                    break;
      case "month"  :  output += sprintf("%s", month_names[time_value["MONTH"]]);         break;
      case "DD"     :  output += sprintf("%02d", time_value["DATE"]);                     break;
      case "ddd"    :  output += sprintf("%3s", day_names[time_value["WEEKDAY"]][0..2]);  break;
      case "day"    :  output += sprintf("%s", day_names[time_value["WEEKDAY"]]);         break;
      case "dow"    :  output += sprintf("%1d", time_value["WEEKDAY"]);                   break;
      case "HH"     :  output += sprintf("%02d", time_value["HOUR"]);                     break;
      case "hh"     :  output += sprintf("%02d", (time_value["HOUR"] %12) || 12);         break;
      case "ampm"   :  output += (time_value["HOUR"] < 12) ? "am" : "pm";                 break;
      case "mm"     :  output += sprintf("%02d", time_value["MINUTE"]);                   break;
      case "ss"     :  output += sprintf("%02d", time_value["SECOND"]);                   break;
      default       :  output += token;                                                   break;
    }

  return output;
}


////


