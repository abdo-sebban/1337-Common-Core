*This project has been created as part of the 42 curriculum by asebban, hfalati, mouait-e.*

# ft_irc

> A lightweight Internet Relay Chat (IRC) server written in **C++98**, implementing the core features of the IRC protocol using non-blocking sockets and an event-driven architecture.

---

# Description

## Overview

**ft_irc** is a network programming project from the 42 curriculum. The objective is to build an **Internet Relay Chat (IRC) server** capable of communicating with any standard IRC client implementing the IRC protocol.

The server is designed to handle multiple simultaneous clients using a **single `poll()` event loop**, ensuring efficient, non-blocking communication. It allows users to authenticate, register nicknames, join channels, exchange private messages, and manage channels through IRC commands.

Unlike a complete IRC network, this project focuses on implementing a **single standalone IRC server**.

---

## Goals

The project aims to develop a solid understanding of:

- TCP/IP networking
- Socket programming
- Event-driven architectures
- Non-blocking I/O
- Client-server communication
- The IRC protocol
- Object-Oriented Programming in C++98

---

# Features

## User Features

- Password authentication
- Nickname registration
- Username registration
- Multiple simultaneous client connections
- Private messaging
- Channel messaging
- Creation and management of multiple channels

## Channel Operator Features

- `KICK`
- `INVITE`
- `TOPIC`
- `MODE`

Supported channel modes:

| Mode | Description |
| :--: | ----------- |
| `+i` | Invite-only channel |
| `+t` | Only channel operators may change the topic |
| `+k` | Password-protected channel |
| `+o` | Grant or remove operator privileges |
| `+l` | Set or remove the maximum number of users |

---

# Project Architecture

The server follows an **event-driven architecture** based on non-blocking sockets and a single `poll()` event loop.

```text
                   IRC Client
                        │
                        │ TCP/IP
                        ▼
                +----------------+
                |   IRC Server   |
                +----------------+
                        │
        ┌───────────────┼───────────────┐
        │               │               │
        ▼               ▼               ▼
 Client Manager   Channel Manager   Command Parser
        │               │               │
        └───────────────┼───────────────┘
                        ▼
                  poll() Event Loop
```

### Main Components

### Server

- Creates and configures the listening socket.
- Accepts incoming client connections.
- Executes the main event loop using `poll()`.

### Client

Stores information about each connected user:

- Socket descriptor
- Authentication state
- Nickname
- Username

### Channel

Stores:

- Connected members
- Channel operators
- Topic
- Channel modes
- Password
- User limit

### Command Parser

Responsible for:

- Parsing IRC commands
- Validating command syntax
- Dispatching commands to their corresponding handlers

---

# Instructions

## Requirements

- macOS or Linux
- C++98 compatible compiler
- Make
- An IRC client

---

## Compilation

Compile the project:

```bash
make
```

Remove object files:

```bash
make clean
```

Remove object files and executable:

```bash
make fclean
```

Recompile everything:

```bash
make re
```

---

## Running the Server

```bash
./ircserv <port> <password>
```

Example:

```bash
./ircserv 6667 password42
```

Arguments:

| Argument   | Description                                 |
| --------   | ------------------------------------------- |
| `port`     | Listening port used by the server           |
| `password` | Password required for client authentication |

---

## Connecting with an IRC Client

The server can be used with any IRC client that follows the IRC protocol.

The reference client used during development was **LimeChat**.

Example connection:

| Field    |   Value      |
|-------   |------------- |
| Server   | `127.0.0.1`  |
| Port     | `6667`       |
| Password | `password42` |

After connecting, join a channel:

```text
/join #general
```

---

## Testing with Netcat

Although **Netcat (`nc`)** is **not** an IRC client, it is extremely useful for debugging the server and validating command parsing.

Connect:

```bash
nc -C 127.0.0.1 6667
```

Example session:

```text
    PASS password42
    NICK alice
    USER username hostname servername realname
    JOIN #general
    PRIVMSG #general :Hello everyone!
```

Netcat was primarily used to test:

- Command parsing
- Partial packet reception
- Server responses
- Error handling

---

# Usage Examples

Authenticate:

```text
PASS password42
```

Choose a nickname:

```text
NICK alice
```

Register a username:

```text
USER username hostname servername realname
```

Join a channel:

```text
JOIN #general
```

Send a private message:

```text
PRIVMSG bob :Hello!
```

Send a message to a channel:

```text
PRIVMSG #general :Hello everyone!
```

---

# Bonus: IRC Bot

A simple IRC bot is provided as a bonus feature. The bot connects to the running `ircserv` server over TCP like any regular IRC client, joins a channel, and greets anyone who joins that channel.

## Building the Bot

The bot is **not** built by default. Build it with the `bonus` target:

```bash
make bonus
```

This produces a second executable named `ircbot`.

## Running the Bot

Start your server first, then launch the bot:

```bash
./ircserv 6667 password42
./ircbot 127.0.0.1 6667 password42 greeter '#general'
```

Arguments:

| Argument    | Description                              |
| ----------- | ---------------------------------------- |
| `host`      | Server hostname or IP (e.g. `127.0.0.1`) |
| `port`      | Port the IRC server is listening on      |
| `password`  | Same connection password used by the server |
| `nickname`  | Nickname the bot will register           |
| `#channel`  | Channel the bot will join and watch      |

## Behavior

- The bot authenticates with `PASS`, registers with `NICK`/`USER`, and joins the given channel.
- It answers server `PING` requests automatically.
- Whenever another client joins the channel, the bot sends:

```text
PRIVMSG #channel :Hi <nick>!
```

The bot ignores its own join so it never greets itself.

---

# Supported Commands

| Command  | Description                       |
|----------|-----------------------------------|
| `PASS`   | Authenticate with the server      |
| `NICK`   | Set the client's nickname         |
| `USER`   | Register the client               |
| `JOIN`   | Join a channel                    |
| `PRIVMSG`| Send a private or channel message |
| `KICK`   | Remove a user from a channel      |
| `INVITE` | Invite a user to a channel        |
| `TOPIC`  | View or change a channel topic    |
| `MODE`   | Modify channel modes              |

---

# Technical Choices

## Why `poll()`?

The project specification requires the server to handle multiple clients simultaneously without using threads or `fork()`.

Using `poll()` makes it possible to monitor every socket inside a single event loop while keeping all operations non-blocking and efficient.

---

## Why TCP?

IRC is built on top of the TCP protocol because it provides:

- Reliable communication
- Ordered packet delivery
- Error detection
- Stream-oriented communication

---

## Why C++98?

The project strictly follows the requirements of the 42 curriculum and is fully compatible with the **C++98** standard.

---

# Testing

The server was tested using:

- LimeChat (reference IRC client)
- Netcat (`nc`) for parser and protocol testing
- Multiple simultaneous clients
- Invalid IRC commands
- Authentication failures
- Partial packet reception
- Channel operator commands
- Multiple channel scenarios

---

# Resources

## Official IRC Documentation

- RFC 1459 — Internet Relay Chat Protocol
- RFC 2810 — IRC Architecture
- RFC 2811 — Channel Management
- RFC 2812 — Client Protocol

## Networking

- Beej's Guide to Network Programming
- Linux `socket(2)` Manual
- Linux `poll(2)` Manual

## C++

- ISO C++98 Standard
- cppreference (C++98)

## Additional References

- IRC protocol documentation
- Socket programming tutorials
- Event-driven networking articles

---

## AI Usage

Artificial Intelligence was used as a learning and productivity tool in accordance with the **42 AI Guidelines**.

AI assisted with:

- Understanding the IRC protocol.
- Explaining socket programming concepts.
- Learning the behavior of non-blocking sockets and the `poll()` system call.
- Clarifying C++98 language features.
- Reviewing and improving documentation.
- Brainstorming software architecture and testing strategies.

Every AI-generated explanation or suggestion was reviewed, tested, adapted, and fully understood by the project authors before being incorporated into the project. All implementation decisions, debugging, testing, and validation were completed by the team.

---

# Authors

- asebban
- hfalati
- mouait-e

---

# License

This project was developed as part of the **42 School** curriculum and is intended for educational purposes.