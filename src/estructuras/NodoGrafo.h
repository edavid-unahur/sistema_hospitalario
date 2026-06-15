#ifndef NODO_GRAFO_H
#define NODO_GRAFO_H

class NodoGrafo {
private:
    int id;
    int hospitalCodigo;
public:    
    NodoGrafo(int id, int codigo) {
        this->id = id;
        this->hospitalCodigo = codigo;
    }

    int getId() {
        return id;
    };
    int getCodigoHospital(){
        return hospitalCodigo;
    };
};

#endif