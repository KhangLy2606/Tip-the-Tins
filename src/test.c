// Sample code for ECE 198

// Written by Bernie Roehl, August 2021

// This file contains code for a number of different examples.
// Each one is surrounded by an #ifdef ... #endif block inside of main().

// To run a particular example, you should remove the comment (//) in
// front of exactly ONE of the following lines:


//Tip the Tins Helper Functions 
#define RAND_QUEST  
// #define DISTANCE_1  
// #define DISTANCE_2  
// #define DISTANCE_3  
// #define DISTANCE_4  
// #define ANSWER      
#define CHECK_PIN    
#define LED        

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

bool answer;
size_t count;

//the following code is just to test the LED and CHECK_PIN, if you change the values the corresponding light will turn on!
int player_array[4] = {1,3,2,4};
int correct_array[4] = {1,3,2,4};

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

int main(void)
{
    HAL_Init(); 
    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED
    SerialSetup(9600);

#ifdef RAND_QUEST
// Generates a random question with correct answer 
int rand_num = 0;
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

#ifdef CHECK_PIN
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
#endif


#ifdef LED
// If CHECKPIN is true, pin will be displayed and LED will turn green. If CHECKPIN is false, a life will be lost and LED will turn red
InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    int colour = 0;
    if(answer == true) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, colour = 2);  // green (hex 2 == 0010 binary)
        }else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, colour = 4);  // red   (hex 4 == 0100 binary)
        }
#endif