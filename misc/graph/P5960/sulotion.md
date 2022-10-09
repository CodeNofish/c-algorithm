`xi - xj <= c`
反向边 add(j, i, c); 求dist

`xi - xj >= c`
正向边 add(i, j, c); 求dist

`xi == xj`
`xi - xj <= 0 && xi - xj >= 0`
add(j, i, 0);
add(i, j, 0);

+ 超级源点