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
using namespace std;
#define CONTACTOS 50 //Limite de contactos en la agenda

//Estructuras con variables dinamicas 
struct RedesSociales{
    char *correo;//Quitamos [] no son necesarios
    char *insta;
    char *facebook;
};//RedesSociales

struct Contacto{
    char *curp;
    char *nombre;
    long long int tel;//No es dinamica es estatica
	bool tieneRed;
    struct RedesSociales redes;
};//Contacto

void menu(); //buenas tardes senora como se encuentra el dia de hoy
void agregar(Contacto*&, int &); // en agenda * por que es amperson y & para cambiar la direccion
void buscar(Contacto*, int);// no se pone agenda por que no es necesario el nombre de la variable
void actualizar(Contacto*, int);
void showSinRedes(Contacto*, int);
void extras(Contacto*, int);
void contInsta(Contacto*, int);
void contSin(Contacto*, int);
void continuar();//Retorna al usuario en caso de que inserte una opcion no valida
void mostrar(Contacto*, int);
bool verificarOpc(int);//Se verifica la opcion que de el usuario

bool limpiar(bool,int,int);
int main(){
	Contacto *agenda = new Contacto[CONTACTOS];//inicializamos la variable dinamica
    //Una estructura con el nombre de agenda de tipo Data
    int num=0, opcion=0;
    bool validar=false;
	
    do{
        menu();
		cin>>opcion;
		limpiar(cin.fail(),0,0);
        fflush(stdin);
        
        switch(opcion){
            case 1:
                agregar(agenda,num);
                break;
            case 2:
                buscar(agenda,num);
                break;
            case 3:
                actualizar(agenda,num);
                break;
            case 4:
                extras(agenda,num);
                break;
            case 5://SALIR
                cout<<endl<<"Programa finalizado..."<<endl;
                break;
            default:
                cout << "\nOpcion no valida"<<endl;
                continuar();
                break;
        }//switch
    }while(opcion!=5);
    delete[] agenda; // Liberar memoria al finalizar el programa
    
    return 0;
}//main

void menu(){
    cout<<"\n======== AGENDA DE CONTACTOS ========\n"<<endl;
	cout<<" Agregar nuevo contacto...........(1)\n";
	cout<<" Buscar contacto..................(2)\n";
	cout<<" Actualizar contacto..............(3)\n";
	cout<<" Extras...........................(4)\n";
	cout<<" Salir............................(5)\n\n";
    cout<<" Ingrese su opcion: ";
}//menu

void agregar(Contacto *&agenda, int &numContactos) {
	Contacto nuevo;//nueva estructura de tipo contacto con el nombre de nuevo
	char auxChar[50];
	int resp=0, opcion=0,numero=0;
	bool validar=false;
	bool insta=false, facebook=false, correo=false;
	
	system("cls"); 
    cout<<"\n========= AGREGAR CONTACTO =========\n"<<endl;
  
    if (numContactos>=CONTACTOS) {
        cout<<"No se pueden agregar más contactos"<< endl<<"La agenda esta llena<<"<<endl;
        return;
    }//if
//==============================================================================================================================================
	//LLENAR DATOS	
	do{//Nombre===========
 	   	cout<<" Nombre: ";
		cin.getline(auxChar,31,'\n');//dejo 31 porque son 30 caracteres + el salto de linea
	}while(limpiar(cin.fail(),1,0)!=0);
	nuevo.nombre=new char[strlen(auxChar)+1];
	strcpy(nuevo.nombre,auxChar);
	
	do{//telefono========
		cout<<" Telefono: ";//-----------------------------------------------------------------AQUI FALTA VALIDAR
	    cin>>nuevo.tel;
	    if(nuevo.tel<1000000000||nuevo.tel>10000000000){numero=1;}else{numero=0;}
	}while(limpiar(cin.fail(),2,numero)!=0);    
	
    do{//curp========================
    	cout<< " CURP: ";//-----------------------------------------------------------------AQUI FALTA VALIDAR(Resuelto)
  		cin>>auxChar;
  		if(strlen(auxChar)!=18){numero=1;}else{numero=0;}
	}while(limpiar(cin.fail(),3,numero)!=0);
	nuevo.curp=new char[strlen(auxChar)+1];
	strcpy(nuevo.curp,auxChar);
//============================================================================================================================================== 	
  	
    
	do{
		cout<<" Desea agregar alguna red social? Si (1)  No(0)\n";
		cout<<" Ingrese su opcion: ";
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
			cout<<" Correo electronico...............(1)\n";
			cout<<" Cuenta de instagram..............(2)\n";
			cout<<" Cuenta de facebook...............(3)\n";
			cout<<" Regresar.........................(4)\n";
			cout<<"\nSeleccione la red social a agregar: ";
			cin>>opcion;
			limpiar(cin.fail(),0,0);
			switch(opcion){
				system("cls");
				case 1:
					do{//Correo===========
						correo=true;
						cout<<"Introduzca el correo electronico: ";
						cin>>nuevo.redes.correo;//dejo 31 porque son 30 caracteres + el salto de linea
						if(strlen(nuevo.redes.correo)>30){numero=1;}else{numero=0;}
					}while(limpiar(cin.fail(),4,numero)!=0);
					break;
				case 2:
					do{//Insta===========
						insta=true;
						cout<<"Introduzca la cuenta de instagram: ";
						cin>>nuevo.redes.insta;//dejo 31 porque son 30 caracteres + el salto de linea
						if(strlen(nuevo.redes.insta)>30){numero=1;}else{numero=0;}
					}while(limpiar(cin.fail(),5,numero)!=0);
					break;
				case 3:
					do{//Facebook===========
						facebook=true;
						cout<<"Introduzca la cuenta de facebook: ";
						cin.ignore();
    						cin.getline(nuevo.redes.facebook,31);
						if(strlen(nuevo.redes.facebook)>30){numero=1;}else{numero=0;}
					}while(limpiar(cin.fail(),6,numero)!=0);
					break;
				case 4:
					system("cls");
					break;
				default:
					cout<<"Opcion invalida.\n";
					continuar();
					break;
				system("cls");
			}//swicth
			
			
			if(opcion<4&&opcion>0){
				do{
					cout<<"\n¿Desea agregar otra red social? Si (1)  No(0)\n";
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
	}//if
	
	if(correo==false){nuevo.redes.correo= new char[30];strcpy(nuevo.redes.correo,"*\0");}
	if(insta==false){nuevo.redes.insta= new char[30];strcpy(nuevo.redes.insta,"*\0");}	
	if(facebook==false){nuevo.redes.facebook= new char[30];strcpy(nuevo.redes.facebook,"*\0");}	
    
	agenda[numContactos++] = nuevo;
    cout<<"Contacto agregado correctamente"<<endl;
    continuar();
    cin.clear();
    
}//agregar

void buscar(Contacto *agenda, int numContactos){
    bool encontrado = false,validar = false;
	char clave[50];	
	int opcion=0,numero=0;	
	
	do{
		system("cls");
		cout<<"\n========== BUSCAR CONTACTO ==========\n"<<endl;
		cout<<" Nombre............................(1)\n";
		cout<<" Curp..............................(2)\n";
		cout<<" Regresar..........................(3)\n\n";
		cout<<" Seleccione una opcion: ";
		fflush(stdin);
		cin>>opcion;
		if(cin.fail()){cin.clear();cin.ignore(40,'\n');}//ignora la entrada del buffer}//Esto evita que al meter una letra explote================================
		switch(opcion){
			case 1:
				fflush(stdin);
					do{//Nombre===========
						cout<<" Introduzca el nombre a buscar: ";	
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
        			cout<<" Contacto no encontrado"<<endl;
        			continuar();
    			}//if
				break;
			case 2:
				cout<<" Introduzca la curp a buscar: ";
				 do{//curp========================
  					cin>>clave;
  						if(strlen(clave)!=18){numero=1;}else{numero=0;}
				}while(limpiar(cin.fail(),3,numero)!=0);
				
				for(int i=0; i<numContactos; i++){
       				if(strcmp(clave, agenda[i].curp)==0){
        				mostrar(agenda, i);
        				continuar();
        				encontrado = true;
       				}//if prinicipal
    			}//for
    			if (encontrado==false) {
        			cout<<" Contacto no encontrado"<<endl;
        			continuar();
    			}//if
    			encontrado=false;
				break;
			case 3:
				break;
			default:
			cout<<"Opcion invalida.\n";
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
    system("cls");
	cout<<"\n======== ACTUALIZAR CONTACTO ========\n"<<endl;//------------------------------------------------------Aqui tambien se puede dividir buscando por nombre y curp
    cout << "Ingrese nombre o CURP del contacto a actualizar: "<<endl;
    do{//Nombre o curp===========
 	   	cout<<" Nombre: ";
		cin.getline(clave,31,'\n');//dejo 31 porque son 30 caracteres + el salto de linea
	}while(limpiar(cin.fail(),1,0)!=0);
    
    for(int i=0; i<numContactos; i++){
        if(strcmp(clave, agenda[i].nombre)==0||strcmp(clave, agenda[i].curp)==0){
            cout<<" Ingrese nueva informacion para el contacto: "<<endl;
            do{//Nombre===========
 	   			cout<<" Nombre: ";
				cin.getline(auxChar,31,'\n');//dejo 31 porque son 30 caracteres + el salto de linea
			}while(limpiar(cin.fail(),1,0)!=0);
            if(strlen(auxChar)>strlen(agenda[i].nombre)){
            	agenda[i].nombre=(char*)realloc(agenda[i].nombre, strlen(auxChar)*sizeof(char));
			}//if
			strcpy(agenda[i].nombre,auxChar);
			
			do{//telefono========
				cout<<" Telefono: ";//-----------------------------------------------------------------AQUI FALTA VALIDAR
	    		cin>>agenda[i].tel;
	    			if(agenda[i].tel<1000000000||agenda[i].tel>10000000000){numero=1;}else{numero=0;}
			}while(limpiar(cin.fail(),2,numero)!=0);    
			
			do{//curp========================
    			cout<< " CURP: ";//-----------------------------------------------------------------AQUI FALTA VALIDAR(Resuelto)
  				cin>>auxChar;
  					if(strlen(auxChar)!=18){numero=1;}else{numero=0;}
			}while(limpiar(cin.fail(),3,numero)!=0);
            	if(strlen(auxChar)>strlen(agenda[i].curp)){
            		agenda[i].curp=(char*)realloc(agenda[i].curp, strlen(auxChar)*sizeof(char));
			}//if
			strcpy(agenda[i].curp,auxChar);
		//==============================================================================================================================	
		
		cin>>opc;
		limpiar(cin.fail(),0,0);
		if(opc==1){
			if(agenda[i].tieneRed==false){
				agenda[i].tieneRed=true;
			}
				do{//Correo===========
					cout<<"Introduzca el correo electronico: ";
					cin>>agenda[i].redes.correo;//dejo 31 porque son 30 caracteres + el salto de linea
					if(strlen(agenda[i].redes.correo)>30){numero=1;}else{numero=0;}
				}while(limpiar(cin.fail(),4,numero)!=0);
			
				do{//Instagram===========
					cout<<"Introduzca la cuenta de instagram: ";
					cin>>agenda[i].redes.insta;//dejo 31 porque son 30 caracteres + el salto de linea
					if(strlen(agenda[i].redes.insta)>30){numero=1;}else{numero=0;}
				}while(limpiar(cin.fail(),5,numero)!=0);

				do{//Facebook===========
					cout<<"Introduzca la cuenta de facebook: ";
					cin.ignore();
					cin.getline(agenda[i].redes.facebook, 30);
					if(strlen(agenda[i].redes.facebook)>30){numero=1;}else{numero=0;}
				}while(limpiar(cin.fail(),6,numero)!=0);	
		}else{
			continue;
		}
		//==============================================================================================================================	
            cout<<"Contacto actualizado correctamente"<<endl;
    		continuar();
        }else{
        	cout<<"Contacto no encontrado"<<endl;
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
		cout<<"\n============== EXTRAS ==============\n"<<endl;
		cout<<" Listado de contactos con cuenta de instagram........(1)\n";
		cout<<" Listado de contactos sin redes sociales.............(2)\n";
		cout<<" Regresar............................................(3)\n";
		cout<<" Seleccione una opcion:\n";
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
				cout<<"Opcion invalida.\n";
				continuar();
				break;
		}//switch
	}while(opcion!=3);
}//extras

void contInsta(Contacto *agenda, int numContactos){
	bool contactos=false;//=======controla el mensaje=============
	
	cout<<endl;
    cout<< "===== CONTACTOS CON INSTAGRAM ====="<<endl;
    for(int i=0; i<numContactos; i++) {
        if (strlen(agenda[i].redes.insta)>1){
        	contactos=true;
			cout<< "Nombre: "<<agenda[i].nombre<<endl;
			cout<< "Instagram : @"<<agenda[i].redes.insta<<endl;
			cout<<"----------------------------------"<<endl;
        }//if
    }//for
    //==========mensaje cuando no hay usuarios==================================
    if(contactos==false){
    	cout<<endl<<"   No Hay usuarios con Instagram"<<endl<<endl;
	}
    
    continuar();
}//conInsta

void contSin(Contacto *agenda, int numContactos){
	bool contactos=false;//=======controla el mensaje=============
	
	cout<<endl;
    cout<< "====== CONTACTOS SIN REDES ======"<<endl;
	for (int i = 0; i < numContactos; i++) {
        if (agenda[i].tieneRed==false){

    		cout<<endl<< "Nombre: " <<agenda[i].nombre<< endl;
    	contactos=true;
        }//if
    }//if
	//==========mensaje cuando no hay usuarios==================================
    if(contactos==false){
    	cout<<"No Hay usuarios sin redes"<<endl<<endl;
	}
    continuar();
}//void

void mostrar(Contacto *agenda, int i){
	cout<<endl;
    cout<< "Contacto encontrado:"<< endl;
    cout<< "Nombre: " <<agenda[i].nombre<< endl;
    cout<< "Telefono: " <<agenda[i].tel<< endl;
    cout<< "CURP: " <<agenda[i].curp<< endl;
    if(agenda[i].tieneRed==true && agenda[i].redes.correo[0]!='*'){
        cout<< "Correo electronico: "<< agenda[i].redes.correo << endl;	
	}//if
	if(agenda[i].tieneRed==true && agenda[i].redes.insta[0]!='*'){
        cout<< "Cuenta de Instagram: "<< agenda[i].redes.insta << endl;	
	}//if
	if(agenda[i].tieneRed==true && agenda[i].redes.facebook[0]!='*'){
		cout<< "Cuenta de Facebook: "<< agenda[i].redes.facebook << endl;	
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
		cout<<"Opcion invalida.\n";
		continuar();
		return false;
	}//else
}//verificarOpc
bool limpiar(bool a,int opc,int estado){
	
	if(a){//esto debuelve un 1 o verdadero si hay un problema con la entrada
		switch(opc){
			case 1:
				cout<<" Ingrese un nombre con menos de 30 elementos"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			case 2:
				cout<<" Ingrese un numero valido de 10 digitos"<<endl;
				break;
			case 3:
				cout<<"Ingrese una curp valida de 18 caracteres"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			case 4:
				cout<<"Ingrese una correo valido"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			case 5:
				cout<<"Ingrese un usuario de Instagram correcto"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			case 6:
				cout<<"Ingrese un usuario de Facebook correcto"<<endl;//si no les gusta este mensaje cambiarlo
				break;
			default:
				break;
		}
		cin.clear();//limpia el error en la consola
		cin.ignore(40,'\n');//ignora la entrada del buffer
		return 1;
	}
	
	if(estado==1&&!a&&opc==2){
		cout<<" Ingrese un numero valido de 10 digitos"<<endl;	
		return 1;	
	}
	if(estado==1&&!a&&opc==3){
		cout<<" Ingrese una curp valida de 18 caracteres"<<endl;
		return 1;	
	}
	if(estado==1&&!a&&opc==4){
		cout<<" Ingrese un correo valido"<<endl;
		return 1;	
	}
	return 0;
}
