# Interactive_Multiplication
This is an interactable multiplication game made on the Arduino IDE.

# Author's Note:
I created this for the sole purpose of learning how to program on an Arduino and practicing object oriented programming to assign objects to buttons.
If you see anything that can be improved or have any tips (including this readme file), I would greatly appreciate any sort of feedback.

### Summary:
This program's purpose is to be an interactable math game.
The system will prompt the user a multiplication problem and give them 4 possible answers to choose from.
This would be visually displayed through the serial monitor in the Arduino IDE.
The system will wait for the user's input from the buttons with a yellow LED inidicating that it is waiting for input.
If the user presses the correct button, a green LED will luminate.
If the user presses the wrong button, a red LED will luminate.

### Materials needed:
- Arduino Uno or any board that can utilize Serial - 1 (Click [here](https://www.arduino.cc/reference/en/language/functions/communication/serial/) to check which type of Serial you would have to use for this program.)
- Breadboard - 1
- 1kΩ resistors - 7
- LED - 7
- Any USB that is compatible with your Arduino that can be connected to a computer.
- A computer.

### Diagram:
![here](https://github.com/VueChu/Interactable-Multiplication/blob/main/MathGameDiagram.png)
### ---Button class---
- ### ATTRIBUTES
	- ```int pin```
      - Pin will store the specified pin.

	- ```int value```
		- Value will hold a possible answer.

-	### CONSTRUCTOR
    - ```Buttons(int pin, int value)```
    
      - Instantiates the Buttons class by taking in pin and value.

- ### FUNCTIONS
  - ```void initButtons()```
  
	  - Initializes the pins on the arduino board by utilizing the current object's pin value, and set it as an input pin.

  - ```bool isPresed()```
  
    - Returns true if a HIGH input is read from one of the buttons. Returns false if a LOW input is read from one of the buttons.

  - ```int getButtonAnswer()```

    - Returns the current object's value of type int.

### ---End of Button class---
### GLOBAL VARIABLES WORTH MENTIONING

- ```Buttons *buttonArray[MAX_BUTTONS]```

  - buttonArray is a pointer and used as an array of objects of type Buttons.

### FUNCTIONS
- ```void initializations()```

  - Initializes/Reinitializes randNum1, randNum2, and the answer positions.

- ```void buttonPress()```
  
  - Loops forever until an input signal is read as a HIGH from any of the buttons. 

- ```void setAnswers()```

  - Randomly select an index that will contain the correct answer. All of the other indexes will have randomly generated answers, whereas the index with the correct answer will be retrieved from the function getAnswer().

- ```void setButtons()```

  - Populates the buttonsArray by instantiating the Buttons class.

- ```void randomizer()```

  - Randomize global variables of type int, randNum1 and randNum2, numbers between 0 through 11. (0,12). 

- ```void prompt()```

  - Outputs to the serial monitor a multiplication problem and 4 possible answers to choose from.

- ```int getAnswer()```

  - Returns the product of randNum1 and randNum2 of type int.

