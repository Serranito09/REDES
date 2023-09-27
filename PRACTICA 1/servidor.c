#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<time.h>
#include <locale.h>


/* --------------------------------------------------------------------------------------

 * El servidor que ofrece es devolver la dirección IP y el puerto del cliente que se conectó.

---------------------------------------------------------------------------------------- */

 
int main ()
{

    /*

    
    */

   	time_t tiempo;
	struct tm * stTm;
	char cadena [80];


	tiempo = time(NULL);

	setlocale(LC_ALL,"");
	
	stTm = localtime(&tiempo);
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int Socket_Servidor;
	struct sockaddr_in Servidor;
	char buffer[1024];
	
	

	/* -----------------------------------------------------
   		Informaci\ufffdn del Cliente
   	-----------------------------------------------------*/
   	struct sockaddr_in Cliente;
	socklen_t Longitud_Cliente;
	char cliente_ip[INET_ADDRSTRLEN];
	int cliente_puerto;
	
	/* --------------------------------------------------
		Se abre el socket Servidor
	---------------------------------------------------*/
	Socket_Servidor = socket (AF_INET, SOCK_DGRAM, 0);
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket servidor\n");
		exit (-1);	
	}

	/* ------------------------------------------------------------------
		Se rellenan los campos de la estructura servidor, necesaria
		para la llamada a la funcion bind().
	-------------------------------------------------------------------*/
	Servidor.sin_family = AF_INET;
	Servidor.sin_port = htons(2000);
	Servidor.sin_addr.s_addr = htonl(INADDR_ANY); 

	if (bind (Socket_Servidor, (struct sockaddr *)&Servidor, sizeof (Servidor)) == -1)
	{
		close (Socket_Servidor);
		exit (-1);
	}
	

  	/*---------------------------------------------------------------------
		Del cliente solamente necesitamos el tamaño de su estructura, el 
		resto de información (familia, puerto, ip), la obtendremos 
		nos la proporcionará el propio método recvfrom, cuando
		recibamos la llamada de un cliente.
   	----------------------------------------------------------------------*/
	Longitud_Cliente = sizeof (Cliente);

   	
	/*-----------------------------------------------------------------------
		El servidor espera continuamente los mensajes de los clientes
	------------------------------------------------------------------------ */
	while (1)
	{
    		/* -----------------------------------------------------------------
			Esperamos la llamada de alg\ufffdn cliente
		-------------------------------------------------------------------*/
		bzero(buffer, sizeof(buffer));
      		int recibido = recvfrom (Socket_Servidor, buffer, sizeof(buffer), 0,
			(struct sockaddr *) &Cliente, &Longitud_Cliente);



		/* -----------------------------------------------------------------
			Comprobamos si hemos recibido alguna informaci\ufffdn 
		-------------------------------------------------------------------*/
		if (recibido > 0)
		{
			/*-----------------------------------------------------------------
				Identificamos la petición 
			------------------------------------------------------------------*/
			if(strcmp(buffer, "DAY") == 0)			{
				
                strftime(cadena,80,"%A, %d de %B", stTm);
			
      
				// Responder al cliente con la dirección IP y el puerto
        			snprintf(buffer, sizeof(buffer), "%s\n",cadena);

        			int enviado = sendto(Socket_Servidor, buffer, sizeof(buffer), 0, (struct sockaddr*)&Cliente,Longitud_Cliente);

				if(enviado == -1){
					printf("Error en el envío de la respuesta\n");
                }
      		
			}
            else if(strcmp(buffer, "TIME") == 0){
				
                strftime(cadena,80,"%H:%M:%S", stTm);
			
      
				// Responder al cliente con la dirección IP y el puerto
        			snprintf(buffer, sizeof(buffer), "%s\n",cadena);

        			int enviado = sendto(Socket_Servidor, buffer, sizeof(buffer), 0, (struct sockaddr*)&Cliente,Longitud_Cliente);

				if(enviado == -1){
					printf("Error en el envío de la respuesta\n");
                }
      		
			}
            else if(strcmp(buffer, "DAYTIME") == 0){
		
                strftime(cadena,80,"%A, %d de %B %H:%M:%S", stTm);
			
      
				// Responder al cliente con la dirección IP y el puerto
        			snprintf(buffer, sizeof(buffer), "%s\n",cadena);

        			int enviado = sendto(Socket_Servidor, buffer, sizeof(buffer), 0, (struct sockaddr*)&Cliente,Longitud_Cliente);

				if(enviado == -1){
					printf("Error en el envío de la respuesta\n");
                }
      		
			}
			else
			{
				//Respondemos que no reconocemos la petición
				strcpy(buffer, "Comando no reconocido\n");
			
				// Enviar la respuesta al cliente
        			int enviado = sendto(Socket_Servidor, buffer, sizeof(buffer), 0, (struct sockaddr*)&Cliente, 				Longitud_Cliente);

				if(enviado == -1)
					printf("Error en el envío de la respuesta\n");
    

			}

    		}
		else
			printf("Error en la recepción del mensaje\n");

	}

	 
	close(Socket_Servidor);


	return 0;

}
