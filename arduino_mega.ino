
#include <Keypad.h>


/* 
 *  Struct that will represent single node in database linked list
 */
typedef struct ___node {
  long _id;
  char _name[20];
  char _surname[25];
  short int _status;
  struct ___node* _next; 
} _node;


/*
 * Struct that will represent linked list database. This linked list is used to store users with their names and their id key for 
 * activating or deactivating system. 
 */
typedef struct ___linked_list {
  _node* _first_node;
  int _counter;
} _list;


/*
 * Struct that will represent single node in keypadl linked list.
 */
typedef struct __node{
  int _value;
  struct __node* _next;
}node;


/*
 * Struct that will represent linked list. This linked list is used to store digits entered by user through keypad.
 * Linked list is used to easily create and manipulate queue of digits.
 */
typedef struct __linked_list{
  short int counter;
  node* _first_node;
}list;


// Array that will hold seven digits from linked list when they need to be sent to main server on Raspberry Pi.
char* array = (char*) malloc(7 * sizeof(char));
// Creating actual linked list variable that will be used to hold digits from keypad.



list keypadl;
_list database;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {1,2,3},
  {4,5,6},
  {7,8,9},
  {'*',0,'#'}
};
int motionSensorPin = 38;
int buzzerPin = 36;
long pin;
bool alarmSystem = false;
byte rowPins[ROWS] = {52, 50, 48, 46}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {44,42,40}; //connect to the column pinouts of the keypad


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


/*
*   
*/
void addNode(list*, int);


/*
*   Prints out list to the Serial monitor.
*/
void printList();


/*
*   Converts seven digits from the linked list to the seven digit integer.
*   Returns integer representation of the digits from linked list.
*/
long convertToNumber();


/*
 * Restart all data stored in linked list to zeros
 */
void restartList();


/*
 * This function adds new user to the linked list called database
 */
void addUser(_list*, long, char*, char*);


/*
 * Removes user from linked list. 
 * Takes one argument which is user ID
 */
void removeUser(long);


/*
 * Deletes node from database linked list
 * Function is called automaticlly in removeUser function and tkaes one argument, ID
 */
void deleteNode(long);


void idCheck(_list*);


char user[20]="name";
char surname[25]="lastname";
long id = 1111111;

void setup() {
  Serial.begin(9600);
  Serial.println("Robojax 4x3 keypad");
  pinMode(buzzerPin, OUTPUT); 
  pinMode(motionSensorPin, INPUT); 
  addUser(&database,id, user, surname);
 

    keypadl.counter = 0;
}

void loop() {
int a=1;
  database._counter = 0;
  char key = keypad.getKey();

      

     
     
      if(key!=0 && key!='#')
        {
          addNode(&keypadl, (char)key);
        }
        
        else if(key== '#')
        {
          pin=convertToNumber();
          Serial.println("Checked");
         Serial.println(pin);
          idCheck(&database);
          restartList();
          delay(4000);
          }
          
    
      while((alarmSystem==true) ){
      key = keypad.getKey();
      Serial.println(digitalRead(motionSensorPin));
         if ((digitalRead(motionSensorPin) == HIGH))
     {
       Serial.println(digitalRead(motionSensorPin));
      
      digitalWrite(buzzerPin,HIGH);
     }
      
       if(key!=0 && key!='#')
        {
          addNode(&keypadl, (char)key);
        }
        else if(key== '#')
        {
          pin=convertToNumber();
        idCheck(&database);
        restartList();
          }
          
        
        
      
      
     
      }
     
}
    



void addNode(list* myList, int value)
{
  if (myList->counter == 0)
  {
    node* some_node = new node;
    some_node->_value = value;
   
    Serial.println("Added as a head of the linked list!");
    
    some_node->_next = 0;
    myList->_first_node = some_node;
    myList->counter = 1;
  }
  else if (myList->counter < 7)
  {
    node* some_node = new node;
    some_node->_value = value;
  
    some_node->_next = 0;

    node* current = myList->_first_node;
    while(current)
    {
      if (!current->_next)
      {
        current->_next = some_node;
        Serial.println("Added as below 7");
       
        myList->counter += 1;
       
        break;
      }
      else
      {
        current = current->_next;
      }
    }
  }
  else
  {
      node* some_node = new node;
      some_node->_value = value;
      Serial.println("Added as above 7");
      some_node->_next = 0;

      node* current = myList->_first_node;
      while(current)
      {
        if (!current->_next)
        {
          current->_next = some_node;
          break;
        }
        else
        {
          current = current->_next;
        }
      }
      node* _node = myList->_first_node;
      myList->_first_node = myList->_first_node->_next;
      delete _node;
    }
}


long convertToNumber()
{
node* current = keypadl._first_node;
long result=0;
  while(current)
  {
      result = (result * 10) + current->_value;
      Serial.println(result);
      current = current->_next;
  }
  return result;
 }

 
  void restartList()
{
  node* current = keypadl._first_node;
  while(current)
  {
      current->_value = 0;
      
      current = current->_next;
  }
  
}


void addUser(_list* _database, long id, char* name, char* surname)
{
  
  if (database._counter == 0)
  {
    _node* newNode = (_node*) malloc(sizeof(_node));
    newNode->_id = id;
    strcpy(newNode->_name, name);
    strcpy(newNode->_surname, surname);
    newNode->_status = 0;
    newNode->_next = 0;
    _database->_first_node = newNode;
    printf("\n");
    _database->_counter += 1;
    return;
  }
  else 
  {
    _node* current = _database->_first_node;

    while(current)
    {
      if (current->_id == id)
        return;
      
      if (!current->_next)
      {
        
        _node* newNode = (_node*) malloc(sizeof(_node));
        newNode->_id = id;
        strcpy(newNode->_name, name);
        strcpy(newNode->_surname, surname);
        newNode->_status = 0;
        newNode->_next = 0;
        current->_next = newNode;
        printf("\n");
        _database->_counter += 1;
        return;
      }
      else
      {
        current = current->_next;
      }
    }
  }
}


void removeUser(long id)
{
  bool check = false;
  _node* current = database._first_node;
  while(current)
  {
    if(current->_id == id)
    {
      check = true;
      if (current->_status == 1)
        current->_status = 2;
      else if(current->_status == 0)
        deleteNode(id);
    }
    current = current->_next;
  }

  if (!check)
    return;
}


void deleteNode(long id)
{
  if (database._first_node->_id == id)
  {
    _node* temp = database._first_node;
    database._first_node = database._first_node->_next;
    free(temp);
    return;
  }

  _node* current = database._first_node->_next;
  _node* previous = database._first_node;

  while(current)
  {
    if (current->_id == id)
    {
      previous->_next = current->_next; 
      free(current);
      return;
    }
    previous = current;
    current = current->_next;
  }
}


void idCheck(_list* _database)
{
  _node* current = _database->_first_node;  

Serial.println(pin);
  while(current)
  {
    
    Serial.println(current->_id);
     Serial.println(current->_name);
    if(current->_id == pin)
    {
    
      if(alarmSystem==true)
      {
   
        alarmSystem=false;
        digitalWrite(buzzerPin,LOW);
      }
      else if(alarmSystem!=true) 
      {
   
        alarmSystem=true;
      }
    }
    current = current->_next;
  }
}
