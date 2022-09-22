//A00831289 Daniel Evaristo Escalera Bonilla
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

// Complejidad: Pendiente*********************************************************************
// Compara dos strings y devuelve el substring más largo encontrado
string compararStrings(string t1, string t2){
    string substring = "A";

    // Código para cálculo

    return substring;
}

// Complejidad: Pendiente*********************************************************************
// Busca el substring común más largo en cada par de transmisiones
void substringMasLargo(vector<string> transmisiones, ofstream& check){
    check << "Los Substring más largos son:" << endl;
    
    string substring;

    for (int i = 0; i < transmisiones.size(); i++) {

        for (int j = i+1; j < transmisiones.size(); j++) {

            substring = compararStrings(transmisiones[i],transmisiones[j]);

            check << "T" << i+1 << "-T" << j+1 << " ==> " << substring << endl;
        }
    }
    
}

// Complejidad: Pendiente*********************************************************************
// Busca el palíndromo más grande en la transmisión
void palindromoMasGrande(vector<string> transmisiones, ofstream& check){
    check << "Palíndromo más grande:" << endl;

    for (int i = 0; i < transmisiones.size(); i++)
    {
        int pos = 1;
        string palindromo = "A";

        // Código para cálculo

        check << "Transmission" << i+1 << ".txt" << " ==> Posición: " << pos << endl;
        check << palindromo << endl;

        if(i < transmisiones.size()-1) check << "----" << endl;
    }
    
}

// Complejidad: Pendiente*********************************************************************
// Busca la subsecuencia del código menos un caracter que más se repite en la transmisión
void encontrarSubsequencia(string codigo, vector<string> transmisiones, ofstream& check){
    string sub = "A";
    int cant = 0;
    int archivo = 1;

    // Código del cálculo

    check << "La subsecuencia más encontrada es: " << sub << " con " << cant << " veces en el archivo" << endl;
    check << "Transmisión" << archivo << ".txt" << endl;
}

// Complejidad: Pendiente*********************************************************************
// Busca las coincidencias del código en la transmision y regresa sus posiciones en el string
vector<int> revisionCodigo(string codigo, string tr){
    vector<int> incidencias;

    // Código de cálculo

    incidencias.push_back(1);

    return incidencias;
}

// Complejidad: Pendiente*********************************************************************
// Recibe el código a buscar en las transmisiones y despliega las incidencias y su cantidad
// Asi como la subsequencia con un caracter menos más común
void incidenciasCodigo(string codigo, vector<string> transmisiones, ofstream& check){
    check << "Código: " << codigo << endl;
    
    for (int i = 0; i < transmisiones.size(); i++)
    {
        vector<int> incidencias = revisionCodigo(codigo,transmisiones[i]);

        check << "Transmission" << i+1 << ".txt ==> " << incidencias.size() << "  veces" << endl;

        for (int i = 0; i < incidencias.size()-1; i++) {
            check << incidencias[i] << ", ";
        }
        check << incidencias[incidencias.size()-1] << endl;

    }

    encontrarSubsequencia(codigo, transmisiones, check);

    check << "--------------" << endl;
}

// Complejidad: O(1)
// Abre el archivo deseado y regresa el texto que contiene
string lecturaTransmision(string archivo){
    ifstream transmission;

    string texto;

    transmission.open(archivo);

    getline(transmission,texto);

    transmission.close();

    return texto;
    
}

int main(){

    // Variables auxiliares para el código y el número del archivo
    string txt, archivo;

    // Vectores que almacenan el código y las transmisiones
    vector<string> code;
    vector<string> transmisiones (3);

    // Por cada archivo se guarda el texto de las transmisiones
    for (int i = 0; i < 3; i++) {
        archivo = "transmission";
        archivo += 49+i;
        archivo += ".txt";
        transmisiones[i] = lecturaTransmision(archivo);
    }
    
    // Se almacena el código en un vector de strings
    ifstream mcode("mcode.txt");

    while (getline(mcode,txt)) {
        code.push_back(txt);
    }

    mcode.close();

    // Se abre el archivo de resultado
    ofstream checking1("checking1.txt");

    // Por cada código se despliegan las incidencias y la subsequencia más común
    for (int i = 0; i < code.size(); i++)
    {
        incidenciasCodigo(code[i],transmisiones,checking1);
    }

    checking1 << "==============" << endl;

    // Se busca el palíndromo más grandes en las transmisiones
    palindromoMasGrande(transmisiones, checking1);

    checking1 << "============" << endl;

    // Se busca el substring común más largo de cada pareja de transmisiones
    substringMasLargo(transmisiones, checking1);

    checking1.close();

    return 0;
    

}