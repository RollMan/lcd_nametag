project('lcd_nametag', 'c')

if meson.is_cross_build()
# Prerequisites
  objcopy = find_program('avr-objcopy')
  cflags = ['-Wall', '-g', '-Os', '-mmcu=' + host_machine.cpu()]

# Project Build
  src = [
    'main.c',
    'jpg/decode.c',
    'jpg/header.c',
    'jpg/header/segments.c',
  ]
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
else
  # Unit tests
  #  JPEG decoder test
  jpg_decoder_test = executable('jpg_decode_test_bin', 'jpg/test_decode.c')
  test('jpg_decode_test', jpg_decoder_test)
endif
