int pin2 = 2; //these are all pushbuttons
int pin3 = 3;
int pin4 = 4;
int pin5 = 5;
int pin7 = 7;

int initialized = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin2, INPUT); //declare all inputs
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);
  pinMode(pin7, INPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pin7) == HIGH && initialized == 0){ //wthhen the startup button has been pressed, enable the if loop for the serial 
    Serial.println("I");
    initialized = 1;
  }
  
  if(initialized == 1){ //these if loops are for if the buttons are pressed, submit the right byte to the arduino with the shield
    if(digitalRead(pin2) == HIGH){
      Serial.println("u");
    }
    
    if(digitalRead(pin3) == HIGH){
      Serial.println("d");
    }
    
    if(digitalRead(pin4) == HIGH){
      Serial.println("U");
    }
    
    if(digitalRead(pin5) == HIGH){
      Serial.println("D");  
    }
  }
  
}
