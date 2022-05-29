/***********************************************
 * Déclaration et initialisation des variables *
 ***********************************************/
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN); // appel de la classe
const int Buzzer = 666;

const int pinPWM_A = 3;      // Broche pour la vitesse du moteur A
const int pinPWM_B = 11;      // Broche pour la vitesse du moteur B
const int pinDIR_A = 12;      // Broche pour le sens du moteur A
const int pinDIR_B = 13;      // Broche pour le sens du moteur B
const int pinBRAKE_A = 9;    // Broche pour le freinage du moteur A
const int pinBRAKE_B = 8;    // Broche pour le freinage du moteur B

const int pinTrig = 4;      // Broche pour la commande d'émission des ultrasons
const int pinEcho = 5;      // Broche pour le signal de retour du capteur
int distance = 0;           // Variable utilisée pour stocker la distance mesurée
int IN1 = 4; //Pin pour Le Capteur Gauche
int IN4 = 5; //Pin pour Le Capteur Droite
int GA=12,GB=3,DA=13,DB=11;

void setup() {
  pinMode(pinPWM_A,OUTPUT);     // Toutes les broches sont configurées en mode sortie (OUTPUT)
  pinMode(pinPWM_B,OUTPUT);
  pinMode(pinDIR_A,OUTPUT);
  pinMode(pinDIR_B,OUTPUT);
  pinMode(pinBRAKE_A,OUTPUT);
  pinMode(pinBRAKE_B,OUTPUT);

  pinMode(pinTrig,OUTPUT);     // la broche de commande est une sortie (OUTPUT), on envoie un signal
  pinMode(pinEcho,INPUT);      // la broche de retour est une entrée (INPUT), on reçoit un signal
  pinMode(IN1,INPUT);
  pinMode(IN4,INPUT);
  pinMode(DA,OUTPUT);
  pinMode(DB,OUTPUT);
  pinMode(GA,OUTPUT);
  pinMode(GB,OUTPUT);
  Serial.begin(9600);          // Démarrage de la communication série visualisable dans Outils/Moniteur série (Ctrl+Maj+M)
}
void d() //Fonction qui permet au robot de tourner a droite
        {
      digitalWrite(DA,LOW);
      analogWrite(DB,55);
      analogWrite(GA,55);
      digitalWrite(GB,LOW);
         }
         void g() //Fonction qui permet au robot de tourner a gauche
{
      analogWrite(DA,55);
      digitalWrite(DB,LOW);
      digitalWrite(GA,LOW);
      analogWrite(GB,55);
}
         void av() //Fonction qui permet au robot de continuer tout droit
         {
          digitalWrite(DA,LOW);
          analogWrite(DB,55);
          digitalWrite(GA,LOW);
          analogWrite(GB,55);
         }


void loop() 
{
   int in1_val = digitalRead(IN1);
          int in4_val = digitalRead(IN4);
          if ((in1_val) && ( ! in4_val))
         
          {
            Serial.println("Tourner à gauche");
            g();
          }
          
          else if (( ! in1_val) && (in4_val))
          
          {
          Serial.println("Tourner à droite");
          d();
          }        
          else //Si les conditions plus haut ne s'appliquent pas, continuer tout droit
          {
          Serial.println("Continuer tout droit");
          av();
          }
  distance = mesurerDistance();    
  if (distance>40){
    avancerA(255);
    avancerB(255);
    Serial.println("A fond !");
  }
  else if(distance >= 15 && distance <= 40) {
    avancerA(100);
    avancerB(100);
    Serial.println("Doucement");
  }
  else {
    arreter();
    Serial.println("Stop");
  }
  }
  

int mesurerDistance() {
  long duree = 2;                     // Initialisation de la variable "duree" destinée au stockage du temps d'aller-retour des ultrasons
  digitalWrite(pinTrig,LOW);          // Arrêt des ultrasons (pour être sûr)
  delayMicroseconds(5);               // Pause de 5 µs
  digitalWrite(pinTrig,HIGH);         // Emission des ultrasons
  delayMicroseconds(10);              // Les ultrasons sont émis pendant 10 µs
  digitalWrite(pinTrig,LOW);          // Arrêt des ultrasons
  duree = pulseIn(pinEcho,HIGH);      // Calcul du temps mis par les ultrasons pour faire un aller-retour
  return duree*0.034/2;               // Calcul de la distance à l'obstacle à l'aide de la vitesse du son : 340 m/s soit 0.034 cm/µs
}

//-> A FAIRE : Ecrivez les instructions à exécuter entre les {} en utilisant les fonctions ci-dessous.

/************************************************
 * Fonctions utilisables dans loop() et setup() *
 ************************************************/
void avancerA(int vitesse) {        // Fonction faisant avancer le moteur A
  digitalWrite(pinBRAKE_A,LOW);     // La vitesse doit être comprise entre 0 et 255
  digitalWrite(pinDIR_A,HIGH);      // Exemple d'utilisation : avancerA(255);
  analogWrite(pinPWM_A,vitesse);
}

void avancerB(int vitesse) {        // Fonction faisant avancer le moteur B
  digitalWrite(pinBRAKE_B,LOW);     // La vitesse doit être comprise entre 0 et 255
  digitalWrite(pinDIR_B,LOW);       // Exemple d'utilisation : avancerB(127);
  analogWrite(pinPWM_B,vitesse);
}
void arreter() {                    // Fonction arrêtant les 2 moteurs
  analogWrite(pinPWM_A,0);          // Exemple d'utilisation : arreter();
  analogWrite(pinPWM_B,0);
}
