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

int filtroP(struct persona **p,int cedula){
    struct persona *aux;
    aux = *p;
    while(aux != NULL){
        if(aux->cedula == cedula){
            printf("\n\nya existe esta cedula en el sistema, introduzca otra\n\n");
            getch();
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

int filtroCNA(char nombre[20], char apellido[20]){
    if(strlen(nombre) + strlen(apellido) > 22){
        printf("\n\nentre el nombre y apellido no puede exceder de los 20 caracteres\n\n");
        getch();
        return 0;
    }
    return 1;
}

int filtroD(char direccion[40]){
    if(strlen(direccion) > 25){
        printf("\n\nla direccion no puede exceder los 25 caracteres\n\n");
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

int contarinfraccion(struct infraccion *p){
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
        y = 1;
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
                z++;
            }
            y++;
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

int agregarP(struct persona **p){
    int cedula;
    char nombre[20],apellido[20], fecha[20], ciudad_nacimiento[20], direccion[40];
    do{
    system("cls");
    printf("introduzca la cedula (0 para salir): ");
    scanf("%i",&cedula);
    fflush(stdin);
    }while (filtroP(p,cedula) == 0);
    if(cedula == 0){
        system("cls");
        return 0;
    }
    do{
    printf("introduzca su nombre: ");
    fgets(nombre,20,stdin);
    printf("introduzca su apellido: ");
    fgets(apellido,20,stdin);
    } while (filtroCNA(nombre,apellido) == 0);

    printf("introduzca su fecha de nacimiento: ");
    fgets(fecha,20,stdin);
    printf("introduzca su ciudad de nacimiento: ");
    fgets(ciudad_nacimiento,20,stdin);

    do{
    printf("introduzca su direccion: ");
    fgets(direccion,40,stdin);
    }while(filtroD(direccion) == 0);

    agregarpersona(p,cedula,nombre,apellido,fecha,ciudad_nacimiento,direccion);

    return 1;
}

int modificarpersona(struct persona **p,int buscar){
    int op = -1;
    struct persona *aux;
    aux = *p;
    while(aux!=NULL){
        if(aux->cedula == buscar){
            while(op != 0){
                printf("----DATOS DE LA PERSONA----\n\n");
                printf("nombre-> %s",aux->nombre);
                printf("apellido-> %s",aux->apellido);
                printf("fecha-> %s",aux->fecha);
                printf("ciudad de nacimiento-> %s",aux->ciudad);
                printf("direccion-> %s",aux->direccion);
                printf("\n\nque dato desea modificar?\n\n");
                printf("1. nombre y apellido\n");
                printf("2. fecha de nacimiento\n");
                printf("3. ciudad de nacimiento\n");
                printf("4. direccion\n");
                printf("0. salir\n\n");
                printf("introduzca una opcion: ");
                scanf("%i",&op);
                fflush(stdin);
                system("cls");
                switch(op){
                    case 1:
                    do{
                    printf("introduzca su nuevo nombre: ");
                    fgets(aux->nombre,20,stdin);
                    printf("introduzca su nuevo apellido: ");
                    fgets(aux->apellido,20,stdin);
                    } while(filtroCNA(aux->nombre,aux->apellido)==0);
                    break;

                    case 2:
                    printf("introduzca su nueva fecha de nacimiento: ");
                    fgets(aux->fecha,20,stdin);
                    break;

                    case 3:
                    printf("introduzca su nueva ciudad de nacimiento: ");
                    fgets(aux->ciudad,20,stdin);
                    break;

                    case 4:
                    do{
                    printf("introduzca su nueva direccion: ");
                    fgets(aux->direccion,30,stdin);
                    } while(filtroD(aux->direccion)==0);
                    break;

                    case 0:
                    break;
                }
                system("cls");
            }
            return 1;
        }
        aux=aux->prox;
    }
    return 0;
}

int consultarpersonaN(struct persona **p, char nombre[20],char apellido[20]){
    int op = -1;
    struct persona *aux;
    aux = *p;
    while(aux!=NULL){
        if(strcmp(aux->nombre,nombre)==0 && strcmp(aux->apellido,apellido)==0){
            system("cls");
            printf("----DATOS DE LA PERSONA----\n\n");
            printf("cedula-> %i\n",aux->cedula);
            printf("nombre-> %s",aux->nombre);
            printf("apellido-> %s",aux->apellido);
            printf("fecha-> %s",aux->fecha);
            printf("ciudad de nacimiento-> %s",aux->ciudad);
            printf("direccion-> %s",aux->direccion);
            getch();
            return 1;
        }
        aux=aux->prox;
    }
    return 0;
}

int consultarpersonaC(struct persona **p, int buscar){
    int op = -1;
    struct persona *aux;
    aux = *p;
    while(aux!=NULL){
        if(aux->cedula == buscar){
            system("cls");
            printf("----DATOS DE LA PERSONA----\n\n");
            printf("cedula-> %i\n",aux->cedula);
            printf("nombre-> %s",aux->nombre);
            printf("apellido-> %s",aux->apellido);
            printf("fecha-> %s",aux->fecha);
            printf("ciudad de nacimiento-> %s",aux->ciudad);
            printf("direccion-> %s",aux->direccion);
            getch();
            return 1;
        }
        aux=aux->prox;
    }
    return 0;
}

int eliminarP(struct persona **p, int x){
    struct persona *aux = *p;
    if(aux){
        if(aux->cedula==x){
        for(struct vehiculo *ve = NULL; aux->vehiculo; aux->vehiculo = aux->vehiculo->prox, delete(ve)){
			ve = aux->vehiculo;
            for(struct infraccion *in = NULL; ve->infraccion; ve->infraccion = ve->infraccion->prox,delete(in)){
                in = ve->infraccion;
            }
		}
        *p= aux->prox;
        delete aux;
        return 1;
        } else {
            while(aux->prox!= NULL && aux->prox->cedula!=x){
                aux = aux->prox;
            }
            if(aux->prox){
                persona *temp = aux->prox;
                for(struct vehiculo *ve = NULL; temp->vehiculo; temp->vehiculo = temp->vehiculo->prox, delete(ve)){
                    ve = temp->vehiculo;
                    for(struct infraccion *in = NULL; ve->infraccion; ve->infraccion = ve->infraccion->prox,delete(in)){
                        in = ve->infraccion;
                    }
                }
                aux->prox = temp->prox;
                delete temp;
                return 1;
            }
            return 0;
        }
    } else {
        return 0;
    }
    
}

void cargardatos(struct persona **p){
    int i,y,z,cedula,Nmultas,monto,cantidadpersona = 0, cantidadvehiculos = 0,cantidadmultas = 0;
    char tomar[101];
    char nombre[20], apellido[20], fecha[20], ciudad_nacimiento[20], direccion[20];
    char marca[20], modelo[20], year[20], color[20], placa[20];
    char fechai[20], tipo[20], pagado[5];
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
            fgets(fecha,20,archivo);
            fgets(ciudad_nacimiento,20,archivo);
            fgets(direccion,20,archivo);
            agregarpersona(p,cedula,nombre,apellido,fecha,ciudad_nacimiento,direccion);
            fgets(tomar,20,archivo); sscanf(tomar,"%i",&cantidadvehiculos);
            for(y=cantidadvehiculos;y>0;y--){
                fgets(placa,20,archivo);
                fgets(marca,20,archivo);
                fgets(color,20,archivo);
                fgets(modelo,20,archivo);
                fgets(year,20,archivo);
                agregarvehiculo(&(*p)->vehiculo,placa,marca,color,modelo,year);
                fgets(tomar,20,archivo); sscanf(tomar,"%i",&cantidadmultas);
                for(z=cantidadmultas;z>0;z--){
                    fgets(tomar,20,archivo); sscanf(tomar,"%i",&Nmultas);
                    fgets(fechai,20,archivo);
                    fgets(tipo,20,archivo);
                    fgets(tomar,20,archivo); sscanf(tomar,"%i",&monto);
                    fgets(pagado,20,archivo);
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
    int op = -1, modif, elim, buscarpersona, monto, Nmultas, borrar,consul;
    int opC = -1;
    char nombreC[20],apellidoC[20];
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
            if(agregarP(&p)== 0){
                break;
            } else{
                guardardatos(p);
            }
            break;

            case 2:
            fflush(stdin);
            printf("introduzca la cedula de la persona: ");
            scanf("%i",&buscarpersona);
            system("cls");
            modif = modificarpersona(&p,buscarpersona);
            if(modif == 0){
                system("cls");
                printf("no se pudo encontrar a la persona\n");
                getch();
            } else{
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
                printf("2. nombre y apellido\n");
                printf("0. salir\n\n");
                printf("introduzca una opcion: ");
                scanf("%i",&opC);
                system("cls");
                switch(opC){
                    case 1:
                    printf("introduzca la cedula de la persona: ");
                    scanf("%i",&buscarpersona);
                    consul = consultarpersonaC(&p,buscarpersona);
                    if(consul == 0){
                        system("cls");
                        printf("no se pudo encontrar a la persona\n");
                        getch();
                    }
                    system("cls");
                    break;
                    case 2:
                    fflush(stdin);
                    do{
                    printf("introduzca el nombre de la persona: ");
                    fgets(nombreC,20,stdin);
                    printf("introduzca el apellido de la persona: ");
                    fgets(apellidoC,20,stdin);
                    }while(filtroCNA==0);
                    consul = consultarpersonaN(&p,nombreC,apellidoC);
                    if(consul == 0){
                        system("cls");
                        printf("no se pudo encontrar a la persona\n");
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
            scanf("%i",&borrar);
            elim = eliminarP(&p,borrar);
            if(elim == 0){
                system("cls");
                printf("no se pudo encontrar a la persona\n");
                getch();
            } else {
                guardardatos(p);
            }
            system("cls");
            break;

            case 5:
            imprimirTodo(p);
            getch();
            system("cls");
            case 0:
            break;
        }
    }
    return 0;
}