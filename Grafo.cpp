#include "Grafo.h"
#include <iostream>

Grafo::Grafo() {
    matriz_de_adyacencia = nullptr;
    vertices = new Vector<string>;
    minimo_camino = nullptr;
}

void Grafo::agregar_vertice(string nuevo_vertice) {
    agrandar_matriz_de_adyacencia();
    vertices -> cargar(nuevo_vertice, vertices->obtener_longitud());
}

void Grafo::mostrar_grafo() {
    mostrar_vertices();
    mostrar_matriz_adyacencia();
}

void Grafo::agregar_camino(string origen, string destino, int peso) {
    int posicion_origen = vertices ->obtener_posicion(origen);
    int posicion_destino = vertices ->obtener_posicion(destino);

    if(posicion_origen == NO_ENCONTRO){
        cout << "El vertice " << origen << " no existe en el grafo" << endl;
    }
    if(posicion_destino == NO_ENCONTRO){
        cout << "El vertice " << destino << " no existe en el grafo" << endl;
    }

    if(!(posicion_destino == NO_ENCONTRO || posicion_origen == NO_ENCONTRO)) {
        matriz_de_adyacencia[posicion_origen][posicion_destino] = peso;
        matriz_de_adyacencia[posicion_destino][posicion_origen] = peso;
    }
}

void Grafo::camino_minimo(string origen, string destino) {
    int posicion_origen = vertices ->obtener_posicion(origen);
    int posicion_destino = vertices ->obtener_posicion(destino);

    if(posicion_origen == NO_ENCONTRO){
        cout << "El vertice " << origen << " no existe en el grafo" << endl;
    }
    if(posicion_destino == NO_ENCONTRO){
        cout << "El vertice " << destino << " no existe en el grafo" << endl;
    }

    camino_minimo(posicion_origen, posicion_destino);
}

void Grafo::agrandar_matriz_de_adyacencia() {
    int** matrizAuxiliar;
    int nueva_cantidad_de_vertices = vertices->obtener_longitud() + 1;

    matrizAuxiliar = new int*[nueva_cantidad_de_vertices];
    for(int i = 0; i < nueva_cantidad_de_vertices; i++){
        matrizAuxiliar[i] = new int[nueva_cantidad_de_vertices];
    }

    copiar_matriz_adyacente(matrizAuxiliar);
    inicializar_nuevo_vertice(matrizAuxiliar);
    liberar_matriz_adyacencia();
    matriz_de_adyacencia = matrizAuxiliar;
}

void Grafo::copiar_matriz_adyacente(int** nueva_adyacente) {
    for(int i = 0; i < vertices -> obtener_longitud(); i++){
        for(int j = 0; j < vertices -> obtener_longitud(); j++){
            nueva_adyacente[i][j] = matriz_de_adyacencia[i][j];
        }
    }
}

void Grafo::inicializar_nuevo_vertice(int** nueva_adyacente) {
    for(int i = 0; i < vertices -> obtener_longitud(); i++){
        nueva_adyacente[vertices -> obtener_longitud()][i] = INFINITO;
        nueva_adyacente[i][vertices -> obtener_longitud()] = INFINITO;
    }
    nueva_adyacente[vertices -> obtener_longitud()][vertices -> obtener_longitud()] = 0;
}

void Grafo::liberar_matriz_adyacencia() {
    for(int i = 0; i < vertices -> obtener_longitud(); i++){
        delete[] matriz_de_adyacencia[i];
    }
    delete[] matriz_de_adyacencia;
}

Grafo::~Grafo() {
    liberar_matriz_adyacencia();
    matriz_de_adyacencia = nullptr;
    delete minimo_camino;
}

void Grafo::mostrar_vertices() {
    cout << "Lista de vértices: [";
    for(int i = 0; i < vertices -> obtener_longitud(); i++){
        cout << vertices -> obtener_elemento(i + 1);
        if(i + 1 != vertices -> obtener_longitud()){
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void Grafo::mostrar_matriz_adyacencia() {
    cout << "Matriz de adyacencia:" << endl;
    for(int i = 0; i < vertices -> obtener_longitud(); i++){
        for(int j = 0; j < vertices -> obtener_longitud() * 2; j++) {
            if(j == vertices -> obtener_longitud() * 2 - 1){
                cout << endl;
            } else if(j % 2 == 0){
                if(matriz_de_adyacencia[i][j/2] == INFINITO){
                    cout << "∞";
                } else {
                    cout << matriz_de_adyacencia[i][j/2];
                }
            } else{
                cout << "|";
            }
        }
    }
    cout << endl;
}

void Grafo::camino_minimo(int origen, int destino) {
    minimo_camino -> camino_minimo(origen, destino);
}

void Grafo::usar_floyd() {
    delete minimo_camino;
    minimo_camino = new Floyd(vertices, matriz_de_adyacencia);
}