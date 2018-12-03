/***************************************************************************
utils.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/**
 * @brief Calcula la potenciación modular rop=base^exp (mod mod)
 *
 * @param el resultado de la potenciación modular
 * @param la base de la potencia
 * @param el exponente de la potencia
 * @param el módulo
 * 
 */
void powm(mpz_t rop, const mpz_t base, const mpz_t exp, const mpz_t mod) {
    size_t l;
    long int i;
    /*x = 1*/
    mpz_set_ui(rop, 1);
    l = mpz_sizeinbase(exp, 2);
    for (i = l - 1; i >= 0; i--) {
        /*x = x^2 mod n*/
        mpz_mul(rop, rop, rop);
        mpz_mod(rop, rop, mod);
        /*si a_i == 1*/
        if (mpz_tstbit(exp, i) == 1) {
            /*x = x*z mod n*/
            mpz_mul(rop, rop, base);
            mpz_mod(rop, rop, mod);
        }
    }
}