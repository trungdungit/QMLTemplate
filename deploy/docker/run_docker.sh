#! /usr/bin/env bash

#Run this from root directory

set -e

docker build --file ./deploy/docker/Dockerfile -t template-qml-docker:1.0 .
docker run -it --name qml-docker --network=host --env DISPLAY=$DISPLAY --privileged \
    --volume="$HOME/.Xauthority:/root/.Xauthority:rw" -v /tmp/.X11-unix:/tmp/.X11-unix --rm template-qml-docker:1.0 /bin/bash