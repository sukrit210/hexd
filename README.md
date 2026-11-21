# myxxd

A small `xxd`-style hexdump tool written in C, built step by step as a learning project.

It reads a file and prints each line as an offset, 16 bytes in hex (grouped in pairs), and the printable ASCII on the right.

```
00000000: 4865 6c6c 6f2c 2057 6f72 6c64 210a       Hello, World!.
```

## Build

```bash
gcc -Wall -Wextra -o myxxd xxd.c
```

## Usage

```bash
./myxxd <file>
```

Example:

```bash
echo "Hello, World!" > hello.txt
./myxxd hello.txt
```

## Output format

| Part | Meaning |
|------|---------|
| `00000000:` | Offset of the first byte on the line, 8 hex digits |
| `4865 6c6c ...` | 16 bytes per line, shown as hex in 2-byte groups |
| `Hello, World!.` | ASCII view. Printable characters as-is, everything else as `.` |

## How it works

1. Open the file in binary mode with `fopen(path, "rb")`.
2. Read up to 16 bytes at a time with `fread` into an `unsigned char` buffer.
3. For each line:
   - print the offset with `%08lx`
   - print each byte with `%02x`, adding a space after every 2 bytes
   - pad with spaces if the last line has fewer than 16 bytes, so the ASCII column stays aligned
   - print the ASCII column using `isprint`
4. Add the number of bytes read to the offset and repeat until `fread` returns 0.

### Functions used

| Function | Header | Purpose |
|----------|--------|---------|
| `fopen`, `fclose` | `stdio.h` | Open and close the file |
| `fread` | `stdio.h` | Read a block of bytes, returns how many were read |
| `printf`, `putchar` | `stdio.h` | Formatted and single-character output |
| `fprintf`, `perror` | `stdio.h` | Error messages on `stderr` |
| `isprint` | `ctype.h` | Check whether a byte is a printable character |

## Testing

Compare with the real tool:

```bash
diff <(./myxxd file) <(xxd file) && echo "match"
```

Try these inputs:
- an empty file
- a 1-byte file
- exactly 16 bytes
- a file whose size is not a multiple of 16
- a real binary, such as `/bin/ls`

## Learning path

The program was built in small steps:

1. Print bytes as hex with `fgetc`
2. Read 16 bytes per line with `fread`
3. Add the offset column
4. Add the ASCII column
5. Handle the short last line and 2-byte grouping

## Roadmap

- [ ] Read from `stdin` when no file is given
- [ ] `-s N` skip N bytes at the start (`fseek`)
- [ ] `-l N` limit output to N bytes
- [ ] `-c N` set the number of bytes per line
- [ ] `-p` plain hex output
- [ ] `-u` uppercase hex
- [ ] `-r` reverse a hex dump back to binary

## License

Add a license of your choice (for example MIT) before publishing.
