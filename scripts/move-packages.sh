#!/bin/bash

PACKAGES_PROJECT_DIR=$1
if [ ! -d "$PACKAGES_PROJECT_DIR/apt" ]; then
  echo "Wrong packages project path."
  exit 1
fi

MECHANIC_PROJECT_DIR=$(cd `dirname $0`/..; pwd)
if [ ! -d "$MECHANIC_PROJECT_DIR/target/" ]; then
  echo "No mechanic build dir target/ found."
  exit 1
fi

mkdir -p $PACKAGES_PROJECT_DIR/bash-installer/unstable/
for i in $MECHANIC_PROJECT_DIR/target/bash-installer*.sh; do
  cp $i $PACKAGES_PROJECT_DIR/bash-installer/unstable/
  rm -f $PACKAGES_PROJECT_DIR/bash-installer/unstable/latest.sh
  ln -s $(basename $i) $PACKAGES_PROJECT_DIR/bash-installer/unstable/latest.sh
done
cp $MECHANIC_PROJECT_DIR/target/*ubuntu-yakkety*.deb $PACKAGES_PROJECT_DIR/apt/ubuntu/dists/yakkety/unstable/binary-amd64/
cp $MECHANIC_PROJECT_DIR/target/*ubuntu-yakkety*.deb $PACKAGES_PROJECT_DIR/apt/ubuntu/dists/yakkety/unstable/binary-i386/
cp $MECHANIC_PROJECT_DIR/target/*ubuntu-xenial*.deb $PACKAGES_PROJECT_DIR/apt/ubuntu/dists/xenial/unstable/binary-amd64/
cp $MECHANIC_PROJECT_DIR/target/*ubuntu-xenial*.deb $PACKAGES_PROJECT_DIR/apt/ubuntu/dists/xenial/unstable/binary-i386/
cp $MECHANIC_PROJECT_DIR/target/*wheezy*.deb $PACKAGES_PROJECT_DIR/apt/debian/dists/wheezy/unstable/binary-amd64/
cp $MECHANIC_PROJECT_DIR/target/*wheezy*.deb $PACKAGES_PROJECT_DIR/apt/debian/dists/wheezy/unstable/binary-i386/
cp $MECHANIC_PROJECT_DIR/target/*jessie*.deb $PACKAGES_PROJECT_DIR/apt/debian/dists/jessie/unstable/binary-amd64/
cp $MECHANIC_PROJECT_DIR/target/*jessie*.deb $PACKAGES_PROJECT_DIR/apt/debian/dists/jessie/unstable/binary-i386/
cp $MECHANIC_PROJECT_DIR/target/*sid*.deb $PACKAGES_PROJECT_DIR/apt/debian/dists/sid/unstable/binary-amd64/
cp $MECHANIC_PROJECT_DIR/target/*sid*.deb $PACKAGES_PROJECT_DIR/apt/debian/dists/sid/unstable/binary-i386/

