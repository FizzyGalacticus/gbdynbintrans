# GbDynBinTrans
Extremely basic GameBoy ROM dynamic binary translator.

## Dev Tools:
[GBDK - GameBoy Development Kit](https://sourceforge.net/projects/gbdk/)

[Qt Framework](http://www.qt.io/)

## Compile .s assembly  files using GBDK
```
gbdk/bin/lcc -o <outputfilename> <inputfilename>
```

## Helpful Links
* [GameBoy CPU Manual](https://community.teamviennagames.com/uploads/files/1446411043985-gbcpuman.pdf)
* [GameBoy Opcode Map](http://imrannazar.com/Gameboy-Z80-Opcode-Map)
* [Qt Framework Documentation](http://doc.qt.io/qt-5/)

## Special Thanks
* [NewbiZ](https://github.com/NewbiZ) - Provided [opcodes.json](https://github.com/NewbiZ/gbemu/blob/master/scripts/opcodes.json) which allows us to easily translate opcodes to corresponding assembly commands.
* [Baptiste Lepilleur](https://sourceforge.net/u/blep/profile/) - Authored [JsonCpp](https://github.com/open-source-parsers/jsoncpp), allowing us to easily read/write/manipulate JSON data in C++.