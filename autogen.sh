#!/bin/sh

mkdir -p m4 config

aclocal -I m4
autoreconf --force --install -I config -I m4

