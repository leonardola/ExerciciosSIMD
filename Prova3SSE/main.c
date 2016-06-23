//
//  main.c
//  Prova3SSE
//
//  Created by leonardo albuquerque on 15/06/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <emmintrin.h>

#define X 4


void exercicio1(){
    int i;
    __m128i a128;
    __m128i b128;
    __m128i c128;
    
    char *a  = (char*) malloc(X * sizeof(char));
    char *b  = (char*) malloc(X * sizeof(char));
    char *c  = (char*) malloc(X * sizeof(char));
    
    printf("Exercio 1\n");
    
    //carrega o vetor
    for (i = 0; i < X; i++){
        a[i] = i;
        b[i] = i;
    }
    
    for(i = 0; i < X; i+=16){
        //transforma em _m128i uma parte do vetor
        a128 = _mm_load_si128((__m128i const*) &a[i]);
        b128 = _mm_load_si128((__m128i const*) &b[i]);
        
        c128 = _mm_add_epi8(a128,b128);
        
        //armazena em vetor de novo
        _mm_store_si128((__m128i*) &c[i], c128);
    }
    
    for(i = 0; i < X; i++){
        printf("%d\n",c[i]);
    }
    
    free(a);
    free(b);
    free(c);

}

void exercicio2(){
    int i;
    float *a = (float*) malloc(X * sizeof(float));
    float *b = (float*) malloc(X * sizeof(float));
    
    printf("Exercicio 2\n");
    
    //carrega o vetor
    for(i = 0; i < X; i++){
        b[i] = i;
    }
    
    __m128 x =  _mm_set1_ps (5);
    __m128 a128;
    __m128 b128;
    
    for(i = 0; i < X; i+=4){
        //armazena em _m128
        b128 = _mm_load_ps(&b[i]);
        
        //faz soma
        a128 = _mm_add_ps(b128, x);
        
        //coloca de volta no vetor
        _mm_store_ps(&a[i], a128);
    }
    
    for(i = 0; i < X; i++){
        printf("%f\n", a[i]);
    }
    
    free(a);
    free(b);
    
}

void exercicio3(){
    
    int i;
    unsigned char *a = (unsigned char*) malloc(X * sizeof(unsigned char));
    
    __m128i x;
    
    printf("Exercicio 3\n");
    
    for(i = 0; i < X; i+=16){
        //carrega com 16 valores
        x =  _mm_set_epi8(i, i+1, i+2, i+3, i+4, i+5, i+6, i+7, i+8, i+9, i+10, i+11, i+12, i+13, i+14, i+15);
        //joga no vetor
        _mm_store_si128((__m128i *) &a[i], x);
    }
    
    for(i = 0; i < X; i++){
        printf("%u\n", a[i]);
    }
    
    free(a);
}

void  exercicio4(){
    int *a = (int*) malloc(X * sizeof(int));
    int i;
    int x = 0;
    
    __m128i sum128 =  _mm_setzero_si128();
    
    printf("Exercicio 4\n");
    
    //carrega vetor
    for(i = 0; i < X; i++){
        a[i] = 2;
    }
    
    __m128i a128;
    for(i = 0; i < X; i += 4){
        //carrea em variavel _m128
        a128 = _mm_load_si128((const __m128i*) &a[i]);
        //faz soma
        sum128 = _mm_add_epi32(a128, sum128);
    }
    
    int *sum = (int*) malloc(4*sizeof(int));
    
    _mm_store_si128((__m128i *) &sum[0], sum128);

    //soma os ultimos 4 elementos
    for(i = 0 ; i < 4; i++){
        
        printf("%i\n", sum[i]);
        x += sum[i];
    }
    
    printf("%i\n", x);
    
    free(a);
    free(sum);
    
}

void exercicio5(){
    int i;
    float *sum = (float*) malloc(4 * sizeof(float));
    float x = 0;
    
    float *a = (float*) malloc(X * sizeof(float));
    float *b = (float*) malloc(X * sizeof(float));
    
    printf("Exercicio 5\n");
    
    for(int i = 0; i < X; i++){
        a[i] = i;
        b[i] = i;
    }

    __m128 x128 =  _mm_set1_ps (0);
    
    __m128 a128;
    __m128 b128;
    
    for(i = 0; i < X; i+=4){
        a128 = _mm_load_ps((const float*) &a[i]);
        b128 = _mm_load_ps((const float*) &b[i]);
        
        
        //multiplica
        a128 = _mm_mul_ps(a128, a128);
        //soma e armazena em x
        x128 = _mm_add_ps(a128, x128);
        
        //coloca no vetor
        _mm_store_ps(&a[i], a128);
    }
    
    _mm_store_ps((float *) &sum[0], x128);
    
    //soma os ultimos 4
    for(i = 0; i < 4; i++){
        x += sum[i];
    }

    printf("%f\n", x);
    
    free(sum);
    free(a);
    free(b);
}

void exercicio6(){
    int i;
    float *a = (float*) (malloc(X * sizeof(float)));
    float *x = (float*) (malloc(4 * sizeof(float)));
    
    printf("Exercicio 6\n");
    
    for(i = 0; i < X; i++){
        a[i] = i;
    }
    
    __m128 x128 =  _mm_set1_ps (0);
    __m128 a128 = _mm_load_ps(a);
    __m128 three128 = _mm_set1_ps (3);
    
    for(i = 0; i < X; i+=4){
        //carrega em _m128
        a128 = _mm_load_ps((float*) &a[i]);
        
        //multiplica
        a128 = _mm_mul_ps(a128, three128);
        //soma
        x128 = _mm_add_ps(a128, x128);
        
        _mm_store_ps(&x[i], x128);
    }

    float sum = 0;
    
    for(i = 0; i < 4; i++){
        sum += x[i];
    }
    
    printf("%f\n", sum);
    
    free(a);
    free(x);

}

void exercicio7(){
    int i;
    float *a = (float*) (malloc(X * sizeof(float)));
    float *b = (float*) (malloc(X * sizeof(float)));
    float *c = (float*) (malloc(X * sizeof(float)));
    
    printf("Exercicio 7\n");
    
    for(i = 0; i < X; i++){
        b[i] = i+1;
        c[i] = i;
    }
    
    __m128 one128 = _mm_set1_ps(1);
    __m128 a128;
    __m128 b128;
    __m128 c128;
    __m128 max128;
    
    for(i = 0; i < X; i+=4){
        b128 = _mm_load_ps((float*) &b[i]);
        c128 = _mm_load_ps((float*) &c[i]);
        
        //verifica qual o maior entre o array e 1, evita divisões por 0
        max128 = _mm_max_ps(b128, one128);
        
        a128 = _mm_div_ps(b128, max128);
        _mm_store_ps(&a[i], a128);
    }
    
    for(i = 0; i < X; i++){
        printf("%f\n", a[i]);
    }
    
    free(a);
    free(b);
    free(c);
}

int main(int argc, const char * argv[]) {

    exercicio1();
    exercicio2();
    exercicio3();
    exercicio4();
    exercicio5();
    exercicio6();
    exercicio7();
    
}