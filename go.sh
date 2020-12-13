#!/bin/bash
set -euo pipefail
shopt -s inherit_errexit

optdebug-clang() {
    CC=clang CC_LD=lld meson setup \
        -Ddebug=false -Dc_args='-ggdb3' -Doptimization=g -Dwarning_level=3 \
        "b-${FUNCNAME[0]}"
    ln -sf "b-${FUNCNAME[0]}"/compile_commands.json .
}

optdebug() {
    CC=gcc CC_LD=gold meson setup \
        -Ddebug=false -Dc_args='-ggdb3' -Doptimization=g -Dwarning_level=3 \
        "b-${FUNCNAME[0]}"
}

debug() {
    CC=gcc CC_LD=gold meson setup \
        -Dbuildtype=debug -Dwarning_level=3 \
        "b-${FUNCNAME[0]}"
}

asan() {
    CC=clang CC_LD=lld meson setup \
        -Ddebug=false -Doptimization=1 -Dwarning_level=3 \
        -Db_sanitize=address -Db_lundef=false \
        "b-${FUNCNAME[0]}"
}

tar() {
    local version="$(git describe --always --abbrev=20)"
    if [[ -z $version ]]; then
        return 1
    fi
    version="${version/#v/}"
    local folder="xp-getentropy-$version"
    local tarball="$folder.tar"
    local zstdcmd="zstd --rm --force -q -10 -T0"

    git archive --verbose --prefix "${folder}/" --output "$tarball" @
    $zstdcmd "$tarball"
}

help() { h; }
h() {
    echo "$0 <task> [args]"
    echo "Tasks:"
    compgen -A function | sed -E '/default/d' | cat -n
}

default() {
    debug "$@"
}

TIMEFORMAT="Task completed in %3lR"
time ${@:-default}
