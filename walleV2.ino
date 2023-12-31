
#include <Servo.h>
#include "inc.h" 


// Used to hold data that comes from the serial port
String readString; 

// holds serial port incoming messages
String inputString = "";

// turn light on
bool lighton = false;

bool bPrintBytes = false;

// Message from the serial port is ready
bool stringComplete = false; 

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 30000;  //the value is a number of milliseconds

Servo myServo4;
Servo myServo5;
Servo myServo6;
Servo myServo7;
Servo myServo8;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:
  startMillis = millis();  //initial start time
  myServo4.attach(4);
  myServo5.attach(5);
  myServo6.attach(6);
  myServo7.attach(7);
  myServo8.attach(8);                
  Serial.begin(19200);
  Serial.println(SECRET_SSID);
  myServo5.write(180);// low neck
  //myServo4.write(90);// low neck
}

void loop() {
  // put your main code here, to run repeatedly:
  readstring();
  
  if(lighton == true)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }else if(lighton == false)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  currentMillis = millis();
  
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    Serial.println(SECRET_SSID);
    startMillis = millis();
  }

   if(stringComplete)
   {
      handleInput(inputString);
   }
}



void serial_flush(void) {
  while (Serial.available()) Serial.read();
}

void runPro()
{
  for(int i = 0;i < 10;i++)
  {
    setServo(180);
    delay(1000);
    setServo(1);
    delay(1000);
  }
  
}

void setServo(int newpos)
{
  Serial.print("Setting position to ");
  Serial.println(newpos);
  myServo6.write( newpos);
  delay(20);
}

void setServo(int newpos, int serv)
{
  if(serv == 4)
  {
    Serial.print("Setting 4 position to ");
    Serial.println(newpos);
    myServo4.write(newpos);
    delay(20);
  }else if(serv == 5)
  {
    Serial.print("Setting 5 position to ");
    Serial.println(newpos);
    myServo5.write(newpos);
    delay(20);
  }else if(serv == 6)
  {
    Serial.print("Setting 6 position to ");
    Serial.println(newpos);
    myServo6.write(newpos);
    delay(20);
  }else if(serv == 7)
  {
    Serial.print("Setting 7 position to ");
    Serial.println(newpos);
    myServo7.write( newpos);
    delay(20);
  }else if(serv == 8)
  {
    Serial.print("Setting 8 position to ");
    Serial.println(newpos);
    myServo8.write( newpos);
    delay(20);
  }
  
}

void readstring()
{
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();
      // add it to the inputString:
      inputString += inChar;
        // if the incoming character is a newline, set a flag so the main loop can
        // do something about it:
        if (inChar == '\n')
        {
          stringComplete = true;
          serial_flush();
          return;
        }
    }
}


bool containsStr(String inStr, String substr)
{
  int pos = inStr.indexOf(substr);

  if (pos >= 0) {
    return true;
  } else {
    return false;
  }
  delay(100);
}

int extractNumber(String inStr)
{
  String numStr = "";

  // Extract numbers from the string
  for (int i = 0; i < inStr.length(); i++) {
    if (isdigit(inStr.charAt(i))) {
      numStr += inStr.charAt(i);
    }
  }

  // Convert the extracted string of numbers to an integer
  int num = atoi(numStr.c_str());
  return num;
}

void handleInput(String iput)
{
  
  Serial.println(iput);
  if(bPrintBytes)
  {
    //printBytes(iput);
  }
  
  if(iput == "on\n" || iput == "on")
  {
    lighton = true;
    //break;
  }else if(iput == "off\n" || iput == "off")
  {
    lighton = false;
   // break;
  }else if(iput == "byteson" || iput == "byteson\n")
  {
    bPrintBytes = true;
    Serial.println("I will print the bytes of received messages.");
    //break;
  }else if(iput == "bytesoff" || iput == "bytesoff\n")
  {
    bPrintBytes = false;
    Serial.println("I will not print the bytes of received messages.");
    //break;
  }else if(containsStr(iput,"four"))
  {

    int newVal = extractNumber(iput);

    setServo(newVal,4);
  }else if(containsStr(iput,"five"))
  {

    int newVal = extractNumber(iput);

    setServo(newVal,5);
  }else if(containsStr(iput,"six"))
  {

    int newVal = extractNumber(iput);

    setServo(newVal,6);
  }else if(containsStr(iput,"seven"))
  {

    int newVal = extractNumber(iput);

    setServo(newVal,7);
  }else if(containsStr(iput,"eight"))
  {

    int newVal = extractNumber(iput);

    setServo(newVal,8);
  }else if(containsStr(iput,"run"))
  {

   runPro();
   
  }else if(containsStr(iput,"test"))
  {

   int newVal = extractNumber(iput);
   test(newVal);
   
  }else if(iput == "pos\n")
  {
    Serial.println(myServo6.read());
  }

  stringComplete = false;
  inputString = "";

}

void test(int serv)
{
  for(int i = 0;i<181;i++)
  {
    setServo(i,serv);
    //delay(50);
  }
}

//void printBytes(String bStr){
  // int strlen = bStr.length();
  // for(int i = 0;i< strlen;i++)
  // {
  //   //Serial.print(byte(bStr[i]),HEX ;
  //   
  // //