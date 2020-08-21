#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

FILE *archivo;

struct persona {
    int cedula;
    char nombre[20];
    char apellido[20];
    char fecha[20];
    char ciudad[20];
    char direccion[20];
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

void mostrar(struct persona *p){ /* muestra por pantalla la persona enlazada */
	system("cls");
	printf( "\n\nMostrar persona\n\n");	
	while (p){
		printf("cedula->%i\n", p->cedula);
        printf("nombre->%s", p->nombre);
        printf("fecha->%s", p->fecha);
        printf("ciudad de nacimiento->%s",p->ciudad);
        printf("direccion->%s", p->direccion);
		p = p->prox;
	};	
}

void mostrar(struct vehiculo *v){ /* muestra por pantalla la persona enlazada */
    if(v == NULL){
        printf("nada");
    }
	printf( "\n\nMostrar vehiculos\n\n");
	while (v){
        printf("Vehiculo %i\n\n");
		printf("placa ->%s", v->placa);
        printf("marca ->%s", v->marca);
        printf("color ->%s", v->color);
        printf("modelo ->%s", v->modelo);
        printf("year ->%s", v->year);
		v = v->prox;
	};	
}

void mostrar(struct infraccion *in){ /* muestra por pantalla la persona enlazada */
    if(in == NULL){
        printf("nada");
        getch();
    }
	printf( "\n\nMostrar multas\n\n");
	while (in){
        printf("multa %i\n\n");
        printf("fecha ->%s", in->fecha);
        printf("tipo ->%s", in->tipo);
        printf("monto ->%i\n", in->monto);
        printf("pagado ->%s", in->pagado);
		in = in->prox;
	};	
}

void imprimirTodo(struct persona *p){
    int x = 1, y = 1,z = 1;
    system("cls");
	printf("----BASE DE DATOS----\n\n");
    x = 1;
	for(; p; p = p->prox){
        printf("---persona %i---\n\n",x);
        printf("cedula->%i\n", p->cedula);
        printf("nombre->%s", p->nombre);
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
            z = 1;
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
        x++;
	}
}

void agregarpersona(struct persona **p,int cedula, char nombre[20], char apellidos[20], char fecha[20], char ciudad_nacimiento[20], char direccion[20]){
    persona *aux;
    aux = new struct persona;
    aux->cedula = cedula;
    strcpy(aux->nombre,nombre);
    strcpy(aux->apellido,apellidos);
    strcpy(aux->fecha,fecha);
    strcpy(aux->ciudad, ciudad_nacimiento);
    strcpy(aux->direccion,direccion);
    aux->prox = *p;
    aux->vehiculo = NULL;
    *p = aux;
}

void agregarvehiculo(struct vehiculo **p, char placa[50], char marca[50], char color[50], char modelo[50], char year[20]){
    vehiculo *aux;
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

void agregarinfraccion(struct infraccion **p, int Nmultas, char fecha_multa[50], char tipo_multa[50], int monto, char pagado[20]){
    infraccion *aux;
    aux = new struct infraccion;
    aux->cantidad = Nmultas;
    strcpy(aux->fecha,fecha_multa);
    strcpy(aux->tipo,tipo_multa);
    aux->monto = monto;
    strcpy(aux->pagado,pagado);
    aux->prox = *p;
    *p = aux;
}

void cargardatos(struct persona **p){
    int i,y,z,cedula,monto,Nmultas,cantidadpersona = 0, cantidadvehiculos = 0,cantidadmultas = 0;
    char tomar[101];
    char nombre[20], apellido[20], fecha[20], ciudad_nacimiento[20], direccion[20];
    char marca[20], modelo[20], year[20], color[20], placa[20];
    char fechai[20], tipo[20], pagado[5];
    if(p){
        archivo = fopen("datos.txt","rt");
        if(archivo == NULL){
            printf("no se pudo encontrar el archivo o no hay ningun registro de personas\n\n");
            system("pause");
        }
        fgets(tomar,20,archivo); sscanf(tomar,"%i",&cantidadpersona);
        for(i=0; i<cantidadpersona;i++){
            fgets(tomar,20,archivo); sscanf(tomar,"%i",&cedula);
            fgets(nombre,20,archivo);
            fgets(apellido,20,archivo);
            fgets(ciudad_nacimiento,20,archivo);
            fgets(fecha,20,archivo);
            fgets(direccion,20,archivo);
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

int main(){
    persona *p = NULL;
    int cedula, cantidadcar;
    char nombre[20], fecha[20], direccion[20];
    char marca[20], modelo[20], year[20], color[20], placa[20];
    cargardatos(&p);
    imprimirTodo(p);
    printf("\n\n");
    system("pause");
    return 0;
}