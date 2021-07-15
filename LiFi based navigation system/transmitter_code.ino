int led = 9;
int a1, a2;
int dly = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
int flag = 1;
void loop() {
  // put your main code here, to run repeatedly:
  String incoming;
  int b1;
  char b[9] = "!ABCDEFG!";
  
  if(flag == 1){
      for(int j = 0; j<1; j++){
          b1 = b[j];
          int a = b1, ba1 = 0;
          int ar[8] = {}, k = 0;
          Serial.println(a); 
          for(int k = 0; k<8; k++){
          if(a&1){
            analogWrite(9, 255);
            delay(dly);
            analogWrite(led, 0);
          }else{
            analogWrite(led, 0);
            delay(dly);
            analogWrite(led, 0);
          }
          a >>= 1;
        /*
          if(a2 < 600){
            ar[k++] = 0;
          }else{
            ar[k++] = 1;
          }
          */
        }

       /*
        for(int i = 7; i>=0; i--){
            Serial.println(ar[i]);
           ba1 += ((1<<i)*ar[i]);
        }

        Serial.println(ba1);
      */
      }
  }
      //a1 = analogRead(A0);
      //Serial.println(a1);
}
