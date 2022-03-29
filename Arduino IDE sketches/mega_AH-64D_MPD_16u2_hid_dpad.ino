#include <HID-Project.h>
#include <HID-Settings.h>

union DATA_BUFFER_UNION
{
  uint64_t data = 0; 
  struct DATA_BUFFER_STRUCT
  {
    uint32_t buttonsState : 32;
    uint8_t switchState : 8;
    uint8_t unused : 8;
    uint8_t analogIn0 : 8;
    uint8_t analogIn1 : 8;
  }data_struct;
}dataUnion;


bool dataReady = false;

void setup() {
  Serial.begin(9600);
  Serial1.begin(960000);
  Gamepad.begin();
  delay(5000);
  pinMode(3,INPUT_PULLUP); //remove this
}

void loop() 
{
  //Serial.write("sending 0xA");
  Serial1.write("a");
  delay(5);
  //Serial.println(Serial1.available());
  if (Serial1.available() > 7)
  {
    while (Serial1.available() > 0)
    {
      dataUnion.data <<= 8;
      dataUnion.data |= Serial1.read();
    }
    dataReady = true;

   //print serial monitor.
  /*Serial.print("data received. > ");
  uint64_t pipe = dataUnion.data;
  uint32_t *p = (uint32_t *)&pipe;
  Serial.print(p[1],BIN);
  Serial.print(" | ");
  Serial.println(p[0],BIN); */
   //back to the main code.
  
  } 
  if (dataReady)
  {
    Gamepad.buttons(dataUnion.data_struct.buttonsState);
    Gamepad.xAxis(dataUnion.data_struct.analogIn0);
    Gamepad.yAxis(dataUnion.data_struct.analogIn1);
    Gamepad.dPad1(dataUnion.data_struct.switchState + 1);
    Gamepad.write();
    dataReady = false;
  }
  delay(15);
}
