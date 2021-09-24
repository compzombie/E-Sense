//TODO:
//calculator is not displaying second screen

#include <math.h>

//general
const int byteSize = 8; //def 8
const long debounceDelay = 50;
int outPins[8] = {
  5, 6, 7, 8, 9, 10, 11, 12};
int inPins[2] = {
  3, 4};
float toProcess = 0;

//calculator
int firstNum = 0;
int secondNum = 0;
float answer = 0;


void setup ()
{
  // Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop()
{
  AllOff();
  toProcess = 0;
  toProcess = Input();
  //Serial.println(toProcess);
  delay(500);
  AllOff();


  switch ((int)(toProcess + 0.5))
  {
    //add
  case 3:
    DisplaySelected(outPins, byteSize, 250);
    AllOff();
    delay (250);
    DisplaySelected(outPins, byteSize, 250);
    AllOff();

    firstNum = Input();
    AllOff();
    secondNum = Input();
    AllOff();

    answer = firstNum + secondNum;
    //        Serial.println(firstNum);
    //        Serial.println(secondNum);
    //        Serial.println(answer);
    //        Serial.println("*********************");

    CalcDisplay(answer);
    break;

    //flashlight
  case 10:
    AllOn();
    delay(5000);
    break;

    //subtract
  case 12:
    break;


    //divide 
  case 48:
    break;

    //multiply
  case 192:
    break;

    //blink test
  case 255:
    for (int i = 0; i < 3; i++)
    {
      AllOn();
      delay(250);
      AllOff();
      delay(250); 
    }        
    break;

  }

}

void AllOn()
{
  for (int i = 0; i < sizeof(outPins); i++)
  {
    digitalWrite(outPins[i], HIGH);
  } 
}
void AllOff()
{
  for (int i = 0; i < sizeof(outPins); i++)
  {
    digitalWrite(outPins[i], LOW);
  }
}

void DisplaySelected(int selectedLEDs[], int selLEDSize, int displayTime)
{
  //Serial.println(sizeof(selectedLEDs));
  for (int i = 0; i < selLEDSize; i++)
  {
    digitalWrite(selectedLEDs[i], HIGH);
  }

  delay(displayTime);
}

float Input()
{
  float command = 0;
  int in0 = 1;
  int in1 = 1;
  int in0Last = 1;
  int in1Last = 1;
  int releaseCount = 0;

  while (releaseCount < byteSize)
  {
    delay(100); //critcally important that this delay is included, necessary for software-side debouncing
    //4 is on 3 is off
    in0 = digitalRead(inPins[0]);
    in1 = digitalRead(inPins[1]);

    if (in0 == 1 && in0Last == 0)
    {
      digitalWrite(outPins[releaseCount], HIGH);
      delay(10);
      digitalWrite(outPins[releaseCount], LOW);
      releaseCount++;
    }

    if (in1 == 1 && in1Last == 0)
    {
      digitalWrite(outPins[releaseCount], HIGH);
      command = command + pow(2, releaseCount);
      releaseCount++;
    }


    in0Last = in0;
    in1Last = in1;

  }

  return command;
}

void CalcDisplay(int calcAnswer) //if there is a decimal attached to a number we can still use this function in essentially the same way
{
  //keep calling Display() from itself until the output is less then 0
  int numOfScreens = 0;
  int displaySet[byteSize] = {
    0, 0, 0, 0, 0, 0, 0, 0  };

  numOfScreens = ceil(answer / (pow(2, byteSize)));

  for (int i = 0; i < numOfScreens; i++)
  {
    //count backwards to light LEDs in correct order (right to left)
    if ((answer - 128) >= 0)
    {
      answer = answer - 128;
      displaySet[7] = 12;
    }

    if ((answer - 64) >= 0)
    {
      answer = answer - 64;
      displaySet[6] = 11;
    }

    if ((answer - 32) >= 0)
    {
      answer = answer - 32;
      displaySet[5] = 10;
    }

    if ((answer - 16) >= 0)
    {
      answer = answer - 16;
      displaySet[4] = 9;
    }

    if ((answer - 8) >= 0)
    {
      answer = answer - 8;
      displaySet[3] = 8;
    }

    if ((answer - 4) >= 0)
    {
      answer = answer - 4;
      displaySet[2] = 7;
    }

    if ((answer - 2) >= 0)
    {
      answer = answer - 2;
      displaySet[1] = 6;
    }

    if ((answer - 1) >= 0)
    {
      answer = answer - 1;
      displaySet[0] = 5;
    }

    //   for (int i = 0; i < 8; i++)
    //   {
    //     Serial.println(displaySet[i]); 
    //   }

    DisplaySelected(displaySet, byteSize, 1000);
    AllOff();

    //   if (i < numOfScreens)
    //   {
    //     //flash once for next screen
    //     delay(250);
    //     DisplaySelected(outPins, byteSize, 250);
    //     AllOff();
    //   }
  }

}


