#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

FILE *archivo;

struct persona {
    int cedula;
    char nombre[50];
    char apellido[50];
    char fecha[50];
    char direccion[50];
    persona *prox;
    struct vehiculo *vehiculo;
};

struct vehiculo {
    char placa[50];
    char marca[50];
    char modelo[50];
    char year[50];
    char color[50];
    vehiculo *prox;
    struct infraccion *infraccion;
};

struct infraccion {
    int cantidad;
    char fecha[50];
    char tipo[50];
    int monto;
    char pagado[50];
    infraccion *prox;
};

void imprimirTodo(struct persona *p){
    int x, y,z;
    system("cls");
	printf("----BASE DE DATOS----\n\n");
    x = 1;
	for(; p; p = p->prox){
        printf("---persona %i---\n\n",x);
        printf("cedula->%i\n", p->cedula);
        printf("nombre->%s", p->nombre);
        printf("fecha->%s", p->fecha);
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

void agregarpersona(struct persona **p,int cedula, char nombre[20],char apellido[20], char fecha[20], char direccion[20]){
    struct persona *aux;
    aux = new struct persona;
    aux->cedula = cedula;
    strcpy(aux->nombre,nombre);
    strcpy(aux->apellido,apellido);
    strcpy(aux->fecha,fecha);
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

void guardardatos(struct persona *p){
    archivo = fopen("datos.txt", "wt");
    fprintf(archivo,"%i\n",contarpersona(p));
    for(; p; p = p->prox) {
        fprintf(archivo,"%i\n",p->cedula);
        fprintf(archivo,"%s",p->nombre);
        fprintf(archivo,"%s",p->apellido);
        fprintf(archivo,"%s",p->fecha);
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
    int cedula, monto, Nmultas, cantidadcar, cantidadmultas;
    char nombre[20],apellido[20], fecha[20], direccion[20];
    char marca[20], modelo[20], year[20], color[20], placa[20];
    char fechai[20], tipo[20], pagado[5];
    printf("introduzca la cedula: ");
    scanf("%i",&cedula);
    fflush(stdin);
    printf("introduzca su nombre: ");
    fgets(nombre,20,stdin);
    printf("introduzca su apellido: ");
    fgets(apellido,20,stdin);
    printf("introduzca su fecha de nacimiento: ");
    fgets(fecha,20,stdin);
    printf("introduzca su direccion: ");
    fgets(direccion,20,stdin);
    agregarpersona(&p,cedula,nombre,apellido,fecha,direccion);
    printf("cantidad de vehiculos(cero el caso de que no tenga vehiculo): ");
    scanf("%i",&cantidadcar);
    fflush(stdin);
    system("cls");
    if(cantidadcar != 0){
        for(int i = 1; i<=cantidadcar; i++){
        printf("\n\nVehiculo %i:\n\n",i);
        printf("Placa: ");
        fgets(placa,20,stdin);
        printf("marca: ");
        fgets(marca,20,stdin);
        printf("color: ");
        fgets(color,20,stdin);
        printf("Modelo: ");
        fgets(modelo,20,stdin);
        printf("year: ");
        fgets(year,20,stdin);
        agregarvehiculo(&p->vehiculo,placa,marca,color,modelo,year);
        printf("cantidad de multas(cero en el caso que no tenga multa): ");
        scanf("%i",&cantidadmultas);
        fflush(stdin);
        system("cls");
        if(cantidadmultas != 0){
            for(int i = 1; i<=cantidadmultas; i++){
            printf("\n\nMultas %i:\n\n",i);
            Nmultas = i;
            printf("fecha: ");
            fgets(fechai,20,stdin);
            printf("tipo: ");
            fgets(tipo,20,stdin);
            printf("monto: ");
            scanf("%i",&monto);
            fflush(stdin);
            printf("pagado: ");
            fgets(pagado,5,stdin);
            agregarinfraccion(&p->vehiculo->infraccion,Nmultas,fechai,tipo,monto,pagado);
            }
        }
        system("cls");
        }
    }
    system("pause");
    guardardatos(p);
    return 0;
}