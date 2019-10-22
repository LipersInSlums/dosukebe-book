#!/bin/bash
rm -rf build
mkdir -p build
cp -r ./book/ ./build
find chapters -name *.re | sed -E 's#chapters/(.*)/(.*)#cp chapters/\1/\2 build/book/\1-\2#g' | bash
cd build/book
review-pdfmaker ./config.yml
mv ./book.pdf ../../
