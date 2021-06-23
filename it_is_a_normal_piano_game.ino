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

#define BUTTON  A0

int buttonPin[]={2,3,4,5,6,7,8,9};

//設定各接腳
int latchPin = 10;
int clockPin = 12;
int dataPin = 11;

int waitTime=0;
int createTime=0;
int playGame=0;

int previousState=1;
int presentState=1;

int note[] = {
  NOTE_C3, NOTE_D3,NOTE_E3, NOTE_F3,NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4
};

////////////////////////////////////////////////////////

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

byte space[8] = {
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
}; //空白（全暗）

byte place[8] = {
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
}; //場地（預設0）

byte bullet[8] = {
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
}; //子彈（預設0）

byte monster[8] = {
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
}; //怪物（預設0）

byte NoteLight[8] = {
   B10000000,
   B01000000,
   B00100000,
   B00010000,
   B00001000,
   B00000100,
   B00000010,
   B00000001,
}; //對應查詢表

byte p1[8] = {
   B00111000,
   B01111000,
   B11011000,
   B10011000,
   B00011000,
   B00011000,
   B11111111,
   B11111111,
}; //start pattern 1
byte p2[8] = {
   B00011000,
   B11100110,
   B11000011,
   B01000011,
   B00000110,
   B00001100,
   B11111000,
   B11111111,
}; //start pattern 2
byte p3[8] = {
   B00111100,
   B01100110,
   B10000011,
   B00111110,
   B00111110,
   B10000011,
   B11000110,
   B00111100,
}; //start pattern 3
byte loseP[8] = {
   B10000001,
   B01000010,
   B00100100,
   B00011000,
   B00011000,
   B00100100,
   B01000010,
   B10000001,
}; //lose pattern

byte shineP[8] = {
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
}; //shine pattern 

////////////////////////////////////////////////////////
void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  for(byte i=0;i<=7;i++){
    pinMode(buttonPin[i],INPUT_PULLUP);
    //digitalWrite(buttonPin[i],HIGH);
  }
}
////////////////////////////////////////////////////////

void clear(){  //start pattern setting
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, space[i]);
    digitalWrite(latchPin,HIGH);
  }
}

void start(){  //start pattern setting
  delay(500);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, p3[i]);
    digitalWrite(latchPin,HIGH);
    delay(10);
  }
  clear();
  delay(1000);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, p2[i]);
    digitalWrite(latchPin,HIGH);
    delay(10);
  }
  clear();
  delay(1000);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, p1[i]);
    digitalWrite(latchPin,HIGH);
    delay(10);
  }
  clear();
  delay(1000);
}

void shine(){  //start pattern setting
  delay(300);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, shineP[i]);
    digitalWrite(latchPin,HIGH);
    }
  delay(400);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, shineP[i]);
    digitalWrite(latchPin,HIGH);
  }
  delay(400);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, shineP[i]);
    digitalWrite(latchPin,HIGH);
  }
  clear();
  delay(500);
  
}   
void lose(){  //lose pattern setting
  delay(1000);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, loseP[i]);    
    digitalWrite(latchPin,HIGH);
    }
  clear();
  delay(500);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, loseP[i]);
    digitalWrite(latchPin,HIGH);
    }
  clear();
  delay(500);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, loseP[i]); 
    digitalWrite(latchPin,HIGH);
    }
  clear();
  delay(500);
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, loseP[i]);
    digitalWrite(latchPin,HIGH);
    }
  clear();
  delay(500);  

}

void change(){		//子彈往上飛
  	bullet[0]=bullet[1];
  	bullet[1]=bullet[2];
  	bullet[2]=bullet[3];
  	bullet[3]=bullet[4];
  	bullet[4]=bullet[5];
  	bullet[5]=bullet[6];
  	bullet[6]=bullet[7];
}

void monsterChange(){		//怪物往下走
  	monster[7]=monster[6];
  	monster[6]=monster[5];
  	monster[5]=monster[4];
  	monster[4]=monster[3];
  	monster[3]=monster[2];
  	monster[2]=monster[1];
  	monster[1]=monster[0];
    monster[0]=0;
}

void monsterCreate(){		//產生怪物
  	monster[0]=NoteLight[random(0, 8)];
}

void play(){	//判斷按鈕被點擊＝子彈發射、怪物行動、生成
  if(digitalRead(buttonPin[0]) == LOW){
    change();	
    bullet[7]=NoteLight[0];
    tone(13, note[0]);
  }
  else if(digitalRead(buttonPin[1]) == LOW){
    change();
    bullet[7]=NoteLight[1];
    tone(13, note[1]); 
  }
  else if(digitalRead(buttonPin[2]) == LOW){
    change();
    bullet[7]=NoteLight[2];
    tone(13, note[2]);
  }
  else if(digitalRead(buttonPin[3]) == LOW){
    change();
    bullet[7]=NoteLight[3];
    tone(13, note[3]);
  }
  else if(digitalRead(buttonPin[4]) == LOW){
    change();
    bullet[7]=NoteLight[4];
    tone(13, note[4]);
  }
  else if(digitalRead(buttonPin[5]) == LOW){
    change();
    bullet[7]=NoteLight[5];
    tone(13, note[5]);
  }
  else if(digitalRead(buttonPin[6]) == LOW){
    change();
    bullet[7]=NoteLight[6];
    tone(13, note[6]);
  }
  else if(digitalRead(buttonPin[7]) == LOW){
    change();
    bullet[7]=NoteLight[7];
    tone(13, note[7]);
  }
  else {
    change();
    bullet[7]=0;
    noTone(13);
  }
  waitTime++;
  createTime++;
    if(waitTime>=15){		//判斷怪物行動
    monsterChange();
    waitTime=0;
  }
    if(createTime>=30){		//判斷怪物生成
    monsterCreate();
    createTime=0;
  }
}

void attack(){		//判斷子彈擊中怪物與否＆更新場地狀況
  for(int i=0;i<8;i++){
    if(bullet[i]==monster[i]) place[i]=bullet[i]=monster[i]=0;
    else place[i]=bullet[i]+monster[i];
  }
}

void goStart(){
  for(int i=0;i<8;i++){
    place[i]=0;
    bullet[i]=0;
    monster[i]=0;
  }
  start();
  shine();
}

void checkBotton(){
  presentState=digitalRead(BUTTON);
  if(previousState==1&&presentState==0)
  {
  	playGame++;
    if(playGame>1) playGame=0;
  }
  previousState=presentState;
}

void checkLose(){
  for(int i=0;i<8;i++){
    if(monster[7]==NoteLight[i]){
      playGame=0;
      lose();
      shine();
    }
  }
}

////////////////////////////////////////////////////////

void loop() {
  //playGame=1;
  checkBotton();
  if(playGame){
    goStart();
    delay(50);
 	monsterCreate();
    while(playGame){
      play();
  	  attack();
  	  for(int i = 0; i < 8 ; i++){
    	digitalWrite(latchPin,LOW);
    	shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    	shiftOut(dataPin, clockPin, LSBFIRST, place[i]);
    	digitalWrite(latchPin,HIGH);
    	delay(5);
  	  }
      checkLose();
    }
    delay(1000);
    //checkBotton();
  }

}
