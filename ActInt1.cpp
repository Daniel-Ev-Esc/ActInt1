//A00831289 Daniel Evaristo Escalera Bonilla
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<set>
#include<utility>

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

// Complejidad: O(nm)
// Donde n es la longitud del string y m es la longitud del substring a buscar
// Recibe un string y un substring a buscar y regresa el número de veces que aparece ese substring en el string
int contarSubseq(string str, string subs) {
    int n = str.length(),m = subs.length();

    if (n <= 0) return 0; // Si el string esta vacío regresa 0, no hay substrings
    if (m <= 0) return 1; // Si el substring a buscar está vacío, el unico substring es null
    
    vector<vector<int>> mat (m,vector<int> (n,0)); // Matriz

    mat[0][0] = (str[0] == subs[0]) ? 1 : 0; // Si el primer caracter de ambos strings es el mismo, pone 1 

    for (int i = 1; i < n; i++) { // Inicializar primera fila
        mat[0][i] = (str[i] == subs[0]) ? mat[0][i-1] + 1 : mat[0][i-1]; 
    }

    for (int i = 1; i < m; i++) { // Inicializar primera columna que nunca tendrá coincidencias
        mat[i][0] = 0;
    }
    
    for (int i = 1; i < m; i++) { // A lo largo de la matriz, si los caracteres coinciden, sumamos las coincidencias que tenemos hasta el momento
        for (int j = 1; j < n; j++) {
            mat[i][j] = (str[j] == subs[i]) ? mat[i-1][j-1] + mat[i][j-1] : mat[i][j-1];
        }
        
    }
    
    // Regresa el total de coincidencias
    return mat[m-1][n-1];
}

// Complejidad: O(x(x-1)*y)
// Donde x es la longitud del código, que eventualmente se pasa con un caracter menos y y es la longitud del string
// Busca la subsecuencia del código menos un caracter que más se repite en la transmisión
pair<int,string> encontrarSubsequencia(string codigo, string transmision){
    
    set<string> grupo;
    vector<pair<int,string>> subseq;

    // Por cada caracter se guarda el string de el string original menos un caracter
    for (int i = 0; i < codigo.length(); i++) {
        string menosuno = "";
        
        for (int j = 0; j < codigo.length(); j++) {
            if (j != i) menosuno += codigo[j]; 
        }
        
        grupo.insert(menosuno);
    }

    // Por cada subsequencia almacenamos la cantidad de apariciones de esa subsequencia
    for (string x: grupo) {
        pair<int,string> reps (0,x);
        if(x != "") reps.first = contarSubseq(transmision, x);
        else reps.second = "null";
        subseq.push_back(reps);
    }

    pair<int,string> max (1,"null");

    // Buscar la subsequencia que más apareció
    for (int i = 0; i < subseq.size(); i++) {
        if (subseq[i].first >= max.first) {
            if (subseq[i].first == 1) max.second = subseq[i].second;      
            max = subseq[i];
        }
    }

    return max;
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

    vector<pair<int,string>> subseq;

    for (int i = 0; i < transmisiones.size(); i++) { // Llamar al buscador de subsequencia por cada transmision
        subseq.push_back(encontrarSubsequencia(codigo, transmisiones[i]));
    }

    int arch;
    pair<int,string> max (0,"null");

    // Buscar el archivo donde se encontraron más subsequencias
    for (int i = 0; i < subseq.size(); i++) {
        if (subseq[i].first > max.first) {
            max = subseq[i];
            arch = i+1;
        }
    }
    
    check << "La subsecuencia más encontrada es: " << max.second << " con " << max.first << " veces en el archivo" << endl;
    check << "Transmisión" << arch << ".txt" << endl;
    
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