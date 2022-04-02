
# Requirements

## Conan install

```shell
pip install --user conan
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan config set general.revisions_enabled=1
```

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
or
```shell
./build.sh re
```