# clibgame

`clibgame` stands for Common Library [for] Games. That is, I find myself
writing the same utilities for developing games over and over again, so instead
of continuing that pattern I decided to instead write more generic helper
classes.

### Building

Building this project requires CMake version `>= 2.8`.

```bash
$ cmake .
$ make
$ make install # OPTIONAL - If you want to install the libraries / headers.
```

If you choose to uninstall the library, the `uninstall.sh` in this directory
removes all items added from the `install_manifest.txt`.

### Licensing

This project is licensed under the MIT Open Source license. For more detailed
information, look at the `LICENSE` file in this repository.
