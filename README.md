# QML Template Project

*QMLTemplate* is template for QML application

## Directory structure
```
+---cmake
|   |   Git.cmake                   # CMake contains Git information
|   |   Qt5Configuration.cmake      # CMake contains Qt information
|   \
|---config                          # Json config
|---deploy
|   |   docker                      # Dockerfile
|   |   jenkins                     # Jenkinsfile
|   |   linux
|   |   windows
|   \
|---libs                            # Submodule or 3rdParty
|---resources                       # Image, icon, font, ...
|---src                             # Main source
|---test                            # Test module
|---tools
|---translations                    # Qt translation .ts file
|---UI                              # QML file
```

## How to run

### Build source (Qt)
```
qmake ../qmltemplate.pro
make -j
```

### Build source (CMake, Ubuntu)
```
cmake -DQt5_DIR=$$PWD/Qt/5.15.2/gcc_64/lib/cmake/Qt5 -DQML_BUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug ..
make -j
```

### Build source (CMake, Windows)
```
cmake -DQt5_DIR=$$PWD/Qt/5.15.2/gcc_64/lib/cmake/Qt5 -DQML_BUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CC_COMPILER=gcc -DCMAKE_MAKE_PROGRAM=mingw32-make -G "MinGW Makefiles" ..
make -j
```

### Run on docker
```
# Config Xauth (need to test further)
xhost +local:docker
xauth add ${HOST}:0 . $(xxd -l 16 -p /dev/urandom)
xauth list > .Xauthority
xauth generate :0 . trusted

docker build --file ./deploy/docker/Dockerfile -t template-qml-docker:1.0 .
docker run -it --network=host --env DISPLAY=$DISPLAY --privileged --volume="$HOME/.Xauthority:/root/.Xauthority:rw" -v /tmp/.X11-unix:/tmp/.X11-unix --rm template-qml-docker:1.0 /bin/bash
```

## TODO
[TODO](TODO.md)
