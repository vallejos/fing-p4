#ifndef MANEJADOROFERTALABORAL_H
#define MANEJADOROFERTALABORAL_H

#include "OfertaLaboral.h"
#include"ICollection.h"
#include "IDictionary.h"
#include <string>

using namespace std;

class ManejadorOfertaLaboral
{
    public:
		static ManejadorOfertaLaboral *getInstance();
		ICollection *getDataOfertaLaboral(); // Set DataOfertaLaboral
		ICollection *getAllDataOfertaLaboral(); // Set DataOfertaLaboral
		OfertaLaboral *SeleccionarOferta(string numExpediente);
		void addOfertaManejador(OfertaLaboral *ol);
		void DarDeBajaLlamado(OfertaLaboral *ol);
		destroyManejadorOfertaLaboral();

    private:
        ~ManejadorOfertaLaboral();
    	ManejadorOfertaLaboral();
        static ManejadorOfertaLaboral *instance;
        IDictionary *ofertasLaborales; //Pseudoatributo para representar la asociación con una coleccion de OfertaLaboral
};

#endif // MANEJADOROFERTALABORAL_H
