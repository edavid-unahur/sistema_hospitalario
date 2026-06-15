#pragma once
#include <iostream>
#include <string>
#include "Hospital.h"
#include <vector>


class Ciudad {
    private:
        std::string codigoCiudad;
        std::string nombre;
        std::string pais;
        std::vector<Hospital*> hospitales;
    public:
        Ciudad(
            std::string codigoCiudad, 
            std::string nombre, 
            std::string pais
        );
        
        //Metodos gettes
        std::string getCodigoCiudad() const;
        std::string getNombre() const;
        std::string getPais() const;

        //Metodos de logica
        void agregarHospital(Hospital* hospital);
        void mostrarInformacion();
        void mostrarHospitales();   
};  
        