#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string>
#define TAM_BUFFER 100
using namespace std;
class Lexico
{
char *nombreFichero;//Nombre del fichero fuente
FILE* entrada; //Fichero de entrada
int n1; //Número de línea
int traza; //Control de traza
char buffer[TAM_BUFFER]; //Buffer auxiliar de caracteres
int pBuffer; //Posición en el buffer
public:
Lexico(const char *unNombreFichero, int una_traza=0);
~Lexico(void);
char siguienteToken(void);
void devuelveToken(char toke);
int lineaActual(void){return n1; };
int existeTraza(void){if(traza)return 1; else return 0;}
};
Lexico::Lexico(const char *unNombreFichero, int una_traza)
{
entrada=fopen(unNombreFichero, "rt");
if((entrada==NULL))
{
cout<<"No se puede abrir el archivo"<<endl;
system("sleep 1");
exit(-2);
}
if(una_traza) traza=1;
else traza = 0;
n1=1; //Se inicializa el contador de línea
pBuffer=0; //Se inicializa la posición del buffer
}
Lexico::~Lexico()
{
fclose(entrada);
}
char Lexico::siguienteToken(void)
{
char car;
while((car=((pBuffer>0) ? buffer[--pBuffer]:getc(entrada)))!=EOF)
{
if(car==' ') continue;
if(car=='\n'){++n1; continue;}
break;
}
if(traza) cout<<"ANALIZADOR LEXICO: Lee el token "<<car<<endl;
switch(car)
{
case'M': //palabra reservada
case'R': //palabra reservada
case'W': //palabra reservada
case'I':
case'=': //asignación
case'(': //parentesis
case')':
case';': //separadores
case'}': //separadores
case'{':
case'.': //fin de programa
case'+': //operador
case'*':
case'-':
case'/':
case'%':
case'<':
case'>':
case',':
return(car);
}
if(islower(car))return(car); //variable
else if(isdigit(car)) return(car); //constante
else
{
cout<<"Error Lexico: Token Desconocido"<<endl;
system("sleep 1");
exit(-4);
}
return(car);
}
void Lexico::devuelveToken(char token)
{
if(pBuffer>TAM_BUFFER)
{
cout<<"ERROR: Desbordamiento del buffer del analizador lexico"<<endl;
system("sleep 1");
exit(-5);
}
else
{
buffer[pBuffer++]=token;
if(existeTraza())
cout<<"ANALIZADOR LEXICO: Recibe en buffer el token"<<token<<endl;
system("sleep 1");
}
}
