# feh - Imlib2 based image viewer

 * <http://feh.finalrewind.org/>
 * <http://linuxbrit.co.uk/feh/>
 * \#feh on irc.oftc.net

## Dependencies

### Required dependencies
 * Imlib2
 * libpng
 * libX11

### Optional dependencies
 * libcurl
 * libXinerama
 * json-c

### Recommended
 * jpegtran  (supplied by the jpeg library, for lossless image rotation)
 * convert  (supplied by ImageMagick, can be used to load unsupported formats)

## Installation

Open cloned/downloaded feh project folder

```shell
$ cmake .
$ make
$ sudo make install-all
```

ZSH Completion for feh is available [here](https://raw.githubusercontent.com/Caellian/feh/master/zsh/completions/_feh).

## Make options

Make file can be configured in config.cmake file before building/installing,
if it's changed later, feh has to be rebuilt.
