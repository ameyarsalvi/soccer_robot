
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(A2, A3);  // Connect the TXD pin of BT module to pin A2 of the Arduino, RXD to pin A3

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

signed int x;
signed int y;
signed int z;
signed int btna;
signed int btnb;
float a;
float m;


String str;
char dir = 0;


int ML1 = 5;
int ML2 = 4;
int MR1 = 6;
int MR2 = 7;


int EL = 9;   
int ER = 10; 

int el = 0;
int er = 0;

int elp = 0;
int erp = 0;


boolean fast = true;
boolean StateA0 = false;
boolean StateA1 = false;
boolean State11 = false;

int LED1 = 13;
int LED2 = 3;



void setup() {
  
pinMode(ER, OUTPUT); 
pinMode(EL, OUTPUT); 
pinMode(ML1, OUTPUT); 
pinMode(ML2, OUTPUT); 
pinMode(MR1, OUTPUT); 
pinMode(MR2, OUTPUT); 

pinMode(11, OUTPUT); 
pinMode(12, OUTPUT); 

pinMode(LED1, OUTPUT); 
pinMode(LED2, OUTPUT); 

digitalWrite(LED1, LOW);

mySerial.begin(9600);
mySerial.println("Start");

  myservo1.attach(11);  // attaches the servo on pin 11 to the servo object
  myservo2.attach(12);  // attaches the servo on pin 12 to the servo object
  myservo1.write(0);
  delay(1000);
  myservo1.detach();  // attaches the servo on pin 11 to the servo object
  myservo2.detach();  // attaches the servo on pin 12 to the servo object  
  delay(1000);

digitalWrite(LED1, HIGH);
//myservo1.write(0);   
//myservo2.write(0);   
}


void loop() 
{
    while(mySerial.available())
    {
      
      char getData = mySerial.read();
      
        if (getData == 'M')
        {
          m = mySerial.parseFloat();
          
          if (mySerial.read() == '#') 
          {
            processM();
          }
        }
        
        if (getData == 'A')
        {
          a = mySerial.parseFloat();
          
          if (mySerial.read() == '#') 
          {
            processA();
          }
        }
       
        if (getData == 'a')
        {  
          delay(5);        
          if (mySerial.read() == '#') 
          {
            processa();
          }
        }      
       
        if (getData == 'b')
        {    
          delay(5);
          if (mySerial.read() == '#') 
          {
            processb();
          }
        }   

        if (getData == 'c')
        {     
          delay(5);
          if (mySerial.read() == '#') 
          {
            processc();
          }
        } 

        if (getData == 'x')
        {  
          delay(5);        
          if (mySerial.read() == '#') 
          {
            processx();
          }
        }      
       
        if (getData == 'y')
        {    
          delay(5);
          if (mySerial.read() == '#') 
          {
            processy();
          }
        }   

        if (getData == 'z')
        {     
          delay(5);
          if (mySerial.read() == '#') 
          {
            processz();
          }
        } 
        
        if (getData == '~') {
        
          x = mySerial.parseInt();
        
            if (mySerial.read() == '*') {
        
              y = mySerial.parseInt();
        
                if (mySerial.read() == '@') {
                
                  z = mySerial.parseInt();
                  
                    if (mySerial.read() == '#') {
                    
                      process();
                  }                
              } 
           }
        }
        
          
        
    }
    
}

void processa(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);   
  mySerial.println("Front gate opened!");
  myservo1.attach(11);  // attaches the servo on pin 11 to the servo object
  myservo2.attach(12);  // attaches the servo on pin 12 to the servo object
  myservo1.write(100);
  delay(1000);
  myservo1.detach();  // attaches the servo on pin 11 to the servo object
  myservo2.detach();  // attaches the servo on pin 12 to the servo object  
  delay(1000);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW); 
  mySerial.flush();  
}

void processb(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);  
  mySerial.println("Front gate closed! ");
  myservo1.attach(11);  
  myservo2.attach(12);  
  myservo1.write(0);
  delay(1000);
  myservo1.detach();  
  myservo2.detach();   
  delay(1000);
  mySerial.flush();  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
}

void processc(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  mySerial.println("Kick! ");
  myservo1.attach(11);  
  myservo2.attach(12);  
  myservo2.write(90);
  delay(1000);
  myservo2.write(0);
  delay(1000);
  myservo1.detach();  
  myservo2.detach(); 
  delay(1000);
  mySerial.flush(); 
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);  
}

void processx(){
  mySerial.println("GATE OPENED!"); 
  for(int i=0; i++; i<300)
  { 
        mySerial.print("Open i: " + String(i));
        bukaGate(); }
  mySerial.flush(); 
  //fast = true;
}

void processy(){
  mySerial.println("GATE CLOSED!"); 
  tutupGate();
  mySerial.flush(); 
}

void processz(){
  mySerial.println("KICK!"); 
  myservo2.write(90);         
  delay(800);
  myservo2.write(0);          
  delay(800);  
  mySerial.flush(); 
  //fast = false;
}



void processM(){
//  m1 = map(m, 0, 500, 0, 255); 
//  mySerial.print("Received Magnitude: ");
//  mySerial.println(m1); 
//  mySerial.flush();   
}

void processA(){
  mySerial.print("Received Angle: ");
  mySerial.println(a); 
  mySerial.flush();   
}

void bukaGate(){
    digitalWrite(11, HIGH);
    delayMicroseconds(2000);
    digitalWrite(11, LOW);
    delayMicroseconds(18000);  
}

void tutupGate(){
  for(int i=0; i++; i<300)
  {
    mySerial.print("Close i: " + String(i));
    digitalWrite(11, HIGH);
    delayMicroseconds(1000);
    digitalWrite(11, LOW);
    delayMicroseconds(19000);  
  }
}

void process(){

//  mySerial.println("x: " + String(x) + ", y: " + String(y));
//
//  mySerial.print("Received x: " );
//  mySerial.print(x);
//  
//  mySerial.print(", Received y: " );
//  mySerial.println(y);
  

  //left motor control:

  y = constrain(y, -255, 255);
    
//  if (fast == false) { er = map(y, 0, 255, 0, 255); }
//  else { er = y; }
  er = y;
  
  er = map(y, 0, 255, 0, 255);

  if (er < 0) { 
    digitalWrite(MR1, HIGH);
    digitalWrite(MR2, LOW);  
  } 
  
  else if (er >= 0) { 
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, HIGH);
  } 
  
  erp = abs(er);
  

//right motor control:

  x = constrain(x, -255, 255);

//  if (fast == false) { el = map(x, 0, 255, 0, 255); }
//  else { el = x; }
  el = x;
  
  el = map(x, 0, 255, 0, 255);

  if (el < 0) { 
    digitalWrite(ML1, HIGH); 
    digitalWrite(ML2, LOW); 
  } 
  
  else if (el >= 0)  {
    digitalWrite(ML1, LOW); 
    digitalWrite(ML2, HIGH); 
  } 
  
  elp = abs(el);
                                                 
  analogWrite(EL, elp);  
  analogWrite(ER, erp);     
  
  
  mySerial.flush(); 
}  
