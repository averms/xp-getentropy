project('xp_getentropy', 'c',
  version: '0.0.0',
  meson_version: '>=0.56.0',
  license: 'ISC',
  default_options: [
    'c_std=c99',
    'warning_level=3',
    'strip=true',
    'buildtype=release',
  ]
)

cc = meson.get_compiler('c')

if cc.get_id() in ['gcc', 'clang'] and get_option('warning_level').to_int() == 3
  add_project_arguments(
    '-pedantic-errors',
    '-Wuninitialized',
    '-Wconversion',
    '-Wcast-qual',
    '-Wdouble-promotion',
    '-Wundef',
    language: 'c',
  )
  cc_major = cc.version().split('.')[0].to_int()
  # GCC 5 and below (maybe 6) die on unrecognized warnings.
  if cc.get_id() == 'gcc' and cc_major >= 7
    add_project_arguments(
      '-Wshadow=local',
      '-Wredundant-decls',
      '-Wformat=2',
      '-Wnull-dereference',
      '-Wduplicated-branches',
      '-Wduplicated-cond',
      language: 'c',
    )
  elif cc.get_id() == 'clang'
    add_project_arguments(
      # '-Wshadow',
      # '-Wunreachable-code-aggressive',
      # '-Wdeprecated',
      # '-Wno-empty-translation-unit',
      # '-Wassign-enum',
      '-Weverything',
      language: 'c',
    )
  endif
  if get_option('optimization') == 'g'
    add_project_arguments('-D_FORTIFY_SOURCE=1', language: 'c')
  endif
endif

os = host_machine.system()
lib_args = []

if os == 'linux'
  if cc.has_function('getrandom', prefix: '#include <sys/random.h>')
    lib_args += ['-D_DEFAULT_SOURCE']
    srcfile = 'getentropy_getrandom.c'
  else
    # Old Linux distros like CentOS 7
    lib_args += ['-D_POSIX_C_SOURCE=200809L']
    srcfile = 'getentropy_urandom.c'
  endif

elif os == 'windows'
  srcfile = 'getentropy_bcryptgenrandom.c'

elif os == 'darwin'
  srcfile = 'getentropy_getentropy_macos.c'

elif os == 'freebsd'
  if cc.has_function('getentropy', prefix: '#include <unistd.h>')
    srcfile = 'getentropy_getentropy.c'
  else
    # FreeBSD 11 is still supported.
    srcfile = 'getentropy_sysctl.c'
  endif

elif os == 'netbsd'
  srcfile = 'getentropy_sysctl.c'

elif os == 'openbsd'
  srcfile = 'getentropy_getentropy.c'

elif os == 'dragonfly'
  srcfile = 'getentropy_getrandom.c'

elif os == 'sunos'
  srcfile = 'getentropy_getrandom.c'

elif os == 'cygwin'
  srcfile = 'getentropy_getentropy.c'
  lib_args += ['-D_DEFAULT_SOURCE']

elif os == 'emscripten'
  srcfile = 'getentropy_getentropy_wasm.c'

endif

inc = include_directories('include')
lib = static_library(meson.project_name(), 'source' / srcfile,
  c_args: lib_args,
  include_directories: inc,
  implicit_include_directories: false,
)
xp_getentropy_dep = declare_dependency(
  link_with: lib,
  version: meson.project_version(),
  include_directories: inc,
)

unity_proj = subproject('unity')
unity_dep = dependency('unity')

t_basic = executable('t_basic',
  'test/t_basic.c',
  dependencies: xp_getentropy_dep,
  implicit_include_directories: false,
)
t_asking_for_257 = executable('t_more',
  'test/t_more.c',
  dependencies: [xp_getentropy_dep, unity_dep],
  implicit_include_directories: false,
)
