/*
A00831289 Daniel Evaristo Escalera Bonilla
A01284373 Andres Aguirre Rodriguez
A00831719 Alberto Horacio Orozco Ramos 
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<set>

using namespace std;

// Tamaño máximo de las transmisiones
#define MAXSTR 1001

// Complejidad: O(m*n)
// Compara dos strings y devuelve el substring más largo encontrado
string compararStrings(string t1, string t2){

    // Variables que permiten manejar y almacenar los strings y el resultado de su comparación
    int m = t1.length();
    int n = t2.length();
    int result = 0;
    int end;

    // El arreglo de dos renglones en donde se irá intercalando el renglón y nos dirá el numero de coincidencias seguidas en ambos strings
    int len[2][MAXSTR];
    int currRow = 0;
 
    for (int i = 0; i <= m; i++) { // Por cada caracter en el primer string
        for (int j = 0; j <= n; j++) { // Recorre el segundo string
            if (i == 0 || j == 0) {
                len[currRow][j] = 0;
            }
            else if (t1[i - 1] == t2[j - 1]) { // Cuando se encuentra alguna coincidencia entre ambos strings
                len[currRow][j] = len[1 - currRow][j - 1] + 1; // Se agrega y almacena con las coincidencias anteriores
                if (len[currRow][j] > result) { // Si es el mayor numero de coinciencias hasta el momento, se guarda ese dato
                    result = len[currRow][j];
                    end = i - 1;
                }
            }
            else {
                len[currRow][j] = 0;
            }
        }

        // Según el renglón donde se encuentre calcula las coincidencias con ayuda del otro y las almacena
        currRow = 1 - currRow;
    }
    if (result == 0) {
        return "-1";
    }
 
    // Regresamos el substring en el rango en donde se encontraron mas coincidencias
    return t1.substr(end - result + 1, result);
}

// Complejidad: O(3mn)
// Donde m y n son los tamaños de los strings y se utilizan en la función interna
// Busca el substring común más largo en cada par de transmisiones
void substringMasLargo(vector<string> transmisiones, ofstream& check){
    check << "Los Substring más largos son:" << endl;
    
    string substring;

    // Se realiza la comparación con todos los pares diferentes de transmisiones
    for (int i = 0; i < transmisiones.size(); i++) {

        for (int j = i+1; j < transmisiones.size(); j++) {

            substring = compararStrings(transmisiones[i],transmisiones[j]);

            check << "T" << i+1 << "-T" << j+1 << " ==> " << substring << endl;
        }
    }
    
}

// Complejidad: O(n)
// Donde n es la longitud del string
// Encuentra el palindromo más grande dentro del string
// Modificación del algoritmo de manacher para que también devuelva el indice de inicio
pair<int,string> manacher(string tr){

    // Inicializa variables para el manejo de strings y el almacenamiento de resultados
    int n = tr.length();
    string palindromo = "";

    // Se crea un string con los caracteres del original, pero separado por un caracter especial
    for (int i = 0; i < n; i++) {
        palindromo += "-";
        palindromo += tr[i];
    }
    palindromo += "-";

    // Se utiliza este nuevo string para el algoritmo
    n = palindromo.length();
    vector<int> l(n);

    // Incializamos la primera letra
    l[0] = 0;
    l[1] = 1;

    // Valores de control de resultados
    int mLong = 0, mCenter = 0;
    bool e;

    // Definimos variables para saber las posiciones relevantes en el algoritmo y recorrelo hasta el final
    for (int c=1, li=0, ri=2; ri < n; ri++)
    {
        li = c-(ri-c);
        e = false;
        if (c-mLong <= ri && ri >= mLong)
        {
            // Si el valor en la izquierda es menor a la suma del ultimo valor calculado con su valor actual menos la derecha, li y ri tienen el mismo valor
            if (l[li] < (c+l[c]-ri))
            {
                l[ri] = l[li];
            }
            // Si el valor de li es igual a la suma del ultimo valor calculado con su valor actual menos ri y esta suma es dos veces la longitud de n, li y ri tienen el mismo valor
            else if (l[li] == (c+l[c]) - ri && (c+l[c]) == 2*n){
                l[ri] = l[li];
            }
            // Si el valor de li es igual a la suma del ultimo valor calculado con su valor actual menos ri y esta suma es menor a dos veces la longitud de n, li y ri tienen el mismo valor y expandimos
            else if (l[li] == (c+l[c]) - ri && (c+l[c]) < 2*n){
                l[ri] = l[li];
                e = true;
            }
            // Si el valor de li es mayor a la suma del ultimo valor calculado con su valor actual menos ri y esta suma es menor a dos veces la longitud de n, li toma el valor de ese cálculo y expandimos
            else if (l[li] > (c+l[c]) - ri && (c+l[c]) < 2*n){
                l[ri] = (c+l[c]) - ri;
                e = true;
            }
        }
        else{ // Si ri no se encuentra dentro dle rango entre c y la longitud máxima, su valor es 0 y expandimos
            l[ri] = 0;
            e = true; 
        }
        if (e) // Expandir
        {
            // Mientras se siga encontrando un palindromo en las casillas dentro del rango, aumentamos el valor de la casilla ris
            while ((ri + l[ri] < n) && (ri-l[ri]>0) && (palindromo[ri-l[ri]-1] == palindromo[ri+l[ri]+1]))
            {
                l[ri]++;
            }
            
        }
        c = ri; // Establecemos el último valor calculado como ri
        if (l[ri] > mLong) // Si el valor calculado es el más grande que hemos encontrado actualizamos los valores máximos
        {
            mLong = l[ri];
            mCenter = ri;
        } 
    }
    int ini = (mCenter - mLong)/2; // Encontramos el inicio del palíndromo
    string salida ="";
    for (int i = ini; i < (ini+mLong); i++) // Lo vamos guardando en un string
    {
        salida += tr[i];
    }

    pair<int,string> pal (ini + 1,salida);
    
    return pal;
}

// Complejidad: O(3n)
// Donde n es la longitud de la transmisión más grande
// Busca el palíndromo más grande en la transmisión
void palindromoMasGrande(vector<string> transmisiones, ofstream& check){
    check << "Palíndromo más grande:" << endl;

    // Buscamos en cada transmisión
    for (int i = 0; i < transmisiones.size(); i++)
    {   
        pair<int,string> palindromo = manacher(transmisiones[i]);

        check << "Transmission" << i+1 << ".txt ==> Posición: " << palindromo.first << endl;
        check << palindromo.second << endl;

        if(i < transmisiones.size()-1) check << "----" << endl;
    }
    
}

// Complejidad: O(m) m es la longitud del patron
// Preprocesamiento: Longest Proper Prefix which is also a suffix
vector<int> lps (string p) {
    int n = p.length();
    vector<int> lpsv(n, 0);

    int j = 0, i = 1;

    while (i < n) {
        if (p[i] == p[j]) {
            lpsv[i] = j + 1;
            j++;
            i++;
        }
        else {
            if (j == 0) {
                lpsv[i] = 0;
                i++;
            }
            else {
                j = lpsv[j - 1];
            }
        }
    }

    return lpsv;
}

// Complejidad: O(n + m) n es la longitud del texto y m es la longitud del patron
/* Busca las coincidencias del código en la transmision y regresa sus posiciones en el string.
Esta función esta basada en el algoritmo de KMP (Knuth-Morris-Pratt)
*/
vector<int> revisionCodigo(string codigo, string tr){

    vector<int> incidencias;
    vector<int> lpsv = lps(codigo);

    int j = 0, i = 0, n = tr.length(), m = codigo.length();

    while (i < n) {
        if (tr[i] == codigo[j]) {
            i++;
            j++;
            if (j == m) {
                incidencias.push_back(i - m);
                j = lpsv[j - 1];
            }
        }
        else {
            if (j == 0) {
                i++;
            }
            else {
                j = lpsv[j - 1];
            }
        }
    }

    return incidencias;
}


// Complejidad: O(n^2 + nm)
// Donde n es la cantidad de subsecuencias del codigo menos uno diferente y m la longitud del string
// Obtiene la subsecuencia que más se encuentra en la transmisión
pair<int,string> encontrarSubsequencia(string codigo, string transmision){
    
    set<string> grupo;
    vector<pair<int,string>> subseq;

    // Se almacenan las subsequencias menos uno del código
    for (int i = 0; i < codigo.length(); i++) {
        
        string menosuno = "";
        
        for (int j = 0; j < codigo.length(); j++) {
            if (j != i) menosuno += codigo[j];
        }
        
        grupo.insert(menosuno);
    }

    // Se buscan las incidencias de cada subsequencia
    for (string x: grupo)
    {
        pair<int,string> reps (0,x);
        vector<int> incSubseq = revisionCodigo(x, transmision);
        reps.first = incSubseq.size();
        subseq.push_back(reps);
    }

    pair<int,string> max (0,"null");

    // Se regresa la subsequencia más común
    for (int i = 0; i < subseq.size(); i++)
    {
        if (subseq[i].first > max.first)
        {
            max = subseq[i];
        }
        
    }

    return max;
}

// Complejidad: O(3n^2 + 3nm)
// Donde n es la longitud del codigo y m la de la tranmisión más grande
// Recibe el código a buscar en las transmisiones y despliega las incidencias y su cantidad
// Asi como la subsequencia con un caracter menos más común
void incidenciasCodigo(string codigo, vector<string> transmisiones, ofstream& check){
    check << "Código: " << codigo << endl;
    
    // Para cada transmision
    for (int i = 0; i < transmisiones.size(); i++)
    {
        // Buscamos sus incidencias del código malicioso y las desplegamos
        vector<int> incidencias = revisionCodigo(codigo,transmisiones[i]);

        check << "Transmission" << i+1 << ".txt ==> " << incidencias.size() << "  veces" << endl;
        if (incidencias.size() > 0) {
            for (int i = 0; i < incidencias.size()-1; i++) {
                check << incidencias[i] + 1;
                
                if (i != incidencias.size() - 1) {
                    check << ", ";
                }
                else {
                    check << endl;
                }
            }
            check << incidencias[incidencias.size()-1] + 1;
        }
        check << endl;
    }

    // Guardamos las incidencias de las subsecuencias del codigo menos un caracter
    vector<pair<int,string>> subseq;

    for (int i = 0; i < transmisiones.size(); i++)
    {
        subseq.push_back(encontrarSubsequencia(codigo, transmisiones[i]));
    }

    // Se busca la más comun y se despliega
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

    if (max.second != "null") {
        check << "La subsecuencia más encontrada es: " << max.second << " con " << max.first << " veces en el archivo" << endl;
        check << "Transmisión" << arch << ".txt" << endl;
    }
    else {
        check << "La subsecuencia más encontrada es: No se encontró ninguna subsecuencia" << endl;
    }
    
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