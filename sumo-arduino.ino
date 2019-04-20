#define borda 2 
#define trigger 13   
#define echo 12 
#define IN1 2 
#define IN2 4 
#define IN3 6 
#define IN4 7 

#define velocidadeA 3
#define velocidadeB 5


 typedef struct Timer  
 {  
   unsigned long start;
   unsigned long timeout;  
 };  
 unsigned long Now ( void )  
 {  
   return millis ( );// Retorna os milisegundos depois do reset  
 }  
 boolean TimerEstorou (struct Timer * timer)  
 {  
   // Verifica se o timer estourou  
   if ( Now () > timer->start + timer->timeout) {  
     return true;  
   }  
   return false;   
 }  
 
 void timerStart(struct Timer * timer){  
   timer->start = Now();  
 }  
 void timerDesloc(struct Timer * timer, unsigned long tempo){  
  timer->start = Now()+tempo;  
 }  
 Timer timerBorda = {0, 10}; // Verifica se achou a borda a cada 10 milisegundos  
 Timer timerAchou = {0, 100}; // Verifica se achou o oponente a cada 100 milisegundos  
 Timer timerFrente = {0, 800}; // Tempo que o robô passa indo pra frente  
 Timer timerGira = {0, 3243}; // Tempo que o robô passa girando
 Timer timerfinal = {0, 85000}; // Tempo de 1:30 minutos de round 
 boolean sentidoGiro=true; //variável criada para o robô girar hora pra direita, hora pra esquerda  

 void setup(){  
  
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);  
  pinMode(velocidadeA, OUTPUT);
  pinMode(velocidadeB, OUTPUT);
  pinMode(trigger, OUTPUT);  
  pinMode(borda, INPUT);  
  pinMode(echo, INPUT);  
  
  parado();  
  delay(5000); // Aguarda 5 segundos no inicio do round 
  timerFrente.start= Now() - timerFrente.timeout; 
  timerGira.start= Now();  
  timerAchou.start= Now();  
 }  
 int i=0;  
 void loop(){  
 if(TimerEstorou(&timerfinal)){  
  while(1)  
   parado(); // Para o robô ao final de cada round
 }  
 if(i=0)  
 {  
  timerStart(&timerBorda);  
  timerStart(&timerGira);  
  timerStart(&timerAchou);  
  i+=1;  
 }  
 if(TimerEstorou(& timerFrente)){  
  andaFrente();  
  timerStart(& timerFrente);  
  //timerStart(& timerGira);  
 }  
 if(TimerEstorou(& timerBorda)){  
  if(!digitalRead(borda)){ // Verifica se encontrou a borda
   andaTras();  
   delay(1000);//delay de sobrevivência  
   timerStart(& timerFrente);// Reinicia o timer 
   timerDesloc(& timerGira, -timerGira.timeout);// Giro 
   timerStart(& timerAchou);  
  }  
  timerStart(& timerBorda);  
 }  

 if(TimerEstorou(& timerAchou)){  
  if(achou()){  
   andaFrente();  
   timerStart(& timerGira);  
  }  
  timerStart(& timerAchou);  
 }  
 if(TimerEstorou(& timerGira)){  
  if(sentidoGiro){  
   giraDireita();  
   sentidoGiro=!sentidoGiro;  
  }  
  else  
  {  
   giraEsquerda();  
   sentidoGiro=!sentidoGiro;  
  }  
  timerStart(& timerGira);  
 }  
 }  

 void andaFrente(v){ 
  analogWrite(velocidadeA, v); 
  analogWrite(velocidadeB, v);
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW);  
 }  
 void andaTras(v){  
  analogWrite(velocidadeA, v); 
  analogWrite(velocidadeB, v);
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW); 
 }  
 void parado(v){  
  analogWrite(velocidadeA, v); 
  analogWrite(velocidadeB, v);
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW); 
 }  
 void giraDireita(v){  
  analogWrite(velocidadeA, v); 
  analogWrite(velocidadeB, v);
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW);
 }  
 void giraEsquerda(v){  
  analogWrite(velocidadeA, v); 
  analogWrite(velocidadeB, v);
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW);
 }  

 float distancia() {  
  float tempo, dist;  
  digitalWrite(trigger, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigger, HIGH);  
  delayMicroseconds(10);  
  tempo = pulseIn(echo, HIGH);  
  dist = (((tempo/2) * 350)/1000000);  
  dist *= 100;  
  return dist;  
 }  
 boolean achou(){  
  if (distancia()<50)  
   return true;  
  else  
   return false;  
 }  
