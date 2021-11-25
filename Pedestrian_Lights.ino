                    //13a,12b,11c,10d,9e,8f,7g
                    //a,b,c,d,e,f,g
int digits[10][7] = {{1,1,1,1,1,1,0},//0
                     {0,1,1,0,0,0,0},//1
                     {1,1,0,1,1,0,1},//2
                     {1,1,1,1,0,0,1},//3
                     {0,1,1,0,0,1,1},//4
                     {1,0,1,1,0,1,1},//5
                     {1,0,1,1,1,1,1},//6
                     {1,1,1,0,0,0,0},//7
                     {1,1,1,1,1,1,1},//8
                     {1,1,1,1,0,1,1},//9
                    };
int digit_row = 9;
int light_state = 0; // 0 - stop; 1 - go

unsigned int startTime_display = 0; // for changing digits in 7-segment
unsigned int startTime_caution = 0; // for caution light blinking

int red_light = 3;
int yellow_light = 2; 
int green_light = 1; 

void setup() {
  Serial.begin(9600);
  for(int pin = 13; pin >= 7; pin--) {pinMode(pin, OUTPUT);} // 7-segment
  pinMode(5, OUTPUT); // buzzer
  pinMode(6, INPUT_PULLUP); // internal pull-up | for checking ground
  pinMode(red_light, OUTPUT); // red LED
  pinMode(yellow_light, OUTPUT); // yellow LED
  pinMode(green_light, OUTPUT); // green LED
}

void loop() {
  // multitask to push button at any time within time frame
  unsigned currentTime = millis();
  Serial.println(digit_row);

  segment_display(currentTime);
  
  if(light_state == 0 && digit_row >= 0) { // make if() condition when row is >= 0 && cycle is stop then *stop
    digitalWrite(red_light, HIGH);
    
  }
  else {
    light_state = 1;
    digit_row = 9;
  }
  
  if(light_state == 1 && digit_row >= 6){ // make if() condition when row is >= 6 && cycle is go THEN *go
    digitalWrite(red_light, LOW);
    digitalWrite(green_light, HIGH);    
  }
  else if(light_state == 1 && digit_row <= 5){ // make if() condition when row is <= 5 && cycle is go THEN *caution
    digitalWrite(green_light, LOW);
    // caution blink logic
    if(currentTime - startTime_caution >= 1000) startTime_caution = currentTime; // new cycle if 1000 millis
    if(digit_row < 9 && currentTime - startTime_caution <= 500) digitalWrite(yellow_light, HIGH); // within the 500 millis in the caution cycle, turn it on
    else digitalWrite(yellow_light, LOW);
  }
  else {
    light_state == 0;
  }
    

  // make if() condition when button is pushed in stop state
  
}

void segment_display(int currentTime) {
  if(currentTime - startTime_display >= 1000){ // change digit if 1000 millis has passed
    startTime_display = currentTime; // we do this because we can't reset currentTime
    for(int section = 13; section >= 7; section--) digitalWrite(section, digits[digit_row][13-section]); // for loop so we skip 1-by-1 light setting
    digit_row--;
  }
}
