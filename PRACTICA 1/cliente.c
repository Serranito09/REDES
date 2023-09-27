#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>
#include<sys/time.h>
#include<sys/socket.h>

/* --------------------------------------------------------------------------------------
 
 Se conecta al servidor y le devuelve el n�mero de puerto y la direcci�n IP que ha usado para conectarse al servicio.

---------------------------------------------------------------------------------------- */
 




int main ( )
{
    /*
    */

	struct timeval timeout;
	fd_set lectura;
	int salida;
	char cadena[60];

	//Inicializar la estructua timeval
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	
	//Inicializar los conjuntos fd_set
	FD_ZERO(&lectura);
	FD_SET(0,&lectura);





    /*
    */
   int opcion;
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer para datos 
	-----------------------------------------------------*/
	int Socket_Cliente;
	char buffer[1024];
   
   	/* -----------------------------------------------------
   		Informaci\ufffdn del Servidor
   	-----------------------------------------------------*/
   	struct sockaddr_in Servidor;  
   	socklen_t Longitud_Servidor;
  
  
   	/* --------------------------------------------------
			Se abre el socket cliente
	---------------------------------------------------*/
	Socket_Cliente = socket (AF_INET, SOCK_DGRAM, 0);
	if (Socket_Cliente == -1)
	{
		printf ("No se puede abrir el socket cliente\n");
    		exit (-1);	
	}

 	/*---------------------------------------------------------------------
		Necesitamos una estructura con la informaci\ufffdn del Servidor
		para poder solicitarle un servicio.
   	----------------------------------------------------------------------*/
	Servidor.sin_family = AF_INET;
	Servidor.sin_port = htons(2000);
	Servidor.sin_addr.s_addr =  inet_addr("127.0.0.1");
  	Longitud_Servidor = sizeof(Servidor);
	

	/*------------------------------------------------------------------------
		Completamos buffer con la petici�n
	------------------------------------------------------------------------ */
 printf("Elija una opcion:\n");
    printf("1. Dia\n");
    printf("2. Hora\n");
    printf("3. Dia y hora\n");
    scanf("%d", &opcion);
    switch (opcion)
    {
    case 1:
            strcpy(buffer, "DAY");
        break;
    case 2:
            strcpy(buffer, "TIME");
        break;
    case 3:
            strcpy(buffer, "DAYTIME");
        break;
    }

   	
	/*-----------------------------------------------------------------------
		Se env\ufffda mensaje al Servidor
	-----------------------------------------------------------------------*/
    for(int i=0;i<3;i++){
        printf("entro");
	int enviado = sendto (Socket_Cliente, buffer, sizeof(buffer), 0,
			(struct sockaddr *) &Servidor, Longitud_Servidor);
   
   	if (enviado < 0)
    	{
		printf("Error al solicitar el servicio\n");
	}
     else{
            salida = select(Socket_Cliente+1,&lectura,NULL,NULL,&timeout);
	
	if(salida == -1)
	{
		printf("Se ha producido un error en select\n");
	}
     if(i==3)
	{
        printf("Se ha agotado el tiempo\n");
        exit(-1);	
    }
    else{
    
    
    
   
		/*----------------------------------------------------------------------
			Esperamos la respuesta del Servidor
		----------------------------------------------------------------------- */ 
		bzero(buffer, sizeof(buffer));
		int recibido = recvfrom (Socket_Cliente, buffer, sizeof(buffer), 0,
			(struct sockaddr *) &Servidor, &Longitud_Servidor);
			
   		if (recibido > 0){
      			printf ("%s\n", buffer);
                i=4;
        }
		
    }
     }
    }
		
	close(Socket_Cliente);

	return 0;
}
