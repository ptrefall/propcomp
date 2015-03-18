# Issues #

# Fixed #
  * 1) T\_HashString destructor crashes after Murmur hashing was added.
    * Fix: Changed from 128bit to 32bit hashing.