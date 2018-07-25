
/* Initalizing the array length/array/difficulty arr/difficulty viarable */
const int arr_length = 40;
int arr[arr_length];
int difficulty_arr[5] = {500, 400, 300, 200, 100};
int difficulty = 0;

/* Initalizing the tone array */
int tone_arr[5] = {700, 600, 500, 300, 200};

/* Initalizing the level and state */
int level = 1;
int state = 1;

/* Initalizing LED's */
int led1 = 10;
int led2 = 11;
int led3 = 12;
int led4 = 13;

void setup() {
  /* Void Setup will initalize the inputs/outputs 
  for LED's and pushbuttons, it will then run a while loop that 
  will not stop untill the red button was held down */
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  /* LED pattern and tone untill the user holds down the 
  red button to start the game */
  while(digitalRead(A0) != HIGH){
  digitalWrite(led1, HIGH);
  tone(2, tone_arr[1], 500);
  delay(150);
  digitalWrite(led1, LOW);
  
  digitalWrite(led2, HIGH);
  tone(2, tone_arr[2], 500);
  delay(150);
  digitalWrite(led2, LOW);
  
  digitalWrite(led3, HIGH);
  tone(2, tone_arr[3], 500);
  delay(150);
  digitalWrite(led3, LOW);
    
  digitalWrite(led4, HIGH);
  tone(2, tone_arr[4], 500);
  delay(150);
  digitalWrite(led4, LOW);
  
  digitalWrite(led3, HIGH);
  tone(2, tone_arr[3], 500);
  delay(150);
  digitalWrite(led3, LOW);
  
  digitalWrite(led2, HIGH);
  tone(2, tone_arr[2], 500);
  delay(150);
  digitalWrite(led2, LOW);}

  /* this for loop will start after the break after the start button 
  was held down */
  for (int i = 0; i < 3; i++ ) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(2, 250, 500);
  delay(200);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(400);
  }
}

void loop() {
  /* loop will endlessly run the Simon Says program
  based on the state, */
  if (state == 1) { 
    level = 1;
    get_difficulty(); /* Initalizes the difficulty */
    start_state(); /* Initalizes the random array */
    state = 2; 
  }
  else if (state == 2){
    show_pattern(); /* Shows pattern */
    state = 3; 
  }
  else if (state == 3){
    get_sequence(); /* Gets user input */
  }
}

void get_difficulty() {
  /* will reset the difficulty to zero
  turn all lights on and wait for user to select difficulty */
  difficulty = 0;
  while(difficulty == 0){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    if(digitalRead(A0) == HIGH){ /* Lowest difficulty selected */
      difficulty = 1;
      digitalWrite(led1, LOW);
      tone(2, tone_arr[1], 200);
      delay(200);
    }
    else if(digitalRead(A1) == HIGH){ /* Second Lowest difficulty selected */
      difficulty = 2;
      digitalWrite(led2, LOW);
      tone(2, tone_arr[2], 200);
      delay(200);
    }
    else if(digitalRead(A2) == HIGH){ /* Second to Highest difficulty selected */
      difficulty = 3;
      digitalWrite(led3, LOW);
      tone(2, tone_arr[3], 200);
      delay(200);
    }
    else if(digitalRead(A3) == HIGH){ /* Highest difficulty selected */
      difficulty = 4;
      digitalWrite(led4, LOW);
      tone(2, tone_arr[4], 200);
      delay(200);
    }
  }
  /* turn off all LED's */
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(200);
}

void start_state() {
  /* start_state will fill the array of all 0's to be an 
  array of random numbers between 10 and 13 */
  for (int i = 0; i < arr_length; i++ ) {
    randomSeed(analogRead(3));
    arr[i] = random(10,14);/* set element at location i random (10-13) */
  } 
}

void show_pattern() {
  /* show_pattern will show the current pattern up untill the current level 
  the user is on */
  delay(250);
  int n = 0;
  while(n < level){
    digitalWrite(arr[ n ], HIGH);
    tone(2, tone_arr[arr[ n ]-9], difficulty_arr[difficulty]);
    delay(difficulty_arr[difficulty]);
    digitalWrite(arr[ n ], LOW);
    delay(200);
    n++;
  }
} 

void get_sequence() {
  /* need while to keep track of where in the array the user is compared to the level */ 
  /* if at any time the index and button press dont match up break loop and call restart funnction */ 
  int i = 0;
  while(i < level){
  if(digitalRead(A3) == HIGH){ /* Green LED was pressed */
    digitalWrite(13, HIGH);
    tone(2, tone_arr[arr[ i ]-9], 100);
    delay(100);
    digitalWrite(13, LOW);
    if(arr[i] != 13){ /* Incorrect pattern sequence */
      incorrect_pattern();
      return;
    }
    i++;
    delay(100);
  }
  if(digitalRead(A2) == HIGH){  /* Yellow LED was pressed */
    digitalWrite(12, HIGH);
    tone(2, tone_arr[arr[ i ]-9], 100);
    delay(100);
    digitalWrite(12, LOW);
    if(arr[i] != 12){ /* Incorrect pattern sequence */
      incorrect_pattern();
      return;
    }
    i++;
    delay(100);
  }
  if(digitalRead(A1) == HIGH){ /* Blue LED was pressed */
    digitalWrite(11, HIGH);
    tone(2, tone_arr[arr[ i ]-9], 100);
    delay(100);
    digitalWrite(11, LOW);
    if(arr[i] != 11){ /* Incorrect pattern sequence */
      incorrect_pattern();
      return;
    }
    i++;
    delay(100);
  }
  if(digitalRead(A0) == HIGH){ /* Red LED was pressed */
    digitalWrite(10, HIGH);
    tone(2, tone_arr[arr[ i ]-9], 100);
    delay(100);
    digitalWrite(10, LOW);
    if(arr[i] != 10){ /* Incorrect pattern sequence */
      incorrect_pattern();
      return;
    }
    i++;
    delay(100);
  }
  }
  delay(100);
  for (int i = 0; i < 3; i++ ) { /* Correct pattern LED sequence */
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(2, 800, 100);
  delay(100);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(100);
  }
  /* Incriment the Level and reshow the pattern */
  level++;
  show_pattern();
}

void incorrect_pattern(){
  /* incorrect_pattern will flash all LED's three times slowly
  and play a low tone */
  delay(250);
  level = 1;
  state = 1;
  
  for (int i = 0; i < 3; i++ ) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(2, 100, 500);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(400);
  }
}
