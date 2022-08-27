FROM golang:1.18

RUN mkdir /app
COPY . /app
WORKDIR /app

# pre-copy/cache go.mod for pre-downloading dependencies and only redownloading them in subsequent builds if they change
COPY go.mod go.sum ./
RUN go mod download && go mod verify

COPY . .
RUN go build -o /app/go_executable

CMD [ "/app/go_executable" ]
