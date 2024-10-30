# Giant Hook

### System Initialization

| ADDRS       | Vector | Description / Functions            |
|-------------|--------|--------------------------------------------------------|
| `3E00H + b` | BOOT   | Enter after power on or RESET and after system has been loaded from disk. Display sign-on message, zero IOBYT and DRIVE, set up low RAM vectors, select current drive, go to CCP. |
| `3E03H + b` | WBOOT  | Enter after CTRL-C or JMP 0. Load system from disk, set up low RAM vectors, select current drive, go to CCP.         |

### Console I/O Functions

| ADDRS       | Vector | Description / Functions            |
|-------------|--------|---------------------------------|
| `3E06H + b` | CONST  | Test CON: for keyboard character ready.                                                                             |
| `3E09H + b` | CONIN  | Wait for and read CON: keyboard character.                                                                          |
| `3E0CH + b` | CONOUT | Send one character to CON: display.                                                                                 |
| `3E0FH + b` | LIST   | Send one character to LST: device.                                                                                  |
| `3E12H + b` | PUNCH  | Send one character to PUN: device.                                                                                  |
| `3E15H + b` | READER | Wait for and input one RDR: character.                                                                              |

### Disk I/O Functions

| ADDRS       | Vector | Description / Functions        |
|-------------|--------|------------------------------------|
| `3E18H + b` | HOME   | Set current drive head to track 0.                                                                                   |
| `3E1BH + b` | SELDSK | Select drive, store number in DRIVE.                                                                                |
| `3E1EH + b` | SETTRK | Set current drive head to track specified.                                                                          |
| `3E21H + b` | SETSEC | Seek current drive to sector specified.                                                                             |
| `3E24H + b` | SETDMA | Set RAM buffer start address for next disk read or write.                                                           |
| `3E27H + b` | READ   | Read selected disk, track, sector into RAM buffer.                                                                  |
| `3E2AH + b` | WRITE  | Write contents of RAM buffer into selected disk, track, sector.                                                     |

Functions use the standardized access points/vectors provided by the giant hook to work their magic.

Input/Output Functions
| Label    | Code    | Function|
| -------- | ------- | ------- |
| RCONF  | 1    |   Read character from console device |
| WCONF | 2     |     Write character to console device    |
| RRDRF |3     |      Read character from reader device   |
| WPUNF | 4     |   Write character to punch device      |
| WLSTF | 5     |      Write character to list device   |
| RIOBF | 7     |    Read IOBYT from memory location 3     |
| WIOBF |  8    |    Write 10BYT to memory location 3     |
| RBUFF | 10     |   Read console edited line input       |
| CRDYF | 11     |   Check console for character ready      |

Disk Access Functions
| Label    | Code    | Function|
| -------- | ------- | ------- |
| INITF | 13    |    Initialize BDOS. select drive A:      |
| DSELF | 14     |      Log in and select drive d:  |
| OPENF | 15   |    Open a file for read or write      |
| CLOSEF | 16    |    Close a file     |
| FINDF | 17     |  Find a file in the disk directory        |
| NEXTF | 18   |     Find next occurrence of a file     |
| DELEF | 19     |     Delete a file     |
| READF | 20     |   Read one disk record into memory       |
| WRITF | 21     |    Write one record from memory to disk     |
| MAKEF | 22     |       Create a disk directory entry  |
| SDMAF | 26     |    Set RAM buffer address for read or write     |

To use these functions you would use MVI REGISTER CODE

Input/Output Functions:

- RCONF (1) and WCONF (2): If we want to output anything to the console or take input from console. In other words necessary for console programs.
- RBUFF (10): Reading an entire line of console input is a typical requirement in user-interactive programs.

Disk Access Functions:

- OPENF (15) and CLOSEF (16): In order to manipulate the files we need to first open them and after we are done we need to close them.
- READF (20) and WRITF (21): Reads and writes from disk, so we could use this to take files as input and directly change a file if necessary
- MAKEF (22): Creates a new file, could be used to store output data.