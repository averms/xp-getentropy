#!/bin/bash
set -euo pipefail
shopt -s inherit_errexit

lint() {
    run-clang-tidy -quiet source/ test/
}

optdebug-clang() {
    CC=clang CC_LD=lld meson setup \
        -Dbuildtype=debugoptimized -Doptimization=g -Dwarning_level=3 \
        "b-${FUNCNAME[0]}"
    ln -sf "b-${FUNCNAME[0]}"/compile_commands.json .
}

optdebug() {
    CC=gcc CC_LD=lld meson setup \
        -Dbuildtype=debugoptimized -Doptimization=g -Dwarning_level=3 \
        "b-${FUNCNAME[0]}"
}

debug() {
    CC=gcc CC_LD=lld meson setup \
        -Dbuildtype=debug -Ddebug=false -Dc_args='-ggdb3' -Dwarning_level=3 \
        "b-${FUNCNAME[0]}"
}

asan() {
    CC=clang CC_LD=lld meson setup \
        -Dbuildtype=debug -Doptimization=1 -Dwarning_level=3 \
        -Db_sanitize=address -Db_lundef=false \
        "b-${FUNCNAME[0]}"
}

dist() {
    local version="$(git describe --always)"
    if [[ -z $version ]]; then
        return 1
    fi
    version="${version/#v/}"
    local folder="xp-getentropy-$version"
    local tarball="$folder.tar"
    local zstdcmd="zstd --rm -q -12 -T0"

    git archive --verbose --prefix "${folder}/" --output "$tarball" @
    $zstdcmd "$tarball"
}

predist() {
    cd "$MESON_DIST_ROOT"
    rm -r .appveyor/ .builds/
}

help() { h; }
h() {
    echo "$0 <task> [args]"
    echo "Tasks:"
    compgen -A function | sed -E '/default/d' | cat -n
}

TIMEFORMAT="Task completed in %3lR"
time "${@:-debug}"
