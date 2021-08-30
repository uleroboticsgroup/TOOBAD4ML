Usage {#usage}
=====

[TOC]

## Run

```bash
./toobad4ml_exe <path_to_file_or_to_multiple_files.c> -d=DESCRIPTOR -f=FORMAT -o=FILENAME --
```

## Supported arguments

| Argument | Value | Description |
|----------|-------|-------------|
| -d       | Padmanabhuni | Descriptor model proposed by [Padmanabhuni and Tan (2015)](https://doi.org/10.1109/COMPSAC.2014.62) |
| -f       | STD   | Standard output |
|          | CSV   | CSV format      |
| -o       |       | Name of the output file¹ |

¹ *Only valid if filename is provided and `format` argument is different from STD. Otherwise, this flag is ignored.*

## Tagged source files format

The tool accepts pre-tagged *.c* files that contain comments appended at the end of each file. Such comments (see code below) start with line `/// ###BEGIN_VULNERABLE_LINES###` and is followed by several lines with the format `/// starting_line,starting_offset;ending_line,ending_offset` (with offset being the column).

```c
/// ###BEGIN_VULNERABLE_LINES###

/// 1126,3;1126,9

/// 1153,9;1153,15

/// 1341,9;1341,15

/// 1734,6;1734,12
```

These lines represent the lines of code that TOOBAD4ML will analyze and extract features from. For a list of examples, please check the `data` directory.