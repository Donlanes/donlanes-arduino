//This will work with a relay with NO and NC pins
//Saying the relay is in state "NO" means the NO Pin is connected
//Saying it is in "NC" means the NC Pin is connected

#define RELAY 7
#define AC 5

char incomingByte = 0;
int relay = LOW;  //usually the normally closed pin is connected
//to the relay output

void setup(){
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  pinMode(AC, INPUT);
}

int ac(){
  return !(digitalRead(AC));
}

void switchRelay(){
  if(relay == LOW){
     //shouldn't this be digitalWrite?
    //gutenesque
    digitalWrite(RELAY, HIGH);
   
    relay = HIGH;
  } else {
    //same here
    digitalWrite(RELAY, LOW);
    relay = LOW;
  }
}

void turnOn(){
  if(ac() == LOW){
    switchRelay();
    delay(50);
  }
}

void turnOff(){
  if(ac() == HIGH){
    switchRelay();
    delay(50);
  }
}

void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    if(incomingByte == '0'){
      turnOff();
    }
    if(incomingByte == '1'){
      turnOn();
    }
    if(incomingByte == 'q'){
      if(ac() == HIGH) Serial.println("1");
      if(ac() == LOW) Serial.println("0");
    }
  }
}
