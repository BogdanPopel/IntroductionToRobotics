# IntroductionToRobotics
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

# Homework no.1

## RGB LED CONTROLLED BY DIGITAL ELECTRONICS


### TASKS:
•Components: 1 RBG LED, 3 Potentiometers, Resistors and Wires (per logic).

•Technical Task: Use a separate potentiometer in controlling each of the colors of the RGB LED (Red, Green and Blue). The control must be done with digital electronics.

•Coding task: Coding style is of utmost importance.

### SEE IT IN ACTION:

#### The [code](https://github.com/BogdanPopel/IntroductionToRobotics/blob/main/Tema%201%20-%20RGBwithPotentiometers.ino) for this build can be found here.

#### [Video demonstration](https://www.youtube.com/watch?v=3S08bdfMk_I)

#### [This](https://youtu.be/3S08bdfMk_I?t=61) is how it looks in lower light conditions.

The circuit is a fragile build, due to imperfect connections between the cables, potentiometers and the breadboard. Therefore, any movement may cause flickering in the LED. To see this, check out [this part of the demo](https://youtu.be/3S08bdfMk_I?t=117).
<details>
<summary>This what the end product looks like:</summary>

![WhatsApp Image 2022-10-26 at 18 36 58](https://user-images.githubusercontent.com/79463256/198071657-169fc7c2-7aa7-4970-a026-ca6d22fd3b43.jpeg)
![WhatsApp Image 2022-10-26 at 18 36 55](https://user-images.githubusercontent.com/79463256/198071709-af636a55-08df-4f6a-be0e-233ffaf9b658.jpeg)
![WhatsApp Image 2022-10-26 at 18 36 55 (1)](https://user-images.githubusercontent.com/79463256/198071793-ae9c3136-dc80-4733-a8b5-42718f0aa811.jpeg)
![WhatsApp Image 2022-10-26 at 18 36 55 (2)](https://user-images.githubusercontent.com/79463256/198071815-6d67d5b4-e5ab-4c65-b0a5-b7b7dba22e36.jpeg)
![WhatsApp Image 2022-10-26 at 18 36 56 (1)](https://user-images.githubusercontent.com/79463256/198071875-20bc3688-e63f-4feb-baf8-a5fe48c9951d.jpeg)
![WhatsApp Image 2022-10-26 at 18 36 57](https://user-images.githubusercontent.com/79463256/198071913-9f5cd657-c2e3-42a0-ab5e-ee9bdd211af7.jpeg)
![WhatsApp Image 2022-10-26 at 18 36 57 (1)](https://user-images.githubusercontent.com/79463256/198071951-1e2a4617-7835-4fa4-b8de-ee1e91c1ba7d.jpeg)
![WhatsApp Image 2022-10-26 at 18 36 58 (1)](https://user-images.githubusercontent.com/79463256/198072006-c493859b-4a56-4949-aed9-861040026a62.jpeg)
![WhatsApp Image 2022-10-26 at 18 36 56 (2)](https://user-images.githubusercontent.com/79463256/198073066-4761468c-8f01-47cd-8a10-6755b49cb567.jpeg)
</details>

# Homework no.2 

## Traffic Lights with Audio Feedback

### Tasks:

•Components:  5 LEDs, 1 Button, 1 Buzzer, Resistors and Wires (per logic)

•Technical Task: Building  the  traffic  lights  for  a  crosswalk. 2 LEDs are used to represent the traffic lights for people and 3 for the traffic lights for cars. Also, a buzzer is used to signal to the pedestrians when the light goes green and also it starts buzzing faster when it's about to go red, along with the flashing of the green LED.

•Coding task: Coding style is of utmost importance.

  The system encapsulates 4 states that it goes through, consecutively:
  
1) green light for cars, red  light for people, no sounds. Duration: indefinite, changed by pressing the button.
2) (initiated by counting down 8 seconds after a button press): the light should be yellow for  cars, red for people and no sounds. Duration: 3 seconds.
3) (initiated after state 2 ends): red for cars, green for pedestrians and a beeping sound from the buzzer at a constant interval. Duration: 8 seconds.
4) (initiated after state 3 ends):  red for cars, blinking green for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3. This state should last 4 seconds. After the final state, the system should return to state 1 until the button is pressed again.
Important to know: Pressing the button in any state other than state 1 should NOT yield any actions.

<details>
<summary>How should the input of a button be read?</summary>

  The input is registered via a ISR() function called Interrupt, which receives the signal from a button. The signal is then debounced, to be sure it didn't register from interferences or a 'half push' of the button. Esentially, it makes sure that the user pushed the button on purpose and that the push of the button was well executed, resulting in a continous signal. Arduino reads 0s and 1s from the button. To understand it better, you can view the signal recieved from a button like this:
  
  - bad signal: 1 1 0 0 1 1 0 0 (with ISR) -> we skip reading this part
  - good signal: 1 1 1 1 1 1 1 -> we consider the button pressed, when it sends a signal that looks like this
</details>

### SEE IT IN ACTION:

#### The [code](https://github.com/BogdanPopel/IntroductionToRobotics/blob/main/TrafficLight.ino) is here.
#### [Video demonstration](https://youtu.be/PXnF78SRz44)

<details>
<summary>This what the end product looks like:</summary>

![WhatsApp Image 2022-11-03 at 00 45 04](https://user-images.githubusercontent.com/79463256/199616720-2daaf8ba-8761-4873-8160-88ad13662cf7.jpeg)

![WhatsApp Image 2022-11-03 at 00 45 06](https://user-images.githubusercontent.com/79463256/199616724-a1717c5c-2d5a-4a12-be2a-86b7c10420dc.jpeg)

![WhatsApp Image 2022-11-03 at 00 45 05 (2)](https://user-images.githubusercontent.com/79463256/199616728-2c6205c7-51ca-481f-8bc8-fbefc14eb5f1.jpeg)

![WhatsApp Image 2022-11-03 at 00 45 05 (1)](https://user-images.githubusercontent.com/79463256/199616730-5647d9c7-e186-445e-9076-f4bbee9165c8.jpeg)

![WhatsApp Image 2022-11-03 at 00 45 05](https://user-images.githubusercontent.com/79463256/199616731-3054c80e-ab3d-4f10-8112-0e874d6e90d5.jpeg)
</details>


# Homework no.3

## 7 Segment Display Controlled By Joystick

### Tasks:

•Components:   1  Seven Segment Display (Common Cathode in my case), 1  Joystick,  Resistors and Wires (per logic)

•Technical Task: This task involves taking control of each segment by moving between them via the joystick, rendering each one of them on or off, by choice. Essentially, I am drawing on the display with a joystick, being able to render each segment on or off. The movement between the segments is meant to feel as natural as possible. Also, I am able to 'reset' the display by pressing down on the joystick for a minimum of 3 seconds, meaning that all the segments are turned off and the controlled segment becomes the DP (decimal point). 

•Coding task: Coding style is of utmost importance.

  The system encapsulates 2 states that it goes through, changed by the push of a button:
  
1) default, but also initiated after a button press in State 2: Current position (segment) is blinking. The joystick can be used to move to the segment's neighbours. Short pressing the  button toggles the second state. Long pressing the button in state 1 resets the entire display by turning all the segments OFF and moving the current position to the decimal point.
2) initiated after a button press in State 1: The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the X axis changes the segment state  from ON to OFF or from OFF to  ON. Clicking the joystick should save the segment state and exit back to state 1.

  These are the allowed transitions between the segments:
  [Code Representation](https://github.com/BogdanPopel/IntroductionToRobotics/blob/4b84fe34710972f7cb5cabef7e2bfc3be2698b8d/Homework%233%207SDwithJoystick.ino#L58)
  
  ![tranzitii](https://user-images.githubusercontent.com/79463256/200967395-16e1aadd-9c16-4e8d-8f01-21188fe225b1.png)

  
### SEE IT IN ACTION:

#### The [code](https://github.com/BogdanPopel/IntroductionToRobotics/blob/main/Homework%233%207SDwithJoystick.ino) is here.
#### [Video demonstration](https://www.youtube.com/watch?v=h8aT8BLyIBo)

<details>
<summary>This what the end product looks like:</summary>

![WhatsApp Image 2022-11-10 at 01 43 22 (1)](https://user-images.githubusercontent.com/79463256/200965850-fc124e7a-2e42-4714-80e9-273b2ac0a7aa.jpeg)

![WhatsApp Image 2022-11-10 at 01 43 22](https://user-images.githubusercontent.com/79463256/200965868-87731b46-e704-47bd-86e5-fe83e84b1239.jpeg)

![WhatsApp Image 2022-11-10 at 01 43 21 (2)](https://user-images.githubusercontent.com/79463256/200965881-016658c4-4f35-43a7-9d31-c995dc28477a.jpeg)

![WhatsApp Image 2022-11-10 at 01 43 21 (1)](https://user-images.githubusercontent.com/79463256/200965909-e63b2ed5-94df-4afe-8218-65548b65d9b3.jpeg)

![WhatsApp Image 2022-11-10 at 01 43 21](https://user-images.githubusercontent.com/79463256/200965941-8722d15f-26c7-48cc-a78f-5f2ddabed283.jpeg)

![WhatsApp Image 2022-11-10 at 01 43 20](https://user-images.githubusercontent.com/79463256/200965953-b90542c5-101b-4b11-8c41-612872c4530d.jpeg)
</details>
