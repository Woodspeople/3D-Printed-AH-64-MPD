const uint8_t mapSize = 32;
const uint8_t pinMap[mapSize] = {
  53,52,51,50, 49,48,47,46,
  45,44,43,42, 41,40,39,38,
  37,36,35,34, 33,32,31,30,
  29,28,27,26, 25,24,23,22//end

};

uint8_t inputBuffer[8];


void setup() 
{ 
  Serial.begin(960000);
  for (uint8_t i = 0; i < 32; i++)
  {
    pinMode(pinMap[i],INPUT_PULLUP); 
  }
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
}

void loop() 
{
  // Read button values //
  uint8_t i = 0;
  for (uint8_t j = 4; j < 8; j++)
  {
    for (uint8_t k = 0; k < 8; k++)
    {
      inputBuffer[j] = inputBuffer[j] << 1;
      if (!digitalRead(pinMap[i]))
      {
        inputBuffer[j] = inputBuffer[j] | 1;
      }
      i++; 
    }
  }
  
  // Read toggle switch and encode? //
  if (!digitalRead(2))
  {
    inputBuffer[3] = 1;
  }
  else if (!digitalRead(3))
  {
    inputBuffer[3] = 2;
  }
  else
  {
    inputBuffer[3] = 0;
  }
  // Read potentiometers //

  inputBuffer[0] = analogRead(A0) >> 2;
  inputBuffer[1] = analogRead(A1) >> 2;

  
  //Serial.write(Serial.available());
  if (Serial.available())
    {
      Serial.read();
      
      for (uint8_t i = 0; i < 8; i++)
      {
        Serial.write(inputBuffer[i]);
        //Serial.write(0xBB);
      }
    }
}
