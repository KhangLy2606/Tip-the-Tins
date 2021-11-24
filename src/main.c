// Libraries included
#include <stdbool.h> 
#include <stdio.h>   
#include <stdlib.h>  
#include "ece198.h"
#include <string.h>
#include "LiquidCrystal.h"

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

void RAND_QUEST ();
void CHECK_PIN();
void LED();
int get_distance1();
int get_distance2();
int get_distance3();
int get_distance4();
void LCD_print(char buff[]);

bool answer;
size_t count;
char buff[100];
int Ticks;
const float speed_of_sound = 0.0343/2;
int distance = 6;

int correct_array[4];
int player_array[4];
int turn = 1;

char question;




int main(void)
{
   
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A - for LCD screen
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B - for LEDS
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port D arduino - for sensors

    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    // initialize pins for sensors - NEED TO CHANGE
    InitializePin(GPIOC, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_NOPULL, 0);

    // Game code

    while(turn <= 4){
        // Gets random question 
        RAND_QUEST();
        get_distance();
    }

    CHECK_PIN();
    LED();

return 0;
}

void RAND_QUEST ()  {
// Generates a random question with correct answer 

int rand_num = 0; // keeps track of random number
srand(HAL_GetTick());
rand_num = rand()%30; // selects a random number using the function from the HAL library

switch (rand_num) // matches rand_num with question 
{
case 1 : 
LCD_print("How many championship title has the raptor won ?");
LCD_print("A:3");
LCD_print("B:1");
LCD_print("C:2");
LCD_print("D:0");
correct_array[count] = 2;
break;

case 2 : 
LCD_print(" The American Falls and Horseshoe Falls are better known as?");
LCD_print("A: Rainbow falls");
LCD_print("B: Niagara falls");
LCD_print("C: Union falls");
LCD_print("D: Yosemite falls");
correct_array[count] = 2;
break;

case 3 : 
LCD_print("Whose nickname was the Wizard of Menlo Park?");
LCD_print("A:Voldemort");
LCD_print("B:Albus Dumbledore");
LCD_print("C:Gandalf");
LCD_print("D:Thomas Edison");
correct_array[count] = 4;
break;

case 4 : 
LCD_print("What animals are pearls found in?");
LCD_print("A:Seals");
LCD_print("B:Whales");
LCD_print("C:Oysters");
LCD_print("D:Corals");
correct_array[count] = 3;
break;

case 5 : 
LCD_print("Which cartoon character lives in a pineapple under the sea?");
LCD_print("A:Spongebob Squarepants");
LCD_print("B:Rick");
LCD_print("C:Phineas");
LCD_print("D:Elsa");
correct_array[count] = 1;
break;

case 6 : 
LCD_print("How many soccer players should each team have on the field at the start of each match?");
LCD_print("A:9");
LCD_print("B:10");
LCD_print("C:21");
LCD_print("D:11");
correct_array[count] = 4;
break;

case 7 : 
LCD_print("Which boxer was known as The Greatest and The People Champion");
LCD_print("A:Tyson Fury");
LCD_print("B:Donal Trump");
LCD_print("C:Muhammad Ali");
LCD_print("D:Conor McGregor");
correct_array[count] = 3;
break;

case 8 : 
LCD_print("What is the highest-grossing film of all time ?");
LCD_print("A:Avenger: End game");
LCD_print("B:Sherk");
LCD_print("C:Sherk 2");
LCD_print("D:Avatar");
correct_array[count] = 4;
break;

case 9 : 
LCD_print("Which country is responsible for giving us pizza and pasta?");
LCD_print("A: Italy");
LCD_print("B: Russia");
LCD_print("C: Antartica");
LCD_print("D: North Korea ");
correct_array[count] = 1;
break;

case 10 : 
LCD_print("What is your body largest organ?");
LCD_print("A: Heart");
LCD_print("B: Intestines");
LCD_print("C: Skin");
LCD_print("D: Organ");
correct_array[count] = 3; 
break;

case 11 : 
LCD_print("What percentage of a adult body is made up of water?");
LCD_print("A:69%% ");
LCD_print("B:50-65%%");
LCD_print("C:70-80%%");
LCD_print("D:0%%");
correct_array[count] = 2;
break;

case 12 : 
LCD_print("What is the smallest country in the world?");
LCD_print("A: Vatican City");
LCD_print("B: Cuba");
LCD_print("C: Russia");
LCD_print("D: Monaco");
correct_array[count] = 1;
break;

case 13 : 
LCD_print("Which two countries share the longest international border?");
LCD_print("A: Russia and China");
LCD_print("B: Canada and the US");
LCD_print("C: The US and Mexico");
LCD_print("D: Britain and France");
correct_array[count] = 2;
break;

case 14 : 
LCD_print("Which continent is the largest? ?");
LCD_print("A: North America");
LCD_print("B: South America");
LCD_print("C: Asia");
LCD_print("D: Antartica");
correct_array[count] = 3; 
break; 

case 15 : 
LCD_print("How many championship title has the raptor won ?");
LCD_print("A: 3");
LCD_print("B: 1");
LCD_print("C: 2");
LCD_print("D: 0");
correct_array[count] = 2;
break;

case 16 : 
LCD_print("What is the name of the longest river in the world?");
LCD_print("A:The Nile river");
LCD_print("B:The Amazon River");
LCD_print("C:Mississippi river");
LCD_print("D:Mekong river");
correct_array[count] = 1;
break;

case 17 : 
LCD_print("Which religion dominated the Middle Ages?");
LCD_print("A:Catholism");
LCD_print("B:Hinduism");
LCD_print("C:Islam");
LCD_print("D:Buddhism");
correct_array[count] = 1;
break;

case 18 : 
LCD_print("In which country was Adolph Hitler born in?");
LCD_print("A:Germany");
LCD_print("B:Austria");
LCD_print("C:Netherland");
LCD_print("D:Poland");
correct_array[count] = 2;
break;

case 19 : 
LCD_print("What is the name of the fourth book in the Harry Potter series?");
LCD_print("A: Harry Potter and the Goblet of Fire");
LCD_print("B: Harry Potter and the Sorcerer’s Stone");
LCD_print("C: Harry Potter and the Deathly Hallows");
LCD_print("D: Harry Potter and the Order of the Phoenix");
correct_array[count] = 1;
break;

case 20 : 
LCD_print("Who is the writer of Merchant of Venice?");
LCD_print("A: William Shakespeare");
LCD_print("B: J.K Rowling");
LCD_print("C: J.R.R Tolkien");
LCD_print("D: Charles Darwin");
correct_array[count] = 1;
break;

case 21 : 
LCD_print("What animal is on the lamborghini logo?");
LCD_print("A: Bull");
LCD_print("B: Horse");
LCD_print("C: Eagle");
LCD_print("D: Fish");
correct_array[count] = 1;
break;

case 22 : 
LCD_print("Donald Trump and which North Korean leader are known to trade threats over the internet?");
LCD_print("A: Kim Jong-Il");
LCD_print("B: Kim Jong Un");
LCD_print("C: Mao Zedong");
LCD_print("D: Xi Jinping");
correct_array[count] = 2;
break;

case 23 : 
LCD_print("Question:What is the fastest land animal in the world?");
LCD_print("A: Wolf");
LCD_print("B: Hyena");
LCD_print("C: Lion");
LCD_print("D: Cheetah");
correct_array[count] = 4;
break;

case 24 : 
LCD_print("Who is the richest person in the world right now?");
LCD_print("A: Jeff bezos");
LCD_print("B: Elon Musk");
LCD_print("C: Bill Gates");
LCD_print("D: You :>");
correct_array[count] = 2;
break;

case 26 : 
LCD_print("Which watch company has a pointed crown as its logo?");
LCD_print("A: Cartier");
LCD_print("B: Gucci");
LCD_print("C: Rolex");
LCD_print("D: Omega");
correct_array[count] = 3;
break;

case 27 : 
LCD_print("What is the slogan of Apple Inc.?");
LCD_print("A: Think different");
LCD_print("B: Think same");
LCD_print("C: Just do it");
LCD_print("D: Impossible is nothing");
correct_array[count] = 1;
break;

case 28 : 
LCD_print("Oktoberfest in Germany is celebrated with what drink?");
LCD_print("A:Vodka");
LCD_print("B:Cider");
LCD_print("C:Beer");
LCD_print("D:Rum");
correct_array[count] = 3;
break;

case 29 : 
LCD_print("When is Canada Day?");
LCD_print("A:July 28");
LCD_print("B:December 26");
LCD_print("C:July 1");
LCD_print("D:June 32");
correct_array[count] = 3;
break;

case 30 : 
LCD_print("How many buildings does the University of Waterloo have");
LCD_print("A:75");
LCD_print("B:50");
LCD_print("C:100+");
LCD_print("D:28");
correct_array[count] = 3;
break;

default: 
LCD_print("Who was the first person to be pictured on a coin?");
LCD_print("A: Benjamin Franklin");
LCD_print("B: Genghis Khan");
LCD_print("C: Alexander the Great");
LCD_print("D: Cleopatra");
correct_array[count] = 3;
break;
    } 
}

void CHECK_PIN () {
// Checks if player's array = correct array. (their answers were all right) 

//false until player answers all questions
answer = false;
int correct_count = 0;

//compare every entry of player's array to answer array
for(int i = 0; i < 4; ++i){
    if(player_array[i] == correct_array[i]){
        correct_count++;
    }

    if (correct_count == 4){
        answer = true;
        }
    }
}

void LED (){
    // If CHECKPIN is true, pin will be displayed and LED will turn green. If CHECKPIN is false, a life will be lost and LED will turn red
InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    int colour = 0;
    if(answer == true) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, colour = 2);  // green (hex 2 == 0010 binary)
        }else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, colour = 4);  // red   (hex 4 == 0100 binary)
        }
}

int get_distance1(void){
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

int get_distance2(void){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_Delay(3);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

    //wait for rising edge of echo pin
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET);
    

    //measure ECHO pulse width in Us
    Ticks = 0;
    while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_SET){
        Ticks++;
        HAL_Delay(2);
    };

    //calculate distance in cm
    distance = 1000*(Ticks)*2.8*speed_of_sound;
    
     return distance;
 }

int get_distance3(void){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_Delay(3);

    //set trigger pin high for 10 uS and then set it low
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

    //wait for rising edge of echo pin
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET);
    

    //measure ECHO pulse width in Us
    Ticks = 0;
    while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET){
        Ticks++;
        HAL_Delay(2);
    };

    //calculate distance in cm
    distance = 1000*(Ticks)*2.8*speed_of_sound;
    
     return distance;
 }

int get_distance4(void){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_Delay(3);

    //set trigger pin high for 10 uS and then set it low
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

    //wait for rising edge of echo pin
    while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7) == GPIO_PIN_RESET);
    

    //measure ECHO pulse width in Us
    Ticks = 0;
    while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7) == GPIO_PIN_SET){
        Ticks++;
        HAL_Delay(2);
    };

    //calculate distance in cm
    distance = 1000*(Ticks)*2.8*speed_of_sound;
    
     return distance;
 }

void LCD_print(char buff[]){
     //The circuit:
    //* LCD RS pin to PA8
    //* LCD R/W pin to PA9
    //* LCD En pin to PA10
    //* LCD D4 pin to PA11
    //* LCD D5 pin to PA12
    //* LCD D6 pin to PA13
    //* LCD D7 pin to PA14
    //* 10K resistor:
    //* ends to +5V and ground
    //* wiper to LCD VO pin (pin 3)

    // initialize the library by associating any needed LCD interface pin
	LiquidCrystal(GPIOA, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);

	print(buff);
	HAL_Delay(10000);

}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
}

