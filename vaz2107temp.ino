#include <math.h>
// number of items in an array
#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))
// for (byte i = 0; i < NUMITEMS (profName); i++)   profName - massiv
float RtableMassiv[] = {963000,670100,471700,336500,242600,177000,130400,97070,72930,55330,42320,32650,25390,19900,15710,12490,10000,8057,6531,5327,4369,3603,2986,2488,2083,1752,1481,1258,1072,917.7,788.5,680,588.6,511.2,445.4,389.3,341.7,300.9,265.4,234.8,208.3,185.3,165.3};
float TempTableMassiv[] = {-55,-50,-45,-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155};
float u = 0;
float Rtemp = 0;
float temp = 0;

struct Params {
 float TempMassiv[10] = {0,0,0,0,0,0,0,0,0,0}; 
 int Relay = 0; 
  };
  
Params MyParams;
Params* MyParamsPointer = &MyParams;

void setup() {
  // put your setup code here, to run once:
Serial.begin(19200);
pinMode(4, OUTPUT);
// 15 pin = A1 reading voltage
// 4 pin = D4 relay control
}

void loop() {
  for (unsigned int j = 0; j < 10; j++)
  {
    float AvgTempCooler10 = 0;
    Serial.print("temp massiv: ");
    for (int i = 0 ; i < 10; i++)
    {
      AvgTempCooler10 = AvgTempCooler10 + (*MyParamsPointer).TempMassiv[i];
        
        Serial.print((*MyParamsPointer).TempMassiv[i]);Serial.print(" ");
    }
    Serial.println(" ");
    Serial.print("Relay state: ");
    Serial.println((*MyParamsPointer).Relay);
    AvgTempCooler10 = AvgTempCooler10 / 10;
    if ( (*MyParamsPointer).Relay == 1 || AvgTempCooler10 > 87 ) 
    {
      digitalWrite(4, 1);
      MyParamsPointer -> Relay = 1;
    } 
      else 
    {
      digitalWrite(4, 0);
    }
    if ( (*MyParamsPointer).Relay == 1 && AvgTempCooler10 < 81 )
    {
      digitalWrite(4, 0);
      MyParamsPointer -> Relay = 0;
    }
    int massivpoint = 0;
    float massivsrednee = 0;
    
        for (int i = 0; i<100; i++)
        {
          massivsrednee = massivsrednee + analogRead( 15 );
          delay(5);
        }
        float u = ((massivsrednee/100) * 5.0) / 1023;
        Serial.print("u: ");
        Serial.println(u);
        float Rtemp = (u * 9880)/(5.0 - u);
        Serial.print("R temp: ");
        Serial.println(Rtemp);
        for (unsigned int i = 0; i<NUMITEMS (RtableMassiv); i++)
        {
          if (Rtemp > RtableMassiv[i])
          {
            massivpoint = i;
            break;
          }
        }
          Serial.print("position: ");
        Serial.println(massivpoint);
        float TempCdegree = TempTableMassiv[massivpoint-1] + (Rtemp - RtableMassiv[massivpoint-1])/((RtableMassiv[massivpoint] - RtableMassiv[massivpoint-1])/5);
        Serial.print("TempCdegree: ");
        Serial.println(TempCdegree);
        MyParamsPointer -> TempMassiv[j]=TempCdegree;
        delay(1000);
  }   
}

/*
************************************
*****TEMP TABLE*********************
    Rt/R25  a (%/K) 
-55 96,3    7.4 963000
-50 67,01   7.2 670100
-45 47,17   6.9 471700
-40 33,65   6.7 336500
-35 24,26   6.4 242600
-30 17,7    6.2 177000
-25 13,04   6.0 130400
-20 9,707   5.8 97070
-15 7,293   5.6 72930
-10 5,533   5.5 55330
-5  4,232   5.3 42320
0   3,265   5.1 32650
5   2,539   5.0 25390
10  1,99    4.8 19900
15  1,571   4.7 15710
20  1,249   4.5 12490
25  1       4.4 10000
30  0,8057  4.3 8057
35  0,6531  4.1 6531
40  0,5327  4.0 5327
45  0,4369  3.9 4369
50  0,3603  3.8 3603
55  0,2986  3.7 2986
60  0,2488  3.6 2488
65  0,2083  3.5 2083
70  0,1752  3.4 1752
75  0,1481  3.3 1481
80  0,1258  3.2 1258
85  0,1072  3.2 1072
90  0,09177 3.1 917,7
95  0,07885 3.0 788,5
100 0,068   2.9 680
105 0,05886 2.9 588,6
110 0,05112 2.8 511,2
115 0,04454 2.7 445,4
120 0,03893 2.6 389,3
125 0,03417 2.6 341,7
130 0,03009 2.5 300,9
135 0,02654 2.5 265,4
140 0,02348 2.4 234,8
145 0,02083 2.4 208,3
150 0,01853 2.3 185,3
155 0,01653 2.3 165,3
*/
