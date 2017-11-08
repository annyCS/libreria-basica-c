#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libreria.h"

// - constantes
#define BUFFER 1024		// constante para el tamaño del buffer
#define MAX_LINES 10    // TEST: define el numero de lineas a introducir por defecto en caso que no se indique por argumento

int head(int N) {
    int cont = 0;		// acumulador que nos permite saber cuantas lineas se van leyendo
    char buf[BUFFER];	// cadena en donde se almancenara cada linea leida de la entrada estandar

    // - se lee por la entrada estandar, mientras el contador de lineas sea menor que N
    // o haya finalizado la ejecucion del programa (CTRL+D)
    while( (cont < N) && (fgets(buf, BUFFER, stdin)!= NULL) )
    {
        printf("%s", buf);
        cont++;
    }

    return 0;
}


int tail(int N){
    char buffer[BUFFER];    // almacenara la linea introducida por STDIN
    char **pListString;    // matriz dinamica que almacenara la lista lineas

    int i, sizeLine;	// i, variable iteradora. sizeLine, variable para guardar la longitud de la linea a almacenar en la lista
    int cont = 0;		// contador de las lineas que se van introduciendo antes de producirse el EOF
    
    // - se reserva memoria para almacenar las N ultimas lineas leidas por stdin
    pListString = (char **) malloc(N * sizeof(char *));
    
    // - se comprueba si el sistema pudo reservar memoria
    if( pListString != NULL )
    {
        // - ejecutamos el bucle mientras haya lineas que leer
        while( fgets(buffer, BUFFER, stdin) != NULL )
        {
            // - nos cercioramos de que el buffer vuelque lo que se haya leido por la entrada
            fflush(stdin);

            // - se comprueba si el contador de lineas es menor que el numero total de lineas (N) a almacenar
            if( cont < N )
            {
                // - se reserva memoria para la nueva linea que sera almacenada
                sizeLine = (strlen(buffer) + 1);
                pListString[cont] = (char *) malloc(sizeLine * sizeof(char));

                // - se copia la linea del buffer
                strcpy(pListString[cont], buffer);
                
                // - se incrementa el contador de lineas almacenadas
                cont++;
            }
            
            // - si se ha llegado aqui, significa que el contador de lineas introducidas es
            // mayor que el total de lineas (N).
            else {
                // - se van desplazando las lineas desde la posicion 1 hasta la posicion N-1
                // y poder almacenar la ultima introducida
                free(pListString[0]);
                
                i = 0;
                for(i = 0; i < N-1; i++)
                {
                    pListString[i] = pListString[i+1];
                }
                
                // almaceno la linea actual en la lista de strings
                sizeLine = (strlen(buffer) + 1);
                pListString[N-1] = (char *) malloc(sizeLine * sizeof(char));
                strcpy(pListString[N-1], buffer);
            }
        }

        i = 0;

        // - se imprime por STDOUT las lineas que exactamente hayan sido almacenadas
        while( i < cont )
        {
            printf("%s", *(pListString + i));
			
			// - liberamos memoria
            free(pListString[i]);

            i++;
        }

		// - liberamos la memoria de la matriz dinámica
        free(pListString);
		pListString = NULL
    }
	
	else{
		return 1;
	}

    return 0;
}


int longlines(int N){
    int i,j;			// i,j variables iteradoras para las líneas y recorrer la longitud de las mismas
    char buf[BUFFER];	// almacenara la linea introducida por STDIN
    char **cadenas;		// matriz dinamica que almacenara la lista lineas

    //Reservamos memoria
    cadenas = malloc(N * sizeof(char *));
    
    for(i = 0; i < N; i++){
        cadenas[i] = malloc(BUFFER*sizeof(char));
    }

    //Almacenamos las lineas ordenadamente hasta pulsar CONTROL+D
    while(fgets(buf, BUFFER, stdin)!=NULL)
	{
        for(i = 0; i < N; i++)
		{
            if(strlen(buf) > strlen(cadenas[i])){
                for(j = N-1; j > i; j--){
                    strcpy(cadenas[j], cadenas[j-1]);
                }
                strcpy(cadenas[i], buf);
                i = N;
            }
        }
    }

    //Imprimimos las lineas almacenadas y las liberamos
    for(i = 0; i < N; i++)
	{
        printf("%s", cadenas[i]);
        free(cadenas[i]);
    }

    free(cadenas);

    return 0;
}