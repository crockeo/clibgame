# clibgame-res

### Intent

The intent of the `clibgame-res` library is to provide an easy-to-use API for
the raw logic of loading resources from the filesystem (or wherever they may be
located).

### Implementation

The general implementation of the API is designed around this concept of a
`Resource` -- some piece of information that exists on the filesystem which can
be loaded and freed. Therefore, most every resource in this library has a
similar code-structure for loading and disposing:

```cpp
struct Resource {
    // Loading data into a resource from a variety of sources.
    virtual void load(std::string path)
            throw(std::runtime_error) = 0;
    virtual void load(std::ifstream& file)
            throw(std::runtime_error) = 0;
    virtual void load(FILE* file)
            throw(std::runtime_error) = 0;

    // Disposing of a Resource.
    virtual void dispose()
            throw(std::runtime_error) = 0;
};
```
