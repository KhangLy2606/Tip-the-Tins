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
void check_answer();
void LCD_print(char buff[]);

bool answer = false;
size_t count;
char buff[100];
int Ticks;
const float speed_of_sound = 0.0343/2;


char correct_array[4];
char player_array[4];
char player_answer[4];
int turn = 0;
char lives = '3';
bool answered;
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
    LCD_print("====Welcome====");
    LCD_print("Press the blue"); 
    LCD_print("button to"); 
    LCD_print ( "START THE GAME");
    while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));
    srand(HAL_GetTick());
    while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));

    // initialize pins for sensors
    //sen 1
    InitializePin(GPIOC, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_NOPULL, 0);
    //sen2
    InitializePin(GPIOB, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_NOPULL, 0);
    //sen3
    InitializePin(GPIOB, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_5, GPIO_MODE_INPUT, GPIO_NOPULL, 0);
    //sen4
    InitializePin(GPIOB, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_7, GPIO_MODE_INPUT, GPIO_NOPULL, 0);

    
    //test for sensors
    // while(1){
    //     sprintf(buff, "distance 1 (cm) =  %d\n", get_distance1());
    //     SerialPuts(buff);

    //     HAL_Delay(3000);

    //      sprintf(buff, "distance 2 (cm) =  %d\n", get_distance2());
    //     SerialPuts(buff);

    //     HAL_Delay(3000);

    //      sprintf(buff, "distance 3 (cm) =  %d\n", get_distance3());
    //     SerialPuts(buff);

    //     HAL_Delay(3000);

    //      sprintf(buff, "distance 4 (cm) =  %d\n", get_distance4());
    //     SerialPuts(buff);

    //     HAL_Delay(3000);
    // }

   
    // Game code
    // Asks 4 questions and inputs answers based on sensors

    while((answer == false) && ((lives - '0')> 0)){
        while(turn < 4){
        // Gets random question 
        answered = false;
        RAND_QUEST();
        
        while (answered == false) {
        check_answer();
        }
        ++turn;
        count++;
        HAL_Delay(200);
    }
        // Checks if player got all 4 questions correctly and turns LED on accordingly and prints lives 
        CHECK_PIN();
        LED();
        turn = 0;
    }

    

return 0;
}

void RAND_QUEST ()  {
// Generates a random question with correct answer 

// keeps track of random number

int rand_num  = random()%30; // selects a random number using the function from the HAL library

switch (rand_num) // matches rand_num with question 
{
case 1 : 
LCD_print("3x+6=0");
LCD_print("A: x=5");
LCD_print("B: x=-2");
LCD_print("C: x=2");
LCD_print("D: x=3");
correct_array[count] = 2 + '0';
break;

case 2 : 
LCD_print("5*7=");
LCD_print("A: 75");
LCD_print("B: 35");
LCD_print("C: 30");
LCD_print("D: 5");
correct_array[count] = 2 + '0';
break;

case 3 : 
LCD_print("16*18=");
LCD_print("A: 128");
LCD_print("B: 248");
LCD_print("C: 48");
LCD_print("D: 288");
correct_array[count] = 4 + '0';
break;

case 4 : 
LCD_print("5+(8*3)=");
LCD_print("A: 17");
LCD_print("B: 39");
LCD_print("C: 29");
LCD_print("D: 25");
correct_array[count] = 3 + '0';
break;

case 5 : 
LCD_print("7*8*9=");
LCD_print("A: 504");
LCD_print("B: 65");
LCD_print("C: 178");
LCD_print("D: 897");
correct_array[count] = 1 + '0';
break;

case 6 : 
LCD_print("13x-26=0");
LCD_print("A: x=-1/2");
LCD_print("B: x=1/2");
LCD_print("C: x=-2");
LCD_print("D: x=2");
correct_array[count] = 4 + '0';
break;

case 7 : 
LCD_print("45/5=");
LCD_print("A: 5");
LCD_print("B: 8");
LCD_print("C: 9");
LCD_print("D: 7");
correct_array[count] = 3 + '0';
break;

case 8 : 
LCD_print("67+90+33=");
LCD_print("A: 200");
LCD_print("B: 97");
LCD_print("C: 187");
LCD_print("D: 190");
correct_array[count] = 4 + '0';
break;

case 9 : 
LCD_print("1234*5678=");
LCD_print("A: I7006652");
LCD_print("B: 23084833");
LCD_print("C: 14637823");
LCD_print("D: 20393682");
correct_array[count] = 1 + '0';
break;

case 10 : 
LCD_print("123456+789124=");
LCD_print("A: 238479");
LCD_print("B: 829038");
LCD_print("C: 912580");
LCD_print("D: 349870");
correct_array[count] = 3 + '0'; 
break;

case 11 : 
LCD_print("67*3=");
LCD_print("A: 184 ");
LCD_print("B: 201");
LCD_print("C: 191");
LCD_print("D: 352");
correct_array[count] = 2 + '0';
break;

case 12 : 
LCD_print("120/3=");
LCD_print("A: 40");
LCD_print("B: 60");
LCD_print("C: 20");
LCD_print("D: 45");
correct_array[count] = 1 + '0';
break;

case 13 : 
LCD_print("2+3+6+8=");
LCD_print("A: 20");
LCD_print("B: 19");
LCD_print("C: 16");
LCD_print("D: 24");
correct_array[count] = 2 + '0';
break;

case 14 : 
LCD_print("20*5=");
LCD_print("A: 80");
LCD_print("B: 120");
LCD_print("C: 100");
LCD_print("D: 90");
correct_array[count] = 3 + '0'; 
break; 

case 15 : 
LCD_print("7*9=");
LCD_print("A: 49");
LCD_print("B: 63");
LCD_print("C: 92");
LCD_print("D: 56");
correct_array[count] = 2 + '0';
break;

case 16 : 
LCD_print("13*7=");
LCD_print("A: 91");
LCD_print("B: 78");
LCD_print("C: 99");
LCD_print("D: 120");
correct_array[count] = 1 + '0';
break;

case 17 : 
LCD_print("6y-3=0");
LCD_print("A: y=1/2");
LCD_print("B: y=2");
LCD_print("C: y=-1/2");
LCD_print("D:y=-2");
correct_array[count] = 1 + '0';
break;

case 18 : 
LCD_print("6*5=");
LCD_print("A: 35");
LCD_print("B: 30");
LCD_print("C: 25");
LCD_print("D: 36");
correct_array[count] = 2 + '0';
break;

case 19 : 
LCD_print("180/6=");
LCD_print("A: 30");
LCD_print("B: 60");
LCD_print("C: 3");
LCD_print("D: 36");
correct_array[count] = 1 + '0';
break;

case 20 : 
LCD_print("234+789=");
LCD_print("A: 1023");
LCD_print("B: 1765");
LCD_print("C: 1234");
LCD_print("D: 9887");
correct_array[count] = 1 + '0';
break;

case 21 : 
LCD_print("56/7=");
LCD_print("A: 8");
LCD_print("B: 7");
LCD_print("C: 12");
LCD_print("D: 4");
correct_array[count] = 1 + '0';
break;

case 22 : 
LCD_print("145/5=");
LCD_print("A: 25");
LCD_print("B: 29");
LCD_print("C: 30");
LCD_print("D: 17");
correct_array[count] = 2 + '0';
break;

case 23 : 
LCD_print("25*4=");
LCD_print("A: 125");
LCD_print("B: 75");
LCD_print("C: 168");
LCD_print("D: 100");
correct_array[count] = 4 + '0';
break;

case 24 : 
LCD_print("5x-25=0");
LCD_print("A: x=-5");
LCD_print("B: x=5");
LCD_print("C: x=3");
LCD_print("D: x=10");
correct_array[count] = 2 + '0';
break;

case 26 : 
LCD_print("50*3=");
LCD_print("A: 105");
LCD_print("B: 200");
LCD_print("C: 150");
LCD_print("D: 70");
correct_array[count] = 3 + '0';
break;

case 27 : 
LCD_print("80x-20=0");
LCD_print("A: x=1/4");
LCD_print("B: x=-1/4");
LCD_print("C: x=4");
LCD_print("D: x=8");
correct_array[count] = 1 + '0';
break;

case 28 : 
LCD_print("905/5=");
LCD_print("A: 50");
LCD_print("B: 90");
LCD_print("C: 181");
LCD_print("D: 200");
correct_array[count] = 3 + '0';
break;

case 29 : 
LCD_print("786-564=");
LCD_print("A: 197");
LCD_print("B: 245");
LCD_print("C: 222");
LCD_print("D: 234");
correct_array[count] = 3 + '0';
break;

case 30 : 
LCD_print("167*4/2=");
LCD_print("A: 157");
LCD_print("B: 400");
LCD_print("C: 334");
LCD_print("D: 350");
correct_array[count] = 3 + '0';
break;

default: 
LCD_print("5x-100=0");
LCD_print("A: x=-20");
LCD_print("B: x=1/5");
LCD_print("C: x=20");
LCD_print("D: x=100");
correct_array[count] = 3 + '0';
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
            LCD_print("You've tipped...");
            LCD_print("the right tins!");
            LCD_print("Pin to escape:");
            for(int i = 0; i < 4; ++i){
            LCD_print(&player_array[i]);
            }
        }else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, colour = 4);  // red   (hex 4 == 0100 binary)
            LCD_print("You've tipped...");
            LCD_print("the wrong tins:(");
            lives = lives - 1;
            LCD_print("Lives left: ");
            LCD_print(&lives);
            LCD_print("Try again.");
        }
}

void check_answer(){
    while(answered == false){
    
        HAL_Delay(200);
        if(get_distance1() > 48){
            player_array[turn] = 1 + '0';
            answered = true;
            break;
        }
        HAL_Delay(200);
        if(get_distance2() > 48){
            player_array[turn] = 2 + '0';
            answered = true;
            break;
        }
        HAL_Delay(200);
        if(get_distance3() > 48){
            player_array[turn] = 3 + '0';
            answered = true;
            break;
        }
        HAL_Delay(200);
        if(get_distance4() > 48){
            player_array[turn] = 4 + '0';
            answered = true;
            break;
        }
    }
}

int get_distance1(void){
    int distance ;
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
    int distance ;
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
    int distance ;
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
    int distance ;
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
    //* LCD D6 pin to PA1
    //* LCD D7 pin to PA4
    //* 10K resistor:
    //* ends to +5V and ground
    //* wiper to LCD VO pin (pin 3)

    // initialize the library by associating any needed LCD interface pin
	LiquidCrystal(GPIOA, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_1, GPIO_PIN_4);

	print(buff);
	HAL_Delay(3500);

}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
}

