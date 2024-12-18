#! /usr/bin/env bash

set -e

apt-get update -y --quiet

#Build Tools
DEBIAN_FRONTEND=noninteractive apt-get -y --quiet --no-install-recommends install \
	build-essential \
	ccache \
	cmake \
	cppcheck \
	file \
	g++ \
	gcc \
	gdb \
	git \
	libfuse2 \
	make \
	ninja-build \
	rsync \
    binutils \
    locales \
    patchelf \
	vim \
	mesa-common-dev \
	libglu1-mesa-dev \
	libdbus-1-3 \
	fontconfig \

#Qt Required
DEBIAN_FRONTEND=noninteractive apt-get -y --quiet --no-install-recommends install \
	libxcb-xinerama0 \
    libxkbcommon-x11-0 \
    libxcb-cursor0 \
	libxcb-keysyms1 \
	libxcb-icccm4 \
	libxcb-shape0 \
	libxcb-randr0-dev \
	libdrm-dev \

DEBIAN_FRONTEND=noninteractive rm -rf /var/lib/apt/lists/*
