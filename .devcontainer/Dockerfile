# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.202.5/containers/debian/.devcontainer/base.Dockerfile

FROM debian:experimental

#** [Optional] Uncomment this section to install additional packages. **
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends sudo git ca-certificates build-essential pkg-config liburing-dev cmake gdb libfmt-dev \
    && apt-get -y install libboost-dev -t experimental

# Create the gitpod user. UID must be 33333.
RUN useradd -l -u 33333 -G sudo -md /home/gitpod -s /bin/bash -p gitpod gitpod \
    && echo gitpod ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/gitpod \
    && chmod 0440 /etc/sudoers.d/gitpod

USER gitpod
