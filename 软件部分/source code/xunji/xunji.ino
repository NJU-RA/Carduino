#define Vo 130// Vo(0-255)
#define k  0.85//k  (0-10)
int IN[4]={5,3,6,9};
int p1,p2,p;
int last_proportional = 0;
long integral = 0;
int proportional,derivative,power_difference;
//int maxspeed=200;
int readl(){           //read 
  p1=analogRead(A6);
  p2=analogRead(A5);
  p=p1-p2;
  return p;
}
void motor(int speed2,int speed1){ //speed1 right,speed2 left
  int s1,s2,s3,s4;
  if(speed1>0){
    s1=0;
    s2=1;
  }
  else{
    s1=1;
    s2=0;
  }
  digitalWrite(IN[s1],LOW);
  analogWrite(IN[s2],abs(speed1));
  if(speed2>0){
    s3=2;
    s4=3;
  }
  else{
    s3=3;
    s4=2;
  }
  digitalWrite(IN[s3],LOW);
  analogWrite(IN[s4],abs(speed2));
}
void pid(int max_speed){
  proportional = readl();
  derivative = proportional-last_proportional;
  integral+= proportional;
  last_proportional = proportional;
  power_difference = proportional*k;// + integral/20000 + derivative*3/4;
//power_difference = proportional*5;
  if(power_difference > max_speed)
  power_difference = max_speed;
  if(power_difference < -max_speed)
  power_difference = -max_speed;
  if(power_difference<0)
  motor((max_speed+power_difference),max_speed);
  else
  motor(max_speed,(max_speed-power_difference));
}
void setup() {
  // put your setup code here, to run once:
pinMode(IN[0],OUTPUT);
pinMode(IN[1],OUTPUT);
pinMode(IN[2],OUTPUT);
pinMode(IN[3],OUTPUT);
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
   pid(Vo);
}
