//
// Created by angel on 1/24/17.
//
#include <netinet/in.h>
#include "sys/socket.h" // depedency for
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 2024
#define ERROR_PARAMS_MESSAGAE "invalid or missing options\nusage: snc [-k] [-l] [-u] [-s source_ip_address] [hostname] port\n"

struct snc {
  int port; // required (must be last argument)
  int udp_flag;
  int listen_flag;
  int source_ip_address_flag;
  char* source_ip_address;
  char* hostname;
  //const execute(); //?
  //const snc();//?
};



int main(int argc, char* argv[]) {

  int opt;
  int num_of_optparams_specified;
  struct snc command;

  while ( (opt = getopt(argc-1, argv, "lus:")) != -1 ) {
    switch (opt) {
      case 'l':
        command.listen_flag = 1;
        ++num_of_optparams_specified;
        break;
      case 'u':
        command.udp_flag = 1;
        ++num_of_optparams_specified;
        break;
      case 's':
        command.source_ip_address_flag = 1;
        command.source_ip_address = optarg; //must be required
        num_of_optparams_specified += 2;
        // check that the syntax follows x.x.x.x
        break;
      default:
        printf(ERROR_PARAMS_MESSAGAE);
        break;
    }
  }
  // unsigned int or int
  //std::strtoul() or atoi().

  // retrieve port number (as last argument)
  command.port = atoi(argv[argc - 1]);

  // port is required
  if (command.port == NULL)
    printf(ERROR_PARAMS_MESSAGAE);

  // [hostname] argument is required if the [-l] flag is not given
  if (command.listen_flag == NULL && command.hostname == NULL )
    printf(ERROR_PARAMS_MESSAGAE);

  // [-s source_ip address] grammar is required
  if ((command.source_ip_address_flag != NULL
        && command.source_ip_address == NULL)
      || (command.source_ip_address != NULL
          && command.source_ip_address_flag == NULL)
      )
    printf(ERROR_PARAMS_MESSAGAE);



  // it is an error to use [-s source_ip_address] in conjunction with the [-l] option
  if (command.source_ip_address != NULL && command.listen_flag != NULL)
    printf(ERROR_PARAMS_MESSAGAE);



  int index;
  for(index =0; index < argc; index++)
    printf("argv[%d]:\t%s\n",index, argv[index]);


  struct sockaddr_in *client_addr;
  struct hostent *hostinfo;
  client_addr->sin_family = AF_INET; // use IPv4
  client_addr->sin_port = htons(command.port);

//    client_addr->sin_addr.s_addr = inet_addr(command.hostname);

  /**
   * This method is to detect the host
   */
  hostinfo = gethostbyname(command.hostname);
  if (hostinfo == NULL) {
    fprintf (stderr, "Unknown host %s.\n", command.hostname);
    exit (EXIT_FAILURE);
  }
  client_addr->sin_addr = *(struct in_addr *) hostinfo->h_addr;

  //  inet_aton("63.161.169.137", (client_addr->sin_addr).s_addr);


//  client_addr->sin_addr.s_addr = inet_addr(command.hostname);
  //  inet_aton("63.161.169.137", &myaddr.sin_addr.s_addr);

  int byte_type;
  if (command.udp_flag != 0)
    byte_type = SOCK_DGRAM;
  else
    byte_type = SOCK_STREAM;

  int socketfd = socket(AF_INET, byte_type, 0);
  bind(socketfd, (struct sockaddr *)client_addr, sizeof(client_addr));

  listen( socketfd, 1000 );


  /***
   * Construct buffer for server
   */
  char *req = "Test";
  char buffer[DEFAULT_BUFFER_SIZE];
  char *buffer_addr;
  ssize_t n_bytes_to_read;
  int buffer_free_space;
  buffer_addr = buffer;
  buffer_free_space = DEFAULT_BUFFER_SIZE;

  int conn_fd_passthrough = accept(socketfd, ( struct sockaddr * ) &client_addr, (socklen_t *) &client_addr);
   while ( (n_bytes_to_read = recv( conn_fd_passthrough, buffer_addr, DEFAULT_BUFFER_SIZE, 0)) > 0) {
     buffer_addr++;
     buffer_free_space -= n_bytes_to_read;
   }
  send( conn_fd_passthrough, buffer_addr, strlen(req), 0);
//  struct snc commands = parseCommands(argc,argv);
//  deploy(*commands,commands->port,commands->udp_flag);


}

//void deploy(struct snc simple_nc, unsigned port,int udp_flag) {
//
//
//
////  connect(socketfd, ,)
//
//
//  /**
//   * Base case: -l snc command (UDP server)
//   */
//  createUDPClient();
//}

/**
 * The assumption is that we are working with the [-u], [-l], [port number]
 */
void createUDPClient() {
  //
}

void parseCommands(struct snc command, int argc, char *argv[]) {


}

/**
 * If -l
 */
