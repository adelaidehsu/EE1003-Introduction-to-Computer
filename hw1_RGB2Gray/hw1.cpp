//#include "BMPImg_ans.h"
#include "BMPImg.h"
#include<string>
using namespace std;

int main(){
    BMPImg img;
    img.loadPic("liver.bmp");
    img.storePic("result1.bmp");
    img.RGB2Y();
    
    //img.SobelFilter();
    img.storePic("result2.bmp");
    return 0;
}
