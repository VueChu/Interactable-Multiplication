/*
 * This program will prompt the user a multiplication question.
 * The user has unlimited time to answer the question.
 * If the user answered correctly, the green LED will luminate.
 * If the user answered incorrectly, the red LED will luminate.
 * The yellow LED is an indicator that the program is prcoessing inputs.
 */
 
String stringVar;
const int LED_RIGHT = 13, LED_WRONG = 12, LED_ON = 11;  //LED Display:: GREEN = LED_RIGHT :: RED = LED_WRONG :: YELLOW = LED_ON.
const int MAX_BUTTONS = 4;
int randNum1, randNum2, userAnswer;
int ansArray[MAX_BUTTONS];


class Buttons
{
  private:
    int pin, value;
    bool pressed;
  public:
    Buttons(int pin, int value)
    {
      this->pin = pin;
      this->value = value;
      this->pressed = false;  //Don't think we need this.
      initButtons();
    }

    void initButtons()
    {
      pinMode(this->pin, INPUT);
    }

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
        notAnswer = answer/2;
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
    buttonArray[i] = new Buttons(pinNum, ansArray[i]); //Creating objects //This is creating a memory leak I assume. 
    //Maybe it isn't because it's an array, and their indexes have a fixed memory address. So maybe when recreating these objects in these indexes it's just overwriting the data inside of them with the new data.
    //Check with visual studios and have it print out the memory addresses of an array of objects similar to this.
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
