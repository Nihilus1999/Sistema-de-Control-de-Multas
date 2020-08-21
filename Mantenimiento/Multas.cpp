#include <stdio.h>
#include <stdlib.h>
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

int filtroM(struct persona *p,int Nmulta){
    struct persona *aux;
    aux = p;
    while(aux != NULL){
        struct vehiculo *v;
        v = aux->vehiculo;
        while(v != NULL){
            struct infraccion *in;
            in = v->infraccion;
                while(in != NULL){
                    if(in->cantidad == Nmulta){
                    printf("\n\nya existe este numero de multa en el sistema, introduzca otra\n\n");
                    getch();
                    return 0;
                    }
                    in = in->prox;
                }
            v = v->prox;
            }
        aux = aux->prox;
        }
    return 1;
}

int filtroPagar(char pagado[4]){
    if((strcmp(pagado,"si\n")!=0) && (strcmp(pagado,"no\n")!=0)){
        printf("\n\n solo puede colocar si o no\n\n");
        getch();
        return 0;
    }
    return 1;
}

int contarinfraccion(struct infraccion *p){
    int cont = 0;
    for(;p; p = p->prox){
        cont += 1;
    }
    return cont;

}

int contarpersona(struct persona *p){
    int cont = 0;
	for(;p; p = p->prox){
        cont += 1;
    }
	return cont;
}

int contarvehiculo(struct vehiculo *p){
    int cont = 0;
	for(;p; p = p->prox){
        cont += 1;
    }
	return cont;

}

void imprimirTodo(struct persona *p){
    int x, y,z;
    system("cls");
	printf("----BASE DE DATOS----\n\n");
    x = contarpersona(p);
	for(; p; p = p->prox){
        printf("---persona %i---\n\n",x);
        printf("cedula->%i\n", p->cedula);
        printf("nombre->%s", p->nombre);
        printf("apellido->%s",p->apellido);
        printf("fecha->%s", p->fecha);
        printf("ciudad de nacimiento->%s",p->ciudad);
        printf("direccion->%s\n", p->direccion);
        y = contarvehiculo(p->vehiculo);
		for(struct vehiculo *v = p->vehiculo; v; v = v->prox){
            printf("\t----Vehiculo %i----\n\n", y);
            printf("\tplaca ->%s", v->placa);
            printf("\tmodelo ->%s", v->modelo);
            printf("\tcolor ->%s", v->color);
            printf("\tmarca ->%s", v->marca);
            printf("\tyear ->%s\n", v->year);
            z = contarinfraccion(p->vehiculo->infraccion);
            for(struct infraccion *in = v->infraccion;in;in = in->prox){
                printf("\t\t----multa %i----\n\n", z);
                printf("\t\tnumero multa -> %i\n",in->cantidad);
                printf("\t\tfecha ->%s", in->fecha);
                printf("\t\ttipo ->%s", in->tipo);
                printf("\t\tmonto ->%i\n", in->monto);
                printf("\t\tpagado ->%s\n", in->pagado);
                z--;
            }
            y--;
        }
        x--;
	}
}

void agregarpersona(struct persona **p,int cedula, char nombre[20], char apellido[20], char fecha[20],char ciudad_nacimiento[20], char direccion[20]){
    struct persona *aux;
    aux = new struct persona;
    aux->cedula = cedula;
    strcpy(aux->nombre,nombre);
    strcpy(aux->apellido,apellido);
    strcpy(aux->fecha,fecha);
    strcpy(aux->ciudad,ciudad_nacimiento);
    strcpy(aux->direccion,direccion);
    aux->prox = *p;
    aux->vehiculo = NULL;
    *p = aux;
}

void agregarvehiculo(struct vehiculo **p, char placa[50], char marca[50], char color[50], char modelo[50], char year[20]){
    struct vehiculo *aux;
    aux = new struct vehiculo;
    strcpy(aux->placa,placa);
    strcpy(aux->marca,marca);
    strcpy(aux->color,color);
    strcpy(aux->modelo,modelo);
    strcpy(aux->year,year);
    aux->prox = *p;
    aux->infraccion = NULL;
    *p = aux;
}

void agregarinfraccion(struct infraccion **p,int Nmultas, char fecha_multa[50], char tipo_multa[50], int monto, char pagado[20]){
    struct infraccion *aux;
    aux = new struct infraccion;
    aux->cantidad = Nmultas;
    strcpy(aux->fecha,fecha_multa);
    strcpy(aux->tipo,tipo_multa);
    aux->monto = monto;
    strcpy(aux->pagado,pagado);
    aux->prox = *p;
    *p = aux;
}


int agregarM(struct persona *p,int buscar, char placa[20]){
    int cantidadmultas, i, t;
    int Nmultas, monto;
    char fechai[20], tipo[20], pagado[20]; 
    struct persona *aux = p;
    while(aux != NULL){
        if(aux->cedula == buscar){
            struct vehiculo *v = aux->vehiculo;
            while(v != NULL){
                if(strcmp(v->placa,placa) == 0){
                    printf("cantidad de multas(0 para salir): ");
                    scanf("%i",&cantidadmultas);
                    fflush(stdin);
                    if(cantidadmultas == 0){
                        return 1;
                    }
                    for(i = 1; i<=cantidadmultas; i++){
                        printf("\n\nMultas %i:\n\n",i);
                        do{
                        printf("numero de multa: ");
                        scanf("%i",&Nmultas);
                        }while(filtroM(p,Nmultas) == 0);
                        fflush(stdin);
                        printf("fecha: ");
                        fgets(fechai,20,stdin);
                        printf("tipo: ");
                        fgets(tipo,20,stdin);
                        printf("monto: ");
                        scanf("%i",&monto);
                        fflush(stdin);
                        do{
                        printf("pagado: ");
                        fgets(pagado,4,stdin);
                        } while(filtroPagar(pagado)==0);
                        agregarinfraccion(&v->infraccion, Nmultas,fechai,tipo,monto,pagado);
                    }
                    return 1;
                }
                v = v->prox;
            }
        }
        aux = aux->prox;
    }
    return 0;
}

int pagar(struct persona **p,int buscar,char Nplaca[20]){
    int cont = 0, i,op = -1, op1 = -1, mal = -1;
    char confirmar[20];
    struct persona *aux;
    struct vehiculo *v;
    aux = *p;
    while(aux!=NULL){
        if(aux->cedula == buscar){
            v = aux->vehiculo;
            while(v != NULL){
                if(strcmp(v->placa,Nplaca)==0){
                    struct infraccion *in = v->infraccion;
                    struct infraccion *in2 = v->infraccion;
                    printf( "\n\n----MULTAS NO PAGADAS----\n\n");
                    while(in){
                        if(strcmp(in->pagado,"no\n")==0){
                            printf("----MULTA %i----\n\n",in->cantidad);
                            printf("fecha -> %s", in->fecha);
                            printf("tipo -> %s", in->tipo);
                            printf("monto -> %i\n", in->monto);
                            printf("pagado -> %s", in->pagado);
                            printf("\n\n");
                            cont++;
                        }
                        in = in->prox;
                    }
                    printf("las multas NO pagadas en total son %i\n\n",cont);
                    getch();
                    if(cont != 0){
                        printf("desea pagar una de estas multa?\n\n");
                        printf("1. si\n");
                        printf("2. no\n\n");
                        printf("introduzca una opcion: ");
                        scanf("%i",&op);
                        switch(op){
                            case 1:
                            printf("\n\nque multa quiere pagar (coloca el numero de multa): ");
                            scanf("%i",&op1);
                            while(in2){
                            if(op1 == in2->cantidad){
                                strcpy(in2->pagado,"si\n");
                                return 1;
                            } 
                            else {
                                printf("\n\nno selecciono un numero de multa acorde, regresara al menu\n\n");
                                system("pause");
                                system("cls");
                                return -2;
                            }
                            in2 = in2->prox;
                            }
                            break;

                            case 2:
                            return 1;
                            break;
                        }
                    }
                    return 1;
                }
               v = v->prox;    
            }
            return 0;
        }
        aux=aux->prox;
    }
    return 0;
}

int consultarmulta(struct persona **p, int Nmulta){
    struct persona *aux;
    aux = *p;
    while(aux!=NULL){
        struct vehiculo *v = aux->vehiculo;
        while(v != NULL){
            struct infraccion *in = v->infraccion;
            while(in != NULL){
                if(in->cantidad == Nmulta){
                    system("cls");
                    printf("---- MULTA %i----\n\n", in->cantidad);
                    printf("fecha -> %s",in->fecha);
                    printf("tipo -> %s",in->tipo);
                    printf("monto -> %i\n", in->monto);
                    printf("pagado -> %s", in->pagado);
                    getch();
                    return 1;
                }
                in = in->prox;
            }
            v = v->prox;
        }
        aux = aux->prox;
    }
    return 0;
}

int eliminarM(struct persona **p, int x, char Nplaca[20], int Nmulta){
    struct persona *aux = *p;
    struct vehiculo *v;
    struct infraccion *in;

    while(aux != NULL){
        if(aux->cedula == x){
                v = aux->vehiculo;
                while(v != NULL){
                    if(strcmp(v->placa,Nplaca)==0){
                            in = v->infraccion;
                            if(in){
                            if(in->cantidad == Nmulta){
                            v->infraccion = in->prox;
                            delete in;
                            return 1;
                            } else {
                                while(in->prox!= NULL && in->prox->cantidad != Nmulta){
                                    in = in->prox;
                                }
                                if(in->prox){
                                    struct infraccion *temp = in->prox;
                                    in->prox = temp->prox;
                                    delete temp;
                                    return 1;
                                }
                                return -2;
                            }
                        } else {
                            return -2;
                        }
                    }
                v = v->prox;
                return -1;
            }
        }
        aux = aux->prox;
    }
    return 0;
    
}

void cargardatos(struct persona **p){
    int i,y,z,cedula,monto,Nmultas,cantidadpersona = 0, cantidadvehiculos = 0,cantidadmultas = 0;
    char tomar[101];
    char nombre[20], apellido[20], fecha[20], ciudad_nacimiento[20], direccion[40];
    char marca[20], modelo[20], year[20], color[20], placa[20];
    char fechai[20], tipo[20], pagado[20];
    if(p){
        archivo = fopen("datos.txt","rt");
        if(archivo == NULL){
            printf("No se pudo encontrar el archivo\n");
            printf("Posiblemente se deba a que no ha registrado ninguna persona\n");
            printf("Para registrar vaya a la opcion:\n\n");
            printf("MANTENIMIENTO->PERSONAS->AGREGAR\n\n");
            system("pause");
        }
        fgets(tomar,20,archivo); sscanf(tomar,"%i",&cantidadpersona);
        for(i=0; i<cantidadpersona;i++){
            fgets(tomar,20,archivo); sscanf(tomar,"%i",&cedula);
            fgets(nombre,20,archivo);
            fgets(apellido,20,archivo);
            fgets(ciudad_nacimiento,20,archivo);
            fgets(fecha,20,archivo);
            fgets(direccion,30,archivo);
            agregarpersona(p,cedula,nombre,apellido,fecha,ciudad_nacimiento,direccion);
            fgets(tomar,20,archivo); sscanf(tomar,"%i",&cantidadvehiculos);
            for(y=0;y<cantidadvehiculos;y++){
                fgets(placa,20,archivo);
                fgets(marca,20,archivo);
                fgets(color,20,archivo);
                fgets(modelo,20,archivo);
                fgets(year,20,archivo);
                agregarvehiculo(&(*p)->vehiculo,placa,marca,color,modelo,year);
                fgets(tomar,20,archivo); sscanf(tomar,"%i",&cantidadmultas);
                for(z=0;z<cantidadmultas;z++){
                    fgets(tomar,20,archivo); sscanf(tomar,"%i",&Nmultas);
                    fgets(fechai,20,archivo);
                    fgets(tipo,20,archivo);
                    fgets(tomar,20,archivo); sscanf(tomar,"%i",&monto);
                    fgets(pagado,4,archivo);
                    agregarinfraccion(&(*p)->vehiculo->infraccion,Nmultas,fechai,tipo,monto,pagado);
                }
            }
        }
    }
    else{
        system("cls");
        printf("No ha ingresado ningun dato");
        system("pause");
        exit;
    }
}

void guardardatos(struct persona *p){
    archivo = fopen("datos.txt", "wt");
    fprintf(archivo,"%i\n",contarpersona(p));
    for(; p; p = p->prox) {
        fprintf(archivo,"%i\n",p->cedula);
        fprintf(archivo,"%s",p->nombre);
        fprintf(archivo,"%s",p->apellido);
        fprintf(archivo,"%s",p->fecha);
        fprintf(archivo, "%s", p->ciudad);
        fprintf(archivo,"%s",p->direccion);
        fprintf(archivo,"%i\n",contarvehiculo(p->vehiculo));
        for(struct vehiculo *v = p->vehiculo; v; v = v->prox){
            fprintf(archivo,"%s",v->placa);
            fprintf(archivo,"%s",v->marca);
            fprintf(archivo,"%s",v->color);
            fprintf(archivo,"%s",v->modelo);
            fprintf(archivo,"%s",v->year);
            fprintf(archivo,"%i\n",contarinfraccion(v->infraccion));
            for(struct infraccion *in = v->infraccion; in ; in = in->prox){
                fprintf(archivo,"%i\n",in->cantidad);
                fprintf(archivo,"%s",in->fecha);
                fprintf(archivo,"%s",in->tipo);
                fprintf(archivo,"%i\n",in->monto);
                fprintf(archivo,"%s",in->pagado);
            }

        }
    }
    fclose(archivo);
    system("cls");
    printf("datos guardados exitosamente\n\n");
    system("pause");
    system("cls");
}

int main(){
    persona *p = NULL;
    int op = -1, cedula, modif, elim, consul, buscarpersona;
    int opC = -1, multaA, Nmulta;
    char Nplaca[20];
    cargardatos(&p);
    system("cls");
    while(op != 0){
        opC = -1;
        printf("1. agregar datos\n");
        printf("2. pagar\n");
        printf("3. consultar\n");
        printf("4. eliminar\n");
        printf("5. base de datos\n");
        printf("0. salir\n\n");
        printf("introduzca una opcion: ");
        scanf("%i",&op);
        fflush(stdin);
        system("cls");
        switch(op){
            case 1:
            printf("introduzca la cedula del titular: ");
            scanf("%i",&cedula);
            fflush(stdin);
            printf("introduzca la placa de la persona: ");
            fgets(Nplaca,20,stdin);
            system("cls");
            multaA = agregarM(p,cedula,Nplaca);
            if(multaA == 0){
                system("cls");
                printf("no se pudo encontrar a la persona\n");
                getch();
            }
            else if(multaA == 1){
                guardardatos(p);
            }
            system("cls");
            break;

            case 2:
            fflush(stdin);
            printf("introduzca la cedula de la persona: ");
            scanf("%i",&buscarpersona);
            fflush(stdin);
            printf("introduzca la placa: ");
            fgets(Nplaca,20,stdin);
            system("cls");
            modif = pagar(&p,buscarpersona,Nplaca);
            if(modif == 0){
                system("cls");
                printf("no se pudo encontrar a la persona o la placa del vehiculo\n");
                getch();
            } 
            else if(modif == 1){
                guardardatos(p);
            }
            system("cls");
            break;

            case 3:
            fflush(stdin);
            printf("introduzca el numero de la multa: ");
            scanf("%i",&Nmulta);
            fflush(stdin);
            consul = consultarmulta(&p,Nmulta);
            if(consul == 0){
                printf("\n\nhay un error en el numero de multa\n\n");
                system("pause");
                system("cls");
            }
            system("cls");
            break;

            case 4:
            fflush(stdin);
            printf("introduzca su cedula: ");
            scanf("%i",&buscarpersona);
            fflush(stdin);
            printf("introduzca su placa asociada a la multa a eliminar: ");
            fgets(Nplaca,20,stdin);
            printf("introduzca el numero de multa a eliminar: ");
            scanf("%i",&Nmulta);
            elim = eliminarM(&p,buscarpersona,Nplaca, Nmulta);
            if(elim == 0){
                system("cls");
                printf("no se pudo encontrar a la persona\n");
                getch();
            } else if(elim == -1){
                system("cls");
                printf("no se pudo encontrar la placa asociada a %i\n",buscarpersona);
                getch();
            } else if(elim == -2){
                system("cls");
                printf("el numero de multa asociado a %s es incorrecto\n",Nplaca);
                getch();
            }
            else if(elim == 1) {
                guardardatos(p);
            }
            system("cls");
            break;

            case 5:
            imprimirTodo(p);
            getch();
            system("cls");
            break;

            case 0:
            break;
        }
    }
    return 0;
}