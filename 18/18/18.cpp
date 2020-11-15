
// Nombre y Apellidos
//Mario Blanco TAIS13

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <deque>

class sumidero {
private:
    std::vector<std::vector<bool>> g;
    std::vector<bool> candidatos;

    bool sumid;
    int vertice;
    void leeGrafo(int m) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            std::cin >> a >> b;
            g[a][b] = true;
        }
    }
public:
    
    sumidero(int n, int m) :g(n,std::vector<bool>(m)), candidatos(n,true),sumid(false){
        if (n == 1) {
            sumid = true;
            vertice = 0;
            return;
        }
        leeGrafo(m);
        int candidato = 0;
        int tachados = 0;
        bool posibleSum = false;
        while (!posibleSum && tachados < n) {
            int gEntrada = 0;
            bool aborta = false;
 
            for (int i = 0; i < n && !aborta; ++i) {
                
                if (i != candidato) {
                    if (g[i][candidato]) {
                        ++gEntrada;
                        if (candidatos[i]) {
                            candidatos[i] = false;
                            ++tachados;
                            
                        }
                    }
                    else {
                        candidatos[candidato] = false;
                        ++tachados;
                        candidato = i;
                        aborta = true;
                    }
                } 

            }
            if (gEntrada == n - 1) posibleSum = true;

        }

        //comprobamos si el unico candidato tiene grado de salida =0
        if (posibleSum) {
            bool gSalida = false;
            for (int i = 0; !gSalida && i < n; ++i) {
                if (g[candidato][i]) gSalida = true;
            }

            if (!gSalida) {
                sumid = true;
                vertice = candidato;
            }
        }
    }
    void escribeSol() {
        if (sumid) std::cout << "SI " << vertice;
        else std::cout << "NO";
        std::cout << '\n';
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n, m;
    std::cin >> n >> m;
   if (!std::cin)  // fin de la entrada
      return false;
   sumidero t(n, m);
   t.escribeSol();
   
   // escribir sol
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
