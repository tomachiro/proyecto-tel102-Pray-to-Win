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
        std::cout<<"\033[37mSelecciona una opción\033[0m\n\033[36m1.Jugar\t\t2.Configuración\n3.Reglas\t4.Salir\033[0m"<<std::endl;
        std::cin>>opcion;

    switch (opcion)
            {
            case '1':
                jugar(jugadores,n,config);
                break;
            case '2':
                std::system("clear");
                std::cout<<"\033[36mEsta es la configuración del sistema\033[0m\n";
                configuraciones(config);
                stop_system();
                break;
            case '3':
                reglas();
                break;
            case '4':
                std::system("clear");
                std::cout<<"\033[31msaliendo....\033[0m\n";
                stop_system();
                std::system("clear");
                return 1;
                break;
            
            default:
                std::system("clear");
                std::cout<<"\033[33mopción no valida\033[0m\n";
                stop_system();
                break;
            } 
        }while(ejecucion);

        return 1;

}
