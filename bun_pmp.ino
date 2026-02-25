#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Definiții pini
#define TRIG_ENTRY 2    // Intrare
#define ECHO_ENTRY 3
#define TRIG_EXIT 4     // Ieșire
#define ECHO_EXIT 5
#define SERVO_PIN 11    // Bariera

// Setări
#define MAX_DISTANCE 50     // cm
#define DETECTION_DISTANCE 30  // distanță activare
#define TOTAL_SPOTS 4       // număr total locuri
#define CHECK_INTERVAL 300  // ms între verificări
#define BARRIER_OPEN_TIME 3000 // ms cât stă bariera deschisă

// Obiecte
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adresa LCD 
Servo barrierServo;

// Variabile globale
int availableSpots = TOTAL_SPOTS;
bool barrierOpen = false;
unsigned long barrierCloseTime = 0;
unsigned long lastCheckEntry = 0;
unsigned long lastCheckExit = 0;
bool entryBlocked = false;  // Pentru a evita detectări multiple
bool exitBlocked = false;

void setup() {
  Serial.begin(9600);
  
  // Inițializare pini senzori
  pinMode(TRIG_ENTRY, OUTPUT);
  pinMode(ECHO_ENTRY, INPUT);
  pinMode(TRIG_EXIT, OUTPUT);
  pinMode(ECHO_EXIT, INPUT);
  
  // Inițializare servo
  barrierServo.attach(SERVO_PIN);
  closeBarrier(); // Închide bariera la start
  
  // Inițializare LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Afișare inițială
  updateDisplay();
  Serial.println("Sistem parcare pornit");
  Serial.print("Loc. totale: ");
  Serial.println(TOTAL_SPOTS);
}

void loop() {
  unsigned long currentTime = millis();
  
  // Verificare senzor INTRARE
  if (currentTime - lastCheckEntry >= CHECK_INTERVAL) {
    lastCheckEntry = currentTime;
    float distance = measureDistance(TRIG_ENTRY, ECHO_ENTRY);
    
    if (distance < DETECTION_DISTANCE && distance > 2) {
      if (!entryBlocked && availableSpots > 0) {
        Serial.println("Masina detectata la INTRARE");
        entryBlocked = true;
        carEntered();
      }
    } else {
      entryBlocked = false;
    }
  }
  
  // Verificare senzor IESIRE
  if (currentTime - lastCheckExit >= CHECK_INTERVAL) {
    lastCheckExit = currentTime;
    float distance = measureDistance(TRIG_EXIT, ECHO_EXIT);
    
    if (distance < DETECTION_DISTANCE && distance > 2) {
      if (!exitBlocked && availableSpots < TOTAL_SPOTS) {
        Serial.println("Masina detectata la IESIRE");
        exitBlocked = true;
        carExited();
      }
    } else {
      exitBlocked = false;
    }
  }
  
  // Închidere automată barieră
  if (barrierOpen && currentTime >= barrierCloseTime) {
    closeBarrier();
  }
}

// Funcție pentru măsurarea distanței
float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);
  float distance = duration * 0.034 / 2;
  
  if (distance > MAX_DISTANCE || distance <= 0) {
    return MAX_DISTANCE + 1;
  }
  return distance;
}

// Mașină intră în parcare
void carEntered() {
  if (availableSpots > 0) {
    availableSpots--;
    openBarrier();
    updateDisplay();
    
    Serial.print("Masina a intrat. Loc. ramase: ");
    Serial.println(availableSpots);
    
    // Afișare mesaj pe LCD temporar
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" BINE ATI VENIT! ");
    lcd.setCursor(0, 1);
    lcd.print("Loc: ");
    lcd.print(availableSpots);
    lcd.print("/");
    lcd.print(TOTAL_SPOTS);
    delay(2000);
    updateDisplay();
  }
}

// Mașină iese din parcare
void carExited() {
  if (availableSpots < TOTAL_SPOTS) {
    availableSpots++;
    openBarrier();
    updateDisplay();
    
    Serial.print("Masina a iesit. Loc. disponibile: ");
    Serial.println(availableSpots);
    
    // Afișare mesaj pe LCD temporar
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" LA REVEDERE! ");
    lcd.setCursor(0, 1);
    lcd.print("Loc: ");
    lcd.print(availableSpots);
    lcd.print("/");
    lcd.print(TOTAL_SPOTS);
    delay(2000);
    updateDisplay();
  }
}

// Deschide bariera
void openBarrier() {
  if (!barrierOpen) {
    barrierServo.write(90); // Deschide 90 grade
    barrierOpen = true;
    barrierCloseTime = millis() + BARRIER_OPEN_TIME;
    Serial.println("Bariera DESCHISA");
  }
}

// Închide bariera
void closeBarrier() {
  if (barrierOpen) {
    barrierServo.write(0); // Închide
    barrierOpen = false;
    Serial.println("Bariera INCHISA");
  }
}

// Actualizează display-ul LCD
void updateDisplay() {
  lcd.clear();
  
  // Linia 1: Titlu
  lcd.setCursor(0, 0);
  lcd.print("PARCARE AUTO");
  
  // Linia 2: Locuri disponibile
  lcd.setCursor(0, 1);
  lcd.print("Loc: ");
  
  // Afișează cu verde/roșu simbolic
  if (availableSpots > 0) {
    lcd.print(availableSpots);
    lcd.print("/");
    lcd.print(TOTAL_SPOTS);
    lcd.print(" LIBER");
  } else {
    lcd.print("0/");
    lcd.print(TOTAL_SPOTS);
    lcd.print(" PLIN ");
  }
}

// Funcție pentru testare/debug (opțional)
void testSensors() {
  Serial.println("=== TEST SENZORI ===");
  
  float distEntry = measureDistance(TRIG_ENTRY, ECHO_ENTRY);
  Serial.print("INTRARE: ");
  Serial.print(distEntry);
  Serial.println(" cm");
  
  float distExit = measureDistance(TRIG_EXIT, ECHO_EXIT);
  Serial.print("IESIRE: ");
  Serial.print(distExit);
  Serial.println(" cm");
  
  delay(1000);
}
