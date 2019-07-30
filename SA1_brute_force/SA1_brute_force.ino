//https://github.com/jorticus/Arduino-Serial9b
//https://github.com/FrankBoesing/FastCRC
//MEGA2560 & max13487

#include <Serial9b_private.h>
#include <Serial9b.h>
#include <FastCRC.h>

FastCRC16 CRC16;

byte sti = 0;

#define RCV_BUFFER_SIZE 64
uint8_t rcv[RCV_BUFFER_SIZE];
byte ind = 0;

uint8_t sendline[64] = { 0x25, 0x24, 0x81, 0x28, 0x30, 0x80, 0xFF, 0x90, 0x92, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xB1, 0x95, 0x00 };
uint8_t sendstr[64] = { 0x7A, 0x03, 0x00, 0x00, 0x00, 0x28, 0x55, 0x30, 0x30, 0x35, 0x2E, 0x34, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x21, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xF6, 0x11};
uint8_t spb[20];

#define SND_BUFFER_SIZE 64
uint8_t sendBufferIndex = 1;
uint8_t sendBuffer[SND_BUFFER_SIZE] = { 0x25 };
byte Sequence = 1;
byte lineCRC = 0;

void sndbuf_write(uint8_t data) {
  sendBuffer[sendBufferIndex++] = data;
}

void sndbuf_writeC(uint8_t data) {
  sendBuffer[sendBufferIndex++] = data;
  lineCRC += data;
}

void sndbuf_writeSeq() {
  sendBuffer[sendBufferIndex++] = 0x20 + ((Sequence++ & 0x07) <<1);
}

void sndbuf_crc() {
  uint16_t crc_t = CRC16.x25(sendBuffer, sendBufferIndex);
  sendBuffer[sendBufferIndex++] = crc_t;
  sendBuffer[sendBufferIndex++] = (crc_t>>8);
}

void sndbuf_clr() {
  sendBufferIndex = 0;
  lineCRC = 0;
  for(int i = 0; i < SND_BUFFER_SIZE; i++) {
    sendBuffer[i] = 0;
  }
  sendBuffer[sendBufferIndex++] = 0x25;
}

byte seq = 4;

unsigned long currentTime;
unsigned long loopTime;
bool s = true;

int cnt = 0;
byte cnt2 = 253;


void notSend() {}
void sendAnswer_0();
void sendAnswer_1();
void sendAnswer_1_bf();
void sendAnswer_2();
void sendAnswer_3();
void sendAnswer_4();
void sendAnswer_5();
void sendAnswer_6();
void sendAnswer_7();
void sendAnswer_8();
void sendAnswer_9();
void sendAnswer_A();
void sendAnswer_B();
void sendAnswer_C();

void (*sendAnswerArray[14])()= { 
  notSend, 
  sendAnswer_0, 
  sendAnswer_1, 
  sendAnswer_2, // user simbol 0
  sendAnswer_3, // user simbol 1
  sendAnswer_4, // user simbol 2
  sendAnswer_5, // user simbol 3
  sendAnswer_6, // user simbol 4
  sendAnswer_7, // user simbol 5
  sendAnswer_8, // user simbol 6
  sendAnswer_9, // user simbol 7
  sendAnswer_A, // SELECT CHARACTER SET???
  sendAnswer_B, // text on line 1
  sendAnswer_C // text on line 2
};

#define ELEMENTS sizeof(sendAnswerArray) / sizeof(sendAnswerArray[0])

void clrBuff() {
  ind = 0;
  for(byte i = 0; i < RCV_BUFFER_SIZE; i++) {
    rcv[i]=0;
  }
}

void sendMark(uint16_t data) {
  Serial9b1.write9b(data);
Serial.print(data, HEX);
Serial.print(" ");
  delayMicroseconds(191);
  Serial9b1.write9b(data);
Serial.print(data, HEX);
Serial.print(" ");
}

void sendData(uint8_t data) {
  Serial9b1.write(data);
  Serial.print(data, HEX);
  Serial.print(" ");
  delayMicroseconds(100);
}

void sendAnswer_0() {
  sti++;
  Serial.println("SA0");
  Serial.print(">> ");

  delayMicroseconds(200);

  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_write(0x83);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" "); 
  Serial.println("");
}

void sendAnswer_1() {
  sti++;
  Serial.println("SA1");
  Serial.print(">> ");
  delayMicroseconds(200);
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x01);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_1_alt() {
  sti++;
  Serial.println("SA1");
  Serial.print(">> ");
  delayMicroseconds(200);
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x03);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}
  
void sendAnswer_2() {
  sti++;
  Serial.println("SA2");
  Serial.print(">> ");
  delayMicroseconds(200);

  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_write(0x21);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  delayMicroseconds(260);
  
  sendMark(0x1CA);

  delayMicroseconds(2917);

  // user simbol 0
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x40);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x04);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  delayMicroseconds(200);
  Serial.println("");
}

void sendAnswer_3() {
  sti++;
  Serial.println("SA3");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);

  // user simbol 1
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x40);
  sndbuf_write(0x01);
  sndbuf_write(0x06);
  sndbuf_write(0x09);
  sndbuf_write(0x1C);
  sndbuf_write(0x08);
  sndbuf_write(0x1C);
  sndbuf_write(0x09);
  sndbuf_write(0x06);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_4() {
  sti++;
  Serial.println("SA4");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);

  // user simbol 2
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x40);
  sndbuf_write(0x02);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x04);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_5() {
  sti++;
  Serial.println("SA5");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);
  
  // user simbol 3
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x40);
  sndbuf_write(0x03);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x04);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_6() {
  sti++;
  Serial.println("SA6");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);
  
  // user simbol 4
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x40);
  sndbuf_write(0x04);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x04);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_7() {
  sti++;
  Serial.println("SA7");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);
  
  // user simbol 5
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x40);
  sndbuf_write(0x05);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x04);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_8() {
  sti++;
  Serial.println("SA8");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);

  // user simbol 6
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x40);
  sndbuf_write(0x06);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x04);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_9() {
  sti++;
  Serial.println("SA9");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);
  
  // user simbol 7
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x40);
  sndbuf_write(0x07);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x04);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_A() {
  sti++;
  Serial.println("SAA");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);

  // SELECT CHARACTER SET???
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x41);
  sndbuf_write(0x0A);
  sndbuf_write(0x00);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_B() {
  sti++;
  Serial.println("SAB");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);

  //  text on line 1
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x81);
  sndbuf_write(0x28);
  sndbuf_writeC(0x91);
  sndbuf_writeC(0xE2);
  sndbuf_writeC(0xE0);
  sndbuf_writeC(0xAE);
  sndbuf_writeC(0xAA);
  sndbuf_writeC(0xA0);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x31);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_write(lineCRC);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_C() {
  sti--;
  Serial.println("SAC");
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3078);
  
  //  text on line 2
  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);
  
  sndbuf_clr();
  sndbuf_writeSeq();
  sndbuf_write(0x82);
  sndbuf_write(0x28);
  sndbuf_writeC(0x91);
  sndbuf_writeC(0xE2);
  sndbuf_writeC(0xE0);
  sndbuf_writeC(0xAE);
  sndbuf_writeC(0xAA);
  sndbuf_writeC(0xA0);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x32);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_writeC(0x20);
  sndbuf_write(lineCRC);
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_Y() {
  Serial.print(">> ");
  
  uint16_t crc_t = CRC16.x25(sendstr, 47);
  sendstr[47] = crc_t;
  sendstr[48] = (crc_t>>8);
  
  Serial9b1.write9b(0x17A);
Serial.print(0x17A, HEX);
Serial.print(" ");
  delayMicroseconds(200);

  for( int i = 1; i < 49 ; i++) {
    sendData( sendstr[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  Serial.println("");
}

void sendAnswer_X() {
  //sti++;
  Serial.print(">> ");
  delayMicroseconds(1500);
  sendMark(0x1CA);

  delayMicroseconds(3000);
  
  byte sum = 0;
  for( int i = 0; i < 20 ; i++) {
    sum += sendline[4 +i];
  }
  sendline[1] = 0x20 + ((seq & 0x07) <<1);
  //Serial.println((byte)sendline[1], HEX);
  sendline[24] = sum;
  uint16_t crc_t = CRC16.x25(sendline, 25);
  sendline[25] = crc_t;
  sendline[26] = (crc_t>>8);

  Serial9b1.write9b(0x125);
Serial.print(0x125, HEX);
Serial.print(" ");
  delayMicroseconds(200);
 
  for( int i = 1; i < 27 ; i++) {
    sendData( sendline[i]);
  }

  Serial9b1.write9b(0x17E);
Serial.print(0x17E, HEX);
Serial.print(" ");
  seq++;
  Serial.println("");
}

void send_eop() {
      Serial.print(">> ");
      delayMicroseconds(300);
      sendMark(0x180);
      delayMicroseconds(1600);
      sendMark(0x180);
      delayMicroseconds(1600);
      sendMark(0x1A5);
      Serial.println("");
}

void await_available() {
  while(true){
    if(!Serial9b1.available()) {
      delayMicroseconds(1500);
    }
    if(!Serial9b1.available()) {
      send_eop();
    }
    if(Serial9b1.available()) {
      break;
    }
  }
}

void clear_available_buffer() {
  Serial.print("<< ");
  while(Serial9b1.available ()) {
    Serial.print((byte)Serial9b1.read (), HEX);
    Serial.print(" ");
  }
  Serial.println("");
}

void sendAnswer_1_bf_data(int offset, int val) {
  Serial.println("SA1");
  Serial.print(">> ");
  delayMicroseconds(200);
  Serial9b1.write9b(0x125);
  Serial.print(0x125, HEX);
  Serial.print(" ");
  delayMicroseconds(200);

  sndbuf_clr();

  while(offset>0) {
    sndbuf_write(0x00);
    offset--;
  }
  sndbuf_write((byte)val);
  
  sndbuf_crc();
  for( int i = 1; i < sendBufferIndex ; i++) {
    sendData( sendBuffer[i]);
  }

  Serial9b1.write9b(0x17E);
  Serial.print(0x17E, HEX);
  Serial.print(" ");
  Serial.println("");
}

bool validate_SA1_response() {
  Serial.print("<< ");
  while(Serial9b1.available ()) {
    uint16_t d = Serial9b1.read ();
    Serial.print(d, HEX);
    Serial.print(" ");
    rcv[ind++] = (byte)d;
  }
  Serial.println("");

  bool no_error = true;

  if(ind == 5 && rcv[0] == 0x25 && rcv[1] == 0x21 && rcv[2] == 0x47 && rcv[3] == 0x62 && rcv[4] == 0x7E) {
    no_error = false;
  } 

  if(ind == 1 && rcv[0] == 0x5A) {
    no_error = false;
  }
  
  clrBuff();

  return no_error;
}

void sendAnswer_1_bf() {

  bool success = false;
  int offset = 0;
  int value = 0;

  while(!success && offset < 10) {
    while(!success && value<256) {
      sendAnswer_1_bf_data(offset, value);
      delayMicroseconds(1500);
      send_eop();
      
      await_available();
  
      delayMicroseconds(1500); // We need to wait a bit for all data to come in
  
      success = validate_SA1_response();
  
      value++;
    }
    value = 0;
    offset++;
  }

  if(success) {
    Serial.println("SUCCESS!");
  } else {
    Serial.println("FAILURE");
  }

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial9b1.begin(187500);

  Serial.println("--- START ---");

  await_available();
  clear_available_buffer();

  sendAnswer_0();
  delayMicroseconds(1500);
  send_eop();
  
  await_available();
  clear_available_buffer();

  sendAnswer_1_bf();

  sti = 3;
  
}


void loop() {
  currentTime = micros();
  if( s ) {
    Serial.print(">> ");
    delayMicroseconds(300);
    sendMark(0x180);
    delayMicroseconds(1600);
    sendMark(0x180);
    delayMicroseconds(1600);
    sendMark(0x1A5);
    currentTime = micros();
    loopTime = currentTime;
    s = false;
    Serial.println("");
  }
  /*  
   *  data packet
   *  15A
   *  125 xx cc cc 17E
   *  17A 03 00 00 00 LL xx cc cc 17E
   *  180
   *  1СA
   *  
   */
  if (Serial9b1.available ()) {
    loopTime = currentTime;

    if(Serial9b1.available ()) {
      Serial.print("<< ");
      while(Serial9b1.available ()) {
        uint16_t d = Serial9b1.read ();
        Serial.print(d, HEX);
        Serial.print(" ");
        rcv[ind++] = (byte)d;
      }
      Serial.println("");
    }
    
    if( rcv[0] == 0x5A ) {
        delayMicroseconds(200);
        if( cnt > 50 ) {
          cnt = 0;
          //cnt2 = 0xF0;
          sprintf(spb, "0x%02X '%c' ", cnt2, cnt2);
          for(int i = 0; i < strlen(spb);i++) {
            sendline[4+i] = spb[i];
          }
          for(int i = 0; i < 12;i++) {
            sendline[4+strlen(spb) + i] = i + cnt2;
          }
          if(cnt2 &1) {
            sendline[2] = 0x82;
          } else {
            sendline[2] = 0x81;
          }
          sendAnswer_X();
              
          cnt2++;
        }
        cnt++;
        clrBuff();//*/
    }
    else if (rcv[0] == 0x25) {
      if(rcv[1] != 0x20){
        if (rcv[4] == 0x7E)  {
          if((sti == 0 )&&(rcv[1] == 0x0F)) {
            sti = 1;
          }
          (*sendAnswerArray[sti])();
          //Serial.println("T2");
          clrBuff();
        }
      }
      else {
        loopTime = currentTime;
        if (rcv[10] == 0x7E)  {
          //(*sendAnswerArray[3])();
          sendAnswer_2();

          //Serial.println("T3");
          clrBuff();
        }
      }
    }
  }
  if(currentTime >= (loopTime + 1600)) {
    if( ind > 0 ) {
      //Serial.println("T4");      
      clrBuff();
    }
    loopTime = currentTime;
    s = true;
  }
  if( sti >= ELEMENTS ) {
    // restart & stop state mashine
    sti = 0;
  }
}
