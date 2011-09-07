//// array_utils.c
// Array utility functions.
//
// Bubbs.  2010ish.  Last revision Sep/2011.


/*
** public mixed* make_unique(mixed* values);
** public mixed* make_unique(mixed* values, closure mapper, varargs mixed* args);
**   Make an array unique, preserving the original ordering.
**   With additional arguments, it is the mapped values that are made
**   unique, and the first matching value is returned.
**   For example:
**     printf("%#Q\n", make_unique(({ 1, 1, 2, 3, 2, 1, 1, })));
**     printf("%#Q\n", make_unique(users(), #'environment));
**
** public mixed merge(varargs mixed *args);
** public mixed merge(closure func, varargs mixed *args);
**   Iteratively call binary functions with result and arguments.
**   Default func is #'+ (sum).
**   For example:
**     printf("%#Q, %#Q\n", merge(0, 1, 2, 3, 4), merge(#'+, 0, 1, 2, 3, 4));
**     printf("%#Q\n", merge(#'*, 1, 2, 4, 8));
**     printf("%#Q\n", merge("hello ", "world"));
**
** public mixed combine(closure func, varargs mixed *args);
** public mixed combine(varargs mixed *args);
**   Combine arrays into a single value.
**   For example:
**     printf("%#Q\n", combine(#'tell_object, users(), combine("Hello ", users()->query_name())));
**     printf("%#Q\n", combine(#'call_other, users(), "short"));
**     printf("%#Q\n", combine(#'+, "10 +", ({ "1", "2", "3", }), " =", ({ "11", "12", "13", })));
**
** public mixed decode(mixed value, [mixed question, mixed answer]*[, mixed default_value]);
**   Compare a value against pairs of question and answer values, returning the
**   corresponding answer, return the default_value or 0 if no questions match.
**   (your right, this doesn't really have anything to do with arrays).
**   For example:
**     printf("%#Q\n", decode(random(4), 0, "north", 1, "east", 2, "south", 3, "west", "up"));
**     printf("%#Q\n", decode(random(4), 0, "north", 1, "east", 2, "south", 3, "west") || "up");
**
** public int pointerp_match(mixed value, closure match, varargs mixed* args);
**   Returns non-zero if value is an array and match evaluates as non-zero for all its elements.
**   For example:
**     printf("%#Q\n", pointerp_match(users(), #'objectp));
**     printf("%#Q\n", pointerp_match(users(), (: environment($1) == $2 :), environment(this_player())));
**
** public mixed* find_by(mixed* values, mixed search_value, closure find_value, varargs mixed* args);
**   Returns an array filtered where the search_value matches the result of calling the find_value
**   function (with additional arguments).  A bit like filter(), but akin to group_by() and order_by().
**   For example:
**     printf("%#Q\n", find_by(users(), environment(this_player()), #'environment));
**     printf("%#Q\n", find_by(all_inventory(), "soul", #'call_other, "id"));
**
** public mapping group_by(mixed* values, closure group_value, varargs mixed* args);
**   Returns a mapping keyed by group values containing arrays of values.
**   The group value is determined by evaluating <group_value>(value, args...).
**   For example:
**     printf("%#Q\n", group_by(({ 0, 1, 2, 3, 4, 5, }), #'%, 3));
**       /* ([ 0:({ 0, 3, }), 1:({ 1, 4, }), 2:({ 2, 5, }), ])
**     printf("%#Q\n", group_by(users(), #'call_other, "query_gender"));
**
** public mixed* order_by(mixed* values, closure order_value, varargs mixed* args);
**   Returns the values sorted by the value of <order_value>(value, args...).
**   For example:
**     printf("%#Q\n", order_by(users(), #'call_other, "query_level"));
**
** public int*   range(int finish);
** public int*   range(int start, int finish);
** public int*   range(int start, int increment, int finish);
** public float* range(float finish);
** public float* range(float start, float finish);
** public float* range(float start, float increment, float finish);
**   Create a range of numbers, from start (default 0) up to the finish, with increment (default 1).
**   If all of the arguments are integers, the result is an integer array.
**   If any of the arguments are floats, the result is a float array.
**   For example:
**     printf("%#Q, %#Q, %#Q\n", range(5), range(0, 5), range(0, 1, 5));
**     printf("%#Q, %#Q, %#Q\n", range(5.0), range(0.0, 5.0), range(0.0, 1.0, 5.0));
*/


//#include "array_utils.h"
//// array_utils.h
//
// Definitions for array utilities.

#if !defined(ARRAY_UTILS_H)
#define ARRAY_UTILS_H


/// array_utils mudlib configuration.

#if defined(TIMEWARP)
// Timewarp style mudlib.

#include <lpctypes.h>

//
#elif defined(DUNE)
// Dune style mudlib.

#include <sys/lpctypes.h>

//
#else
// Unknown 2.4.5 style mudlib.

#include <sys/lpctypes.h>

// If defined, merge() uses a recursive approach, rather than a for() loop.
////#define MERGE_RECURSIVE
//#define NO_MERGE_RECURSIVE

//
#endif


/// array_utils definitions.

#if !defined(MERGE_RECURSIVE) && !defined(NO_MERGE_RECURSIVE)
//#define MERGE_RECURSIVE
#define NO_MERGE_RECURSIVE
#endif


// check a value for an array with elements having a specific property.
#if !defined(POINTERP_MATCH)
//#define POINTERP_MATCH(A, M)           (pointerp((A)) && (sizeof((A)) == sizeof(filter((A), (M)))))
//#define POINTERP_MATCH(A, M)           (funcall((: pointerp($1) && (sizeof($1) == sizeof(filter($1, $2))) :), (A), (M)))
#define POINTERP_MATCH(A, M)           (pointerp_match((A), (M)))
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


#endif
////


//#pragma no_shadow


/// array_utils method prototypes.

public mixed   make_unique        (mixed* values, varargs mixed* args);

public mixed   combine            (mixed func, varargs mixed *args);
public mixed   merge              (mixed func, varargs mixed *args);

public mixed   decode             (mixed value, varargs mixed *args);

public int     pointerp_match     (mixed value, closure match);

public mixed*  find_by            (mixed* values, mixed search_value, closure find_value, varargs mixed* args);
public mapping group_by           (mixed* values, closure group_value, varargs mixed* args);
public mixed*  order_by           (mixed* values, closure order_value, varargs mixed* args);

public mixed*  range              (varargs mixed* args);


/// array_utils methods.

// public mixed* make_unique(values);
// public mixed* make_unique(values, closure mapper, varargs mixed* args);
public mixed* make_unique(mixed* values, varargs mixed* args) {
  !pointerp(values) && raise_error(FUNC_ARG_TYPE_ERROR("make_unique", 1));
  sizeof(args) && !closurep(args) && raise_error(FUNC_ARG_TYPE_ERROR("make_unique", 2));

  mixed *unique = copy(values);
  mixed* mapped = sizeof(args) ? apply(#'map, values, args) : values;
  int    pos    = -1;
  for(int index = sizeof(unique); index-- > 0; )
    if (((pos = member(mapped, mapped[index])) != -1) && (pos < index))
      unique[index..index] = ({ });

  return unique;
}


// public mixed combine(closure func, varargs mixed *args);
// public mixed combine(varargs mixed *args);
// combine() is a generalised index-aware map().
public mixed combine(mixed func, varargs mixed *args) {
  if (!closurep(func)) {
    args = ({ func, }) +args;
    func = #'merge;
  }

  int  *sizes  = map(filter(args, #'pointerp), #'sizeof);
  mixed output = 0;

  if (sizeof(sizes)) {
    int size      = min(sizes);
    int args_size = sizeof(args);

    output = allocate(size);
    for(int index = 0; index < size; index++) {
      int *index_args = allocate(args_size);
      for(int arg_index = 0; arg_index < args_size; arg_index++)
        switch(get_type_info(args[arg_index], 0)) {
          case T_POINTER     :  index_args[arg_index] = args[arg_index][index];    break;
          case T_QUOTED_ARRAY:  index_args[arg_index] = unquote(args[arg_index]);  break;
          default            :  index_args[arg_index] = args[arg_index];           break;
        }

      output[index] = apply(func, index_args);
    }
  }
  else
    output = apply(func, args);

  return output;
}


// public mixed merge(varargs mixed *args);
// public mixed merge(closure func, varargs mixed *args);
public mixed merge(mixed func, varargs mixed *args) {
  if (!closurep(func)) {
    args = ({ func, }) +args;
    func = #'+;
  }

  int   size   = sizeof(args);
#if defined(MERGE_RECURSIVE) && !defined(NO_MERGE_RECURSIVE)
  return (size > 1) ? apply(#'merge, func, apply(func, args[0..1]), args[2..]) : (size && args[0]);
#else
  mixed result = size && args[0];
  for(int index = 1; index < size; index++)
    result = funcall(func, result, args[index]);

  return result;
#endif
}


// public mixed decode(mixed value, [mixed question, mixed answer]*[, mixed default_value]);
public mixed decode(mixed value, varargs mixed *args) {
  int size = sizeof(args);
  for(int index = 0; index < size; index += 2) {
    if ((index +1) == size)
      return args[index];
    if (value == args[index])
      return args[index +1];
  }

  return 0;
}


// public int pointerp_match(value, closure match, varargs mixed* args);
public int pointerp_match(mixed value, closure match, varargs mixed* args) {
  !closurep(match) && raise_error(FUNC_ARG_TYPE_ERROR("pointerp_match", 2));

  return pointerp(value) && (sizeof(value) == sizeof(apply(#'filter, value, match, args)));
}


// find_by(users(), environment(this_player()), #'environment);
// find_by(all_inventory(), "soul", #'call_other, "id");
// public mixed* find_by(mixed* values, mixed search_value, closure find_value, varargs mixed* args)
public mixed* find_by(mixed* values, mixed search_value, closure find_value, varargs mixed* args) {
  !pointerp(values)     && raise_error(FUNC_ARG_TYPE_ERROR("find_by", 1));
  !closurep(find_value) && raise_error(FUNC_ARG_TYPE_ERROR("find_by", 3));

  return
    filter(values, (: apply($3, $1, $4) == $2 :), search_value, find_value, args);
}


// public mapping group_by(mixed* values, closure group_value, varargs mixed* args);
public mapping group_by(mixed* values, closure group_value, varargs mixed* args) {
  !pointerp(values)      && raise_error(FUNC_ARG_TYPE_ERROR("group_by", 1));
  !closurep(group_value) && raise_error(FUNC_ARG_TYPE_ERROR("group_by", 2));

  mixed groups = ([ ]);
  foreach(mixed value : values) {
    mixed group = apply(group_value, value, args);
    groups[group] = (groups[group] || ({ })) +({ value, });
  }

  return groups;
}


// public mixed* order_by(mixed* values, closure order_value, varargs mixed* args);
public mixed* order_by(mixed* values, closure order_value, varargs mixed* args) {
  !pointerp(values)      && raise_error(FUNC_ARG_TYPE_ERROR("order_by", 1));
  !closurep(order_value) && raise_error(FUNC_ARG_TYPE_ERROR("order_by", 2));

  return
    sort_array(values, (: apply($3, $1, $4) > apply($3, $2, $4) :), order_value, args);
}


// public int*   range(int finish);
// public int*   range(int start, int max_number);
// public int*   range(int start, int increment, int finish);
// public float* range(float finish);
// public float* range(float start, float finish);
// public float* range(float start, float increment, float finish);
public varargs mixed* range(varargs mixed* args) {
  int   num_args  = sizeof(args);
  (num_args == 0) && raise_error(FUNC_ARG_ERROR("range", "No arguments"));
  (num_args  > 3) && raise_error(FUNC_ARG_ERROR("range", "Too many arguments"));

  mixed start     = (num_args > 1) && args[0];
  mixed finish    = (num_args > 0) && args[<1];
  mixed increment = (num_args > 2) ? args[1] : ((intp(start) || floatp(start)) && (intp(finish) || floatp(finish)) && sgn(finish -start));

  !(intp(start)     || floatp(start))     && raise_error(FUNC_ARG_TYPE_ERROR("range", 1));
  !(intp(finish)    || floatp(finish))    && raise_error(FUNC_ARG_TYPE_ERROR("range", 3));
  !(intp(increment) || floatp(increment)) && raise_error(FUNC_ARG_TYPE_ERROR("range", 2));

  (sgn(finish -start) != sgn(increment))  && raise_error(FUNC_ARG_ERROR("range", "Bad increment"));

  int  float_range  = floatp(start) || floatp(increment) || floatp(finish);
  int* range_result = ({ });
  for(mixed value = float_range ? to_float(start) : start; (increment > 0) ? (value <= finish) : (value >= finish); value += increment)
    range_result += ({ value, });

  return range_result;
}


////


