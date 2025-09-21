/*
This is a quiz game. 4 Buttons which equal answers A,B,C,D. Buzzer returns if the answer is wrong or correct.
*/

#define Correct 100
#define Wrong 1000

char questions[][100] = {"What city is known as The Eternal City ?", 
                    "In which country would you find Mount Kilimanjaro?",
                    "True or false: Halloween originated as an ancient Irish festival",
                    "What is the largest Spanish-speaking city in the world?",
                    "Which country has the most islands?"};

char answers[][100] = {"A) Plovdiv B) Rome C) Sofia D) Turkey",
                  "A) China B) Bulgaria C) Turkey D) Tanzania",
                  "A) True B) False",
                  "A) Mexico City B) Bulgaria C) Romania D) Sofia",
                  "A) Bulgaria B) Singapore C) Turkey D) Sweden"};

int correct_answers[] = {2, 4, 1, 1, 4};
char buttons[] = {1,2,3,4};

int question_num = 0;
const byte Buzz = 9;
const byte ButtonA = 2;
const byte ButtonB = 3;
const byte ButtonC = 4;
const byte ButtonD = 5;

const byte allButtons[] = {ButtonA, ButtonB, ButtonC, ButtonD};

void print_question();
void check_answer(int answer);

void setup(){
  pinMode(Buzz, OUTPUT);
  for (int i = 0; i < 4; i++){
    pinMode(allButtons[i], INPUT_PULLUP);
  }
  Serial.begin(115200);
}

void loop(){
  int answer = 1;
  print_question();
  while (answer == 1){
    for (int i = 0; i < 4; i++){
      answer = digitalRead(allButtons[i]);
      if (answer == 0){
        check_answer(i);
        break;
      }
    }
  }
  question_num++;
  if (question_num == 4)
    question_num = 0;
}

void print_question(){
  Serial.println(questions[question_num]);
  Serial.println(answers[question_num]);
}

void check_answer(int butNum){
  if ((butNum+1) == correct_answers[question_num]){
    tone(Buzz, Correct); 
  }
  else{
    tone(Buzz, Wrong);
  }
  delay(1000);
  noTone(Buzz);
}



