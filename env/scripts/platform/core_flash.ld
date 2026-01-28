ENTRY(_start)

SECTIONS {
  _stack_top = 0x0F000000;
  _appmem_start = _stack_top;
  . = _stack_top + 0x10000;
  _stack_pointer = .;
  _heap_start = ALIGN(0x1000);
  /* _pmem_start and _entry_offset are defined in LDFLAGS */
  . = _pmem_start + _entry_offset;
  .text : {
    *(entry)
    *(.text*)
  }
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  }
  .data : {
    *(.data)
  }
  edata = .;
  _data = .;
  .bss : {
	_bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  }
  end = .;
  _end = .;
}
