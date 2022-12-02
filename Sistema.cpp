#include "Sistema.h"
#include <iostream>

using namespace std;

Sistema::Sistema()
{
    grafo= new Grafo();
    menu = new Menu();
    vehiculo = new Auto();
    mapa= new Mapa();
    arbol_b = new ArbolB<Animal>(TRES_VIAS);

}

void Sistema::leer_animales()
{
    fstream archivo (PATH_ANIMALES);
    if (archivo.is_open())
    {
        string nombre, edad, tamanio , especie, personalidad;
        while(getline(archivo,nombre, ','))
        {
            getline(archivo,edad,',');
            getline(archivo,tamanio,',');
            getline(archivo,especie,',');
            getline(archivo,personalidad);

            cargar_animal(especie[0], nombre, stoi(edad), tamanio[0], personalidad[0]);
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();
}

void Sistema::cargar_animal(char especie, string nombre, int edad, char tamanio, char personalidad)
{
    Animal* animal;

    switch(especie)
    {
        case PERRO: 
            animal = new Perro(nombre, edad, tamanio, personalidad);
            break;
        case GATO: 
            animal = new Gato(nombre, edad, tamanio, personalidad);
            break;
        case CABALLO:
            animal = new Caballo(nombre, edad, tamanio, personalidad);
            break;
        case ROEDOR: 
            animal = new Roedor(nombre, edad, tamanio, personalidad);
            break;
        case CONEJO: 
            animal = new Conejo(nombre, edad, tamanio, personalidad);
            break;
        case ERIZO: 
            animal = new Erizo(nombre, edad, tamanio, personalidad);
            break;
        case LAGARTIJA:
            animal = new Lagartija(nombre, edad, tamanio, personalidad);
            break;
    }

    animales -> alta(animal, animales -> obtener_cantidad() + 1);

    punteros_animales -> cargar(animal, punteros_animales -> obtener_longitud());
}

void Sistema::cargar_mapa_grafo(){
    fstream archivo (PATH_MAPA);
    if (archivo.is_open())
    {   
        string vertice, total_filas, total_columnas, fila , columna , terreno, salto_linea;
        getline(archivo,total_filas,',');
        getline(archivo,total_columnas,';');

        mapa->establecer_filas(stoi(total_filas));
        mapa->establecer_columnas(stoi(total_columnas));
        mapa->inicializar_tablero();

        while(getline(archivo,salto_linea,'\n'))
        {   
            getline(archivo,fila,',');
            getline(archivo,columna,',');
            getline(archivo,terreno,';');
            
            vertice = fila + columna;
            mapa->cargar_casilla(stoi(fila)-1 , stoi(columna)-1 , vertice, terreno);
            grafo->agregar_vertice(vertice);
            
        } 
        cargar_caminos();
        cargar_contenido_mapa();
        grafo->usar_floyd();   
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();
}


void Sistema::cargar_caminos(){
    string origen;
    for (int i = 0; i < this->mapa->obtener_filas(); i++)
    {
        for (int j = 0; j < this->mapa->obtener_columnas(); j++){

            origen = mapa->obtener_tablero()[i][j].obtener_nombre();

            if (dentro_de_rango(i-1,j)){

                grafo->agregar_camino(origen, mapa->obtener_tablero()[i-1][j].obtener_nombre(), mapa->obtener_tablero()[i-1][j].obtener_costo());

            }
            if (dentro_de_rango(i+1,j)){

                grafo->agregar_camino(origen, mapa->obtener_tablero()[i+1][j].obtener_nombre(), mapa->obtener_tablero()[i+1][j].obtener_costo());

            }
            if (dentro_de_rango(i,j-1)){

                grafo->agregar_camino(origen, mapa->obtener_tablero()[i][j-1].obtener_nombre(), mapa->obtener_tablero()[i][j-1].obtener_costo());

            }
            if (dentro_de_rango(i,j+1)){

                grafo->agregar_camino(origen, mapa->obtener_tablero()[i][j+1].obtener_nombre(), mapa->obtener_tablero()[i][j+1].obtener_costo());

            }
        }
    } 
}

void Sistema::cargar_contenido_mapa(){
    int fila_animal=0, columna_animal=0, animal_random;
    mapa->obtener_tablero()[vehiculo->obtener_fila()][vehiculo->obtener_columna()].asignar_contenido(AUTO);

    for (int i = 0 ; i < ANIMALES_MAPA; i++){
        animal_random =  rand() % CANTIDAD_ESPECIES;

        do{
        fila_animal= rand() % mapa->obtener_filas();
        columna_animal= rand() % mapa->obtener_columnas();
            
        }while (mapa->obtener_tablero()[fila_animal][columna_animal].obtener_contenido() != VACIO);

        switch (animal_random)
        {
        case 0:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(PERRO);
            break;

        case 1:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(GATO);
            break;

        case 2:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(CABALLO);
            break;

        case 3:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(ROEDOR);
            break;

        case 4:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(CONEJO);
            break;

        case 5:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(ERIZO);
            break;

        case 6:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(LAGARTIJA);
            break;

        }
    }
}

void Sistema::cargar_contenido_mapa(){
    mapa->obtener_tablero()[vehiculo->obtener_fila()][vehiculo->obtener_columna()].asignar_contenido(AUTO);
    int fila_animal=0, columna_animal=0, animal_random;

    for (int i = 0 ; i < ANIMALES_MAPA; i++){
        animal_random =  rand() % CANTIDAD_ESPECIES;

        do{
        fila_animal= rand() % mapa->obtener_filas();
        columna_animal= rand() % mapa->obtener_columnas();
            
        }while (mapa->obtener_tablero()[fila_animal][columna_animal].obtener_contenido() != VACIO);

        switch (animal_random)
        {
        case 0:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(PERRO);
            break;
        case 1:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(GATO);
            break;
        case 2:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(CABALLO);
            break;
        case 3:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(ROEDOR);
            break;
        case 4:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(CONEJO);
            break;
        case 5:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(ERIZO);
            break;
        case 6:
            mapa->obtener_tablero()[fila_animal][columna_animal].asignar_contenido(LAGARTIJA);
            break;
        }
    }
}

bool Sistema::dentro_de_rango(int fila, int columna){
    return (fila >= 0 && fila < this->mapa->obtener_filas() && columna >= 0 && columna < this->mapa->obtener_columnas());
}

void Sistema::pedir_movimiento(int &fila , int &columna){
    
    cout<<"Ingrese la fila donde desea moverse: "<<endl;
    cin>>fila;
    cout<<"Ingrese la columna donde desea moverse: "<<endl;
    cin>>columna;
     
    while (!dentro_de_rango(fila-1,columna -1)){
        cout<<"Ingrese una fila valida para moverse: "<<endl;
        cin>>fila;
        cout<<"Ingrese una columna valida para moverse: "<<endl;
        cin>>columna;
    }
    fila--;
    columna--;
}
void Sistema::procesar_movimiento(){

    int fila , columna, costo_combustible;
    string nombre, origen , destino;

    pedir_movimiento(fila , columna);

    origen= mapa->obtener_tablero()[vehiculo->obtener_fila()][vehiculo->obtener_columna()].obtener_nombre();

    destino= mapa->obtener_tablero()[fila][columna].obtener_nombre();

    costo_combustible= grafo->costo_camino( origen, destino);

    if (vehiculo->obtener_combustible() < costo_combustible){

        cout<<"Combustible insuficiente "<<endl;
        cout<< "Combustible actual: "<<vehiculo->obtener_combustible()<<endl;
        cout<<"Combustible necesario: "<< costo_combustible <<endl;

    }else{

        vehiculo->restar_combustible(costo_combustible);
        grafo->minimo_camino(origen, destino);
        cout<< "Combustible restante: "<<vehiculo->obtener_combustible()<<endl;

        mapa->obtener_tablero()[vehiculo->obtener_fila()][vehiculo->obtener_columna()].asignar_contenido(VACIO);
        
        switch (mapa->obtener_tablero()[fila][columna].obtener_contenido())
        {
        case PERRO:
            
            cout<<"Encontraste un Perro!"<<endl;

            pedir_nombre(nombre);
            rescatar_animal(nombre, PERRO);
            break;

        case GATO:
            
            cout<<"Encontraste un Gato!"<<endl;

            pedir_nombre(nombre);
            rescatar_animal(nombre, GATO);     
            break;

        case CABALLO:
            
            cout<<"Encontraste un Caballo!"<<endl;

            pedir_nombre(nombre);
            rescatar_animal(nombre, CABALLO);
            break;

        case ROEDOR:
            
            cout<<"Encontraste un Roedor!"<<endl;

            pedir_nombre(nombre);
            rescatar_animal(nombre, ROEDOR);
            break;

        case CONEJO:
            
            cout<<"Encontraste un Conejo!"<<endl;

            pedir_nombre(nombre);
            rescatar_animal(nombre, CONEJO);
            break;

        case ERIZO:
            
            cout<<"Encontraste un Erizo!"<<endl;

            pedir_nombre(nombre);
            rescatar_animal(nombre, ERIZO);   
            break;

        case LAGARTIJA:
            
            cout<<"Encontraste una Lagartija!"<<endl;
            
            pedir_nombre(nombre);
            rescatar_animal(nombre, LAGARTIJA);
            break;

        }
        vehiculo->cambiar_posicion(fila,columna);
        mapa->obtener_tablero()[vehiculo->obtener_fila()][vehiculo->obtener_columna()].asignar_contenido(AUTO);
    }
}
void Sistema::procesar_opcion(int opcion_tomada)
{   
    int combustible_cargar;
    string nombre, espacio, opcion_submenu, posicion_adopcion;

    pasar_tiempo();

    switch (opcion_tomada)
    {
        case LISTAR_ANIMALES:
            if(animales -> vacia())
            {
                cout << endl << "La reserva actualmente no tiene animales :(" << endl;
                break;
            }

            cout << endl << "LISTA DE ANIMALES EN LA RESERVA:" << endl << endl;
            
            listar_animales();
            break;

        case RESCATAR_ANIMAL: 
            cout << endl << "RESCATAR ANIMAL:" << endl << endl;

            menu->mostrar_mapa(mapa->obtener_tablero() , mapa->obtener_filas() , mapa->obtener_columnas());
            procesar_movimiento();

            break;

        case BUSCAR_ANIMAL:
            if(animales -> vacia())
            {
                cout << endl << "La reserva actualmente no tiene animales :(" << endl;
                break;
            }

            cout << endl << "BUSCAR ANIMAL DE LA RESERVA:" << endl << endl;

            pedir_nombre(nombre);
            posicion = buscar_nombre(nombre);
            if (posicion != NO_ENCONTRO)
            {
                mostrar_animal(animales -> consulta(posicion));
            }
            else
            {
                cout << endl << "No se pudo encontrar el nombre ingresado." << endl << endl;
            }
            break;

        case CUIDAR_ANIMAL:
            if(animales -> vacia())
            {
                cout << endl << "La reserva actualmente no tiene animales :(" << endl;
                break;
            }

            cout << endl << "CUIDAR ANIMALES:" << endl << endl;

            mostrar_submenu();
            ingresar_opcion_submenu(opcion_submenu); 
            procesar_opcion_submenu(opcion_submenu);
            while (stoi(opcion_submenu) != REGRESAR_INICIO)
            {
                mostrar_submenu();
                ingresar_opcion_submenu(opcion_submenu); 
                procesar_opcion_submenu(opcion_submenu);
            }
            break;

        case ADOPTAR_ANIMAL:
            if(animales -> vacia())
            {
                cout << endl << "La reserva actualmente no tiene animales :(" << endl;
                break;
            }

            cout << endl << "ADOPTAR ANIMAL:" << endl << endl;

            break;
        
        case CARGAR_COMBUSTIBLE:

            cout << endl << "CARGAR_COMBUSTIBLE:" << endl << endl;

            do{
                cout<<"Ingrese la cantidad de combustible que desea cargar: "<<endl;
                cin>>combustible_cargar;
                
            }while(combustible_cargar >= 100 || combustible_cargar < 1);

            vehiculo->cargar_combustible(combustible_cargar);

            break;
        case GUARDAR_Y_SALIR:

            guardar();

            break;    
    }
}

void Sistema::pasar_tiempo()
{
    Animal* animal;

    while (animales -> hay_siguiente())
    {
        animal = animales -> siguiente();
        
        if (animal -> requiere_ducha())
        {
            animal -> dearmar_higiene();
        }
        animal -> aumentar_hambre();
    }
    animales -> iniciar();
}

void Sistema::limpiar_pantalla()
{
    #ifdef _WIN32
            system("cls");
    #else
            system ("clear");
    #endif
}

void Sistema::listar_animales()
{
    if(arbol_b -> arbol_vacio())
    {
        cout << endl << "La reserva actualmente no tiene animales :( " << endl << endl;
    }
    else
    {
        arbol_b -> listar_creciente();
    }
    animales -> iniciar();
}

void Sistema::mostrar_animal(Animal* animal)
{
    cout << "---------------------------------------------------" << endl << endl;
    cout << "Nombre: " << animal -> obtener_nombre() << endl <<
    "Edad: " << animal -> obtener_edad() << endl <<
    "Tamanio: " << animal -> obtener_tamanio_texto() << endl <<
    "Especie: " << animal -> obtener_especie_texto() << endl <<
    "Personalidad: " << animal -> obtener_personalidad_texto() << endl <<
    "Hambre: " << animal -> obtener_hambre() << endl <<
    "Higiene: " << animal -> obtener_higiene() << endl << endl;
}

void Sistema::pedir_nombre(string &nombre)
{
    cout << "Ingrese el nombre del animal: ";
    getline (cin >> ws, nombre);
}

int Sistema::buscar_nombre(string nombre)
{
    bool encontrado = false;
    int posicion = NO_ENCONTRO, i = 1;
    Animal* animal; 
    
    while (animales -> hay_siguiente() && !encontrado)
    {
        animal = animales -> siguiente();

    mostrar_submenu();
    ingresar_opcion_submenu(opcion_submenu);

}

bool Sistema::verificar_intentar_de_nuevo(int posicion, string nombre)
{
    string decision;

    cout << "El nombre ingresado ya existe en la reserva." << endl <<
    "Ingrese [1] si desea ingresar otro nombre, si desea volver al menu principal ingrese cualquier otro numero: ";      
        
    getline(cin >> ws, decision);

    while (!cadena_numeros_valida(decision))
    {
        cout << endl << "Decision invalida, ingrese un numero para su decision: ";
        getline(cin >> ws, decision);
    }
    
    if (stoi(decision) == 1)
        return true;

    return false;
}
*/

string Sistema::tamanio_animal_aleatorio (int numero)
{
    string tamanio;
    
    switch(numero)
    {
    case 1: 
        tamanio = DIMINUTO_TEXTO;
        break;

    case 2:
        tamanio = PEQUENIO_TEXTO;
        break;

    case 3:
        tamanio = MEDIANO_TEXTO;
        break;

    case 4:
        tamanio = GRANDE_TEXTO;
        break;

    case 5:
        tamanio = GIGANTE_TEXTO;
        break;
    }
    return tamanio;
}

string Sistema::personalidad_animal_aleatoria (int numero)
{
    string personalidad;
    
    switch(numero)
    {
    case 1: 
        personalidad = DORMILON_TEXTO;
        break;

    case 2:
        personalidad = JUGUETON_TEXTO;
        break;

    case 3:
        personalidad = SOCIABLE_TEXTO;
        break;

    case 4:
        personalidad = TRAVIESO_TEXTO;
        break;

    }
    return personalidad;
}

void Sistema::rescatar_animal(string nombre,char especie)
{
    string tamanio, personalidad;
    int edad;

    edad = rand() % DELIMITADOR_EDAD;

    tamanio = tamanio_animal_aleatorio (1 + (rand() % CANTIDAD_TAMANIOS));

    personalidad = personalidad_animal_aleatoria (1 + (rand() % CANTIDAD_PERSONALIDADES));

    cargar_animal(especie, nombre, edad, tamanio[0], personalidad[0]);
}

void Sistema::mostrar_submenu()
{
    cout << "[1] Elegir individualmente." << endl <<
    "[2] Alimentar a todos." <<endl << 
    "[3] Duchar a todos." <<endl <<
    "[4] Regresar al inicio." << endl << endl;
}

void Sistema::ingresar_opcion_submenu(string &opcion_submenu)
{
    cout << "Ingrese el numero de la opcion que desa ejecutar: ";
    getline(cin >> ws, opcion_submenu);

    while (!cadena_numeros_valida(opcion_submenu) || stoi(opcion_submenu) == 0 || stoi(opcion_submenu) > REGRESAR_INICIO)
    {
        cout << "Opcion invalida, ingrese el numero de la opcion que desa ejecutar: ";
        getline(cin >> ws, opcion_submenu);
    }
}

void Sistema::procesar_opcion_submenu(string opcion_submenu)
{
    switch(stoi(opcion_submenu))
    {
        case ELEGIR_INDIVIDUALMENTE:
            eleccion_individual();
            break;
    }
}

/*void Sistema::mostrar_opciones_individuales()
{
    cout << "[1] Duchar." << endl <<
    "[2] Alimentar." << endl << 
    "[3] Saltear animal." << endl << endl;
}

void Sistema::pedir_opciones_individuales(string &opcion_individual)
{
    cout << "Ingrese la opcion a ejecutar: ";
    getline(cin >> ws, opcion_individual);

    while (!cadena_numeros_valida(opcion_individual) || stoi(opcion_individual) == 0 || stoi(opcion_individual) > SALTEAR_ANIMAL)
    {
        cout << "Opcion invalida, ingrese la opcion a ejecutar: ";
        getline(cin >> ws, opcion_individual);
    }

}

void Sistema::procesar_opcion_individual(int opcion_individual, Animal* animal)
{
    switch (opcion_individual)
    {
        case DUCHAR:
            if (animal -> requiere_ducha())
            {
                animal -> duchar();
            }
            else 
            {
                cout << animal -> obtener_nombre() << " no necesita ducharse porque es un/a " << animal -> obtener_especie_texto() << endl; 
            }
            break;

        case ALIMENTAR:
            animal -> alimentar();
            cout << animal -> obtener_nombre() << " ha sido alimentado" << endl;
            break;
    }
}
void Sistema::eleccion_individual()
{
    Animal* animal;
    string opcion_individual;

    while(animales ->hay_siguiente())
    {
        animal = animales -> siguiente ();
        //mostrar_animal(animal);
        mostrar_opciones_individuales();
        pedir_opciones_individuales(opcion_individual);
        
        if (stoi(opcion_individual) != SALTEAR_ANIMAL)
        {
            procesar_opcion_individual(stoi(opcion_individual), animal);
        }
    }
    animales -> iniciar();
}

void Sistema::alimentar_todos()
{
    Animal* animal;
    
    while (animales -> hay_siguiente())
    {
        animal = animales -> siguiente();
        animal -> alimentar();
    }
    animales -> iniciar();
}

void Sistema::duchar_todos()
{
    Animal * animal;

    while (animales -> hay_siguiente())
    {
        animal = animales -> siguiente();
        
        if (animal -> requiere_ducha())
        {
            animal -> duchar();
        }
        else
        {
            cout << animal -> obtener_nombre() << " no necesita ducharse porque es un/a " << animal -> obtener_especie_texto() << endl;
        }
    }
    animales -> iniciar();
}
*/
void Sistema::pedir_espacio(string &espacio)
{
    cout << "Ingrese el espacio disponible para el animal en m² (mayor a 0): ";
    getline(cin >> ws, espacio);

    while (!cadena_numeros_valida(espacio) || stoi(espacio) == 0)
    {
        cout << "Espacio invalido, ingrese el espacio en  m² disponible para el animal (mayor a 0): ";
        getline(cin >> ws, espacio);
    }
}

bool Sistema::cadena_numeros_valida(string numeros)
{
    int i = 0;
    long int tamanio = numeros.size();
    bool valido = true; 

    while (i < tamanio && valido)
    {
        if (!isdigit(numeros[i]))
        {
            valido = false;
        }
        i++;
    } 
    return valido;
}

void Sistema::mostrar_animal_espacio(Animal* animal, int posicion)
{
    cout << posicion << ") " << "Nombre: " << animal -> obtener_nombre() << endl <<
    "Edad: " << animal -> obtener_edad() << endl <<
    "Especie: " << animal -> obtener_especie_texto() << endl <<
    "Personalidad: " << animal -> obtener_personalidad_texto() << endl;
}

void Sistema::validar_animales_espacio(Animal* animal, string espacio, int posicion, bool* animales_validos, int &contador_validos)
{
    char tamanio = animal -> obtener_tamanio_caracter();
    contador_validos = 0;

    int espacio_int = stoi(espacio);
    
    if (espacio_int < DELIMITADOR_DIMINUTO)
    {
        if (tamanio == DIMINUTO)
        {
            mostrar_animal_espacio(animal, posicion);
            animales_validos[posicion - 1] = true;
            contador_validos++;
        }
        else
            animales_validos[posicion - 1] = false;
    } 

    else

    if (espacio_int < DELIMITADOR_PEQUENIO_MEDIANO)
    {
        if (tamanio == DIMINUTO || tamanio == PEQUENIO)
        {
            mostrar_animal_espacio(animal, posicion);
            animales_validos[posicion - 1] = true;
            contador_validos++;
        }
        else
            animales_validos[posicion - 1] = false;
    }

    else 

    if (espacio_int < DELIMITADOR_GRANDE) 
    {
        if (tamanio != GIGANTE && tamanio != GRANDE)
        {
            mostrar_animal_espacio(animal, posicion);
            animales_validos[posicion - 1] = true;
            contador_validos++;
        }
        else
            animales_validos[posicion - 1] = false;
    }

    else 

    if (espacio_int < DELIMITADOR_GIGANTE)
    {
        if (tamanio != GIGANTE)
        {
            mostrar_animal_espacio(animal, posicion);
            animales_validos[posicion - 1] = true;
            contador_validos++;
        }
        else
            animales_validos[posicion - 1] = false;
    }

    else

    {
        mostrar_animal_espacio(animal, posicion);
        animales_validos[posicion - 1] = true;
        contador_validos++;
    }
} 
/*

bool Sistema::posicion_espacio_validado(int posicion, bool* animales_validos)
{
    if(posicion == -1) 
    {
        return true;
    }

    bool valido = false;

    if(posicion < animales -> obtener_cantidad() && posicion >= 0)
    {
        valido = animales_validos[posicion];
    }

    return valido;
}

string Sistema::pedir_opcion_adopcion(bool* animales_validos)
{
    string posicion_adopcion;

    cout << endl << "Ingrese el numero del animal que desea ingresar, si desea cancelar la adopcion ingrese [0]: ";
    getline(cin >> ws, posicion_adopcion);

    while (!cadena_numeros_valida(posicion_adopcion) || stoi(posicion_adopcion) > animales -> obtener_cantidad() || !posicion_espacio_validado(stoi(posicion_adopcion) -1, animales_validos))
    {
        cout << endl << "Opcion invalida, ingrese el numero del animal que desea ingresar, si desea cancelar la adopcion ingrese [0]: ";
        getline(cin >> ws, posicion_adopcion);
    }

    return posicion_adopcion;
}
void Sistema::listar_animales_espacio(string espacio, int posicion , bool* animales_validos, int &animales_validados)
{
    Animal* animal;
    int contador_validos;

    while (animales -> hay_siguiente())
    {

        animal = animales -> siguiente();
        validar_animales_espacio(animal, espacio, posicion , animales_validos, contador_validos);
        posicion++;
    }
    animales_validados = contador_validos;

    animales -> iniciar();
}
*/

void guardar_animal(Animal* animal, ofstream& archivo)
{
    archivo << 
    animal -> obtener_nombre() << "," << 
    animal -> obtener_edad()<< "," << 
    animal -> obtener_tamanio_texto() << "," << 
    animal -> obtener_especie_caracter() << "," << 
    animal -> obtener_personalidad_texto() << 
    endl;
}

void Sistema::guardar()
{
    Animal * animal;
    ofstream archivo (PATH_ANIMALES);
    if (archivo.is_open())
    {
        for (int i = 1; i <= animales -> obtener_cantidad(); i++)
        {
            animal = animales -> consulta(i);
            archivo << animal -> obtener_nombre() << "," << animal -> obtener_edad()<< "," << animal -> obtener_tamanio_texto() <<
            "," << animal -> obtener_especie_caracter() << "," << animal -> obtener_personalidad_texto() << endl;
        }        
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    archivo.close();
}

Sistema::~Sistema()
{
    delete arbol_b;
    delete vehiculo;
    delete grafo;
    delete menu;
}
