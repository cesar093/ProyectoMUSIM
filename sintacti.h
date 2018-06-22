#ifndef sintacti_H
#define sintacti_H
#include "lexico.h"
#include "genera.h"
#include <stdlib.h>
#include <ctype.h>
using namespace std;
class Sintactico{
void programa (void);
void bloque (void);
void sentencia (void);
void otra_sentencia (void);
void asignacion(void);
void lectura (void);
void escritura(void);
void condicional(void);
void comparacion(void);
void variable(void);
void expresion(void);
void termino(void);
void mas_terminos(void);
void factor(void);
void mas_factores(void);
void constante(void);
void errores (int codigo);
Lexico lexico; //objeto léxico miembro de la clase
GeneraCodigo generaCodigo;
public:
Sintactico(const char *fuente, const char *objeto, int traza);
~Sintactico(void);
};

Sintactico::Sintactico(const char *fuente, const char *objeto,int traza):lexico(fuente, traza), generaCodigo(objeto)
//se inicializa el constructor de la clase léxico
{
if (lexico.existeTraza())
cout<<"INICIO DE ANALISIS SINTACTICO"<<endl;
programa();
}

/***********************************************************/
Sintactico::~Sintactico(void)
{
if (lexico.existeTraza())
{
cout<<"FIN DE ANALISIS SINTACTICO"<<endl;
cout<<"FIN DE COMPILACION"<<endl;
}
}

/***********************************************************/
void Sintactico::programa(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <PROGRAMA>"<<endl;
token=lexico.siguienteToken();
if (token=='M')
{
	cout<<"M";
	generaCodigo.code();
}
else errores(8);
token=lexico.siguienteToken();
if (token!='{') errores(9);
bloque();
//lexico.devuelveToken(token);
token=lexico.siguienteToken();
cout<<token;
if (token=='}')
{
cout<<"}";
generaCodigo.end();
}
else errores(2);
}

/***********************************************************/
void Sintactico::bloque(void)
{
//char token=' ';
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <BLOQUE>"<<endl;
sentencia();
otra_sentencia();
}

/***********************************************************/
void Sintactico::otra_sentencia(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <OTRA_SENTENCIA>"<<endl;
token=lexico.siguienteToken();
if (token==';')
{
sentencia();
otra_sentencia();
}
else lexico.devuelveToken(token); //vacio
}

/***********************************************************/
void Sintactico::sentencia(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <SENTENCIA>"<<endl;
token=lexico.siguienteToken();
if ((token>='a') && (token<='z'))
{
lexico.devuelveToken(token);
asignacion();
}
else if (token=='R') lectura();
else if (token=='W') escritura();
else if (token=='I') condicional();
else if (token=='}') {
lexico.devuelveToken(token);
return;
}
else errores(6);
}

/***********************************************************/
void Sintactico::asignacion()
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <ASIGNACION>"<<endl;
variable();
token=lexico.siguienteToken();
if (token!='=') errores(3);
expresion();
generaCodigo.store();
}

/***********************************************************/
void Sintactico::variable(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <VARIABLE>"<<endl;
token=lexico.siguienteToken();
if ((token>='a') && (token<='z')) 
{
	generaCodigo.pusha(token);
}
else errores(5);
}

/***********************************************************/
void Sintactico::expresion(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <EXPRESION>"<<endl;
termino();
if (token != ',') mas_terminos();
else lexico.devuelveToken(token); // <vacio>
}

/***********************************************************/
void Sintactico::termino(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <TERMINO>"<<endl;
factor();
if (token != ',') mas_factores();
else lexico.devuelveToken(token); // <vacio>
}

/***********************************************************/
void Sintactico::mas_terminos(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <MAS_TERMINOS>"<<endl;
token=lexico.siguienteToken();
if (token=='+')
{
termino();
generaCodigo.add();
mas_terminos();
}
else if (token =='-')
{
termino();
generaCodigo.neg();
generaCodigo.add();
mas_terminos();
}
else lexico.devuelveToken(token); // <vacio>
}

/***********************************************************/
void Sintactico::factor(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <FACTOR>"<<endl;
token=lexico.siguienteToken();
if ((token>='0') && (token<='9'))
{
lexico.devuelveToken(token);
constante();
}
else if (token=='(')
{
expresion();
token=lexico.siguienteToken();
if (token!=')') errores(4);
}
else
{
lexico.devuelveToken(token);
variable();
generaCodigo.load();
}
}

/***********************************************************/
void Sintactico::mas_factores(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <MAS_FACTORES>"<<endl;
token=lexico.siguienteToken();
switch (token)
{
case '*':factor();
generaCodigo.mul();
mas_factores();
break;
case '/':factor();
generaCodigo.div();
mas_factores();
break;
case '%':factor();
generaCodigo.mod();
mas_factores();
break;
default: //<vacio>
lexico.devuelveToken(token);
}
}

/***********************************************************/
void Sintactico::lectura(void)
{
char token;
token=lexico.siguienteToken();
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <LECTURA> "<<token<<endl;
if((token<'a')||(token>'z')) errores(5);// aqui se verifica que solo lea letras minusculas
generaCodigo.input(token);
}

/***********************************************************/
void Sintactico::escritura(void)
{
char token;
token=lexico.siguienteToken();
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <ESCRITURA> "<<token<<endl;
if ((token<'a') || (token>'z')) errores(5);
generaCodigo.output(token);
}

/***********************************************************/
void Sintactico::condicional(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <CONDICIONAL>"<<endl;
comparacion();
token=lexico.siguienteToken();
if ((token!=',')) errores(13);
sentencia();
generaCodigo.etiqueta();
if ((token!=',')) errores(13);
token=lexico.siguienteToken();
sentencia();
generaCodigo.etiqueta2();
}


/***********************************************************/
void Sintactico::comparacion(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <COMPARACION>"<<endl;
token=lexico.siguienteToken();
if ((token>='a') && (token<='z')) 
{
	generaCodigo.cond1(token);
}
else errores(5);

token=lexico.siguienteToken();
if ((token=='=') || (token=='<')|| (token=='>')) {
	generaCodigo.cond2(token);
token=lexico.siguienteToken();
if (((token>='0') && (token<='9')) || ((token>='a') && (token<='Z')) || (token='.')) {
	generaCodigo.cond3(token);
}
}
else errores(12);
}


/************************************************/
void Sintactico::constante(void)
{
char token;
if (lexico.existeTraza())
cout<<"ANALISIS SINTACTICO: <CONSTANTE> "<<endl;
token=lexico.siguienteToken();
if (((token>='0') && (token<='9')) || ((token>='a') && (token<='Z')) || (token='.')) 
{
generaCodigo.pushc(token);
}
else errores(7);
}

/***********************************************************/
void Sintactico::errores(int codigo)
{
int x;
cout<<"LINEA "<<lexico.lineaActual();
cout<<" ERROR SINTACTICO "<<codigo;
switch (codigo)
{
case 1 :cout<<" :ESPERABA UN ;"<<endl;break;
case 2 :cout<<" :ESPERABA UNA }"<<endl;break;
case 3 :cout<<" :ESPERABA UN ="<<endl;break;
case 4 :cout<<" :ESPERABA UN )"<<endl;break;
case 5 :cout<<" :ESPERABA UN IDENTIFICADOR"<<endl;break;
case 6 :cout<<" :INSTRUCCION DESCONOCIDA"<<endl;break;
case 7 :cout<<" :ESPERABA UNA "<<endl;break;
case 8 :cout<<" :ESPERABA UNA M DE MAIN"<<endl;break;
case 9 :cout<<" :ESPERABA UNA {"<<endl;break;
case 11:cout<<" :Se esperaba un \' "<<endl;break;
case 12:cout<<" :Se esperaba un operando de comparacion' "<<endl;break;
case 13:cout<<" :Se esperaba una , ' "<<endl;break;
default:
cout<<" :NO DOCUMENTADO"<<endl;
}
cin>>x;
exit(-(codigo+100));
}
#endif
