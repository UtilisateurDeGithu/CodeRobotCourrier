const int pinPWM_A = 3;      // Broche pour la vitesse du moteur A
const int pinPWM_B = 11;      // Broche pour la vitesse du moteur B
const int pinDIR_A = 12;      // Broche pour le sens du moteur A
const int pinDIR_B = 13;      // Broche pour le sens du moteur B
const int pinBRAKE_A = 9;    // Broche pour le freinage du moteur A
const int pinBRAKE_B = 8; // Broche pour le freinage du moteur B
const int Buzzer = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinPWM_A,OUTPUT);     // Toutes les broches sont configurées en mode sortie (OUTPUT)
  pinMode(pinPWM_B,OUTPUT);
  pinMode(pinDIR_A,OUTPUT);
  pinMode(pinDIR_B,OUTPUT);
  pinMode(pinBRAKE_A,OUTPUT);
  pinMode(pinBRAKE_B,OUTPUT);
  digitalWrite (Buzzer, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (pinPWM_A, HIGH);
  digitalWrite (pinPWM_B, HIGH);
  digitalWrite (pinDIR_A, HIGH);
  digitalWrite (pinDIR_B, HIGH);

}
