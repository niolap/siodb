# Building Siodb

- [Environment Preparation](#environment-preparation)
  - [Ubuntu 18.04 LTS](#ubuntu-1804-lts)
  - [Ubuntu 20.04 LTS](#ubuntu-2004-lts)
  - [CentOS 7](#centos-7)
  - [CentOS 8](#centos-8)
  - [RHEL 7](#rhel-7)
  - [RHEL 8](#rhel-8)
- [Building Third-Party Libraries](#building-third-party-libraries)
- [System Setup (Debian, Ubuntu, CentOS, RHEL, SuSE, SLES)](#system-setup-debian-ubuntu-centos-rhel-suse-sles)
- [Compiling Siodb](#compiling-siodb)
- [Running Siodb](#running-siodb)

## Environment Preparation

### Ubuntu 18.04 LTS

Run following commands:

```shell
cd $HOME

# Required tools and libraries
sudo apt install build-essential cmake doxygen gdb graphviz gcc-8 g++-8 libboost1.65-dev \
    libboost-log1.65-dev libboost-program-options1.65-dev libcurl4-openssl-dev \
    libssl-dev openjdk-8-jdk-headless pkg-config uuid-dev clang-format-8 \
    ubuntu-dbgsym-keyring

# Set up alternatives for the clang-format
sudo update-alternatives --install /usr/bin/clang-format clang-format \
    /usr/lib/llvm-8/bin/clang-format 1
sudo update-alternatives --install /usr/bin/git-clang-format git-clang-format \
    /usr/lib/llvm-8/bin/git-clang-format 1
sudo update-alternatives --set clang-format /usr/lib/llvm-8/bin/clang-format
sudo update-alternatives --set git-clang-format /usr/lib/llvm-8/bin/git-clang-format
```

Now, proceed to the section [Building Third-Party Libraries](#building-third-party-libraries).

### Ubuntu 20.04 LTS

Run following commands:

```shell
cd $HOME

# Required tools and libraries
sudo apt install build-essential cmake doxygen gdb graphviz gcc-8 g++-8 libboost1.67-dev \
    libboost-log1.67-dev libboost-program-options1.67-dev libcurl4-openssl-dev \
    libssl-dev openjdk-8-jdk-headless pkg-config uuid-dev clang-format-8 \
    ubuntu-dbgsym-keyring

# Set up alternatives for the clang-format
sudo update-alternatives --install /usr/bin/clang-format clang-format \
    /usr/lib/llvm-8/bin/clang-format 1
sudo update-alternatives --install /usr/bin/git-clang-format git-clang-format \
    /usr/lib/llvm-8/bin/git-clang-format 1
sudo update-alternatives --set clang-format /usr/lib/llvm-8/bin/clang-format
sudo update-alternatives --set git-clang-format /usr/lib/llvm-8/bin/git-clang-format
```

Now, proceed to the section [Building Third-Party Libraries](#building-third-party-libraries).

### CentOS 7

Run following commands:

```shell
cd $HOME

# Enable additional repositories
sudo yum -y install \
    https://packages.endpoint.com/rhel/7/os/x86_64/endpoint-repo-1.8-1.x86_64.rpm \
    https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm

# Enable software collections
sudo yum -y install centos-release-scl

# Update your system
sudo yum -y update

# Uninstall any existing git
sudo yum remove git*

# Install latest git
sudo yum install git

# Install required tools and libraries
sudo yum -y install cmake3 curl gcc gcc-c++ devtoolset-8-toolchain boost169-devel libcurl-devel \
    libuuid-devel openssl-devel java-1.8.0-openjdk-headless redhat-lsb uuid-devel \
    wget zlib-devel python

sudo alternatives --install /usr/local/bin/cmake cmake /usr/bin/cmake 10 \
--slave /usr/local/bin/ctest ctest /usr/bin/ctest \
--slave /usr/local/bin/cpack cpack /usr/bin/cpack \
--slave /usr/local/bin/ccmake ccmake /usr/bin/ccmake \
--family cmake

sudo alternatives --install /usr/local/bin/cmake cmake /usr/bin/cmake3 20 \
--slave /usr/local/bin/ctest ctest /usr/bin/ctest3 \
--slave /usr/local/bin/cpack cpack /usr/bin/cpack3 \
--slave /usr/local/bin/ccmake ccmake /usr/bin/ccmake3 \
--family cmake

# Install clang-9. This one is for SLES, but works on the CentOS 7 too.
mkdir /tmp/getllvm
cd /tmp/getllvm
wget http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-sles11.3.tar.xz
tar xaf clang+llvm-9.0.0-x86_64-linux-sles11.3.tar.xz
mv -f clang+llvm-9.0.0-x86_64-linux-sles11.3  local
sudo cp -Rf local /usr
sudo ldconfig
sudo mandb
cd $HOME
rm -rf /tmp/getllvm

# Permanently tell ldconfig to scan /usr/local/lib when updating cache
sudo /bin/sh -c 'echo "/usr/local/lib" >/etc/ld.so.conf.d/usr-local-lib.conf'
sudo ldconfig
```

Install latest version of the OpenSSL 1.1.1 into `/usr/local/ssl/`.

- You can check what is latest version here: [OpenSSL Downloads](https://www.openssl.org/source/)
  (for example, latest version is 1.1.1g at the moment of writing this).
- You can get detailed installation instructions, for example, on the following web pages:
  - [How To Install OpenSSL 1.1.1d in CentOS](https://www.hostnextra.com/kb/how-to-install-openssl-1-1-1d-in-centos/)
  - [Installing OpenSSL on CentOS 7](https://cloudwafer.com/blog/installing-openssl-on-centos-7/)

Below instructions are based on the mentioned above sources:

```shell
# Define lastest OpenSSL version
export LATEST_OPENSSL_VERSION=1.1.1g

# Download, build, test install
cd /usr/local/src
sudo wget https://www.openssl.org/source/openssl-${LATEST_OPENSSL_VERSION}.tar.gz
sudo yum update -y
sudo yum install yum install perl-core libtemplate-perl zlib-devel
sudo tar xaf openssl-${LATEST_OPENSSL_VERSION}.tar.gz
cd openssl-${LATEST_OPENSSL_VERSION}
sudo ./config --prefix=/usr/local/ssl --openssldir=/usr/local/ssl shared zlib
sudo make -j4
sudo make -j4 test
sudo make -j4 install
sudo /bin/sh -c 'echo "/usr/local/ssl/lib" > /etc/ld.so.conf.d/openssl-'${LATEST_OPENSSL_VERSION}'.conf'
sudo ldconfig -v
sudo mv /bin/openssl /bin/openssl.backup
sudo /bin/sh -c 'echo "OPENSSL_PATH=/usr/local/ssl/bin" > /etc/profile.d/openssl.sh'
sudo /bin/sh -c 'echo "export OPENSSL_PATH" >> /etc/profile.d/openssl.sh'
sudo /bin/sh -c 'echo "PATH=\$PATH:\$OPENSSL_PATH" >> /etc/profile.d/openssl.sh'
sudo /bin/sh -c 'echo "export PATH" >> /etc/profile.d/openssl.sh'
sudo chmod +x /etc/profile.d/openssl.sh
source /etc/profile.d/openssl.sh
which openssl
openssl version -a
```

Now, proceed to the section [Building Third-Party Libraries](#building-third-party-libraries).

### CentOS 8

Run following commands:

```shell
cd $HOME

# Enable additional repositories
sudo yum -y install https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm

# Update your system
sudo yum -y update

# Install required tools and libraries
sudo yum -y install cmake curl gcc gcc-c++ boost-devel libcurl-devel \
          libuuid-devel openssl-devel java-1.8.0-openjdk-headless redhat-lsb \
          wget zlib-devel python2

# Install clang-9. This one is for SLES, but works on the CentOS 8 too.
mkdir /tmp/getllvm
cd /tmp/getllvm
wget http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-sles11.3.tar.xz
tar xaf clang+llvm-9.0.0-x86_64-linux-sles11.3.tar.xz
mv -f clang+llvm-9.0.0-x86_64-linux-sles11.3  local
sudo cp -Rf local /usr
sudo ldconfig
sudo mandb
cd $HOME
rm -rf /tmp/getllvm

# Permanently tell ldconfig to scan /usr/local/lib when updating cache
sudo /bin/sh -c 'echo "/usr/local/lib" >/etc/ld.so.conf.d/usr-local-lib.conf'
sudo ldconfig

# Link python 2
sudo ln -s /usr/bin/python2 /usr/bin/python
```

Now, proceed to the section [Building Third-Party Libraries](#building-third-party-libraries).

### RHEL 7

Run following commands:

```shell
cd $HOME

# Enable additional repositories
sudo yum -y install \
    https://packages.endpoint.com/rhel/7/os/x86_64/endpoint-repo-1.7-1.x86_64.rpm \
    https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm

# Enable software collections
sudo yum-config-manager --enable rhel-server-rhscl-7-rpms

# Update your system
sudo yum -y update

# Uninstall any existing git
sudo yum remove git*

# Install latest git
sudo yum install git

# Install required tools and libraries
sudo yum -y install cmake3 curl gcc gcc-c++ devtoolset-8-toolchain boost169-devel libcurl-devel \
          libuuid-devel openssl-devel java-1.8.0-openjdk-headless redhat-lsb uuid-devel \
          wget zlib-devel python

sudo alternatives --install /usr/local/bin/cmake cmake /usr/bin/cmake 10 \
--slave /usr/local/bin/ctest ctest /usr/bin/ctest \
--slave /usr/local/bin/cpack cpack /usr/bin/cpack \
--slave /usr/local/bin/ccmake ccmake /usr/bin/ccmake \
--family cmake

sudo alternatives --install /usr/local/bin/cmake cmake /usr/bin/cmake3 20 \
--slave /usr/local/bin/ctest ctest /usr/bin/ctest3 \
--slave /usr/local/bin/cpack cpack /usr/bin/cpack3 \
--slave /usr/local/bin/ccmake ccmake /usr/bin/ccmake3 \
--family cmake

# Install clang-9. This one is for SLES, but works on the CentOS 7 too.
mkdir /tmp/getllvm
cd /tmp/getllvm
wget http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-sles11.3.tar.xz
tar xaf clang+llvm-9.0.0-x86_64-linux-sles11.3.tar.xz
mv -f clang+llvm-9.0.0-x86_64-linux-sles11.3  local
sudo cp -Rf local /usr
sudo ldconfig
sudo mandb
cd $HOME
rm -rf /tmp/getllvm

# Permanently tell ldconfig to scan /usr/local/lib when updating cache
sudo /bin/sh -c 'echo "/usr/local/lib" >/etc/ld.so.conf.d/usr-local-lib.conf'
sudo ldconfig
```

Install latest version of the OpenSSL 1.1.1 into `/usr/local/ssl/`.

- You can check what is latest version here: [OpenSSL Downloads](https://www.openssl.org/source/)
  (for example, latest version is 1.1.1g at the moment of writing this).
- You can get detailed installation instructions, for example, on the following web pages:
  - [How To Install OpenSSL 1.1.1d in CentOS](https://www.hostnextra.com/kb/how-to-install-openssl-1-1-1d-in-centos/)
  - [Installing OpenSSL on CentOS 7](https://cloudwafer.com/blog/installing-openssl-on-centos-7/)

Below instructions are based on the mentioned above sources:

```shell
# Define lastest OpenSSL version
export LATEST_OPENSSL_VERSION=1.1.1g

# Download, build, test install
cd /usr/local/src
sudo wget https://www.openssl.org/source/openssl-${LATEST_OPENSSL_VERSION}.tar.gz
sudo yum update -y
sudo yum install yum install perl-core libtemplate-perl zlib-devel
sudo tar xaf openssl-${LATEST_OPENSSL_VERSION}.tar.gz
cd openssl-${LATEST_OPENSSL_VERSION}
sudo ./config --prefix=/usr/local/ssl --openssldir=/usr/local/ssl shared zlib
sudo make -j4
sudo make -j4 test
sudo make -j4 install
sudo /bin/sh -c 'echo "/usr/local/ssl/lib" > /etc/ld.so.conf.d/openssl-'${LATEST_OPENSSL_VERSION}'.conf'
sudo ldconfig -v
sudo mv /bin/openssl /bin/openssl.backup
sudo /bin/sh -c 'echo "OPENSSL_PATH=/usr/local/ssl/bin" > /etc/profile.d/openssl.sh'
sudo /bin/sh -c 'echo "export OPENSSL_PATH" >> /etc/profile.d/openssl.sh'
sudo /bin/sh -c 'echo "PATH=$PATH:$OPENSSL_PATH" >> /etc/profile.d/openssl.sh'
sudo /bin/sh -c 'echo "export $PATH" >> /etc/profile.d/openssl.sh'
sudo chmod +x /etc/profile.d/openssl.sh
source /etc/profile.d/openssl.sh
which openssl
openssl version -a
```

Now, proceed to the section [Building Third-Party Libraries](#building-third-party-libraries).

### RHEL 8

Run following commands:

```shell
cd $HOME

# Enable additional repositories
sudo yum -y install https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm

# Update your system
sudo yum -y update

# Install required tools and libraries
sudo yum -y install cmake curl gcc gcc-c++ boost-devel libcurl-devel \
          libuuid-devel openssl-devel java-1.8.0-openjdk-headless redhat-lsb \
          wget zlib-devel python2

# Install clang-9. This one is for SLES, but works on the CentOS 8 too.
mkdir /tmp/getllvm
cd /tmp/getllvm
wget http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-sles11.3.tar.xz
tar xaf clang+llvm-9.0.0-x86_64-linux-sles11.3.tar.xz
mv -f clang+llvm-9.0.0-x86_64-linux-sles11.3  local
sudo cp -Rf local /usr
sudo ldconfig
sudo mandb
cd $HOME
rm -rf /tmp/getllvm

# Permanently tell ldconfig to scan /usr/local/lib when updating cache
sudo /bin/sh -c 'echo "/usr/local/lib" >/etc/ld.so.conf.d/usr-local-lib.conf'
sudo ldconfig

# Link python 2
sudo ln -s /usr/bin/python2 /usr/bin/python
```

Now, proceed to the section [Building Third-Party Libraries](#building-third-party-libraries).

## Building Third-Party Libraries

Change current directory to the root of siodb Git repository and execute following commands:

**NOTE:** Adjust make parameter `-j4` to number of CPUs/cores available on the your build machine.

```shell

# Clone Siodb repository or your Siodb fork, like this:
mkdir ~/projects
cd ~/projects
git clone git@github.com:siodb/siodb.git

# Enter repository root directory
cd siodb

# CentOS 7/RHEL 7 ONLY: Enable devtoolset-8
scl enable devtoolset-8 bash

# Install source code formatting hook for git
cp -fv tools/git_hooks/siodb-clang-format.hook .git/hooks/pre-commit

# Build and install Google Protobuf library
cd thirdparty/protobuf
tar xaf protobuf-all-3.11.4.tar.xz
cd protobuf-3.11.4
./configure
make -j4
sudo make install
sudo ldconfig
cd ../..

# Build and install Utf8cpp library
cd utf8cpp
tar xaf utfcpp-3.1.tar.xz
cd utfcpp-3.1
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DUTF8_TESTS=Off ..
make -j4
sudo make install
sudo ldconfig
cd ../../..

# Install ANTLR4 executables
cd antlr4
sudo ./install.sh
cd ..

# Build and isntall ANTLR4 runtime library
cd antlr4-cpp-runtime
tar xaf antlr4-cpp-runtime-4.8-source.tar.xz
cd antlr4-cpp-runtime-4.8-source
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
sudo make install
sudo ldconfig
cd ../../..

# Build and install Google Test library
cd googletest
tar xaf googletest-release-1.8.1.tar.xz
cd googletest-release-1.8.1/googlemock/scripts
./fuse_gmock_files.py gtest-gmock-1.8.1
sudo cp -Rf gtest-gmock-1.8.1 /usr/local/include
cd ../../../..

# Build and install date library
cd date
tar xaf date-20190911.tar.xz
cd date-20190911
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DUSE_SYSTEM_TZ_DB=ON \
      -DENABLE_DATE_TESTING=OFF -DBUILD_SHARED_LIBS=ON ..
make -j4
sudo make install
cd ../../..

# Build and install xxHash library
cd xxHash
tar xaf xxHash-0.7.2.tar.xz
cd xxHash-0.7.2
make -j4
sudo make install
sudo ldconfig
cd ../..

# Build and install message compiler
cd ../tools/message_compiler
make -j4
sudo make install
cd ../..
```

## System Setup (Debian, Ubuntu, CentOS, RHEL, SuSE, SLES)

One-time system setup commands (with explanation):

```shell
sudo useradd -M siodb
sudo usermod -L siodb

sudo mkdir -p /var/lib/siodb
sudo chown -R siodb:siodb /var/lib/siodb
sudo chmod -R 0770 /var/lib/siodb

sudo mkdir -p /var/log/siodb
sudo chown -R siodb:siodb /var/log/siodb
sudo chmod -R 0770 /var/log/siodb

sudo mkdir -p /run/siodb/
sudo chown -R siodb:siodb /run/siodb
sudo chmod -R 0770 /run/siodb

sudo mkdir -p /run/lock/siodb/
sudo chown -R siodb:siodb /run/lock/siodb
sudo chmod -R 0770 /run/lock/siodb

sudo /bin/sh -c 'echo "d /run/siodb 0770 siodb siodb -" >/usr/lib/tmpfiles.d/siodb.conf'
sudo /bin/sh -c 'echo "d /run/lock/siodb 0770 siodb siodb -" >>/usr/lib/tmpfiles.d/siodb.conf'
sudo /bin/sh -c 'echo "siodb hard nofile 524288" >>/etc/security/limits.conf'
sudo /bin/sh -c 'echo "siodb soft nofile 524288" >>/etc/security/limits.conf'
```

To allow your own user run siodb:

```shell
sudo usermod -a -G siodb `whoami`
sudo /bin/sh -c 'echo "'`whoami`' hard nofile 524288" >>/etc/security/limits.conf'
sudo /bin/sh -c 'echo "'`whoami`' soft nofile 524288" >>/etc/security/limits.conf'
```

and re-login.

## Compiling Siodb

- Build debug version: `make -j4`. Build outputs will appear in the directory `debug/bin`.
- Build release version: `make -j4 DEBUG=0`. Build outputs will appear in the directory `release/bin`.
- List all available build commands: `make help`.

**NOTE:** Adjust `-jN` option in the above `make` commands according to available number of CPUs and memory
  on the build host.

## Running Siodb

Before running Siodb, you need to create some instance configuration files:

- `/etc/siodb/instances/<configuration-name>/config` - instance configuration options file.
- `/etc/siodb/instances/<configuration-name>/system_db_key` - encryption key for the system database.
  Note that this file must be present even if encryption of the system database is set to the `none`
  (in such case it can be just zero length).

These files owner must be owned by the user `siodb` and group `siodb`. File mode must be `0400` or `0600`.
Debug build of Siodb also allows members of owner group to have access to these files.
There are some sample configurations in the directory `config` that may be used as starting point.

- Run Siodb server: `siodb --instance <configuration-name>`
- Run Siodb client in the admin mode: `siocli --admin <configuration-name>`
