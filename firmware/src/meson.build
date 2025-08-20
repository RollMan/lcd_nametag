project('lcd_nametag', 'c')

common_src = [
    'jpg/decode.c',
    'jpg/header.c',
    'jpg/header/segments.c',
]

if meson.is_cross_build()
  # Prerequisites
  objcopy = find_program('avr-objcopy')
  cflags = ['-Wall', '-g', '-Os', '-mmcu=' + host_machine.cpu()]

# Project Build
  src = [
    'main.c',
  ]
  elf = executable(
      'lcd_nametag.elf',
      src + common_src,
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
  # Platform-independent unit tests to be run in building host.
  #  JPEG decoder test
  jpg_decode_test_src = ['jpg/test_decode.c']
  jpg_decoder_test = executable('jpg_decode_test_bin', jpg_decode_test_src + common_src)
  test('jpg_decode_test', jpg_decoder_test, args: [meson.current_source_dir() / 'jpg/for_test.jpg'])
endif
