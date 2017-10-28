project('vvg', ['c', 'cpp'],
  license: 'BSL',
  version: '0.1.0',
  meson_version: '>=0.42',
  default_options: ['cpp_std=c++1z', 'c_std=c11', 'warning_level=3'])
# to disable ninja byproduct warning
# cmake_policy(['SET', 'CMP0058', 'NEW'])
# enable warnings
if build_machine.system() == 'windows'
	add_project_arguments('/W4', language: 'cpp')
#~ else
	#~ add_project_arguments('-Wall -Wno-long-long -Wextra -Wpedantic', language: 'cpp')
endif
#~ cmake_runtime_output_directory = [cmake_binary_dir, '/bin']
# include_directories([cmake_current_source_dir, '/include'])
# include_directories([cmake_current_source_dir, '/src'])
# include_directories([cmake_current_source_dir, '/external'])
# include_directories([cmake_current_binary_dir, '/external/install/include'])
# link_directories([cmake_current_binary_dir, '/external/install/lib'])
#~ vvg_inc = include_directories('include')
#~ vvg_inc_private = include_directories('src')
dep_vpp = dependency('vpp', fallback: ['vpp', 'vpp_dep'])
# vpp (using vulkan 1.0.20 api)
# externalproject_add(['vpp_ep', 'PREFIX', cmake_inary_dir, '/vpp', 'GIT_REPOSITORY', 'https://github.com/nyorain/vpp.git', 'GIT_TAG', 'master', 'INSTALL_DIR', cmake_binary_dir, '/external/install', 'CMAKE_ARGS', externalprojectcmakeargs, '-DApiVersion=1-0-20'])
# externalproject_add_step(['vpp_ep', 'forceinstall', 'DEPENDEES', 'configure', 'DEPENDERS', 'install', 'ALWAYS', '1'])
# list(['APPEND', 'CMAKE_MODULE_PATH', '${CMAKE_CURRENT_SOURCE_DIR}'])
dep_vulkan = dependency('vulkan')
deps = [
	dep_vulkan,
	dep_vpp]
subdir('src')
subdir('src/shader')
examples = get_option('Examples')
#~ if examples
	#~ subdir('examples')
#~ endif
