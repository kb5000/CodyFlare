#pragma once
#include "linked_list.h"
#include "utility.h"

typedef enum {
	Col_Box, Col_Line
} ColType;

typedef struct {
	int id;
	ColType colType;
	Pos start, end;
} CollisionObj;

typedef void ColHandler(int id1, int id2, void* para);

///these are functions to control collision system

///name: init_col_detector
///func: initialize the collision detector
///visb: public
void init_col_detector();
///name: destroy_col_detector
///func: stop and destroy the detection 
///visb: public
void destroy_col_detector();
///name: start_detection
///func: start to detect collision
///para: detectInterval expects during how long it will detect collision
///visb: public
///warn: timerID 16777216 will be occupied
void start_detection(int detectInterval);
///name: stop_detection
///func: stop the detection
///visb: public
void stop_detection();

///these are functions to control collision object

///name: add_col_group
///func: add a new collision group
///para: id expects a unique group id
///visb: public
void add_col_group(int id);
///name: create_col_obj
///func: create a Collision Object
///para: colType expects Col_Box or Col_Line, start expects the pos of the down-left corner,
///      end expects the pos of the up-right corner, id expects a unique obj id
///visb: public
CollisionObj create_col_obj(ColType colType, Pos start, Pos end, int id);
///name: add_col_obj_to_group
///func: add a collision object to the group
///para: groupID expects an exist groupID, colObj expects a CollisionObj
///visb: public
///warn: make sure colObj has a unique id, or it will update the exist value
void add_col_obj_to_group(int groupID, CollisionObj colObj);

///this is to control collision event

///name: add_col_handler
///func: add an event handler when groupID1 and groupID2 have collisions
///para: groupID1 and groupID2 expects valid groupID, func expects a func like
///      void func(int objID1, int objID2, void* para), and will pass para to func
///visb: public
void add_col_handler(int groupID1, int groupID2, ColHandler func, void* para);

///these are functions to handle collision object

///name: find_col_obj
///func: return an obj determined by groupID and objID
///para: groupID and objID expects valid ID
///visb: public
CollisionObj* find_col_obj(int groupID, int objID);
///name: remove_col_obj
///func: remove an collision object
///para: groupID and objID expects valid ID
///visb: public
void remove_col_obj(int groupID, int objID);
///name: update_col_info
///func: update an collision object
///para: groupID and objID expects valid ID, start and end expects the new position
///visb: public
void update_col_info(int groupID, int objID, Pos start, Pos end);



