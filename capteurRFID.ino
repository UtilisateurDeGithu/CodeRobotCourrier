
/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read new NUID from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN); // appel de la classe
const int Buzzer = 2;
int repeat = 0;
const int retour = 6;


// liste clÃ©s valides
String keyOk[]={"15 c4 2d 5","15 c4 2d 6"};


void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  // led eteintes a l'init
  digitalWrite (Buzzer, HIGH);
  pinMode (retour, INPUT);
}
 
void loop() {

  // Si on ne detecte pas une carte on reboucle au debut
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // as t'on lu la carte
  if ( ! rfid.PICC_ReadCardSerial())
    return;

// recuperation de l'UID et concatÃ©nation de sa valeur en hex dans un string
String myKey=String(rfid.uid.uidByte[0],HEX) + " " + String(rfid.uid.uidByte[1],HEX) + " " + String(rfid.uid.uidByte[2],HEX) + " " + String(rfid.uid.uidByte[3],HEX);

// j'affiche la valeur de la carte sur le serial
Serial.println(myKey);

bool accessOk = 0;
// je boucle sur toutes les valeurs des clÃ©s autorisÃ©s et si je la trouve accesOK => 1
for(int y = 0; y < (sizeof(keyOk)/sizeof(String)) ; y++){

  if(keyOk[y] == myKey){
    accessOk = 1;
  
  }
  
}

  // Halt PICC, fin de lecture de carte
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();


// La carte as t'elle acces , si oui led verte , si non led rouge
  if(accessOk == 1){
    Serial.println("test");
    digitalWrite (retour, HIGH);
  }
  else{
    Serial.println("test2");
  }

// on eteind les led apres un delais
delay(2000);
}
