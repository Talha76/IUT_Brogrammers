int basis[21] = {}, sz = 0;
 
auto insert = [&](int x) {
  while (x) {
    int i = __builtin_ctz(x & -x);
    if (not basis[i]) {
      basis[i] = x;
      sz++;
      return x;
    }
    x ^= basis[i];
  }
  return 0;
};
