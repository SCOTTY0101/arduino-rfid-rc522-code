#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define RED 2
#define Green 3
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   digitalWrite(Green, LOW);
   digitalWrite(RED, LOW);

}

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
 
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if ((content.substring(1) == "1A 7C 78 30") || (content.substring(1) == "CC CC A3 16") ) {
   //change here the UID of the card/cards that you want to give access
  
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(Green, HIGH);
    delay(10000);
    digitalWrite(Green, LOW);
  }
 
 else   {
  
    Serial.println(" Access denied");
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(RED, HIGH);
    delay(10000);
    digitalWrite(RED, LOW);
  
  }
} 
