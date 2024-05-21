FROM ubuntu:20.04

ENV TZ Asia/Ho_Chi_Minh

LABEL authors="dungpt"

ENV DEBIAN_FRONTEND noninteractive

ENV DISPLAY :99

ENV QT_PATH /opt/Qt
ENV QT_DESKTOP $QT_PATH/${QT_VERSION}/gcc_64

ENV PATH /usr/lib/ccache:$QT_DESKTOP/bin:$PATH

# Install dependencies
COPY tools/setup/install-dependencies.sh /tmp/qt/
RUN /tmp/qt/install-dependencies.sh

# Install Qt
COPY tools/setup/install-qt.sh /tmp/qt/
RUN /tmp/qt/install-qt.sh

# Reconfigure locale
RUN locale-gen en_US.UTF-8 && dpkg-reconfigure locales

WORKDIR /project/build
# CMD cmake -S /project/source -B . -G Ninja -DCMAKE_BUILD_TYPE=Debug; \
# 	cmake --build . --target all --config Debug ; \
# 	cmake --install . --config Debug