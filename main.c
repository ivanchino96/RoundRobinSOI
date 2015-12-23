#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void leerArchivo(char* archivo, char* proceso, int *q, int *inicio, int *duracion, int *num_lineas);


void main() {
	
	int contador;
	char* nombrearchivo = "tablaProcesos.txt";
	char* nombre= (char*)malloc(sizeof(char));
	int *q = (int*)malloc(sizeof(int));
	int *inicio = (int*)malloc(100*sizeof(int));
	int *duracion = (int*)malloc(100*sizeof(int));
	int *num_lineas=(int*)malloc(sizeof(int));
	*num_lineas = 0;

	leerArchivo(nombrearchivo,nombre,q,inicio,duracion,num_lineas);

	printf("Numero de lineas: %d\n", *num_lineas); //Solamente compruebamos que nos devuelve el numero de lineas del fichero correcto

	for(contador=0; contador<*num_lineas; contador++){
		printf("Linea %d contiene al proceso %c, con quanto=%d, inicio=%d y duracion=%d \n", contador+1, nombre[contador], q[contador], inicio[contador], duracion[contador]);
	}
	
}


//FUNCION PARA QUE LEA DEL ARCHIVO, GUARDES EN VECTORES Y COMPRUEBA QUE SE HAN GUARDADO BIEN
void leerArchivo(char* archivo, char* proceso, int *q, int *inicio, int *duracion, int *num_lineas){
	FILE* miarchivo;
	int contador; 
	int ch;
	miarchivo = fopen(archivo, "r");

	//Calculamos el numero de lineas
	while ((ch = fgetc(miarchivo)) != EOF)
	if (ch == '\n'){
		*num_lineas = *num_lineas + 1;
	}

	fclose(miarchivo);
	miarchivo = fopen(archivo, "r");
	//En este bucle tengemos en cuenta los campos con la expresion %d:%[A-Z]:%d:%d\n, cada campo lo asigno al vector que le corresponde
	for(contador = 0; contador<*num_lineas; contador++){
		fscanf(miarchivo, "%d:%[A-Z]:%d:%d\n", &q[contador], &proceso[contador], &inicio[contador], &duracion[contador]);
	}

	fclose(miarchivo);
}
