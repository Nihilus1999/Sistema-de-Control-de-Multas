#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

FILE *archivo;

struct persona {
    int cedula;
    char nombre[20];
    char apellido[20];
    char fecha[20];
    char ciudad[20];
    char direccion[40];
    persona *prox;
    struct vehiculo *vehiculo;
};

struct vehiculo {
    char placa[20];
    char marca[20];
    char modelo[20];
    char year[20];
    char color[20];
    vehiculo *prox;
    struct infraccion *infraccion;
};

struct infraccion {
    int cantidad;
    char fecha[20];
    char tipo[20];
    int monto;
    char pagado[20];
    infraccion *prox;
};

int validar_numero_naturales(char numero[]){
    int i;
        for(i=0; i<strlen(numero); i++)
        {
            if(!(isdigit(numero[i]))){

                system("cls");
                printf("Solo puede ingresar numeros positivos en el menu");
                getch();
                system("cls");
                return 0;
            }
        }
        return 1;
}

int main(){ 
    persona *p = NULL;// variables de las estructuras
    char op[10], op1[10], op2[10]; //variables de tipo caracter
    int bandera = 0, opvalido = -1, op1valido = -1, op2valido = -1; //variables de tipo enteras
    while(opvalido != 0){
        system("cls");
        op1valido = -1;
        do{
        printf("----SISTEMA DE CONTROL DE MULTAS----\n\n");
        printf("1. Mantenimineto\n");
        printf("2. Operaciones y consultas\n");
        printf("0. Salir del programa\n\n");
        printf("introduzca una opcion: ");
        scanf("%s",&op);
        bandera=validar_numero_naturales(op);
        } while(bandera==0);

        opvalido = atoi(op);

        if(opvalido>2){
            system("cls");
            printf("la opcion no corresponde al menu principal\n\n");
            system("pause");
        }

        else{
            system("cls");
            switch(opvalido){
                case 1:
                while(op1valido != 0){
                    op2valido = -1;
                    system("cls");
                    do{
                    printf("----MANTENIMIENTO----\n\n");
                    printf("1. Personas\n");
                    printf("2. Vehiculos\n");
                    printf("0. salir al menu anterior\n\n");
                    printf("introduzca una opcion: ");
                    scanf("%s",&op1);
                    bandera = validar_numero_naturales(op1);
                    } while(bandera == 0);

                    op1valido = atoi(op1);

                    system("cls");
                    if(op1valido == 0){
                        break;
                    }
                    else if(op1valido>2){
                        printf("la opcion no corresponde al menu principal\n\n");
                        system("pause");
                    }
                    else{
                        switch(op1valido){
                        case 1:
                        while(op2valido != 0){
                            system("cls");
                            do{
                            printf("----PERSONA----\n\n");
                            printf("1. Agregar\n");
                            printf("2. Modificar\n");
                            printf("3. Consultar\n");
                            printf("4. borrar una personas\n");
                            printf("0. salir al menu anterior\n\n");
                            printf("introduzca una opcion: ");
                            scanf("%s",&op2);
                            bandera = validar_numero_naturales(op2);
                            } while(bandera == 0);

                            op2valido = atoi(op2);

                            system("cls");
                            if(op2valido == 0){
                                break;
                            }
                            else if(op2valido>4){
                                printf("la opcion no corresponde al menu principal\n\n");
                                system("pause");
                            }
                            else{
                                switch(op2valido){
                                    case 1:
                                    
                                    break;

                                    case 2:

                                    break;

                                    case 3:

                                    break;

                                    case 4:

                                    break;
                                }
                            }

                        }

                        case 2:
                        while(op2valido != 0){
                            system("cls");
                            do{
                            printf("----VEHICULO----\n\n");
                            printf("1. Agregar\n");
                            printf("2. Modificar\n");
                            printf("3. Consultar\n");
                            printf("4. Eliminar vehiculo del sistema\n");
                            printf("0. salir al menu anterior\n\n");
                            printf("introduzca una opcion: ");
                            scanf("%s",&op2);
                            bandera = validar_numero_naturales(op2);
                            } while(bandera == 0);

                            op2valido = atoi(op2);

                            system("cls");
                            if(op2valido == 0){
                                break;
                            }
                            else if(op2valido>4){
                                printf("la opcion no corresponde al menu principal\n\n");
                                system("pause");
                            }
                            else{
                                switch(op2valido){
                                    case 1:

                                    break;

                                    case 2:

                                    break;

                                    case 3:

                                    break;

                                    case 4:

                                    break;
                                }
                            }

                        }
                        break;
                        }
                    }
                }
                break;

                case 2:
                while(op1valido != 0){
                    system("cls");
                    op2valido = -1;
                    do{
                    printf("----OPERACIONES----\n\n");
                    printf("1. Operaciones con multas\n");
                    printf("2. Consultas\n");
                    printf("0. salir al menu anterior\n\n");
                    printf("introduzca una opcion: ");
                    scanf("%s",&op1);
                    bandera = validar_numero_naturales(op1);
                    } while(bandera == 0);

                    op1valido = atoi(op1);

                    system("cls");
                    if(op1valido == 0){
                        break;
                    }
                    else if(op1valido>2){
                        printf("la opcion no corresponde al menu principal\n\n");
                        system("pause");
                    }
                    else{
                        switch(op1valido){
                        case 1:
                        while(op2valido != 0){
                            system("cls");
                            do{
                            printf("----OPERACIONES CON MULTAS----\n\n");
                            printf("1. Agregar\n");
                            printf("2. Pagar\n");
                            printf("3. Consultar\n");
                            printf("4. Eliminar multa\n");
                            printf("0. salir al menu anterior\n\n");
                            printf("introduzca una opcion: ");
                            scanf("%s",&op2);
                            bandera = validar_numero_naturales(op2);
                            } while(bandera == 0);

                            op2valido = atoi(op2);

                            system("cls");
                            if(op2valido == 0){
                                break;
                            }
                            else if(op2valido>4){
                                printf("la opcion no corresponde al menu principal\n\n");
                                system("pause");
                            }
                            else{
                            switch(op2valido){
                                case 1:

                                break;

                                case 2:

                                break;

                                case 3:

                                break;

                                case 4:

                                break;
                            }
                            }
                        }
                        break;
                        case 2:
                        while(op2valido != 0){
                            system("cls");
                            do{
                            printf("----CONSULTAS----\n\n");
                            printf("1. Buscar nombre de la persona\n");
                            printf("2. Buscar cedula de la persona\n");
                            printf("3. Buscar una placa\n");
                            printf("4. Buscar por infracciones de hace 2 años\n");
                            printf("0. salir al menu anterior\n\n");
                            printf("introduzca una opcion: ");
                            scanf("%s",&op2);
                            bandera = validar_numero_naturales(op2);
                            } while(bandera == 0);

                            op2valido = atoi(op2);

                            system("cls");
                            if(op2valido == 0){
                                break;
                            }
                            else if(op2valido>4){
                                printf("la opcion no corresponde al menu principal\n\n");
                                system("pause");
                            }
                            else{
                                switch(op2valido){
                                    case 1:

                                    break;

                                    case 2:

                                    break;

                                    case 3:

                                    break;

                                    case 4:

                                    break;
                                }

                            }
                        }
                        break;
                        }
                    }
                }
                case 0:
                system("cls");
                printf("Gracias por usar nuestro servicios");
                break;
            }
        }
    }
    return 0;
}