FROM ubuntu:20.04

ENV TZ Asia/Ho_Chi_Minh

LABEL authors="dungpt"

ENV DEBIAN_FRONTEND noninteractive

ENV QT_PATH /opt/Qt
ENV QT_VERSION 5.15.2
ENV QT_DESKTOP $QT_PATH/${QT_VERSION}/gcc_64

ENV PATH /usr/lib/ccache:$QT_DESKTOP/bin:$PATH

# Install dependencies
COPY tools/setup/install-dependencies.sh /tmp/qt/
RUN chmod +x /tmp/qt/install-dependencies.sh
RUN /tmp/qt/install-dependencies.sh

# Install Qt
COPY tools/setup/install-qt.sh /tmp/qt/
RUN chmod +x /tmp/qt/install-qt.sh
RUN /tmp/qt/install-qt.sh

# Reconfigure locale
RUN locale-gen en_US.UTF-8 && dpkg-reconfigure locales

WORKDIR /usr/project
COPY . /usr/project/