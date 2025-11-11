#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//prototipos de las funciones
int agregarProducto();
double calcularValorTotalInventario();
void mostrarProductos();
void liberarInventario();
void buscarProducto();
void actualizarStock();

#define MAX_NOMBRE 60

// Punteros dobles globales para el inventario
char **nombresProductos= NULL;
int *cantidades= NULL;
double *precios=NULL;
int numProductos=0;

int main() {
    int opcion;

    printf("=== SISTEMA DE INVENTARIO ===\n");

    // Llenar inventario con datos de ejemplo (usar la tabla proporcionada)
    
    // Menú interactivo
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Agregar producto\n");
        printf("2. Mostrar inventario\n");
        printf("3. Calcular valor total del inventario\n");
        printf("4. Busca un producto por su nombre\n");
        printf("5. Modifica una cantidad de un  producto\n");
        printf("6. Salir\n");
        printf("Seleccione opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
            //agregar producto
            agregarProducto();
            break;
            case 2:
            //muestra todo el inventario
            mostrarProductos();
            break;
            case 3:
            //calcula el valor total del inventario
            printf("El valor total del inventario es: %.5lf\n",calcularValorTotalInventario());
            break;
            case 4:
            
            buscarProducto();
            break;

            case 5:

            actualizarStock();
            break;
            case 6:

            printf("Saliendo del sistema...\n");
            break;

            default:
            printf("Opcion invalida.\n");
        }
    } while(opcion != 6);

    // Liberar memoria antes de salir
    liberarInventario();
    return 0;
}

int agregarProducto() {
    
    int num_productos_agrega;

    if (numProductos==0){
        
        printf("Cuantos productos quieres ingresar:");
    } else {

        printf("Actualmente hay %d productos. Cuantos mas quieres agregar:", numProductos);
        
    }
    scanf("%d", &num_productos_agrega);

    if (num_productos_agrega<= 0){
        return 0;
    }
    // Re-Asignar memoria exacta para el nombre y copiarlo
    if (numProductos==0){
        
        nombresProductos= (char**) calloc(num_productos_agrega,sizeof(char *));
        precios= (double *) calloc(num_productos_agrega,sizeof(double));
        cantidades= (int *) calloc(num_productos_agrega,sizeof(int));

        if (!nombresProductos || !precios || !cantidades) {
        
            printf("NO SE PUDO RESERVAR MEMORIA\n");
            exit(1);
        }
        
    }else{
     //Aumentamos la memoria en caso de que quiera ingresar mas productos 
     
        //variable que guarda el total de los productos + los nuevos productos
        int nuevo_total= numProductos+num_productos_agrega;

        char **tem_nombres= (char **) realloc(nombresProductos,nuevo_total*sizeof(char*));
        double *tem_precios= (double *) realloc(precios,nuevo_total*sizeof(double));
        int *tem_cantidades= (int *) realloc(cantidades,nuevo_total*sizeof(int));

        if (!tem_nombres || !tem_precios || !tem_cantidades) {
        
            printf("NO SE PUDO RESERVAR MEMORIA\n");
            exit(1);
        }
        //asignacion para incrementar la memoria
        nombresProductos = tem_nombres;
        precios = tem_precios;
        cantidades = tem_cantidades;

    }

    //esta operacion es para tener una variable y saber cuantos productos se van a ingresar
    int limite_prod= numProductos + num_productos_agrega;

    //bucle para ingresar los productos
    for (int i = numProductos; i < limite_prod; i++){

        char buffer[MAX_NOMBRE];

        printf("\nNombre del producto: ");
        // Limpiar el búfer de entrada antes de fgets 
        while (getchar() != '\n'); 

        if (fgets(buffer, MAX_NOMBRE, stdin) != NULL) {
            // Eliminar el salto de línea de fgets
            buffer[strcspn(buffer, "\n")] = 0;
        }

        *(nombresProductos + i) = (char *)calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(*(nombresProductos + i), buffer);

        printf("\nPrecio: ");
        scanf("%lf", (precios + i));
        printf("\nCantidad: ");
        scanf("%d", (cantidades + i));
        
    }
    
    //actualiza el total de productos
    numProductos+=num_productos_agrega;

    return 0;
}


void mostrarProductos() {
	if (numProductos==0){
        printf("Inventario vacio");
        return;
    }
    
    printf("\n|||||---- Lista de productos (%d) ----|||||  \n",numProductos);
    
    for (int i = 0; i < numProductos; i++){
        
        printf("%d. %-15s | $%-8.4lf | Cantidad: %d \n"
            ,(i+1), *(nombresProductos+i),*(precios+i),*(cantidades+i));

    }
}

double calcularValorTotalInventario() {
	double total = 0;
	// Recorrer todos los productos de la categoría
    for (int i = 0; i < numProductos; i++){

        total+=*(precios+i) * *(cantidades+i); 
        
    }
	
	return total;
}

void liberarInventario() {
	for (int i = 0; i < numProductos; i++) {
        free(*(nombresProductos + i));
    }
    free(nombresProductos);
    free(cantidades);
    free(precios);
}

void buscarProducto(){

    char nombreBuscado[MAX_NOMBRE];
    int encontrado=0;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nIngresa el nombre del producto a buscar: ");
    
    // 2. Lectura segura del nombre
    if (fgets(nombreBuscado, MAX_NOMBRE, stdin) == NULL) {
        return; // Si falla la lectura
    }
    // Eliminamos el salto de línea que fgets guarda al final
    nombreBuscado[strcspn(nombreBuscado, "\n")] = 0;

    for (int i = 0; i < numProductos; i++){
        
        if (strcmp(*(nombresProductos+i),nombreBuscado)==0){

            printf("\nProducto encontrado \n");
            printf("%d. %-15s | $%-8.4lf | Cantidad: %d \n"
            ,(i+1), *(nombresProductos+i),*(precios+i),*(cantidades+i));
 
            encontrado=1;

            break;
        }
         
    }

    if(!encontrado){

        printf("El producto no existe");
    }
    

}

void actualizarStock(){

    int nuevaCantidad;
    int posicion;

    if (numProductos == 0) {
        printf("\nEl inventario está vacío.\n");
        return;
    }

    printf("Productos disponibles: 1 al %d\n", numProductos);
    
    printf("Ingresa la posicion del producto a modificar: ");
    scanf("%d",&posicion);

    if(posicion<1 || posicion>numProductos){

        printf("\n Posicion invalida. Debe ser entre 1 y %d",numProductos);
        return;
    }

    int i= posicion-1;

    //dato que se pidio 
    printf("\nProducto seleccionado: %s\n", *(nombresProductos + i));
    printf("Cantidad actual: %d\n", *(cantidades + i));

    // Pedir el nuevo dato
    printf("Ingresa la nueva cantidad: ");

    int c; 
    while ((c = getchar()) != '\n' && c != EOF);

    scanf("%d", &nuevaCantidad);

    //asignamos la nueva cantidad del producto a la anterio 
    *(cantidades + i) = nuevaCantidad;

    //Dato actualizado 
    printf("\n¡Stock actualizado para %s!\n", *(nombresProductos + i));
    printf(" Nueva cantidad: %d\n", *(cantidades + i));

}