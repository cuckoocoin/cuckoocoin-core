#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/cuckoocoin.png
ICON_DST=../../src/qt/res/icons/cuckoocoin.ico
convert ${ICON_SRC} -resize 16x16 cuckoocoin-16.png
convert ${ICON_SRC} -resize 32x32 cuckoocoin-32.png
convert ${ICON_SRC} -resize 48x48 cuckoocoin-48.png
convert cuckoocoin-16.png cuckoocoin-32.png cuckoocoin-48.png ${ICON_DST}

