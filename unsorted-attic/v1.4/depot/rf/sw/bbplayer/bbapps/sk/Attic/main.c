d93 1
a93 2
  field_2n private_key1, private_key2, shared_secret1, shared_secret2;
  
d97 1
d106 4
a109 4
  
  random_field( &private_key1);
  random_field( &private_key2);
  
d112 1
d124 2
a125 2
  print_field("Private key 1", &private_key1);
  print_field("Private key 2", &private_key2);
d128 1
a128 1
  err = generate_public_key(&named_point, &named_curve, &private_key1, &public_key1);
d130 1
a130 1
  print_point("Public Key 1 ", &public_key1);
d132 1
a132 1
  err = generate_public_key(&named_point, &named_curve, &private_key2, &public_key2);
d134 1
a134 1
  print_point("Public Key 2 ", &public_key2);
d138 2
a139 2
  err = generate_shared_key(&named_point, &named_curve, &public_key2, &private_key1, &shared_secret1);
  print_field("Shared Key 1 ", &shared_secret1);
d141 2
a142 2
  err = generate_shared_key(&named_point, &named_curve, &public_key1, &private_key2, &shared_secret2);
  print_field("Shared Key 2 ", &shared_secret2);
d144 13
