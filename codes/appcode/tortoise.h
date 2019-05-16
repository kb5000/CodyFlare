#pragma once
#include "utility.h"

///This is the powerful tortoise drawing system

///name: move_tortoise
///func: move my cute tortoise to the specified position
///para: pos expects a valid position
///visb: public
void move_tortoise(Pos pos);

///name: tts_fd
///func: let my cute tortoise go forward, it may remain some trace, but it is not smelly!
///para: len expects the length tortoise will go
///visb: public
void tts_fd(double len);

///name: tts_bk
///func: cruelly make my pitiful tortoise go backward, it may also remain trace.
///para: len expects the length tortoise will go
///visb: public
void tts_bk(double len);

///name: tts_lt
///func: let my little tortoise turn left, degrees only!
///para: deg expects a degree from 0 to 360
///visb: public
void tts_lt(double deg);

///name: tts_rt
///func: try to make my naughty tortoise turn right, it seems that we are always successful
///para: deg expects a degree from 0 to 360
///visb: public
void tts_rt(double deg);

///name: tts_pu
///func: let my dirty tortoise go shower and it will not remain trace
///visb: public
void tts_pu();

///name: tts_pd
///func: do some unknown things to my clean tortoise and it will remain trace
///visb: public
void tts_pd();

///name: tts_turn
///func: roll my tortoise to the specified direction, does it so cruel?
///para: deg expects a direction from 0 to 360
///visb: public
void tts_turn(double deg);

///name: tts_home
///func: let my kind tortoise go home immediatlely, may remain some trace!
///visb: public
void tts_home();

///name: tts_set_home
///func: tell my learned tortoise to build a house here, this is its new home!
///visb: public
void tts_set_home();
