//Proyecto ABC ----- "AGENDA DE CONTACTOS"
/*
 =   ID     -   APELLIDOS   -    NOMBRES                                               
 =ID:206774  Sanchez Vallin    Francisco Javier
 =ID:246871  Calzada González  Georgina Guadalupe
 =ID:376905  Andrade Olvera    Dulce Mariana 
 =ID:453701  Arteaga Delgado   Elia Guadalupe                                                                            
*/
//Equipo #9

//Librerías
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //colores

using namespace std;
#define CONTACTOS 50 //Limite de contactos en la agenda

//Estructuras con variables dinamicas 
struct RedesSociales{
    char *correo;//Quitamos [] no son necesarios
    char *insta;//Variable dinamica
    char *facebook;//Variable dinamica
};//RedesSociales

struct Contacto{
    char *curp;//Variable dinamica
    char *nombre;//Variable dinamica
    long long int tel;//No es dinamica es estatica
	bool tieneRed;//Controla si tiene red social
    struct RedesSociales redes;//Variable a struct
};//Contacto

void menu(); //buenas tardes senora como se encuentra el dia de hoy
void agregar(Contacto*&, int &); // en agenda * por que es amperson y & para cambiar la direccion
void buscar(Contacto*, int);// no se pone agenda por que no es necesario el nombre de la variable
void actualizar(Contacto*, int);//Actualiza el contacto
void extras(Contacto*, int);//Abre un sub menu con demas opciones
void contInsta(Contacto*, int);//Muestra los que tienen insta
void contSin(Contacto*, int);//Muestra los que no tienen redes
void continuar();//Retorna al usuario en caso de que inserte una opcion no valida
void mostrar(Contacto*, int);//Muestra el contacto encontrado
bool verificarOpc(int);//Se verifica la opcion que de el usuario
bool limpiar(bool,int,int);//limpia y verifica opciones

int main(){
	system("color 87");//color de fondo
	Contacto *agenda = new Contacto[CONTACTOS];//inicializamos la variable dinamica
    //Una estructura con el nombre de agenda de tipo Data
    int num=0, opcion=0;//opciones del menu
    bool validar=false;//valida una opcion
	
    do{
        menu();//llamada a la funcion menu
		cin>>opcion;
		limpiar(cin.fail(),0,0);//llamada a la funcion limpiar
        fflush(stdin);//limpia el buffer
        
        switch(opcion){
            case 1:
                agregar(agenda,num);//llamada a la funcion agregar
                break;
            case 2:
                buscar(agenda,num);//llamada a la funcion buscar
                break;
            case 3:
                actualizar(agenda,num);//llamada a la funcion limpiar
                break;
            case 4:
                extras(agenda,num);//llamada a la funcion extras
                break;
            case 5://SALIR
                printf("\x1b[38;5;74m");cout<<endl<<"Programa finalizado..."<<endl;
                break;
            default:
                printf("\x1b[38;5;74m");cout << "\nOpcion no valida"<<endl;
                continuar();
                break;
        }//switch
    }while(opcion!=5);
    delete[] agenda; // Liberar memoria al finalizar el programa
    
    return 0;
}//main

void menu(){
    printf("\x1b[38;5;222m");cout<<"\n======== AGENDA DE CONTACTOS ========\n"<<endl;
	printf("\x1b[38;5;231m");cout<<" Agregar nuevo contacto...........(1)\n";
	printf("\x1b[38;5;231m");cout<<" Buscar contacto..................(2)\n";
	printf("\x1b[38;5;231m");cout<<" Actualizar contacto..............(3)\n";
	printf("\x1b[38;5;231m");cout<<" Extras...........................(4)\n";
	printf("\x1b[38;5;231m");cout<<" Salir............................(5)\n\n";
   	printf("\x1b[38;5;231m");cout<<" Ingrese su opcion: ";
}//menu

void agregar(Contacto *&agenda, int &numContactos) {
	Contacto nuevo;//nueva estructura de tipo contacto con el nombre de nuevo
	char auxChar[50];//auxiliar de char
	int resp=0, opcion=0,numero=0;//opciones del menu
	bool validar=false, insta=false, facebook=false, correo=false;//valid la opcion

	system("cls"); 
    printf("\x1b[38;5;222m");cout<<"\n========= AGREGAR CONTACTO =========\n"<<endl;
  
    if (numContactos>=CONTACTOS){//En caso de que no se puedan agregar mas contactos
        printf("\x1b[38;5;90m");cout<<"No se pueden agregar más contactos"<< endl<<"La agenda esta llena<<"<<endl;
        return;
    }//if
	//LLENAR DATOS	
	do{//Nombre===========
 	   	printf("\x1b[38;5;231m");cout<<" Nombre: ";
		cin.getline(auxChar,31,'\n');//dejo 31 porque son 30 caracteres + el salto de linea
	}while(limpiar(cin.fail(),1,0)!=0);
	nuevo.nombre=new char[strlen(auxChar)+1];//Se le agrega memoria dinamica conforme al numero de caracteres que ocpe su nombre
	strcpy(nuevo.nombre,auxChar);//Se copea la cadena
	do{//telefono========
		printf("\x1b[38;5;231m");cout<<" Telefono: ";
	    cin>>nuevo.tel;
	    if(nuevo.tel<1000000000||nuevo.tel>10000000000){//Se valida el numero
			numero=1;
		}else{
			numero=0;
		}//else
	}while(limpiar(cin.fail(),2,numero)!=0);    
	
    do{//curp========================
    	printf("\x1b[38;5;231m");cout<< " CURP: ";//-----------------------------------------------------------------AQUI FALTA VALIDAR(Resuelto)
  		cin>>auxChar;
  		if(strlen(auxChar)!=18){//Se valida la curp
		  	numero=1;
		  }else{
		  	numero=0;
		  }//else
	}while(limpiar(cin.fail(),3,numero)!=0);
	nuevo.curp=new char[strlen(auxChar)+1];
	strcpy(nuevo.curp,auxChar);    
	do{
		printf("\x1b[38;5;231m");cout<<" Desea agregar alguna red social? Si (1)  No(0)\n";
		printf("\x1b[38;5;231m");cout<<" Ingrese su opcion: ";
		cin>>nuevo.tieneRed;
	}while(limpiar(cin.fail(),0,0)!=0);//Se verifica si se eligio un 1 o un 0, si no se repite la pregunta//====================================	
    nuevo.redes.correo = new char[50];
  	nuevo.redes.insta = new char[50];
    nuevo.redes.facebook = new char[50];
	
	if(nuevo.tieneRed==true){
		//REDES SOCIALES
		//inicializamos las varibles de la estructura que son dinamicas "Solo si tiene para no gastar espacio"
		system("cls");
		do{
			cout<<endl;
			printf("\x1b[38;5;160m");cout<<" Correo electronico...............(1)\n";
			printf("\x1b[38;5;211m");cout<<" Cuenta de instagram..............(2)\n";
			printf("\x1b[38;5;21m");cout<<" Cuenta de facebook...............(3)\n";
			printf("\x1b[38;5;231m");cout<<" Regresar.........................(4)\n";
			printf("\x1b[38;5;231m");cout<<"\nSeleccione la red social a agregar: ";
			cin>>opcion;
			limpiar(cin.fail(),0,0);
			switch(opcion){
				system("cls");
				case 1:
					do{//Correo===========
						correo=true;//Se valida el correo
						printf("\x1b[38;5;160m");cout<<"Introduzca el correo electronico: ";
						cin>>nuevo.redes.correo;//dejo 31 porque son 30 caracteres + el salto de linea
						if(strlen(nuevo.redes.correo)>30){
							numero=1;
						}else{
							numero=0;
						}//else
					}while(limpiar(cin.fail(),4,numero)!=0);
					break;
				case 2:
					do{//Insta===========
						insta=true;
						printf("\x1b[38;5;211m");cout<<"Introduzca la cuenta de instagram: ";
						cin>>nuevo.redes.insta;//dejo 31 porque son 30 caracteres + el salto de linea
						if(strlen(nuevo.redes.insta)>30){
							numero=1;
						}else{
							numero=0;
						}//else
					}while(limpiar(cin.fail(),5,numero)!=0);
					break;
				case 3:
					do{//Facebook===========
						facebook=true;
						printf("\x1b[38;5;21m");cout<<"Introduzca la cuenta de facebook: ";
						cin.ignore();
    						cin.getline(nuevo.redes.facebook,31);
						if(strlen(nuevo.redes.facebook)>30){
							numero=1;
						}else{
							numero=0;
						}//else
					}while(limpiar(cin.fail(),6,numero)!=0);
					break;
				case 4:
					system("cls");
					break;
				default:
					printf("\x1b[38;5;74m");cout<<"Opcion invalida.\n";
					continuar();
					break;
				system("cls");
			}//swicth
			if(opcion<4&&opcion>0){
				do{
					printf("\x1b[38;5;231m");cout<<"\n¿Desea agregar otra red social? Si (1)  No(0)\n";
					cin>>resp;
					fflush(stdin);
				}while(!verificarOpc(resp));
			}//if
			system("cls");
		}while(opcion!=4&&resp==1);
	}else{
	strcpy(nuevo.redes.correo,"\0");
	strcpy(nuevo.redes.insta,"\0");
	strcpy(nuevo.redes.facebook,"\0");
	system("cls");
	
	}//else
	if(correo==false){nuevo.redes.correo= new char[30];strcpy(nuevo.redes.correo,"*\0");}
	if(insta==false){nuevo.redes.insta= new char[30];strcpy(nuevo.redes.insta,"*\0");}	
	if(facebook==false){nuevo.redes.facebook= new char[30];strcpy(nuevo.redes.facebook,"*\0");}	
    
	agenda[numContactos++] = nuevo;
    printf("\x1b[38;5;231m");cout<<"Contacto agregado correctamente"<<endl;
    continuar();
    cin.clear();
    
}//agregar

void buscar(Contacto *agenda, int numContactos){
    bool encontrado=false, validar=false;//valida entradas
	char clave[50];	
	int opcion=0,numero=0;	
	
	if(numContactos==0){//En caso de que la agenda este vacia
    	cout<<"\n La agenda esta vacia\n";
    	continuar();
    	return;
	}//if
	
	do{
		system("cls");
		printf("\x1b[38;5;222m");cout<<"\n========== BUSCAR CONTACTO ==========\n"<<endl;
		printf("\x1b[38;5;231m");cout<<" Nombre............................(1)\n";
		printf("\x1b[38;5;231m");cout<<" Curp..............................(2)\n";
		printf("\x1b[38;5;231m");cout<<" Regresar..........................(3)\n\n";
		printf("\x1b[38;5;231m");cout<<" Seleccione una opcion: ";
		fflush(stdin);
		cin>>opcion;
		if(cin.fail()){
			cin.clear();cin.ignore(40,'\n');
		}//ignora la entrada del buffer}//Esto evita que al meter una letra explote
		switch(opcion){
			case 1:
				fflush(stdin);
				do{//Nombre===========
					printf("\x1b[38;5;231m");cout<<" Introduzca el nombre a buscar: ";	
					cin.getline(clave,31,'\n');//dejo 31 porque son 30 caracteres + el salto de linea
				}while(limpiar(cin.fail(),1,0)!=0);
				for(int i=0; i<numContactos; i++){
       				if(strcmp(clave, agenda[i].nombre)==0){
        				mostrar(agenda, i);
        				continuar();
        				encontrado = true;
       				}//if 
    			}//for
    			if(!encontrado) {
        			printf("\x1b[38;5;74m");cout<<" Contacto no encontrado"<<endl;
        			continuar();
    			}//if
				break;
			case 2:
				printf("\x1b[38;5;231m");cout<<" Introduzca la curp a buscar: ";
				 do{//curp========================
  					cin>>clave;
  						if(strlen(clave)!=18){
						  	numero=1;
					    }else{
						  	numero=0;
						}//else
				}while(limpiar(cin.fail(),3,numero)!=0);
				for(int i=0; i<numContactos; i++){
       				if(strcmp(clave, agenda[i].curp)==0){
        				mostrar(agenda, i);
        				continuar();
        				encontrado = true;
       				}//if prinicipal
    			}//for
    			if (encontrado==false) {
        			printf("\x1b[38;5;74m");cout<<" Contacto no encontrado"<<endl;
        			continuar();
    			}//if
    			encontrado=false;
				break;
			case 3:
				break;
			default:
			printf("\x1b[38;5;74m");cout<<"Opcion invalida.\n";
			continuar();
			break;
		}//switch
		
	}while(opcion!=3);
	system("cls");
	
}//buscar

void actualizar(Contacto *agenda, int numContactos){
    char clave[50], auxChar[50];
    bool validar=false;
    int numero=0;
    bool opc=false;
   
   	cin.clear();
    
    if(numContactos==0){
    	cout<<"\n La agenda esta vacia\n";
    	continuar();
    	return;
	}//if
	
	system("cls");
	printf("\x1b[38;5;222m");cout<<"\n======== ACTUALIZAR CONTACTO ========\n"<<endl;
    printf("\x1b[38;5;231m");cout << "Ingrese nombre o CURP del contacto a actualizar: "<<endl;
    do{//Nombre o curp===========
 	   	printf("\x1b[38;5;231m");cout<<" Nombre: ";
		cin.getline(clave,31,'\n');//dejo 31 porque son 30 caracteres + el salto de linea
	}while(limpiar(cin.fail(),1,0)!=0);
    
    for(int i=0; i<numContactos; i++){
        if(strcmp(clave, agenda[i].nombre)==0||strcmp(clave, agenda[i].curp)==0){
            printf("\x1b[38;5;231m");cout<<" Ingrese nueva informacion para el contacto: "<<endl;
            do{//Nombre===========
 	   			printf("\x1b[38;5;231m");cout<<" Nombre: ";
				cin.getline(auxChar,31,'\n');//dejo 31 porque son 30 caracteres + el salto de linea
			}while(limpiar(cin.fail(),1,0)!=0);
            if(strlen(auxChar)>strlen(agenda[i].nombre)){
            	agenda[i].nombre=(char*)realloc(agenda[i].nombre, strlen(auxChar)*sizeof(char));
			}//if
			strcpy(agenda[i].nombre,auxChar);
			
			do{//telefono========
				printf("\x1b[38;5;231m");cout<<" Telefono: ";
	    		cin>>agenda[i].tel;
	    			if(agenda[i].tel<1000000000||agenda[i].tel>10000000000){numero=1;}else{numero=0;}
			}while(limpiar(cin.fail(),2,numero)!=0);    
			
			do{//curp========================
    			printf("\x1b[38;5;231m");cout<< " CURP: ";
  				cin>>auxChar;
  					if(strlen(auxChar)!=18){numero=1;}else{numero=0;}
			}while(limpiar(cin.fail(),3,numero)!=0);
            	if(strlen(auxChar)>strlen(agenda[i].curp)){
            		agenda[i].curp=(char*)realloc(agenda[i].curp, strlen(auxChar)*sizeof(char));
			}//if
			strcpy(agenda[i].curp,auxChar);	
			cin>>opc;
			limpiar(cin.fail(),0,0);
			if(opc==1){
				if(agenda[i].tieneRed==false){
					agenda[i].tieneRed=true;
				}//if
				do{//Correo===========
					printf("\x1b[38;5;160m");cout<<"Introduzca el correo electronico: ";
					cin>>agenda[i].redes.correo;//dejo 31 porque son 30 caracteres + el salto de linea
					if(strlen(agenda[i].redes.correo)>30){
							numero=1;
						}else{
							numero=0;
						}//else
				}while(limpiar(cin.fail(),4,numero)!=0);
			
				do{//Instagram===========
					printf("\x1b[38;5;211m");cout<<"Introduzca la cuenta de instagram: ";
					cin>>agenda[i].redes.insta;//dejo 31 porque son 30 caracteres + el salto de linea
					if(strlen(agenda[i].redes.insta)>30){numero=1;}else{numero=0;}
				}while(limpiar(cin.fail(),5,numero)!=0);

				do{//Facebook===========
					printf("\x1b[38;5;21m");cout<<"Introduzca la cuenta de facebook: ";
					cin.ignore();
					cin.getline(agenda[i].redes.facebook, 30);
					if(strlen(agenda[i].redes.facebook)>30){numero=1;}else{numero=0;}
				}while(limpiar(cin.fail(),6,numero)!=0);	
			}else{
				continue;
			}//else
            printf("\x1b[38;5;231m");cout<<"Contacto actualizado correctamente"<<endl;
    		continuar();
        }else{
        	printf("\x1b[38;5;74m");cout<<"Contacto no encontrado"<<endl;
			continuar();
		}//else	
    }//for
    cin.clear();
}//actualizar

void extras(Contacto *agenda, int numContactos){
	int opcion=0;
	do{
		fflush(stdin);
		system("cls");
		printf("\x1b[38;5;222m");cout<<"\n============== EXTRAS ==============\n"<<endl;
		printf("\x1b[38;5;231m");cout<<" Listado de contactos con cuenta de instagram........(1)\n";
		printf("\x1b[38;5;231m");cout<<" Listado de contactos sin redes sociales.............(2)\n";
		printf("\x1b[38;5;231m");cout<<" Regresar............................................(3)\n";
		printf("\x1b[38;5;231m");cout<<" Seleccione una opcion: ";
		cin>>opcion;
		if(cin.fail()){cin.clear();cin.ignore(40,'\n');}//ignora la entrada del buffer}//Esto evita que al meter una letra explote================================
		switch(opcion){
			case 1://CONTACTOS SIN CUENTA DE INSTA
				contInsta(agenda, numContactos);
				break;
			case 2://CONTACTOS SIN REDES SOCIALES
				contSin(agenda, numContactos);
				break;
			case 3://REGRESAR
				break;
			default:
				printf("\x1b[38;5;74m");cout<<"Opcion invalida.\n";
				continuar();
				break;
		}//switch
	}while(opcion!=3);
	system("cls");
}//extras

void contInsta(Contacto *agenda, int numContactos){
	bool contactos=false;//=======controla el mensaje=============
	
	if(numContactos==0){
    	cout<<"\n La agenda esta vacia\n";
    	continuar();
    	return;
	}//if
	
	cout<<endl;
    printf("\x1b[38;5;222m");cout<< "===== CONTACTOS CON INSTAGRAM ====="<<endl;
    for(int i=0; i<numContactos; i++) {
        if (strlen(agenda[i].redes.insta)>1){
        	contactos=true;
			printf("\x1b[38;5;231m");cout<< "Nombre: "<<agenda[i].nombre<<endl;
			printf("\x1b[38;5;211m");cout<< "Instagram : @"<<agenda[i].redes.insta<<endl;
			cout<<"----------------------------------"<<endl;
        }//if
    }//for
    //==========mensaje cuando no hay usuarios==================================
    if(contactos==false){
    	printf("\x1b[38;5;74m");cout<<endl<<"   No Hay usuarios con Instagram"<<endl<<endl;
	}//if
    continuar();
}//conInsta

void contSin(Contacto *agenda, int numContactos){
	bool contactos=false;//=======controla el mensaje=============
	
	if(numContactos==0){
    	cout<<"\n La agenda esta vacia\n";
    	continuar();
    	return;
	}//if
	
	cout<<endl;
    printf("\x1b[38;5;222m"); cout<< "====== CONTACTOS SIN REDES ======"<<endl;
	for (int i = 0; i < numContactos; i++) {
        if (agenda[i].tieneRed==false){
    		printf("\x1b[38;5;231m");cout<<endl<< "Nombre: " <<agenda[i].nombre<< endl;
    	contactos=true;
        }//if
    }//if
	//==========mensaje cuando no hay usuarios==================================
    if(contactos==false){
    	printf("\x1b[38;5;74m");cout<<"No Hay usuarios sin redes"<<endl<<endl;
	}//if
    continuar();
}//void

void mostrar(Contacto *agenda, int i){
	cout<<endl;
    printf("\x1b[38;5;184m");cout<< "Contacto encontrado:"<< endl;
    printf("\x1b[38;5;231m");cout<< "Nombre: " <<agenda[i].nombre<< endl;
    printf("\x1b[38;5;231m");cout<< "Telefono: " <<agenda[i].tel<< endl;
    printf("\x1b[38;5;231m");cout<< "CURP: " <<agenda[i].curp<< endl;
    if(agenda[i].tieneRed==true && agenda[i].redes.correo[0]!='*'){
        	printf("\x1b[38;5;160m");cout<< "Correo electronico: "<< agenda[i].redes.correo << endl;	
	}//if
	if(agenda[i].tieneRed==true && agenda[i].redes.insta[0]!='*'){
        	printf("\x1b[38;5;211m");cout<< "Cuenta de Instagram: "<< agenda[i].redes.insta << endl;	
	}//if
	if(agenda[i].tieneRed==true && agenda[i].redes.facebook[0]!='*'){
		printf("\x1b[38;5;21m");cout<< "Cuenta de Facebook: "<< agenda[i].redes.facebook << endl;	
	}//if
}//mostrar

void continuar(){
	system("Pause");			
    system("cls");
}//negar

bool verificarOpc(int opcion){//Se verifica si la opcion ingresada 
//Se puede cambiar a char
	if(opcion==0||opcion==1){
		return true;
	}else{
		printf("\x1b[38;5;74m");cout<<"Opcion invalida.\n";
		continuar();
		return false;
	}//else
}//verificarOpc

bool limpiar(bool a,int opc,int estado){
	
	if(a){//esto debuelve un 1 o verdadero si hay un problema con la entrada
		switch(opc){
			case 1:
				printf("\x1b[38;5;74m");cout<<" Ingrese un nombre con menos de 30 elementos"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			case 2:
				printf("\x1b[38;5;74m");cout<<" Ingrese un numero valido de 10 digitos"<<endl;
				break;
			case 3:
				printf("\x1b[38;5;74m");cout<<"Ingrese una curp valida de 18 caracteres"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			case 4:
				printf("\x1b[38;5;74m");cout<<"Ingrese una correo valido"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			case 5:
				printf("\x1b[38;5;74m");cout<<"Ingrese un usuario de Instagram correcto"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			case 6:
				printf("\x1b[38;5;74m");cout<<"Ingrese un usuario de Facebook correcto"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			default:
				break;
		}//switch
		cin.clear();//limpia el error en la consola
		cin.ignore(40,'\n');//ignora la entrada del buffer
		return 1;
	}//if
	
	if(estado==1&&!a&&opc==2){
		printf("\x1b[38;5;74m");cout<<" Ingrese un numero valido de 10 digitos"<<endl;	
		return 1;	
	}//if
	if(estado==1&&!a&&opc==3){
		printf("\x1b[38;5;74m");cout<<" Ingrese una curp valida de 18 caracteres"<<endl;
		return 1;	
	}//if
	if(estado==1&&!a&&opc==4){
		printf("\x1b[38;5;74m");cout<<" Ingrese un correo valido"<<endl;
		return 1;	
	}//if
	return 0;
	
}//limpiar
