#include <stdio.h>

/*
 * Programa: Control de acceso y descuentos (Ejercicio final)
 * Descripción:
 *   - Solicita banderas 0/1 del usuario (credencial, roles, etc.)
 *   - Verifica ACCESO con condicional compuesto usando && y ||
 *   - Calcula un ÚNICO descuento (máximo aplicable): 40, 30, 25 (promo), 20 o 0
 *   - Muestra el total a pagar sobre un precio base
 *
 * Notas para desarrolladores:
 *   - No se usa '!' por requerimiento didáctico.
 *   - El orden de los else-if garantiza "solo el mayor" descuento.
 *   - 'aplicaPromo' se activa solo si hay cupón Y es miércoles.
 */

int main (void){
    /* ---- Banderas de entrada (0/1). esDocente se inicializa: puede no preguntarse si esEstudiante=1 ---- */
    int credencial, esEstudiante, esDocente = 0, esVip, bloqueado, climaSevero, esMiercoles, esManana, cupon;

    /* ---- Señales de control y resultados ---- */
    int banderaAccesoConcedido = 0;
    int descuento = 0;
    const float precioBase = 100.0f;   /* const para evitar cambios accidentales */
    int aplicaPromo = 0;
    float precioFinal = 0.0f;

    /* ---- Entradas validadas (0/1) ---- */
    printf("Cuenta usted con credencial? (0=No,1=Si): ");
    if (scanf(" %d", &credencial) != 1 || (credencial != 0 && credencial != 1)) {
        puts("Entrada invalida para credencial (use 0 o 1).");
        return 1;
    }

    printf("Es usted estudiante actualmente? (0=No,1=Si): ");
    if (scanf(" %d", &esEstudiante) != 1 || (esEstudiante != 0 && esEstudiante != 1)) {
        puts("Entrada invalida para estudiante (use 0 o 1).");
        return 1;
    }

    /* Si NO es estudiante, preguntamos por docente. esDocente ya vale 0 por defecto. */
    if (esEstudiante == 0){
        printf("Es usted docente activo? (0=No,1=Si): ");
        if (scanf(" %d", &esDocente) != 1 || (esDocente != 0 && esDocente != 1)) {
            puts("Entrada invalida para Docente (use 0 o 1).");
            return 1;
        }
    }

    printf("Es usted miembro Vip? (0=No,1=Si): ");
    if (scanf(" %d", &esVip) != 1 || (esVip != 0 && esVip != 1)) {
        puts("Entrada invalida para Vip (use 0 o 1).");
        return 1;
    }

    printf("Presenta usted alguna penitencia de bloqueo? (0=No,1=Si): ");
    if (scanf(" %d", &bloqueado) != 1 || (bloqueado != 0 && bloqueado != 1)) {
        puts("Entrada invalida para bloqueo (use 0 o 1).");
        return 1;
    }

    printf("Hace un clima desfavorable? (0=No,1=Si): ");
    if (scanf(" %d", &climaSevero) != 1 || (climaSevero != 0 && climaSevero != 1)) {
        puts("Entrada invalida para clima (use 0 o 1).");
        return 1;
    }

    printf("Hoy es miercoles? (0=No,1=Si): ");
    if (scanf(" %d", &esMiercoles) != 1 || (esMiercoles != 0 && esMiercoles != 1)) {
        puts("Entrada invalida para miercoles (use 0 o 1).");
        return 1;
    }

    printf("Aun no son las 12:00 pm? (0=No,1=Si): ");
    if (scanf(" %d", &esManana) != 1 || (esManana != 0 && esManana != 1)) {
        puts("Entrada invalida para mañana (use 0 o 1).");
        return 1;
    }

    printf("Tiene codigo de la promoEspecial? (0=No,1=Si): ");
    if (scanf(" %d", &cupon) != 1 || (cupon != 0 && cupon != 1)) {
        puts("Entrada invalida para cupon (use 0 o 1).");
        return 1;
    }

    /* ---- Activación de la promo especial: requiere cupón Y miércoles ---- */
    aplicaPromo = (cupon == 1) && (esMiercoles == 1);

    /* ---- Acceso: condicional compuesto (sin '!') ----
       Requisitos:
         - credencial == 1
         - al menos uno de: esEstudiante==1, esDocente==1, esVip==1
         - bloqueado == 0
         - climaSevero == 0
    */
    if ( credencial == 1
         && (esEstudiante == 1 || esDocente == 1 || esVip == 1)
         && bloqueado == 0
         && climaSevero == 0 ) {

        banderaAccesoConcedido = 1;

        /* ---- Descuento: elegir SOLO el mayor aplicable (orden 40 -> 30 -> 25 -> 20 -> 0) ---- */
        if (esVip == 1 && bloqueado == 0) {
            descuento = 40;
        }
        else if (esEstudiante == 1 || esDocente == 1) {
            descuento = 30;
        }
        else if (aplicaPromo == 1) {
            descuento = 25;
        }
        else if (esMiercoles == 1 || esManana == 1) {
            descuento = 20;
        }
        else {
            descuento = 0;
        }
    }
    else {
        /* Justificación mínima: acceso falló por algún requisito (credencial/rol/bloqueo/clima) */
        printf("----------Acceso Denegado!----------\n");
        return 1;
    }

    /* ---- Precio final ---- */
    precioFinal = precioBase - (precioBase * (descuento / 100.0f));

    /* ---- Salida amigable ---- */
    if (banderaAccesoConcedido == 1){
        printf("\n\n-----------Acceso Concedido-----------\n");
        printf("Descuento aplicado: %i%%\n", descuento);
        printf("Total a pagar: $%.2f\n", precioFinal);  /* línea final con salto de línea */
    }

    return 0;
}

