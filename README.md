# TCP & HTTP Echo Server

This project is a simple server written in C++ that can operate in two modes:

- **Echo Mode**: echoes any received message line by line (ideal for testing with Telnet).
- **HTTP Mode**: responds to HTTP GET requests with a plain-text message showing the requested path (testable in a web browser).

---

## Files

- `main.cpp` — parses command-line arguments and starts the server.
- `server.h` — declares the `startServer()` function.
- `server.cpp` — handles socket setup and connection logic for both echo and HTTP modes.
- `Makefile` — compiles the project.

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

   
   