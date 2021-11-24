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
LCD_print("Question: How many championship title has the raptor won ?\n ");
LCD_print("A:3\n ");
LCD_print("B:1\n ");
LCD_print("C:2\n ");
LCD_print("D:0\n ");
correct_array[count] = 2;
break;

case 2 : 
LCD_print("Question: The American Falls and Horseshoe Falls are better known as?\n ");
LCD_print("A: Rainbow falls\n ");
LCD_print("B: Niagara falls\n ");
LCD_print("C: Union falls\n ");
LCD_print("D: Yosemite falls\n ");
correct_array[count] = 2;
break;

case 3 : 
LCD_print("Question: Whose nickname was the Wizard of Menlo Park?\n ");
LCD_print("A:Voldemort\n ");
LCD_print("B:Albus Dumbledore\n ");
LCD_print("C:Gandalf\n ");
LCD_print("D:Thomas Edison\n ");
correct_array[count] = 4;
break;

case 4 : 
LCD_print("Question: What animals are pearls found in?\n ");
LCD_print("A:Seals\n ");
LCD_print("B:Whales\n ");
LCD_print("C:Oysters\n ");
LCD_print("D:Corals\n ");
correct_array[count] = 3;
break;

case 5 : 
LCD_print("Question: Which cartoon character lives in a pineapple under the sea?\n ");
LCD_print("A:Spongebob Squarepants\n ");
LCD_print("B:Rick\n ");
LCD_print("C:Phineas\n ");
LCD_print("D:Elsa\n ");
correct_array[count] = 1;
break;

case 6 : 
LCD_print("Question: How many soccer players should each team have on the field at the start of each match?\n ");
LCD_print("A:9\n ");
LCD_print("B:10\n ");
LCD_print("C:21\n ");
LCD_print("D:11\n ");
correct_array[count] = 4;
break;

case 7 : 
LCD_print("Question: Which boxer was known as The Greatest and The People Champion\n ");
LCD_print("A:Tyson Fury\n ");
LCD_print("B:Donal Trump\n ");
LCD_print("C:Muhammad Ali\n ");
LCD_print("D:Conor McGregor\n ");
correct_array[count] = 3;
break;

case 8 : 
LCD_print("Question: What is the highest-grossing film of all time ?\n ");
LCD_print("A:Avenger: End game\n ");
LCD_print("B:Sherk\n ");
LCD_print("C:Sherk 2\n ");
LCD_print("D:Avatar\n ");
correct_array[count] = 4;
break;

case 9 : 
LCD_print("Question: Which country is responsible for giving us pizza and pasta?\n ");
LCD_print("A: Italy\n ");
LCD_print("B: Russia\n ");
LCD_print("C: Antartica\n ");
LCD_print("D: North Korea \n ");
correct_array[count] = 1;
break;

case 10 : 
LCD_print("Question: What is your body largest organ?\n ");
LCD_print("A: Heart\n ");
LCD_print("B: Intestines\n ");
LCD_print("C: Skin\n ");
LCD_print("D: Organ\n ");
correct_array[count] = 3; 
break;

case 11 : 
LCD_print("Question: What percentage of a adult body is made up of water?\n ");
LCD_print("A:69%% \n ");
LCD_print("B:50-65%%\n ");
LCD_print("C:70-80%%\n ");
LCD_print("D:0%%\n ");
correct_array[count] = 2;
break;

case 12 : 
LCD_print("Question: What is the smallest country in the world?\n ");
LCD_print("A: Vatican City\n ");
LCD_print("B: Cuba\n ");
LCD_print("C: Russia\n ");
LCD_print("D: Monaco\n ");
correct_array[count] = 1;
break;

case 13 : 
LCD_print("Question: Which two countries share the longest international border?\n ");
LCD_print("A: Russia and China\n ");
LCD_print("B: Canada and the US\n ");
LCD_print("C: The US and Mexico\n ");
LCD_print("D: Britain and France\n ");
correct_array[count] = 2;
break;

case 14 : 
LCD_print("Question: Which continent is the largest? ?\n ");
LCD_print("A: North America\n ");
LCD_print("B: South America\n ");
LCD_print("C: Asia\n ");
LCD_print("D: Antartica\n ");
correct_array[count] = 3; 
break; 

case 15 : 
LCD_print("Question: How many championship title has the raptor won ?\n ");
LCD_print("A: 3\n ");
LCD_print("B: 1\n ");
LCD_print("C: 2\n ");
LCD_print("D: 0\n ");
correct_array[count] = 2;
break;

case 16 : 
LCD_print("Question: What is the name of the longest river in the world?\n ");
LCD_print("A:The Nile river\n ");
LCD_print("B:The Amazon River\n ");
LCD_print("C:Mississippi river\n ");
LCD_print("D:Mekong river\n ");
correct_array[count] = 1;
break;

case 17 : 
LCD_print("Question: Which religion dominated the Middle Ages?\n ");
LCD_print("A:Catholism\n ");
LCD_print("B:Hinduism\n ");
LCD_print("C:Islam\n ");
LCD_print("D:Buddhism\n ");
correct_array[count] = 1;
break;

case 18 : 
LCD_print("Question: In which country was Adolph Hitler born in?\n ");
LCD_print("A:Germany\n ");
LCD_print("B:Austria\n ");
LCD_print("C:Netherland\n ");
LCD_print("D:Poland\n ");
correct_array[count] = 2;
break;

case 19 : 
LCD_print("Question: What is the name of the fourth book in the Harry Potter series?\n ");
LCD_print("A: Harry Potter and the Goblet of Fire\n ");
LCD_print("B: Harry Potter and the Sorcerer’s Stone\n ");
LCD_print("C: Harry Potter and the Deathly Hallows\n ");
LCD_print("D: Harry Potter and the Order of the Phoenix\n ");
correct_array[count] = 1;
break;

case 20 : 
LCD_print("Question: Who is the writer of Merchant of Venice?\n ");
LCD_print("A: William Shakespeare\n ");
LCD_print("B: J.K Rowling\n ");
LCD_print("C: J.R.R Tolkien\n ");
LCD_print("D: Charles Darwin\n ");
correct_array[count] = 1;
break;

case 21 : 
LCD_print("Question: What animal is on the lamborghini logo?\n ");
LCD_print("A: Bull\n ");
LCD_print("B: Horse\n ");
LCD_print("C: Eagle\n ");
LCD_print("D: Fish\n ");
correct_array[count] = 1;
break;

case 22 : 
LCD_print("Question: Donald Trump and which North Korean leader are known to trade threats over the internet?\n ");
LCD_print("A: Kim Jong-Il\n ");
LCD_print("B: Kim Jong Un\n ");
LCD_print("C: Mao Zedong\n ");
LCD_print("D: Xi Jinping\n ");
correct_array[count] = 2;
break;

case 23 : 
LCD_print("Question:What is the fastest land animal in the world?\n ");
LCD_print("A: Wolf\n ");
LCD_print("B: Hyena\n ");
LCD_print("C: Lion\n ");
LCD_print("D: Cheetah\n ");
correct_array[count] = 4;
break;

case 24 : 
LCD_print("Question: Who is the richest person in the world right now?\n ");
LCD_print("A: Jeff bezos\n ");
LCD_print("B: Elon Musk\n ");
LCD_print("C: Bill Gates\n ");
LCD_print("D: You :>\n ");
correct_array[count] = 2;
break;

case 26 : 
LCD_print("Question: Which watch company has a pointed crown as its logo?\n ");
LCD_print("A: Cartier\n ");
LCD_print("B: Gucci\n ");
LCD_print("C: Rolex\n ");
LCD_print("D: Omega\n ");
correct_array[count] = 3;
break;

case 27 : 
LCD_print("Question: What is the slogan of Apple Inc.?\n ");
LCD_print("A: Think different\n ");
LCD_print("B: Think same\n ");
LCD_print("C: Just do it\n ");
LCD_print("D: Impossible is nothing\n ");
correct_array[count] = 1;
break;

case 28 : 
LCD_print("Question: Oktoberfest in Germany is celebrated with what drink?\n ");
LCD_print("A:Vodka\n ");
LCD_print("B:Cider\n ");
LCD_print("C:Beer\n ");
LCD_print("D:Rum\n ");
correct_array[count] = 3;
break;

case 29 : 
LCD_print("Question: When is Canada Day?\n ");
LCD_print("A:July 28\n ");
LCD_print("B:December 26\n ");
LCD_print("C:July 1\n ");
LCD_print("D:June 32\n ");
correct_array[count] = 3;
break;

case 30 : 
LCD_print("How many buildings does the University of Waterloo have\n ");
LCD_print("A:75\n ");
LCD_print("B:50\n ");
LCD_print("C:100+\n ");
LCD_print("D:28\n ");
correct_array[count] = 3;
break;

default: 
LCD_print("Question: Who was the first person to be pictured on a coin?\n ");
LCD_print("A: Benjamin Franklin\n ");
LCD_print("B: Genghis Khan\n ");
LCD_print("C: Alexander the Great\n ");
LCD_print("D: Cleopatra\n ");
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
	HAL_Delay(1000);

}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
}

