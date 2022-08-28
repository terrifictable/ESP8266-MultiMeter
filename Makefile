all:
	docker-compose build --no-cache
	docker-compose up --force-recreate

go_rebuild:
	docker-compose build go
	docker-compose restart go
