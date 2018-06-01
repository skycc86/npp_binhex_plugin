# notepad++ binhex plugin

## binhex plugin for bin/hex string manipulating functions, bit shifting/grouping manipulations
## can support very long string manipulation

FORMAT : MSB --> LSB
accepts prefix 0x/0b
-----------------
bin2hex/hex2bin       - conversion between hex and binary text
bin_invert/hex_invert - bit inversion for bin/hex text (0b1010 -> 0b0101)
reverse	              - text reverse (abcd -> dcba)
hex_shift             - shift left/right for hex values, lose the shift out bit
hex_rotate            - rotate left/right for hex values, lsb become msb and vice versa
grouping_2/4/8/16     - grouping hex/bin string to 2/4/8/16 char
added incremental search and move to other view toolbar icon


copy the respective dll file over to notepad++ plugin directory (default to C:\Program Files\Notepad++\plugins)
restart notepad++ then u shall see additional BinHex item in the plugin menu

2.0 - compile for win32 and x64
    - added default shortcut key
    - added incremental search and move to other view toolbar icon
    - maintain 0x / 0b prefix

Author : skycc86
