/*
 * This program will prompt the user a multiplication question.
 * The user has unlimited time to answer the question.
 * If the user answered correctly, the green LED will luminate.
 * If the user answered incorrectly, the red LED will luminate.
 * The yellow LED is an indicator that the program is prcoessing inputs.
 */
 
const int LED_RIGHT = 13, LED_WRONG = 12, LED_ON = 11;  //LED Display:: GREEN = LED_RIGHT :: RED = LED_WRONG :: YELLOW = LED_ON.
const int MAX_BUTTONS = 4;
int randNum1, randNum2, userAnswer;
int ansArray[MAX_BUTTONS];


class Buttons
{
  private:
    int pin;  //Pin will store the specified pin.
    int value;  //Value will hold a possible answer.
  public:
    Buttons(int pin, int value)
    {
      this->pin = pin;
      this->value = value;
      initButtons();
    }
    
    ~Buttons()
    {
    }
    
    /*
     * initButtons() 
     * Initializes the pins on the arduino board by utilizing the current object's pin value, and set it as an input pin.
     */
    void initButtons()
    {
      pinMode(this->pin, INPUT);
    }
    /*
     * isPressed()
     * Returns true if a HIGH input is read from one of the buttons. Returns false if a LOW input is read from one of the buttons.
     */
    bool isPressed()
    {
      if(digitalRead(this->pin) == HIGH)
      {
        return true;
      }
      else if(digitalRead(this->pin) == LOW)
      {
        return false;
      }
    }
    /*
     * getButtonAnswer()
     * Returns the current object's value of type int.
     */
    int getButtonAnswer()
    {
      return this->value;
    }
};

Buttons *buttonArray[MAX_BUTTONS];

void setup() {
  
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(LED_RIGHT, OUTPUT); //Pin 13 -- GREEN
  pinMode(LED_WRONG, OUTPUT); //Pin 12 -- RED
  pinMode(LED_ON, OUTPUT); //Pin 11 -- ON
  randomSeed(analogRead(0));
}

void initializations()
{
  randomizer();
  setAnswers();
  setButtons();
  prompt();
}

void loop() 
{
    initializations();
    delay(50);
    buttonPress();
    delay(2000);
}
/*
 * buttonPress() loops forever until a user presses a button. 
 * 
 */
void buttonPress()
{
  bool pressed = false;
  while(pressed == false) //This will loop forever until the user presses a button.
  {
    digitalWrite(LED_ON, HIGH);
    for(int i = 0; i < MAX_BUTTONS; i++)
    {
      if(buttonArray[i]->isPressed())
      {
        if(buttonArray[i]->getButtonAnswer() == getAnswer())
        {
          digitalWrite(LED_RIGHT, HIGH);
          delay(100);
          digitalWrite(LED_RIGHT, LOW);
          delay(100);
          Serial.println("Correct! You answered : ");
          Serial.println(buttonArray[i]->getButtonAnswer());
          digitalWrite(LED_ON, LOW);
          return;
        }
        else
        {
          digitalWrite(LED_WRONG, HIGH);
          delay(100);
          digitalWrite(LED_WRONG, LOW);
          delay(100);
          Serial.println("Incorrect! You answered : ");
          Serial.println(buttonArray[i]->getButtonAnswer());
          digitalWrite(LED_ON, LOW);
          return;
        }
      }
    }
  }
}

void setAnswers()
{
  int answer = getAnswer();
  int answerPin = random(0,4); //0 is inclusive, 4 is exclusive.
  for(int i = 0; i < MAX_BUTTONS; i++)
  {
    int notAnswer = random(0,100);
    if(i == answerPin)
    {
      ansArray[i] = answer;
    }
    else
    {
      if(notAnswer == answer) //If by any chance that notAnswer is actually the same as answer then re-randomize the number.
      {
        notAnswer = answer/2; //The chances of notAnswer being answer is still possible. So if that is the case, divide by 2.
        ansArray[i] = notAnswer;
      }
      else
      {
        ansArray[i] = notAnswer;
      }
    }
  }
}

/*
 * setButtons() will create an array of objects of type Buttons and set up the pins and values.
 */
void setButtons()
{
  for(int i = 0; i < MAX_BUTTONS; i++)
  {
    int pinNum = 4 + i; //This is to correctly assign the pins when creating the objects.
                        //i is used to insert these buttons correctly in the array from 0 -> 3.
    buttonArray[i] = new Buttons(pinNum, ansArray[i]);

  }
}

void randomizer()
{
  randNum1 = random(0,12);
  randNum2 = random(0,12);
}

void prompt()
{
  Serial.print(randNum1);
  Serial.print(" x ");
  Serial.print(randNum2);
  Serial.println(":");
  for(int i = 0; i < MAX_BUTTONS; i++)
  {
    Serial.print(" ~> ");
    Serial.println(ansArray[i]);
  }
}

int getAnswer()
{
  int answer = randNum1 * randNum2;
  return answer;
}
