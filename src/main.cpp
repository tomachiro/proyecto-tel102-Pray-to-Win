#include "funciones.hpp"
int main(void){
    bool ejecucion = true;

    
    jugador* jugadores[2];
    //lo que a;adi

    
    
    configuracion config; 

    do{
        char opcion;
        int n = 0;
        std::system("clear");
        std::cout<<"Selecciona una opción\n1.Jugar\t\t2.Configuración\n3.Reglas\t4.Salir"<<std::endl;
        std::cin>>opcion;

    switch (opcion)
            {
            case '1':
                jugar(jugadores,n,config);
                break;
            case '2':
                std::system("clear");
                std::cout<<"Esta es la configuración del sistema\n";
                configuraciones(config);
                stop_system();
                break;
            case '3':
                reglas();
                break;
            case '4':
                std::system("clear");
                std::cout<<"saliendo....\n";
                stop_system();
                std::system("clear");
                return 1;
                break;
            
            default:
                std::system("clear");
                std::cout<<"opción no valida\n";
                stop_system();
                break;
            } 
        }while(ejecucion);

        return 1;

}
