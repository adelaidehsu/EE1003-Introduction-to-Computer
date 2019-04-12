#ifndef __BMPIMG_H__
#define __BMPIMG_H__

#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

static const int headerNum = 15;
static const int headerSize[headerNum] = {2,4,4,4,  4,4,4,2,2,4,4,4,4,4,4};
static const string headerInfo[headerNum]
    = {"Identifier","FileSize","Reserved","BitmapDataOffset",
       "BitmapHeaderSize","Width","Height","Planes",
       "BitsPerPixel","Compression","BitmapDataSize","H_Resolution",
       "V_Resolution","UsedColors","ImportantColors"};

class BMPHead{
private:
    char Identifier[2];
    unsigned int    FileSize;
    unsigned int    Reserved;
    unsigned int    BitmapDataOffset;

    unsigned int    BitmapHeaderSize;
    unsigned int    Width;
    unsigned int    Height;
    unsigned short  Planes;
    unsigned short  BitsPerPixel;
    unsigned int    Compression;
    unsigned int    BitmapDataSize;
    unsigned int    H_Resolution;
    unsigned int    V_Resolution;
    unsigned int    UsedColors;
    unsigned int    ImportantColors;
public:
    friend class BMPImg;
    void* pFlag(const int i)const{  //return pointers of flags according to its order(int)
        switch(i){
        default:
        case  0:    return (void*)Identifier;
        case  1:    return (void*)&FileSize;
        case  2:    return (void*)&Reserved;
        case  3:    return (void*)&BitmapDataOffset;
        case  4:    return (void*)&BitmapHeaderSize;
        case  5:    return (void*)&Width;
        case  6:    return (void*)&Height;
        case  7:    return (void*)&Planes;
        case  8:    return (void*)&BitsPerPixel;
        case  9:    return (void*)&Compression;
        case 10:    return (void*)&BitmapDataSize;
        case 11:    return (void*)&H_Resolution;
        case 12:    return (void*)&V_Resolution;
        case 13:    return (void*)&UsedColors;
        case 14:    return (void*)&ImportantColors;
        }
    }
};
class BMPImg{
private:
    BMPHead header;
public:
    unsigned char* data;

    int getWidth()const{return header.Width;}
    int getHeight()const{return header.Height;}
    int getPxlNum()const{return header.Width * header.Height;}
    int getBytesPerPixel()const{return header.BitsPerPixel/8;}

    BMPImg(){}
    BMPImg(const char* picPath){loadPic(picPath);}
    ~BMPImg(){delete [] data;}

    bool loadPic(const char* picPath){
        //ifstream file(picPath, ios::binary);
        FILE* file = fopen(picPath, "rb");
        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, file);
        
        int index = 0;
        for(int i=0; i<headerNum; ++i)
        {
            if(headerSize[i] == 4)
            {
                *((unsigned int*)(header.pFlag(i))) = *(unsigned int*)&info[index];
                index += 4;
            }
            else
            {
                *((unsigned short*)(header.pFlag(i))) = *(unsigned short*)&info[index];
                index += 2;
            }
        }
        int size = 3 * getWidth() * abs(getHeight());
        data = new unsigned char[size];
        fread(data, sizeof(unsigned char), size, file);
        fclose(file);
    }
    
    void printHeader()const{
        for(int i=0;i<headerNum;++i){
            cout<< headerInfo[i]+":";

            if(i==0){
                cout<< header.Identifier[0] << header.Identifier[1];
            }else{
                if(headerSize[i]==4)
                    cout<< *(  (unsigned int*)(header.pFlag(i))  );
                else
                    cout<< *(  (unsigned short*)(header.pFlag(i))  );
            }
            cout<< endl;
        }
    }
    
    bool RGB2Y(){
        int size = 3 * getWidth() * abs(getHeight());
        for(int i=0; i<size; i+=3)
        {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
            
            unsigned char y;
            y = 0.299*data[i] + 0.587*data[i+1] + 0.114*data[i+2];
            data[i] = y;
            data[i+1] = y;
            data[i+2] = y;
        }
        return true;
    }
    
    bool storePic(const string& outPath){
        ofstream file(outPath, ios::binary);
        char info[54];
        int index = 0;
        for(int i=0; i<headerNum; ++i)
        {
            if(headerSize[i] == 4)
            {
                 *(unsigned int*)&info[index] = *((unsigned int*)(header.pFlag(i)));
                index += 4;
            }
            else
            {
                *(unsigned short*)&info[index] = *((unsigned short*)(header.pFlag(i)));
                index += 2;
            }
        }
        file.write(info, 54);

        int size = 3 * getWidth() * abs(getHeight());
        for(int i=0; i<size; i+=3)
        {
            file.put(data[i]).put(data[i+1]).put(data[i+2]);
        }
        file.close();
        return true;
    }
    /*
    bool SobelFilter(){
        unsigned char GX [3][3];
        unsigned char GY [3][3];
        GX[0][0] = 1; GX[0][1] = 0; GX[0][2] = -1;
        GX[1][0] = 2; GX[1][1] = 0; GX[1][2] = -2;
        GX[2][0] = 1; GX[2][1] = 0; GX[2][2] = -1;
        
        GY[0][0] = 1; GY[0][1] = 2; GY[0][2] = 1;
        GY[1][0] = 0; GY[1][1] = 0; GY[1][2] = 0;
        GY[2][0] = -1; GY[2][1] = -2; GY[2][2] = -1;
        
        for(int i=0; i<getHeight(); ++i)
        {
            pixel[i] = new pixel [getWidth()];
            for(int j=0; j<getWidth(); ++j)
            {
                
            }
        }
        
        for(int i=0; i<size; ++i)
        {
            unsigned char X1, X2, X3, X4, X5, X6, X7, X8, X9;
            
            unsigned char G, Gx, Gy;
            
        }
        return true;}
     */
};

#endif // __BMPIMG_H__
