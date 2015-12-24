#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

void leerArchivo(char* archivo, char* proceso, int *q, int *inicio, int *duracion, int *num_lineas);


void main(int argc, char *argv[]) 
{

	if(argc!=2)
	{
		puts("ERROR, numero de parametros incorrecto");
		puts("La sintaxis correcta es: \"main fichero\" siendo \"fichero\" el nombre del fichero que contiene los datos");
		exit(0);
	}	
	
	//Buscamos el archivo
	HANDLE handle;
	WIN32_FIND_DATA datos;
	puts("1");
	handle=FindFirstFile(argv[1],&datos);
	//Si el archivo existe
	if (handle!=INVALID_HANDLE_VALUE){
		char* nombrearchivo = (char*)malloc(100*sizeof(char));
		nombrearchivo = argv[1];
		int contador;
		char* nombre= (char*)malloc(sizeof(char));
		int *q = (int*)malloc(sizeof(int));
		int *inicio = (int*)malloc(100*sizeof(int));
		int *duracion = (int*)malloc(100*sizeof(int));
		int *num_lineas=(int*)malloc(sizeof(int));
		*num_lineas = 0;

		leerArchivo(nombrearchivo,nombre,q,inicio,duracion,num_lineas);

		//PROVISIONAL PARA DEBUGGING
		printf("Numero de lineas: %d\n", *num_lineas); //Solamente compruebamos que nos devuelve el numero de lineas del fichero correcto

		for(contador=0; contador<*num_lineas; contador++){
			printf("Linea %d contiene al proceso %c, con quanto=%d, inicio=%d y duracion=%d \n", contador+1, nombre[contador], q[contador], inicio[contador], duracion[contador]);
		}
		//ROUNDROBIN
	}else{
		//Si no existe el archivo salir
		puts("ERROR");
		puts("No se encuentra el archivo");
		exit(0);		
	}
}


//FUNCION PARA QUE LEA DEL ARCHIVO, GUARDES EN VECTORES Y COMPRUEBA QUE SE HAN GUARDADO BIEN
void leerArchivo(char* archivo, char* proceso, int *q, int *inicio, int *duracion, int *num_lineas)
{
	FILE* miarchivo;
	int contador; 
	int ch;
	miarchivo = fopen(archivo, "r");

	//Calculamos el numero de lineas
	while ((ch = fgetc(miarchivo)) != EOF)
	if (ch == '\n')
	{
		*num_lineas = *num_lineas + 1;
	}

	fclose(miarchivo);
	miarchivo = fopen(archivo, "r");
	//En este bucle tengemos en cuenta los campos con la expresion %d:%[A-Z]:%d:%d\n, cada campo lo asigno al vector que le corresponde
	for(contador = 0; contador<*num_lineas; contador++)
	{
		fscanf(miarchivo, "%d:%[A-Z]:%d:%d\n", &q[contador], &proceso[contador], &inicio[contador], &duracion[contador]);
	}

	fclose(miarchivo);
}
