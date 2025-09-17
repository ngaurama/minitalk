# minitalk

A client-server communication program implemented in C, part of the 42 Common Core curriculum.
This project demonstrates interprocess communication using UNIX signals, handling messages between multiple clients and a single server in real time.

---

## Features
### Mandatory:
#### Server
+ Prints its PID upon launch.
+ Receives messages from clients via SIGUSR1 and SIGUSR2 signals.
+ Prints received messages immediately, without delay.
+ Can handle messages from multiple clients consecutively without restarting.

#### Client
+ Takes two parameters:
  - Server PID
  - Message string to send

Sends the specified string to the server using signals only.
(Only SIGUSR1 and SIGUSR2 are allowed for communication.)

### Bonus
+ Server sends acknowledgment signals back to clients for each received message.
+ Support for Unicode characters.
---

## Project Structure

```
├── client.c       # Sends messages to the server
├── server.c       # Receives messages and prints them
├── libft/         # Libft
├── Makefile
└── README.md
```

---

## Installation

### Clone and build
```bash
git clone https://github.com/ngaurama/minitalk.git
cd minitalk
make
```
This will generate the executables:
+ `server`
+ `client`

▶ Usage

Start the server:
```
./server
```
+ The server prints its PID, e.g.:
  + `Server PID: 12345`

Send a message from the client:
```
./client <SERVER_PID> "Hello World!"
```
The server will immediately print:
+ `Hello World!`

---

### Learning Outcomes

Through this project, I gained experience with:
+ Interprocess communication using UNIX signals
+ Encoding and decoding bits to transmit messages via signals
+ Handling real-time message reception without delays
+ Managing multiple clients in a single-server architecture
---
## Author
+ Nitai Gauramani
  - 42 Paris – Common Core project <br>

![Nitai's GitHub stats](https://github-readme-stats.vercel.app/api?username=ngaurama&show_icons=true&theme=transparent)
