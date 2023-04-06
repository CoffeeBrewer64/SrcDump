
===== D I S C L A I M E R =====
-------------------------------

The release of this data shall not and will not hurt anyone or anything, and
shall not and will not be used to exclude, extort, harass, stalk, dox, brigade
against or otherwise hurt anyone or anything.
Please be civil.


Contents
--------

This is an archive containing four roms of japanese Pokémon Gold and Silver.
Two of them are debug roms, the other two are release roms. All of the
timestamps are for february 3rd, 2000, three months after release. This can
be right, as the main differences between these and the real release are
bugfixes that can be found in either the international releases or crystal.

There is two assembler output files, a symbol file that matches exactly with
the previously leaked CRYSTAL_BY_NUM.SYM, and a ranges file, that spells out
what parts of the rom are code or data, and corresponds to the same rom as the
symbol file, probably a debug version of japanese Pokémon Crystal. This rom is
not included in the archive.

The last file is a spreadsheet, timestamped april 7th, 2017, which explains
how the debug menus work. This file might have been used to test the virtual
console releases.

The untouched files in the archive are in 000203/, the fixed/ folder has the
roms with their headers fixed so they can be played in an emulator. The
extracted range and symbol files, as well as some documentation about them,
are in the research/ folder.


Original archive file structure
-------------------------------

It has four directories:
GOLD_N: Gold
GOLD_D: Gold (debug)
SILVER_N: Silver
SILVER_D: Silver (debug)

Each of these directories contain:
MONS[xx].COM: The rom of the game
MONS[xx].LZH: An lzh archive containing the rom
PM[xx]BIN.LZH: An archive containing the rom of the game split in two 512kb parts

The roms contain a header with a wrong MBC type, which will cause them to
crash in most emulators. Fix this by setting the byte at offset 0x147 to 0x10
and fixing the header checksum or run:
    rgbfix -m 0x10 -v rom.gb
Or use one of the fixed roms in the fixed/ directory.

GOLD_D/ISDWDSYM.DAT and GOLD_D/ISDWDRNG.DAT are assembler output files. They
contain the symbols and ranges of probably a debug version of japanese Pokémon
Crystal.

pokGSC_DebugMenu_Manual.xlsx is a manual explaining the debug menus.


Changes from Pocket Monsters Kin V1.1 to MONSGN.COM
---------------------------------------------------

- Clock reset function is included (Down+Select+B in main menu)
- When changing boxes, the box is swapped after the "don't turn off the power"
  message instead of before, like in Crystal.
- A disobedient pokemon stops encore properly. This was fixed in the
  international Gold and Silver release.
- wBattleType is reset in TryWildEncounter.no_battle and
  SweetScentEncounter.no_battle.
- Two 2-byte insertions were made in bank $22, but are unidentified.


Debug menus
-----------

You can access the debug menus by pressing select on the title screen, and
b+start in the overworld.
Hold select before entering the game through "continue" to enable overworld
debug features.
Hold b in the overworld to walk through walls and avoid encounters.

Title screen options:
- Fight, battle test
- Communication, enters the overworld in viridian pokecenter
- Field, enters the overworld in the player's room
- Sound, sound and sfx test
- Clock Function, RTC changing tool
- Monster, pokemon sprite viewing tool
- Trainer, trainer sprite viewing tool
- Password, generate a password for the clock reset function

Overworld options (pg 1):
- Warp, opens fly map
- Breeding, test the day care
- Make, create a pokemon, store it in the current box
- Pokegear:
-- Clock, open overworld day/time and pokegear status overlay
-- Coordinates, open overworld coordinate viewer overlay
-- Adjust, change current time
-- 60 second, unknown
-- 24 hour, unknown
-- Dismiss, close overworld overlays
- PC, opens the PC

Overworld options (pg 2):
- Item, get any item
- Recovery, heals your team
- Experiment, set the ID of the first pokemon in the party
- Game:
-- Slot Machine
-- Poker Game
-- Pair Game
- Timer, RTC changing tool

Overworld options (pg 3, use the d-pad):
- Test 1, test capture tutorial
- Test 2, test hall of fame/credits
- Test 3, test radio tower event
- Test 4, get items 1 through 50 in the PC
- Hatch, cause first egg in party to hatch in next step
