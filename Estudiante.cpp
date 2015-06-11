#include "Estudiante.h"

Estudiante::Estudiante()
{
    //ctor
    this->cedula = '\0';
    this->nombre = '\0';
    this->apellido = '\0';
    this->telefono = '\0';
    this->fechaNacimiento = NULL;
    this->creditos = 0;
    this->email = '\0';
    this->carreras = NULL;
    this->aprobadas= NULL;
    this->inscripciones = NULL;

}

Estudiante::Estudiante(String cedula,String nombre,String apellido, String telefono, Date* fechaNacimiento, Integer creditos,
                        String email, IDictionary* carreras, ICollection* aprobadas, ICollection* inscripciones)
{
    this->cedula = cedula;
    this->nombre = nombre;
    this->apellido = apellido;
    this->telefono = telefono;
    this->fechaNacimiento = fechaNacimiento;
    this->creditos = creditos;
    this->email = email;
    this->carreras = carreras;
    this->aprobadas = aprobadas;
    this->inscripciones = inscripciones;
}

Estudiante::Estudiante(const Estudiante &e)
{
    this->cedula = e.cedula;
    this->nombre = e.nombre;
    this->apellido = e.apellido;
    this->telefono = e.telefono;
    this->fechaNacimiento = e.fechaNacimiento;
    this->creditos = e.creditos;
    this->email = e.email;
    //falta carreras, aprobadas e inscripciones pero es al pedo xq no lo vamos a usar
}

String Estudiante::getCedula()
{
    return this->cedula;
}

String Estudiante::getNombre()
{
    return this->nombre;
}

String Estudiante::getApellido()
{
    return this->apellido;
}

String Estudiante::getTelefono()
{
    return this->telefono;
}

Date* Estudiante::getFechaNacimiento()
{
    return this->fechaNacimiento;
}

Integer Estudiante::getCreditos()
{
    return this->creditos;
}

String Estudiante::getEmail()
{
    return this->email;
}

List* Estudiante::getCarreras()
{
    return this->carreras;
}

List* Estudiante::getAprobadas()
{
    return this->aprobadas;
}

void Estudiante::setCedula(String cedula)
{
    this->cedula = cedula;
}

void Estudiante::setNombre(String nombre)
{
    this->nombre = nombre;
}

void Estudiante::setApellido(String apellido)
{
    this->apellido = apellido;
}

void Estudiante::setTelefono(String telefono)
{
    this->telefono = telefono;
}

void Estudiante::setFechaNacimiento(Date* fechaNacimiento)
{
    this->fechaNacimiento = fechaNacimiento;
}

void Estudiante::setCreditos(Integer creditos)
{
    this->creditos = creditos;
}

void Estudiante::setEmail(String email)
{
    this->email = email;
}

DataEstudiante* Estudiante::getDataEstudiante()
{
    try
    {
        //Se obtiene la coleccion de DataAsignatura
        List* dataAsignaturas = new List();
        ListIterator * lIt = this->aprobadas->getIterator();
        while(lIt.hasCurrent())
        {
            Aprobacion *apro;
            if( (apro = dynamic_cast<Aprobacion*> (lIt.current())) != NULL )
            {
                dataAsignaturas->add(apro->getDataAsignatura());
            } else
            {
                throw std::invalid_argument("Estudiante -> El objeto no es de la clase Aprobacion.");
            }

            lIt.next();
        }
        delete lIt;

        //Se obtiene la coleccion de DataCarrera
        List* dataCarreras = new List();
        IIterator * It = this->carreras->getElemIterator();
        while(It.hasCurrent())
        {
            Carrera *carr;
            if( (carr = dynamic_cast<Carrera*> (It.current())) != NULL )
            {
                dataCarreras->add(carr->getDataCarrera());
            } else
            {
                throw std::invalid_argument("Estudiante -> El objeto no es de la clase Carrera.");
            }

            It.next();
        }
        delete It;

        DataEstudiante* dataEstudiante = new DataEstudiante(this->cedula, this->nombre, this->apellido, this->telefono, this->fechaNacimiento, this->creditos, dataAsignaturas, dataCarreras);

        return dataEstudiante;

    }
    catch(const std::invalid_argument &e)
    {
    	throw std::invalid_argument(e.what());
    }

}

bool Estudiante::EstNoInscripto(int numExpediente)
{
    try
    {
        bool res;
        ListIterator * lIt = this->inscripciones->getIterator();
        while(lIt.hasCurrent())
        {
            Inscripcion *insc;
            if( (insc = dynamic_cast<Inscripcion*> (lIt.current())) != NULL )
            {
                res = insc->EstInscripto(numExpediente);
            } else
            {
                throw std::invalid_argument("Estudiante -> El objeto no es de la clase Inscripcion.");
            }

            lIt.next();
        }
        delete lIt;

        return res;
    }
    catch(const std::invalid_argument &e)
    {
    	throw std::invalid_argument(e.what());
    }
}

void AsociarInscripcion (Inscripcion *insc)
{
    this->inscripciones->add(insc);
}

DataDatosEstudiante* Estudiante::getDataDatosEstudiante()
{
    try
    {
        //Se obtiene la coleccion de DataAprobada
        List* dataAprobadas = new List();
        ListIterator * lIt = this->aprobadas->getIterator();
        while(lIt.hasCurrent())
        {
            Aprobacion *apro;
            if( (apro = dynamic_cast<Aprobacion*> (lIt.current())) != NULL )
            {
                dataAprobadas->add(apro->getDataAprobada());
            } else
            {
                throw std::invalid_argument("Estudiante -> El objeto no es de la clase Aprobacion.");
            }

            lIt.next();
        }
        delete lIt;

        List* dataOfertasEmpresas = new List();
        ListIterator * lIt = this->inscripciones->getIterator();
        while(lIt.hasCurrent())
        {
            Inscripcion *insc;
            if( (insc = dynamic_cast<Inscripcion*> (lIt.current())) != NULL )
            {
                dataOfertasEmpresas->add(insc->getDataOfertaLaboral());
            } else
            {
                throw std::invalid_argument("Estudiante -> El objeto no es de la clase Inscripcion.");
            }

            lIt.next();
        }

        delete lIt;

        DataDatosEstudiante* datosEstudiante = new DataDatosEstudiante(dataAprobadas, dataOfertasEmpresas,
                                                                       "Faltaria una coleccion de DataEmpresa de acuerdo al DataType");

        return datosEstudiante;
    }
    catch(const std::invalid_argument &e)
    {
    	throw std::invalid_argument(e.what());
    }
}

void enviarMail(){

}

Estudiante::~Estudiante()
{
    //dtor
}
