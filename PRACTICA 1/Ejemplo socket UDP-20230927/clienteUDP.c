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

/* --------------------------------------------------------------------------------------
 
 Se conecta al servidor y le devuelve el nœmero de puerto y la direcci—n IP que ha usado para conectarse al servicio.

---------------------------------------------------------------------------------------- */
 
int main ( )
{
  
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
		Completamos buffer con la petici—n
	------------------------------------------------------------------------ */
   	strcpy(buffer, "ObtenerPuertoIP");

   	
	/*-----------------------------------------------------------------------
		Se env\ufffda mensaje al Servidor
	-----------------------------------------------------------------------*/
	int enviado = sendto (Socket_Cliente, buffer, sizeof(buffer), 0,
			(struct sockaddr *) &Servidor, Longitud_Servidor);
   
   	if (enviado < 0)
    	{
		printf("Error al solicitar el servicio\n");
	}
    	else
	{
   
		/*----------------------------------------------------------------------
			Esperamos la respuesta del Servidor
		----------------------------------------------------------------------- */ 
		bzero(buffer, sizeof(buffer));
		int recibido = recvfrom (Socket_Cliente, buffer, sizeof(buffer), 0,
			(struct sockaddr *) &Servidor, &Longitud_Servidor);
			
   		if (recibido > 0)
      			printf ("Respuesta %s\n", buffer);
   		else
      			printf ("Error al recibir la respuesta del servidor\n");
		
	}
		
	close(Socket_Cliente);

	return 0;
}
