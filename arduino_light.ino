// This will work with a relay with NO and NC pins
// Saying the relay is in state "NO" means the NO Pin is connected
// Saying it is in "NC" means the NC Pin is connected

const int RELAY_pin = 7;
const int AC_pin = 5; // AC_pin detector
const int sevlev_button_pin = 8;
const int LED_indicator_pin = 13;

boolean sevlev_action_pending = 0;

void setup(){
  Serial.begin(9600);
  pinMode(RELAY_pin, OUTPUT);
  digitalWrite(RELAY_pin, LOW);
  pinMode(AC_pin, INPUT);
  pinMode(sevlev_button_pin, INPUT);
  digitalWrite(sevlev_button_pin, HIGH);
  pinMode(LED_indicator_pin, OUTPUT);

}
void loop(){
  read_serial_cmd();
  check_sevlev_press();
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
      Serial.println(sevlev_action_pending ? '7' : '0');
      sevlev_action_pending = 0;
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

void check_sevlev_press() {
  digitalWrite(LED_indicator_pin, digitalRead(sevlev_button_pin));

  // Check whether the button pin is grounded for two samples 200ms apart.
  // This should catch button presses longer than 200ms.
  if (!digitalRead(sevlev_button_pin)) {
    delay(200);
    if (!digitalRead(sevlev_button_pin))
      sevlev_action_pending = 1;
  }
}
