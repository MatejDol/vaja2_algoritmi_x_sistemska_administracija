FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y g++ && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY vaja.cpp .

RUN g++ -O2 -o vaja vaja.cpp

ENTRYPOINT ["./vaja"]
