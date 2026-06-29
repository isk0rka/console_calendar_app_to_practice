#ifndef CALENDAR_APP_CORE_CONSTANTS_H
#define CALENDAR_APP_CORE_CONSTANTS_H

constexpr int EVENT_TITLE_SIZE = 128;
constexpr int EVENT_DESCRIPTION_SIZE = 256;
constexpr int EVENT_CATEGORY_SIZE = 64;
constexpr int REMINDER_MESSAGE_SIZE = 256;

constexpr int INITIAL_EVENTS_CAPACITY = 10;
constexpr int INITIAL_REMINDERS_CAPACITY = 10;    

constexpr int MIN_YEAR = 2000;
constexpr int MAX_YEAR = 2100;

constexpr int MIN_MONTH = 1;
constexpr int MAX_MONTH = 12;

constexpr int MIN_DAY = 1;
constexpr int MAX_DAY = 31;

constexpr int MIN_HOUR = 0;
constexpr int MAX_HOUR = 23;

constexpr int MIN_MINUTE = 0;
constexpr int MAX_MINUTE = 59;

constexpr int DEFAULT_IS_RUNNING = 1;              
constexpr int DEFAULT_IS_NOT_TRIGGERED = 0;        
constexpr int DEFAULT_IS_TRIGGERED = 1;

constexpr int DEFAULT_NEXT_EVENT_ID = 1;
constexpr int DEFAULT_NEXT_REMINDER_ID = 1;        

constexpr int PROGRAM_SUCCESS_STATUS = 0;
constexpr int PROGRAM_ERROR_STATUS = 1;            

constexpr int LOGIC_OK = 0;                        
constexpr int LOGIC_ERROR_INVALID_DATE = 1;       
constexpr int LOGIC_ERROR_INVALID_TIME = 2;        
constexpr int LOGIC_ERROR_INVALID_TIME_RANGE = 3;  
constexpr int LOGIC_ERROR_EMPTY_TITLE = 4;         
constexpr int LOGIC_ERROR_EVENT_NOT_FOUND = 5;     
constexpr int LOGIC_ERROR_REMINDER_NOT_FOUND = 6;  
constexpr int LOGIC_ERROR_EVENT_ALREADY_EXISTS = 7; 
constexpr int LOGIC_ERROR_REMINDER_ALREADY_EXISTS = 8; 
constexpr int LOGIC_ERROR_MEMORY_ALLOCATION = 9;   
constexpr int LOGIC_ERROR_FILE_OPEN = 10;          
constexpr int LOGIC_ERROR_FILE_READ = 11;          
constexpr int LOGIC_ERROR_FILE_WRITE = 12;         
constexpr int LOGIC_ERROR_INVALID_EVENT_ID = 13;   
constexpr int LOGIC_ERROR_INVALID_REMINDER_ID = 14;
constexpr int LOGIC_ERROR_INVALID_CATEGORY = 15;
constexpr int LOGIC_ERROR_INVALID_PRIORITY = 16;
constexpr int LOGIC_ERROR_INVALID_STATUS = 17;
constexpr int LOGIC_ERROR_LINKED_EVENT_NOT_FOUND = 18;
constexpr int LOGIC_ERROR_STORAGE_IS_EMPTY = 19;  

constexpr int MENU_SHOW_TODAY_EVENTS = 1;         
constexpr int MENU_SHOW_EVENTS_BY_DATE = 2;        
constexpr int MENU_SHOW_EVENTS_BY_WEEK = 3;        
constexpr int MENU_ADD_EVENT = 4;                  
constexpr int MENU_EDIT_EVENT = 5;                 
constexpr int MENU_DELETE_EVENT = 6;              
constexpr int MENU_FIND_EVENT = 7;                 
constexpr int MENU_ADD_REMINDER = 8;               
constexpr int MENU_SHOW_REMINDERS = 9;             
constexpr int MENU_CHECK_DUE_REMINDERS = 10;       
constexpr int MENU_DELETE_REMINDER = 11;           
constexpr int MENU_SAVE_DATA = 12;                 
constexpr int MENU_EXIT = 13;                      

constexpr const char EVENTS_FILE_NAME[] = "data/events.txt";
constexpr const char REMINDERS_FILE_NAME[] = "data/reminders.txt";

constexpr char FIELD_SEPARATOR = ';';
constexpr char DATE_SEPARATOR = '.';
constexpr char TIME_SEPARATOR = ':';

#endif