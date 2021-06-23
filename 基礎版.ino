/*
  Melody
 */
#define NOTE_C3  131
#define NOTE_D3  147
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

int buttonPin[]={2,3,4,5,6,7,8,9};

//設定各接腳
int latchPin = 10;
int clockPin = 12;
int dataPin = 11;

int note[] = {
  NOTE_C3, NOTE_D3,NOTE_E3, NOTE_F3,NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4
};

byte scan[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
}; //掃描
byte memory[8] = {
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
}; //最近八個音符（預設0）

byte NoteLight[8] = {
   B10000000,
   B01000000,
   B00100000,
   B00010000,
   B00001000,
   B00000100,
   B00000010,
   B00000001,
}; //音符對應查詢表

void change(){		//把音符燈往上推
  	memory[0]=memory[1];
  	memory[1]=memory[2];
  	memory[2]=memory[3];
  	memory[3]=memory[4];
  	memory[4]=memory[5];
  	memory[5]=memory[6];
  	memory[6]=memory[7];
}

void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  for(byte i=0;i<=7;i++){
    pinMode(buttonPin[i],INPUT_PULLUP);
    //digitalWrite(buttonPin[i],HIGH);
  }
}

void play(){	//判斷按鈕被點擊
  if(digitalRead(buttonPin[0]) == LOW){
    change();	
    memory[7]=NoteLight[0];
    tone(13, note[0]);
  }
  else if(digitalRead(buttonPin[1]) == LOW){
    change();
    memory[7]=NoteLight[1];
    tone(13, note[1]); 
  }
  else if(digitalRead(buttonPin[2]) == LOW){
    change();
    memory[7]=NoteLight[2];
    tone(13, note[2]);
  }
  else if(digitalRead(buttonPin[3]) == LOW){
    change();
    memory[7]=NoteLight[3];
    tone(13, note[3]);
  }
  else if(digitalRead(buttonPin[4]) == LOW){
    change();
    memory[7]=NoteLight[4];
    tone(13, note[4]);
  }
  else if(digitalRead(buttonPin[5]) == LOW){
    change();
    memory[7]=NoteLight[5];
    tone(13, note[5]);
  }
  else if(digitalRead(buttonPin[6]) == LOW){
    change();
    memory[7]=NoteLight[6];
    tone(13, note[6]);
  }
  else if(digitalRead(buttonPin[7]) == LOW){
    change();
    memory[7]=NoteLight[7];
    tone(13, note[7]);
  }
  else noTone(13);
}


void loop() {
  play();
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, memory[i]);
    digitalWrite(latchPin,HIGH);
    delay(5);
  }

}
