int flag = 1, ar[200] = {}, a0, i = 0;
int ldr = A0;
int cutoff = 500;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ldr, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag){
    while(i != 200){
      ar[i++] = getbit();
      delay(50);
      //Serial.println(ar[i-1]);
    }
    int a1 = 0, flag1 = 0;
    
    for(int j = 0; j<200; j++){
      for(int k = j; k<(j+8); k++){
        a1 += (1<<(7-k))*(ar[k]);
      }
      if(a1 == 33){
        flag1 = 1;
        j = 200;
      }
    }
    if(flag1){
      Serial.println("YES");
    }else{
      Serial.println("NO");
    }
    flag--;
  }
}

int getbit(){
  if(analogRead(ldr) > cutoff){
    return 1;
  }
  return 0;
}
