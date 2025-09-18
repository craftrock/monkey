project('monkey', 'c', 
  version: '0.1.0',
  default_options: ['c_std=c23'])

# Find the Check testing framework with all required libs
check_dep = dependency('check')
math_dep = meson.get_compiler('c').find_library('m')
thread_dep = dependency('threads')
rt_dep = meson.get_compiler('c').find_library('rt')

# Source files
lexer_sources = files(
  'src/lexer.c',
  'src/token.c'
)

# Test executable - matching your Makefile exactly
test_lexer = executable('test_lexer',
  'tests/test_lexer.c',
  lexer_sources,
  dependencies: [check_dep, math_dep, thread_dep, rt_dep],
  c_args: ['-Wall', '-Wextra', '-g'],
  install: false,
)

# Register the test
test('lexer_tests', test_lexer)

# Optional: Main executable (if you want to build the main program too)
main_exe = executable('monkey',
  'src/main.c',
  lexer_sources,
  c_args: ['-Wall', '-Wextra', '-g'],
  install: false,
)