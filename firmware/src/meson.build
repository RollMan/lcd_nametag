project('lcd_nametag', 'c')

# Prerequisites
objcopy = find_program('avr-objcopy')
cflags = ['-Wall', '-g', '-Os', '-mmcu=' + host_machine.cpu()]

# Project Build
src = ['main.c']
elf = executable(
    'lcd_nametag.elf',
    src,
    c_args: cflags,
    link_args: cflags,
)
ihex_target = custom_target(
    'objcopy_ihex_tgt',
    input: [elf],
    output: [elf.name().replace('.elf', '.hex')],
    command: [objcopy, '-S', '-j', '.text', '-j', '.data', '-O', 'ihex', '@INPUT@', '@OUTPUT@'],
    build_by_default: true,
)
