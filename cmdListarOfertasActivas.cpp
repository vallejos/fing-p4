#include "cmdListarOfertasActivas.h"
#include <iostream>
#include <string>
#include "interfaces/ICollection.h"
#include "IOfertaLaboralController.h"
#include "interfaces/IIterator.h"
#include "DataOfertaLaboral.h"
#include "Rango.h"
#include "Date.h"
#include "IDictionary.h"

using namespace std;

cmdListarOfertasActivas::cmdListarOfertasActivas()
{
    //ctor
}

void cmdListarOfertasActivas::ejecutarComando()
{
    Fabrica* fab = Fabrica::getInstance();
    IOfertaLaboralController* cOferta = fab->getIOfertaLaboralController();
    int cantInscriptos;

    try
    {
        //MOSTRAR OFERTAS LABORALES ACTIVAS
        IDictionary* dataOfertasActivas = cOferta->MostrarOfertasActivas();
        cout << "Lista de Ofertas Laborales Activas:\n";
        IIterator *it = dataOfertasActivas->getIterator();
        while (it->hasCurrent())
        {
            DataOfertaLaboral *dOferta;
            if ( (dOferta = dynamic_cast<DataOfertaLaboral*> (it->getCurrent())) != NULL )
            {
            //calculo la cantidad de inscriptos
                IIterator *it2 = dOferta->getInscripciones()->getIterator();
                cantInscriptos = 0;
                while (it2->hasCurrent())
                {
                    cantInscriptos ++;
                    it2->next();
                }
                delete it2;
            //IMPRIMO LOS DATOS QUE INDICA ELCASO DE USO
                cout << "---------------" + "\n" + "NOMBRE: " + dOferta->getTitulo() + "\n" + ", EMPRESA:" + dOferta->getSeccion()->getSucursal()->getEmpresa()->getRut() + "\n" + ", UBICACION:" + dOferta->getSeccion()->getSucursal()->getDireccion() + "\n" + ", CANTIDAD DE INSCRIPTOS: " + cantInscriptos + "\n" + ", RANGO SALARIAL:" + dOferta->getRangoSalarial()->getSueldoMinimo() + " - " + dOferta->getRangoSalarial()->getSueldoMaximo() + "\n" + ", CANTIDAD DE PLAZAS:" + dOferta->cantidadPuestosNecesarios() + "\n";
            } else
            {
                throw std::invalid_argument("cmdListarOfertasActivas -> El objeto no es de la clase DataOfertaLaboral.");
            }
            it->next();
        }
        delete it;
    }
    catch(const std::invalid_argument &e)
    {
        cout << e.what();
    }
}

cmdListarOfertasActivas::~cmdListarOfertasActivas()
{
    //dtor
}
