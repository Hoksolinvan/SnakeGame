#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <fcntl.h>


/* Function Prototype */
std::vector< std::vector<std::string> > renderBox(int width,int height);
void displayCanvas (std::vector< std::vector<std::string> >& matrixBox);
void clearScreen();
void setup();



/* Global constant */
const int width = 20;
const int height = 20;


/* Global Variable */
int x_position;
int y_position;
int fruit_x_position;
int fruit_y_position;
int score;
int nTail;
enum Direction = {STOP =0, LEFT, RIGHT, UP, DOWN};
Direction dir;
bool gameOver;



int main(){

    
   std::vector< std::vector<std::string> > matrixBox = renderBox(20,20);
   setup();

   int count=0;


    while(!gameOver){

          
           displayCanvas(matrixBox);
           input();
           logic();
           

    }

   

   



    return 0;
}






void input(){

}












void setup(){
    gameOver=false;
    dir = STOP;
    x = width / 2;
    y = width / 2;


    srand(time(0));
    fruit_x_position = rand() % width;
    fruit_y_position = rand() % height;
    score = 0;



}


std::vector< std::vector<std::string> > renderBox(int width,int height){

std::vector< std::vector<std::string> > matrixBox(width, std::vector<std::string>(height,"#"));

for(int i=1; i< width-1; i++){
    for(int j=1; j<width-1;j++){
        matrixBox[i][j]=" ";
    }
}

return matrixBox;

}

void displayCanvas (std::vector< std::vector<std::string> >& matrixBox){
   clearScreen();
    for (size_t i=0; i< matrixBox.size(); i++){
       for (size_t j=0; j< matrixBox[i].size();j++){
           std::cout<< matrixBox[i][j] << " ";
       }
       std::cout << std::endl;
    }

}

void clearScreen(){
    std::cout << "\033[2J\033[H";
}

void setup(){
    gameOver = false;
}
