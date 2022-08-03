#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

FILE *archivo;

struct fecha {
    int dia;
    int mes;
    int year;
};

struct persona {
    int cedula;
    char nombre[20];
    char apellido[20];
    struct fecha fecha;
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
    char hola[20];
    vehiculo *prox;
    struct infraccion *infraccion;
};

struct infraccion {
    int cantidad;
    struct fecha fecha;
    char tipo[20];
    int monto;
    char pagado[20];
    infraccion *prox;
};

//funciones extras

int validar_numero_naturales(char numero[]){
    int i;
        for(i=0; i<strlen(numero); i++)
        {
            if(!(isdigit(numero[i]))){

                system("cls");
                printf("\n\nSolo puede ingresar numeros positivos\n\n");
                getch();
                system("cls");
                return 0;
            }
        }
        return 1;
}

int validar_numero_fecha(char numero[]){
    int i;
        for(i=0; i<strlen(numero); i++)
        {
            if(!(isdigit(numero[i]))){
                printf("\n\nSolo puede ingresar numeros positivos\n\n");
                getch();
                return 0;
            }
        }
        return 1;
}

int contarpersona(struct persona *p){
    int cont = 0;
	for(;p; p = p->prox){
        cont++;
    }
	return cont;
}

int contarinfraccion(struct infraccion *p){
    int cont = 0;
    for(;p; p = p->prox){
        cont++;
    }
    return cont;

}

int contarvehiculo(struct vehiculo *p){
    int cont = 0;
	for(;p; p = p->prox){
        cont++;
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
        printf("cedula-> %i\n", p->cedula);
        printf("nombre-> %s", p->nombre);
        printf("apellido->%s",p->apellido);
        printf("fecha de nacimiento-> %i/%i/%i\n",p->fecha.dia,p->fecha.mes,p->fecha.year);
        printf("ciudad de nacimiento-> %s",p->ciudad);
        printf("direccion-> %s\n", p->direccion);
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
                printf("\t\t----multa %i----\n\n", in->cantidad);
                printf("\t\tfecha-> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
                printf("\t\ttipo ->%s", in->tipo);
                printf("\t\tmonto ->%i\n", in->monto);
                printf("\t\tpagado ->%s\n", in->pagado);
            }
            y++;
        }
        x--;
	}
}

//funciones para agregar a la lista

void agregarpersona(struct persona **p,int cedula, char nombre[20], char apellido[20], int year, int mes, int dia,char ciudad_nacimiento[20], char direccion[20]){
    struct persona *aux;
    aux = new struct persona;
    aux->cedula = cedula;
    strcpy(aux->nombre,nombre);
    strcpy(aux->apellido,apellido);
    aux->fecha.year = year;
    aux->fecha.mes = mes;
    aux->fecha.dia = dia;
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

void agregarinfraccion(struct infraccion **p,int Nmultas, int year, int mes, int dia, char tipo_multa[50], int monto, char pagado[20]){
    struct infraccion *aux;
    aux = new struct infraccion;
    aux->cantidad = Nmultas;
    aux->fecha.year = year;
    aux->fecha.mes = mes;
    aux->fecha.dia = dia;
    strcpy(aux->tipo,tipo_multa);
    aux->monto = monto;
    strcpy(aux->pagado,pagado);
    aux->prox = *p;
    *p = aux;
}

//funcion para el guardado y carga de archivos

void cargardatos(struct persona **p){
    int i,y,z,cedula,Nmultas,monto,yearP,mesP,diaP,yearM,mesM,diaM, cantidadpersona = 0, cantidadvehiculos = 0,cantidadmultas = 0;
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
            fgets(tomar,20,archivo); sscanf(tomar,"%i",&yearP);
            fgets(tomar,20,archivo); sscanf(tomar,"%i",&mesP);
            fgets(tomar,20,archivo); sscanf(tomar,"%i",&diaP);
            fgets(ciudad_nacimiento,20,archivo);
            fgets(direccion,20,archivo);
            agregarpersona(p,cedula,nombre,apellido,yearP,mesP,diaP,ciudad_nacimiento,direccion);
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
                    fgets(tomar,20,archivo); sscanf(tomar,"%i",&yearM);
                    fgets(tomar,20,archivo); sscanf(tomar,"%i",&mesM);
                    fgets(tomar,20,archivo); sscanf(tomar,"%i",&diaM);
                    fgets(tipo,20,archivo);
                    fgets(tomar,20,archivo); sscanf(tomar,"%i",&monto);
                    fgets(pagado,20,archivo);
                    agregarinfraccion(&(*p)->vehiculo->infraccion,Nmultas,yearM,mesM,diaM,tipo,monto,pagado);
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
        fprintf(archivo,"%i\n", p->fecha.year);
        fprintf(archivo,"%i\n", p->fecha.mes);
        fprintf(archivo,"%i\n", p->fecha.dia);
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
                fprintf(archivo,"%i\n",in->fecha.year);
                fprintf(archivo,"%i\n",in->fecha.mes);
                fprintf(archivo,"%i\n",in->fecha.dia);
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

//funciones relacionada con el apartado personas

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

int filtroF(int year, int mes, int dia){
    if(dia == 0){
        printf("\n\nel cero no es valido en la creacion de la fecha\n\n");
        getch();
        return 0;
    } 
    else if(mes == 0){
        printf("\n\nel cero no es valido en la creacion de la fecha\n\n");
        getch();
        return 0;
    }
    else if(year == 0){
        printf("\n\nel cero no es valido en la creacion de la fecha\n\n");
        getch();
        return 0;
    }
    else{
            if(year >1920 && year <=2020){
            if(mes > 0 && mes <13){
                if(mes = 1 && dia <=31){
                    return 1;
                }
                else if(mes = 2 && dia <28){
                    return 1;
                }
                else if(mes = 3 && dia <31){
                    return 1;
                }
                else if(mes = 4 && dia <30){
                    return 1;
                }
                else if(mes = 5 && dia <31){
                    return 1;
                }
                else if(mes = 6 && dia <30){
                    return 1;
                }
                else if(mes = 7 && dia <31){
                    return 1;
                }
                else if(mes = 8 && dia <31){
                    return 1;
                }
                else if(mes = 9 && dia <30){
                    return 1;
                }
                else if(mes = 10 && dia <31){
                    return 1;
                }
                else if(mes = 11 && dia <30){
                    return 1;
                }
                else if(mes = 12 && dia <=31){
                    return 1;
                }
                else{
                    printf("\n\nfecha invalida, debe corresponder a su respectivo mes\n\n");
                    getch();
                    return 0;
                }

            } else {
                printf("\n\nmes invalidado, debe ser entre 1 y 12\n\n");
                getch();
                return 0;
            }
        } else {
            printf("\n\nyear invalido, la persona tuvo que haber nacido entre 1921 y 2020 para entrar en el sistema\n\n");
            getch();
            return 0;
        }
    }
    

}

int agregarP(struct persona **p){
    int bandera, bandera1, bandera2, bandera3, validarcedula, validaryear, validarmes, validardia;
    char cedula[20], year[20], mes[20], dia[20];
    char nombre[20],apellido[20], fecha[20], ciudad_nacimiento[20], direccion[40];
    do{
        do{
        system("cls");
        printf("introduzca la cedula (0 para salir): ");
        scanf("%s",&cedula);
        bandera = validar_numero_naturales(cedula);
        }while (bandera == 0);

        validarcedula = atoi(cedula);

    } while(filtroP(p,validarcedula)==0);

    if(validarcedula == 0){
        system("cls");
        return 0;
    }
    fflush(stdin);
    do{
    printf("\nintroduzca su nombre: ");
    fgets(nombre,20,stdin);
    printf("\nintroduzca su apellido: ");
    fgets(apellido,20,stdin);
    } while (filtroCNA(nombre,apellido) == 0);
    do{
        do{
        printf("\nintroduzca su fecha de nacimiento\n\n");
        printf("year: ");
        scanf("%s",&year);
        } while(validar_numero_fecha(year)==0);
        do{
        printf("mes: ");
        scanf("%s",&mes);
        } while(validar_numero_fecha(mes)==0);
        do{
        printf("dia: ");
        scanf("%s",&dia);
        } while(validar_numero_fecha(dia)==0);

    validaryear = atoi(year);
    validarmes = atoi(mes);
    validardia = atoi(dia);

    }while(filtroF(validaryear,validarmes,validardia) == 0);
    
    fflush(stdin);
    printf("\nintroduzca su ciudad de nacimiento: ");
    fgets(ciudad_nacimiento,20,stdin);

    do{
    printf("\nintroduzca su direccion: ");
    fgets(direccion,40,stdin);
    }while(filtroD(direccion) == 0);

    agregarpersona(p,validarcedula,nombre,apellido,validaryear,validarmes,validardia,ciudad_nacimiento,direccion);

    return 1;
}

int modificarpersona(struct persona **p,int buscar){
    int op = -1, bandera1, bandera2, bandera3;
    char year[20], mes[20], dia[20];
    struct persona *aux;
    aux = *p;
    while(aux!=NULL){
        if(aux->cedula == buscar){
            while(op != 0){
                printf("----DATOS DE LA PERSONA----\n\n");
                printf("nombre-> %s",aux->nombre);
                printf("apellido-> %s",aux->apellido);
                printf("fecha de nacimiento-> %i/%i/%i\n",aux->fecha.dia,aux->fecha.mes,aux->fecha.year);
                printf("ciudad de nacimiento-> %s",aux->ciudad);
                printf("direccion-> %s",aux->direccion);
                printf("\n\nque dato desea modificar?\n\n");
                printf("1. nombre y apellido\n");
                printf("2. fecha de nacimiento\n");
                printf("3. ciudad de nacimiento\n");
                printf("4. direccion\n");
                printf("0. salir para guardar\n\n");
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
                    do{
                        do{
                        printf("introduzca su fecha de nacimiento\n\n");
                        printf("year: ");
                        scanf("%s",&year);
                        printf("mes: ");
                        scanf("%s",&mes);
                        printf("dia: ");
                        scanf("%s",&dia);
                        bandera1 = validar_numero_naturales(year);
                        bandera2 = validar_numero_naturales(mes);
                        bandera3 = validar_numero_naturales(dia);
                        }while(bandera1 == 0 || bandera2 == 0 || bandera3 == 0);

                    aux->fecha.year = atoi(year);
                    aux->fecha.mes = atoi(mes);
                    aux->fecha.dia = atoi(dia);

                    }while(filtroF(aux->fecha.year,aux->fecha.mes,aux->fecha.dia) == 0);
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
        if(strcmpi(aux->nombre,nombre)==0 && strcmpi(aux->apellido,apellido)==0){
            system("cls");
            printf("----DATOS DE LA PERSONA----\n\n");
            printf("cedula-> %i\n",aux->cedula);
            printf("nombre-> %s",aux->nombre);
            printf("apellido-> %s",aux->apellido);
            printf("fecha de nacimiento-> %i/%i/%i\n",aux->fecha.dia,aux->fecha.mes,aux->fecha.year);
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
            printf("fecha de nacimiento-> %i/%i/%i\n",aux->fecha.dia,aux->fecha.mes,aux->fecha.year);
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

//funciones relacionado con el apartado vehiculo

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
            printf("\nsmarca ->%s", v->marca);
            printf("\ncolor ->%s", v->color);
            printf("\nmodelo ->%s", v->modelo);
            printf("\nyear ->%s", v->year);
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

//funciones relacionada con el apartado multas

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
    if((strcmpi(pagado,"si\n")!=0) && (strcmpi(pagado,"no\n")!=0)){
        printf("\n\n solo puede colocar si o no\n\n");
        getch();
        return 0;
    }
    return 1;
}

int agregarM(struct persona *p,int buscar, char placa[20]){
    int cantidadmultas, i, t, validaryear, validarmes, validardia;
    int Nmultas, validarmonto;
    char fechai[20], tipo[20], pagado[20], dia[20], mes[20], year[20], monto[20]; 
    struct persona *aux = p;
    while(aux != NULL){
        if(aux->cedula == buscar){
            struct vehiculo *v = aux->vehiculo;
            while(v != NULL){
                if(strcmpi(v->placa,placa) == 0){
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
                        do{
                            do{
                            printf("\nintroduzca la fecha de la multa\n\n");
                            printf("year: ");
                            scanf("%s",&year);
                            } while(validar_numero_fecha(year)==0);
                            do{
                            printf("mes: ");
                            scanf("%s",&mes);
                            } while(validar_numero_fecha(mes)==0);
                            do{
                            printf("dia: ");
                            scanf("%s",&dia);
                            } while(validar_numero_fecha(dia)==0);

                        validaryear = atoi(year);
                        validarmes = atoi(mes);
                        validardia = atoi(dia);

                        }while(filtroF(validaryear,validarmes,validardia) == 0);
                        fflush(stdin);
                        printf("\n\ntipo: ");
                        fgets(tipo,20,stdin);
                        do{
                        printf("\nmonto: ");
                        scanf("%s",&monto);
                        fflush(stdin);
                        } while(validar_numero_naturales(monto)==0);

                        validarmonto = atoi(monto);

                        do{
                        printf("\npagado: ");
                        fgets(pagado,4,stdin);
                        } while(filtroPagar(pagado)==0);
                        agregarinfraccion(&v->infraccion, Nmultas,validaryear,validarmes,validardia,tipo,validarmonto,pagado);
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
                        if(strcmpi(in->pagado,"no\n")==0){
                            printf("----MULTA %i----\n\n",in->cantidad);
                            printf("fecha-> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
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
                    printf("fecha-> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
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

//funciones de la consulta

int consultaName (struct persona *p, char nombre[20]){
    struct persona *aux;
    int i = 1, entra = 0;
    aux = p;
    system("cls");
    printf("\tlistado con nombre %s\n",nombre);
    while(aux != NULL){
        if(strcmpi(aux->nombre,nombre)==0){
            entra = 1;
            printf("----persona %i----\n\n",i);
            printf("cedula -> %i\n",aux->cedula);
            printf("nombre -> %s",aux->nombre);
            printf("apellido -> %s",aux->apellido);
            printf("fecha -> %i/%i/%i",aux->fecha.dia,aux->fecha.mes,aux->fecha.year);
            printf("ciudad de nacimiento -> %s",aux->ciudad);
            printf("dirreccion -> %s",aux->direccion);
            i++;
            printf("\n");
        }
        aux = aux->prox;
    }
    if(entra == 1){
        getch();
        return 1;
    } else{
        return 0;
    }
}

void ordenarmulta(struct infraccion **in){
    int cantidad, monto, year, mes, dia;
    char fecha[20], tipo[20], pagado[20];
    struct infraccion *aux, *inicio;
    aux = *in;
    while(aux != NULL){
        struct infraccion *u;
        u = aux;
        while(u != NULL){
            if(aux->cantidad>u->cantidad){
            cantidad = aux->cantidad;
            aux->cantidad = u->cantidad;
            u->cantidad = cantidad;
            year = aux->fecha.year;
            aux->fecha.year = u->fecha.year;
            u->fecha.year = year;
            mes = aux->fecha.mes;
            aux->fecha.mes = u->fecha.mes;
            u->fecha.mes = mes;
            dia = aux->fecha.dia;
            aux->fecha.dia = u->fecha.dia;
            u->fecha.dia = dia;
            strcpy(tipo,aux->tipo);
            strcpy(aux->tipo,u->tipo);
            strcpy(u->tipo,tipo);
            monto = aux->monto;
            aux->monto = u->monto;
            u->monto = monto;
            strcpy(pagado,aux->pagado);
            strcpy(aux->pagado,u->pagado);
            strcpy(u->pagado,pagado);
            }
            u = u->prox;
        }
        aux = aux->prox;
    }

}

int consultarplaca(struct persona *p,char placa[20]){
    struct persona *aux;
    struct vehiculo *v;
    int entra = 0, no = 0, si = 0, i = 1;
    aux = p;
    system("cls");
    while(aux != NULL){
        v = aux->vehiculo;
        while(v != NULL){
                if(strcmpi(v->placa,placa)==0){
                struct infraccion *in;
                in = v->infraccion;
                printf("multas de la placa %s\n",placa);
                ordenarmulta(&in);
                while(in != NULL){
                    printf("----multa %i----\n\n",in->cantidad);
                    printf("fecha-> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
                    printf("tipo -> %s",in->tipo);
                    printf("monto -> %i\n",in->monto);
                    printf("pagado -> %s",in->pagado);
                    printf("\n");
                    if(strcmp(in->pagado,"no\n")==0){
                        no++;
                    } else {
                        si++;
                    }
                    in = in->prox;
                }
                printf("cantidad de multas pagadas %i\n\n",si);
                printf("cantidad de multas no pagadas %i\n\n",no);
                getch();
                return 1;

            }
            v = v->prox;
        }
        aux = aux->prox;
    }
    return 0;
}

//preguntas de la opcion 2.2.2

int mostrar2221(struct persona *p,int cedula){
    struct persona *aux;
    int i = 1, o = 1, x = 0, y = 0;
    aux = p;
    system("cls");
    while(aux != NULL){
        if(aux->cedula == cedula){
            printf("----detalles personales del titular----\n\n");
            printf("cedula -> %i\n",aux->cedula);
            printf("nombre -> %s",aux->nombre);
            printf("apellido -> %s",aux->apellido);
            printf("fecha -> %i/%i/%i\n",aux->fecha.dia,aux->fecha.mes,aux->fecha.year);
            printf("ciudad de nacimiento -> %s",aux->ciudad);
            printf("dirreccion -> %s",aux->direccion);
            printf("\ndetalles de vehiculos y multas del titular\n\n");
            for(struct vehiculo *v = aux->vehiculo;v;v = v->prox){
                printf("\t----vehiculo %i----\n\n",i);
                printf("\tplaca -> %s",v->placa);
                printf("\tmarca -> %s",v->marca);
                printf("\tcolor -> %s",v->color);
                printf("\tmodelo -> %s",v->modelo);
                printf("\tyear -> %s\n",v->year);
                x++;
                for(struct infraccion *in = v->infraccion;in;in = in->prox){
                    printf("\t\t----multa %i----\n\n",in->cantidad);
                    printf("\t\tfecha -> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
                    printf("\t\ttipo -> %s", in->tipo);
                    printf("\t\tmonto -> %i\n",in->monto);
                    printf("\t\tpagado -> %s\n",in->pagado);
                    y++;
                }
                i++;
            }
            printf("\n\ntotal de vehiculos: %i\n",x);
            printf("total de multas que posee: %i\n\n",y);
            system("pause");
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

int mostrar2222(struct persona *p,int cedula){
    struct persona *aux;
    int i = 1, o = 1, x = 0, y = 0;
    aux = p;
    system("cls");
    while(aux != NULL){
        if(aux->cedula == cedula){
            printf("----detalles personales del titular----\n\n");
            printf("cedula -> %i\n",aux->cedula);
            printf("nombre -> %s",aux->nombre);
            printf("apellido -> %s",aux->apellido);
            printf("\ndetalles de sus vehiculos\n\n");
            for(struct vehiculo *v = aux->vehiculo;v;v = v->prox){
                printf("\t----vehiculo %i----\n\n",i);
                printf("\tplaca -> %s",v->placa);
                printf("\tmarca -> %s",v->marca);
                printf("\tcolor -> %s",v->color);
                printf("\tmodelo -> %s",v->modelo);
                printf("\tyear -> %s\n",v->year);
                y = 0; x = 0;
                for(struct infraccion *in = v->infraccion;in;in = in->prox){
                    if(strcmp(in->pagado,"no\n")==0){
                        y++;
                    } else{
                        x++;
                    }
                
                }
                printf("\ntotal de multas pagadas del vehiculo %i: %i\n",i,x);
                printf("total de multas no pagadas del vehiculo %i: %i\n\n",i,y);
                i++;
            }
            system("pause");
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void ordenarplaca(struct vehiculo **v){
    struct vehiculo *aux, *u;
    struct infraccion *l;
    aux = *v;
    char placa[20],marca[20],color[20],modelo[20],year[20];
    while(aux != NULL){
        u = aux;
        while(u != NULL){
            if(strcmp(aux->placa,u->placa)>0){
                strcpy(placa,aux->placa);
                strcpy(aux->placa,u->placa);
                strcpy(u->placa,placa);
                strcpy(marca,aux->marca);
                strcpy(aux->marca,u->marca);
                strcpy(u->marca,marca);
                strcpy(color,aux->color);
                strcpy(aux->color,u->color);
                strcpy(u->color,color);
                strcpy(modelo,aux->modelo);
                strcpy(aux->modelo,u->modelo);
                strcpy(u->modelo,modelo);
                strcpy(year,aux->year);
                strcpy(aux->year,u->year);
                strcpy(u->year,year);
                l = aux->infraccion;
                aux->infraccion = u->infraccion;
                u->infraccion = l;
            }
            u = u->prox;
        }
        aux = aux->prox;
    }
}

int mostrar2223(struct persona *p, int cedula){
    struct persona *aux;
    int i = 1, o = 1, y = 0;
    aux = p;
    system("cls");
    while(aux != NULL){
        if(aux->cedula == cedula){
            ordenarplaca(&aux->vehiculo);
            for(struct vehiculo *v = aux->vehiculo;v;v = v->prox){
                printf("multas de la placa %s\n",v->placa);
                for(struct infraccion *in = v->infraccion;in;in = in->prox){
                    if(strcmp(in->pagado,"no\n")==0){
                    printf("\t----multa %i----\n\n",in->cantidad);
                    printf("\tfecha -> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
                    printf("\ttipo -> %s", in->tipo);
                    printf("\tmonto -> %i\n",in->monto);
                    printf("\tpagado -> %s\n",in->pagado);
                    y = y + in->monto;
                    }
                }
                i++;
            }
            printf("total que adeuda el titular: %i\n\n",y);
            system("pause");
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void ordenarfecha(struct infraccion **in){
    struct infraccion *aux, *u;
    int year=0, mes=0, dia=0, monto, cantidad;
    char tipo[20], pagado[20];
    aux = *in;
    while(aux != NULL){
        u = aux;
        while(u != NULL){
            if(aux->fecha.year > u->fecha.year){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                }
                else if((aux->fecha.year == u->fecha.year) && (aux->fecha.mes > u->fecha.mes)){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                } 
                else if((aux->fecha.year == u->fecha.year) && (aux->fecha.mes == u->fecha.mes) && (aux->fecha.dia > u->fecha.dia)){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                }
            u = u->prox;
        }
        aux = aux->prox;
    }

}

void ordenarfechaypago(struct infraccion **in){
    struct infraccion *aux, *u;
    int year=0, mes=0, dia=0, monto, cantidad;
    char tipo[20], pagado[20];
    aux = *in;
    while(aux != NULL){
        u = aux;
        while(u != NULL){
            if(strcmpi(u->pagado,"no\n")==0 && strcmpi(aux->pagado,"si\n")==0){
                cantidad = aux->cantidad;
                aux->cantidad = u->cantidad;
                u->cantidad = cantidad;
                year = aux->fecha.year;
                aux->fecha.year = u->fecha.year;
                u->fecha.year = year;
                mes = aux->fecha.mes;
                aux->fecha.mes = u->fecha.mes;
                u->fecha.mes = mes;
                dia = aux->fecha.dia;
                aux->fecha.dia = u->fecha.dia;
                u->fecha.dia = dia;
                fflush(stdin);
                strcpy(tipo,aux->tipo);
                strcpy(aux->tipo,u->tipo);
                strcpy(u->tipo,tipo);
                monto = aux->monto;
                aux->monto = u->monto;
                u->monto = monto;
                fflush(stdin);
                strcpy(pagado,aux->pagado);
                strcpy(aux->pagado,u->pagado);
                strcpy(u->pagado,pagado);
                }
            else if(strcmpi(aux->pagado,"no\n")==0 && strcmpi(u->pagado,"no\n")==0){
                    if(aux->fecha.year > u->fecha.year){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                }
                else if((aux->fecha.year == u->fecha.year) && (aux->fecha.mes > u->fecha.mes)){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                } 
                else if((aux->fecha.year == u->fecha.year) && (aux->fecha.mes == u->fecha.mes) && (aux->fecha.dia > u->fecha.dia)){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                }
            }
            else if(strcmpi(aux->pagado,"si\n")==0 && strcmpi(u->pagado,"si\n")==0){
                if(aux->fecha.year > u->fecha.year){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                }
                else if((aux->fecha.year == u->fecha.year) && (aux->fecha.mes > u->fecha.mes)){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                } 
                else if((aux->fecha.year == u->fecha.year) && (aux->fecha.mes == u->fecha.mes) && (aux->fecha.dia > u->fecha.dia)){
                    cantidad = aux->cantidad;
                    aux->cantidad = u->cantidad;
                    u->cantidad = cantidad;
                    year = aux->fecha.year;
                    aux->fecha.year = u->fecha.year;
                    u->fecha.year = year;
                    mes = aux->fecha.mes;
                    aux->fecha.mes = u->fecha.mes;
                    u->fecha.mes = mes;
                    dia = aux->fecha.dia;
                    aux->fecha.dia = u->fecha.dia;
                    u->fecha.dia = dia;
                    fflush(stdin);
                    strcpy(tipo,aux->tipo);
                    strcpy(aux->tipo,u->tipo);
                    strcpy(u->tipo,tipo);
                    monto = aux->monto;
                    aux->monto = u->monto;
                    u->monto = monto;
                    fflush(stdin);
                    strcpy(pagado,aux->pagado);
                    strcpy(aux->pagado,u->pagado);
                    strcpy(u->pagado,pagado);
                }
            }
            u = u->prox;
        }
        aux = aux->prox;
    }

}

int mostrar2224(struct persona *p, int cedula, char Nplaca[20]){
    struct persona *aux;
    struct vehiculo *v;
    struct infraccion *in;
    aux = p;
    system("cls");
    while(aux != NULL){
        if(aux->cedula == cedula){
            v = aux->vehiculo;
            while(v != NULL){
                if(strcmpi(v->placa,Nplaca)==0){
                    in = v->infraccion;
                    if(in == NULL){
                        system("cls");
                        printf("no hay multas que mostrar");
                        getch();
                        return 1;
                    }
                    ordenarfechaypago(&in);
                    while(in != NULL){
                
                    printf("----multa %i----\n\n",in->cantidad);
                    printf("fecha -> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
                    printf("tipo -> %s", in->tipo);
                    printf("monto -> %i\n",in->monto);
                    printf("pagado -> %s\n",in->pagado);

                    in = in->prox;
                    }
                    getch();
                    return 1;
                }
                v = v->prox;
            }
            return -1;
        }
        aux = aux->prox;
    }
    return 0;
}

int mostrar2225(struct persona *p, int cedula, char infraccion[20]){
    struct persona *aux;
    struct vehiculo *v;
    struct infraccion *in;
    int i, entra = 0, nunca = 0;
    aux = p;
    system("cls");
    while(aux != NULL){
        if(aux->cedula == cedula){
            v = aux->vehiculo;
            while(v != NULL){
                entra = 0;
                in = v->infraccion;
                ordenarfecha(&in);
                while(in != NULL){
                    if(strcmpi(in->tipo,infraccion)==0){
                    entra = 1;
                    nunca = 1;
                    printf("----multa %i----\n\n",in->cantidad);
                    printf("fecha -> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
                    printf("tipo -> %s", in->tipo);
                    printf("monto -> %i\n",in->monto);
                    printf("pagado -> %s\n",in->pagado);
                    }
                    in = in->prox;
                }
                if(entra == 1){
                    printf("\testas infraccion le pertenece al vehiculo con estos detalles: \n\n");
                    printf("\tplaca -> %s",v->placa);
                    printf("\tmarca -> %s",v->marca);
                    printf("\tcolor -> %s",v->color);
                    printf("\tmodelo -> %s",v->modelo);
                    printf("\tyear -> %s\n",v->year);
                } else if(entra == 0 && nunca == 1) {
                    printf("Este tipo de infraccion no se encuentra en este vehiculo: \n\n");
                    printf("\tplaca -> %s",v->placa);
                    printf("\tmarca -> %s",v->marca);
                    printf("\tcolor -> %s",v->color);
                    printf("\tmodelo -> %s",v->modelo);
                    printf("\tyear -> %s\n",v->year);
                }
                v = v->prox;
            }
            if(nunca == 0){
                return -1;
            }
            getch();
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void ordenarcedulaD(struct persona **p){
    struct persona *aux, *u;
    struct vehiculo *v;
    char nombre[20], apellido[20], ciudad[20], direccion[20];
    int cedula, year, mes, dia;
    aux = *p;

    while(aux != NULL){
        u = aux;

        while( u != NULL){
            if(aux->cedula < u->cedula){
                cedula = aux->cedula;
                aux->cedula = u->cedula;
                u->cedula = cedula;
                strcpy(nombre,aux->nombre);
                strcpy(aux->nombre,u->nombre);
                strcpy(u->nombre,nombre);
                strcpy(apellido,aux->apellido);
                strcpy(aux->apellido,u->apellido);
                strcpy(u->apellido,apellido);
                year = aux->fecha.year;
                aux->fecha.year = u->fecha.year;
                u->fecha.year = year;
                mes = aux->fecha.mes;
                aux->fecha.mes = u->fecha.mes;
                u->fecha.mes = mes;
                dia = aux->fecha.dia;
                aux->fecha.dia = u->fecha.dia;
                u->fecha.dia = dia;
                strcpy(ciudad,aux->ciudad);
                strcpy(aux->ciudad,u->ciudad);
                strcpy(u->ciudad,ciudad);
                strcpy(direccion,aux->direccion);
                strcpy(aux->direccion,u->direccion);
                strcpy(u->direccion,direccion);
                v = aux->vehiculo;
                aux->vehiculo = u->vehiculo;
                u->vehiculo = v;
            }

            u = u->prox;
        }

        aux = aux->prox;
    }
}

void ordenarcedulaA(struct persona **p){
    struct persona *aux, *u;
    struct vehiculo *v;
    char nombre[20], apellido[20], ciudad[20], direccion[20];
    int cedula, year, mes, dia;
    aux = *p;

    while(aux != NULL){
        u = aux;

        while( u != NULL){
            if(aux->cedula > u->cedula){
                cedula = aux->cedula;
                aux->cedula = u->cedula;
                u->cedula = cedula;
                strcpy(nombre,aux->nombre);
                strcpy(aux->nombre,u->nombre);
                strcpy(u->nombre,nombre);
                strcpy(apellido,aux->apellido);
                strcpy(aux->apellido,u->apellido);
                strcpy(u->apellido,apellido);
                year = aux->fecha.year;
                aux->fecha.year = u->fecha.year;
                u->fecha.year = year;
                mes = aux->fecha.mes;
                aux->fecha.mes = u->fecha.mes;
                u->fecha.mes = mes;
                dia = aux->fecha.dia;
                aux->fecha.dia = u->fecha.dia;
                u->fecha.dia = dia;
                strcpy(ciudad,aux->ciudad);
                strcpy(aux->ciudad,u->ciudad);
                strcpy(u->ciudad,ciudad);
                strcpy(direccion,aux->direccion);
                strcpy(aux->direccion,u->direccion);
                strcpy(u->direccion,direccion);
                v = aux->vehiculo;
                aux->vehiculo = u->vehiculo;
                u->vehiculo = v;
            }

            u = u->prox;
        }

        aux = aux->prox;
    }
}

int mostrar2241(struct persona *p, char infraccion[20], int minimo, int maximo){
    struct persona *aux;
    struct vehiculo *v;
    struct infraccion *in;
    aux = p;
    int x = 0, entra;
    system("cls");
    printf("----MULTAS NO PAGADAS----\n\n");
    ordenarcedulaD(&p);
    while(aux != NULL){
        printf("---DATOS DEL TITULAR----\n\n");
        printf("cedua -> %i\n",aux->cedula);
        printf("nombre -> %s",aux->nombre);
        printf("apellido -> %s\n",aux->apellido);
        x = 0;
        entra = 0;
        v = aux->vehiculo;
        while(v != NULL){
            printf("\t----DATOS DEL VEHICULO----\n\n");
            printf("\tplaca -> %s", v->placa);
            printf("\tmarca -> %s", v->marca);
            printf("\tyear -> %s\n",v->year);
            x = 0;
            in = v->infraccion;
            while(in != NULL){
                if(strcmp(in->tipo,infraccion)==0 && strcmpi(in->pagado,"no\n")==0 && in->fecha.year >= minimo && in->fecha.year <= maximo){
                    entra = 1;
                    printf("\t\t----MULTA %i----\n\n",in->cantidad);
                    printf("\t\tfecha -> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
                    printf("\t\tmonto -> %i\n",in->monto);
                    printf("\t\tpagado -> %s\n",in->pagado);
                    x = x + in->monto;
                }
                in = in->prox;
            }
            v = v->prox;
        }
        if(entra == 0){
            printf("este titular no posee multas\n\n");
        } else{
            printf("total del monto por pagar: %i\n\n",x);
        }
        aux = aux->prox;
    }
    if(p == NULL){
        return 0;
    }
    getch();
    return 1;
}

int mostrar2242(struct persona *p, char infraccion[20], int minimo, int maximo){
    struct persona *aux;
    struct vehiculo *v;
    struct infraccion *in;
    aux = p;
    int x = 0, entra = 0;
    system("cls");
    ordenarcedulaA(&p);
    printf("----MULTAS YA PAGADAS----\n\n");
    while(aux != NULL){
        printf("---DATOS DEL TITULAR----\n\n");
        printf("cedua -> %i\n",aux->cedula);
        printf("nombre -> %s",aux->nombre);
        printf("apellido -> %s\n",aux->apellido);
        x = 0;
        entra = 0;
        v = aux->vehiculo;
        while(v != NULL){
            printf("\t----DATOS DEL VEHICULO----\n\n");
            printf("\tplaca -> %s", v->placa);
            printf("\tmarca -> %s", v->marca);
            printf("\tyear -> %s\n",v->year);
            in = v->infraccion;
            while(in != NULL){
                if(strcmp(in->tipo,infraccion)==0 && strcmpi(in->pagado,"si\n")==0 && in->fecha.year >= minimo && in->fecha.year <= maximo){
                    entra = 1;
                    printf("\t\t----MULTA %i----\n\n",in->cantidad);
                    printf("\t\tfecha -> %i/%i/%i\n",in->fecha.dia,in->fecha.mes,in->fecha.year);
                    printf("\t\tmonto -> %i\n",in->monto);
                    printf("\t\tpagado -> %s\n",in->pagado);
                    x = x + in->monto;
                }
                in = in->prox;
            }
            v = v->prox;
        }
        if(entra == 0){
            printf("este titular no posee multas\n\n");
        } else{
            printf("total del monto pagado: %i\n\n",x);
        }
        aux = aux->prox;
    }
    if(p == NULL){
        return 0;
    }
    getch();
    return 1;
}

int filtrorango(int minimo, int maximo){
    if(maximo > minimo + 2 || maximo < minimo){
        printf("\n\nsolo puedes colocar un rango maximo de 2 years\n\n");
        getch();
        return 0;
    }
    return 1;
}

int main(){ 
    persona *p = NULL;
    char op[10], op1[10], op2[10], op3[10];
    int bandera = 0, opvalido = -1, op1valido = -1, op2valido = -1, op3valido = -1;
    int modif, cedula, elim, buscarpersona, monto, Nmultas, borrar, consul, rangominimo, rangomaximo;;
    int opC = -1, vehiculoA, multaA, Nmulta, pregunta2221, pregunta2222, pregunta2223, pregunta2224, pregunta2225;
    char Nplaca[20],placaP[20], nombreC[20], apellidoC[20],name[20], infraccion[20];
    cargardatos(&p);
    system("cls");
    while(opvalido != 0){
        system("cls");
        op1valido = -1;
        do{
        printf("----SISTEMA DE CONTROL DE MULTAS----\n\n");
        printf("1. Mantenimineto\n");
        printf("2. Operaciones y consultas\n");
        printf("3. Base de datos\n");
        printf("0. Salir del programa\n\n");
        printf("introduzca una opcion: ");
        scanf("%s",&op);
        bandera=validar_numero_naturales(op);
        } while(bandera==0);

        opvalido = atoi(op);

        if(opvalido>3){
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
                            opC = -1;
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
                                }
                            }

                        }

                        case 2:
                        while(op2valido != 0){
                            opC = -1;
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
                                    printf("el numero de multa asociado a %ses incorrecto\n",Nplaca);
                                    getch();
                                }
                                else if(elim == 1) {
                                    guardardatos(p);
                                }
                                system("cls");
                                break;
                            }
                            }
                        }
                        break;
                        case 2:
                        while(op2valido != 0){
                            op3valido = -1;
                            system("cls");
                            do{
                            printf("----CONSULTAS----\n\n");
                            printf("1. Buscar nombre de la persona\n");
                            printf("2. Buscar datos con la cedula de la persona\n");
                            printf("3. Buscar una placa\n");
                            printf("4. Buscar por infracciones de hace 2 a�os\n");
                            printf("0. salir al menu anterior\n\n");
                            printf("introduzca una opcion: ");
                            scanf("%s",&op2);
                            fflush(stdin);
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
                                    printf("introduzca el nombre de la persona: ");
                                    fgets(name,20,stdin);
                                    if(consultaName(p,name) == 0){
                                        printf("No se ha encontrado la persona con el nombre %s\n",name);
                                        system("pause");
                                        system("cls");
                                    }
                                    break;

                                    case 2:
                                    while(op3valido != 0){
                                        system("cls");
                                        do{
                                        printf("----BUSCAR POR CEDULA----\n\n");
                                        printf("1. mostrar datos del titular y sus vehiculos, con el total de vehiculos y el total de multas que posee\n");
                                        printf("2. mostrar datos del titular y sus vehiculos con sus multas pagadas y no pagadas\n");
                                        printf("3. mostrar multas no pagadas por cada vehiculo que posee\n");
                                        printf("4. mostrar las multas separadas por pagadas y no pagadas, ordenadas por fechas\n");
                                        printf("5. mostrar datos de la multa por un tipo de infraccion, ordenada por su fecha\n");
                                        printf("0. regrasar al menu anterior\n\n");
                                        printf("introduzca una opcion: ");
                                        scanf("%s",&op3);
                                        } while(bandera == 0);

                                        op3valido = atoi(op3);

                                        if(op3valido == 0){
                                            break;
                                        }

                                        else if(op3valido > 5){
                                            printf("la opcion no corresponde al menu principal\n\n");
                                            system("pause");
                                        }

                                        else{
                                            system("cls");
                                            switch(op3valido){
                                                case 1:
                                                printf("introduzca la cedula: ");
                                                scanf("%i",&cedula);
                                                pregunta2221 = mostrar2221(p,cedula);
                                                if(pregunta2221 == 0){
                                                    system("cls");
                                                    printf("no se pudo encontrar a la persona con la cedula %i", cedula);
                                                    getch();
                                                    system("cls");
                                                }
                                                break;

                                                case 2:
                                                printf("introduzca la cedula: ");
                                                scanf("%i",&cedula);
                                                pregunta2222 = mostrar2222(p,cedula);
                                                if(pregunta2222 == 0){
                                                    system("cls");
                                                    printf("no se pudo encontrar a la persona con la cedula %i", cedula);
                                                    getch();
                                                    system("cls");
                                                }
                                                break;

                                                case 3:
                                                printf("introduzca la cedula: ");
                                                scanf("%i",&cedula);
                                                pregunta2223 = mostrar2223(p,cedula);
                                                if(pregunta2223 == 0){
                                                    system("cls");
                                                    printf("no se pudo encontrar a la persona con la cedula %i", cedula);
                                                    getch();
                                                    system("cls");
                                                }
                                                break;

                                                case 4:
                                                printf("introduzca la cedula: ");
                                                scanf("%i",&cedula);
                                                fflush(stdin);
                                                printf("introduzca la placa: ");
                                                fgets(Nplaca,20,stdin);
                                                pregunta2224 = mostrar2224(p,cedula,Nplaca);
                                                if(pregunta2224 == 0){
                                                    system("cls");
                                                    printf("no se pudo encontrar a la persona con la cedula %i", cedula);
                                                    getch();
                                                    system("cls");
                                                }
                                                else if(pregunta2224 == -1){
                                                    system("cls");
                                                    printf("no se pudo encontrar la placa %s",Nplaca);
                                                    getch();
                                                    system("cls");
                                                }
                                                break;

                                                case 5:
                                                printf("introduzca la cedula: ");
                                                scanf("%i",&cedula);
                                                fflush(stdin);
                                                printf("\nintroduzca el tipo de infraccion: ");
                                                fgets(infraccion,20,stdin);
                                                pregunta2225 = mostrar2225(p,cedula,infraccion);
                                                if(pregunta2225 == 0){
                                                    system("cls");
                                                    printf("no se pudo encontrar a la persona con la cedula %i", cedula);
                                                    getch();
                                                    system("cls");
                                                } else if(pregunta2225 == -1){
                                                    system("cls");
                                                    printf("no se pudo encontrar este tipo de infraccion con la cedula %i", cedula);
                                                    getch();
                                                    system("cls");
                                                }
                                                break;
                                            }


                                        }

                                    }
                                    break;

                                    case 3:
                                    int placa;
                                    printf("introduzca la placa: ");
                                    fgets(Nplaca,20,stdin);
                                    placa = consultarplaca(p,Nplaca);
                                    if(placa==0){
                                        system("cls");
                                        printf("No se pudo encontrar la placa");
                                        getch();
                                        system("cls");
                                    }
                                    else if(placa== -1){
                                        system("cls");
                                        printf("la placa no tiene multas asociadas\n");
                                        getch();
                                        system("cls");
                                    }
                                    break;

                                    case 4:
                                    while(op3valido != 0){
                                        system("cls");
                                        do{
                                        printf("----BUSCAR POR INFRACCION Y RANGO DE ANOS----\n\n");
                                        printf("1. mostrar multas de los titulares no pagadas\n");
                                        printf("2. mostrar multas de los titulares ya pagadas\n");
                                        printf("0. regrasar al menu anterior\n\n");
                                        printf("introduzca una opcion: ");
                                        scanf("%s",&op3);
                                        } while(bandera == 0);

                                        op3valido = atoi(op3);

                                        if(op3valido == 0){
                                            break;
                                        }

                                        else if(op3valido > 2){
                                            printf("la opcion no corresponde al menu principal\n\n");
                                            system("pause");
                                        }

                                        else{
                                            system("cls");
                                            switch(op3valido){
                                                case 1:
                                                int pregunta2241;
                                                fflush(stdin);
                                                printf("introduzca el tipo de infraccion: ");
                                                fgets(infraccion,20,stdin);
                                                printf("\nintroduzca el year minimo: ");
                                                scanf("%i", &rangominimo);
                                                do{
                                                printf("\nintroduzca el year maximo (solo hasta el %i): ",rangominimo + 2);
                                                scanf("%i",&rangomaximo);
                                                } while(filtrorango(rangominimo,rangomaximo) == 0);
                                                pregunta2241 = mostrar2241(p,infraccion,rangominimo,rangomaximo);
                                                if(pregunta2241 == 0){
                                                    system("cls");
                                                    printf("no se pudo encontrar la persona");
                                                    getch();
                                                    system("cls");
                                                }
                                                break;

                                                case 2:
                                                int pregunta2242;
                                                fflush(stdin);
                                                printf("introduzca el tipo de infraccion: ");
                                                fgets(infraccion,20,stdin);
                                                printf("\nintroduzca el year minimo(entero): ");
                                                scanf("%i", &rangominimo);
                                                do{
                                                printf("\nintroduzca el year maximo (solo hasta el %i): ",rangominimo + 2);
                                                scanf("%i",&rangomaximo);
                                                } while(filtrorango(rangominimo,rangomaximo) == 0);
                                                pregunta2242 = mostrar2242(p,infraccion,rangominimo,rangomaximo);
                                                if(pregunta2242 == 0){
                                                    system("cls");
                                                    printf("no se pudo encontrar la persona");
                                                    getch();
                                                    system("cls");
                                                }
                                                break;
                                            }

                                        }

                                    }
                                    break;
                                }

                            }
                        }
                        break;
                        }
                    }
                }
                break;

                case 3:
                imprimirTodo(p);
                getch();
                system("cls");
                break;
                
                case 0:
                guardardatos(p);
                system("cls");
                printf("\n\nGracias por usar nuestros servicios\n\n");
                system("pause");
                break;
            }
        }
    }
    return 0;
}