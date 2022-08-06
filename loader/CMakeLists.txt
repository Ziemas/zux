add_custom_command(OUTPUT kernel.s
  COMMAND bin2s $<TARGET_FILE:kernel> kernel.s kelf_data
)

add_executable(loader)
target_include_directories(loader PRIVATE
	"include/"
	$ENV{PS2SDK}/ee/include
	$ENV{PS2SDK}/common/include
  )
target_compile_options(loader PRIVATE -G0 -Wall -Werror-implicit-function-declaration)
target_sources(loader PRIVATE
	src/loader.c
	kernel.s
)
target_link_options(loader PRIVATE
	-T$ENV{PS2SDK}/ee/startup/linkfile
)
target_compile_definitions(loader PRIVATE _EE)
target_link_libraries(loader PRIVATE
)
add_dependencies(loader kernel)
