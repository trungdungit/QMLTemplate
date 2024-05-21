#! /usr/bin/env bash

#Run this from root directory

set -e

docker build --file ./deploy/docker/Dockerfile -t template-docker .
docker run --cap-add SYS_ADMIN --device /dev/fuse --rm -v ${PWD}:/project/source -v ${PWD}/build:/project/build template-docker