//Awaaz Dahal
//My name is Ryland Smith and this is my edit for assignment 14
//Single LED
const int BUTTON_PIN = 11;  
const int LED_PIN =  12;
int buttonState = 0;   
void setup()
{ 
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop()
{
  buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == LOW){        // If button is pressed
    digitalWrite(LED_PIN, HIGH); // turn on LED
	delay(1000);//pause
  	digitalWrite(LED_PIN, LOW);  //turn off led
    delay(1000);
  }
  else                           
    digitalWrite(LED_PIN, LOW);  // turn off LED   
  } 
