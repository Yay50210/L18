#include<iostream>
using namespace std;

struct Rect{
	double x,y,w,h;
};

double overlap( Rect R1, Rect R2 ){
    
    double width = 0.0;
    double lenght = 0.0;
    if(R1.x+R1.w >= R2.x){
            if(R2.x+R2.w <= R1.x+R1.w){
                width = R2.w;
            }else{
               width = R1.x+R1.w-R2.x;
            }
            
        
    }
    if(R1.y+R1.h >= R2.y){
            if(R2.y+R2.h <= R1.y+R1.h){
                lenght = R2.h;
            }else{
               lenght = R1.y+R1.h-R2.y;
            }
        }
    return width*lenght;
}
