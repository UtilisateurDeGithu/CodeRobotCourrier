/*

Cette partie du code
Sert à faire fonctionner
Le Capteur RFID

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


// La carte est-elle autorisé ?
  if(accessOk == 1){
    Serial.println("test");
    digitalWrite (retour, HIGH);
  }
  else{
    Serial.println("test2");
  }

// on eteins les leds après un delais
delay(2000);
}
