int x = 5328; // 00000000000000000001010011010000

//cuenta los zeros a la izquierda del numero
__builtin_clz(x); // 19

//cuenta los zeros a la derecha del numero
__builtin_ctz(x); // 4

//cuenta los unos en el numero
__builtin_popcount(x); // 5

//cuenta la paridad de cantidad de unos
__builtin_parity(x); // 1