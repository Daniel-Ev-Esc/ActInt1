//A00831289 Daniel Evaristo Escalera Bonilla
//A01284373 Andres Aguirre Rodriguez
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<set>

using namespace std;

#define MAXSTR 1001

// Complejidad: O(m*n)
// Compara dos strings y devuelve el substring más largo encontrado
string compararStrings(string t1, string t2){
    //string substring = "A";

    int m = t1.length();
    int n = t2.length();
    int result = 0;
    int end;
    int len[2][MAXSTR];
    int currRow = 0;
 
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                len[currRow][j] = 0;
            }
            else if (t1[i - 1] == t2[j - 1]) {
                len[currRow][j] = len[1 - currRow][j - 1] + 1;
                if (len[currRow][j] > result) {
                    result = len[currRow][j];
                    end = i - 1;
                }
            }
            else {
                len[currRow][j] = 0;
            }
        }
 
        currRow = 1 - currRow;
    }
    if (result == 0) {
        return "-1";
    }
 
    return t1.substr(end - result + 1, result);
    //return substring;
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
// Busca las coincidencias del código en la transmision y regresa sus posiciones en el string
vector<int> revisionCodigo(string codigo, string tr){
    vector<int> incidencias;

    // Código de cálculo

    incidencias.push_back(1);

    return incidencias;
}

// Complejidad: O(nm)
// Donde n es la cantidad de subsecuencias del codigo menos uno diferente y m la longitud del string
// Obtiene la subsecuencia que más se encuentra en la transmisión
pair<int,string> encontrarSubsequencia(string codigo, string transmision){
    
    set<string> grupo;
    vector<pair<int,string>> subseq;

    for (int i = 0; i < codigo.length(); i++) {
        
        string menosuno = "";
        
        for (int j = 0; j < codigo.length(); j++) {
            if (j != i) menosuno += codigo[j];
        }
        
        grupo.insert(menosuno);
    }

    for (string x: grupo)
    {
        pair<int,string> reps (0,x);
        reps.first = revisionCodigo(transmision, x).size();
        subseq.push_back(reps);
    }

    pair<int,string> max (1,"null");

    for (int i = 0; i < subseq.size(); i++)
    {
        if (subseq[i].first > max.first)
        {
            max = subseq[i];
        }
        
    }

    return max;
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

    for (int i = 0; i < transmisiones.size(); i++)
    {
        subseq.push_back(encontrarSubsequencia(codigo, transmisiones[i]));
    }

    int arch;
    pair<int,string> max (0,"null");

    for (int i = 0; i < subseq.size(); i++)
    {
        if (subseq[i].first > max.first)
        {
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