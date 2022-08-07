#include <Wire.h>
#include <VL53L0X.h>


VL53L0X sensor;

int motor1pin1 = 4;
int motor1pin2 = 5;

int motor2pin1 = 6;
int motor2pin2 = 7;

int velocidade1 = 10;
int velocidade2 = 11; 

int sensorLinhaFrente = 2;
int sensorLinhaTras = 3;


 int coisa = 300;
 
void setup() {
 
   
  Serial.begin(9600);
  Wire.begin();
  
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(velocidade1, OUTPUT);
  pinMode(velocidade2, OUTPUT);
  pinMode(sensorLinhaFrente, INPUT);
  pinMode(sensorLinhaTras, INPUT);

  sensor.setTimeout(100);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();

  delay(10000);
}

void andar_frente(int vel1, int vel2){
  //Controlling speed (0 = off and 255 = max speed):
  analogWrite(velocidade1, vel1); //ENA pin
  analogWrite(velocidade2, vel2); //ENB pin
  
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void virar_esquerda(int vel1, int vel2){
   //Controlling speed (0 = off and 255 = max speed):
  analogWrite(velocidade1, vel1); //ENA pin
  analogWrite(velocidade2, vel2); //ENB pin
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}
void virar_direita(int vel1, int vel2){
   //Controlling speed (0 = off and 255 = max speed):
  analogWrite(velocidade1, vel1); //ENA pin
  analogWrite(velocidade2, vel2); //ENB pin
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}
void andar_re(int vel1,int vel2){
   //Controlling speed (0 = off and 255 = max speed):
  analogWrite(velocidade1, vel1); //ENA pin
  analogWrite(velocidade2, vel2); //ENB pin
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}


void virar_canto(){
  andar_re(255,255);
  delay(300);
  virar_esquerda(255,255);
  delay(200);
}

int le_sensor_dis(){
  return (sensor.readRangeContinuousMillimeters());
}

int le_linha_frente(){
  int aux =  digitalRead(sensorLinhaFrente);
  if (aux < coisa){
    return 1;
  }
  return 0;
}

int le_linha_tras(){
  int aux =  digitalRead(sensorLinhaTras);
  if (aux < coisa){
    return 1;
  }
  return 0;
}




void loop() {
    // ------------------- estrategia 1 ----------------------------------------------------------------------------

    //codigo aqui
   
    unsigned long time;
    
    while(!le_linha_frente()){
        while(!le_linha_frente() || !le_linha_tras()){
            andar_frente(255, 200);
        }
        
        if (le_linha_tras()){
            while(le_linha_tras()){
                andar_frente(255,255);
            }
        }
    }
    
    if (le_linha_frente()){
          while(le_linha_frente()){
              andar_re(255,255);
        }
        virar_canto();   
    }
    
    //perseguicao
    time = millis();
    while(le_sensor_dis() < coisa && millis() < time + 1000 && !le_linha_tras() &&  !le_linha_frente()){
        virar_direita(100, 100);
    }
    
    if (millis() < time + 1000){
        while(le_linha_frente() < coisa && !le_linha_tras() &&  !le_sensor_dis()){
            andar_frente(255,255);
        }
    }

    //na posicao inicial sair da reta com o outro cara ate encontrar um canto
        //codigo aqui 
    
    //apos encontrar o canto se reposicionar ()virar 180 enquando escaneia o ambiente
        //  codigo aqui
    
    // caso encontre algo, todo vapor para frente ate nao ver mais nada ou chegar em outra borda
        //codigo aqui
    
    //caso nao encontre nada, fazer um linha reta so para se mexer
       // codigo aqui

   // --------------------------------------------------------------------------------------------------------------*/

    /*andar_frente(255);
    delay(200);
    virar_esquerda(255,255);
    delay(200);
    virar_direita(255,255);
    delay(200);
    andar_re(255);
    delay(1000);

   // ;;Serial.print(le_linha_frente());
  //Serial.print(le_linha_tras());
    //Serial.print(sensor.readRangeContinuousMillimeters());
    //if (sensor.timeoutOccurred()) {
    //  Serial.print(" TIMEOUT"); 
    //}

    Serial.println();*/
}
