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

int filtroV(struct persona *p,char placa[20]){
    struct persona *aux;
    aux = p;
    while(aux != NULL){
        struct vehiculo *v;
        v = aux->vehiculo;
        while(v != NULL){
            if(strcmp(v->placa,placa)==0){
            printf("\n\nya existe esta placa en el sistema, introduzca otra\n\n");
            getch();
            return 0;
            }
            v = v->prox;
        }
        aux = aux->prox;
    }
    return 1;
}

int filtroPlaca(char placa[20]){
    if(strlen(placa)> 9){
        printf("\n\nla placa no puede exceder los 8 caracteres\n\n");
        getch();
        return 0;
    }
    return 1;
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

int contarinfraccion(struct infraccion *p){
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

int agregarV(struct persona *p,int buscar){
    struct persona *aux = p;
    int cedula,monto,Nmultas,cantidadcar,cantidadmultas,aprobado,aprobadoP;
    char marca[20], modelo[20], year[20], color[20], placa[20];
    while(aux != NULL){
        if(aux->cedula == buscar){
            printf("cantidad de vehiculos(0 para salir): ");
            scanf("%i",&cantidadcar);
            fflush(stdin);
            system("cls");
            if(cantidadcar != 0){
                for(int i = 1; i<=cantidadcar; i++){
                printf("\n\nVehiculo %i:\n\n",i);
                do{
                    printf("Placa: ");
                    fgets(placa,20,stdin);
                    aprobadoP = filtroPlaca(placa);
                    aprobado = filtroV(p,placa);
                } while(aprobado == 0 || aprobadoP == 0);
                printf("marca: ");
                fgets(marca,20,stdin);
                printf("color: ");
                fgets(color,20,stdin);
                printf("Modelo: ");
                fgets(modelo,20,stdin);
                printf("year: ");
                fgets(year,20,stdin);
                agregarvehiculo(&aux->vehiculo,placa,marca,color,modelo,year);
                }
                return 1;
            }
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

int modificarV(struct persona **p,int buscar,char Nplaca[20]){
    int op = -1;
    struct persona *aux;
    struct vehiculo *v;
    aux = *p;
    while(aux!=NULL){
        if(aux->cedula == buscar){
            v = aux->vehiculo;
            while(v != NULL){
                if(strcmp(v->placa,Nplaca)==0){
                    while(op != 0){
                    printf("----DATOS DEL VEHICULO----\n\n");
                    printf("marca-> %s",v->marca);
                    printf("modelo-> %s",v->modelo);
                    printf("color-> %s",v->color);
                    printf("year-> %s",v->year);
                    printf("\n\nque dato desea modificar del vehiculo?\n\n");
                    printf("1. marca\n");
                    printf("2. modelo\n");
                    printf("3. color\n");
                    printf("4. year\n");
                    printf("0. salir para guardar\n\n");
                    printf("introduzca una opcion: ");
                    scanf("%i",&op);
                    fflush(stdin);
                    system("cls");
                    switch(op){
                        case 1:
                        printf("introduzca su nueva marca: ");
                        fgets(v->marca,20,stdin);
                        break;

                        case 2:
                        printf("introduzca su nuevo modelo: ");
                        fgets(v->modelo,20,stdin);
                        break;

                        case 3:
                        printf("introduzca su nuevo color: ");
                        fgets(v->color,20,stdin);
                        break;

                        case 4:
                        printf("introduzca su nuevo year: ");
                        fgets(v->year,20,stdin);
                        break;

                        case 0:
                        break;
                    }
                    system("cls");
                }
                return 1;
                }
               v = v->prox;    
            }
            return -1;
        }
        aux=aux->prox;
    }
    return 0;
}

int consultarvehiculoN(struct persona **p, char placaP[20]){
    int op = -1;
    struct persona *aux;
    struct vehiculo *v;
    aux = *p;
    while(aux!=NULL){
        v = aux->vehiculo;
        while(v != NULL){
                if(strcmp(v->placa,placaP)==0){
                system("cls");
                printf("----DATOS DEL VEHICULO----\n\n");
                printf("placa-> %s",v->placa);
                printf("marca-> %s",v->marca);
                printf("modelo-> %s",v->modelo);
                printf("color-> %s",v->color);
                printf("year-> %s",v->year);
                getch();
                return 1;
            }
            v = v->prox;
        }
        aux=aux->prox;
    }
    return 0;
}

int consultarvehiculoC(struct persona **p, int buscar){
    int op = -1,i = 1;
    struct persona *aux;
    struct vehiculo *v;
    aux = *p;
    while(aux!=NULL){
        if(aux->cedula == buscar){
            v = aux->vehiculo;
            printf( "\n\nMostrar vehiculos\n\n");
            while (v){
            printf("Vehiculo %i\n\n",i);
            printf("placa ->%s", v->placa);
            printf("marca ->%s", v->marca);
            printf("color ->%s", v->color);
            printf("modelo ->%s", v->modelo);
            printf("year ->%s", v->year);
            printf("\n");
            v = v->prox;
            i++;
	        };
            getch();
            return 1;
        }
        aux=aux->prox;
    }
    return 0;
}

int eliminarV(struct persona **p, int x, char Nplaca[20] ){
    struct persona *aux = *p;
    struct vehiculo *v;

    while(aux != NULL){
        v = aux->vehiculo;
        if(v){
            if(strcmp(v->placa,Nplaca)==0){
            for(struct infraccion *in = NULL;v->infraccion;v->infraccion = v->infraccion->prox,delete(in)){
                in = v->infraccion;
            }
            aux->vehiculo = v->prox;
            delete v;
            return 1;
            } else {
                while(v->prox!= NULL && strcmp(v->prox->placa,Nplaca)!=0){
                    v= v->prox;
                }
                if(v->prox){
                    vehiculo *temp = v->prox;
                    for(struct infraccion *in = NULL;temp->infraccion;temp->infraccion = temp->infraccion->prox,delete(in)){
                        in = temp->infraccion;
                    }
                    v->prox = temp->prox;
                    delete temp;
                    return 1;
                }
                return -1;
            }
        } else {
            return -1;
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
        for(i=cantidadpersona; i>0;i--){
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
    int opC = -1,vehiculoA;
    char Nplaca[20],placaP[20];
    cargardatos(&p);
    system("cls");
    while(op != 0){
        opC = -1;
        printf("1. agregar datos\n");
        printf("2. modificar datos\n");
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
            system("cls");
            vehiculoA = agregarV(p, cedula);
            if(vehiculoA == 0){
                system("cls");
                printf("no se pudo encontrar a la persona\n");
                getch();
            }
            else if(vehiculoA == 1){
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
            modif = modificarV(&p,buscarpersona,Nplaca);
            if(modif == 0){
                system("cls");
                printf("no se pudo encontrar a la persona\n");
                getch();
            } 
            else if(modif == -1){
                system("cls");
                printf("no se pudo encontrar la placa asociada a %i\n",buscarpersona);
                getch();
            }
            else if(modif == 1){
                guardardatos(p);
            }
            system("cls");
            break;

            case 3:
            fflush(stdin);
            system("cls");
            while(opC != 0){
                printf("----CONSULTAS----\n\n");
                printf("1. cedula\n");
                printf("2. placa del vehiculo\n");
                printf("0. salir\n\n");
                printf("introduzca una opcion: ");
                scanf("%i",&opC);
                system("cls");
                switch(opC){
                    case 1:
                    printf("introduzca la cedula de la persona: ");
                    scanf("%i",&buscarpersona);
                    consul = consultarvehiculoC(&p,buscarpersona);
                    if(consul == 0){
                        system("cls");
                        printf("no se pudo encontrar a la persona\n");
                        getch();
                    }
                    system("cls");
                    break;
                    case 2:
                    fflush(stdin);
                    printf("introduzca la placa del vehiculo: ");
                    fgets(placaP,20,stdin);
                    consul = consultarvehiculoN(&p,placaP);
                    if(consul == 0){
                        system("cls");
                        printf("no se pudo encontrar la placa\n");
                        getch();
                    }
                    system("cls");
                    break;
                }
            }
            break;

            case 4:
            fflush(stdin);
            printf("introduzca la cedula de la persona: ");
            scanf("%i",&buscarpersona);
            fflush(stdin);
            printf("introduzca la placa: ");
            fgets(Nplaca,20,stdin);
            elim = eliminarV(&p,buscarpersona,Nplaca);
            if(elim == 0){
                system("cls");
                printf("no se pudo encontrar a la persona\n");
                getch();
            } else if(elim == -1){
                system("cls");
                printf("no se pudo encontrar la placa asociada a %i\n",buscarpersona);
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