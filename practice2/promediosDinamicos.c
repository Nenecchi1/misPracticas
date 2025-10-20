#include<stdio.h>
#include<stdlib.h>

double* aumentaMemoria(double *ptr, int tam);//prototipo de funcion
double* reservaMemoria(int tam);//prototipo de funcion
void ingresaCalificaciones(double *ptr, int tam,int ini);//prototipo de funcion


int main(){

    int opcion;//variable para el menu
    int numC;//variable para el numero de calificaciones
    double *calificaciones=NULL;//puntero para las calificaciones
    double suma_cali= 0.0;//variable para la suma de las calificaciones
    double promedio;//variable para el promedio
    char resp;//variable para la respuesta del usuario
    int newCalificaciones;//variable para el numero de nuevas calificaciones

    //mensaje de bienvenida
    printf("=== Calculadora de Promedio Dinámica ===\n\n");
    
    //menu de opciones
    while(opcion != 2){
        printf("1) Ingresar calificaciones\n");
        printf("2) Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d",&opcion);

        //estructura de control para las opciones del menu
        switch(opcion){
        
            case 1:

            //solicitud del numero de calificaciones
            printf("\n Cuantas calificaciones quieres ingresar?: ");
            scanf("%d",&numC);

            //reserva de memoria para las calificaciones
            calificaciones = reservaMemoria(numC);

            //Verificar si la memoria se asigno correctamente
            if (calificaciones==NULL){
                
                printf("Error en la asignacion de memoria");
                exit(1);//Termina el programa
            }

            //ingreso de las calificaciones
            ingresaCalificaciones(calificaciones,numC,1);

            //calculo del promedio
            for(int i=0; i<numC; i++){
                suma_cali += *(calificaciones+i);//*(calificaciones+i) es equivalente a calificaciones[i]
            }

            //calculo del promedio
            promedio = suma_cali/numC;

            //mostrar el promedio
            printf("\nEl promedio de las calificaciones es: %.2lf\n\n",promedio);

            do
            {
                //preguntar al usuario si desea ingresar mas calificaciones
                printf("Deseas ingresar mas calificaciones? (s/n): ");
                scanf(" %c",&resp);

                if(resp == 's' || resp == 'S'){
                    //solicitud del numero de calificaciones
                    printf("\n Cuantas calificaciones quieres ingresar?: ");
                    scanf("%d",&newCalificaciones);

                    int numC_anterior = numC; // Guardamos el número de calificaciones antes de la reasignación

                    //aumento de la memoria para las calificaciones
                    // El nuevo tamaño es el anterior (numC) + el nuevo (newCalificaciones).
                    calificaciones = aumentaMemoria(calificaciones, numC + newCalificaciones);
                    
                    //Actualizar el numero de calificaciones
                    numC += newCalificaciones;//suma el numero de calificaciones anteriores con las nuevas



                    //Verificar si la memoria se asigno correctamente
                    if (calificaciones==NULL){
                        
                        printf("Error en la asignacion de memoria");
                        exit(1);//Termina el programa
                    }
                    
                    /*
                    Se ingresa las nuevas calificaciones a partir de la posicion
                    numC_anterior, que es donde terminan las calificaciones anteriores.
                    Esto es, si se ingresaron 3 calificaciones inicialmente, las nuevas
                    calificaciones se ingresaran a partir de la posicion 3 (indice 2).
                    */
                    ingresaCalificaciones(calificaciones + numC_anterior, newCalificaciones, numC_anterior + 1);

                    //calculo del promedio
                    suma_cali = 0.0;//reiniciar la suma de calificaciones

                    //calculo del nuevo promedio
                    for(int i=0; i<numC; i++){
                        suma_cali += *(calificaciones+i);//*(calificaciones+i) es equivalente a calificaciones[i]
                    }

                    //calculo del promedio nuevo
                    promedio = suma_cali/numC;

                    //mostrar el promedio
                    printf("\nEl promedio de las calificaciones es: %.2lf\n\n",promedio);
                }

            } while (resp != 'n' && resp != 'N');//si la respuesta es diferente de 'n' o 'N', se repite el ciclo
        
            break;
            case 2:

            //liberacion de la memoria asignada
            free(calificaciones);
            
            
            //mensaje de despedida
            printf("\nMemoria liberada!!! Hasta luego.\n");
            break;
            
            default:
            //opcion del usuario invalida
            printf("\n=== Opcion invalida === \nPor favor seleccione una opcion del menu:\n");
            break;
        
        }//fin del switch

    }//fin del while menu   

    return 0;
}//fin del main


//esta funcion aumenta el tamaño de la memoria
double* aumentaMemoria(double *ptr, int tam){

    ptr = (double*) realloc(ptr, tam * sizeof(double));//reasignacion dinamica de memoria
    
    return ptr;//retorna el puntero
}

//esta funcion reserva memoria dinamica
double* reservaMemoria(int tam){

    double *ptr= NULL;//puntero para la memoria dinamica

    ptr = (double*) calloc(tam,sizeof(double));//reserva de memoria dinamica

    return ptr;//retorna el puntero
}

//esta funcion ingresa las calificaciones
void ingresaCalificaciones(double *ptr, int tam,int inicio){

    for(int i=0; i<tam; i++){
        printf("Ingresa la calificacion %d: ",inicio+i);
        scanf("%lf",ptr+i);//ptr+i es equivalente a &ptr[i]
    }
}



 