#vkg
if 'Shared'
  vvg_lib = shared_library('vvg', 'renderer.cpp', 'nanovg.c')
else
  vvg_lib = static_library('vvg', 'renderer.cpp', 'nanovg.c')
endif
if 'Depend'
  # add_dependencies(['vvg', 'vpp_ep'])
endif
# link to vulkan and vpp
Vulkan_dep = dependency('Vulkan')
# target_link_libraries(['vvg', 'vpp', vulkan_library])
# target_include_directories(['vvg', 'PUBLIC', vulkan_include_dir])
# copy runtime files
# add_custom_command(['TARGET', 'vvg', 'PRE_BUILD', 'COMMAND', cmake_command, '-E', 'copy_directory', '${CMAKE_BINARY_DIR}/external/install/bin/.', '${CMAKE_BINARY_DIR}/bin', 'COMMENT', 'Copying vpp bin files'])
#install
# install(['TARGETS', 'vvg', 'RUNTIME', 'DESTINATION', 'bin', 'LIBRARY', 'DESTINATION', 'lib', 'ARCHIVE', 'DESTINATION', 'lib'])
