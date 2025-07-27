FROM debian:12.11 as toolchain

# Non-interactive configuration of tzdata
ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NONINTERACTIVE_SEEN true


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
RUN curl -L -o - http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.27.0.tar.xz | tar -C /usr -Jxf -
