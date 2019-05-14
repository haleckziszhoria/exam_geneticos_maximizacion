#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iomanip>

#define col 9
using namespace std;


bool comprobacion_optimo(int ar[][col],int fil){
    int sum=0;
    int indice=6,limite;

    if(ar[fil][0]==1 && ar[fil][1]==1)
        limite = 13;
    else
        limite = 99;

    for(int i=2;i<col;i++){
        if(ar[fil][i]==1)
            sum=sum+pow(2,indice);

        indice--;
    }
    if(sum<=limite)
        return true;
    else
        return false;
}

void imprimir_poblacion_valor(int ar[][col],int fil, float ar2[]){
    cout<<"valor binario:    || Valor decimal: "<<endl;
    for(int i=0; i<fil;i++){

        for(int j=0; j<col;j++){
            cout<<ar[i][j]<<" ";
        }
        cout<<" = "<<ar2[i]<<endl;
    }
}

float binario_decimal(int ar[][col],int fil){
    float entero=0,decimal=0;
    float indice1=1,indice2=6;

    for(int i=0;i<2;i++){
        if(ar[fil][i]==1)
            entero=entero+pow(2,indice1);

        indice1--;
    }
    for(int i=2;i<col;i++){
        if(ar[fil][i]==1)
            decimal=decimal+pow(2,indice2);

        indice2--;
    }
    return (entero + decimal/100);
}

void valores_decimales(int ar[][col],int fil,float ar2[]){
    for(int i=0; i<fil;i++){
        ar2[i] = binario_decimal(ar,i);
    }
}
//void ordenar_matriz(int ar[][col],int fil,float ar2[]){
//    float temp2;
//    int artemp[col];
//    for(int i=0;i<fil;i++){
//        for(int j=i+1;j<fil;j++){
//            if(ar2[i]>ar2[j]){
//                temp2 = ar2[i];
//                ar2[i] = ar2[j];
//                ar2[j] = temp2;
//
//                for(int k=0;k<col;k++){
//                    artemp[k] = ar[i][k];
//                    ar[i][k] = ar[j][k];
//                    ar[j][k] = artemp[k];
//                }
//            }
//        }
//    }
//}


void seleccion_PC(float ar2[],float pc[][2],int fil){
    cout<<"Probabilidad de Cruce"<<endl;
    for(int i=0;i<fil;i++){
        pc[i][0] = i;
        pc[i][1] = 1.00-(1.00*ar2[i]/3.14);
        pc[i][1] = roundf(pc[i][1] * 100) / 100;
        cout<<"Individuo: "<<i<<" PC: "<<pc[i][1]<<" %"<<endl;
    }

    float temp1,temp2;
    for(int i=0;i<fil-1;i++){
        for(int j=i+1;j<fil;j++){
            if(pc[i][1]<pc[j][1]){
                temp1 = pc[i][1];
                pc[i][1] = pc[j][1];
                pc[j][1] = temp1;

                temp2 = pc[j][0];
                pc[j][0] = pc[i][0];
                pc[i][0] = temp2;
            }
        }

    }

}


void cruzar_cromosomas(int ar[][col],float ar2[],float pc[][2],int fil){
    int pivot;
    int indice1,indice2;
    int temp2;

    cout<<"Cruce de Individuos (6 con mejores probabilidades)"<<endl;
    for(int i=0;i<6;i+=2){
        pivot = 0+rand()%9;

        cout<<"========== Cruce entre Individuos:"<<int(pc[i][0])<<" y "<<int(pc[i+1][0])<<"========="<<endl;
        cout<<"Prob. Cruce: "<<pc[i][1]<<" - "<<pc[i+1][1];
        cout<<" || Pivot: "<<pivot<<endl;

        for(int j=pivot+1;j<col;j++){
            indice1=int(pc[i][0]);
            indice2=int(pc[i+1][0]);
            temp2=ar[indice1][j];
            ar[indice1][j]=ar[indice2][j];
            ar[indice2][j]=temp2;
        }
    }
    cout<<"Despues de Cruzar:"<<endl;
    valores_decimales(ar,fil,ar2);
}

void PM_mutacion(int ar[][col],float ar2[],float pm[][2],float pc[][2],int fil){
    cout<<"=========MUTACION========="<<endl;

    for(int i=0;i<fil;i++){
        pm[i][0] = pc[i][0];
        pm[i][1] = float(0+rand()%100)/100;
        pm[i][1] = roundf(pm[i][1] * 100) / 100;
        if(i<3)
            pm[i][1]=0.30;

        cout<<"Individuo: "<<pm[i][0]<<" PM: "<<pm[i][1]<<" %"<<endl;
    }
    int rmpivot;
    int cont(0);
    for(int i=0;i<fil;i++){
        if(pm[i][1]>=0.50){
            rmpivot = 0+rand()%9;
            if(ar[int(pm[i][0])][rmpivot]==1)
               ar[int(pm[i][0])][rmpivot] = 0;
            else
                ar[int(pm[i][0])][rmpivot] = 1;

            cout<<"----------------------------------------------"<<endl;
            cout<<"Individuo Nro: "<<pm[i][0];
            cout<<" Probabilidad de Mutacion: "<<pm[i][1];
            cout<<" Mutacion en Posicion Nro: "<<rmpivot<<endl;
            cont++;
        }

   }
   cout<<"Cantidad Total de Mutaciones: "<<cont<<endl;
   valores_decimales(ar,fil,ar2);

}
int main(){
    srand(time(NULL));
    int filas,temp =10,contador(0),iteraciones(0);
    filas = temp;
    int matriz [filas][col];
    //Declarando Probabilidad de Cruce y Probabilidad de Mutación
    float PC[filas][2],PM[filas][2];
    float decimal[filas];
    float mejor_indiv[11]={};
    //GENERANDO LA POBLACION
    for(int i=0; i<temp;i++){
        for(int j=0; j<col;j++){
            matriz[i][j] = 0+rand()%2;
        }
        if(comprobacion_optimo(matriz,i)==false){
            i--;
        }
    }
    valores_decimales(matriz,10,decimal);


    while(contador<=1){
        iteraciones++;
        cout<<"||||||||||||||||||||||||||||||||||| GENERACION Nro :"<<iteraciones<<" |||||||||||||||||||||||||||||||||||"<<endl;
        imprimir_poblacion_valor(matriz,10,decimal);
        seleccion_PC(decimal,PC,10);
        cruzar_cromosomas(matriz,decimal,PC,filas);
        imprimir_poblacion_valor(matriz,10,decimal);
        PM_mutacion(matriz,decimal,PM,PC,filas);
        imprimir_poblacion_valor(matriz,10,decimal);

        if(mejor_indiv[10]<PC[0][1]){
            mejor_indiv[9] = PC[0][0];
            for(int k=0;k<9;k++)
                mejor_indiv[k] = float(matriz[int(mejor_indiv[9])][k]);
            mejor_indiv[10] = PC[0][1];
        }
        else
            contador++;
    }

    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%% MEJOR INDIVIDUO %%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
    cout<<"INDIVIDUO Nro: "<<mejor_indiv[9]<<endl;
    cout<<"valor decimal: "<<endl;
    for(int i=0;i<9;i++){
        cout<<mejor_indiv[i]<<" ";
    }


    return 0;
}
