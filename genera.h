#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>

class GeneraCodigo
{
char *nombreFichero; // Nombre del fichero objeto de salida
FILE *salida; // Fichero objeto de salida
public:
int contador = 1;
int contetiqueta = 1;

GeneraCodigo(const char *unNombreFichero);
~GeneraCodigo();
void code();
void pushc(const char constante);
void pusha(const char direccion);
void load();
void store();
void neg();
void add();
void mul();
void div();
void mod();
void input(const char direccion);
void output(const char direccion);
void end();
void cond1(const char direccion);
void cond2(const char direccion);
void cond3(const char direccion);
void cond4(const char direccion);
void etiqueta();
void etiqueta2();
void etiqueta3();
};

GeneraCodigo::GeneraCodigo(const char *unNombreFichero)
{
if ((salida=fopen(unNombreFichero,"w"))==NULL)
{
cout<<"No se puede crear el fichero"<<unNombreFichero<<endl;
exit(-3);
}
}

GeneraCodigo::~GeneraCodigo(void)
{
fclose(salida);
}

void GeneraCodigo::code()
{
cout<<".CODE"<<endl;
fputs(".CODE\n",salida);
}

void GeneraCodigo::pushc(const char constante)
{
cout<<"PUSHC "<<constante<<endl;
fputs("PUSHC ",salida);
fputc(constante,salida);
fputc('\n',salida);
}

void GeneraCodigo::pusha(char direccion)
{
cout<<"PUSHA "<<direccion<<endl;
fputs("PUSHA ",salida);
fputc(direccion,salida);
fputc('\n',salida);
}

void GeneraCodigo::load()
{
cout<<"LOAD"<<endl;
fputs("LOAD\n",salida);
}
 
void GeneraCodigo::store()
{
	cout<<"STORE"<<endl;
	fputs("STORE\n",salida);
}

void GeneraCodigo::neg()
{
cout<<"NEG"<<endl;
fputs("NEG\n",salida);
}

void GeneraCodigo::add()
{
cout<<"ADD"<<endl;
fputs("ADD\n",salida);
}

void GeneraCodigo::mul()
{
cout<<"MUL"<<endl;
fputs("MUL\n",salida);
}

void GeneraCodigo::div()
{
cout<<"DIV"<<endl;
fputs("DIV\n",salida);
}

void GeneraCodigo::mod()
{
cout<<"MOD"<<endl;
fputs("MOD\n",salida);
}

void GeneraCodigo::input(const char direccion)
{
cout<<"INPUT "<<direccion<<endl;
fputs("INPUT ",salida);
fputc(direccion,salida);
fputc('\n',salida);
}

void GeneraCodigo::output(const char direccion)
{
cout<<"OUTPUT "<<direccion<<endl;
fputs("OUTPUT ",salida);
fputc(direccion,salida);
fputc('\n',salida);
}


void GeneraCodigo::cond1(const char caracter)
{
fputs("T",salida);
fprintf(salida, "%d", contador);
fputs(" = (",salida);
fputc(caracter, salida);
}

void GeneraCodigo::cond2(const char caracter)
{
fputc(caracter,salida);
}

void GeneraCodigo::cond3(const char caracter)
{
fputc(caracter, salida);
fputs(")\n",salida);
cout<< "IF T"<<contador<<" GOTO L"<<contetiqueta<< endl;
fputs("IF T",salida);
fprintf(salida, "%d", contador);
fputs(" GOTO L",salida);
fprintf(salida, "%d", contetiqueta);
fputc('\n',salida);
cout<< "GOTO L"<<contetiqueta+1<< endl;
fputs("GOTO L",salida);
fprintf(salida, "%d", contetiqueta+1);
fputc('\n',salida);
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
contador++;
}

void GeneraCodigo::cond4(const char caracter)
{
fputc(caracter, salida);
fputs(")\n",salida);
cout<< "L"<<(contetiqueta-1)<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta-1);
fputs(":\n",salida);
cout<< "IF T"<<contador<<" GOTO L"<<contetiqueta<< endl;
fputs("IF T",salida);
fprintf(salida, "%d", contador);
fputs(" GOTO L",salida);
fprintf(salida, "%d", contetiqueta);
fputc('\n',salida);
cout<< "GOTO L"<<contetiqueta+1<< endl;
fputs("GOTO L",salida);
fprintf(salida, "%d", contetiqueta+1);
fputc('\n',salida);
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
contador++;
}

void GeneraCodigo::etiqueta()
{
contetiqueta++;
cout<< "GOTO L"<<contetiqueta+1<< endl;
fputs("GOTO L",salida);
fprintf(salida, "%d", contetiqueta+1);
fputc('\n',salida);
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
}

void GeneraCodigo::etiqueta2()
{
contetiqueta++;
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
contetiqueta++;
}


void GeneraCodigo::etiqueta3()
{
contetiqueta++;
cout<< "GOTO L"<<contetiqueta-2<< endl;
fputs("GOTO L",salida);
fprintf(salida, "%d", contetiqueta-2);
fputc('\n',salida);
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
contetiqueta++;
}


void GeneraCodigo::end()
{
cout<<"END"<<endl;
fputs("END\n",salida);
}
