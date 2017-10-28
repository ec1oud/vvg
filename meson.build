project('vvg')
cmake_build_type = 'Debug'
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED on)
cmake_cxx_flags = '${CMAKE_CXX_FLAGS} -std=c++1z'
# to disable ninja byproduct warning
# cmake_policy(['SET', 'CMP0058', 'NEW'])
# enable warnings
is_clang = ['CMAKE_CXX_COMPILER_ID', 'MATCHES', 'Clang']
if 'MSVC'
  if 'CMAKE_CXX_FLAGS', 'MATCHES', '/W[0-4]'
    # string(['REGEX', 'REPLACE', '/W[0-4]', '/W4', 'CMAKE_CXX_FLAGS', '${CMAKE_CXX_FLAGS}'])
  else
    cmake_cxx_flags = '${CMAKE_CXX_FLAGS} /W4'
  endif
elif 'CMAKE_COMPILER_IS_GNUCC', 'OR', 'CMAKE_COMPILER_IS_GNUCXX', 'OR', 'is_clang'
  cmake_cxx_flags = '${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Wextra -Wpedantic'
endif
cmake_runtime_output_directory = [cmake_binary_dir, '/bin']
# include_directories([cmake_current_source_dir, '/include'])
# include_directories([cmake_current_source_dir, '/src'])
# include_directories([cmake_current_source_dir, '/external'])
# include_directories([cmake_current_binary_dir, '/external/install/include'])
# link_directories([cmake_current_binary_dir, '/external/install/lib'])
# external projects
externalprojectcmakeargs = ['-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/install', '-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}', '-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}', '-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}', '-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}', '-DDebug=${Debug}']
# vpp (using vulkan 1.0.20 api)
# externalproject_add(['vpp_ep', 'PREFIX', cmake_inary_dir, '/vpp', 'GIT_REPOSITORY', 'https://github.com/nyorain/vpp.git', 'GIT_TAG', 'master', 'INSTALL_DIR', cmake_binary_dir, '/external/install', 'CMAKE_ARGS', externalprojectcmakeargs, '-DApiVersion=1-0-20'])
# externalproject_add_step(['vpp_ep', 'forceinstall', 'DEPENDEES', 'configure', 'DEPENDERS', 'install', 'ALWAYS', '1'])
# list(['APPEND', 'CMAKE_MODULE_PATH', '${CMAKE_CURRENT_SOURCE_DIR}'])
Vulkan_dep = dependency('Vulkan')
subdir('src')
if 'Shaders'
  subdir('src/shader')
endif
if 'Examples'
  if 'Win32', 'OR', 'MSYS', 'OR', 'MINGW'
    subdir('examples')
  else
    # message(['WARNING', 'The examples are windows-only at the moment.'])
  endif
endif
