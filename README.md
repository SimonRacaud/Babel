
# Requirements

## Qt install (linux)

- Ubuntu
```shell 
sudo apt-get install qtbase5-dev qtdeclarative5-dev
```
- Fedora 34
```shell 
sudo dnf install qt5-qtbase-devel
```

# Build on linux
```shell
mkdir build && (cd build && conan install .. --build=missing && cmake .. && make)
```
