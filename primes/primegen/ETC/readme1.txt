D. J. Bernstein
The latest published primegen package is
primegen/primegen-0.97.tar.gz
primegen-0.97.tar.gz</a>.

On some machines you have to add
-fsigned-char to the first line of conf-cc before compiling.

This is safe on all machines.
primegen is a small, fast library to generate prime numbers in order.
It generates the 50847534 primes up to 1000000000 in just 8 seconds on a
Pentium II-350; it prints them in decimal in just 35 seconds.

primegen can generate primes up to 1000000000000000, although it is not
optimized for primes past 32 bits. It uses the Sieve of Atkin instead of
the traditional Sieve of Eratosthenes.
Checksums
primes 1 1000000 | md5: c13929ee9d2aea8f83aa076236079e94<br>
primes 1 10000000 | md5: 60e34d268bad671a5f299e1ecc988ff6<br>
primes 1 100000000 | md5: 4e2b0027288a27e9c99699364877c9db<br>
primes 1 1000000000 | md5: 92c178cc5bb85e06366551c0ae7e18f6<br>
primes 1 10000000000 | md5: 95ded65c9ddca18e1df966ba2a2b373a<br>
primes 1 100000000000 | md5: 9d8a8c2d7221497843ca289e6f463bfd<br>
primes 1 1000000000000 | md5: c899bf5d0ccef05787ac969afd6606ff<br>

