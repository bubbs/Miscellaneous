//// input_key.
//
// simple interface to a simple character buffer engine with key recognition.
//
// Bubbs.  August/2011.


/// input_key portable mudlib configuration definitions.

#if defined(TIMEWARP)
// Timewarp style mudlib.

#include <input_to.h>


//
#elif defined(DUNE)
// Dune style mudlib.


//
#else
// Unknown mudlib (assume 2.5.5 LPMud mudlib).

// Include system input_to.h header file.
//#include <sys/input_to.h>

// If active (default), defines key definition file which enables "key" input type.
// If not active, generate essential key definitions only.
//#define KEY_DEFINITION_DATA_FILE       "/"__DIR__".input_key.o"
////#define NO_KEY_DEFINITION_DATA_FILE


//
#endif


/// input_key portable mudlib definitions.

#if !defined(LPC_INPUT_TO_)
#include <sys/input_to.h>
#endif

#if !defined(KEY_DEFINITION_DATA_FILE) && !defined(NO_KEY_DEFINITION_DATA_FILE)
#define KEY_DEFINITION_DATA_FILE       "/"__DIR__".input_key.o"
//#define NO_KEY_DEFINITION_DATA_FILE
#endif


/// input_key macro definitions.

// check a value for an array with elements having a specific property.
#if !defined(POINTERP_MATCH)
//#define POINTERP_MATCH(A, M)           (pointerp((A)) && (sizeof((A)) == sizeof(filter((A), (M)))))
#define POINTERP_MATCH(A, M)           (funcall((: pointerp($1) && (sizeof($1) == sizeof(filter($1, $2))) :), (A), (M)))
//#define POINTERP_MATCH(A, M)           (pointerp_match((A), (M)))
#endif

// check a value for an array of a specific type.
#if !defined(TYPED_POINTERP)
#define TYPED_POINTERP(A, T)           (POINTERP_MATCH((A), symbol_function(trim("T") +"p") || raise_error("TYPED_POINTERP(): Bad second argument.\n")))
#endif

// format an function argument error.
#if !defined(FUNC_ARG_ERROR)
#define FUNC_ARG_ERROR(F, E)           (object_name() +"::" +(F) +"(): " +(E) +".\n")
#endif

// format an function argument type error.
#if !defined(FUNC_ARG_TYPE_ERROR)
#define FUNC_ARG_TYPE_ERROR(F, N)      (FUNC_ARG_ERROR((F), "Bad type to argument " +(N)))
#endif



/// input_key variables.

nosave    mapping key_defns          = 0;
nosave    mapping build_keys         = 0;


/// input_key query method prototypes.

public    string* query_key_defns      ();
public    string* query_key_names      ();
public    string* query_build_keys     ();
public    string  query_key_name       (string key_defn);
public    string* query_key_defn       (string key_name);


/// input_key process method prototypes.

public    int     input_key            (mixed callback, varargs mixed* args);

public    int     init_key_defns       ();
protected void    input_key_handler    (string character, string key_buffer, closure callback, mixed* args);


/// input_key utility method prototypes.

public    string  encode_key_name      (string key_defn);
public    int     generate_key_defns   (string output_fname);


/// input_key mudlib interface.

//public void create() {
//}

//public void reset() {
//}

//public void init() {
//}

public int deny_update() {
  return sizeof(filter(map(users(), #'query_input_pending), #'==, this_object()));
}

public int clean_up(int arg) {
  if (deny_update())
    return 1;
  destruct(this_object());
  return 0;
}

public void destructor() {
  //
}


/// input_key query methods.

public string* query_key_defns () { return m_indices(key_defns);  }
public string* query_key_names () { return m_values(key_defns);   }
public string* query_build_keys() { return m_indices(build_keys); }

public string  query_key_name  (string key_defn) { return key_defns[key_defn]; }

public string* query_key_defn  (string key_name) { return filter(m_indices(key_defns), (: key_defns[$1] == $2:), key_name); }



/// input_key process methods.


public int input_key(mixed callback, varargs mixed* args) {
  !(stringp(callback) || closurep(callback)) && raise_error(FUNC_ARG_TYPE_ERROR("input_key", 1));

  closure cback = closurep(callback) ? callback : symbol_function(callback, extern_call() ? previous_object() : this_object());
  !cback && raise_error("input_key(): Unable to find callback function.\n");

  if (!this_player() || query_input_pending(this_player()) || query_editing(this_player()))
    return 0;

  //(!load_term_type || (load_term_type != loaded_term_type)) && init_key_defns(load_trm_type);
  !sizeof(key_defns) && init_key_defns();

  input_key_handler(0, "", cback, args);

  return 1;
}


public int init_key_defns() {
  // load key definitions file.
  string defn_fname = KEY_DEFINITION_DATA_FILE;
  defn_fname = ((defn_fname[0] == '/') ? "" : "/") +defn_fname;
  foreach(string defn_line : explode(read_file(defn_fname) || read_file(defn_fname +".o") || "", "\n")) {
    string var_name = 0;
    string var_defn = 0;
    switch((defn_line[0] != '#') && (sscanf(defn_line, "%s %s", var_name, var_defn) == 2) && var_name) {
      case "build_keys":  build_keys = restore_value("#1:0\n" +var_defn +"\n");  break;
      case "key_defns" :  key_defns  = restore_value("#1:0\n" +var_defn +"\n");  break;
    }
  }

  if (!sizeof(key_defns)) {
    // generate emergency key definitions.
    key_defns  = ([ ]);
    build_keys = ([:0 ]);

    m_add(build_keys, "");
    m_add(build_keys, "\e");
    m_add(build_keys, "\e\e");
    m_add(build_keys, "\eO");
    m_add(build_keys, "\e[");
    m_add(build_keys, "\e\eO");
    m_add(build_keys, "\e\e[");

    for(int ch = 1; ch < 256 ; ch++) {
      string key_defn = sprintf("%c", ch);
      !member(build_keys, key_defn) && m_add(key_defns, key_defn, encode_key_name(key_defn));
      key_defn = "\e" +key_defn;
      !member(build_keys, key_defn) && m_add(key_defns, key_defn, encode_key_name(key_defn));
      key_defn = "\e" +key_defn;
      !member(build_keys, key_defn) && m_add(key_defns, key_defn, encode_key_name(key_defn));
    }
  }

  return 1;
}


protected void input_key_handler(string character, string key_buffer, closure callback, mixed* args) {
  !(!character || stringp(character)) && raise_error(FUNC_ARG_TYPE_ERROR("input_key_handler", 1));
  !stringp(key_buffer)                && raise_error(FUNC_ARG_TYPE_ERROR("input_key_handler", 2));
  !closurep(callback)                 && raise_error(FUNC_ARG_TYPE_ERROR("input_key_handler", 3));
  !pointerp(args)                     && raise_error(FUNC_ARG_TYPE_ERROR("input_key_handler", 4));

  key_buffer += (character || "");

  int    building = 0;
  string key_name = 0;

  if (member(build_keys, key_buffer))
    building = 1;
  else if (member(key_defns, key_buffer))
    key_name = key_defns[key_buffer];

  // unknown key; do not know if the input buffer has keys pending,
  // cannot be certain if the key is a build-key or not.
  // adding global variable and more structure could enable waiting for more characters with a time-out.
  // for now, see if there are any existing keys which would need this as a build-key.

  else if (sizeof(filter(m_indices(key_defns), (: !strstr($1, $2) :), key_buffer))) {
    // learn the build key, for the future.
    m_add(build_keys, key_buffer);
    building = 1;
  }

  // otherwise, assume it's a key, but don't learn it.
  else
    key_name = encode_key_name(key_buffer);

  if (building)
    input_to(#'input_key_handler, INPUT_NOECHO | INPUT_CHARMODE | INPUT_IGNORE_BANG, key_buffer, callback, args);
  else
    apply(callback, key_name, args);
}


/// input_key utility method prototypes.

public string encode_key_name(string key_defn) {
  !stringp(key_defn) && raise_error(FUNC_ARG_TYPE_ERROR("encode_key_name", 1));

  string key_name = "";
  foreach(int ch : key_defn)
    switch(ch) {
      case  0 .. 31:  key_name += sprintf("^%c", '@' +ch);  break;
      case      ' ':  key_name += "SPACE";                  break;
      case '!'..'~':  key_name += sprintf("%c", ch);        break;
      case 127     :  key_name += "^?";                     break;
      default      :  key_name += sprintf("#%02x", ch);     break;
    }

  return key_name;
}


public int generate_key_defns(string output_fname) {
  !(!output_fname || stringp(output_fname)) && raise_error(FUNC_ARG_TYPE_ERROR("generate_key_defns", 1));

  string defn_fname = strlen(output_fname) ? output_fname : KEY_DEFINITION_DATA_FILE;
  defn_fname = ((defn_fname[0] == '/') ? "" : "/") +defn_fname;
  if (regreplace(defn_fname, "^.*/[^/]+\\.[^/]+$", "", 0) == defn_fname)
    defn_fname += ".o";

  if (((file_size(defn_fname) > 0) && !rm(defn_fname)) || !write_file(defn_fname, ""))
    return 0;

  mapping  builds    = ([:0 ]);
  mapping  defns     = ([ ]);

  closure add_builds = (: m_add($1, $2),     m_add($1, "\e" +$2),           $1 :);
  closure add_defns  = (: m_add($1, $2, $3), m_add($1, "\e" +$2, "^[" +$3), $1 :);

  builds = funcall(add_builds, builds, "");
  builds = funcall(add_builds, builds, "\e");
  builds = funcall(add_builds, builds, "\e[");
  builds = funcall(add_builds, builds, "\eO");
  for(int n = 0; n <= 99; n++)
    builds = funcall(add_builds, builds, "\e[" +n);

  for(int ch = 0; ch < 256; ch++)
    if (ch != '\e') {
      string defn = sprintf("%c", ch);
      string name = encode_key_name(defn);
      !member(builds, defn) && m_add(defns, defn, name);
      defn = "\e" +defn;
      name = "^[" +name;
      !member(builds, defn) && m_add(defns, defn, name);
      defn = "\e" +defn;
      name = "^[" +name;
      !member(builds, defn) && m_add(defns, defn, name);
    }

  defns["\e\e\e"] = "^[^[^[";

  //builds = funcall(add_builds, builds, "\eO");
  //builds = funcall(add_builds, builds, "\e[");

  for(int n = 1; n <= 12; n++)
    defns = funcall(add_defns, defns, sprintf("\eO%c", 'O' +n), "F" +n);

  defns = funcall(add_defns, defns, "\e[15~", "F5");
  for(int n = 6; n <= 10; n++)
    defns = funcall(add_defns, defns, sprintf("\e[%d~", 11 +n), "F" +n);
  defns = funcall(add_defns, defns, "\e[23~", "F11");
  defns = funcall(add_defns, defns, "\e[24~", "F12");

  defns = funcall(add_defns, defns, "\e[1~", "HOME");
  defns = funcall(add_defns, defns, "\e[2~", "INSERT");
  defns = funcall(add_defns, defns, "\e[3~", "DELETE");
  defns = funcall(add_defns, defns, "\e[4~", "END");
  defns = funcall(add_defns, defns, "\e[5~", "PAGEUP");
  defns = funcall(add_defns, defns, "\e[6~", "PAGEDOWN");

  defns = funcall(add_defns, defns, "\eOH", "HOME");
  defns = funcall(add_defns, defns, "\eOF", "END");

  defns = funcall(add_defns, defns, "\e[A", "UP");
  defns = funcall(add_defns, defns, "\e[B", "DOWN");
  defns = funcall(add_defns, defns, "\e[C", "RIGHT");
  defns = funcall(add_defns, defns, "\e[D", "LEFT");

  //defns = funcall(add_defns, defns, "\eOZ",   "SF1");
  //defns = funcall(add_defns, defns, "\eO[",   "SF2");
  defns = funcall(add_defns, defns, "\e[25~", "SF3");
  defns = funcall(add_defns, defns, "\e[26~", "SF4");

  defns = funcall(add_defns, defns, "\e[28~", "SF5");
  defns = funcall(add_defns, defns, "\e[29~", "SF6");
  defns = funcall(add_defns, defns, "\e[31~", "SF7");
  defns = funcall(add_defns, defns, "\e[32~", "SF8");

  defns = funcall(add_defns, defns, "\e[33~", "SF9");
  defns = funcall(add_defns, defns, "\e[34~", "SF10");
  //defns = funcall(add_defns, defns, "\e[23~", "SF11");
  //defns = funcall(add_defns, defns, "\e[24~", "SF12");

  defns = funcall(add_defns, defns, "\eOA", "^UP");
  defns = funcall(add_defns, defns, "\eOB", "^DOWN");
  defns = funcall(add_defns, defns, "\eOC", "^RIGHT");
  defns = funcall(add_defns, defns, "\eOD", "^LEFT");

#if 0
  foreach(string key_defn : defns)
    for(int index = 1; index < strlen(key_defn); index++) {
      m_add(builds, key_defn[..index -1]);
      m_delete(defns, key_defn[..index  -1]);
    }
#endif

  return write_file(defn_fname, sprintf("#1:0\nbuild_keys %skey_defns %s", save_value(builds)[5..], save_value(defns)[5..]));
}


////


