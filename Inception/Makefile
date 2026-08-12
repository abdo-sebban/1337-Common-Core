all:
	mkdir -p $(HOME)/data/mariadb
	mkdir -p $(HOME)/data/wordpress
	docker compose -f srcs/docker-compose.yml up -d --build

down:
	docker compose -f srcs/docker-compose.yml down

clean:
	docker compose -f srcs/docker-compose.yml down --rmi all
	docker system prune -af

fclean:
	docker compose -f srcs/docker-compose.yml down --rmi all -v
	docker volume prune -f
	sudo rm -rf $(HOME)/data

re: fclean all

.PHONY: re
