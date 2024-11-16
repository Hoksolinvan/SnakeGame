#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>


std::vector< std::vector<std::string> > renderBox(int width,int height);
void displayCanvas (std::vector< std::vector<std::string> >& matrixBox);


int main(){

    
   std::vector< std::vector<std::string> > matrixBox = renderBox(30,30);


    while(1){
        displayCanvas(matrixBox);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

   



    return 0;
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
    std::cout << "\033[2J";     
    std::cout << "\033[0;0H";
    for (size_t i=0; i< matrixBox.size(); i++){
       for (size_t j=0; j< matrixBox[i].size();j++){
           std::cout<< matrixBox[i][j] << " ";
       }
       std::cout << std::endl;
    }

}
