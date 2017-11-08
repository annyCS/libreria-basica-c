#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "libreria.h"

#define DEF 3

// Funcion que dado un entero y el nombre de otra funcion, llamara a dicha funcion pasandole el entero como argumento.
int orden(int N, char *string){
    if(strcmp(string, "head") == 0){
        return head(N);
    }
    else if(strcmp(string, "tail") == 0){
        return tail(N);
    }
    else if(strcmp(string, "longlines") == 0){
        return longlines(N);
    }
    else{
        printf("%s","No se encontró la orden.\n");
        return 1;
    }
}

int main(int argc, char *argv[]){

    // Si el numero de argumentos es dos llamara a la función requerida pasandole como argumento nuestro numero de linas por defecto
    if(argc == 2){
        return (orden(DEF, argv[1]));
    }
    
    //Si el numero de argumentos es tres, comprobara si el segundo argumento es un entero de la forma -N, o un fichero.
    //En caso de que sea -N llamara a la funcion pasandole como argumento N, y si es un fichero redigira la entrada estandar a ese fichero.
    else if(argc == 3){
        if (argv[2][0] == '-'){
            return(orden(atoi(argv[2]+1),argv[1]));
        }
        else{
            FILE *newin;
            int retorno;
            
            if ((newin = freopen(argv[2], "r", stdin))!=NULL){
                retorno = (orden(DEF, argv[1]));
                fclose(newin);
                return retorno;
            }
            else {
                printf("Error al encontrar <%s>\n",argv[2]);
                return 1;
            }
        }
    }

    //Si el numero de argumentos es cuatro, llamara a la funcion pasandole -N y redirigiendo la entrada estandar al fichero introducido.
    else if(argc == 4){
        FILE *newin;
        int retorno;

        if ((newin = freopen(argv[3], "r", stdin))!=NULL){
            retorno = (orden(atoi(argv[2]+1), argv[1]));
            fclose(newin);
            return retorno;
        }
        else {
            printf("Error al encontrar <%s>\n",argv[3]);
            return 1;
        }
    }

    //Si el numero de argumentos no es el correcto mostrara un error.
    else{
        printf("%s","Número de argumentos inválido.\n");
        return 1;
    }
}