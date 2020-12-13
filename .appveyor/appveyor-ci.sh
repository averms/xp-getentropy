#!/bin/bash
set -euo pipefail

(
    curl -fsSLO 'https://git.sr.ht/~mcf/samurai/archive/1.1.tar.gz'
    tar -xf 1.1.tar.gz
    cd samurai-1.1
    make -j 3
    install -D samu /usr/local/bin/ninja
)

git clone --quiet --branch "$APPVEYOR_REPO_BRANCH" 'https://github.com/a-vrma/xp-getentropy.git'
cd xp-getentropy

curl -fsSLO 'https://raw.githubusercontent.com/a-vrma/getmeson.py/b5289de387f84d00b9f06043e49bd3fcd28ece87/getmeson_3.5.py'
python3.8 getmeson_3.5.py
./meson-portable/meson.py setup b-release
cd b-release
ninja -v

./t_basic
./t_more
