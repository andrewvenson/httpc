#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define HTTP_1_1 "HTTP/1.1 "

void get_date(char *time_buffer, size_t time_buffer_size) {
  time_t now = time(NULL);
  struct tm *local = localtime(&now);
  strftime(time_buffer, time_buffer_size, "Date: %a, %d %b %Y %H:%M:%S %Z",
           local);
}

void get_response(char *response) {
  char time_buffer[200];
  char response_content_size[21];
  char response_date[87];
  ;
  char response_content_length[20];
  char response_status[] = "HTTP/1.1 200 OK\r\n";
  char response_content_type[] = "Content-Type: text/html; charset=UTF-8\r\n";
  char response_message[] = "<h1>get</h1>\n";

  memset(time_buffer, 0, sizeof(time_buffer));
  memset(response_content_size, 0, sizeof(response_content_size));
  memset(response_content_length, 0, sizeof(response_content_length));

  get_date(time_buffer, sizeof(time_buffer));
  strcat(response_date, time_buffer);
  strcat(response_date, "\r\n");
  sprintf(response_content_size, "%lu", strlen(response_message));
  strcat(response_content_length, "Content-Length: ");
  strcat(response_content_length, response_content_size);
  strcat(response_content_length, "\r\n");

  strcat(response, response_status);
  strcat(response, response_date);
  strcat(response, response_content_type);
  strcat(response, response_content_length);
  strcat(response, "\r\n");
  strcat(response, response_message);
}

void put_response(char *response) {
  char time_buffer[200];
  char response_content_size[21];
  char response_date[87];
  ;
  char response_content_length[20];
  char response_status[] = "HTTP/1.1 200 OK\r\n";
  char response_content_type[] = "Content-Type: text/html; charset=UTF-8\r\n";
  char response_message[] = "<h1>put</h1>\n";

  memset(time_buffer, 0, sizeof(time_buffer));
  memset(response_content_size, 0, sizeof(response_content_size));
  memset(response_content_length, 0, sizeof(response_content_length));

  get_date(time_buffer, sizeof(time_buffer));
  strcat(response_date, time_buffer);
  strcat(response_date, "\r\n");
  sprintf(response_content_size, "%lu", strlen(response_message));
  strcat(response_content_length, "Content-Length: ");
  strcat(response_content_length, response_content_size);
  strcat(response_content_length, "\r\n");

  strcat(response, response_status);
  strcat(response, response_date);
  strcat(response, response_content_type);
  strcat(response, response_content_length);
  strcat(response, "\r\n");
  strcat(response, response_message);
}

void post_response(char *response) {
  char time_buffer[200];
  char response_content_size[21];
  char response_date[87];
  ;
  char response_content_length[20];
  char response_status[] = "HTTP/1.1 200 OK\r\n";
  char response_content_type[] = "Content-Type: text/html; charset=UTF-8\r\n";
  char response_message[] = "<h1>post</h1>\n";

  memset(time_buffer, 0, sizeof(time_buffer));
  memset(response_content_size, 0, sizeof(response_content_size));
  memset(response_content_length, 0, sizeof(response_content_length));

  get_date(time_buffer, sizeof(time_buffer));
  strcat(response_date, time_buffer);
  strcat(response_date, "\r\n");
  sprintf(response_content_size, "%lu", strlen(response_message));
  strcat(response_content_length, "Content-Length: ");
  strcat(response_content_length, response_content_size);
  strcat(response_content_length, "\r\n");

  strcat(response, response_status);
  strcat(response, response_date);
  strcat(response, response_content_type);
  strcat(response, response_content_length);
  strcat(response, "\r\n");
  strcat(response, response_message);
}

void method_now_allowed_response(char *response) {
  char time_buffer[200];
  char response_content_size[21];
  char response_date[87];
  ;
  char response_content_length[20];
  char response_allowed[] = "Allowed: GET, POST, PUT\r\n";
  char response_status[] = "HTTP/1.1 405 Method Not Allowed\r\n";
  char response_content_type[] = "Content-Type: text/html; charset=UTF-8\r\n";
  char response_message[] = "Method Not Allowed\n";

  memset(time_buffer, 0, sizeof(time_buffer));
  memset(response_content_size, 0, sizeof(response_content_size));
  memset(response_content_length, 0, sizeof(response_content_length));
  memset(response_allowed, 0, sizeof(response_allowed));

  get_date(time_buffer, sizeof(time_buffer));
  strcat(response_date, time_buffer);
  strcat(response_date, "\r\n");
  sprintf(response_content_size, "%lu", strlen(response_message));
  strcat(response_content_length, "Content-Length: ");
  strcat(response_content_length, response_content_size);
  strcat(response_content_length, "\r\n");

  strcat(response, response_status);
  strcat(response, response_allowed);
  strcat(response, response_date);
  strcat(response, response_content_type);
  strcat(response, response_content_length);
  strcat(response, "\r\n");
  strcat(response, response_message);
}

int main() {
  int server_fd;
  int client_fd = -1;
  int opt;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_fd_len = sizeof(client_fd);
  char buffer[BUFFER_SIZE];

  // create socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_fd < 0) {
    perror("Error occurred during server socket creation\n");
    return -1;
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("Error occurred during setting of socket options\n");
    close(server_fd);
    return -1;
  }

  // clear server address memory
  memset(&server_addr, 0, sizeof(server_addr));

  // define server address options
  server_addr.sin_port = htons(PORT);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // bind socket
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("Error occurred during binding of address\n");
    close(server_fd);
    return -1;
  }

  // listen for connections
  if (listen(server_fd, 5) < 0) {
    perror("Error occurred during listening for connections\n");
    close(server_fd);
    return -1;
  }

  printf("Server listening on PORT: %d...\n", PORT);

  while (1) {
    // accept connections
    client_fd =
        accept(server_fd, (struct sockaddr *)&client_addr, &client_fd_len);
    if (client_fd < 0) {
      perror("Error occurred during accepting connection\n");
      continue;
    }

    int bytes_received;
    while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
      char method[5];
      char content_length[21];
      char http_response[2048];
      memset(http_response, 0, sizeof(http_response));

      buffer[bytes_received] = '\0';

      printf("%s\n", buffer);

      for (int x = 0; x < 5; x++) {
        if (buffer[x] == ' ') {
          method[x] = '\0';
          break;
        }
        method[x] = buffer[x];
      }

      void (*get_method_response)(char *response);

      if (strcmp("GET", method) == 0) {
        get_method_response = get_response;
      } else if (strcmp("POST", method) == 0) {
        get_method_response = post_response;
      } else if (strcmp("PUT", method) == 0) {
        get_method_response = put_response;
      } else {
        get_method_response = method_now_allowed_response;
      }

      get_method_response(http_response);
      printf("%s\n", http_response);
      send(client_fd, http_response, strlen(http_response), 0);
    }

    if (bytes_received == 0) {
      printf("client successfully disconnected\n");
    } else if (bytes_received < 0) {
      perror("Recv failed!\n");
    }

    close(client_fd);
  }

  printf("Closing server on port: %d\n", PORT);
  close(server_fd);
  return 0;
}
