#include <english.h>
#include <TTS.h>

#define ledPin 13

#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 7
#define echoPin3 8
#define buzzer   12
char _int2str[7];
char text [50];
char g[20];
char* s;
int count=0;
boolean state=0;
int sound=50;

long duration, distance, RightSensor,FrontSensor,LeftSensor,avg;
 TTS text2speech;
void setup()
{
Serial.begin (9600);
pinMode(ledPin, OUTPUT);

pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
}
 
void loop() {
state = !state;
digitalWrite(ledPin, state);
  
SonarSensor(trigPin2, echoPin2);
FrontSensor = distance;
SonarSensor(trigPin1, echoPin1);
LeftSensor = distance;
SonarSensor(trigPin3, echoPin3);
RightSensor = distance;
avg=(LeftSensor+FrontSensor+RightSensor)/3;
if(count>15){
Test_Speech(avg);
count=0;}
if(avg>=200){
  sound=0;}
  else if(avg<200 && avg>=150){
    sound=100;}
    else if(avg<150 && avg>=100){
      sound=400;}
      else if(avg<100){
        sound=700;}
 tone(buzzer,sound);       
Serial.print(LeftSensor);
Serial.print(" - ");
Serial.println(FrontSensor);
Serial.print(" - ");
Serial.println(text);
Serial.println(s);
Serial.println(g);
delay(10);
count++;
}
 
//================================================================
//void loop(){

    
//    delay(1000);          // delay a second
//}  
//================================================================


void Test_Speech(int dist) {
 text2speech.setPitch(1); //higher values = lower voice pitch
// String mystring= String(dist);
 strcpy(text, "There is an obstacle within");
// String faltu =  String( text + mystring);
 strcpy(g, "Centimeter");
 s = int2str(dist);
 text2speech.say(text);
 text2speech.say(s);
 text2speech.say(g);
// delay(500);
// text2speech.setPitch(1); //lower values = higher voice pitch
// 
// text2speech.say(text);
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
 
}

char* int2str( register int i ) {
  register unsigned char L = 1;
  register char c;
  register boolean m = false;
  register char b;  // lower-byte of i
  // negative
  if ( i < 0 ) {
    _int2str[ 0 ] = '-';
    i = -i;
  }
  else L = 0;
  // ten-thousands
  if( i > 9999 ) {
    c = i < 20000 ? 1
      : i < 30000 ? 2
      : 3;
    _int2str[ L++ ] = c + 48;
    i -= c * 10000;
    m = true;
  }
  // thousands
  if( i > 999 ) {
    c = i < 5000
      ? ( i < 3000
          ? ( i < 2000 ? 1 : 2 )
          :   i < 4000 ? 3 : 4
        )
      : i < 8000
        ? ( i < 6000
            ? 5
            : i < 7000 ? 6 : 7
          )
        : i < 9000 ? 8 : 9;
    _int2str[ L++ ] = c + 48;
    i -= c * 1000;
    m = true;
  }
  else if( m ) _int2str[ L++ ] = '0';
  // hundreds
  if( i > 99 ) {
    c = i < 500
      ? ( i < 300
          ? ( i < 200 ? 1 : 2 )
          :   i < 400 ? 3 : 4
        )
      : i < 800
        ? ( i < 600
            ? 5
            : i < 700 ? 6 : 7
          )
        : i < 900 ? 8 : 9;
    _int2str[ L++ ] = c + 48;
    i -= c * 100;
    m = true;
  }
  else if( m ) _int2str[ L++ ] = '0';
  // decades (check on lower byte to optimize code)
  b = char( i );
  if( b > 9 ) {
    c = b < 50
      ? ( b < 30
          ? ( b < 20 ? 1 : 2 )
          :   b < 40 ? 3 : 4
        )
      : b < 80
        ? ( i < 60
            ? 5
            : i < 70 ? 6 : 7
          )
        : i < 90 ? 8 : 9;
    _int2str[ L++ ] = c + 48;
    b -= c * 10;
    m = true;
  }
  else if( m ) _int2str[ L++ ] = '0';
  // last digit
  _int2str[ L++ ] = b + 48;
  // null terminator
  _int2str[ L ] = 0;  
  return _int2str;
}
