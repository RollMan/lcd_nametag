project('lcd_nametag', 'c')

# Prerequisites
objcopy = find_program('avr-objcopy')
include_dir = include_directories(
  '/usr/local/avr/include',
)
lib_dir = [
  '/usr/local/avr/lib',
]
cflags = ['-Wall', '-g', '-Os']

# Project Build
src = ['main.c']
elf = executable(
    'lcd_nametag.elf',
    src,
    c_args: cflags,
    include_directories: include_dir,
)
ihex_target = custom_target(
    'objcopy_ihex',
    input: [elf],
    output: [elf.name().replace('.elf', '.hex')],
    command: [objcopy, '-j', '.text', '-j', '.data', '-O', 'ihex', '@INPUT', '@OUTPUT'],
)
