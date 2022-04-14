/*

*/
#include <Arduino.h>

#include <IRremote.hpp>

// analog sensor values
int heUpSensor = 0;
int heDownSensor = 0;
uint8_t irrecv;

// variables
int dir = 3;
int UP = 0;
int DOWN = 1;
int TRANSIT = 2;
int STOP = 3;

bool ACTIVE=true;
bool INACTIVE=false;

#define IR_RECEIVE_PIN      8
#define IR_SEND_PIN         6
#define DELAY_AFTER_SEND 2000
#define IRUP  0x95
#define IRDOWN 0x9A
#define IRSTOP 0x9E
#define IRONOFF 0xA8
#define DECODE_NEC          // Includes Apple and Onkyo
#define DECODE_DISTANCE     // in case NEC is not received correctly

// digital outputs
int relay_1 = 4;
int relay_2 = 7;
int upSensorPin =2;
int downSensorPin =3;

volatile int upSensor,downSensor =0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);  

  pinMode(upSensorPin, INPUT_PULLUP);
  pinMode(downSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(upSensorPin), isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(downSensorPin), isr, CHANGE);
  


#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) || defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.print(F("at pin "));
    Serial.println(IR_RECEIVE_PIN);

    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK); // Specify send pin and enable feedback LED at default feedback LED pin
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
}


void loop() {
  if (IrReceiver.decode()) {  // Grab an IR code
        // Check if the buffer overflowed
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            Serial.println(F(">>>>>>>> Overflow detected"));
        } else {
                  //IrReceiver.printIRResultRawFormatted(&Serial, true);  // Output the results in RAW format
                  if(IrReceiver.decodedIRData.command!=0x0)
                  irrecv = IrReceiver.decodedIRData.command;

                switch (irrecv) {
                  case IRUP:
                    executeUpCommands();
                    break;
                  case IRDOWN:
                    executeDownCommands();
                    break;
                  case IRSTOP:
                      stopMotor();
                    break;
                  case IRONOFF: //onoff
                    executeOnOffCommands();
                    break;
                  default:
                    sendRawCode(IrReceiver.decodedIRData.decodedRawData);
                    break;
                }

               IrReceiver.resume();                            // Prepare for the next value
              }
  }
}

void isr() {
  // set sensor value
  upSensor=digitalRead(upSensorPin);
  downSensor=digitalRead(downSensorPin);

 if(getDir()!=STOP) {
        if(getDir()==UP && !upSensor) stopMotor();
        if(getDir()==DOWN && !downSensor) stopMotor(); 
  }
}


/**
 * screen is up : 0
 * screen is down :1
 * screen is travelling: 2
 **/
int checkHESensorsScreenPos() {
  if (upSensor == INACTIVE) return UP;
  if(downSensor == INACTIVE) return DOWN;
  return TRANSIT;
}

void moveUp() {
  digitalWrite(relay_1, LOW);
  digitalWrite(relay_2, HIGH);
  dir = UP;
  Serial.println("Going UP");
}

void moveDown() {
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, LOW);
  dir = DOWN;
  Serial.println("Going DOWN");
}

void stopMotor() {
  digitalWrite(relay_1, LOW);
  digitalWrite(relay_2, LOW);
  dir = STOP;
  Serial.println("STOP!");
}

int getDir(){
  return dir;
}

void sendRawCode(uint32_t code) {
    Serial.print(F("Sending NECRaw "));
    Serial.println(code,HEX);
    Serial.flush();
    
    IrSender.sendNECRaw(code, 0);
       // wait for the receiver state machine to detect the end of a protocol
    //delay((RECORD_GAP_MICROS / 1000) + 5);
}

void sendNecCode(uint16_t address, uint8_t command ) {
    Serial.print(F("Send NEC Code "));
    Serial.print(address,HEX);
    Serial.print(F(" Command "));
    Serial.println(command,HEX);
    //  Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)
    IrSender.sendNEC(address, command, 0);
    //delay((RECORD_GAP_MICROS / 1000) + 5);
}

void executeUpCommands() {
  int screenPos = checkHESensorsScreenPos();
  if( screenPos == DOWN) 
    moveUp();
  if(screenPos==TRANSIT && getDir() != UP) {
    stopMotor();
    moveUp();
  }
}

void executeDownCommands() {
  int screenPos = checkHESensorsScreenPos();
  if( screenPos == UP)
    moveDown();
  if(screenPos==TRANSIT && getDir() != DOWN) {
    stopMotor();
    moveDown();
  }
}

void executeOnOffCommands() {
  int screenPos = checkHESensorsScreenPos();
  if( screenPos == UP) {
    moveDown();
    Serial.println("Turning ON");
  } else if(screenPos == DOWN || screenPos == TRANSIT) {
    moveUp();
    Serial.println("Turning OFF");
    sendNecCode(0xDE21,0xA8);//onoff proj press 2 times
  }
  delay(1000);
  sendNecCode(0xDE21, 0xA8);//onoff proj
  sendRawCode(0xA659FF00);//onoff kiii
  sendNecCode(0xFD02, 0x57);//onoff soundbar
}
