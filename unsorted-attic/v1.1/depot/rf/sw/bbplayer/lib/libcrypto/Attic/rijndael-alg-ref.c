d42 1
a42 1
#include <stdio.h>
d45 2
d49 1
a49 2
#include "rijndael-api-ref.h"
#include "boxes-ref.h"
d51 10
a60 5
static AES_BYTE shifts[3][4][2] = {
  {{ 0, 0 },
   { 1, 3 },
   { 2, 2 },
   { 3, 1 }},
d62 4
a65 9
  {{ 0, 0 },
   { 1, 5 },
   { 2, 4 },
   { 3, 3 }},
 
  {{ 0, 0 },
   { 1, 7 },
   { 3, 5 },
   { 4, 4 }}
d69 1
a69 2
static
AES_BYTE mul(AES_BYTE a, AES_BYTE b) {
d77 1
a77 2
static
void KeyAddition(AES_BYTE a[4][AES_MAXBC], AES_BYTE rk[4][AES_MAXBC], AES_BYTE BC) {
d86 1
a86 2
static
void ShiftRow(AES_BYTE a[4][AES_MAXBC], AES_BYTE d, AES_BYTE BC) {
d90 1
a90 1
	AES_BYTE tmp[AES_MAXBC];
d99 1
a99 2
static
void Substitution(AES_BYTE a[4][AES_MAXBC], const AES_BYTE box[256], AES_BYTE BC) {
d109 1
a109 2
static
void MixColumn(AES_BYTE a[4][AES_MAXBC], AES_BYTE BC) {
d112 1
a112 1
	AES_BYTE b[4][AES_MAXBC];
d125 1
a125 2
static
void InvMixColumn(AES_BYTE a[4][AES_MAXBC], AES_BYTE BC) {
d129 1
a129 1
	AES_BYTE b[4][AES_MAXBC];
d142 1
a142 1
int __rijndaelKeySched (AES_BYTE k[4][AES_MAXKC], int keyBits, int blockBits, AES_BYTE W[AES_MAXROUNDS+1][4][AES_MAXBC]) {
d148 1
a148 1
	AES_BYTE tk[4][AES_MAXKC];   
d204 1
a204 1
int __rijndaelEncrypt (AES_BYTE a[4][AES_MAXBC], int keyBits, int blockBits, AES_BYTE rk[AES_MAXROUNDS+1][4][AES_MAXBC])
d249 1
a249 1
int __rijndaelDecrypt (AES_BYTE a[4][AES_MAXBC], int keyBits, int blockBits, AES_BYTE rk[AES_MAXROUNDS+1][4][AES_MAXBC])
d301 1
a301 1
int __rijndaelDecryptEqvtInv (AES_BYTE a[4][AES_MAXBC], int keyBits, int blockBits, AES_BYTE rk[AES_MAXROUNDS+1][4][AES_MAXBC])
