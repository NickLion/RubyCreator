[![Code Climate](https://codeclimate.com/github/hugopl/RubyCreator/badges/gpa.svg)](https://codeclimate.com/github/hugopl/RubyCreator)

# RubyCreator

Plugin to add Ruby language support to QtCreator IDE.

More info can be found at: http://hugopl.github.io/RubyCreator/

## How to install

Packages are available only for Arch Linux in AUR, for anything different you will need to clone the repository and compile it yourself.

# Note About branches

`master` branch should work with the `master` branch of QtCreator, it may not compile because QtCreator may have changed some API and we had no time to adapt to the changes.

Current development is done on branch qt-3.x, where x is the current QtCreator version on Arch Linux, `master` branch is updated mostly upon contributions.

Old versions of this plugin that works with old versions of QtCreator can be found in tags v3.1, v3.3, etc, these versions will not get any updates, if you like to contribute, do it in the development branch.

## How to compile

**You need Qt5!!**

If you want to try QtCreator but don't want to have a custom QtCreator compiled just to do that, follow these instructions:

* ./configure.rb
* cd build && make

At the end of the build you will see an error about lack of permissions to move the plugin library to /usr/..., move it by yourself and it's done.

If you pretend to contribute with RubyCreator or already write plugins for QtCreator you probably already have a custom build of QtCreator installed in
a sandbox somewhere in your system, so just call qmake passing QTC_SOURCE and QTC_BUILD variables.
