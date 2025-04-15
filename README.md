# TCP & HTTP Echo Server

This project is a simple server written in C++ that can operate in two modes:

- **Echo Mode**: echoes any received message line by line (ideal for testing with Telnet).
- **HTTP Mode**: responds to HTTP GET requests with a plain-text message showing the requested path (testable in a web browser).

---

## Files

- main.cpp — Parses command-line arguments and starts the server.

- server.h — Declares the startServer() function.

- server.cpp — Sets up the server socket, accepts incoming connections, and spawns threads.

- client_handler.h — Declares the handleClient() function that processes individual client connections.

- client_handler.cpp — Handles the logic for echoing messages or serving HTTP responses to connected clients.

- Makefile — Compiles all source files and links the project.

---

## How to Compile

```bash
make

## How to Run
1. Echo Mode (Telnet):
   ./echo -p 2345 -v
   Open another terminal and connect via telnet:
   telnet 127.0.0.1 2345
   Example:
      Trying 127.0.0.1...
      Connected to localhost.
      Escape character is '^]'.
      hi
      hi
      bye
      bye



2. HTTP Mode (Web Browser):
   ./echo -p 2345 -v --http
   Then open your browser:
   http://localhost:2345/foo

3. For Multi threading:
   run: ./echo -p 2345 -v
   in first terminal: 
      telnet 127.0.0.1 2345
         Trying 127.0.0.1...
         Connected to localhost.
         Escape character is '^]'.
         I am Client1!
         I am Client1!
    in second terminal:
      telnet 127.0.0.1 2345
         Trying 127.0.0.1...
         Connected to localhost.
         Escape character is '^]'.
         I am client 2!
         I am client 2!

OUTPUT: ./echo -p 2345 -v
   Echo Server listening on port 2345...
   [INFO] Waiting for data...
   [INFO] Waiting for data...
   [ECHO] Received: I am Client1!
   [INFO] Waiting for data...
   [ECHO] Received: I am client 2!
   [INFO] Waiting for data...
      

   