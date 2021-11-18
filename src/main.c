// Sample code for ECE 198

// Written by Bernie Roehl, August 2021

// This file contains code for a number of different examples.
// Each one is surrounded by an #ifdef ... #endif block inside of main().

// To run a particular example, you should remove the comment (//) in
// front of exactly ONE of the following lines:

// #define BUTTON_BLINK
// #define LIGHT_SCHEDULER
// #define TIME_RAND
// #define KEYPAD
// #define KEYPAD_CONTROL
// #define SEVEN_SEGMENT
// #define KEYPAD_SEVEN_SEGMENT
// #define COLOR_LED
// #define ROTARY_ENCODER
// #define ANALOG
// #define PWM

//Tip the Tins Helper Functions 
#define RAND_QUEST  
// #define DISTANCE_1  
// #define DISTANCE_2  
// #define DISTANCE_3  
// #define DISTANCE_4  
// #define ANSWER      

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

#include "LiquidCrystal.h"

// float get_distance();
void CHECK_PIN();
void LED();

bool answer;
size_t count;

char buff[100];

//definitions to move to top 
int Ticks;
const float speed_of_sound = 0.0343/2;
int distance = 6;
char buff[100];
#include <string.h>



//the following code is just to test the LED and CHECK_PIN, if you change the values the corresponding light will turn on!
int player_array[4];
int correct_array[4];

int main(void)
{
   
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    InitializePin(GPIOC, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_NOPULL, 0);
    
   
    while(1){
        sprintf(buff, "distance (cm) =  %d\n", get_distance());
        SerialPuts(buff);

        HAL_Delay(1000);
    }
   
   
    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)
/*
Program Description: 
- When the game starts, RAND_QUEST runs to generate a random question which will be output into a LCD display: 
Questions generated are multiple choices with A, B, C, D as answers which correspond to the PIN numbers 1, 2, 3, 4. 
- The program will then repeatedly check the DISTANCE_1, DISTANCE_2, DISTANCE_3, DISTANCE_4.
- These four functions will read the distance received from the sensors and return a boolean variable indicating whether there has been a change in distance. 
Change in distance means the tin can is knocked down which determines the player's answer to the question. 
- When a sensor returns a false variable, function ANSWER will store the answer into an array of type int. 
- The Program repeated 3 more times until 4 questions have been answered. At this point, the player will have an array of answers
that will be run by CHECK_PIN. 
- CHECK_PIN stores an array that corresponds to the correct answers to the 4 questions. 
CHECK_PIN returns a boolean variable upon checking if the player's array of answers is equal to the correct array. 
- If CHECK_PIN is true, the pin will be displayed and LED will turn green. If CHECK_PIN is false, a life will be lost and LED will turn red
*/
#ifdef RAND_QUEST
// Generates a random question with correct answer 
int rand_num;
srand(HAL_GetTick());
printf("The randomly generated number is ");

rand_num = rand()%30;

switch (rand_num) 
{
case 1 : 
printf("Question: How many championship title has the raptor won ?\n ");
printf("A:3\n ");
printf("B:1\n ");
printf("C:2\n ");
printf("D:0\n ");
correct_array[count] = 2;

case 2 : 
printf("Question: The American Falls and Horseshoe Falls are better known as?\n ");
printf("A: Rainbow falls\n ");
printf("B: Niagara falls\n ");
printf("C: Union falls\n ");
printf("D: Yosemite falls\n ");
correct_array[count] = 2;

case 3 : 
printf("Question: Whose nickname was the Wizard of Menlo Park?\n ");
printf("A:Voldemort\n ");
printf("B:Albus Dumbledore\n ");
printf("C:Gandalf\n ");
printf("D:Thomas Edison\n ");
correct_array[count] = 4;

case 4 : 
printf("Question: What animals are pearls found in?\n ");
printf("A:Seals\n ");
printf("B:Whales\n ");
printf("C:Oysters\n ");
printf("D:Corals\n ");
correct_array[count] = 3;

case 5 : 
printf("Question: Which cartoon character lives in a pineapple under the sea?\n ");
printf("A:Spongebob Squarepants\n ");
printf("B:Rick\n ");
printf("C:Phineas\n ");
printf("D:Elsa\n ");
correct_array[count] = 1;

case 6 : 
printf("Question: How many soccer players should each team have on the field at the start of each match?\n ");
printf("A:9\n ");
printf("B:10\n ");
printf("C:21\n ");
printf("D:11\n ");
correct_array[count] = 4;

case 7 : 
printf("Question: Which boxer was known as “The Greatest” and “The People’s Champion”\n ");
printf("A:Tyson Fury\n ");
printf("B:Donal Trump\n ");
printf("C:Muhammad Ali\n ");
printf("D:Conor McGregor\n ");
correct_array[count] = 3;

case 8 : 
printf("Question: What is the highest-grossing film of all time ?\n ");
printf("A:Avenger: End game\n ");
printf("B:Sherk\n ");
printf("C:Sherk 2\n ");
printf("D:Avatar\n ");
correct_array[count] = 4;

case 9 : 
printf("Question: Which country is responsible for giving us pizza and pasta?\n ");
printf("A:Italy\n ");
printf("B:Italia\n ");
printf("C:Italie\n ");
printf("D:意大利 \n ");
correct_array[count] = 1;

case 10 : 
printf("Question: What is your body’s largest organ?\n ");
printf("A:Heart\n ");
printf("B:Intestines\n ");
printf("C:Skin\n ");
printf("D:Organ\n ");
correct_array[count] = 3; 

case 11 : 
printf("Question: What percentage of a adult body is made up of water?\n ");
printf("A:69%% \n ");
printf("B:50-65%%\n ");
printf("C:70-80%%\n ");
printf("D:0%%\n ");
correct_array[count] = 2;

case 12 : 
printf("Question: What is the smallest country in the world?\n ");
printf("A:Vatican City\n ");
printf("B:Cuba\n ");
printf("C:Russia\n ");
printf("D:Monaco\n ");
correct_array[count] = 1;

case 13 : 
printf("Question: Which two countries share the longest international border?\n ");
printf("A:Russia and China\n ");
printf("B:Canada and the US\n ");
printf("C:The US and Mexico\n ");
printf("D:Britain and France\n ");
correct_array[count] = 2;

case 14 : 
printf("Question: Which continent is the largest? ?\n ");
printf("A:North America\n ");
printf("B:South America\n ");
printf("C:Asia\n ");
printf("D:Antartica\n ");
correct_array[count] = 3; 

case 15 : 
printf("Question: How many championship title has the raptor won ?\n ");
printf("A:3\n ");
printf("B:1\n ");
printf("C:2\n ");
printf("D:0\n ");
correct_array[count] = 2;

case 16 : 
printf("Question: What is the name of the world’s longest river?\n ");
printf("A:The Nile river\n ");
printf("B:The Amazon River\n ");
printf("C:Mississippi river\n ");
printf("D:Mekong river\n ");
correct_array[count] = 1;

case 17 : 
printf("Question: Which religion dominated the Middle Ages?\n ");
printf("A:Catholism\n ");
printf("B:Hinduism\n ");
printf("C:Islam\n ");
printf("D:Buddhism\n ");
correct_array[count] = 1;

case 18 : 
printf("Question: In which country Adolph Hitler was born?\n ");
printf("A:Germany\n ");
printf("B:Austria\n ");
printf("C:Netherland\n ");
printf("D:Poland\n ");
correct_array[count] = 2;

case 19 : 
printf("Question: What is the name of the fourth book in the Harry Potter series?\n ");
printf("A: Harry Potter and the Goblet of Fire\n ");
printf("B: Harry Potter and the Sorcerer’s Stone\n ");
printf("C: Harry Potter and the Deathly Hallows\n ");
printf("D: Harry Potter and the Order of the Phoenix\n ");
correct_array[count] = 1;

case 20 : 
printf("Question: Who is the writer of “Merchant of Venice”?\n ");
printf("A: William Shakespeare\n ");
printf("B: J.K Rowling\n ");
printf("C: J.R.R Tolkien\n ");
printf("D: Charles Darwin\n ");
correct_array[count] = 1;

case 21 : 
printf("Question: What animal is on Levi’s logo?\n ");
printf("A: Bull\n ");
printf("B: Horse\n ");
printf("C: Eagle\n ");
printf("D: Fish\n ");
correct_array[count] = 2;

case 22 : 
printf("Question: Donald Trump and which North Korean leader are known to trade threats over the internet?\n ");
printf("A: Kim Jong-Il\n ");
printf("B: Kim Jong Un\n ");
printf("C: Mao Zedong\n ");
printf("D: Xi Jinping\n ");
correct_array[count] = 2;

case 23 : 
printf("Question:What’s the fastest land animal in the world?\n ");
printf("A: Wolf\n ");
printf("B: Hyena\n ");
printf("C: Lion\n ");
printf("D: Cheetah\n ");
correct_array[count] = 4;

case 24 : 
printf("Question: Who is the richest person in the world right now?\n ");
printf("A: Jeff bezos\n ");
printf("B: Elon Musk\n ");
printf("C: Bill Gates\n ");
printf("D: You :>\n ");
correct_array[count] = 2;

case 26 : 
printf("Question: Which watch company has a pointed a crown as its logo?\n ");
printf("A: Cartier\n ");
printf("B: Gucci\n ");
printf("C: Rolex\n ");
printf("D: Omega\n ");
correct_array[count] = 3;

case 27 : 
printf("Question: What is the slogan of Apple Inc.?\n ");
printf("A:Think different\n ");
printf("B:Think same\n ");
printf("C:Just do it\n ");
printf("D:Impossible is nothing\n ");
correct_array[count] = 1;

case 28 : 
printf("Question: Oktoberfest in Germany is celebrated with what drink?\n ");
printf("A:Vodka\n ");
printf("B:Cider\n ");
printf("C:Beer\n ");
printf("D:Rum\n ");
correct_array[count] = 3;


case 29 : 
printf("Question: When is Canada Day?\n ");
printf("A:July 28\n ");
printf("B:December 26\n ");
printf("C:July 1\n ");
printf("D:June 32\n ");
correct_array[count] = 3;



default: 
printf("Question: When is Canada Day?\n ");
printf("A:July 28\n ");
printf("B:December 26\n ");
printf("C:July 1\n ");
printf("D:June 32\n ");

} 
#endif 

#ifdef DISTANCE_1
// Gets distance from ultraasonic sensor 1 and checks if answer was selected by comparing value to a previously determined value
// Returns true if distance recieved is equal to previously determined vlaue, returns false otherwise (indicating the player's answer)
#endif

#ifdef DISTANCE_2
// Gets distance from ultrasonic sensor 2 and checks if answer was selected by comparing value to a previously determined value
// Returns true if distance recieved is equal to previously determined vlaue, returns false otherwise (indicating the player's answer)
#endif

#ifdef DISTANCE_3
// Gets distance from ultrasonic sensor 3 and checks if answer was selected by comparing value to a previously determined value
// Returns true if distance recieved is equal to previously determined vlaue, returns false otherwise (indicating the player's answer)
#endif 

#ifdef DISTANCE_4
// Gets distance from ultrasonic sensor 1 and checks if answer was selected by comparing value to a previously determined value
// Returns true if distance recieved is equal to previously determined vlaue, returns false otherwise (indicating the player's answer)
#endif

#ifdef ANSWER
// Inputs the player's answer value into array (ex. if player selects answer 2 for question one, array[0] = 1)
#endif






#ifdef BUTTON_BLINK
    // Wait for the user to push the blue button, then blink the LED.

    // wait for button press (active low)
    while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
    {
    }

    while (1) // loop forever, blinking the LED
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(250);  // 250 milliseconds == 1/4 second
    }
#endif

#ifdef LIGHT_SCHEDULER
    // Turn on the LED five seconds after reset, and turn it off again five seconds later.

    while (true) {
        uint32_t now = HAL_GetTick();
        if (now > 5000 && now < 10000)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);   // turn on LED
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);  // turn off LED
    }
#endif

#ifdef TIME_RAND
    // This illustrates the use of HAL_GetTick() to get the current time,
    // plus the use of random() for random number generation.
    
    // Note that you must have "#include <stdlib.h>"" at the top of your main.c
    // in order to use the srand() and random() functions.

    // while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press
    // srand(HAL_GetTick());  // set the random seed to be the time in ms that it took to press the button
    // if the line above is commented out, your program will get the same sequence of random numbers
    // every time you run it (which may be useful in some cases)

    while (true) // loop forever
    {
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press

        // Display the time in milliseconds along with a random number.
        // We use the sprintf() function to put the formatted output into a buffer;
        // see https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm for more
        // information about this function
        char buff[100];
        sprintf(buff, "Time: %lu ms   Random = %ld\r\n", HAL_GetTick(), random());
        // lu == "long unsigned", ld = "long decimal", where "long" is 32 bit and "decimal" implies signed
        SerialPuts(buff); // transmit the buffer to the host computer's serial monitor in VSCode/PlatformIO

        while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button to be released
    }
#endif

#ifdef KEYPAD
    // Read buttons on the keypad and display them on the console.

    // this string contains the symbols on the external keypad
    // (they may be different for different keypads)
    char *keypad_symbols = "123A456B789C*0#D";
    // note that they're numbered from left to right and top to bottom, like reading words on a page

    InitializeKeypad();
    while (true)
    {
        while (ReadKeypad() < 0);   // wait for a valid key
        SerialPutc(keypad_symbols[ReadKeypad()]);  // look up its ASCII symbol and send it to the hsot
        while (ReadKeypad() >= 0);  // wait until key is released
    }
#endif

#ifdef KEYPAD_CONTROL
    // Use top-right button on 4x4 keypad (typically 'A') to toggle LED.

    InitializeKeypad();
    while (true)
    {
        while (ReadKeypad() < 0);   // wait for a valid key
        int key = ReadKeypad();
        if (key == 3)  // top-right key in a 4x4 keypad, usually 'A'
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);   // toggle LED on or off
         while (ReadKeypad() >= 0);  // wait until key is released
    }
#endif

#ifdef SEVEN_SEGMENT
    // Display the numbers 0 to 9 inclusive on the 7-segment display, pausing for a second between each one.
    // (remember that the GND connection on the display must go through a 220 ohm current-limiting resistor!)
    
    Initialize7Segment();
    while (true)
        for (int i = 0; i < 10; ++i)
        {
            Display7Segment(i);
            HAL_Delay(1000);  // 1000 milliseconds == 1 second
        }
#endif

#ifdef KEYPAD_SEVEN_SEGMENT
    // Combines the previous two examples, displaying numbers from the keypad on the 7-segment display.

    // this string contains the symbols on the external keypad
    // (they may be different for different keypads)
    char *keypad_symbols = "123A456B789C*0#D";
    // note that they're numbered from left to right and top to bottom, like reading words on a page

    InitializeKeypad();
    Initialize7Segment();
    while (true)
    {
        int key = ReadKeypad();
        if (key >= 0)
            Display7Segment(keypad_symbols[key]-'0');  // tricky code to convert ASCII digit to a number
    }
#endif

#ifdef COLOR_LED
    // Cycle through all 8 possible colors (including off and white) as the on-board button is pressed.
    // This example assumes that the color LED is connected to pins D11, D12 and D13.

    // Remember that each of those three pins must go through a 220 ohm current-limiting resistor!
    // Also remember that the longest pin on the LED should be hooked up to GND.

    InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    while (true) {
        for (int color = 0; color < 8; ++color) {
            // bottom three bits indicate which of the three LEDs should be on (eight possible combinations)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, color & 0x01);  // blue  (hex 1 == 0001 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, color & 0x02);  // green (hex 2 == 0010 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, color & 0x04);  // red   (hex 4 == 0100 binary)

            while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));   // wait for button press 
            while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button release
        }
    }
#endif

#ifdef ROTARY_ENCODER
    // Read values from the rotary encoder and update a count, which is displayed in the console.

    InitializePin(GPIOB, GPIO_PIN_5, GPIO_MODE_INPUT, GPIO_PULLUP, 0);   // initialize CLK pin
    InitializePin(GPIOB, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_PULLUP, 0);   // initialize DT pin
    InitializePin(GPIOB, GPIO_PIN_10, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // initialize SW pin
    
    bool previousClk = false;  // needed by ReadEncoder() to store the previous state of the CLK pin
    int count = 0;             // this gets incremented or decremented as we rotate the encoder

    while (true)
    {
        int delta = ReadEncoder(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, &previousClk);  // update the count by -1, 0 or +1
        if (delta != 0) {
            count += delta;
            char buff[100];
            sprintf(buff, "%d  \r", count);
            SerialPuts(buff);
        }
        bool sw = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);  // read the push-switch on the encoder (active low, so we invert it using !)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, sw);  // turn on LED when encoder switch is pushed in
    }
#endif

#ifdef ANALOG
    // Use the ADC (Analog to Digital Converter) to read voltage values from two pins.

    __HAL_RCC_ADC1_CLK_ENABLE();        // enable ADC 1
    ADC_HandleTypeDef adcInstance;      // this variable stores an instance of the ADC
    InitializeADC(&adcInstance, ADC1);  // initialize the ADC instance
    // Enables the input pins
    // (on this board, pin A0 is connected to channel 0 of ADC1, and A1 is connected to channel 1 of ADC1)
    InitializePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_MODE_ANALOG, GPIO_NOPULL, 0);   
    while (true)
    {
        // read the ADC values (0 -> 0V, 2^12 -> 3.3V)
        uint16_t raw0 = ReadADC(&adcInstance, ADC_CHANNEL_0);
        uint16_t raw1 = ReadADC(&adcInstance, ADC_CHANNEL_1);

        // print the ADC values
        char buff[100];
        sprintf(buff, "Channel0: %hu, Channel1: %hu\r\n", raw0, raw1);  // hu == "unsigned short" (16 bit)
        SerialPuts(buff);
    }
#endif

#ifdef PWM
    // Use Pulse Width Modulation to fade the LED in and out.
    uint16_t period = 100, prescale = 16;

    __TIM2_CLK_ENABLE();  // enable timer 2
    TIM_HandleTypeDef pwmTimerInstance;  // this variable stores an instance of the timer
    InitializePWMTimer(&pwmTimerInstance, TIM2, period, prescale);   // initialize the timer instance
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_1);          // initialize one channel (can use others for motors, etc)

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2); // connect the LED to the timer output

    while (true)
    {
        // fade the LED in by slowly increasing the duty cycle
        for (uint32_t i = 0; i < period; ++i)
        {
            SetPWMDutyCycle(&pwmTimerInstance, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
        // fade the LED out by slowly decreasing the duty cycle
        for (uint32_t i = period; i > 0; --i)
        {
            SetPWMDutyCycle(&pwmTimerInstance, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
    }
#endif

return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}

void LED (void){
    // If CHECKPIN is true, pin will be displayed and LED will turn green. If CHECKPIN is false, a life will be lost and LED will turn red
InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    int colour = 0;
    if(answer == true) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, colour = 2);  // green (hex 2 == 0010 binary)
        }else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, colour = 4);  // red   (hex 4 == 0100 binary)
        }
}

void CHECK_PIN (void) {
// Checks if player's array = correct array. (their answers were all right) 

//false until player answers all questions
answer = false;
int correct_count = 0;

//compare every entry of player's array to answer array
int i;
for(int i = 0; i < 4; ++i){
    if(player_array[i] == correct_array[i]){
        correct_count++;
    }

    if (correct_count == 4){
        answer = true;
    }
}
}


int get_distance(void){
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_Delay(3);

    //set trigger pin high for 10 uS and then set it low
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

    //wait for rising edge of echo pin
    while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_RESET);
    

    //measure ECHO pulse width in Us
    Ticks = 0;
    while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET){
        Ticks++;
        HAL_Delay(2);
    };

    //calculate distance in cm
    distance = 1000*(Ticks)*2.8*speed_of_sound;
    
     return distance;
 }

// void LCD_print(void){
//     //initialize the display ports and pins 
//     LiquidCrystal(GPIOB, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6);

//     //display message on first row of display 
//     setCursor(0,0);
//     sprintf(buff, "distance (cm) =  %.2f", distance);
// }



