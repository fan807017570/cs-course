/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:event_manager.h
*      Author: miracle
* crete  date:20220404/13/22
* description:
*
=========================================================*/
#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__
typedef struct event_loop{

}EventLoop; 
/*main loop of the main thread ,get io event through multiplexed io ,and dispatch the event 
 to the reactor thread to handle acceptable ,readable or writable event ,at the same time 
execute the hook.*/
int void main_loop();
/*
 *init a event loop structure.
 * */
EventLoop *create_event_loop(int setsize);

/*
 *Call multiplexed API ,will return only when some vent fires.
 * */
void process_event(EventLoop *loop);
/*
 * Call multiplexed API to add to the io events 
 * */
int add_event(EventLoop *loop); 





#endif
