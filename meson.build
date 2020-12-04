project('xp_getentropy', 'c',
  version: '0.0.0',
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
  if cc.get_id() == 'gcc'
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
      '-Wshadow',
      '-Wunreachable-code-aggressive',
      '-Wdeprecated',
      '-Wno-empty-translation-unit',
      language: 'c',
    )
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
    srcfile = 'getentropy_urandom.c'
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
  # TODO: impl with get_random or getentropy or something.

endif

doxygen = find_program('doxygen', required: false)
if doxygen.found()
  doxy_conf = configuration_data({
    'DOXY_NAME': meson.project_name(),
    'DOXY_VERSION': meson.project_version(),
    'DOXY_ROOT': meson.project_source_root(),
    'DOXY_OUTPUT': meson.current_build_dir(),
  })

  doxyfile = configure_file(
    input: 'documentation/Doxyfile.in',
    output: 'Doxyfile',
    configuration: doxy_conf,
  )

  custom_target('documentation',
    build_by_default: false,
    command: [doxygen, doxyfile],
    input: files('include/xp_getentropy.h'),
    output: ['html'],
  )
endif

inc = include_directories('include')
lib = static_library(meson.project_name(),
  'source' / srcfile,
  c_args: lib_args,
  include_directories: inc,
  implicit_include_directories: false,
)

xp_getentropy_dep = declare_dependency(
  link_with: lib,
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
