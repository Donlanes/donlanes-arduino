// This will work with a relay with NO and NC pins
// Saying the relay is in state "NO" means the NO Pin is connected
// Saying it is in "NC" means the NC Pin is connected

const int RELAY_pin = 7;
const int AC_pin = 5; // AC_pin detector
const int s11_pin = 8;

boolean s11_toggle = 0;

void setup(){
  Serial.begin(9600);
  pinMode(RELAY_pin, OUTPUT);
  digitalWrite(RELAY_pin, LOW);
  pinMode(AC_pin, INPUT);
  pinMode(s11_pin, INPUT);
  digitalWrite(s11_pin, HIGH);
  pinMode(13, OUTPUT);
  
}
void loop(){
  read_serial_cmd();
  seven_eleven();
}

void read_serial_cmd() {
  if(Serial.available() > 0){
    char incomingByte = Serial.read();

    if(incomingByte == '0') { // projector on
      set_projector(true);
    }
    if(incomingByte == '1') { // projector off 
      set_projector(false);
    }
    if(incomingByte == 'q') { // query AC_pin
      Serial.println(ac_state() ? "1" : "0");
    }
    if(incomingByte == '7'){
      Serial.println(s11_toggle ? '7' : '0');
      s11_toggle = 0;
    }
  }
}

int ac_state() {
  return !(digitalRead(AC_pin));
}

void set_projector(bool desired_state) {
  if (ac_state() != desired_state)
    digitalWrite(RELAY_pin, !digitalRead(RELAY_pin));
  delay(100);
}

void seven_eleven() {
  digitalWrite(13, digitalRead(s11_pin));

  if (!digitalRead(s11_pin)) {
    delay(200);
    if (!digitalRead(s11_pin))
      s11_toggle = 1;
  }
}
