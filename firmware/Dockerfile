FROM debian:12.11 AS toolchain

ENV DEBIAN_FRONTEND=noninteractive DEBCONF_NONINTERACTIVE_SEEN=true
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    rm -f /etc/apt/apt.conf.d/docker-clean && \
    echo 'Binary::apt::APT::Keep-Downloaded-Packages "true";' > /etc/apt/apt.conf.d/keep-cache && \
    apt-get update && \
    apt-get install -y \
    autoconf \
    automake \
    bison \
    bzip2 \
    curl \
    flex \
    g++ \
    gawk \
    gcc \
    git \
    gperf \
    help2man \
    libncurses5-dev \
    libstdc++6 \
    libtool \
    libtool-bin \
    make \
    meson \
    ninja-build \
    patch \
    python3-dev \
    rsync \
    texinfo \
    unzip \
    xz-utils \
    ;
WORKDIR /crosstool-ng-src
RUN curl -L -o - http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.27.0.tar.xz | tar --strip-components=1 -C /crosstool-ng-src -Jxf - && \
    ./bootstrap && \
    ./configure --prefix=/usr/local && \
    make -j`nproc` && \
    make install

WORKDIR /avr-toolchain-build
ENV CT_ALLOW_BUILD_AS_ROOT_SURE=y CT_EXPERIMENTAL=y CT_ALLOW_BUILD_AS_ROOT=y
RUN --mount=type=bind,source=./docker/avr-gcc.config,target=/avr-toolchain-config/avr-gcc.config \
    cp /avr-toolchain-config/avr-gcc.config .config && \
    ct-ng build

FROM debian:12.11 AS build
COPY --from=toolchain /avr-toolchain /usr/local/
ENV DEBIAN_FRONTEND=noninteractive DEBCONF_NONINTERACTIVE_SEEN=true
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    rm -f /etc/apt/apt.conf.d/docker-clean && \
    echo 'Binary::apt::APT::Keep-Downloaded-Packages "true";' > /etc/apt/apt.conf.d/keep-cache && \
    apt-get update && \
    apt-get install -y \
    python3-pip \
    python3-venv \
    ;
RUN --mount=type=cache,mode=0755,target=/root/.cache/pip \
    python3 -m venv $HOME/.venv/venv  && \
    . $HOME/.venv/venv/bin/activate && \
    python3 -m pip install meson ninja
WORKDIR /src
RUN --mount=type=bind,source=./src/,target=.,rw=true \
    . $HOME/.venv/venv/bin/activate && \
    meson setup --cross-file cross.ini build/ && \
    ninja -C build/ -j $(nproc)
