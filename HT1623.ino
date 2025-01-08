/****************************************************/
/* This is only one example of code structure       */
/* OFFCOURSE this code can be optimized, but        */
/* the idea is let it so simple to be easy catch    */
/* where we can do changes and look to the results  */
/****************************************************/
#define LCD_data 8// Bit of data to sent
#define LCD_wr 9 // Do the function like a clock
#define LCD_cs 10 // must be LOW to select the driver

#define BUTTON_PIN 2 //Att check wich pins accept interrupts... Uno is 2 & 3, This is our trigger button
volatile byte buttonReleased = false;

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

/*Global Variables Declarations*/
uint8_t dat8bits = 0x00;
uint16_t adr14bits = 0x0000;
uint16_t cmd14bits = 0b10100000000000; //Define command
uint16_t tmp14bits = 0b0;
uint16_t val14bits = 0x00;
/*Global Variables Declarations*/

//    Numbers desing        hijbggcm     ..deklaf
unsigned char number0[]={(0b00010010),(0b00110011),(0b00000000)}; // 0      
unsigned char number1[]={(0b00010010),(0b00000000),(0b00000000)}; // 1
unsigned char number2[]={(0b00011100),(0b00110010),(0b00000000)}; // 2
unsigned char number3[]={(0b00011110),(0b00100010),(0b00000000)}; // 3
unsigned char number4[]={(0b00011110),(0b00000001),(0b00000000)}; // 4
unsigned char number5[]={(0b00001110),(0b00100011),(0b00000000)}; // 5
unsigned char number6[]={(0b00001110),(0b00110011),(0b00000000)}; // 6
unsigned char number7[]={(0b00010010),(0b00000010),(0b00000000)}; // 7
unsigned char number8[]={(0b00011110),(0b00110011),(0b00000000)}; // 8
unsigned char number9[]={(0b00011110),(0b00000011),(0b00000000)}; // 9
//    Letters design        hijbggcm     ..deklaf
unsigned char letterA[]={(0b11100011),(0b00001001),(0b00000000)}; // A
unsigned char letterB[]={(0b10110001),(0b00011010),(0b00000000)}; // B
unsigned char letterC[]={(0b00100001),(0b00011000),(0b00000000)}; // C
unsigned char letterD[]={(0b00100100),(0b00001100),(0b00000000)}; // D
unsigned char letterE[]={(0b11100001),(0b00011000),(0b00000000)}; // E
unsigned char letterF[]= {(24),(0b00001101),(26),(8),(28),(8),(30),(2)};// F
unsigned char letterG[]={(0b01100001),(0b00011001),(0b00000000)}; // G
unsigned char letterH[]={(0),(0b00001101),(6),(0b00001011)}; // H
unsigned char letterI[]={(11),(3),(12),(0b00001101),(10),(0b00001011)}; // I
unsigned char letterJ[]={(0b00000010),(0b00011001),(0b00000000)}; // J
unsigned char letterK[]={(48),(0b00001101),(54),(4),(52),(2)}; // k
unsigned char letterL[]={(40),(0b00001001),(42),(1),(44),(1)}; // L
unsigned char letterM[]={(0b00110110),(0b00001001),(0b00000000)}; // M
unsigned char letterN[]={(0b00100110),(0b00001011),(0b00000000)}; // N
unsigned char letterO[]={(34),(0b00001001),(36),(0b00001001),(32),(0b00001001),(38),(0b00001001)}; // O
unsigned char letterP[]={(0b11100011),(0b00001000),(0b00000000)}; // P
unsigned char letterQ[]={(0b00100011),(0b00011011),(0b00000000)}; // A
unsigned char letterR[]={(0b11100011),(0b00001010),(0b00000000)}; // R
unsigned char letterS[]={(58),(0b00001001),(60),(0b00001001),(56),(0b00001100),(62),(0b00000011)}; // S
unsigned char letterT[]={(0b00001001),(0b00000000),(0b00000000)}; // T
unsigned char letterU[]={(0b00100010),(0b00011001),(0b00000000)}; // U
unsigned char letterV[]={(0b00110000),(0b00001100),(0b00000000)}; // V
unsigned char letterX[]={(0b00010100),(0b00000110),(0b00000000)}; // X
unsigned char letterZ[]={(0b00010001),(0b00010100),(0b00000000)}; // Z
unsigned char letterW[]={(0b00100010),(0b00001111),(0b00000000)}; // W
unsigned char letterSpace[]={(0b00000000),(0b00000000),(0b00000000)}; // Empty space

void cmd_with_stb(uint16_t a){
  // send with stb
  uint16_t data =0x0;
  uint16_t mask = 0x4000; //our bitmask on this methode have a length of 14 bits
  
  data=a;
  
  //This send the strobe signal
  //Note: The first byte input at in after the STB go LOW is interpreted as a command!!!
  digitalWrite(LCD_cs, LOW);
  delayMicroseconds(1);
   for (mask = 0b10000000000000; mask > 0; mask >>= 1) { //iterate through bit mask
     digitalWrite(LCD_wr, LOW);
     delayMicroseconds(1);
     if (data & mask){ // if bitwise AND resolves to true
        digitalWrite(LCD_data, HIGH);
     }
     else{ //if bitwise and resolves to false
       digitalWrite(LCD_data, LOW);
     }
    digitalWrite(LCD_wr, HIGH);
    delayMicroseconds(1);
   }
   digitalWrite(LCD_cs, HIGH);
   delayMicroseconds(1);
}
void cmd12_with_stb(uint16_t a){
  // send with stb
  uint16_t data =0x0;
  uint16_t mask = 0x4000; //our bitmask on this methode have a length of 14 bits
  
  data=a;
  
  //This send the strobe signal
  //Note: The first byte input at in after the STB go LOW is interpreted as a command!!!
  digitalWrite(LCD_cs, LOW);
  delayMicroseconds(1);
   for (mask = 0b100000000000; mask > 0; mask >>= 1) { //iterate through bit mask
     digitalWrite(LCD_wr, LOW);
     delayMicroseconds(1);
     if (data & mask){ // if bitwise AND resolves to true
        digitalWrite(LCD_data, HIGH);
     }
     else{ //if bitwise and resolves to false
       digitalWrite(LCD_data, LOW);
     }
    digitalWrite(LCD_wr, HIGH);
    delayMicroseconds(1);
   }
   digitalWrite(LCD_cs, HIGH);
   delayMicroseconds(1);
}

void clearLCD(){
  for(uint16_t s=0x0000; s < 0x007F; s++){
        cmd14bits = 0b10100000000000;
        adr14bits = s;
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = 0x00;
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(5);
      }
}
void allOn(){
  for(uint16_t s=0x0000; s < 0x0080; s++){
        cmd14bits = 0b10100000000000;
        adr14bits = s;
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = 0x0F;
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(2);
      }
}
void msgHiFolks(){
 clearLCD();
 for(uint8_t i = 0; i < sizeof(letterH); i=i+2){
      Serial.println(i, DEC);
       cmd14bits = 0b10100000000000;
        adr14bits = letterH[i];
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = letterH[i+1];
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(2);
                Serial.println(val14bits, BIN);
    }
    for(uint8_t i = 0; i < sizeof(letterI); i=i+2){
      Serial.println(i, DEC);
       cmd14bits = 0b10100000000000;
        adr14bits = letterI[i];
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = letterI[i+1];
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(2);
                Serial.println(val14bits, BIN);
    }
    for(uint8_t i = 0; i < sizeof(letterF); i=i+2){
      Serial.println(i, DEC);
       cmd14bits = 0b10100000000000;
        adr14bits = letterF[i];
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = letterF[i+1];
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(2);
                Serial.println(val14bits, BIN);
    }
    for(uint8_t i = 0; i < sizeof(letterO); i=i+2){
      Serial.println(i, DEC);
       cmd14bits = 0b10100000000000;
        adr14bits = letterO[i];
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = letterO[i+1];
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(2);
                Serial.println(val14bits, BIN);
    }
    for(uint8_t i = 0; i < sizeof(letterL); i=i+2){
      Serial.println(i, DEC);
       cmd14bits = 0b10100000000000;
        adr14bits = letterL[i];
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = letterL[i+1];
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(2);
                Serial.println(val14bits, BIN);
    }   
     for(uint8_t i = 0; i < sizeof(letterK); i=i+2){
      Serial.println(i, DEC);
       cmd14bits = 0b10100000000000;
        adr14bits = letterK[i];
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = letterK[i+1];
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(2);
                Serial.println(val14bits, BIN);
    }   
    for(uint8_t i = 0; i < sizeof(letterS); i=i+2){
      Serial.println(i, DEC);
       cmd14bits = 0b10100000000000;
        adr14bits = letterS[i];
        adr14bits = (adr14bits << 4);
        tmp14bits = (cmd14bits | adr14bits);
                dat8bits = letterS[i+1];
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                cmd_with_stb(val14bits); 
                delay(2);
                Serial.println(val14bits, BIN);
    }   
}
void displayLetter(unsigned char* letter, uint8_t lng){
  for(uint8_t i = 0; i < lng; i=i+2){
        Serial.println(i, DEC);
        cmd14bits = 0b10100000000000;
          adr14bits = *(letter+i);
          adr14bits = (adr14bits << 4);
          tmp14bits = (cmd14bits | adr14bits);
                  dat8bits = *(letter+(i+1));
                  val14bits = (tmp14bits | (dat8bits  & 0x0F));
                  cmd_with_stb(val14bits); 
                  delay(2);
                  Serial.println(val14bits, BIN);
      }   
}
void initLCD(){
  cmd12_with_stb(0b100101001110); //Define the base time 128
  delay(3);
  cmd12_with_stb(0b100000111000);// 32k EXT(XTAL) This set the clock based on external xTall
  delay(3);
  cmd12_with_stb(0b100000000010);  // SYS enable
  delay(3);
  cmd12_with_stb(0b100000000110);  // LCD on
  delay(3);
  cmd12_with_stb(0b100111000110);  // NORMAL Mode
  delay(3);
  clearLCD();
}

void findSegments(){
  uint8_t seg = 0x00;
  cmd14bits = 0b10100000000000;
  adr14bits = 0b00000000000000;
  tmp14bits = 0b10100000000000;
  dat8bits = 0x00;
  buttonReleased = false;
 allOn();
      for(uint16_t s=0x0000; s < 96; s++){
        cmd14bits = 0b10100000000000;
        adr14bits = s;
        adr14bits = (adr14bits << 4);
       
        tmp14bits = (cmd14bits | adr14bits);
              for (uint8_t i=0; i < 4; i++){
                dat8bits = (0x01 << i);
                dat8bits = ~(dat8bits);
                val14bits = (tmp14bits | (dat8bits  & 0x0F));
                //Serial.println(val14bits, BIN);
                 cmd_with_stb(val14bits); //
                 Serial.print("Mem Addr: "); Serial.print(s, DEC); Serial.print(", Bit: "); Serial.print(i);
                Serial.print(", seg: "); Serial.println(seg, DEC);
                //This wait the action of control button to allow continue the test! 
                        while(1){
                              if(!buttonReleased){
                                delay(200);
                              }
                              else{
                                delay(15);
                                buttonReleased = false;
                                break;
                                }
                        }
                
                //Serial.println(cmd14bits, BIN);
                
                seg++; //Here I increment the count value of segment: "seg".
                delay(5);           
              }
              cmd_with_stb(val14bits | 0x000F); // 
      }
}
void writeMessageByPointers(){
  uint8_t lng = 0x00; //assigne a dummy value to the variable to catch the lenght of my array.
  unsigned char* myArray = NULL; //Here we initialize the pointer as null.
      clearLCD(); //Clean of LCD function.

      myArray = &letterH[0];  //Assign the pointer to array of letter H
      lng = sizeof(letterH);  //Get the size of array of letter H
      displayLetter(myArray, lng); //Call a function to present the segments of letter H

      myArray = &letterI[0];
      lng = sizeof(letterI);
      displayLetter(myArray, lng);

      myArray = &letterF[0];
      lng = sizeof(letterF);
      displayLetter(myArray, lng);

      myArray = &letterO[0];
      lng = sizeof(letterO);
      displayLetter(myArray, lng);

      myArray = &letterL[0];
      lng = sizeof(letterL);
      displayLetter(myArray, lng);

      myArray = &letterK[0];
      lng = sizeof(letterK);
      displayLetter(myArray, lng);

      myArray = &letterS[0];
      lng = sizeof(letterS);
      displayLetter(myArray, lng);
}
void setup(){
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Set PORT
  DDRD = 0xFF;  // IMPORTANT: from pin 0 to 7 is port D, from pin 8 to 13 is port B
  PORTD= 0x00;
  DDRB = 0xFF;
  PORTB= 0x00;
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  //
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),
                buttonReleasedInterrupt,
                FALLING);
 initLCD();
}
void loop() {
  allOn();
  delay(1500);
  clearLCD();
  writeMessageByPointers(); // This will present the letters passed to function by pointers.
  //msgHiFolks(); //This is a way to present the letter with individual metod!
  delay(2000);
  //findSegments(); //Uncomment this line if you want find de segments!
}
void buttonReleasedInterrupt() {
buttonReleased = true; // This is the line of interrupt button to advance one step on the search of segments!
}
  

