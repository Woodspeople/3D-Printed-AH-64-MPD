uint8_t switchState = 0;

const uint8_t pinMap[32] =
{
   0, 1, 2, 3,
   4, 5, 6, 7,
   8, 9,10,11,
  12,24,25,26,
  27,28,29,30,
  31,32,13,14,
  15,16,17,18,
  19,20,21,22
};

void setup() {
  Joystick.begin();
  Joystick.useManualSend(true);

  for (uint8_t i = 0; i < 33; i++)
  {
    pinMode(i,INPUT_PULLUP); 
  }

  pinMode(33,INPUT_PULLUP);
  pinMode(34,INPUT_PULLUP);
}


void loop() {
  for (uint8_t i = 0; i < 32; i++)
  {
    Joystick.button(i + 1, !digitalRead(pinMap[i])); 
  }
  
  if (!digitalRead(33)){
    Joystick.hat(0);
  } 
  else if (!digitalRead(34)){
    Joystick.hat(90);
  }
  else{
    Joystick.hat(45);
  }

  Joystick.X(analogRead(35));
  Joystick.Y(analogRead(36));
  
  Joystick.send_now();
}
