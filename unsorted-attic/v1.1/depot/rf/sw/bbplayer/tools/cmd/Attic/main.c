d201 1
a201 1
    computeEccSig(input_string, 1024, private_keyS, rand_input, eccsign);
d208 1
a208 1
    verifyEccSig(input_string, 1024, public_keyS, eccsign, &res);
