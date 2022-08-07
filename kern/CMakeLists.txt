add_executable(kernel)

target_include_directories(kernel PRIVATE "include/")

target_compile_options(kernel PRIVATE -O2 -ffreestanding -nostdlib -Wall -Werror-implicit-function-declaration)

target_sources(kernel PRIVATE
	src/crt0.s
	src/exception.s
	src/kmain.c
	src/kputchar.c
	src/sio.c
	src/printf.c
	src/dev9.c
	src/timer.c
	src/intc.c
	src/util.c
)

target_link_options(kernel PRIVATE
	-T${CMAKE_CURRENT_SOURCE_DIR}/kern.ld
	-ffreestanding
	-nostdlib
	-Wl,--orphan-handling=error
)

target_link_libraries(kernel PRIVATE
	gcc
)
