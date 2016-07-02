# pak 2016-06-06

The original structure of the pak was an API to fetch `std::istream&`s from
either the filesystem or a singular file made to emulate the filesystem (for
advantages that can be covered elsewhere).

I found a problem with this, which is that a lot of C libraries used to load
resources (e.g. freetype and libpng) rely on having `FILE*`s instead. As such
I'm restructuring the `Pak` struct (and its derived classes) to return `FILE*`
as well.

As such, each resource needs to be modified slightly to make use of this change.

### Pak File Format

The literal string `CPAK` (to ensure that we're looking at an intentionally
pakked file). `<2-byte integer>`, the number of files pakked away. Then for each
pakked away file:

* A path (up to 2047 characters long).
* A `|` character to denote its end.
* 4-byte integer to define its offset.
* 4-byte integer to define its length.
