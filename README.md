
# Requirements

## Qt install (linux)
```shell 
sudo apt-get install qtbase5-dev qtdeclarative5-dev
```

# Build on linux
```shell
mkdir build && cd build && conan install .. --build missing && cmake .. && make && ../Babel
```
