#include <LiquidCrystal.h>

#define ENABLE 13
#define pGas A5
#define pPir 7
#define pTemp A3
//Pinos Leds
#define Verde 8
#define Azul 9
#define Vermelho 10 
//Pino Potenciometro Ngas
#define limiteSuperior A1
#define limiteInferior A0


int enable = 0;


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Monitoramento :");
  pinMode(pPir,INPUT);
  pinMode(Verde,OUTPUT);
  pinMode(Vermelho,OUTPUT);
  pinMode(Azul,OUTPUT);
  
   Serial.begin(9600);
}

void loop() {
 
  
  //leitura sensor gas
  limpa_tela();
  lcd.print("GAS:  ");
  leituragas();	
  //Leitura de presenca
  limpa_tela();
  lcd.print("Estado: ");
  presenca();
  
  //Leitura temperatura
  limpa_tela();
  lcd.print("Temp: ");
  temperatura();
  lcd.print(" °C");
  delay(100);
  
}

void limpa_tela(){
 delay(1500);
 lcd.setCursor(0,1);
 lcd.print("                ");
 lcd.setCursor(0,1); 
}


//ler o nivel de gas do ambiente
 
void leituragas(){
  
  
   //DefineValorMax
  
  float valorMax;
  valorMax = analogRead(limiteSuperior);
  valorMax=map(valorMax,0,1023,0,100); 
  Serial.println("Valor Maximo");
  Serial.println(valorMax);
  
  //DefineValorMin
  
  float valorMin;
  valorMin = analogRead(limiteInferior);
  valorMin=map(valorMin,0,1023,0,100);
  Serial.println("ValorMinimo");
  Serial.println(valorMin);
  
  
  
  //gas
  int sinalGas=analogRead(pGas);
  sinalGas=map(sinalGas,300,750,0,100);
  
  
   enable = digitalRead(ENABLE);
  
  
  if(enable){
     if(sinalGas>=0 && sinalGas<=valorMin){
    digitalWrite(Vermelho,LOW);
    digitalWrite(Verde,HIGH);//Led Verde
    digitalWrite(Azul,LOW);
     analogWrite(6, LOW);
  }else if(sinalGas>valorMin && sinalGas<=valorMax){
   	digitalWrite(Vermelho,HIGH);//led Amarelo
    digitalWrite(Verde,HIGH);
    digitalWrite(Azul,LOW);
    analogWrite(6, HIGH);
    delay(999);
    analogWrite(6, LOW);
  }else {
    analogWrite(6, HIGH);
    digitalWrite(Vermelho,HIGH);// Led Vermelho
    digitalWrite(Verde,LOW);
    digitalWrite(Azul,LOW);
      
    }
  }else{
    digitalWrite(Verde,LOW);
    digitalWrite(Azul,LOW);
    digitalWrite(Verde,LOW);
    digitalWrite(Vermelho,LOW);
    analogWrite(6, LOW);
    lcd.print("sensor desli");
  
    
  }
  
  lcd.print(sinalGas);
  Serial.print("Nivel Gas: ");
  Serial.println(sinalGas);
}

//verifica se tem pessoas no ambiente

void presenca(){
  int sinalPir=digitalRead(pPir);
  Serial.print("Presenca: ");
  Serial.println(sinalPir);
  if(sinalPir==1)
    lcd.print("Em uso");
    
  else
    lcd.print("Vazio");
    
}

//ler a temperatura do ambiente
void temperatura(){
  float sinalTemp=analogRead(pTemp)*5;
  float TempC=((sinalTemp/1023)-0.5)*100;
  lcd.print(TempC);
  Serial.print("Temperatura: ");
  Serial.println(TempC);
  
}






