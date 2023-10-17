FROM ubuntu:latest

WORKDIR /app

COPY . . 

RUN apt-get update && apt-get install -y \
    build-essential \
    libsqlite3-dev \
    libncurses-dev \
    cmake \
    git \
    vim


RUN git clone https://github.com/nlohmann/json.git \
    && cd json \
    && cmake . \
    && make install \
    && cd .. \
    &&  g++ -std=c++20  src/*.cpp -o build/executable -lncurses
     
ENTRYPOINT ["./build/executable"]

