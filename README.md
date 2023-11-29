# hashmap

Simple HasMap implementation in C \
I made this because I wanted to lean about how this datastructure worked,
and so I can have a reusable HashMap implementation for my future C projects.

# Quick Start

```console
$ make
$ ./hashmap
```

# TODO
 * When a key<sub>1</sub> has a collision with another key<sub>2</sub> and the colliding key<sub>2</sub> gets deleted, when setting key<sub>1</sub> it will be put in the slot of key<sub>2</sub> and will create a duplicate of key<sub>1</sub>. It should instead be kept to it's own slow
