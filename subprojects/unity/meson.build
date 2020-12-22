#
# build script written by : Michael Brockus.
# github repo author: Mike Karlesky, Mark VanderVoord, Greg Williams.
#
# license: MIT
#

project('unity', 'c',
    license: 'MIT',
    version: '2.5.1-git',
    meson_version: '>=0.56.0',
    default_options: ['c_std=c89']
)

add_project_arguments('-DUNITY_OUTPUT_COLOR', language: 'c')

unity_dir = include_directories('.')
unity_lib = static_library(meson.project_name(),
  files('unity.c'),
  implicit_include_directories: false,
)

unity_dep = declare_dependency(link_with: unity_lib, include_directories: unity_dir)
meson.override_dependency('unity', unity_dep)
