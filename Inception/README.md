*This project has been created as part of the 42 curriculum by asebban.*

# Inception

## Description

Inception is a system administration project from the 42 curriculum focused on Docker and containerized infrastructures.

The goal of the project is to build a secure multi-container environment using:

- NGINX with TLSv1.2/TLSv1.3
- WordPress with PHP-FPM
- MariaDB
- Docker volumes
- Docker networks

Each service runs inside its own dedicated container and is managed using Docker Compose.

---

## Project Structure

```text
inception/
├── Makefile
├── README.md
└── srcs/
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        ├── nginx/
        └── wordpress/
```

---

# Instructions

## Requirements

- Docker
- Docker Compose
- Make
- Linux Virtual Machine

## Run the project

Build and start all services:

```bash
make
```

Stop containers:

```bash
make down
```

Remove containers, images, and volumes:

```bash
make fclean
```

---

# Docker Usage

Docker is used to isolate each service inside its own container.

Advantages:

- Lightweight virtualization
- Service isolation
- Easy deployment
- Reproducible environments

A custom Docker network allows communication between containers.

Docker named volumes are used to persist:

- WordPress files
- MariaDB database

---

# Comparisons

## Virtual Machines vs Docker

### Virtual Machines
- Full operating system
- Heavy resource usage
- Slower startup

### Docker
- Shares host kernel
- Lightweight
- Faster startup

---

## Secrets vs Environment Variables

### Environment Variables
- Easy configuration
- Less secure for sensitive data

### Docker Secrets
- Better security
- Recommended for credentials

---

## Docker Network vs Host Network

### Docker Network
- Isolated communication
- Better security

### Host Network
- Direct access to host network
- Less isolation

---

## Docker Volumes vs Bind Mounts

### Docker Volumes
- Managed by Docker
- Better portability

### Bind Mounts
- Direct host filesystem access
- Useful during development

---

# Resources

- https://docs.docker.com/
- https://docs.docker.com/compose/
- https://nginx.org/en/docs/
- https://mariadb.org/documentation/
- https://wordpress.org/documentation/

---

# AI Usage

AI tools were used for:

- Learning Docker concepts

